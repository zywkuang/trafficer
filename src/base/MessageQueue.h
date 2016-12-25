//
// Created by zjl on 10/28/16.
//

#ifndef TRAFFICER_MESSAGEQUEUE_H
#define TRAFFICER_MESSAGEQUEUE_H

#include <queue>
#include "Message.h"
#include "Mutex.h"
#include "Event.h"

class MessageQueue : public NonCopyable {
public:
    MessageQueue();
    ~MessageQueue();

    int offerMessage(Message *msg);
    Message *pollMessage();

private:
    void push(Message *msg);
    Message *pop();

    std::queue<Message *> messageQueue;
    MutexLock mutex;
    Event event;
};


#endif //TRAFFICER_MESSAGEQUEUE_H
