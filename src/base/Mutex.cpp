//
// Created by zjl on 10/28/16.
//

#include "Mutex.h"
#include "Exception.h"

//***************************** MutexLock **********************************
MutexLock::MutexLock() {
    int ret = pthread_mutex_init(&this->mutex, 0);

    if (ret != 0)
        throw Exception(EMUTEXINIT, "Mutex Init Exception");
}

MutexLock::~MutexLock() {
    int ret = pthread_mutex_destroy(&this->mutex);

    if (ret != 0)
        throw Exception(EMUTEXDESTROY, "Mutex Destroy Exception");
}

void MutexLock::lock() {
    int ret = pthread_mutex_lock(&this->mutex);

    if (ret != 0)
        throw Exception(EMUTEXLOCK, "Mutex Lock Exception");
}

void MutexLock::unlock() {
    int ret = pthread_mutex_unlock(&this->mutex);

    if (ret != 0)
        throw Exception(EMUTEXUNLOCK, "Mutex Unlock Exception");
}

//**************************** MutexLockGuard *******************************
MutexLockGuard::MutexLockGuard(MutexLock *lock)
    : mutexLock(lock) {
    this->mutexLock->lock();
}

MutexLockGuard::~MutexLockGuard() {
    this->mutexLock->unlock();
}

//************************* ConditionVariable *****************************
ConditionVariable::ConditionVariable() {
    int ret = pthread_cond_init(&this->condition, 0);

    if (ret != 0)
        throw Exception(ECONDITIONINIT, "Condtion Init Exception");
}

ConditionVariable::~ConditionVariable() {
    int ret = pthread_cond_destroy(&this->condition);

    if (ret != 0)
        throw Exception(ECONDITIONDESTROY, "Condition Destroy Exception");
}

void ConditionVariable::wait(MutexLock *lock) {
    int ret = pthread_cond_wait(&this->condition, &(lock->mutex));

    if (ret != 0)
        throw Exception(ECONDITIONWAIT, "Condition Wait Exception");
}

void ConditionVariable::wakeup() {
    int ret = pthread_cond_signal(&this->condition);

    if (ret != 0)
        throw Exception(ECONDITIONSINGAL, "Condition Signal Exception");
}

void ConditionVariable::wakeupAll() {
    int ret = pthread_cond_broadcast(&this->condition);

    if (ret != 0)
        throw Exception(ECONDITIONBROADCAST, "Condition Broadcast Exception");
}

