/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTUDPTRAFFICSENDER_H
#define TRAFFICER_AGENTUDPTRAFFICSENDER_H


#include "base/Thread.h"
#include "TrafficInstanceConfig.h"

class AgentUdpTrafficSender : public Thread {
public:
    AgentUdpTrafficSender(const TrafficInstanceConfig &tic);
    virtual ~AgentUdpTrafficSender();

    void updateTrafficConfig(const TrafficInstanceConfig &newTic);
};


#endif //TRAFFICER_AGENTUDPTRAFFICSENDER_H
