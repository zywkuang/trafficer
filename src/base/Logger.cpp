/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/23/16
**/

#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "Logger.h"
#include "Exception.h"
#include "TimeStamp.h"
#include "../Envcfg.h"

const char *LogLevelName[Logger::NUM_LOG_LEVELS] = {
        "DEBUG ",
        "INFO  ",
        "WARN  ",
        "ERROR ",
        "FATAL ",
};

Logger* Logger::logger = NULL;
MutexLock* Logger::cMutex = new MutexLock();

Logger::Logger() {
    this->fileFd = open(LOG_FILE_NAME, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (this->fileFd == -1)
        throw Exception(EFILEOPEN, "File Open Exception");

    this->wMutex = new MutexLock();
    this->logBuffer = new char[LOG_BUFFER_SIZE];
    this->usedBytesForBuffer = 0;
}

Logger::~Logger() {
    close(this->fileFd);
}

Logger* Logger::getLoggerInstance() {
    if (Logger::logger == NULL) {
        MutexLockGuard mlg(Logger::cMutex);

        if (Logger::logger == NULL) {
            Logger::logger = new Logger();

            int ret = atexit(Logger::flushLog);
            if (ret == -1)
                throw Exception(EATEXITREG, "AtExit Registration Exception");
        }
    }

    return Logger::logger;
}

void Logger::writeLog(std::string logContent, LogLevel level, const char *filename, int line) {
    Logger *logger = Logger::getLoggerInstance();

    logger->writeLogToFile(logContent, level, filename, line);
}

void Logger::writeLogToFile(std::string &logContent, LogLevel level, const char *filename, int line) {
    MutexLockGuard mlg(this->wMutex);

    int ret = 0;
    char logMsg[LOG_LINE_SIZE];
    TimeStamp ts = TimeStamp::now();

    snprintf(logMsg, LOG_LINE_SIZE, "%s\t%s\t%s:%d\t\r\n%s\r\n",
             ts.toFormattedString(true).c_str(), LogLevelName[level], filename, line, logContent.c_str());

    int totalLogLen = strlen(logMsg);

    if (totalLogLen > LOG_BUFFER_SIZE) {
        // Flush current log buffer
        ret = write(this->fileFd, this->logBuffer, usedBytesForBuffer);

        if (ret == -1)
            throw Exception(EFILEWRITE, "File Write Exception");

        usedBytesForBuffer = 0;

        // Write logMsg into file directly
        ret = write(this->fileFd, logMsg, totalLogLen);

        if (ret == -1)
            throw Exception(EFILEWRITE, "File Write Exception");

    } else {
        unsigned int leftRoom = LOG_BUFFER_SIZE - usedBytesForBuffer;

        if (totalLogLen > leftRoom) {
            ret = write(this->fileFd, this->logBuffer, usedBytesForBuffer);

            if (ret == -1)
                throw Exception(EFILEWRITE, "File Write Exception");

            usedBytesForBuffer = 0;
        }

        memcpy(this->logBuffer + usedBytesForBuffer, logMsg, totalLogLen);
        usedBytesForBuffer += totalLogLen;
    }
}

void Logger::flushLog() {
    Logger *logger = Logger::logger;

    logger->flushLogToFile();
}

void Logger::flushLogToFile() {
    MutexLockGuard mlg(this->wMutex);

    if (usedBytesForBuffer == 0)
        return;

    int ret = 0;
    ret = write(this->fileFd, this->logBuffer, usedBytesForBuffer);

    if (ret == -1)
        throw Exception(EFILEWRITE, "File Write Exception");

    usedBytesForBuffer = 0;
}