/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_MCCCOMMANDCONSOLE_H
#define TRAFFICER_MCCCOMMANDCONSOLE_H


#include "base/Thread.h"

class MccCommandConsole : public Thread {
public:
    MccCommandConsole();
    virtual ~MccCommandConsole();

};


#endif //TRAFFICER_MCCCOMMANDCONSOLE_H
