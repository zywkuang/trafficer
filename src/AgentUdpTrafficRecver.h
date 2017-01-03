/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTUDPTRAFFICRECVER_H
#define TRAFFICER_AGENTUDPTRAFFICRECVER_H

#include <stdint.h>
#include "base/Thread.h"
#include "base/TimeStamp.h"
#include "base/BoundedBlockingQueue.h"
#include "msg/Message.h"
#include "net/InetAddress.h"

typedef struct UdpRecvTrafficStats {
    TimeStamp beginTime;
    TimeStamp endTime;
    uint64_t bytesSent;
    uint64_t packetTotal;
    uint64_t packetLost;
    int64_t interval;
    uint64_t bandwidth;
    double jitter;
    double loss;
} UdpRecvTrafficStats;

class AgentUdpTrafficRecver : public Thread {
public:
    AgentUdpTrafficRecver(BoundedBlockingQueue<Message*> *bmq);
    virtual ~AgentUdpTrafficRecver();

    int getRecverListenPort() const;

    virtual void run();

private:
    // Internal functions
    ssize_t recvPacket(uint32_t *pktsn, TimeStamp &sendTime, InetAddress &peerAddr);

    BoundedBlockingQueue<Message *> *messageQueue;
};


#endif //TRAFFICER_AGENTUDPTRAFFICRECVER_H
