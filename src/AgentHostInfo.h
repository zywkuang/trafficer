/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTHOSTINFO_H
#define TRAFFICER_AGENTHOSTINFO_H

#include <stdint.h>
#include <string>
#include "base/Copyable.h"

class AgentHostInfo : public Copyable {
public:
    AgentHostInfo();
    ~AgentHostInfo();

    void setHostAgentId(uint64_t id);
    uint64_t getHostAgentId() const;

    void setHostName(std::string &hostname);
    const std::string &getHostName() const;

    void setHostAddress(std::string &hostAddress);
    const std::string &getHostAddress() const;

    void setHostSysinfo(std::string &hostSysinfo);
    const std::string &getHostSysinfo() const;

    void setTcpTrafficerPort(int port);
    int getTcpTrafficerPort() const;

    void setUdpTrafficerPort(int port);
    int getUdpTrafficerPort() const;

private:
    uint64_t hostAgentId;
    std::string hostName;
    std::string hostAddress;
    std::string hostSysinfo;
    int tcpTrafficerPort;
    int udpTrafficerPort;
};


#endif //TRAFFICER_AGENTHOSTINFO_H
