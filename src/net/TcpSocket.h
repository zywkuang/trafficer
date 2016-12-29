/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

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

    const InetAddress &getLocalAddress();
    const InetAddress &getPeerAddress();

    // Client Function
    void connectServer(InetAddress &remoteAddr);
    void connectServer(InetAddress &remoteAddr, InetAddress &localAddr);

    // Server Function
    void listenServer(InetAddress &localAddr);
    TcpSocket* acceptClient();

protected:
    bool bLocalSet;
    bool bIsConnected;

    InetAddress localAddress;
    InetAddress peerAddress;
};

#endif //TRAFFICER_TCPSOCKET_H
