RS485-Arduino-Library
=====================
Arduino Library for use with RS485 devices. It creates a software-serial on pins D2(RX) and D3(TX) that is connected to a RS485 chip. 

Pin D4 is enabled when sending data over the data bus.

I used SN75176BP chip to transmit the data over CAT5 cable and Arduino UNO.


How to install it:
==================
Down load the library from GitHub : https://github.com/Protoneer/RS485-Arduino-Library/archive/master.zip

Unzip the library and copy the main folder into the "Libraries" folder in the folder you installed your Arduino software. Eg. C:\arduino-1.0.3\libraries\

Rename the folder to "RS485" (This will stop the Arduino IDE from complaining about the long folder name)

Open up the Arduino IDE.

Click on the following menu : File -> Examples -> RS485 (or what ever you renamed the folder to) -> Sender or Receiver

Upload the sketch to your Arduino board.
