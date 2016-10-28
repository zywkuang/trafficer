//
// Created by zjl on 10/28/16.
//

#ifndef TRAFFICER_NONCOPYABLE_H
#define TRAFFICER_NONCOPYABLE_H

class NonCopyable {
protected:
    NonCopyable() { }

private:
    NonCopyable(const NonCopyable &) = delete;
    void operator = (const NonCopyable &) = delete;
};


#endif //TRAFFICER_NONCOPYABLE_H
