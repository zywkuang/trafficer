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

void MccDataStore::insertAgentHostInfo(uint64_t hid, AgentHostInfo *hostinfo) {
    MutexLockGuard mlg(&this->hostMutex);
}

AgentHostInfo *MccDataStore::retrieveAgentHostInfo(uint64_t hid) {
    MutexLockGuard mlg(&this->hostMutex);
}

void MccDataStore::removeAgentHostInfo(uint64_t hid) {
    MutexLockGuard mlg(&this->hostMutex);
}

void MccDataStore::insertAgentConnection(uint64_t conn, TcpMessageConnection *messageConnection) {
    MutexLockGuard mlg(&this->connMutex);
}

TcpMessageConnection *MccDataStore::retrieveAgentConnection(uint64_t conn) {
    MutexLockGuard mlg(&this->connMutex);
}

void MccDataStore::removeAgentConnection(uint64_t conn) {
    MutexLockGuard mlg(&this->connMutex);
}

void MccDataStore::createTrafficInstance(uint64_t tiid, TrafficInstanceConfig *instance) {
    MutexLockGuard mlg(&this->instanceMutex);
}

TrafficInstanceConfig* MccDataStore::retrieveTrafficInstance(uint64_t tiid) const {
    MutexLockGuard mlg(&this->instanceMutex);
}

void MccDataStore::updateTrafficInstance(uint64_t tiid, TrafficInstanceConfig *newInstance) {
    MutexLockGuard mlg(&this->instanceMutex);
}

void MccDataStore::deleteTrafficInstance(uint64_t tiid) {
    MutexLockGuard mlg(&this->instanceMutex);
}