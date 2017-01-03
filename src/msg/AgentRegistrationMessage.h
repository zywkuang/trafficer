/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#ifndef TRAFFICER_AGENTREGISTERMESSAGE_H
#define TRAFFICER_AGENTREGISTERMESSAGE_H

#include <string>
#include "Message.h"

class AgentRegistrationMessage : public Message {
public:
    AgentRegistrationMessage();
    ~AgentRegistrationMessage();

    void setHostName(std::string &hostname) {
        this->hostName = hostname;
    }
    const std::string &getHostName() const {
        return this->hostName;
    }

    void setHostAddress(std::string &hostaddress) {
        this->hostAddress = hostaddress;
    }
    const std::string &getHostAddress() const {
        return this->hostAddress;
    }

    void setHostSysinfo(std::string &hostsysinfo) {
        this->hostSysinfo = hostsysinfo;
    }
    const std::string &getHostSysinfo() const {
        return this->hostSysinfo;
    }

    void setTcpTrafficerPort(int port) {
        this->tcpTrafficerPort = port;
    }
    int getTcpTrafficerPort() const {
        return this->tcpTrafficerPort;
    }

    void setUdpTrafficerPort(int port) {
        this->udpTrafficerPort = port;
    }
    int getUdpTrafficerPort() const {
        return this->udpTrafficerPort;
    }

    virtual void readFromJsonString(std::string &jsonstr);
    virtual std::string writeToJsonString() const;

private:
    std::string hostName;
    std::string hostAddress;
    std::string hostSysinfo;
    int tcpTrafficerPort;
    int udpTrafficerPort;
};


#endif //TRAFFICER_AGENTREGISTERMESSAGE_H
