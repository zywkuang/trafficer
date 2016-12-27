/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#ifndef TRAFFICER_AGENTREGISTERMESSAGE_H
#define TRAFFICER_AGENTREGISTERMESSAGE_H


#include <string>
#include "Message.h"
#include "../base/Json.h"

class AgentRegistrationMessage : public Message {
public:
    AgentRegistrationMessage();
    ~AgentRegistrationMessage();

    // Optimize: change std::string to const std::string&
    void setHostName(std::string &hostname);
    const std::string getHostName() const;

    void setHostAddress(std::string &hostaddress);
    const std::string getHostAddress() const;

    void setHostSysinfo(std::string &hostsysinfo);
    const std::string getHostSysinfo() const;

    void setTcpTrafficerPort(int port);
    int getTcpTrafficerPort() const;

    void setUdpTrafficerPort(int port);
    int getUdpTrafficerPort() const;

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
