/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include "AgentDataStore.h"
#include "base/UtilSet.h"

uint64_t AgentDataStore::agentHostUUID = UtilSet::generateUUID();
std::string AgentDataStore::agentHostName = UtilSet::getHostName();
std::string AgentDataStore::agentHostAddress = UtilSet::getHostAddress();
std::string AgentDataStore::agentHostSysinfo = UtilSet::getHostSysinfo();

AgentDataStore::AgentDataStore() {

}

AgentDataStore::~AgentDataStore() {

}

void AgentDataStore::createTrafficInstanceConfig(uint64_t tiid, const TrafficInstanceConfig &instance) {
    MutexLockGuard mlg(&this->instanceMutex);

    this->trafficInstanceConfigMap[tiid] = instance;
}

const TrafficInstanceConfig &AgentDataStore::retrieveTrafficInstanceConfig(uint64_t tiid) const {
    MutexLockGuard mlg(&this->instanceMutex);

    return this->trafficInstanceConfigMap[tiid];
}

void AgentDataStore::updateTrafficInstanceConfig(uint64_t tiid, const TrafficInstanceConfig &newInstance) {
    MutexLockGuard mlg(&this->instanceMutex);

    this->trafficInstanceConfigMap[tiid] = newInstance;
}

void AgentDataStore::deleteTrafficInstanceConfig(uint64_t tiid) {
    MutexLockGuard mlg(&this->instanceMutex);

    this->trafficInstanceConfigMap.erase(tiid);
}

void AgentDataStore::insertAgentTcpTrafficSender(uint64_t tiid, AgentTcpTrafficSender *tts) {
    MutexLockGuard mlg(&this->tsMutex);

    this->tcpSenderMap[tiid] = tts;
}

AgentTcpTrafficSender* AgentDataStore::retrieveAgentTcpTrafficSender(uint64_t tiid) const {
    MutexLockGuard mlg(&this->tsMutex);

    return this->tcpSenderMap[tiid];
}

void AgentDataStore::removeAgentTcpTrafficSender(uint64_t tiid) {
    MutexLockGuard mlg(&this->tsMutex);

    delete this->tcpSenderMap[tiid];
    this->tcpSenderMap.erase(tiid);
}

void AgentDataStore::insertAgentUdpTrafficSender(uint64_t tiid, AgentUdpTrafficSender *uts) {
    MutexLockGuard mlg(&this->usMutex);

    this->udpSenderMap[tiid] = uts;
}

AgentUdpTrafficSender* AgentDataStore::retrieveAgentUdpTrafficSender(uint64_t tiid) const {
    MutexLockGuard mlg(&this->usMutex);

    return this->udpSenderMap[tiid];
}

void AgentDataStore::removeAgentUdpTrafficSender(uint64_t tiid) {
    MutexLockGuard mlg(&this->usMutex);

    delete this->udpSenderMap[tiid];
    this->udpSenderMap.erase(tiid);
}