/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#ifndef TRAFFICER_MESSAGE_H
#define TRAFFICER_MESSAGE_H

#include <stdint.h>
#include <string>
#include "../base/NonCopyable.h"
#include "../Trafficer.h"

class Message : public NonCopyable{
public:
    Message();
    Message(uint64_t hostId, MessageType type);
    virtual ~Message();

    const uint64_t getHostId() const {
        return this->hostId;
    }

    const uint64_t getMessageId() const {
        return this->msgId;
    }

    const MessageType getMessageType() const {
        return this->msgType;
    }

    const std::string getMessageTimeStamp() const {
        return this->msgTimeStamp;
    }

    virtual void readFromJsonString(std::string &jsonstr) = 0;
    virtual std::string writeToJsonString() const = 0;

protected:
    uint64_t hostId;
    uint64_t msgId;
    MessageType msgType;
    std::string msgTimeStamp;
};


#endif //TRAFFICER_MESSAGE_H
