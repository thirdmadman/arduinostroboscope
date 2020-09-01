# arduinostroboscope
Arduino stroboscope with only one led and nothing more
Wire up led "-" to the GND and "+" to the digital port 2.
Open serial port with 115200 and send half-period time.
Command "+:" + DIGIT allows you to set increment half-period
Command "+" and "-" allows you to increment half-period
Command "p" set auto increment to pause

How to use: place small white sticky-strip on rotation body (from center to the edge). Connect your device to the serial monitor, activate rotation of the rotary body. Watch for strip becomes visible while time increments. Whet see this - stop increment with "p". Get frequency from serial monitor.
