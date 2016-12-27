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

    void setSenderHostPort(int senderHostPort);
    int getSenderHostPort() const;

    void setRecverHostAddress(const std::string &recverHostAddress);
    const std::string &getRecverHostAddress() const;

    void setRecverHostPort(int recverHostPort);
    int getRecverHostPort() const;

    void setProto(PROTOCOL proto);
    PROTOCOL getProto() const;

    void setRole(ROLE role);
    ROLE getRole() const;

    void setWorkDuration(int workDuration);
    int getWorkDuration() const;

    void setReportInterval(int reportInterval);
    int getReportInterval() const;

    void setTcpNoDelay(bool tcpNoDelay);
    bool isTcpNoDelay() const;

    void setTcpMss(int tcpMss);
    int getTcpMss() const;

    void setTrafficModel(TRAFFIC_MODEL trafficModel);
    TRAFFIC_MODEL getTrafficModel() const;

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
    int senderHostPort;

    std::string recverHostAddress;
    int recverHostPort;

    PROTOCOL proto;
    ROLE  role;
    // -1 forever, non-negative for specific duration
    int workDuration;
    int reportInterval;

    // Socket Flags: TCP_NODELAY && TCP_MAXSEG
    bool tcpNoDelay;
    int tcpMss;

    // Bandwidth Unit = BytePerSecond(BPS)
    TRAFFIC_MODEL trafficModel;

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
