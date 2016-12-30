/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTUDPTRAFFICSENDER_H
#define TRAFFICER_AGENTUDPTRAFFICSENDER_H


#include "base/Thread.h"
#include "TrafficInstanceConfig.h"
#include "net/UdpSocket.h"
#include "model/AbstractTrafficModel.h"
#include "UdpTrafficStatistic.h"

class AgentUdpTrafficSender : public Thread {
public:
    AgentUdpTrafficSender(const TrafficInstanceConfig &tic);
    virtual ~AgentUdpTrafficSender();

    void updateTrafficConfig(const TrafficInstanceConfig &newTic);

    virtual void run();

private:
    UdpSocket *uSock;

    UdpTrafficStatistic overallTrafficStat;
    UdpTrafficStatistic tmpTrafficStat;

    AbstractTrafficModel *tModel;
    char *sendBuf;
};


#endif //TRAFFICER_AGENTUDPTRAFFICSENDER_H
