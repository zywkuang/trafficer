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

    void setTrafficInstanceId(uint64_t trafficInstanceId);
    uint64_t getTrafficInstanceId() const;

    void setCmdType(CommandType cmdType);
    CommandType getCmdType() const;

    void setOpSuccess(bool opSuccess);
    bool isOpSuccess() const;

    void setOpResult(const std::string &opResult);
    const std::string &getOpResult() const;

    virtual void readFromJsonString(std::string &jsonstr);
    virtual std::string writeToJsonString() const;

private:
    uint64_t trafficInstanceId;
    CommandType cmdType;

    bool opSuccess;
    std::string opResult;
};


#endif //TRAFFICER_AGENTCOMMANDACKMESSAGE_H
