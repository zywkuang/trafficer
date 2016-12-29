/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include "MccDataStore.h"
#include "base/UtilSet.h"

const uint64_t MccDataStore::mccHostUUID = UtilSet::generateUUID();

MccDataStore::MccDataStore() {

}

MccDataStore::~MccDataStore() {

}

void MccDataStore::insertAgentHostInfo(uint64_t hid, const AgentHostInfo &hostinfo) {
    MutexLockGuard mlg(&this->hostMutex);
    this->agentHostInfoMap.insert(std::pair<uint64_t, AgentHostInfo>(hid, hostinfo));
}

const AgentHostInfo &MccDataStore::retrieveAgentHostInfo(uint64_t hid) const {
    MutexLockGuard mlg(&this->hostMutex);

    AgentHostInfo hostInfo;
    std::map<uint64_t, AgentHostInfo>::iterator it = this->agentHostInfoMap.find(hid);
    if (it != this->agentHostInfoMap.end())
        hostInfo = it->second;

    return hostInfo;
}

void MccDataStore::removeAgentHostInfo(uint64_t hid) {
    MutexLockGuard mlg(&this->hostMutex);

    std::map<uint64_t, AgentHostInfo>::iterator it = this->agentHostInfoMap.find(hid);
    if (it != this->agentHostInfoMap.end())
        this->agentHostInfoMap.erase(it);
}

void MccDataStore::createTrafficInstanceConfig(uint64_t tiid, const TrafficInstanceConfig &instance) {
    MutexLockGuard mlg(&this->instanceMutex);

    this->agentTrafficInstanceConfigMap.insert(std::pair<uint64_t, TrafficInstanceConfig>(tiid, instance));
}

const TrafficInstanceConfig &MccDataStore::retrieveTrafficInstanceConfig(uint64_t tiid) const {
    MutexLockGuard mlg(&this->instanceMutex);

    TrafficInstanceConfig ptic;
    std::map<uint64_t, TrafficInstanceConfig>::iterator it = this->agentTrafficInstanceConfigMap.find(tiid);
    if (it != this->agentTrafficInstanceConfigMap.end())
        ptic = it->second;

    return ptic;
}

void MccDataStore::updateTrafficInstanceConfig(uint64_t tiid, const TrafficInstanceConfig &newInstance) {
    MutexLockGuard mlg(&this->instanceMutex);

    this->agentTrafficInstanceConfigMap.insert(std::pair<uint64_t, TrafficInstanceConfig>(tiid, newInstance));
}

void MccDataStore::deleteTrafficInstanceConfig(uint64_t tiid) {
    MutexLockGuard mlg(&this->instanceMutex);

    std::map<uint64_t, TrafficInstanceConfig>::iterator it = this->agentTrafficInstanceConfigMap.find(tiid);
    if (it != this->agentTrafficInstanceConfigMap.end())
        this->agentTrafficInstanceConfigMap.erase(it);
}

void MccDataStore::insertAgentConnection(uint64_t cid, TcpMessageConnection *messageConnection) {
    MutexLockGuard mlg(&this->connMutex);

    this->agentConnectionMap.insert(std::pair<uint64_t, TcpMessageConnection*>(cid, messageConnection));
}

TcpMessageConnection *MccDataStore::retrieveAgentConnection(uint64_t cid) const {
    MutexLockGuard mlg(&this->connMutex);

    TcpMessageConnection *pmc = NULL;
    std::map<uint64_t, TcpMessageConnection*>::iterator it = this->agentConnectionMap.find(cid);
    if (it != this->agentConnectionMap.end())
        pmc = it->second;

    return pmc;
}

void MccDataStore::removeAgentConnection(uint64_t cid) {
    MutexLockGuard mlg(&this->connMutex);

    std::map<uint64_t, TcpMessageConnection*>::iterator it = this->agentConnectionMap.find(cid);
    if (it != this->agentConnectionMap.end())
        this->agentConnectionMap.erase(it);
}

