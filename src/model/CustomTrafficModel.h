//
// Created by zjl on 12/27/16.
//

#ifndef TRAFFICER_CUSTOMTRAFFICMODEL_H
#define TRAFFICER_CUSTOMTRAFFICMODEL_H


#include <string>
#include "AbstractTrafficModel.h"

class CustomTrafficModel : public AbstractTrafficModel {
public:
    CustomTrafficModel();
    CustomTrafficModel(const char *filename);

    virtual uint64_t getNextTrafficBandwidth();

private:
    std::string customTrafficConfigFileName;
};


#endif //TRAFFICER_CUSTOMTRAFFICMODEL_H
