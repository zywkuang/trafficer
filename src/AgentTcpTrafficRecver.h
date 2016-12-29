/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTTCPTRAFFICRECVER_H
#define TRAFFICER_AGENTTCPTRAFFICRECVER_H


#include "base/Thread.h"

class AgentTcpTrafficRecver : public Thread {
public:
    AgentTcpTrafficRecver();
    virtual ~AgentTcpTrafficRecver();

    int getRecverListenPort() const;

private:

};


#endif //TRAFFICER_AGENTTCPTRAFFICRECVER_H
