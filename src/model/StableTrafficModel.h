//
// Created by zjl on 12/27/16.
//

#ifndef TRAFFICER_STABLETRAFFICMODEL_H
#define TRAFFICER_STABLETRAFFICMODEL_H

#include "AbstractTrafficModel.h"

class StableTrafficModel : public AbstractTrafficModel {
public:
    StableTrafficModel();
    StableTrafficModel(uint64_t stbw);
    ~StableTrafficModel();

    virtual uint64_t getNextTrafficBandwidth();

private:
    uint64_t stableTrafficBandwidth;
};


#endif //TRAFFICER_STABLETRAFFICMODEL_H
