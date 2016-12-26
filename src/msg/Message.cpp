/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#include "Message.h"
#include "../base/UtilSet.h"
#include "../base/TimeStamp.h"

Message::Message()
    : msgTimeStamp(TimeStamp::now().toFormattedString(false)),
      msgId(UtilSet::generateUUID()),
      msgType(UNKNOWN) {

}

Message::Message(MESSAGE_TYPE type)
    : msgTimeStamp(TimeStamp::now().toFormattedString(false)),
      msgId(UtilSet::generateUUID()),
      msgType(type){

}

Message::~Message() {

}

const uint64_t Message::getMessageId() const {
    return this->msgId;
}

const MESSAGE_TYPE Message::getMessageType() const {
    return this->msgType;
}

const std::string Message::getMessageTimeStamp() const {
    return this->msgTimeStamp;
}