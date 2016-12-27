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

class TrafficInstanceConfig {
public:
    TrafficInstanceConfig();
    ~TrafficInstanceConfig();

    void setSenderHostAddress(const std::string &senderHostAddress);
    const std::string &getSenderHostAddress() const;

    void setRecverHostAddress(const std::string &recverHostAddress);
    const std::string &getRecverHostAddress() const;

    void setServerHostPort(int serverHostPort);
    int getServerHostPort() const;

    void setProtocol(ProtocolType proto);
    ProtocolType getProtocol() const;

    void setRole(RoleType role);
    RoleType getRole() const;

    void setWorkDuration(int workDuration);
    int getWorkDuration() const;

    void setReportInterval(int reportInterval);
    int getReportInterval() const;

    void setSendBufSize(int sendBufSize);
    int getSendBufSize() const;

    void setUpdateIntervel(int updateIntervel);
    int getUpdateIntervel() const;

    void setTcpNoDelay(bool tcpNoDelay);
    bool isTcpNoDelay() const;

    void setTcpMss(int tcpMss);
    int getTcpMss() const;

    void setTrafficModel(TrafficModelType trafficModel);
    TrafficModelType getTrafficModel() const;

    void setStableTrafficBandwidth(uint64_t stableTrafficBandwidth);
    uint64_t getStableTrafficBandwidth() const;

    void setRectSupremumTrafficBandwidth(uint64_t rectSupremumTrafficBandwidth);
    uint64_t getRectSupremumTrafficBandwidth() const;

    void setRectInfimumTrafficBandwidth(uint64_t rectInfimumTrafficBandwidth);
    uint64_t getRectInfimumTrafficBandwidth() const;

    void setRectSupreProportion(double rectSupreProportion);
    double getRectSupreProportion() const;

    void setPoissonBurstTrafficBandwidth(uint64_t poissonBurstTrafficBandwidth);
    uint64_t getPoissonBurstTrafficBandwidth() const;

private:
    std::string senderHostAddress;
    std::string recverHostAddress;

    int serverHostPort;

    RoleType  role;
    ProtocolType proto;

    // Time unit: ms
    int workDuration; // -1 for forever, non-negative for specific duration
    int reportInterval;
    int updateIntervel;  // Traffic sending-rate update interval

    int sendBufSize; // Sender buffer size

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
