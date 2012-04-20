//
//  main.c
//  XPNetworkingServer
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

int main(int argc, const char * argv[])
{
    struct sockaddr_in serverAddress;
    short inPort = 666;
    int listenfd, connectfd;
    
    if ( (listenfd = socket( AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket");
        exit(1);
    }
        
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(inPort);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if ( bind( listenfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress) ) < 0 ){
        perror("bind");
        exit(1);
    }
    
    if ( listen( listenfd, 5) < 0 ) {
        perror("listen");
        exit(1);
    }
    
    while(1 == 1){
                
        char buffer[] = "Chris is gay\n";
        
        if ( (connectfd = accept( listenfd, (struct sockaddr *)NULL, NULL)) < 0 ) {
            perror("accpet");
            exit(1);
        }
        
        if ( write( connectfd, buffer, strlen(buffer) ) < 0 ) {
            perror( "write" );
            exit(1);
        }
        
        close( connectfd );
        
    }
}

