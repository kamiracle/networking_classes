//
//  main.c
//  XPNetworkingClient
//
//  Created by Kyle Miracle on 4/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>



#define BUFSIZE 200

int main(int argc, const char * argv[])
{

    int sockfd;
    short inPort = 12345;
    char buffer[20] = "Hello server";
    struct sockaddr_in serverAddress;
    
    if ( argc < 2 ) {
        printf("%s", "Usage: XPNetworkingClient ipaddress\n");
        exit(1);

    }
    
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror( "socket" );
        exit(1);
    }
    else {
        printf("Successful call of socket()\n");
    }
        
    //bzero(&serverAddress, sizeof(serverAddress));
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(inPort);
    
    inet_pton( AF_INET, argv[1], &serverAddress.sin_addr);
    
    if ( connect( sockfd, (struct sockaddr *)&serverAddress,
                 sizeof(serverAddress)) < 0 ) 
    {
        perror("connect");
        exit(1);
    }
    
    if ( write( sockfd, buffer, 20) < 0) {
        perror("write");
        exit(1);
    }
}

