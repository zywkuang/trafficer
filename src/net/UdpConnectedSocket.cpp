//
// Created by zjl on 10/28/16.
//

#include "UdpConnectedSocket.h"

UdpConnectedSocket::UdpConnectedSocket(bool bIpv6) {

}

UdpConnectedSocket::UdpConnectedSocket(int sockfd, bool bIpv6) {

}

UdpConnectedSocket::~UdpConnectedSocket() {

}

ssize_t UdpConnectedSocket::sendData(const char *data, int length) {

}

ssize_t UdpConnectedSocket::recvData(char *buffer, int buflen) {

}

void UdpConnectedSocket::connectServer(InetAddress &remoteAddr) {

}

void UdpConnectedSocket::listenServer(InetAddress &localAddr) {

}

UdpConnectedSocket* UdpConnectedSocket::acceptClient() {

}