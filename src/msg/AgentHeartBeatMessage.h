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
    ~AgentHeartBeatMessage();

    void setHeartBeatContent(std::string &hbcontent) {
        this->heartBeatContent = hbcontent;
    }
    const std::string &getHeartBeatContent() const {
        return this->heartBeatContent;
    }

    virtual void readFromJsonString(std::string &jsonstr);
    virtual std::string writeToJsonString() const;

private:
    std::string heartBeatContent;
};


#endif //TRAFFICER_AGENTHEARTBEATMESSAGE_H
