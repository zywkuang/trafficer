/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include "AgentMessageDispatcher.h"

AgentMessageDispatcher::AgentMessageDispatcher(BoundedBlockingQueue<Message*> *bmq)
        : messageQueue(bmq) {

}

AgentMessageDispatcher::~AgentMessageDispatcher() {

}