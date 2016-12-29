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
#include "AgentHostInfo.h"
#include "net/TcpSocket.h"
#include "TrafficInstanceConfig.h"
#include "base/Mutex.h"
#include "TcpMessageConnection.h"

class MccDataStore {
public:
    MccDataStore();
    ~MccDataStore();

    // ID = AgentHost UUID
    void insertAgentHostInfo(uint64_t hid, const AgentHostInfo &hostinfo);
    const AgentHostInfo &retrieveAgentHostInfo(uint64_t hid) const;
    void removeAgentHostInfo(uint64_t hid);

    // ID = TrafficInstance UUID
    void createTrafficInstanceConfig(uint64_t tiid, const TrafficInstanceConfig &instance);
    const TrafficInstanceConfig &retrieveTrafficInstanceConfig(uint64_t tiid) const;
    void updateTrafficInstanceConfig(uint64_t tiid, const TrafficInstanceConfig &newInstance);
    void deleteTrafficInstanceConfig(uint64_t tiid);

    // ID = AgentHost UUID
    void insertAgentConnection(uint64_t cid, TcpMessageConnection *msgConn);
    TcpMessageConnection *retrieveAgentConnection(uint64_t cid) const;
    void removeAgentConnection(uint64_t cid);

private:
    MutexLock hostMutex;
    std::map<uint64_t, AgentHostInfo> agentHostInfoMap;

    MutexLock instanceMutex;
    std::map<uint64_t, TrafficInstanceConfig> agentTrafficInstanceConfigMap;

    MutexLock connMutex;
    std::map<uint64_t, TcpMessageConnection*> agentConnectionMap;
public:
    static const uint64_t mccHostUUID;
};


#endif //TRAFFICER_MCCDATASTORE_H
