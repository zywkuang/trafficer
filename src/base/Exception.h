//
// Created by zjl on 10/26/16.
//

#ifndef TRAFFICER_EXCEPTION_H
#define TRAFFICER_EXCEPTION_H

#include <exception>
#include <string>

// File Exception
#define EFILEOPEN           00001

// Socket Exception
#define ESOCKCREATE         10001
#define ESOCKCONNECT        10002
#define ESOCKBIND           10003
#define ESOCKLISTEN         10004
#define ESOCKACCEPT         10005
#define ESOCKWRITE          10006
#define ESOCKREAD           10007

// Thread Exception
#define ETHREADCREATE       20001
#define ETHREADJOIN         20002
#define ETHREADDETACH       20003

// Mutex Exception
#define EMUTEXINIT          30001
#define EMUTEXLOCK          30002
#define EMUTEXUNLOCK        30003
#define EMUTEXDESTROY       30004

// Condition Exception
#define ECONDITIONINIT      40001
#define ECONDITIONWAIT      40002
#define ECONDITIONSINGAL    40003
#define ECONDITIONBROADCAST 40004
#define ECONDITIONDESTROY   40005

// Event Exception
#define EEVENTSET           50001
#define EEVENTWAIT          50002

// MessageQueue Exception
#define EMSGQUEUEPUSH       60001
#define EMSGQUEUEPOP        60002

class Exception : public std::exception{
public:
    explicit Exception(int errcode, const char *what);
    virtual ~Exception() throw();

    virtual const char* what() const throw();
    virtual const int code() const throw();

private:
    int errcode;
    const char* message;
};

#endif //TRAFFICER_EXCEPTION_H
