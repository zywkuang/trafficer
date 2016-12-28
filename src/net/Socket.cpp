/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include "Socket.h"
#include "../base/Exception.h"
#include "../base/Logger.h"

Socket::Socket(bool bipv6, int proto)
    : bipv6(bipv6), proto(proto) {
    this->sockfd = socket((bipv6) ? AF_INET6 : AF_INET, proto, 0);

    if (this->sockfd < 0) {
        throw Exception(ESOCKCREATE, "Create Socket Exception");
    }
}

Socket::Socket(int sockfd, bool bipv6, int proto)
    : sockfd(sockfd), bipv6(bipv6), proto(proto) {

}

Socket::~Socket() {
    this->socketClose();
}

bool Socket::equalToSockfd(int otherSockfd) {
    return this->sockfd == otherSockfd;
}

void Socket::socketConnect(InetAddress &remoteAddr) {

    int ret = connect(this->sockfd, remoteAddr.getSockAddr(), static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
    if (ret < 0) {
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
        throw Exception(ESOCKLISTEN, "Listen Failure Exception");
    }
}

int Socket::socketAccept(InetAddress &peerAddr) {
    struct sockaddr_in6 addr;
    memset(&addr, 0, sizeof(struct sockaddr_in6));
    socklen_t  addrlen = static_cast<socklen_t>(sizeof(struct sockaddr_in6));

    int connFd = accept(this->sockfd, static_cast<sockaddr *>(static_cast<void *>(&addr)), &addrlen);
    if (connFd < 0) {
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
        throw Exception(ESOCKREAD, "Read Data Exception");
    } else if (bytesRcvd == 0) {
        throw Exception(ENOTCONN, "Not Connected Exception");
    }

    return bytesRcvd;
}

ssize_t Socket::socketSendTo(const char *payload, size_t length, InetAddress &remoteAddr, int flag) {
    ssize_t bytesSent = 0;
    socklen_t addrlen = static_cast<socklen_t>(sizeof(struct sockaddr_in6));

    bytesSent = sendto(this->sockfd, payload, length, flag, remoteAddr.getSockAddr(), addrlen);
    if (bytesSent < 0) {
        throw Exception(ESOCKWRITE, "Send Data Exception");
    }

    return bytesSent;
}

ssize_t Socket::socketRecvFrom(char *buffer, size_t length, InetAddress &peerAddr, int flag) {
    ssize_t bytesRcvd = 0;

    struct sockaddr_in6 peeraddr;
    memset(&peeraddr, 0, sizeof(struct sockaddr_in6));
    socklen_t addrlen = static_cast<socklen_t>(sizeof(struct sockaddr_in6));

    bytesRcvd = recvfrom(this->sockfd, buffer, length, flag, static_cast<struct sockaddr *>(static_cast<void *>(&peeraddr)), &addrlen);
    if (bytesRcvd < 0) {
        throw Exception(ESOCKREAD, "Read Data Exception");
    }

    peerAddr.setSockAddrIn6(peeraddr);

    return bytesRcvd;
}

void Socket::setReuseAddr(bool on) {
    int optval = on ? 1 : 0;

    int ret = setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof(optval)));
    if (ret < 0) {
        LOG_ERROR("Cannot set socket option SO_REUSEADDR.");
    }
}

void Socket::setReusePort(bool on) {
#ifdef SO_REUSEPORT
    int optval = on ? 1 : 0;

    int ret = setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof(optval)));

    if (ret < 0 && on) {
        LOG_ERROR("Cannot set socket option SO_REUSEPORT.\n");
    }
#else
    if (on) {
       LOG_ERROR("Don't support set socket option SO_REUSEPORT.");
    }
#endif
}

void Socket::setTcpNoDelay(bool on) {
    int optval = on ? 1 : 0;

    int ret = setsockopt(this->sockfd, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof(optval)));
    if (ret < 0) {
        LOG_ERROR("Cannot set socket option TCP_NODELAY.");
    }
}

void Socket::setKeepAlive(bool on) {
    int optval = on ? 1 : 0;

    int ret = setsockopt(this->sockfd, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof(optval)));
    if (ret < 0) {
        LOG_ERROR("Cannot set socket option SO_KEEPALIVE.");
    }
}

void Socket::setTcpMss(int mss) {

    int ret = setsockopt(this->sockfd, IPPROTO_TCP, TCP_MAXSEG, &mss, static_cast<socklen_t>(sizeof(mss)));
    if (ret < 0) {
        LOG_ERROR("Cannot set socket option TCP_MAXSEG.");
    }
}

bool Socket::resolveLocalAddr(InetAddress &localAddr) {
    struct sockaddr_in6 localaddr;
    memset(&localaddr, 0, sizeof(struct sockaddr_in6));
    socklen_t addrlen = static_cast<socklen_t>(sizeof(struct sockaddr_in6));

    int ret = getsockname(this->sockfd, static_cast<sockaddr *>(static_cast<void *>(&localaddr)), &addrlen);
    if (ret < 0) {
        LOG_ERROR("Cannot get local hostname and information.");
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
        LOG_ERROR("Cannot get peer hostname and information.");
        return false;
    }

    peerAddr.setSockAddrIn6(peeraddr);
    return true;
}