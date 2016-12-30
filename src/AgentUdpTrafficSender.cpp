/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include <cstring>
#include "AgentUdpTrafficSender.h"

AgentUdpTrafficSender::AgentUdpTrafficSender(const TrafficInstanceConfig &tic) {
    this->sendBuf = new char[TRAFFIC_UDP_SENDBUF_SIZE];
    memset(this->sendBuf, 'x', TRAFFIC_UDP_SENDBUF_SIZE);

    this->uSock = new UdpSocket();
    InetAddress peerAddr(tic.getRecverHostAddress(), static_cast<uint16_t>(tic.getServerHostPort()));


}

AgentUdpTrafficSender::~AgentUdpTrafficSender() {
    delete this->sendBuf;
}

void AgentUdpTrafficSender::updateTrafficConfig(const TrafficInstanceConfig &newTic) {

}

void AgentUdpTrafficSender::run() {

}