//
//  UDP.h
//  Controller
//
//  Created by Yaadhav Raaj on 19/12/12.
//  Copyright (c) 2012 Yaadhav Raaj. All rights reserved.
//

#ifndef Controller_UDP_h
#define Controller_UDP_h

//Include Paths
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

//Network struct
struct NETWORK_SETTINGS{
    char* SEND_UDP_ADD;
    char* REC_UDP_ADD;
    char* SEND_UDP_PORT;
    char* REC_UDP_PORT;
}Settings;

//Functions to send and receive
void UDPInit(char* SEND_ADD,char* REC_ADD,char* SEND_PORT,char* REC_PORT);
void UDPSend(char* x);
void UDPRec(char x[]);



#endif
