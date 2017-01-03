/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTTCPTRAFFICRECVER_H
#define TRAFFICER_AGENTTCPTRAFFICRECVER_H

#include "msg/Message.h"
#include "base/Thread.h"
#include "base/BoundedBlockingQueue.h"

class AgentTcpTrafficRecver : public Thread {
public:
    AgentTcpTrafficRecver(BoundedBlockingQueue<Message*> *bmq);
    virtual ~AgentTcpTrafficRecver();

    int getRecverListenPort() const;

private:
    BoundedBlockingQueue<Message*> *messageQueue;
};


#endif //TRAFFICER_AGENTTCPTRAFFICRECVER_H
