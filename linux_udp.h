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

int udp_init(udp_stream* stream, const char* connStr );
int udp_connect(udp_stream* stream, const char* remoteIp, uint16_t remotePort);
int udp_send(udp_stream* stream, uint8_t* data, int len);
int udp_recv(udp_stream* stream, uint8_t* data, int len);
int udp_close(udp_stream* stream);


#endif //TEST_UTIL_LINUX_UDP_H
