/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include <sys/time.h>
#include <cstdlib>
#include <fcntl.h>
#include "UtilSet.h"
#include "../Trafficer.h"
#include "Logger.h"
#include "Exception.h"

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