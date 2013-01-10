/*
 * CarProject
 * iOS controlled Car from scratch
 * C++ and ArduinoLib
 * Raaj 2012 
 */

/************************************************************************
 * Car Project
 
 This class does the following:
 
 0. Ensure you set-up your WiFly device first (read instructions)
 1. Car Project is to be an easy to use WiFi Car
 2. It is meant to be used with a mobile WiFi hotspot
 3. Communication uses UDP and must be set manually on the WiFly
 4. Correct IP Addresse and Port number must also be set
 5. 10K resistor between WiFly pins 1 and 3 if used with breakout
 ************************************************************************/

//Include Paths (ADD ARDUINOCORE AND ARDUINOCORE/LIBRARIES TO DIRECTORIES IN PROPERTIES/TOOLCHAIN!)
#include <avr/io.h>
#define F_CPU == 16000000
#define ARDUINO 101
#include "Arduino.h"
#include "Arduino/WiFly/MyWiFi.h"

//Public Objects and variables. Pins 3 and 2 for UART to WiFly
MyWiFi WiFly(3,2); 
boolean bWiFiAvailable=false;
boolean responseFromDevice=false;

//To turn on if connected to iOS WiFi
void SuccessLED(){
	pinMode(8, OUTPUT);  
	digitalWrite(8, HIGH);
}

//To turn on if serial response received from iOS App
void ConnectedLED(){
		pinMode(9, OUTPUT);
		digitalWrite(9, HIGH);
}

//Check if Car is connected to WiFi. Timeout after 8s and reboot to retry if wanted
void CheckWiFly(boolean reboot){
	Serial.println("Checking WiFi");
	bWiFiAvailable=WiFly.CheckForWiFi(8000,reboot);
	if(bWiFiAvailable==false)
		Serial.println("No Wi-Fi Found");
	else{
		Serial.println("WiFi Connected");
		SuccessLED();
	}		
}

//Set up protocol-Arduino.h
void setup() {
	Serial.begin(9600);
	CheckWiFly(true);
}

//Loop protocol-Arduino.h
void loop() {
	
	//Connected to WiFi but no response from App yet-Keep sending character 'r' and wait for App to receive from App 'r'
	if(bWiFiAvailable==true && responseFromDevice==false){			
		responseFromDevice=WiFly.SendUART('r','r');
		if(responseFromDevice==true){
			ConnectedLED();
			Serial.print("YES");
		}			
		
	//Not connected yet, so keep checking, but without rebooting WiFly
	}else if(bWiFiAvailable==false){
		CheckWiFly(false);

	//There is a response from App, so execute Motor code
	}else if(responseFromDevice==true){
		WiFly.Ready();
	}
}