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

    void setHostName(std::string hostname);
    std::string getHostName() const;

    void setHostAddress(std::string hostaddress);
    std::string getHostAddress() const;

    void setHeartBeatContent(std::string hbcontent);
    std::string getHeartBeatContent() const;

    virtual void readFromJsonString(std::string jsonstr);
    virtual std::string writeToJsonString() const;

private:
    std::string hostName;
    std::string hostAddress;
    std::string heartBeatContent;
};


#endif //TRAFFICER_AGENTHEARTBEATMESSAGE_H
