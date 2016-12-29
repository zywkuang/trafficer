/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#ifndef TRAFFICER_AGENTHEARTBEATMESSAGE_H
#define TRAFFICER_AGENTHEARTBEATMESSAGE_H

#include <string>
#include "Message.h"

class AgentHeartBeatMessage : public Message {
public:
    AgentHeartBeatMessage();
    AgentHeartBeatMessage(uint64_t agentId);
    ~AgentHeartBeatMessage();

    void setHostAgentId(uint64_t agentId);
    uint64_t getHostAgentId() const;

    void setHeartBeatContent(std::string &hbcontent);
    const std::string &getHeartBeatContent() const;

    virtual void readFromJsonString(std::string &jsonstr);
    virtual std::string writeToJsonString() const;

private:
    uint64_t hostAgentId;
    std::string heartBeatContent;
};


#endif //TRAFFICER_AGENTHEARTBEATMESSAGE_H
