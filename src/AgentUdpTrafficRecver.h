/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTUDPTRAFFICRECVER_H
#define TRAFFICER_AGENTUDPTRAFFICRECVER_H


#include "base/Thread.h"

class AgentUdpTrafficRecver : public Thread {
public:
    AgentUdpTrafficRecver();
    virtual ~AgentUdpTrafficRecver();

    int getRecverListenPort() const;

private:
};


#endif //TRAFFICER_AGENTUDPTRAFFICRECVER_H
