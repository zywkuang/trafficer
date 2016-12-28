/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include "AgentCommandResponseMessage.h"
#include "../base/Json.h"
#include "../base/Exception.h"

AgentCommandResponseMessage::AgentCommandResponseMessage(uint64_t id)
        : Message(AGENT_COMMAND_RESPONSE),
          hostAgentId(id),
          opSuccess(false) {

}

AgentCommandResponseMessage::~AgentCommandResponseMessage() {

}

void AgentCommandResponseMessage::setHostAgentId(uint64_t id) {
    this->hostAgentId = id;
}

uint64_t AgentCommandResponseMessage::getHostAgentId() const {
    return this->hostAgentId;
}

uint64_t AgentCommandResponseMessage::getTrafficInstanceId() const {
    return this->trafficInstanceId;
}

void AgentCommandResponseMessage::setTrafficInstanceId(uint64_t trafficInstanceId) {
    this->trafficInstanceId = trafficInstanceId;
}

CommandType AgentCommandResponseMessage::getCmdType() const {
    return this->cmdType;
}

void AgentCommandResponseMessage::setCmdType(CommandType cmdType) {
    this->cmdType = cmdType;
}

bool AgentCommandResponseMessage::isOpSuccess() const {
    return this->opSuccess;
}

void AgentCommandResponseMessage::setOpSuccess(bool opSuccess) {
    this->opSuccess = opSuccess;
}

const std::string &AgentCommandResponseMessage::getOpResult() const {
    return this->opResult;
}

void AgentCommandResponseMessage::setOpResult(const std::string &opResult) {
    this->opResult = opResult;
}

void AgentCommandResponseMessage::readFromJsonString(std::string &jsonstr) {
    JsonObject *json = cJsonParse(jsonstr.c_str());

    JsonObject *pj;

    if ((pj = cJsonGetObjectItem(json, "MsgID")) != NULL)
        this->msgId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TimeStamp")) != NULL)
        this->msgTimeStamp = pj->valueString;

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
