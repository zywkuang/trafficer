/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#ifndef TRAFFICER_MESSAGEQUEUE_H
#define TRAFFICER_MESSAGEQUEUE_H

#include <queue>
#include "Message.h"
#include "../base/Mutex.h"
#include "../base/Event.h"

class MessageQueue : public NonCopyable {
public:
    MessageQueue();
    ~MessageQueue();

    int offerMessage(Message *msg);
    Message *pollMessage();

private:
    void push(Message *msg);
    Message *pop();

    unsigned int mqSize;
    std::queue<Message *> messageQueue;
    MutexLock mutex;
    Event event;
};


#endif //TRAFFICER_MESSAGEQUEUE_H
