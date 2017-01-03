/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTMESSAGEDISPATCHER_H
#define TRAFFICER_AGENTMESSAGEDISPATCHER_H

#include "base/BoundedBlockingQueue.h"
#include "base/Thread.h"
#include "msg/Message.h"

class AgentMessageDispatcher : public Thread {
public:
    AgentMessageDispatcher(BoundedBlockingQueue<Message*> *bmq);
    virtual ~AgentMessageDispatcher();


private:
    BoundedBlockingQueue<Message*> *messageQueue;
};


#endif //TRAFFICER_AGENTMESSAGEDISPATCHER_H
