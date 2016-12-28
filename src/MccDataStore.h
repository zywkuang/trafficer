/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_MCCDATASTORE_H
#define TRAFFICER_MCCDATASTORE_H

#include <stdint.h>
#include <string>
#include <map>
#include "base/Copyable.h"
#include "AgentHostInfo.h"

class MccDataStore {
public:

private:
    std::map<uint64_t, AgentHostInfo> agentHostInfoMap;

public:
    static const uint64_t mccHostUUID;
};


#endif //TRAFFICER_MCCDATASTORE_H
