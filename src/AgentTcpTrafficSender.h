/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTTCPTRAFFICSENDER_H
#define TRAFFICER_AGENTTCPTRAFFICSENDER_H


#include "base/Thread.h"
#include "TrafficInstanceConfig.h"

class AgentTcpTrafficSender : public Thread {
public:
    AgentTcpTrafficSender(const TrafficInstanceConfig &tic);
    virtual ~AgentTcpTrafficSender();

    void updateTrafficConfig(const TrafficInstanceConfig &newTic);
private:

};


#endif //TRAFFICER_AGENTTCPTRAFFICSENDER_H
