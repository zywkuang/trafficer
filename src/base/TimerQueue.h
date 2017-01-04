/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 1/4/17
**/

#ifndef TRAFFICER_TIMERQUEUE_H
#define TRAFFICER_TIMERQUEUE_H

#include <stdint.h>
#include <queue>
#include <vector>
#include "TimeStamp.h"

class TimerInfo {
public:
    TimeStamp timeStamp;
    uint64_t itemId;

    TimerInfo(const TimeStamp &tm, uint64_t eid)
            : timeStamp(tm),
              itemId(eid) {
    }

    ~TimerInfo() {

    }

    bool operator < (const TimerInfo &other) const {
        return this->timeStamp.getMicroSecondsSinceEpoch() < other.timeStamp.getMicroSecondsSinceEpoch();
    }

    bool operator > (const TimerInfo &other) const {
        return this->timeStamp.getMicroSecondsSinceEpoch() > other.timeStamp.getMicroSecondsSinceEpoch();
    }
};

class TimerQueue {
public:
    TimerQueue() : timerQueue(){

    }

    ~TimerQueue() {

    }

    uint64_t popFrontTimer() {
        TimeStamp now = TimeStamp::now();
        TimerInfo ti = this->timerQueue.top();

        if (now.isMoreThan(ti.timeStamp))
            return ti.itemId;

        return 0;
    }

    void pushBackTimer(const TimerInfo &timerInfo) {
        this->timerQueue.push(timerInfo);
    }

private:
    std::priority_queue<TimerInfo, std::vector<TimerInfo>, std::less<TimerInfo>> timerQueue;
};

#endif //TRAFFICER_TIMERQUEUE_H
