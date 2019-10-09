#include <Arduino.h>

unsigned long lastLedOn = 0;
unsigned long lastIter = 0;
unsigned long lastLedOff = 0;
unsigned long lastSerial = 0;
double frequency = 1;
double rpm = 0;
bool currentLedState = false;
unsigned long ledDelOff = 25;
unsigned long ledDelOn = 25;
unsigned long ledHold = 100;
unsigned long addition = 10;
bool pause = true;

void setup() {
  DDRD = B00001100;
  PORTD = B00000000;
  lastLedOff = micros();
  Serial.begin(115200);
}

void loop() {
  if (micros() - lastIter >= 100000 && !pause) {
    ledHold++;
    lastIter = micros();
  }
  if (Serial.available() > 0) {
    String readStr = Serial.readString();
    if (readStr.length() >= 1){
      if(readStr.indexOf("+:") >= 0) {
        String number = readStr.substring(2);
        if (number.toInt()>0) {
          addition=number.toInt();
        }
      } else if (readStr.indexOf("+") >= 0) {
        ledHold +=addition;
      } else if (readStr.indexOf("-") >= 0) {
        ledHold -=addition;
      } else if (readStr.indexOf("p") >= 0) {
        pause = !pause;
        Serial.println(ledHold);
      } else {
        ledHold = readStr.toInt();
      }
    }

  }
  if (currentLedState) {
    if ((micros() - lastLedOn) >= ledDelOn) {
      if ((micros() - lastLedOn) >= ledDelOn+ledHold) {
        PORTD &= ~_BV(PD2);
        //PORTD = B00000000;
        currentLedState = false;
        lastLedOff = micros();
      }
    }
  }
  else if (!currentLedState) {
    if ((micros() - lastLedOff) >= ledDelOff) {
      if ((micros() - lastLedOff)>=ledHold+ledDelOff) {
        PORTD |= _BV(PD2);
        //PORTD = B00000100;
        currentLedState = true;
        lastLedOn = micros();
      }
    }
    if (micros() - lastSerial >= 2 * 1000000) {
      frequency = (double)ledDelOn/1000000 + (double)ledHold/1000000 + (double)ledDelOff/1000000 + (double)ledHold/1000000;
      frequency = 1/frequency;
      Serial.print("frequency = ");
      Serial.print(frequency);
      Serial.print("  hold = ");
      Serial.println(ledHold);
      lastSerial = micros();
    }
  }
}
