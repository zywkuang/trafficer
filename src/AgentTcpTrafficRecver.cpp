/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include "AgentTcpTrafficRecver.h"

AgentTcpTrafficRecver::AgentTcpTrafficRecver(BoundedBlockingQueue<Message*> *bmq)
        : messageQueue(bmq) {

}

AgentTcpTrafficRecver::~AgentTcpTrafficRecver() {

}

int AgentTcpTrafficRecver::getRecverListenPort() const {

}