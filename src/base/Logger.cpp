//
// Created by zjl on 12/23/16.
//

#include <fcntl.h>
#include <stdio.h>
#include "Logger.h"
#include "../config.h"
#include "Exception.h"

Logger *Logger::logger = NULL;
MutexLock Logger::mutex = PTHREAD_MUTEX_INITIALIZER;

Logger::Logger() {
    this->fileFd = open(LOG_FILE_NAME, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (this->fileFd == -1)
        throw Exception(EFILEOPEN, "File Open Exception");
}

Logger::~Logger() {
    close(this->fileFd);
}


