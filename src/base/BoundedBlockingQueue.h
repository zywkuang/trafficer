/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_BOUNDEDBLOCKINGQUEUE_H
#define TRAFFICER_BOUNDEDBLOCKINGQUEUE_H

#include <stdint.h>
#include <queue>
#include "NonCopyable.h"
#include "Mutex.h"
#include "../Trafficer.h"

template <typename T>
class BoundedBlockingQueue : public NonCopyable {
public:
    explicit BoundedBlockingQueue(size_t cap = DEFAULT_QUEUE_CAPACITY)
            : size(0),
              capacity(cap) {

    }

    virtual ~BoundedBlockingQueue() {

    }

    void offer(const T &x) {
        MutexLockGuard mlg(&this->mutex);

        while (this->size == this->capacity)
            this->notFullCond.wait(&this->mutex);

        this->iqueue.push(x);
        this->size++;

        this->notEmptyCond.wakeup();
    }

    T poll() {
        MutexLockGuard mlg(&this->mutex);

        while (this->size == 0)
            this->notEmptyCond.wait(&this->mutex);

        T &t = this->iqueue.front();
        this->iqueue.pop();
        this->size--;

        this->notFullCond.wakeup();

        return t;
    }

    bool isEmpty() const {
        MutexLockGuard mlg(&this->mutex);
        return this->size == 0;
    }

    bool isFull() const {
        MutexLockGuard mlg(&this->mutex);
        return this->size == this->capacity;
    }

    size_t getSize() const {
        MutexLockGuard mlg(&this->mutex);
        return this->size;
    }

    size_t getCapacity() const {
        MutexLockGuard mlg(&this->mutex);
        return this->capacity;
    }

private:
    size_t size;
    size_t capacity;

    MutexLock mutex;
    ConditionVariable notEmptyCond;
    ConditionVariable notFullCond;
    std::queue<T> iqueue;
};


#endif //TRAFFICER_BOUNDEDBLOCKINGQUEUE_H
