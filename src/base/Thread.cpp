/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#include "Thread.h"
#include "Exception.h"

Thread::Thread()
    : started(false),
      detached(false),
      thread_id(0),
      thread_name("thrdx") {

}

Thread::Thread(std::string &name)
        : started(false),
          detached(false),
          thread_id(0),
          thread_name(name) {

}

Thread::~Thread() {
    if (started && !detached)
        this->detach();
}

pthread_t Thread::getSelfId() {
    return pthread_self();
}

pthread_t Thread::getThreadId() {
    return this->thread_id;
}

std::string Thread::getThreadName() {
    return this->thread_name;
}

void Thread::setThreadName(std::string &name) {
    this->thread_name = name;
}

bool Thread::isStarted() {
    return this->started;
}

bool Thread::isDetached() {
    return this->detached;
}

void* Thread::exec(void *ptr) {
    reinterpret_cast<Thread *>(ptr)->run();
}

void Thread::start(void *arg) {
    this->arg = arg;

    int ret = pthread_create(&this->thread_id, NULL, &Thread::exec, this);
    if (ret != 0)
        throw Exception(ETHREADCREATE, "Thread Create Exception");

    this->started = true;
}

void Thread::join() {
    int ret = pthread_join(this->thread_id, NULL);
    if (ret != 0)
        throw Exception(ETHREADJOIN, "Thread Join Exception");

    this->detached = false;
}

void Thread::detach() {
    int ret = pthread_detach(this->thread_id);
    if (ret != 0)
        throw Exception(ETHREADDETACH, "Thread Detach Exception");

    this->detached = true;
}