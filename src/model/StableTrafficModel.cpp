/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/27/16
**/

#include "StableTrafficModel.h"

StableTrafficModel::StableTrafficModel()
        : stableTrafficBandwidth(0) {

}

StableTrafficModel::StableTrafficModel(uint64_t stbw) : stableTrafficBandwidth(stbw) {

}

StableTrafficModel::~StableTrafficModel() {

}

uint64_t StableTrafficModel::getNextTrafficBandwidth() {
    return this->stableTrafficBandwidth;
}