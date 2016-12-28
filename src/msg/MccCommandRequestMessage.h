/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#ifndef TRAFFICER_MCCCOMMANDMESSAGE_H
#define TRAFFICER_MCCCOMMANDMESSAGE_H

#include "Message.h"
#include "../TrafficInstanceConfig.h"

class MccCommandRequestMessage : public Message {
public:
    MccCommandRequestMessage(uint64_t id);
    ~MccCommandRequestMessage();

    void setHostMccId(uint64_t id);
    uint64_t getHostMccId() const;

    void setCmdType(CommandType commandType);
    CommandType getCmdType() const;

    void setTrafficInstanceId(uint64_t trafficInstanceId);
    uint64_t getTrafficInstanceId() const;

    void setTrafficInstanceConfig(TrafficInstanceConfig &tic);
    const TrafficInstanceConfig &getTrafficInstanceConfig() const;

    void readFromJsonString(std::string &jsonstr);
    std::string writeToJsonString() const;

private:
    uint64_t hostMccId; // mcc uuid
    uint64_t trafficInstanceId; // target traffic instance
    CommandType cmdType;

    TrafficInstanceConfig trafficInstanceConfig;
};


#endif //TRAFFICER_MCCCOMMANDMESSAGE_H
