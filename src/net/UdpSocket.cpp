/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#include "UdpSocket.h"
#include "../base/Exception.h"

UdpSocket::UdpSocket(bool bIpv6)
    : Socket(bIpv6, SOCK_DGRAM),
      bIsConnected(false) {

}

UdpSocket::~UdpSocket() {

}

ssize_t UdpSocket::sendData(const char *data, size_t length, InetAddress &remoteAddr) {
    this->socketSendTo(data, length, remoteAddr, 0);
}

ssize_t UdpSocket::recvData(char *buffer, size_t length, InetAddress &peerAddr) {
    this->socketRecvFrom(buffer, length, peerAddr, 0);
}

// Client Function
void UdpSocket::connectRemote(InetAddress &remoteAddr) {
    this->socketConnect(remoteAddr);
    this->bIsConnected = true;
    this->peerAddr = remoteAddr;
    this->resolveLocalAddr(this->localAddr);
}

ssize_t UdpSocket::sendData(const char *data, size_t length) {
    if (this->bIsConnected == false) {
        throw Exception(ESOCKCONNECT, "NotConnected Exception");
    }

    this->sendData(data, length, this->peerAddr);
}