/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include <cstring>
#include <map>
#include "AgentUdpTrafficRecver.h"
#include "base/UtilSet.h"
#include "msg/AgentTrafficReportMessage.h"

void resetUdpRecvTrafficStats(UdpRecvTrafficStats *udpts) {
    udpts->beginTime = TimeStamp::now();
    udpts->endTime = TimeStamp::now();
    udpts->bytesRcvd = 0;
    udpts->packetTotal = 0;
    udpts->interval = 0;
    udpts->bandwidth = 0;
    udpts->packetOut = 0;
    udpts->jitter = 0;
    udpts->outss = 0;
}

AgentUdpTrafficRecver::AgentUdpTrafficRecver(const InetAddress &sockAddr, BoundedBlockingQueue<Message*> *bmq)
        : messageQueue(bmq),
          localAddr(sockAddr),
          trafficInstanceSet() {
    this->recvBuf = new char[TRAFFIC_UDP_RECVBUF_SIZE];

    // Connect to remote udp socket.
    this->uSock = new UdpSocket();
    this->uSock->setReuseAddr(true);
    this->uSock->socketBind(this->localAddr);
}

AgentUdpTrafficRecver::~AgentUdpTrafficRecver() {
    if (this->recvBuf) {
        delete []this->recvBuf;
        this->recvBuf = NULL;
    }

    if (this->uSock) {
        delete this->uSock;
        this->uSock = NULL;
    }
}

int AgentUdpTrafficRecver::getRecverListenPort() const {
    return this->localAddr.getPortNumber();
}

void AgentUdpTrafficRecver::createTrafficInstance(uint64_t tiid, const TrafficInstanceConfig &tic) {
    MutexLockGuard mlg(&this->mutex);

    this->trafficInstanceSet.insert(tiid);

    this->reportIntervalMap[tiid] = tic.getReportInterval();
    this->lastReportTimeMap[tiid] = TimeStamp::now();
    this->currentSequenceNumberMap[tiid] = 0;
    this->lastPacketTransitTimeMap[tiid] = 0;

    UdpRecvTrafficStats *udprts = new UdpRecvTrafficStats();
    this->reportStatisticsMap[tiid] = udprts;
}

void AgentUdpTrafficRecver::updateTrafficInstance(uint64_t tiid, const TrafficInstanceConfig &newTic) {
    MutexLockGuard mlg(&this->mutex);
    
    this->reportIntervalMap[tiid] = newTic.getReportInterval();
}

void AgentUdpTrafficRecver::deleteTrafficInstance(uint64_t tiid) {
    MutexLockGuard mlg(&this->mutex);

    this->trafficInstanceSet.erase(tiid);

    this->reportIntervalMap.erase(tiid);
    this->lastReportTimeMap.erase(tiid);
    this->currentSequenceNumberMap.erase(tiid);
    this->lastPacketTransitTimeMap.erase(tiid);

    delete this->reportStatisticsMap[tiid];
    this->reportStatisticsMap.erase(tiid);
}

ssize_t AgentUdpTrafficRecver::recvPacket(uint32_t *pktsn, uint64_t *tiid, TimeStamp &sendTime, InetAddress &peerAddr) {
    uint32_t psn;
    uint64_t tid, st;

    ssize_t plen = this->uSock->recvData(this->recvBuf, TRAFFIC_UDP_RECVBUF_SIZE, peerAddr);

    memcpy(&psn, this->recvBuf, sizeof(psn));
    memcpy(&tid, this->recvBuf + 4, sizeof(tid));
    memcpy(&st, this->recvBuf + 12, sizeof(st));

    *pktsn = ntohl(psn);
    *tiid = Ntohll(tid);
    sendTime.setMicroSecondsSinceEpoch(static_cast<int64_t>(Ntohll(st)));

    return plen;
}

void AgentUdpTrafficRecver::run() {
    int count;
    uint32_t pktsn;
    uint64_t tiid;
    TimeStamp sendTime;
    InetAddress peerAddr;
    std::map<uint64_t, UdpRecvTrafficStats*>::iterator iter;
    UdpRecvTrafficStats *udprts;

    while (true) {
        MutexLockGuard mlg1(&this->mutex);

        count = 0;
        while (count < TRAFFIC_UDP_SENDPKT_CNT) {
            ssize_t recvlen = this->recvPacket(&pktsn, &tiid, sendTime, peerAddr);
            iter = this->reportStatisticsMap.find(tiid);
            if (iter != this->reportStatisticsMap.end()) {
                udprts = iter->second;
                udprts->bytesRcvd += recvlen;
                udprts->packetTotal++;

                // Execute out-of-order packet count
                if (pktsn >= this->currentSequenceNumberMap[tiid] + 1)
                    this->currentSequenceNumberMap[tiid] = pktsn;
                else
                    udprts->packetOut++;

                // Execute jitter calculation
                int64_t transit = TimeStamp::now().diffTimeStamp(sendTime);
                int64_t delta = transit - this->lastPacketTransitTimeMap[tiid];

                if (delta < 0)
                    delta = -delta;

                udprts->jitter += (delta - udprts->jitter) / 16;

                this->lastPacketTransitTimeMap[tiid] = transit;
            }

            count++;
        }

        while (true) {
            MutexLockGuard mlg2(&this->mutex);
            uint64_t reportTiid = this->reportTimerQueue.popFrontTimer();

            if (reportTiid == 0)
                break;

            iter = this->reportStatisticsMap.find(reportTiid);
            udprts = iter->second;

            udprts->beginTime = this->lastReportTimeMap[reportTiid];
            std::string bt = udprts->beginTime.toString();
            udprts->endTime = TimeStamp::now();
            std::string et = udprts->endTime.toString();
            udprts->interval = udprts->endTime.diffTimeStamp(udprts->beginTime);
            udprts->bandwidth = static_cast<uint64_t>(MICROSECOND_PER_SECOND * udprts->bytesRcvd / udprts->interval);
            udprts->outss = static_cast<double>(udprts->packetOut) / udprts->packetTotal;

            AgentTrafficReportMessage *reportmsg = new AgentTrafficReportMessage();
            reportmsg->setProtocol(UDP);
            reportmsg->setRole(SENDER);
            reportmsg->setBeginTimeStamp(bt);
            reportmsg->setEndTimeStamp(et);
            reportmsg->setBytesTransferred(udprts->bytesRcvd);
            reportmsg->setTrafficInterval(udprts->interval);
            reportmsg->setTrafficBandwidth(udprts->bandwidth);
            reportmsg->setPacketTotalCnt(udprts->packetTotal);
            reportmsg->setPacketOutCnt(udprts->packetOut);
            reportmsg->setPacketOutss(udprts->outss);
            reportmsg->setTrafficJitter(udprts->jitter);

            this->messageQueue->offer(reportmsg);

            TimeStamp nowTime = TimeStamp::now();
            TimeStamp nextReportTime = nowTime;
            nextReportTime.addMicroSeconds(this->reportIntervalMap[reportTiid]);
            this->lastReportTimeMap[reportTiid] = nowTime;

            resetUdpRecvTrafficStats(udprts);
        }
    }
}