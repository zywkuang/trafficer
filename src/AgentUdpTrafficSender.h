/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTUDPTRAFFICSENDER_H
#define TRAFFICER_AGENTUDPTRAFFICSENDER_H

#include "base/Thread.h"
#include "base/TimeStamp.h"
#include "base/BoundedBlockingQueue.h"
#include "msg/Message.h"
#include "net/UdpSocket.h"
#include "model/AbstractTrafficModel.h"
#include "TrafficInstanceConfig.h"

typedef struct UdpSendTrafficStats {
    TimeStamp beginTime;
    TimeStamp endTime;
    uint64_t bytesSent;
    uint64_t packetTotal;
    int64_t interval;
    uint64_t bandwidth;
} UdpSendTrafficStats;

class AgentUdpTrafficSender : public Thread {
public:
    AgentUdpTrafficSender(const TrafficInstanceConfig &tic, BoundedBlockingQueue<Message*> *mq);
    virtual ~AgentUdpTrafficSender();

    void updateTrafficConfig(const TrafficInstanceConfig &newTic);

    virtual void run();
    virtual void stop();

private:
    // Internal functions
    ssize_t sendPacket(uint32_t pktSN);  // Packet sequence number);

    // Internal variables
    bool b2Stop; // boolean variable (to stop thread?)

    UdpSocket *uSock;

    char *sendBuf;
    size_t sendBufSize;

    uint64_t trafficInstanceId;

    // Some time interval variables
    int64_t workDuration;
    int64_t reportInterval;
    int64_t updateInterval;

    UdpSendTrafficStats overallTrafficStat;

    AbstractTrafficModel *tModel;
    BoundedBlockingQueue<Message*> *messageQueue;
};


#endif //TRAFFICER_AGENTUDPTRAFFICSENDER_H
