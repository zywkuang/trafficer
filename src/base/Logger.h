//
// Created by zjl on 12/23/16.
//

#ifndef TRAFFICER_LOGGER_H
#define TRAFFICER_LOGGER_H

#include "NonCopyable.h"
#include "../thread/Mutex.h"

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class Logger : public NonCopyable {

public:
    static Logger *getLoggerInstance();
    static void Log(const char *logMsg, LogLevel level);

    void writeLog(const char *logMsg, LogLevel level);
private:
    Logger();
    ~Logger();

private:
    int fileFd;
    static Logger *logger;
    static MutexLock mutex;
};

#endif //TRAFFICER_LOGGER_H
