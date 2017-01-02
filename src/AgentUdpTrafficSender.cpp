/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include <cstring>
#include <sys/time.h>
#include "AgentUdpTrafficSender.h"
#include "base/TimeStamp.h"
#include "base/Logger.h"

AgentUdpTrafficSender::AgentUdpTrafficSender(const TrafficInstanceConfig &tic, BoundedBlockingQueue<Message*> *mq)
        : b2Stop(false),
          messageQueue(mq),
          packetSequenceNumber(0),
          sendBufSize(tic.getSendBufSize()),
          workDuration(tic.getWorkDuration()),
          reportInterval(tic.getReportInterval()),
          updateInterval(tic.getUpdateIntervel()) {

    this->sendBuf = new char[this->sendBufSize];
    memset(this->sendBuf, 'u', static_cast<size_t>(this->sendBufSize));

    this->uSock = new UdpSocket();
    InetAddress peerAddr(tic.getRecverHostAddress(), static_cast<uint16_t>(tic.getServerHostPort()));

    this->uSock->connectRemote(peerAddr);
}

AgentUdpTrafficSender::~AgentUdpTrafficSender() {
    if (this->sendBuf) {
        delete []this->sendBuf;
        this->sendBuf = NULL;
    }

    if (this->uSock) {
        delete this->uSock;
        this->uSock = NULL;
    }
}

ssize_t AgentUdpTrafficSender::sendPacket() {
    struct timeval sendtv;
    gettimeofday(&sendtv, NULL);
    uint32_t packetSendSec = htonl(static_cast<uint32_t>(sendtv.tv_sec));
    uint32_t packetSendUsec = htonl(static_cast<uint32_t>(sendtv.tv_usec));
    uint32_t packetSendSeqno = htonl(this->packetSequenceNumber);

    memcpy(this->sendBuf, &packetSendSec, sizeof(packetSendSec));
    memcpy(this->sendBuf, &packetSendUsec, sizeof(packetSendUsec));
    memcpy(this->sendBuf, &packetSendSeqno, sizeof(packetSendSeqno));

    ssize_t datasnd = this->uSock->sendData(this->sendBuf, TRAFFIC_UDP_SENDBUF_SIZE);

    return datasnd;
}

void AgentUdpTrafficSender::updateTrafficConfig(const TrafficInstanceConfig &newTic) {

}

void AgentUdpTrafficSender::stop() {
    this->b2Stop = true;
}

void AgentUdpTrafficSender::run() {
    TimeStamp nowTime = TimeStamp::now();
    TimeStamp runStopTime = nowTime;
    TimeStamp nextReportTime = nowTime;
    TimeStamp nextUpdateTime = nowTime;
    runStopTime.addMicroSeconds(this->workDuration);

    // Set send_timeout flag
    struct timeval sndTimeout;
    sndTimeout.tv_sec = 0;
    sndTimeout.tv_usec = this->updateInterval;
    this->uSock->setSendTimeout(sndTimeout);

    nextReportTime.addMicroSeconds(this->reportInterval);

    if (this->updateInterval > 0) {
        nextUpdateTime.addMicroSeconds(this->updateInterval);
    }

    while (true) {
        UdpTrafficStatistic tmpTrafficStat;

        if (this->b2Stop) {
            LOG_INFO("UdpTrafficSender Stopped");
            break;
        }



    }
}

