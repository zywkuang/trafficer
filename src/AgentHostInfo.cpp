/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include "AgentHostInfo.h"

AgentHostInfo::AgentHostInfo() {

}

AgentHostInfo::~AgentHostInfo() {

}

void AgentHostInfo::setHostAgentId(uint64_t id) {
    this->hostAgentId = id;
}

uint64_t AgentHostInfo::getHostAgentId() const {
    return this->hostAgentId;
}

void AgentHostInfo::setHostName(std::string &hostname) {
    this->hostName = hostname;
}

const std::string& AgentHostInfo::getHostName() const {
    return this->hostName;
}

void AgentHostInfo::setHostAddress(std::string &hostAddress) {
    this->hostAddress = hostAddress;
}

const std::string& AgentHostInfo::getHostAddress() const {
    return this->hostAddress;
}

void AgentHostInfo::setHostSysinfo(std::string &hostSysinfo) {
    this->hostSysinfo = hostSysinfo;
}

const std::string& AgentHostInfo::getHostSysinfo() const {
    return this->hostSysinfo;
}

void AgentHostInfo::setTcpTrafficerPort(int port) {
    this->tcpTrafficerPort = port;
}

int AgentHostInfo::getTcpTrafficerPort() const {
    return this->tcpTrafficerPort;
}

void AgentHostInfo::setUdpTrafficerPort(int port) {
    this->udpTrafficerPort = port;
}

int AgentHostInfo::getUdpTrafficerPort() const {
    return this->udpTrafficerPort;
}