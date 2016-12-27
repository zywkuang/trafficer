//
// Created by zjl on 12/27/16.
//

#include "CustomTrafficModel.h"

CustomTrafficModel::CustomTrafficModel() {

}

CustomTrafficModel::CustomTrafficModel(const char *filename)
        : customTrafficConfigFileName(filename){

}

uint64_t CustomTrafficModel::getNextTrafficBandwidth() {
    //......

    return 0;
}