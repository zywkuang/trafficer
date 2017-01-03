/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#ifndef TRAFFICER_AGENTCOMMANDACKMESSAGE_H
#define TRAFFICER_AGENTCOMMANDACKMESSAGE_H

#include "Message.h"

class AgentCommandResponseMessage : public Message {
public:
    AgentCommandResponseMessage();
    ~AgentCommandResponseMessage();

    void setTrafficInstanceId(uint64_t trafficInstanceId) {
        this->trafficInstanceId = trafficInstanceId;
    }
    uint64_t getTrafficInstanceId() const {
        return this->trafficInstanceId;
    }

    void setCmdType(CommandType cmdType) {
        this->cmdType = cmdType;
    }
    CommandType getCmdType() const {
        return this->cmdType;
    }

    void setOpSuccess(bool opSuccess) {
        this->opSuccess = opSuccess;
    }
    bool isOpSuccess() const {
        return this->opSuccess;
    }

    void setOpResult(const std::string &opResult) {
        this->opResult = opResult;
    }
    const std::string &getOpResult() const {
        return this->opResult;
    }

    virtual void readFromJsonString(std::string &jsonstr);
    virtual std::string writeToJsonString() const;

private:
    uint64_t trafficInstanceId;
    CommandType cmdType;

    bool opSuccess;
    std::string opResult;
};


#endif //TRAFFICER_AGENTCOMMANDACKMESSAGE_H
