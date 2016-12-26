/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#ifndef TRAFFICER_EVENT_H
#define TRAFFICER_EVENT_H

#include "NonCopyable.h"
#include "Mutex.h"

class Event : public NonCopyable {
public:
    Event();
    explicit Event(bool bsem);
    virtual ~Event();

    void set();
    void wait();

private:
    MutexLock mutex;
    ConditionVariable condition;
    int flag;
    bool bsem;
};


#endif //TRAFFICER_EVENT_H
