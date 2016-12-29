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

    this->trafficInstanceConfigMap.insert(std::pair<uint64_t, TrafficInstanceConfig>(tiid, instance));
}

const TrafficInstanceConfig &AgentDataStore::retrieveTrafficInstanceConfig(uint64_t tiid) const {
    MutexLockGuard mlg(&this->instanceMutex);

    TrafficInstanceConfig tic;
    std::map<uint64_t, TrafficInstanceConfig>::iterator it = this->trafficInstanceConfigMap.find(tiid);
    if (it != this->trafficInstanceConfigMap.end())
        tic = it->second;

    return tic;
}

void AgentDataStore::updateTrafficInstanceConfig(uint64_t tiid, const TrafficInstanceConfig &newInstance) {
    MutexLockGuard mlg(&this->instanceMutex);

    this->trafficInstanceConfigMap.insert(std::pair<uint64_t, TrafficInstanceConfig>(tiid, newInstance));
}

void AgentDataStore::deleteTrafficInstanceConfig(uint64_t tiid) {
    MutexLockGuard mlg(&this->instanceMutex);

    std::map<uint64_t, TrafficInstanceConfig>::iterator it = this->trafficInstanceConfigMap.find(tiid);
    if (it != this->trafficInstanceConfigMap.end())
        this->trafficInstanceConfigMap.erase(it);
}

void AgentDataStore::insertAgentTcpTrafficSender(uint64_t tiid, AgentTcpTrafficSender *tts) {
    MutexLockGuard mlg(&this->tsMutex);

    this->tcpSenderMap.insert(std::pair<uint64_t, AgentTcpTrafficSender*>(tiid, tts));
}

AgentTcpTrafficSender* AgentDataStore::retrieveAgentTcpTrafficSender(uint64_t tiid) const {
    MutexLockGuard mlg(&this->tsMutex);

    AgentTcpTrafficSender *ats = NULL;
    std::map<uint64_t, AgentTcpTrafficSender*>::iterator it = this->tcpSenderMap.find(tiid);
    if (it != this->tcpSenderMap.end())
        ats = it->second;

    return ats;
}

void AgentDataStore::removeAgentTcpTrafficSender(uint64_t tiid) {
    MutexLockGuard mlg(&this->tsMutex);

    std::map<uint64_t, AgentTcpTrafficSender*>::iterator it = this->tcpSenderMap.find(tiid);
    if (it != this->tcpSenderMap.end())
        this->tcpSenderMap.erase(it);
}

void AgentDataStore::insertAgentUdpTrafficSender(uint64_t tiid, AgentUdpTrafficSender *uts) {
    MutexLockGuard mlg(&this->usMutex);

    this->udpSenderMap.insert(std::pair<uint64_t, AgentUdpTrafficSender*>(tiid, uts));
}

AgentUdpTrafficSender* AgentDataStore::retrieveAgentUdpTrafficSender(uint64_t tiid) const {
    MutexLockGuard mlg(&this->usMutex);

    AgentUdpTrafficSender *aus = NULL;
    std::map<uint64_t, AgentUdpTrafficSender*>::iterator it = this->udpSenderMap.find(tiid);
    if (it != this->udpSenderMap.end())
        aus = it->second;

    return aus;
}

void AgentDataStore::removeAgentUdpTrafficSender(uint64_t tiid) {
    MutexLockGuard mlg(&this->usMutex);

    std::map<uint64_t, AgentUdpTrafficSender*>::iterator it = this->udpSenderMap.find(tiid);
    if (it != this->udpSenderMap.end())
        this->udpSenderMap.erase(it);
}