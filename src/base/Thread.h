/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#ifndef TRAFFICER_THREAD_H
#define TRAFFICER_THREAD_H

#include <pthread.h>
#include <string>
#include "NonCopyable.h"

class Thread : public NonCopyable{
public:
    Thread();
    Thread(std::string &name);
    virtual ~Thread();

    pthread_t getSelfId();
    pthread_t getThreadId();

    std::string getThreadName();
    void setThreadName(std::string &name);

    bool isStarted();
    bool isDetached();

    void start(void *arg);
    void join();
    void detach();

    virtual void run() = 0;

private:
    pthread_t thread_id;
    std::string thread_name;

    bool started;
    bool detached;

    void *arg;
    static void* exec(void *ptr);
};


#endif //TRAFFICER_THREAD_H
