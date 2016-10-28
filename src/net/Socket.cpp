//
// Created by zjl on 10/27/16.
//

#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include "Socket.h"
#include "../base/Exception.h"

Socket::Socket(bool bipv6, int proto)
    : bipv6(bipv6), proto(proto) {
    this->sockfd = socket((bipv6) ? AF_INET6 : AF_INET, proto, 0);

    if (this->sockfd < 0) {
        printf("LOG ERROR: Cannot create new socket.\n");
        throw Exception(ESOCKCREATE, "Create Socket Exception");
    }
}

Socket::Socket(int sockfd, bool bipv6, int proto)
    : sockfd(sockfd), bipv6(bipv6), proto(proto) {

}

Socket::~Socket() {
    this->socketClose();
}

void Socket::socketConnect(InetAddress &remoteAddr) {

    int ret = connect(this->sockfd, remoteAddr.getSockAddr(), static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
    if (ret < 0) {
        printf("LOG ERROR: Cannot connect to remote socket.\n");
        switch (errno) {
            case EISCONN:
                throw Exception(EISCONN, "Already Connected Exception");
            case ECONNREFUSED:
                throw Exception(ECONNREFUSED, "Connect Refused Exception");
            case ETIMEDOUT:
                throw Exception(ETIMEDOUT, "Timed Out Exception");
            case ENETUNREACH:
                throw Exception(ENETUNREACH, "Network Unreachable Exception");
            case EADDRINUSE:
                throw Exception(EADDRINUSE, "Address Inuse Exception");
            default:
                throw Exception(ESOCKCONNECT, "Connect Failure Exception");
        }
    }
}

void Socket::socketBind(InetAddress &localAddr) {

    int ret = bind(this->sockfd, localAddr.getSockAddr(), static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
    if (ret < 0) {
        printf("LOG ERROR: Cannot bind to specific address.\n");
        switch (errno) {
            case EINVAL:
                throw Exception(EINVAL, "Already Bound Exception");
            case EADDRINUSE:
                throw Exception(EADDRINUSE, "Address Inuse Exception");
            default:
                throw Exception(ESOCKBIND, "Bind Failure Exception");
        }
    }
}

void Socket::socketListen() {

    int ret = listen(this->sockfd, SOMAXCONN);
    if (ret < 0) {
        printf("LOG ERROR: Cannot listen on socket.\n");
        throw Exception(ESOCKLISTEN, "Listen Failure Exception");
    }
}

int Socket::socketAccept(InetAddress &peerAddr) {
    struct sockaddr_in6 addr;
    memset(&addr, 0, sizeof(struct sockaddr_in6));
    socklen_t  addrlen = static_cast<socklen_t>(sizeof(struct sockaddr_in6));

    int connFd = accept(this->sockfd, static_cast<sockaddr *>(static_cast<void *>(&addr)), &addrlen);
    if (connFd < 0) {
        printf("LOG ERROR: Cannot accept new connection.\n");
        throw Exception(ESOCKACCEPT, "Accept Failure Exception");
    }

    peerAddr.setSockAddrIn6(addr);
    return connFd;
}

void Socket::socketClose() {
    close(this->sockfd);
}

ssize_t Socket::socketSend(const char *payload, size_t length, int flag) {
    ssize_t  bytesSent = 0;

    bytesSent = send(this->sockfd, payload, length, flag);
    if (bytesSent < 0) {
        printf("LOG ERROR: Cannot send data to peer host.\n");
        switch (errno) {
            case EAGAIN:
                throw Exception(EAGAIN, "Would Block Exception");
            default:
                throw Exception(ESOCKWRITE, "Send Data Exception");
        }
    }

    return bytesSent;
}

ssize_t Socket::socketRecv(char *buffer, size_t length, int flag) {
    ssize_t bytesRcvd = 0;

    bytesRcvd = recv(this->sockfd, buffer, length, flag);
    if (bytesRcvd < 0) {
        printf("LOG ERROR: Cannot recv data from peer host.\n");
        throw Exception(ESOCKREAD, "Read Data Exception");
    } else if (bytesRcvd == 0) {
        printf("LOG ERROR: Peer host disconnected.\n");
        throw Exception(ENOTCONN, "Not Connected Exception");
    }

    return bytesRcvd;
}

ssize_t Socket::socketSendTo(const char *payload, size_t length, int flag, InetAddress &remoteAddr) {
    ssize_t bytesSent = 0;
    socklen_t addrlen = static_cast<socklen_t>(sizeof(struct sockaddr_in6));

    bytesSent = sendto(this->sockfd, payload, length, flag, remoteAddr.getSockAddr(), addrlen);
    if (bytesSent < 0) {
        printf("LOG ERROR: Cannot send data to peer host.\n");
        throw Exception(ESOCKWRITE, "Send Data Exception");
    }

    return bytesSent;
}

ssize_t Socket::socketRecvFrom(char *buffer, size_t length, int flag, InetAddress &peerAddr) {
    ssize_t bytesRcvd = 0;

    struct sockaddr_in6 peeraddr;
    memset(&peeraddr, 0, sizeof(struct sockaddr_in6));
    socklen_t addrlen = static_cast<socklen_t>(sizeof(struct sockaddr_in6));

    bytesRcvd = recvfrom(this->sockfd, buffer, length, flag, static_cast<sockaddr *>(static_cast<void *>(&peeraddr), &addrlen);
    if (bytesRcvd < 0) {
        printf("LOG ERROR: Cannot recv data from peer host.\n");
        throw Exception(ESOCKREAD, "Read Data Exception");
    }

    peerAddr.setSockAddrIn6(peeraddr);

    return bytesRcvd;
}

void Socket::setReuseAddr(bool on) {
    int optval = on ? 1 : 0;

    int ret = setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof(optval)));
    if (ret < 0) {
        printf("LOG ERROR: Cannot set socket option SO_REUSEADDR.\n");
    }
}

void Socket::setReusePort(bool on) {
#ifdef SO_REUSEPORT
    int optval = on ? 1 : 0;

    int ret = setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof(optval)));

    if (ret < 0 && on) {
        printf("LOG ERROR: Cannot set socket option SO_REUSEPORT.\n");
    }
#else
    if (on) {
        printf("LOG ERROR: Do not support set socket option SO_REUSEPORT.\n");
    }
#endif
}

void Socket::setTcpNoDelay(bool on) {
    int optval = on ? 1 : 0;

    int ret = setsockopt(this->sockfd, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof(optval)));
    if (ret < 0) {
        printf("LOG ERROR: Cannot set socket option TCP_NODELAY.\n");
    }
}

void Socket::setKeepAlive(bool on) {
    int optval = on ? 1 : 0;

    int ret = setsockopt(this->sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof(optval)));
    if (ret < 0) {
        printf("LOG ERROR: Cannot set socket option SO_KEEPALIVE.\n");
    }
}

bool Socket::resolveLocalAddr(InetAddress &localAddr) {
    struct sockaddr_in6 localaddr;
    memset(&localaddr, 0, sizeof(struct sockaddr_in6));
    socklen_t addrlen = static_cast<socklen_t>(sizeof(struct sockaddr_in6));

    int ret = getsockname(this->sockfd, static_cast<sockaddr *>(static_cast<void *>(&localaddr)), &addrlen);
    if (ret < 0) {
        printf("LOG ERROR: Cannot get local hostname and information.\n");
        return false;
    }

    localAddr.setSockAddrIn6(localaddr);
    return true;
}

bool Socket::resolvePeerAddr(InetAddress &peerAddr) {
    struct sockaddr_in6 peeraddr;
    memset(&peeraddr, 0, sizeof(struct sockaddr_in6));
    socklen_t addrlen = static_cast<socklen_t>(sizeof(struct sockaddr_in6));

    int ret = getpeername(this->sockfd, static_cast<sockaddr *>(static_cast<void *>(&peeraddr)), &addrlen);
    if (ret < 0) {
        printf("LOG ERROR: Cannot get peer hostname and information.\n");
        return false;
    }

    peerAddr.setSockAddrIn6(peeraddr);
    return true;
}