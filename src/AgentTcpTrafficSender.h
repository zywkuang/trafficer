/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTTCPTRAFFICSENDER_H
#define TRAFFICER_AGENTTCPTRAFFICSENDER_H


#include "base/Thread.h"
#include "TrafficInstanceConfig.h"
#include "base/BoundedBlockingQueue.h"
#include "msg/Message.h"

class AgentTcpTrafficSender : public Thread {
public:
    AgentTcpTrafficSender(const TrafficInstanceConfig &tic, BoundedBlockingQueue<Message*> *bmq);
    virtual ~AgentTcpTrafficSender();

    void updateTrafficConfig(const TrafficInstanceConfig &newTic);
private:

    BoundedBlockingQueue<Message*> *messageQueue;
};


#endif //TRAFFICER_AGENTTCPTRAFFICSENDER_H
