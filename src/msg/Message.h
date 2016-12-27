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
    Message(MESSAGE_TYPE type);
    virtual ~Message();

    const uint64_t getMessageId() const;
    const MESSAGE_TYPE getMessageType() const;
    const std::string getMessageTimeStamp() const;

    virtual void readFromJsonString(std::string &jsonstr) = 0;
    virtual std::string writeToJsonString() const = 0;

protected:
    uint64_t msgId;
    MESSAGE_TYPE msgType;
    std::string msgTimeStamp;
};


#endif //TRAFFICER_MESSAGE_H
