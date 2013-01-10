//
//  UDP.c
//  Controller
//
//  Created by Yaadhav Raaj on 19/12/12.
//  Copyright (c) 2012 Yaadhav Raaj. All rights reserved.
//

#include "UDP.h"

void UDPInit(char* SEND_ADD,char* REC_ADD,char* SEND_PORT,char* REC_PORT){
    Settings.SEND_UDP_ADD=SEND_ADD;
    Settings.REC_UDP_ADD=REC_ADD;
    Settings.SEND_UDP_PORT=SEND_PORT;
    Settings.REC_UDP_PORT=REC_PORT;
}

void UDPSend(char* x){
    int sock;
    struct sockaddr_in sa;
    int bytes_sent;
    char buffer[200];
    
    strcpy(buffer, x);
    
    //create an internet, datagram, socket using UDP
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (-1 == sock) /* if socket failed to initialize, exit */
    {
        printf("Error Creating Socket\n");
        exit(EXIT_FAILURE);
    }else{
        printf("Socket initialized\n");
    }
    
    //Zero out socket address
    memset(&sa, 0, sizeof sa);
    
    //The address is ipv4
    sa.sin_family = AF_INET;
    
    //ip_v4 adresses is a uint32_t, convert a string representation of the octets to the appropriate value
    
    sa.sin_addr.s_addr = inet_addr(Settings.SEND_UDP_ADD);
    
    //sockets are unsigned shorts, htons(x) ensures x is in network byte order, set the port to 7654
    
    sa.sin_port = htons(atoi(Settings.SEND_UDP_PORT));
    
    //sendto(int socket, char data, int dataLength, flags, destinationAddress, int destinationStructureLength)
    bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
    
    
    if (bytes_sent < 0) {
        printf("Error sending packet: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }else{
        printf("byte sent");
    }
    
    close(sock); /* close the socket */

}

void UDPRec(char* x){
    // datagram sockets and recvfrom()
    
    struct addrinfo hints, *res;
    int sockfd;
    int byte_count;
    socklen_t fromlen;
    struct sockaddr_storage addr;
    char buf[1];
    char ipstr[INET6_ADDRSTRLEN];
    char fillBuf[256];
    int bufPos=0;
    
    char* tempSides;
    tempSides = (char *)malloc(strlen(x));
    tempSides[strlen(x)] = '\0';
    
    // get host info, make socket, bind it to port 4950
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    
    //addr.sin_addr.s_addr = inet_addr("172.20.10.3");
    //getaddrinfo("172.20.10.3", "50000", &hints, &res);
    getaddrinfo(Settings.REC_UDP_ADD, Settings.REC_UDP_PORT, &hints, &res);
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    
    while(1){
        fromlen = sizeof addr;
        byte_count = recvfrom(sockfd, buf, sizeof buf, 0, &addr, &fromlen);
    
        printf("%c\n",buf[0]);
        tempSides[bufPos]=buf[0];
        bufPos++;
        
        if(strcmp(x,tempSides)==0)
        {
            break;
        }
    }
}


