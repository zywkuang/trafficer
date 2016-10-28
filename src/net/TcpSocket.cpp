//
// Created by zjl on 10/27/16.
//

#include <cstdio>
#include "TcpSocket.h"
#include "../base/Exception.h"

TcpSocket::TcpSocket(bool bIpv6)
    : Socket(bIpv6, SOCK_STREAM),
      bLocalSet(false),
      bIsConnected(false){

}

TcpSocket::TcpSocket(int sockfd, bool bIpv6)
    : Socket(sockfd, bIpv6, SOCK_STREAM),
      bLocalSet(false),
      bIsConnected(false) {

}

TcpSocket::~TcpSocket() {

}

void TcpSocket::setLocal() {

    if (this->resolveLocalAddr(this->localAddr))
        this->bLocalSet = true;
    else
        this->bLocalSet = false;
}

void TcpSocket::setConnected() {

    if (this->resolvePeerAddr(this->peerAddr))
        this->bIsConnected = true;
    else
        this->bIsConnected = false;
}

ssize_t TcpSocket::sendData(const char *data, int length) {
    register ssize_t s;
    register ssize_t left = length;

    while (left > 0) {
        s = this->socketSend(data, left);

        left -= s;
        data += s;
    }

    return length - left;
}

ssize_t TcpSocket::recvData(char *buffer, int length) {
    register ssize_t r;
    register ssize_t left = length;

    while (left > 0) {
        r = this->socketRecv(buffer, left);

        left   -= r;
        buffer += r;
    }

    return length;
}

void TcpSocket::connectServer(InetAddress &remoteAddr) {
    this->socketConnect(remoteAddr);

    this->setLocal();
    this->setConnected();
}

void TcpSocket::listenServer(InetAddress &localAddr) {
    this->setReuseAddr(true);

    this->socketBind(localAddr);
    this->setLocal();
    this->socketListen();
}

TcpSocket* TcpSocket::acceptClient() {
    InetAddress peerAddr;
    int newFd = this->socketAccept(peerAddr);

    TcpSocket *newTcpSocket = new TcpSocket(newFd);
    newTcpSocket->setLocal();
    newTcpSocket->setConnected();

    return newTcpSocket;
}



