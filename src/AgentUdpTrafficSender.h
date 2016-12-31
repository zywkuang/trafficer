/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTUDPTRAFFICSENDER_H
#define TRAFFICER_AGENTUDPTRAFFICSENDER_H


#include "base/Thread.h"
#include "TrafficInstanceConfig.h"
#include "net/UdpSocket.h"
#include "model/AbstractTrafficModel.h"
#include "UdpTrafficStatistic.h"
#include "base/BoundedBlockingQueue.h"
#include "msg/Message.h"

class AgentUdpTrafficSender : public Thread {
public:
    AgentUdpTrafficSender(const TrafficInstanceConfig &tic, BoundedBlockingQueue<Message*> *mq);
    virtual ~AgentUdpTrafficSender();

    void updateTrafficConfig(const TrafficInstanceConfig &newTic);
    void stop();

    virtual void run();

private:
    // Internal functions
    ssize_t sendPacket();

    // Internal variables
    bool b2Stop; // boolean variable (to stop thread?)

    UdpSocket *uSock;
    uint32_t packetSequenceNumber;  // Packet sequence number

    char *sendBuf;
    int sendBufSize;

    // Some time interval variables
    int workDuration;
    int reportInterval;
    int updateInterval;

    UdpTrafficStatistic overallTrafficStat;

    AbstractTrafficModel *tModel;
    BoundedBlockingQueue<Message*> *messageQueue;
};


#endif //TRAFFICER_AGENTUDPTRAFFICSENDER_H
