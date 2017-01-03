/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include <fcntl.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include "UtilSet.h"
#include "Logger.h"
#include "TimeStamp.h"
#include "Exception.h"
#include "../Trafficer.h"


uint64_t UtilSet::generateUUID() {
    uint64_t idval = 0;

    const uint64_t EPOCH = 1367505795100;
    const int MACHINE = MACHINE_CODE;

    // Get System Time
    struct timeval tv;
    gettimeofday(&tv, NULL);

    uint64_t msCnt = tv.tv_usec;
    msCnt = msCnt / 1000;
    msCnt = msCnt + tv.tv_sec * 1000;

    uint64_t timePart = msCnt - EPOCH;

    // 44 bit time part
    idval |= timePart << 22;

    // 10 bit machine part
    idval |= MACHINE & 0x3ff << 12;

    // 12 bit sequence part
    int sequence = Random(4096);
    idval |= sequence & 0xfff;

    return idval;
}

void UtilSet::setNonBlocking(int fd, bool nonblocking) {
    int flags, newflags;

    flags = fcntl(fd, F_GETFL, 0);

    if (flags < 0) {
        LOG_ERROR("Fcntl(F_GETFL) operation error.");
        throw Exception(EFCNTLGET, "Fcntl Get Exception");
    }

    if (nonblocking)
        newflags = flags | static_cast<int>(nonblocking);
    else
        newflags = flags & ~(static_cast<int>(nonblocking));

    if (newflags != flags) {
        if (fcntl(fd, F_SETFL, newflags) < 0) {
            LOG_ERROR("Fcntl(F_SETFL) operation error.");
            throw Exception(EFCNTLSET, "Fcntl Set Exception");
        }
    }
}

std::string UtilSet::getHostName() {
    struct utsname buf;
    uname(&buf);

    std::string hostName = buf.nodename;

    return hostName;
}

std::string UtilSet::getHostSysinfo() {
    struct utsname buf;
    uname(&buf);

    std::string sysname = buf.sysname;
    std::string machine = buf.machine;
    std::string sysinfo = sysname + " " + machine;

    return sysinfo;
}

std::string UtilSet::getHostAddress() {
    struct ifaddrs *pIfAddrs = NULL;
    void *pTmpAddr = NULL;

    char addrBuf[INET_ADDRSTRLEN] = "127.0.0.1";
    getifaddrs(&pIfAddrs);

    while (NULL != pIfAddrs) {
        if (pIfAddrs->ifa_addr->sa_family == AF_INET) {
            pTmpAddr = &((struct sockaddr_in *)pIfAddrs->ifa_addr)->sin_addr;

            inet_ntop(AF_INET, pTmpAddr, addrBuf, INET_ADDRSTRLEN);

            if (strcmp(pIfAddrs->ifa_name, DEFAULT_INTERFACE) == 0)
                return addrBuf;
        }

        pIfAddrs = pIfAddrs->ifa_next;
    }

    freeifaddrs(pIfAddrs);
    return addrBuf;
}

void UtilSet::delayBusyloop(int64_t usecs) {
    TimeStamp nowTS = TimeStamp::now();
    TimeStamp targetTS = TimeStamp::now();
    targetTS.addMicroSeconds(usecs);

    while (true) {
        TimeStamp tmpTs = TimeStamp::now();
        if (tmpTs.isMoreThan(targetTS))
            break;
    }
}

void UtilSet::delayNanosleep(int64_t usecs) {
    struct timespec requested = {0, 0};
    struct timespec remaining;

    requested.tv_nsec += usecs * 1000;

    while (requested.tv_nsec >= NANOSECOND_PER_SECOND) {
        requested.tv_sec++;
        requested.tv_nsec -= NANOSECOND_PER_SECOND;
    }

    nanosleep(&requested, &remaining);
}

void UtilSet::delaySelect(int64_t usecs) {
    struct timeval tv = {0, 0};

    tv.tv_usec += usecs;

    while (tv.tv_usec >= MICROSECOND_PER_SECOND) {
        tv.tv_sec++;
        tv.tv_usec -= MICROSECOND_PER_SECOND;
    }

    select(0, NULL, NULL, NULL, &tv);
}