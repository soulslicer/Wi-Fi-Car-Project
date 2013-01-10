/*
 * MyWiFi.h
 *
 * Created: 12/19/2012 12:28:43 PM
 *  Author: Raaj
 */ 

#ifndef __WIFLYSERIAL_H__
#define __WIFLYSERIAL_H__

/************************************************************************
 * WiFly Class
 
 This class does the following:
 
 1. Send and receive a response from Car to iOS App
 2. Reboot WiFly device and check for WiFi connection
 3. Interrupts and receives when response sent from iOS App
 4. Calls pulse on PWM to run the motors
 ************************************************************************/

//Include Paths
#include <SoftwareSerial.h>
#include <Streaming.h>
#include <avr/pgmspace.h>
#include "PWMDriver.h"

//RX TX Pins
#define ARDUINO_RX_PIN  2
#define ARDUINO_TX_PIN  3

// default ports as set in WiFly - if you change these, make certain you call setRemotePort/setLocalPort
#define WIFLY_DEFAULT_REMOTE_PORT 80    
#define WIFLY_DEFAULT_LOCAL_PORT 2000  
#define WIFLY_DEFAULT_BAUD_RATE 9600

//On line-Off line Status
#define WIFLY_STATUS_OFFLINE    0
#define WIFLY_STATUS_ONLINE     1

//Char Buffer Sizes for Command and Response
#define COMMAND_BUFFER_SIZE 64
#define SMALL_COMMAND_BUFFER_SIZE 20
#define RESPONSE_BUFFER_SIZE 80
#define INDICATOR_BUFFER_SIZE 16

//CMD Wait Times based on manual
#define COMMAND_MODE_GUARD_TIME 	300
#define DEFAULT_WAIT_TIME			1000UL
#define ATTN_WAIT_TIME				1000UL
#define JOIN_WAIT_TIME 				10000UL

class MyWiFi{
	
  public:
	MyWiFi(byte pinReceive, byte pinSend);						//Constructor with Pins for UART
	SoftwareSerial uart;										//SoftwareSerial driver
	PWM pwm;													//PWM Driver

	void Ready();												//Loop to receive and execute commands
	boolean SendUART(char send,char rec);						//True if sent a character to App and receive the correct one
	boolean CheckForWiFi(int successWaitTime,int reboot);		//Check if Car is connected to iOS WiFi
	void RebootWiFly();											//Reboots the WiFly device
  
  private:
	void readSpeed();											//Read the <> command string and process it

	
 };
 
 #endif