/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include "AgentUdpTrafficRecver.h"

AgentUdpTrafficRecver::AgentUdpTrafficRecver(BoundedBlockingQueue<Message*> *bmq)
        : messageQueue(bmq) {

}

AgentUdpTrafficRecver::~AgentUdpTrafficRecver() {

}

int AgentUdpTrafficRecver::getRecverListenPort() const {

}

void AgentUdpTrafficRecver::run() {

}