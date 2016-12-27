/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/27/16
**/

#include <cstdlib>
#include "RectangleTrafficModel.h"
#include "../base/UtilSet.h"

RectangleTrafficModel::RectangleTrafficModel()
        : supremumTrafficBandwidth(0),
          infimumTrafficBandwidth(0),
          supreProportion(0){

}

RectangleTrafficModel::RectangleTrafficModel(uint64_t stb, uint64_t itb)
        : supremumTrafficBandwidth(stb),
          infimumTrafficBandwidth(itb),
          supreProportion(0.5){

}

RectangleTrafficModel::RectangleTrafficModel(uint64_t stb, uint64_t itb, double sp)
        : supremumTrafficBandwidth(stb),
          infimumTrafficBandwidth(itb),
          supreProportion(sp){

}

RectangleTrafficModel::~RectangleTrafficModel() {

}

uint64_t RectangleTrafficModel::getNextTrafficBandwidth() {

    int limit = static_cast<int>(this->supreProportion * 10000);
    int val = Random(10000);

    if (val < limit)
        return this->supremumTrafficBandwidth;

    return this->infimumTrafficBandwidth;
}