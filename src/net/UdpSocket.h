//
// Created by zjl on 10/28/16.
//

#ifndef TRAFFICER_UDPSOCKET_H
#define TRAFFICER_UDPSOCKET_H

#include "Socket.h"

class UdpSocket : public Socket {
public:
    UdpSocket(bool bIpv6);
    virtual ~UdpSocket();

    ssize_t sendData(const char *data, size_t length, InetAddress &remoteAddr);
    ssize_t recvData(char *buffer, size_t length, InetAddress &peerAddr);
};


#endif //TRAFFICER_UDPSOCKET_H
