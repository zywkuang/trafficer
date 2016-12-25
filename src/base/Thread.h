//
// Created by zjl on 10/28/16.
//

#ifndef TRAFFICER_THREAD_H
#define TRAFFICER_THREAD_H

#include <pthread.h>
#include "NonCopyable.h"

class Thread : public NonCopyable{
public:
    Thread();
    virtual ~Thread();

    pthread_t getSelfId();
    pthread_t getThreadId();

    const char* getThreadName();
    void setThreadName(const char *name);

    bool started();
    bool detached();

    void threadStart(void *arg);
    void threadJoin();
    void threadDetach();

    virtual void run() = 0;

private:
    pthread_t thread_id;
    const char* thread_name;

    bool isStarted;
    bool isDetached;

    void *arg;
    static void* exec(void *ptr);
};


#endif //TRAFFICER_THREAD_H
