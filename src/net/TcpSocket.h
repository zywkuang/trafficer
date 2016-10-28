//
// Created by zjl on 10/27/16.
//

#ifndef TRAFFICER_TCPSOCKET_H
#define TRAFFICER_TCPSOCKET_H

#include "Socket.h"

class TcpSocket : public Socket{
public:
    TcpSocket(bool bIpv6 = false);
    TcpSocket(int sockfd, bool bIpv6 = false);
    virtual ~TcpSocket();

    ssize_t sendData(const char *data, int length);
    ssize_t recvData(char *buffer, int length);

    void setLocal();
    void setConnected();

    // Client Function
    void connectServer(InetAddress &remoteAddr);

    // Server Function
    void listenServer(InetAddress &localAddr);
    TcpSocket* acceptClient();

private:
    bool bLocalSet;
    bool bIsConnected;

    InetAddress localAddr;
    InetAddress peerAddr;
};

#endif //TRAFFICER_TCPSOCKET_H
