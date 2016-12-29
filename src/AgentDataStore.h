/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTDATASTORE_H
#define TRAFFICER_AGENTDATASTORE_H

#include <stdint.h>
#include <map>
#include "TcpMessageConnection.h"
#include "base/BoundedBlockingQueue.h"
#include "TrafficInstanceConfig.h"
#include "AgentTcpTrafficSender.h"
#include "AgentUdpTrafficSender.h"

class AgentDataStore {
public:
    AgentDataStore();
    ~AgentDataStore();

    // ID = TrafficInstance-UUID
    void createTrafficInstanceConfig(uint64_t tiid, const TrafficInstanceConfig &instance);
    const TrafficInstanceConfig &retrieveTrafficInstanceConfig(uint64_t tiid) const;
    void updateTrafficInstanceConfig(uint64_t tiid, const TrafficInstanceConfig &newInstance);
    void deleteTrafficInstanceConfig(uint64_t tiid);

    void insertAgentTcpTrafficSender(uint64_t tiid, AgentTcpTrafficSender *tts);
    AgentTcpTrafficSender *retrieveAgentTcpTrafficSender(uint64_t tiid) const;
    void removeAgentTcpTrafficSender(uint64_t tiid);

    void insertAgentUdpTrafficSender(uint64_t tiid, AgentUdpTrafficSender *uts);
    AgentUdpTrafficSender *retrieveAgentUdpTrafficSender(uint64_t tiid) const;
    void removeAgentUdpTrafficSender(uint64_t tiid);

private:
    MutexLock instanceMutex;
    std::map<uint64_t, TrafficInstanceConfig> trafficInstanceConfigMap;

    MutexLock tsMutex;
    std::map<uint64_t, AgentTcpTrafficSender *> tcpSenderMap;

    MutexLock usMutex;
    std::map<uint64_t, AgentUdpTrafficSender *> udpSenderMap;

    // Traffic Recver Configuration
public:
    static uint64_t agentHostUUID;
    static std::string agentHostName;
    static std::string agentHostAddress;
    static std::string agentHostSysinfo;
};


#endif //TRAFFICER_AGENTDATASTORE_H
