#include "MyWiFi.h"

//Constructor-Start listen on uart
MyWiFi::MyWiFi(byte pinReceive, byte pinSend) : uart (pinReceive, pinSend),pwm() {
	uart.begin(WIFLY_DEFAULT_BAUD_RATE);
	uart.listen();
	uart.flush();
}

//Check if two strings/char* are the same
boolean checkForString(char* responseBuffer,char* compare){
	char * pch=NULL;
	pch = strstr (responseBuffer,compare);
	if(pch==NULL)
	return false;
	else
	return true;
}

//Read and process <> command from App and set PWM speed accordingly. Yes i know this is an awful idea too late :(
void MyWiFi::readSpeed(){
	
	int X;
	int Y;
	
	boolean bufRead = true;
	char chResponse = 'A';
	
	boolean openResponse=false;
	boolean readingX=false;
	boolean readingY=false;
	boolean minusState=false;
	
	while(bufRead){
		
		if(uart.available()){
			
			//Read input from WiFly
			chResponse = uart.read();
			
			//Check for first space
			if(chResponse==' '){
				continue;
			}
			
			//Check for <> in response
			if(chResponse=='<'){
				openResponse=true;
				continue;
			}else if(chResponse=='>'){
				openResponse=false;
				bufRead=false;
			}
			
			//Check for X
			if(chResponse=='X'){
				readingX=true;
				readingY=false;
				continue;
			}else if(chResponse=='Y'){
				readingY=true;
				readingX=false;
				continue;				
			}	
			
			if(readingX==true){
				
				//Ignore Open Bracket
				if(chResponse=='('){
					continue;
				}
				
				//Check for Minus
				if(chResponse=='-'){
					minusState=true;
					continue;
				}
				
				//Ignore Close Bracket
				if(chResponse==')'){
					continue;
				}
				
				//Now we will read the number for sure
				if(minusState==false){
					X = chResponse - '0';
					continue;
				}else if(minusState==true){
					X = chResponse - '0';
					X*=-1;
					minusState=false;
					continue;
				}
				
			}else if(readingY==true){
				
				//Ignore Open Bracket
				if(chResponse=='('){
					continue;
				}
				
				//Check for Minus
				if(chResponse=='-'){
					//Serial.println("read -");
					minusState=true;
					continue;
				}
				
				//Ignore Close Bracket
				if(chResponse==')'){
					continue;
				}
				
				//Now we will read the number for sure
				if(isDigit(chResponse)){
				if(minusState==false){
					Y = chResponse - '0';
					continue;;
				}else if(minusState==true){
					Y = chResponse - '0';
					Y*=-1;
					minusState=false;
					continue;
				}	
								
	}}}}

	//Set PWM values
	pwm.X=X;
	pwm.Y=Y;
	
	/*Serial.print(X);
	Serial.print("-");
	Serial.print(Y);
	Serial.println("");*/
	
}

//Send a char and see if the expected one was received
boolean uartLoad=true;
boolean MyWiFi::SendUART(char send,char rec){
	
	if(uartLoad==true){
		delay(500);
		uart.flush();
		uartLoad=false;
		return false;
	}
	
	uart.print(send);
	if(uart.available()){
		char ch=uart.read();
		Serial.print(ch);
		if(ch==rec)
			return true;
		else
			return false;
	}else{
		Serial.println("none");	
	}		
		delay(1000);
	return false;

}

boolean firstLoad=true;
void MyWiFi::Ready(){
	
	//Perform some initial functions and delays
	if(firstLoad==true){
		pwm.X=0;
		pwm.Y=0;
		uart.flush();
		delay(100);
		uart.print("X");
		delay(100);
		uart.print("O");
		delay(100);
		uart.print("X");
		Serial.println("Ready!");
		firstLoad=false;
	}
	
	//If a change in speed response received, change pwm speed
	if(uart.available()){
		pwm.Reset();
		readSpeed();
		uart.flush();
		pwm.Reset();
	}
	
	//If no response, send the pwm pulses to run the dual motors
	pwm.Pulse();	
}

//Reboot WiFly
void MyWiFi::RebootWiFly(){
	uart.print("$$$");
	delay(200);
	uart.print("reboot\r");
}

//Check for WiFi connection from iOS device
boolean MyWiFi::CheckForWiFi(int successWaitTime,int reboot){
	
	//Reboot if true
	if(reboot==true)
		RebootWiFly();
	
	//Variables
	char* responseBuffer;										//Buffer for response
	boolean bufRead = true;										//Finish Reading
	int  bufpos = 0;											//Buffer position
	char chResponse = 'A';										//Initial character response
	int  bufsize = RESPONSE_BUFFER_SIZE -1;						//terminating null for bufsize
	boolean bWiFiState=false;									//boolean for WiFi state
	int noResponseCount=0;										//No response, assume connected
	
	//Reset the buffer
	responseBuffer = (char*) malloc(RESPONSE_BUFFER_SIZE);
	memset (responseBuffer, '\0', bufsize);
	
	//Fill the buffer
	unsigned long startTime = millis();
	while(bufRead){
		
		if(uart.available()){
			//Read input from WiFly
			chResponse = uart.read();	
			
			//Write to buffer
			responseBuffer[bufpos]=chResponse;
			bufpos++;	
		}
		
		//if there is no response after timeout period, assume no connection
		if(checkForString(responseBuffer,"NONE")){
			noResponseCount++;
			if(noResponseCount>2){
				bufRead=false;
				bWiFiState=false;
			}
		}else if(checkForString(responseBuffer,"OK")){
			bufRead=false;
			bWiFiState=true;
		}else if((millis()-startTime)>successWaitTime){
			bufRead=false;
			bWiFiState=false;
		}	
	}
	
	return bWiFiState;
}