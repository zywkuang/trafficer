/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/23/16
**/

#ifndef TRAFFICER_LOGGER_H
#define TRAFFICER_LOGGER_H

#include <string>
#include "NonCopyable.h"
#include "Mutex.h"

#define LOG_DEBUG(str) Logger::writeLog((str), Logger::DEBUG, __FILE__, __LINE__)
#define LOG_INFO(str) Logger::writeLog((str), Logger::INFO, __FILE__, __LINE__)
#define LOG_WARN(str) Logger::writeLog((str), Logger::WARN, __FILE__, __LINE__)
#define LOG_ERROR(str) Logger::writeLog((str), Logger::ERROR, __FILE__, __LINE__)
#define LOG_FATAL(str) Logger::writeLog((str), Logger::FATAL, __FILE__, __LINE__)

class Logger : public NonCopyable {
public:
    static const int NUM_LOG_LEVELS = 5;
    enum LogLevel {
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    static Logger *getLoggerInstance();
    static void writeLog(std::string logContent, LogLevel level, const char *filename, int line);
    void writeLogToFile(std::string &logContent, LogLevel level, const char *filename, int line);

    static void flushLog();
    void flushLogToFile();

private:
    Logger();
    ~Logger();

private:
    int fileFd;
    char *logBuffer;
    unsigned int usedBytesForBuffer;
    MutexLock *wMutex;

    static Logger *logger;
    static MutexLock *cMutex;
};

#endif //TRAFFICER_LOGGER_H
