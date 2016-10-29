//
// Created by zjl on 10/27/16.
//

#ifndef TRAFFICER_SOCKET_H
#define TRAFFICER_SOCKET_H

#include "InetAddress.h"
#include "../base/NonCopyable.h"

class Socket : public NonCopyable{
public:
    Socket(bool bipv6 = false, int proto = SOCK_STREAM);
    Socket(int sockfd, bool bipv6 = false, int proto = SOCK_STREAM);
    virtual ~Socket();

    void socketConnect(InetAddress &remoteAddr);
    void socketBind(InetAddress &localAddr);
    void socketListen();
    int socketAccept(InetAddress &peerAddr);
    void socketClose();

    bool resolveLocalAddr(InetAddress &localAddr);
    bool resolvePeerAddr(InetAddress &peerAddr);

    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void setTcpNoDelay(bool on);
    void setKeepAlive(bool on);

    ssize_t socketSend(const char *payload, size_t length, int flag = 0);
    ssize_t socketRecv(char *buffer, size_t length, int flag = 0);

    ssize_t socketSendTo(const char *payload, size_t length, InetAddress &remoteAddr, int flag = 0);
    ssize_t socketRecvFrom(char *buffer, size_t length, InetAddress &peerAddr, int flag = 0);

    int getSockFd() {
        return this->sockfd;
    }

    int setSockFd(int newFd) {
        this->sockfd = newFd;
    }

private:
    int sockfd;  // socket descriptor

    int proto;   // protocol: tcp or udp
    bool bipv6;  // family: ipv4 or ipv6
};


#endif //TRAFFICER_SOCKET_H
