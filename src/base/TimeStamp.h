//
// Created by zjl on 12/23/16.
//

#ifndef TRAFFICER_TIMESTAMP_H
#define TRAFFICER_TIMESTAMP_H

#include <sys/param.h>
#include <string>
#include "Copyable.h"

#define MICROSECOND_PER_SECOND 1000000
#define NANOSECOND_PER_SECOND 1000000000

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

    void setMicroSecondsSinceEpoch(int64_t mss) {
        this->microSecondsSinceEpoch = mss;
    }

    time_t getSecondsSinceEpoch() const {
        return static_cast<time_t>(microSecondsSinceEpoch / MICROSECOND_PER_SECOND);
    }

    bool isMoreThan(TimeStamp &tm) {
        return this->microSecondsSinceEpoch > tm.getMicroSecondsSinceEpoch();
    }

    bool isLessThan(TimeStamp &tm) {
        return this->microSecondsSinceEpoch < tm.getMicroSecondsSinceEpoch();
    }

    int64_t diffTimeStamp(TimeStamp &tm) {
        return this->microSecondsSinceEpoch - tm.getMicroSecondsSinceEpoch();
    }

    void addMicroSeconds(int64_t increMicroSeconds) {
        this->microSecondsSinceEpoch += increMicroSeconds;
    }

    static TimeStamp now();

    static TimeStamp fromUnixTime(time_t t) {
        return fromUnixTime(t, 0);
    }

    static TimeStamp fromUnixTime(time_t t, int microseconds) {
        return TimeStamp(static_cast<int64_t>(t) * MICROSECOND_PER_SECOND + microseconds);
    }

private:
    int64_t microSecondsSinceEpoch;
};


#endif //TRAFFICER_TIMESTAMP_H
