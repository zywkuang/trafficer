/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include "AgentHeartBeatMessage.h"
#include "../base/Json.h"
#include "../base/Exception.h"

AgentHeartBeatMessage::AgentHeartBeatMessage()
    : Message(AGENT_HEART_BEAT),
      hostName("placeholder"),
      hostAddress("0.0.0.0"),
      heartBeatContent("HEART_BEAT"){

}

AgentHeartBeatMessage::~AgentHeartBeatMessage() {

}

void AgentHeartBeatMessage::setHostName(std::string &hostname) {
    this->hostName = hostname;
}

const std::string &AgentHeartBeatMessage::getHostName() const {
    return this->hostName;
}

void AgentHeartBeatMessage::setHostAddress(std::string &hostaddress) {
    this->hostAddress = hostaddress;
}

const std::string &AgentHeartBeatMessage::getHostAddress() const {
    return this->hostAddress;
}

void AgentHeartBeatMessage::setHeartBeatContent(std::string &hbcontent) {
    this->heartBeatContent = hbcontent;
}

const std::string &AgentHeartBeatMessage::getHeartBeatContent() const {
    return this->heartBeatContent;
}

void AgentHeartBeatMessage::readFromJsonString(std::string &jsonstr) {
    JsonObject *json = cJsonParse(jsonstr.c_str());

    JsonObject *pj;

    if ((pj = cJsonGetObjectItem(json, "MsgID")) != NULL)
        this->msgId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TimeStamp")) != NULL)
        this->msgTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "HostName")) != NULL)
        this->hostName = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "HostAddress")) != NULL)
        this->hostAddress = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "HeartBeatContent")) != NULL)
        this->heartBeatContent = pj->valueString;

    cJsonDelete(json);
}

std::string AgentHeartBeatMessage::writeToJsonString() const {
    JsonObject *json = cJsonCreateObject();

    if (json == NULL) {
        throw Exception(ENULLPOINTER, "Null Pointer Exception");
    } else {
        cJsonAddIntToObject(json, "MsgID", this->msgId);
        cJsonAddIntToObject(json, "MsgType", this->msgType);
        cJsonAddStringToObject(json, "TimeStamp", this->msgTimeStamp.c_str());
        cJsonAddStringToObject(json, "HostName", this->hostName.c_str());
        cJsonAddStringToObject(json, "HostAddress", this->hostAddress.c_str());
        cJsonAddStringToObject(json, "HeartBeatContent", this->heartBeatContent.c_str());
    }

    std::string jsonStr = cJsonPrintUnformatted(json);
    cJsonDelete(json);

    return jsonStr;
}