/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include "AgentCommandResponseMessage.h"
#include "../base/Json.h"
#include "../base/Exception.h"
#include "../AgentDataStore.h"

AgentCommandResponseMessage::AgentCommandResponseMessage()
        : Message(AgentDataStore::agentHostUUID, AGENT_COMMAND_RESPONSE),
          opSuccess(false) {

}

AgentCommandResponseMessage::~AgentCommandResponseMessage() {

}

void AgentCommandResponseMessage::readFromJsonString(std::string &jsonstr) {
    JsonObject *json = cJsonParse(jsonstr.c_str());

    JsonObject *pj;

    if ((pj = cJsonGetObjectItem(json, "MsgID")) != NULL)
        this->msgId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TimeStamp")) != NULL)
        this->msgTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "HostAgentID")) != NULL)
        this->hostId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TrafficInstanceID")) != NULL)
        this->trafficInstanceId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "CommandType")) != NULL)
        this->cmdType = static_cast<CommandType>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "OperationSuccess")) != NULL) {
        if (1 == pj->valueInt)
            this->opSuccess = true;
        else
            this->opSuccess = false;
    }

    if ((pj = cJsonGetObjectItem(json, "OperationResult")) != NULL)
        this->opResult = pj->valueString;

    cJsonDelete(json);
}

std::string AgentCommandResponseMessage::writeToJsonString() const {
    JsonObject *json = cJsonCreateObject();

    if (json == NULL) {
        throw Exception(ENULLPOINTER, "Null Pointer Exception");
    } else {
        cJsonAddIntToObject(json, "MsgID", this->msgId);
        cJsonAddIntToObject(json, "MsgType", AGENT_COMMAND_RESPONSE);
        cJsonAddStringToObject(json, "TimeStamp", this->msgTimeStamp.c_str());
        cJsonAddIntToObject(json, "HostAgentID", this->hostId);
        cJsonAddIntToObject(json, "TrafficInstanceID", this->trafficInstanceId);
        cJsonAddIntToObject(json, "CommandType", this->cmdType);

        if (this->opSuccess)
            cJsonAddIntToObject(json, "OperationSuccess", 1);
        else
            cJsonAddIntToObject(json, "OperationSuccess", 0);

        cJsonAddStringToObject(json, "OperationResult", this->opResult.c_str());
    }

    std::string jsonStr = cJsonPrintUnformatted(json);
    cJsonDelete(json);

    return jsonStr;
}
