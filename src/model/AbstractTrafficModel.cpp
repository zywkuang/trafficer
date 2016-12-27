/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include "AbstractTrafficModel.h"

AbstractTrafficModel::AbstractTrafficModel()
        : modelType(UNKNOWN_TRAFFIC_MODEL){

}

AbstractTrafficModel::AbstractTrafficModel(TrafficModelType mt)
        : modelType(mt){

}

AbstractTrafficModel::~AbstractTrafficModel() {

}