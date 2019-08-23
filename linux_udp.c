//
// Created by Jason on 8/22/2019.
//
#include <fcntl.h>
#include "linux_udp.h"

int udp_init(udp_stream* stream, uint16_t localPort )
{
    int err = 0;
    int sock_flags;

    //setup socket addr
    if ((stream->mSock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Failed to create socket");
    }

    //Set socket to non-blocking
    sock_flags = fcntl(stream->mSock,F_GETFL);
    sock_flags |= O_NONBLOCK;
    fcntl(stream->mSock, F_SETFL, sock_flags);

    //Configure port and bind socket
    memset(&stream->mLocalAddr, 0, sizeof(stream->mLocalAddr));
    stream->mLocalAddr.sin_family = AF_INET;
    stream->mLocalAddr.sin_addr.s_addr = INADDR_ANY;
    stream->mLocalAddr.sin_port = htons(localPort);

    if (bind(stream->mSock, (struct sockaddr*)&stream->mLocalAddr, sizeof(struct sockaddr_in)) < 0)
    {
        printf("Failed to bind socket to port\n");
        err = 1;
    }

    if(err == 0)
    {
        printf("Service listening on Port %d\r\n", localPort);
    }

    stream->mConnected = 0;

    return err;
}

int udp_connect(udp_stream* stream, char* remoteSocket)
{

    int result;

    char* copy = strdup(remoteSocket);
    char* remoteIp = "localhost";//strtok(copy,":");
    char* strPort = "8010";// strtok(NULL,"");
    uint16_t  remotePort= atoi(strPort);

    printf("ip: %s port: %u\n", remoteIp, remotePort);
    stream->mRemoteAddr.sin_family = AF_INET;
    stream->mRemoteAddr.sin_port = htons(remotePort);

    if ((stream->mRemoteAddr.sin_addr.s_addr = inet_addr(remoteIp)) == INADDR_NONE)
    {
        struct hostent *host=NULL;

        host = gethostbyname(remoteIp);
        if (host)
            memcpy(&stream->mRemoteAddr.sin_addr, host->h_addr_list[0], host->h_length);
        else
        {
            printf("gethostbyname() failed\r\n");
            return 1;
        }
    }

    stream->mConnected = 1;
    free(copy);
    return 0;
}

int udp_send(udp_stream* stream, uint8_t* data, int len)
{
    int txLen;

    txLen = sendto(stream->mSock, data, len, 0 , (const struct sockaddr *) &stream->mRemoteAddr, sizeof(stream->mRemoteAddr));

    return txLen;
}

int udp_recv(udp_stream* stream, uint8_t* data, int len)
{
    struct sockaddr_in peerAddr;
    int addrLen;

    int rxLen = recvfrom(stream->mSock, data,  len, 0, (struct sockaddr*)&peerAddr, &addrLen );
    if((rxLen > 0) && (!stream->mConnected))
    {
        stream->mRemoteAddr.sin_port = peerAddr.sin_port;
        stream->mRemoteAddr.sin_addr = peerAddr.sin_addr;
        printf("Connection established with %s:%u \n", inet_ntoa(peerAddr.sin_addr), ntohs(peerAddr.sin_port));
        stream->mRemoteAddr.sin_family = AF_INET;
        stream->mConnected = 1;
    }

    return rxLen;
}