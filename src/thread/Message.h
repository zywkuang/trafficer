//
// Created by zjl on 10/28/16.
//

#ifndef TRAFFICER_MESSAGE_H
#define TRAFFICER_MESSAGE_H

#include "../base/NonCopyable.h"

class Message : public NonCopyable{
public:
    Message(unsigned long msgId);
    virtual ~Message();

    const unsigned long getMessageId();

private:
    unsigned long msgId;
};


#endif //TRAFFICER_MESSAGE_H
