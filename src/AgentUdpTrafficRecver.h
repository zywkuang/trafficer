/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTUDPTRAFFICRECVER_H
#define TRAFFICER_AGENTUDPTRAFFICRECVER_H

#include <stdint.h>
#include <set>
#include "base/Thread.h"
#include "base/TimeStamp.h"
#include "base/BoundedBlockingQueue.h"
#include "msg/Message.h"
#include "net/InetAddress.h"
#include "net/UdpSocket.h"
#include "base/TimerQueue.h"
#include "TrafficInstanceConfig.h"

typedef struct UdpRecvTrafficStats {
    TimeStamp beginTime;
    TimeStamp endTime;
    uint64_t bytesRcvd;
    uint64_t packetTotal;
    uint64_t packetOut;
    int64_t interval;
    uint64_t bandwidth;
    int64_t jitter;
    double outss;
} UdpRecvTrafficStats;

class AgentUdpTrafficRecver : public Thread {
public:
    AgentUdpTrafficRecver(const InetAddress &sockAddr, BoundedBlockingQueue<Message*> *bmq);
    virtual ~AgentUdpTrafficRecver();

    int getRecverListenPort() const;

    void createTrafficInstance(uint64_t tiid, const TrafficInstanceConfig &tic);
    void updateTrafficInstance(uint64_t tiid, const TrafficInstanceConfig &newTic);
    void deleteTrafficInstance(uint64_t tiid);

    virtual void run();

private:
    // Internal functions
    ssize_t recvPacket(uint32_t *pktsn, uint64_t *tiid, TimeStamp &sendTime, InetAddress &peerAddr);

    InetAddress localAddr;
    UdpSocket *uSock;

    char *recvBuf;

    BoundedBlockingQueue<Message *> *messageQueue;

    std::set<uint64_t> trafficInstanceSet;

    std::map<uint64_t, int64_t> reportIntervalMap;
    std::map<uint64_t, TimeStamp> lastReportTimeMap;
    std::map<uint64_t, UdpRecvTrafficStats*> reportStatisticsMap;
    std::map<uint64_t, uint32_t> currentSequenceNumberMap;
    std::map<uint64_t, int64_t> lastPacketTransitTimeMap;

    TimerQueue reportTimerQueue;

    MutexLock mutex;
};


#endif //TRAFFICER_AGENTUDPTRAFFICRECVER_H
