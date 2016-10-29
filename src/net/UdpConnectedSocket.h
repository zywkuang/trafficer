//
// Created by zjl on 10/28/16.
//

#ifndef TRAFFICER_UDPCONNECTEDSOCKET_H
#define TRAFFICER_UDPCONNECTEDSOCKET_H

#include "Socket.h"

class UdpConnectedSocket : public Socket {
public:
    UdpConnectedSocket(bool bIpv6 = false);
    UdpConnectedSocket(int sockfd, bool bIpv6 = false);
    virtual ~UdpConnectedSocket();

    ssize_t sendData(const char *data, int length);
    ssize_t recvData(char *buffer, int buflen);

    // Client Function
    void connectServer(InetAddress &remoteAddr);

    // Server Function
    void listenServer(InetAddress &localAddr);
    UdpConnectedSocket* acceptClient();

private:
    bool bIsConnected;

    InetAddress localAddr;
    InetAddress peerAddr;
};


#endif //TRAFFICER_UDPCONNECTEDSOCKET_H
