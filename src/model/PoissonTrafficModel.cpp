/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/27/16
**/

#include <cstdlib>
#include "PoissonTrafficModel.h"
#include "../base/UtilSet.h"

PoissonTrafficModel::PoissonTrafficModel()
        : poissonBurstTrafficBandwidth(0) {

}

PoissonTrafficModel::PoissonTrafficModel(uint64_t ptbw)
        : poissonBurstTrafficBandwidth(ptbw){

}

PoissonTrafficModel::~PoissonTrafficModel() {

}

uint64_t PoissonTrafficModel::getNextTrafficBandwidth() {

    int val = Random(10000);
    double pt = static_cast<double>(val) / 10000;

    return static_cast<uint64_t>(pt * this->poissonBurstTrafficBandwidth);
}