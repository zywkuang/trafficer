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

    this->agentHostInfoMap[hid] = hostinfo;
}

const AgentHostInfo &MccDataStore::retrieveAgentHostInfo(uint64_t hid) const {
    MutexLockGuard mlg(&this->hostMutex);

    return this->agentHostInfoMap[hid];
}

void MccDataStore::removeAgentHostInfo(uint64_t hid) {
    MutexLockGuard mlg(&this->hostMutex);

    this->agentHostInfoMap.erase(hid);
}

void MccDataStore::createTrafficInstanceConfig(uint64_t tiid, const TrafficInstanceConfig &instance) {
    MutexLockGuard mlg(&this->instanceMutex);

    this->agentTrafficInstanceConfigMap[tiid] = instance;
}

const TrafficInstanceConfig &MccDataStore::retrieveTrafficInstanceConfig(uint64_t tiid) const {
    MutexLockGuard mlg(&this->instanceMutex);

    return this->agentTrafficInstanceConfigMap[tiid];
}

void MccDataStore::updateTrafficInstanceConfig(uint64_t tiid, const TrafficInstanceConfig &newInstance) {
    MutexLockGuard mlg(&this->instanceMutex);

    this->agentTrafficInstanceConfigMap[tiid] = newInstance;
}

void MccDataStore::deleteTrafficInstanceConfig(uint64_t tiid) {
    MutexLockGuard mlg(&this->instanceMutex);

    this->agentTrafficInstanceConfigMap.erase(tiid);
}

void MccDataStore::insertAgentConnection(uint64_t cid, TcpMessageConnection *messageConnection) {
    MutexLockGuard mlg(&this->connMutex);

    this->agentConnectionMap[cid] = messageConnection;
}

TcpMessageConnection *MccDataStore::retrieveAgentConnection(uint64_t cid) const {
    MutexLockGuard mlg(&this->connMutex);

    return this->agentConnectionMap[cid];
}

void MccDataStore::removeAgentConnection(uint64_t cid) {
    MutexLockGuard mlg(&this->connMutex);

    this->agentConnectionMap.erase(cid);
}

