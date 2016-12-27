/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/27/16
**/

#include "TrafficInstanceConfig.h"

TrafficInstanceConfig::TrafficInstanceConfig()
        : senderHostAddress("10.0.0.1"),
          recverHostAddress("10.0.0.2"){

}

TrafficInstanceConfig::~TrafficInstanceConfig() {

}

void TrafficInstanceConfig::setSenderHostAddress(const std::string &senderHostAddress) {
    this->senderHostAddress = senderHostAddress;
}

const std::string &TrafficInstanceConfig::getSenderHostAddress() const {
    return this->senderHostAddress;
}

void TrafficInstanceConfig::setSenderHostPort(int senderHostPort) {
    this->senderHostPort = senderHostPort;
}

int TrafficInstanceConfig::getSenderHostPort() const {
    return this->senderHostPort;
}

void TrafficInstanceConfig::setRecverHostAddress(const std::string &recverHostAddress) {
    this->recverHostAddress = recverHostAddress;
}

const std::string &TrafficInstanceConfig::getRecverHostAddress() const {
    return this->recverHostAddress;
}

void TrafficInstanceConfig::setRecverHostPort(int recverHostPort) {
    this->recverHostPort = recverHostPort;
}

int TrafficInstanceConfig::getRecverHostPort() const {
    return this->recverHostPort;
}

void TrafficInstanceConfig::setProto(PROTOCOL proto) {
    this->proto = proto;
}

PROTOCOL TrafficInstanceConfig::getProto() const {
    return this->proto;
}

void TrafficInstanceConfig::setRole(ROLE role) {
    this->role = role;
}

ROLE TrafficInstanceConfig::getRole() const {
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

void TrafficInstanceConfig::setTrafficModel(TRAFFIC_MODEL trafficModel) {
    this->trafficModel = trafficModel;
}

TRAFFIC_MODEL TrafficInstanceConfig::getTrafficModel() const {
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