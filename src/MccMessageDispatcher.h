/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_MCCMESSAGEDISPATCHER_H
#define TRAFFICER_MCCMESSAGEDISPATCHER_H

#include "base/Thread.h"

class MccMessageDispatcher : public Thread {
public:
    MccMessageDispatcher();
    virtual ~MccMessageDispatcher();

};


#endif //TRAFFICER_MCCMESSAGEDISPATCHER_H
