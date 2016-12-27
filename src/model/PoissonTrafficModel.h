/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/27/16
**/

#ifndef TRAFFICER_POISSONTRAFFICMODEL_H
#define TRAFFICER_POISSONTRAFFICMODEL_H


#include "AbstractTrafficModel.h"

class PoissonTrafficModel : public AbstractTrafficModel {
public:
    PoissonTrafficModel();
    PoissonTrafficModel(uint64_t ptbw);
    ~PoissonTrafficModel();

    virtual uint64_t getNextTrafficBandwidth();

private:
    uint64_t poissonBurstTrafficBandwidth;
};


#endif //TRAFFICER_POISSONTRAFFICMODEL_H
