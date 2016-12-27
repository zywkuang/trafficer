/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/27/16
**/

#include "TrafficInstanceConfig.h"

TrafficInstanceConfig::TrafficInstanceConfig()
        : senderHostAddress("10.0.0.1"),
          recverHostAddress("10.0.0.2"),
          serverHostPort(TRAFFICER_TCP_SERVER_PORT),
          role(SENDER),
          proto(TCP),
          workDuration(-1),
          reportInterval(2000),
          updateIntervel(500),
          sendBufSize(TRAFFIC_TCP_SENDBUF_SIZE),
          tcpNoDelay(false),
          tcpMss(-1),
          trafficModel(STABLE_TRAFFIC) {

}

TrafficInstanceConfig::~TrafficInstanceConfig() {

}

void TrafficInstanceConfig::setSenderHostAddress(const std::string &senderHostAddress) {
    this->senderHostAddress = senderHostAddress;
}

const std::string &TrafficInstanceConfig::getSenderHostAddress() const {
    return this->senderHostAddress;
}

void TrafficInstanceConfig::setRecverHostAddress(const std::string &recverHostAddress) {
    this->recverHostAddress = recverHostAddress;
}

const std::string &TrafficInstanceConfig::getRecverHostAddress() const {
    return this->recverHostAddress;
}

void TrafficInstanceConfig::setServerHostPort(int serverHostPort) {
    this->serverHostPort = serverHostPort;
}

int TrafficInstanceConfig::getServerHostPort() const {
    return this->serverHostPort;
}

void TrafficInstanceConfig::setProtocol(ProtocolType proto) {
    this->proto = proto;
}

ProtocolType TrafficInstanceConfig::getProtocol() const {
    return this->proto;
}

void TrafficInstanceConfig::setRole(RoleType role) {
    this->role = role;
}

RoleType TrafficInstanceConfig::getRole() const {
    return this->role;
}

void TrafficInstanceConfig::setWorkDuration(int workDuration) {
    this->workDuration = workDuration;
}

int TrafficInstanceConfig::getWorkDuration() const {
    return this->workDuration;
}

void TrafficInstanceConfig::setReportInterval(int reportInterval) {
    this->reportInterval = reportInterval;
}

int TrafficInstanceConfig::getReportInterval() const {
    return this->reportInterval;
}

void TrafficInstanceConfig::setSendBufSize(int sendBufSize) {
    this->sendBufSize = sendBufSize;
}

int TrafficInstanceConfig::getSendBufSize() const {
    return this->sendBufSize;
}

void TrafficInstanceConfig::setUpdateIntervel(int updateIntervel) {
    this->updateIntervel = updateIntervel;
}

int TrafficInstanceConfig::getUpdateIntervel() const {
    return this->updateIntervel;
}

void TrafficInstanceConfig::setTcpNoDelay(bool tcpNoDelay) {
    this->tcpNoDelay = tcpNoDelay;
}

bool TrafficInstanceConfig::isTcpNoDelay() const {
    return this->tcpNoDelay;
}

void TrafficInstanceConfig::setTcpMss(int tcpMss) {
    this->tcpMss = tcpMss;
}

int TrafficInstanceConfig::getTcpMss() const {
    return this->tcpMss;
}

void TrafficInstanceConfig::setTrafficModel(TrafficModelType trafficModel) {
    this->trafficModel = trafficModel;
}

TrafficModelType TrafficInstanceConfig::getTrafficModel() const {
    return this->trafficModel;
}

void TrafficInstanceConfig::setStableTrafficBandwidth(uint64_t stableTrafficBandwidth) {
    this->stableTrafficBandwidth = stableTrafficBandwidth;
}

uint64_t TrafficInstanceConfig::getStableTrafficBandwidth() const {
    return this->stableTrafficBandwidth;
}

void TrafficInstanceConfig::setRectSupremumTrafficBandwidth(uint64_t rectSupremumTrafficBandwidth) {
    this->rectSupremumTrafficBandwidth = rectSupremumTrafficBandwidth;
}

uint64_t TrafficInstanceConfig::getRectSupremumTrafficBandwidth() const {
    return this->rectSupremumTrafficBandwidth;
}

void TrafficInstanceConfig::setRectInfimumTrafficBandwidth(uint64_t rectInfimumTrafficBandwidth) {
    this->rectInfimumTrafficBandwidth = rectInfimumTrafficBandwidth;
}

uint64_t TrafficInstanceConfig::getRectInfimumTrafficBandwidth() const {
    return this->rectInfimumTrafficBandwidth;
}

void TrafficInstanceConfig::setRectSupreProportion(double rectSupreProportion) {
    this->rectSupreProportion = rectSupreProportion;
}

double TrafficInstanceConfig::getRectSupreProportion() const {
    return this->rectSupreProportion;
}

void TrafficInstanceConfig::setPoissonBurstTrafficBandwidth(uint64_t poissonBurstTrafficBandwidth) {
    this->poissonBurstTrafficBandwidth = poissonBurstTrafficBandwidth;
}

uint64_t TrafficInstanceConfig::getPoissonBurstTrafficBandwidth() const {
    return this->poissonBurstTrafficBandwidth;
}


