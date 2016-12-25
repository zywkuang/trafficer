//
// Created by zjl on 10/28/16.
//

#include "MessageQueue.h"
#include "Exception.h"

MessageQueue::MessageQueue() {

}

MessageQueue::~MessageQueue() {
    while (true) {
        Message *msg = this->pop();
        if (msg == NULL)
            break;

        delete msg;
    }
}

void MessageQueue::push(Message *msg) {
    MutexLockGuard guard(&this->mutex);
    this->messageQueue.push(msg);
}

Message* MessageQueue::pop() {
    MutexLockGuard guard(&this->mutex);
    this->messageQueue.pop();
}

int MessageQueue::offerMessage(Message *msg) {
    if (msg == NULL)
        return -1;

    try {
        this->push(msg);
        this->event.set();

    } catch(Exception e) {
        throw Exception(EMSGQUEUEPUSH, "MessageQueue Push Exception");
    }

    return 0;
}

Message* MessageQueue::pollMessage() {
    Message *msg = NULL;

    try {
        this->event.wait();
        msg = this->pop();

    } catch (Exception e) {
        throw Exception(EMSGQUEUEPOP, "MessageQueue Pop Exception");
    }

    return msg;
}