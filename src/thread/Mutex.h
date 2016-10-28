//
// Created by zjl on 10/28/16.
//

#ifndef TRAFFICER_MUTEXLOCK_H
#define TRAFFICER_MUTEXLOCK_H


#include <pthread.h>
#include "../base/NonCopyable.h"

class MutexLock : public NonCopyable {
public:
    friend class ConditionVariable;

    MutexLock();
    virtual ~MutexLock();

    void lock();
    void unlock();

private:
    pthread_mutex_t mutex;
};

class MutexLockGuard : public NonCopyable {
public:
    MutexLockGuard(MutexLock *lock);
    virtual ~MutexLockGuard();

private:
    MutexLock *mutexLock;
};

class ConditionVariable : public NonCopyable {
public:
    ConditionVariable();
    virtual ~ConditionVariable();

    void wait(MutexLock *lock);
    void wakeup();
    void wakeupAll();

private:
    pthread_cond_t condition;
};

#endif //TRAFFICER_MUTEXLOCK_H
