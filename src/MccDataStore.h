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

    // HostInfo
    void insertAgentHostInfo(uint64_t hid, AgentHostInfo *hostinfo);
    AgentHostInfo *retrieveAgentHostInfo(uint64_t hid);
    void removeAgentHostInfo(uint64_t hid);

    // Connection
    void insertAgentConnection(uint64_t conn, TcpMessageConnection *msgConn);
    TcpMessageConnection *retrieveAgentConnection(uint64_t conn);
    void removeAgentConnection(uint64_t conn);

    // TrafficInstanceConfig
    void createTrafficInstance(uint64_t tiid, TrafficInstanceConfig *instance);
    TrafficInstanceConfig *retrieveTrafficInstance(uint64_t tiid) const;
    void updateTrafficInstance(uint64_t tiid, TrafficInstanceConfig *newInstance);
    void deleteTrafficInstance(uint64_t tiid);

private:
    MutexLock hostMutex;
    std::map<uint64_t, AgentHostInfo*> agentHostInfoMap; // uint64_t <=> agentHostID

    MutexLock connMutex;
    std::map<uint64_t, TcpMessageConnection*> agentConnectionMap; // uint64_t <=> agentConnectionID

    MutexLock instanceMutex;
    std::map<uint64_t, TrafficInstanceConfig*> agentTrafficInstanceMap; // uint64_t <=> trafficInstanceID

public:
    static const uint64_t mccHostUUID;
};


#endif //TRAFFICER_MCCDATASTORE_H
