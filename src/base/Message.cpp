//
// Created by zjl on 10/28/16.
//

#include "Message.h"

Message::Message(unsigned long msgId)
    : msgId(msgId){

}

Message::~Message() {

}

const unsigned long Message::getMessageId() {
    return this->msgId;
}