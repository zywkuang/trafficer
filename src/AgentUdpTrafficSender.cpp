/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include <cstring>
#include <sys/time.h>
#include "base/Logger.h"
#include "model/StableTrafficModel.h"
#include "model/RectangleTrafficModel.h"
#include "model/PoissonTrafficModel.h"
#include "AgentUdpTrafficSender.h"
#include "base/UtilSet.h"
#include "msg/AgentTrafficReportMessage.h"

void resetUdpSendTrafficStats(UdpSendTrafficStats &udpts) {
    udpts.beginTime = TimeStamp::now();
    udpts.endTime = TimeStamp::now();
    udpts.bytesSent = 0;
    udpts.packetTotal = 0;
    udpts.interval = 0;
    udpts.bandwidth = 0;
}

AgentUdpTrafficSender::AgentUdpTrafficSender(const TrafficInstanceConfig &tic, BoundedBlockingQueue<Message*> *mq)
        : b2Stop(false),
          messageQueue(mq),
          trafficInstanceId(tic.getTrafficInstanceId()),
          sendBufSize(tic.getSendBufSize()),
          workDuration(tic.getWorkDuration()),
          reportInterval(tic.getReportInterval()),
          updateInterval(tic.getUpdateInterval()) {

    // Initialize send buffer - corresponding to packet size.
    this->sendBuf = new char[this->sendBufSize];
    memset(this->sendBuf, 'u', static_cast<size_t>(this->sendBufSize));

    // Initialize traffic model
    TrafficModelType modelType = tic.getTrafficModel();
    switch (modelType) {
        case STABLE_TRAFFIC:
            this->tModel = new StableTrafficModel(tic.getStableTrafficBandwidth());
            break;
        case RECTANGLE_TRAFFIC:
            this->tModel = new RectangleTrafficModel(tic.getRectSupremumTrafficBandwidth(), tic.getRectInfimumTrafficBandwidth(), tic.getRectSupreProportion());
            break;
        case POISSON_TRAFFIC:
            this->tModel = new PoissonTrafficModel(tic.getPoissonBurstTrafficBandwidth());
            break;
        case CUSTOM_TRAFFIC:
            this->tModel = NULL;
            break;
        case UNKNOWN_TRAFFIC_MODEL:
        default:
            this->tModel = NULL;
            break;
    }

    // Connect to remote udp socket.
    this->uSock = new UdpSocket();
    InetAddress peerAddr(tic.getRecverHostAddress(), static_cast<uint16_t>(tic.getServerHostPort()));
    this->uSock->connectRemote(peerAddr);
}

AgentUdpTrafficSender::~AgentUdpTrafficSender() {
    if (this->sendBuf) {
        delete []this->sendBuf;
        this->sendBuf = NULL;
    }

    if (this->tModel) {
        delete this->tModel;
        this->tModel = NULL;
    }

    if (this->uSock) {
        delete this->uSock;
        this->uSock = NULL;
    }
}

ssize_t AgentUdpTrafficSender::sendPacket(uint32_t pktsn) {
    uint32_t packetSendSeqno = htonl(pktsn);
    uint64_t packetSendTid = Htonll(this->trafficInstanceId);

    struct timeval sendtv;
    gettimeofday(&sendtv, NULL);
    uint32_t packetSendSec = htonl(static_cast<uint32_t>(sendtv.tv_sec));
    uint32_t packetSendUsec = htonl(static_cast<uint32_t>(sendtv.tv_usec));

    memcpy(this->sendBuf, &packetSendTid, sizeof(packetSendTid));
    memcpy(this->sendBuf, &packetSendSeqno, sizeof(packetSendSeqno));
    memcpy(this->sendBuf, &packetSendSec, sizeof(packetSendSec));
    memcpy(this->sendBuf, &packetSendUsec, sizeof(packetSendUsec));

    ssize_t datasnd = this->uSock->sendData(this->sendBuf, this->sendBufSize);

    return datasnd;
}

void AgentUdpTrafficSender::updateTrafficConfig(const TrafficInstanceConfig &newTic) {
    this->sendBufSize = newTic.getSendBufSize();

    if (this->sendBuf) {
        delete []this->sendBuf;
        this->sendBuf = NULL;
    }

    this->sendBuf = new char[this->sendBufSize];
    memset(this->sendBuf, 'u', static_cast<size_t>(this->sendBufSize));

    this->workDuration = newTic.getWorkDuration();
    this->reportInterval = newTic.getReportInterval();
    this->updateInterval = newTic.getUpdateInterval();

    if (this->tModel) {
        delete this->tModel;
        this->tModel = NULL;
    }

    TrafficModelType modelType = newTic.getTrafficModel();
    switch (modelType) {
        case STABLE_TRAFFIC:
            this->tModel = new StableTrafficModel(newTic.getStableTrafficBandwidth());
            break;
        case RECTANGLE_TRAFFIC:
            this->tModel = new RectangleTrafficModel(newTic.getRectSupremumTrafficBandwidth(), newTic.getRectInfimumTrafficBandwidth(), newTic.getRectSupreProportion());
            break;
        case POISSON_TRAFFIC:
            this->tModel = new PoissonTrafficModel(newTic.getPoissonBurstTrafficBandwidth());
            break;
        case CUSTOM_TRAFFIC:
            this->tModel = NULL;
            break;
        case UNKNOWN_TRAFFIC_MODEL:
        default:
            this->tModel = NULL;
            break;
    }
}

void AgentUdpTrafficSender::stop() {
    this->b2Stop = true;
}

void AgentUdpTrafficSender::run() {
    TimeStamp nowTime;
    TimeStamp runStopTime = TimeStamp::now();
    runStopTime.addMicroSeconds(this->workDuration);

    // Set send_timeout flag
    struct timeval sndTimeout;
    sndTimeout.tv_sec = 0;
    sndTimeout.tv_usec = this->updateInterval;
    this->uSock->setSendTimeout(sndTimeout);

    TimeStamp lastReportTime = TimeStamp::now();
    TimeStamp nextReportTime = TimeStamp::now();
    nextReportTime.addMicroSeconds(this->reportInterval);

    TimeStamp lastUpdateTime = TimeStamp::now();
    TimeStamp nextUpdateTime = TimeStamp::now();
    if (this->updateInterval > 0) {
        nextUpdateTime.addMicroSeconds(this->updateInterval);
    }

    UdpSendTrafficStats reportIntervalTrafficStat;
    resetUdpSendTrafficStats(reportIntervalTrafficStat);

    UdpSendTrafficStats updateIntervalTrafficStat;
    resetUdpSendTrafficStats(updateIntervalTrafficStat);

    uint64_t specificRate = this->tModel->getNextTrafficBandwidth();
    uint32_t packetSequenceNumber = 0;

    while (true) {

        // User can set stop flag to stop thread
        if (this->b2Stop) {
            LOG_INFO("UdpTrafficSender Stopped");
            break;
        }

        int count = 0;
        while (count < TRAFFIC_UDP_SENDPKT_CNT) {
            ssize_t pktBytes = this->sendPacket(packetSequenceNumber);

            reportIntervalTrafficStat.bytesSent += pktBytes;
            reportIntervalTrafficStat.packetTotal++;

            updateIntervalTrafficStat.bytesSent += pktBytes;
            updateIntervalTrafficStat.packetTotal++;

            this->overallTrafficStat.bytesSent += pktBytes;
            this->overallTrafficStat.packetTotal++;

            packetSequenceNumber++;
            count++;
        }

        // Check whether should execute time-delay operation to meet bandwidth demand
        nowTime = TimeStamp::now();
        int64_t tmpInterval = nowTime.diffTimeStamp(lastUpdateTime); //unit: us
        int64_t expectInterval = static_cast<int64_t>(MICROSECOND_PER_SECOND * (static_cast<double>(updateIntervalTrafficStat.bytesSent) / specificRate));
        if (expectInterval > tmpInterval) {
            int64_t delayUsecs = expectInterval - tmpInterval;
            UtilSet::delayNanosleep(delayUsecs);
        }

        // Check whether should execute traffic statistics report operation
        nowTime = TimeStamp::now();
        if (nowTime.isMoreThan(nextReportTime)) {
            // Result calculation process
            reportIntervalTrafficStat.beginTime = lastReportTime;
            std::string bt = lastReportTime.toString();
            reportIntervalTrafficStat.endTime = nowTime;
            std::string et = nowTime.toString();
            reportIntervalTrafficStat.interval = nowTime.diffTimeStamp(lastReportTime);
            reportIntervalTrafficStat.bandwidth = static_cast<uint64_t>(MICROSECOND_PER_SECOND * reportIntervalTrafficStat.bytesSent / reportIntervalTrafficStat.interval);

            AgentTrafficReportMessage *reportmsg = new AgentTrafficReportMessage();
            reportmsg->setProtocol(UDP);
            reportmsg->setRole(SENDER);
            reportmsg->setBeginTimeStamp(bt);
            reportmsg->setEndTimeStamp(et);
            reportmsg->setBytesTransferred(reportIntervalTrafficStat.bytesSent);
            reportmsg->setTrafficInterval(reportIntervalTrafficStat.interval);
            reportmsg->setTrafficBandwidth(reportIntervalTrafficStat.bandwidth);
            reportmsg->setPacketTotalCnt(reportIntervalTrafficStat.packetTotal);

            this->messageQueue->offer(reportmsg);

            lastReportTime = nowTime;
            nextReportTime = lastReportTime;
            nextReportTime.addMicroSeconds(this->reportInterval);

            resetUdpSendTrafficStats(reportIntervalTrafficStat);
        }

        // Check whether should execute traffic rate update operation
        nowTime = TimeStamp::now();
        if (nowTime.isMoreThan(nextUpdateTime)) {
            specificRate = this->tModel->getNextTrafficBandwidth();

            lastUpdateTime = nowTime;
            nextUpdateTime = lastUpdateTime;
            nextUpdateTime.addMicroSeconds(this->updateInterval);

            resetUdpSendTrafficStats(updateIntervalTrafficStat);
        }

        if (nowTime.isMoreThan(runStopTime)) {
            this->b2Stop = true;
            break;
        }
    }
}

