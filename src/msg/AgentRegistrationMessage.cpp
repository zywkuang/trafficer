/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include "AgentRegistrationMessage.h"
#include "../base/Json.h"
#include "../base/Exception.h"
#include "../base/TimeStamp.h"

AgentRegistrationMessage::AgentRegistrationMessage()
        : Message(AGENT_REGISTERATION),
          hostAgentId(0),
          hostName("placeholder"),
          hostAddress("0.0.0.0"),
          hostSysinfo("Linux-x64"),
          tcpTrafficerPort(TRAFFICER_TCP_SERVER_PORT),
          udpTrafficerPort(TRAFFICER_UDP_SERVER_PORT) {

}

AgentRegistrationMessage::AgentRegistrationMessage(uint64_t agentId)
     : Message(AGENT_REGISTERATION),
       hostAgentId(agentId),
       hostName("placeholder"),
       hostAddress("0.0.0.0"),
       hostSysinfo("Linux-x64"),
       tcpTrafficerPort(TRAFFICER_TCP_SERVER_PORT),
       udpTrafficerPort(TRAFFICER_UDP_SERVER_PORT) {

}

AgentRegistrationMessage::~AgentRegistrationMessage() {

}

void AgentRegistrationMessage::setHostAgentId(uint64_t id) {
    this->hostAgentId = id;
}

uint64_t AgentRegistrationMessage::getHostAgentId() const {
    return this->hostAgentId;
}

void AgentRegistrationMessage::setHostName(std::string &hostname) {
    this->hostName = hostname;
}

const std::string &AgentRegistrationMessage::getHostName() const {
    return this->hostName;
}

void AgentRegistrationMessage::setHostAddress(std::string &hostaddress) {
    this->hostAddress = hostaddress;
}

const std::string &AgentRegistrationMessage::getHostAddress() const {
    return this->hostAddress;
}

void AgentRegistrationMessage::setHostSysinfo(std::string &hostsysinfo) {
    this->hostSysinfo = hostsysinfo;
}

const std::string &AgentRegistrationMessage::getHostSysinfo() const {
    return this->hostSysinfo;
}

void AgentRegistrationMessage::setTcpTrafficerPort(int port) {
    this->tcpTrafficerPort = port;
}

int AgentRegistrationMessage::getTcpTrafficerPort() const {
    return this->tcpTrafficerPort;
}

void AgentRegistrationMessage::setUdpTrafficerPort(int port) {
    this->udpTrafficerPort = port;
}

int AgentRegistrationMessage::getUdpTrafficerPort() const {
    return this->udpTrafficerPort;
}

void AgentRegistrationMessage::readFromJsonString(std::string &jsonstr) {
    JsonObject *json = cJsonParse(jsonstr.c_str());

    JsonObject *pj;

    if ((pj = cJsonGetObjectItem(json, "MsgID")) != NULL)
        this->msgId = static_cast<uint64_t >(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TimeStamp")) != NULL)
        this->msgTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "HostName")) != NULL)
        this->hostName = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "HostAddress")) != NULL)
        this->hostAddress = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "HostSysinfo")) != NULL)
        this->hostSysinfo = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "TCPTrafficerPort")) != NULL)
        this->tcpTrafficerPort = static_cast<int>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "UDPTrafficerPort")) != NULL)
        this->udpTrafficerPort = static_cast<int>(pj->valueInt);

    cJsonDelete(json);
}

std::string AgentRegistrationMessage::writeToJsonString() const {
    JsonObject *json = cJsonCreateObject();

    if (json == NULL) {
        throw Exception(ENULLPOINTER, "Null Pointer Exception");
    } else {
        cJsonAddIntToObject(json, "MsgID", this->msgId);
        cJsonAddIntToObject(json, "MsgType", AGENT_REGISTERATION);
        cJsonAddStringToObject(json, "TimeStamp", this->msgTimeStamp.c_str());
        cJsonAddStringToObject(json, "HostName", this->hostName.c_str());
        cJsonAddStringToObject(json, "HostAddress", this->hostAddress.c_str());
        cJsonAddStringToObject(json, "HostSysinfo", this->hostSysinfo.c_str());
        cJsonAddIntToObject(json, "TCPTrafficerPort", this->tcpTrafficerPort);
        cJsonAddIntToObject(json, "UDPTrafficerPort", this->udpTrafficerPort);
    }

    std::string jsonStr = cJsonPrintUnformatted(json);
    cJsonDelete(json);

    return jsonStr;
}
