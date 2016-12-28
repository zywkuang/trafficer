/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include "AgentHeartBeatMessage.h"
#include "../base/Json.h"
#include "../base/Exception.h"

AgentHeartBeatMessage::AgentHeartBeatMessage(uint64_t id)
        : Message(AGENT_HEART_BEAT),
          hostAgentId(id),
          heartBeatContent("HEART_BEAT") {

}

AgentHeartBeatMessage::~AgentHeartBeatMessage() {

}

void AgentHeartBeatMessage::setHostAgentId(uint64_t agentId) {
    this->hostAgentId = agentId;
}

uint64_t AgentHeartBeatMessage::getHostAgentId() const {
    return this->hostAgentId;
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

    if ((pj = cJsonGetObjectItem(json, "HostAgentID")) != NULL)
        this->hostAgentId = static_cast<uint64_t>(pj->valueInt);

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
        cJsonAddIntToObject(json, "HostAgentID", this->hostAgentId);
        cJsonAddStringToObject(json, "HeartBeatContent", this->heartBeatContent.c_str());
    }

    std::string jsonStr = cJsonPrintUnformatted(json);
    cJsonDelete(json);

    return jsonStr;
}