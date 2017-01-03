/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include "AgentHeartBeatMessage.h"
#include "../base/Json.h"
#include "../base/Exception.h"
#include "../AgentDataStore.h"

AgentHeartBeatMessage::AgentHeartBeatMessage()
        : Message(AgentDataStore::agentHostUUID, AGENT_HEART_BEAT),
          heartBeatContent("HEART_BEAT") {

}

AgentHeartBeatMessage::~AgentHeartBeatMessage() {

}

void AgentHeartBeatMessage::readFromJsonString(std::string &jsonstr) {
    JsonObject *json = cJsonParse(jsonstr.c_str());

    JsonObject *pj;

    if ((pj = cJsonGetObjectItem(json, "MsgID")) != NULL)
        this->msgId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TimeStamp")) != NULL)
        this->msgTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "HostAgentID")) != NULL)
        this->hostId = static_cast<uint64_t>(pj->valueInt);

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
        cJsonAddIntToObject(json, "HostAgentID", this->hostId);
        cJsonAddStringToObject(json, "HeartBeatContent", this->heartBeatContent.c_str());
    }

    std::string jsonStr = cJsonPrintUnformatted(json);
    cJsonDelete(json);

    return jsonStr;
}