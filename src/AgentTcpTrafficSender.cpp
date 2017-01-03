/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include "AgentTcpTrafficSender.h"

AgentTcpTrafficSender::AgentTcpTrafficSender(const TrafficInstanceConfig &tic, BoundedBlockingQueue<Message*> *bmq)
        : messageQueue(bmq) {

}

AgentTcpTrafficSender::~AgentTcpTrafficSender() {

}

void AgentTcpTrafficSender::updateTrafficConfig(const TrafficInstanceConfig &newTic) {

}