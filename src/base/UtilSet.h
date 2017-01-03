/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#ifndef TRAFFICER_UTILSET_H
#define TRAFFICER_UTILSET_H

#include <stdint.h>
#include <string>

#define Random(x) (rand() % x)
#define Htonll(x) ((1==htonl(1)) ? (x) : ((uint64_t)htonl((x) & 0xFFFFFFFF) << 32) | htonl((x) >> 32))
#define Ntohll(x) ((1==ntohl(1)) ? (x) : ((uint64_t)ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32))

class UtilSet {
public:
    // Using snowflake algorithm to generate uuid
    static uint64_t generateUUID();

    // Set file descriptor non-blocking
    static void setNonBlocking(int fd, bool nonblocking);

    // Retrieve basic information from os
    static std::string getHostName();
    static std::string getHostSysinfo();
    static std::string getHostAddress();

    // Delay function
    static void delayNanosleep(int64_t usecs);
    static void delayBusyloop(int64_t usecs);
    static void delaySelect(int64_t usecs);
};


#endif //TRAFFICER_UTILSET_H
