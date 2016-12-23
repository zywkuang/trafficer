//
// Created by zjl on 12/23/16.
//

#ifndef TRAFFICER_TIMESTAMP_H
#define TRAFFICER_TIMESTAMP_H

#include <sys/param.h>
#include <string>
#include "Copyable.h"

class TimeStamp : public Copyable{
public:
    TimeStamp() : microSecondsSinceEpoch(0) {

    }

    explicit TimeStamp(int64_t msFromEpoch) : microSecondsSinceEpoch(msFromEpoch) {

    }

    std::string toString() const;
    std::string toFormattedString(bool showMicroSeconds = true) const;

    bool isValid() const {
        return microSecondsSinceEpoch > 0;
    }

    int64_t getMicroSecondsSinceEpoch() const {
        return microSecondsSinceEpoch;
    }

    time_t getSecondsSinceEpoch() const {
        return static_cast<time_t>(microSecondsSinceEpoch / kMicroSecondsPerSecond);
    }

    static TimeStamp now();

    static TimeStamp fromUnixTime(time_t t) {
        return fromUnixTime(t, 0);
    }

    static TimeStamp fromUnixTime(time_t t, int microseconds) {
        return TimeStamp(static_cast<int64_t>(t) * kMicroSecondsPerSecond + microseconds);
    }

    static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
    int64_t microSecondsSinceEpoch;
};


#endif //TRAFFICER_TIMESTAMP_H
