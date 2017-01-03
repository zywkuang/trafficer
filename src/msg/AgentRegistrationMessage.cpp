/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include "AgentRegistrationMessage.h"
#include "../base/Json.h"
#include "../base/Exception.h"
#include "../base/TimeStamp.h"
#include "../AgentDataStore.h"

AgentRegistrationMessage::AgentRegistrationMessage()
        : Message(AgentDataStore::agentHostUUID, AGENT_REGISTERATION),
          hostName("placeholder"),
          hostAddress("0.0.0.0"),
          hostSysinfo("Linux-x64"),
          tcpTrafficerPort(TRAFFICER_TCP_SERVER_PORT),
          udpTrafficerPort(TRAFFICER_UDP_SERVER_PORT) {

}

AgentRegistrationMessage::~AgentRegistrationMessage() {

}

void AgentRegistrationMessage::readFromJsonString(std::string &jsonstr) {
    JsonObject *json = cJsonParse(jsonstr.c_str());

    JsonObject *pj;

    if ((pj = cJsonGetObjectItem(json, "MsgID")) != NULL)
        this->msgId = static_cast<uint64_t >(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TimeStamp")) != NULL)
        this->msgTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "HostAgentID")) != NULL)
        this->hostId = static_cast<uint64_t>(pj->valueInt);

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
        cJsonAddIntToObject(json, "HostAgentID", this->hostId);
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
