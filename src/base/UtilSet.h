/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#ifndef TRAFFICER_UTILSET_H
#define TRAFFICER_UTILSET_H

#include <stdint.h>

#define Random(x) (rand() % x)

class UtilSet {
public:
    static uint64_t generateUUID();
};


#endif //TRAFFICER_UTILSET_H
