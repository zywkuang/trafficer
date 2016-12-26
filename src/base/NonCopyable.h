/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#ifndef TRAFFICER_NONCOPYABLE_H
#define TRAFFICER_NONCOPYABLE_H

class NonCopyable {
public:
    NonCopyable() {}
    virtual ~NonCopyable() {}

private:
    NonCopyable(const NonCopyable &);
    void operator = (const NonCopyable &);
};


#endif //TRAFFICER_NONCOPYABLE_H
