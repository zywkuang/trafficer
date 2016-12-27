/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#ifndef TRAFFICER_ABSTRACTTRAFFICMODEL_H
#define TRAFFICER_ABSTRACTTRAFFICMODEL_H


#include <stdint.h>
#include "../Trafficer.h"

class AbstractTrafficModel {
public:
    AbstractTrafficModel();
    AbstractTrafficModel(TrafficModelType mt);
    virtual ~AbstractTrafficModel();

    virtual uint64_t getNextTrafficBandwidth() = 0;

protected:
    TrafficModelType modelType;
};


#endif //TRAFFICER_ABSTRACTTRAFFICMODEL_H
