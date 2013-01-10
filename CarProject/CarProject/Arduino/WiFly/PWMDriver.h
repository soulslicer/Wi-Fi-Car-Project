/*
 * PWM.h
 *
 * Created: 12/19/2012 12:28:43 PM
 *  Author: Raaj
 */ 

/************************************************************************
 * PWM Class (Non-interrupt based)
 
 This class does the following:
 
 1. Takes in a response of speeds X and Y
 2. X refers to Motor 1 and Y refers to Motor 2
 3. If speed is negative, automatically set to reverse
 4. Non-asynchronous, and requires Pulse() to be placed in a loop
 ************************************************************************/

#ifndef __PWM_H__
#define __PWM_H__

//Include Paths
#include "Arduino.h"

//Define connections from driver and direction
#define DRIVER_M1 4
#define DIR_M1 5
#define DRIVER_M2 6
#define DIR_M2 7

class PWM{
	
  public:
	PWM();									//Constructor
	void Pulse();							//Send an on-off pulse
	void Reset();							//Reset and set speed and direction to 0
	int X;									//X Speed (Yes, could have used a setter getter)
	int Y;									//Y Speed (Yes, could have used a setter getter)
	
  private:
	void SpeedSetter(int x,int motNum);		//Set speed (-9 to 9) and which motor it is set to
	boolean firstLoad;						//Initial load
	
	int stateM1;							//On off motor state for motor 1
	int stateM2;							//On off motor state for motor 2
	
	unsigned long currTimeM1;				//Pulse time for motor 1
	unsigned long currTimeM2;				//Pulse time for motor 2
	
};


#endif