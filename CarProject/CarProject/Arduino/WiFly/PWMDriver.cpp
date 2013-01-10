/*
 * PWM.cpp
 *
 * Created: 12/19/2012 12:28:55 PM
 *  Author: Raaj
 */ 

#include "PWMDriver.h"

//Listed are all 9 available speeds. 0 for the 0th index really off. 0 for 1st index is an actual speed
int Speed[10]={0,0,50,100,150,200,400,600,800,1000};
	
//Set speed (-9 to 9) and motor number (1 or 2)
void PWM::SpeedSetter(int x,int motNum){

	if(motNum==1){

		//If speed 0 do nothing
		if(x==0){
			currTimeM1=micros();
			return;
		}
		
		//Get actual speed from value
		boolean reverse=false;
		int setSpeed;
		if(x>=0){
			setSpeed=Speed[x];
			reverse=false;
		}else{
			setSpeed=(Speed[-x]);
			reverse=true;
		}			
		
		//Direction Control
		if(reverse==true){
			digitalWrite(DIR_M1, HIGH);
		}else{
			digitalWrite(DIR_M1, LOW);
		}
		
		//Do Pulsing of PWM
		if((micros()-currTimeM1)>=setSpeed){
			if(stateM1==0){
				digitalWrite(DRIVER_M1, HIGH);
				stateM1=1;
			}else{
				digitalWrite(DRIVER_M1, LOW);
				stateM1=0;
			}
			
			//Reset Time
			currTimeM1=micros();
		}
		
	}else if(motNum==2){

		//If speed 0 do nothing
		if(x==0){
			currTimeM2=micros();
			return;
		}
		
		//Get actual speed from value
		boolean reverse=false;
		int setSpeed;
		if(x>=0){
			setSpeed=Speed[x];
			reverse=false;
		}else{
			setSpeed=(Speed[-x]);
			reverse=true;
		}
		
		//Direction Control
		if(reverse==true){
			digitalWrite(DIR_M2, HIGH);
		}else{
			digitalWrite(DIR_M2, LOW);
		}
		
		//Do Pulsing of PWM
		if((micros()-currTimeM2)>=setSpeed){
			if(stateM2==0){
				digitalWrite(DRIVER_M2, HIGH);
				stateM2=1;
			}else{
				digitalWrite(DRIVER_M2, LOW);
				stateM2=0;
			}
			
			//Reset Time
			currTimeM2=micros();
		}
	}		
	
}

//Constructor
PWM::PWM(){
	firstLoad=true;
	stateM1=0; stateM2=0;
	currTimeM1=micros(); currTimeM2=micros();
	X=1;
	Y=1;

	pinMode(DRIVER_M1, OUTPUT);  //Driver M1
	pinMode(DIR_M1,OUTPUT);		 //Direction M1
	pinMode(DRIVER_M2, OUTPUT);  //Driver M1
	pinMode(DIR_M2,OUTPUT);		 //Direction M1
}

//Reset speed and direction
void PWM::Reset(){
	currTimeM1=micros();
	currTimeM2=micros();
	stateM1=0;
	stateM2=0;
	digitalWrite(DIR_M2, LOW);
	digitalWrite(DIR_M1, LOW);
	digitalWrite(DRIVER_M1, LOW);
	digitalWrite(DRIVER_M2, LOW);
}

//Send an on off pulse. To be placed in a loop
void PWM::Pulse(){
	
	if(firstLoad==true){
		currTimeM1=micros();
		currTimeM2=micros();
		firstLoad=false;
	}

	SpeedSetter(X,1);
	SpeedSetter(Y,2);
	
}


