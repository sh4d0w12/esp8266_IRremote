# esp8266_IRremote
IR library for esp8266 using Sming framework.</br>
The code is a port of [Ken Shirriffs' IR library for Arduino](http://www.righto.com/2009/08/multi-protocol-infrared-remote-library.html "Ken Shirriffs' IR library for Arduino")

### IR Reception Details
The receiver code is identical to the one in the original library. A timer routine executes every 50us and appends the data to a buffer. The user then call a decode routine and if it can be decoded then it is returned.

### IR Transmission Details
The IR transmission is done using bit-banging. Although far from ideal it works and the software PWM in the Sming framework could not operate dependably at the desired frequency. I will revisit this when I get a chance and see if I can get a different PWM methodology to work. In essence the current method simply transitions between the on/off states using delays. 
