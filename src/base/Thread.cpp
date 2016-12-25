//
// Created by zjl on 10/28/16.
//

#include "Thread.h"
#include "Exception.h"

Thread::Thread()
    : isStarted(false),
      isDetached(false),
      thread_id(0),
      thread_name(NULL){

}

Thread::~Thread() {
    if (isStarted && !isDetached)
        this->threadDetach();
}

pthread_t Thread::getSelfId() {
    return pthread_self();
}

pthread_t Thread::getThreadId() {
    return this->thread_id;
}

const char* Thread::getThreadName() {
    return this->thread_name;
}

void Thread::setThreadName(const char *name) {
    this->thread_name = name;
}

bool Thread::started() {
    return this->isStarted;
}

bool Thread::detached() {
    return this->isDetached;
}

void* Thread::exec(void *ptr) {
    reinterpret_cast<Thread *>(ptr)->run();
}

void Thread::threadStart(void *arg) {
    this->arg = arg;

    int ret = pthread_create(&this->thread_id, NULL, &Thread::exec, this);
    if (ret != 0)
        throw Exception(ETHREADCREATE, "Thread Create Exception");

    this->isStarted = true;
}

void Thread::threadJoin() {
    int ret = pthread_join(this->thread_id, NULL);
    if (ret != 0)
        throw Exception(ETHREADJOIN, "Thread Join Exception");

    this->isDetached = false;
}

void Thread::threadDetach() {
    int ret = pthread_detach(this->thread_id);
    if (ret != 0)
        throw Exception(ETHREADDETACH, "Thread Detach Exception");

    this->isDetached = true;
}