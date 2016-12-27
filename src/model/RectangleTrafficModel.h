/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/27/16
**/

#ifndef TRAFFICER_RECTANGLETRAFFICMODEL_H
#define TRAFFICER_RECTANGLETRAFFICMODEL_H


#include <cstdint>
#include "AbstractTrafficModel.h"

class RectangleTrafficModel : public AbstractTrafficModel {
public:
    RectangleTrafficModel();
    RectangleTrafficModel(uint64_t stb, uint64_t itb);
    RectangleTrafficModel(uint64_t stb, uint64_t itb, double sp);
    ~RectangleTrafficModel();

    virtual uint64_t getNextTrafficBandwidth();

private:
    uint64_t supremumTrafficBandwidth;
    uint64_t infimumTrafficBandwidth;
    double supreProportion;
};


#endif //TRAFFICER_RECTANGLETRAFFICMODEL_H
