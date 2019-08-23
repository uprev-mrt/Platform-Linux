//
// Created by Jason on 8/22/2019.
//

#ifndef LINUX_UDP_H
#define LINUX_UDP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <assert.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <limits.h>


typedef struct{
    struct sockaddr_in mLocalAddr;
    struct sockaddr_in mRemoteAddr;
    int mSock;
    uint8_t mConnected;
} udp_stream;

int udp_init(udp_stream* stream, uint16_t localPort );
int udp_connect(udp_stream* stream, char* remoteSocket);
int udp_send(udp_stream* stream, uint8_t* data, int len);
int udp_recv(udp_stream* stream, uint8_t* data, int len);


#endif //TEST_UTIL_LINUX_UDP_H
