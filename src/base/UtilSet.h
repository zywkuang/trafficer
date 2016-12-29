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
    static void delayNanosleep(uint32_t usecs);
    static void delayBusyloop(uint32_t usecs);
    static void delaySelect(uint32_t usecs);
};


#endif //TRAFFICER_UTILSET_H
