# Wi-Fi Car Project

A very easy to build an modify WiFi Car controlled currently via an iOS App.

Ever wanted to build a Wi-Fi controlled Arduino device? This project gets you started by introducing Wi-Fi communication, C++ programming on Arduino, writing Serial drivers, UDP Communication and PWM.

Set it up as follows:

### Hardware Needed

1. Breadboard or Solder+Circuit board
2. Arduino Nano
3. RN-XV WiFly Device
4. L293D DC Motor Driver
4. 5V Power source (USB Brick perhaps)
5. Sparkfun Explorer breakout+Sparkfun explorer USB
6. 10k resistor, LEDS and 220 ohm resistors
7. Wires and wire stripper
8. USB Cables

### Software Needed

1. ArduinoCore Library (Provided)
2. Atmel Studio Windows (C++ and Atmega328P)
3. Mac OSX, Xcode and iPhone (If you want to use another platform, read below)
4. CoolTerm for Windows
5. FTDI USB Driver for OSX/Windows


## Setting Up Software

1. The Car/Arduino is programmed to first connect to the iOS devices Wi-Fi, which turns the yellow light on. 
2. It will then start sending a character out (currently 'r') and it is read by the iOS app which sends back 'r'. 3. ```
3. The Green light now lights up when it is received and now the car can accept speeds
4. It accepts the following string example: "< X(-5) Y(6) >\r"
5. X refers to motor 1 and Y to motor 2


###RN-XV WiFly

```
Setting up the RN-XV using CoolTerm

1. Install FTDI USB Driver
2. Plug RN-XV in and set Baud Rate in CoolTerm to 9600
3. Connect it
4. Type '$$$' to enter command mode
5. Enter the following commands to connect to your hotspot

set wlan phrase <password>		//Set WiFi password
set wlan ssid <your ssid>		//Set to SSID of hotspot
save							//Save settings
reboot							//Reboot to take effect

6. Re-enter Command Mode '$$$'
7. Enter UDP mode and set up your ports and IP Address (Page 49 of manual)

set ip proto 1 					// enable UDP as the protocol
set ip host <ip address> 		// set the IP address of remote host
set ip remote <port> 			// set the remote port listen port
set ip local <port> 			// set the port number WiFly listens
save 							// saves the settings in config file
reboot 							// reboot module

```

###Atmel Studio

1. Open CarProject solution
2. Follow Step 4 on this site [ArduinoCore](http://www.jayconsystems.com/tutorial/atmerpt2/)
3. Begin looking at the code!

###iOS App

1. Simply open Controller.project
2. Navigate to the viewDidLoad function
3. Set up your Ports and IP as show below (Re-use WiFly settings)
 
```
UDPInit(char* SEND_ADD,char* REC_ADD,char* SEND_PORT,char* REC_PORT);
```

##Setting Up Hardware

![ScreenShot](http://www.a-iats.com/App/diag2.png)



## Notes

* iOS App written in Objective-C
* UDP Drivers written in C using Berekly Socket Programming
* Arduino programmed in C++ via Atmel Studio
* ArduinoCore packaged by me, contains all required drivers. Using Arduino Libraries
* All devices can be purchased from Sparkfun
* [Video](https://www.youtube.com/watch?v=lQIcHcv1s0U)

LICENSE
-------

Copyright (C) 2012 by Raaj

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.