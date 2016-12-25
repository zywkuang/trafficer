//
// Created by zjl on 12/23/16.
//

#include <cstdio>
#include <sys/time.h>
#include "TimeStamp.h"

const char* TimeStamp::toString() const {
    char buf[32] = {0};
    int64_t seconds = microSecondsSinceEpoch / kMicroSecondsPerSecond;
    int64_t microSeconds = microSecondsSinceEpoch % kMicroSecondsPerSecond;
    snprintf(buf, sizeof(buf), "%ld.%6ld", seconds, microSeconds);

    return buf;
}

const char* TimeStamp::toFormattedString(bool showMicroSeconds) const {
    char buf[32] = {0};
    time_t seconds = static_cast<time_t>(microSecondsSinceEpoch / kMicroSecondsPerSecond);

    // gmtime() function converts the calendar time to broken-down time representation(UTC).
    // localtime() function converts the calendar time to broken-down time representation (user's specified timezone).
    // gmtime_r() and localtime_r() are thread-safe version.
    struct tm tm_time;
    localtime_r(&seconds, &tm_time);

    if (showMicroSeconds) {
        int microSeconds = static_cast<int>(microSecondsSinceEpoch % kMicroSecondsPerSecond);
        snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d.%06d",
                 tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                 tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec, microSeconds);
    } else {
        snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
                 tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                 tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    }

    return buf;
}

TimeStamp TimeStamp::now() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    int64_t seconds = tv.tv_sec;

    return TimeStamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
}