/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/27/16
**/

#ifndef TRAFFICER_TRAFFICINSTANCECONFIG_H
#define TRAFFICER_TRAFFICINSTANCECONFIG_H

#include <stdint.h>
#include <string>
#include "Trafficer.h"
#include "base/Copyable.h"

class TrafficInstanceConfig : public Copyable {
public:
    TrafficInstanceConfig()
            : senderHostAddress("10.0.0.1"),
              recverHostAddress("10.0.0.2"),
              serverHostPort(TRAFFICER_TCP_SERVER_PORT),
              role(SENDER),
              proto(TCP),
              workDuration(-1),
              reportInterval(TRAFFIC_REPORT_INTERVAL),
              updateInterval(TRAFFIC_UPDATE_INTERVAL),
              sendBufSize(TRAFFIC_TCP_SENDBUF_SIZE),
              tcpNoDelay(false),
              tcpMss(-1),
              trafficModel(STABLE_TRAFFIC){

    }
    ~TrafficInstanceConfig() {

    }

    void setTrafficInstanceId(const uint64_t tiid) {
        this->trafficInstanceId = tiid;
    }
    uint64_t getTrafficInstanceId() const {
        return this->trafficInstanceId;
    }

    void setSenderHostAddress(const std::string &senderHostAddress) {
        this->senderHostAddress = senderHostAddress;
    }
    const std::string &getSenderHostAddress() const {
        return this->senderHostAddress;
    }

    void setRecverHostAddress(const std::string &recverHostAddress) {
        this->recverHostAddress = recverHostAddress;
    }
    const std::string &getRecverHostAddress() const {
        return this->recverHostAddress;
    }

    void setServerHostPort(int serverHostPort) {
        this->serverHostPort = serverHostPort;
    }
    int getServerHostPort() const {
        return this->serverHostPort;
    }

    void setProtocol(ProtocolType proto) {
        this->proto = proto;
    }
    ProtocolType getProtocol() const {
        return this->proto;
    }

    void setRole(RoleType role) {
        this->role = role;
    }
    RoleType getRole() const {
        return this->role;
    }

    void setWorkDuration(int64_t workDuration) {
        this->workDuration = workDuration;
    }
    int64_t getWorkDuration() const {
        return this->workDuration;
    }

    void setSendBufSize(size_t sendBufSize) {
        this->sendBufSize = sendBufSize;
    }
    size_t getSendBufSize() const {
        return this->sendBufSize;
    }

    void setReportInterval(int64_t reportInterval) {
        this->reportInterval = reportInterval;
    }
    int64_t getReportInterval() const {
        return this->reportInterval;
    }

    void setUpdateIntervel(int64_t updateInterval) {
        this->updateInterval = updateInterval;
    }
    int64_t getUpdateInterval() const {
        return this->updateInterval;
    }

    void setTcpNoDelay(bool tcpNoDelay) {
        this->tcpNoDelay = tcpNoDelay;
    }
    bool isTcpNoDelay() const {
        return this->tcpNoDelay;
    }

    void setTcpMss(int tcpMss) {
        this->tcpMss = tcpMss;
    }
    int getTcpMss() const {
        return this->tcpMss;
    }

    void setTrafficModel(TrafficModelType trafficModel) {
        this->trafficModel = trafficModel;
    }
    TrafficModelType getTrafficModel() const {
        return this->trafficModel;
    }

    void setStableTrafficBandwidth(uint64_t stableTrafficBandwidth) {
        this->stableTrafficBandwidth = stableTrafficBandwidth;
    }
    uint64_t getStableTrafficBandwidth() const {
        return this->stableTrafficBandwidth;
    }

    void setRectSupremumTrafficBandwidth(uint64_t rectSupremumTrafficBandwidth) {
        this->rectSupremumTrafficBandwidth = rectSupremumTrafficBandwidth;
    }
    uint64_t getRectSupremumTrafficBandwidth() const {
        return this->rectSupremumTrafficBandwidth;
    }

    void setRectInfimumTrafficBandwidth(uint64_t rectInfimumTrafficBandwidth) {
        this->rectInfimumTrafficBandwidth = rectInfimumTrafficBandwidth;
    }
    uint64_t getRectInfimumTrafficBandwidth() const {
        return this->rectInfimumTrafficBandwidth;
    }

    void setRectSupreProportion(double rectSupreProportion) {
        this->rectSupreProportion = rectSupreProportion;
    }
    double getRectSupreProportion() const {
        return this->rectSupreProportion;
    }

    void setPoissonBurstTrafficBandwidth(uint64_t poissonBurstTrafficBandwidth) {
        this->poissonBurstTrafficBandwidth = poissonBurstTrafficBandwidth;
    }
    uint64_t getPoissonBurstTrafficBandwidth() const {
        return this->poissonBurstTrafficBandwidth;
    }

private:
    uint64_t trafficInstanceId;

    std::string senderHostAddress;
    std::string recverHostAddress;

    int serverHostPort;

    RoleType  role;
    ProtocolType proto;

    // Time unit: us
    int64_t workDuration; // -1 for forever, non-negative for specific duration
    int64_t reportInterval;
    int64_t updateInterval;  // Traffic sending-rate update interval

    size_t sendBufSize; // Sender buffer size

    // Socket Flags: TCP_NODELAY && TCP_MAXSEG
    bool tcpNoDelay; // false not set, true set
    int tcpMss;  // -1 for default

    // Bandwidth Unit = BytePerSecond(BPS)
    TrafficModelType trafficModel;

    // Stable Traffic Model
    uint64_t stableTrafficBandwidth;

    // Rectangle Traffic Model
    uint64_t rectSupremumTrafficBandwidth;
    uint64_t rectInfimumTrafficBandwidth;
    double rectSupreProportion;

    // Poisson Traffic Model
    uint64_t poissonBurstTrafficBandwidth;
};


#endif //TRAFFICER_TRAFFICINSTANCECONFIG_H
