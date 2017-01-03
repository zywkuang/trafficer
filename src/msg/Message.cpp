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
      msgType(UNKNOWN_MESSAGE_TYPE) {

}

Message::Message(uint64_t hostId, MessageType type)
    : hostId(hostId),
      msgTimeStamp(TimeStamp::now().toFormattedString(false)),
      msgId(UtilSet::generateUUID()),
      msgType(type){

}

Message::~Message() {

}