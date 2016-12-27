/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#ifndef TRAFFICER_AGENTTRAFFICREPORTMESSAGE_H
#define TRAFFICER_AGENTTRAFFICREPORTMESSAGE_H

#include "Message.h"

class AgentTrafficReportMessage : public Message {
public:
    AgentTrafficReportMessage();
    ~AgentTrafficReportMessage();

    void setTrafficInstanceId(uint64_t tiid);
    uint64_t getTrafficInstanceId() const;

    void setRole(RoleType r);
    RoleType getRole() const;

    void setProtocol(ProtocolType p);
    ProtocolType getProtocol() const;

    void setBeginTimeStamp(std::string &beginTimeStamp);
    const std::string &getBeginTimeStamp() const;

    void setEndTimeStamp(std::string &endTimeStamp);
    const std::string &getEndTimeStamp() const;

    void setBytesTransferred(uint64_t bytes);
    uint64_t getBytesTransferred() const;

    void setTrafficInterval(double interval);
    double getTrafficInterval() const;

    void setTrafficBandwidth(double bandwidth);
    double getTrafficBandwidth() const;

    void setTrafficJitter(double jitter);
    double getTrafficJitter() const;

    void setPacketLostCnt(uint64_t lostCnt);
    uint64_t  getPacketLostCnt() const;

    void setPacketTotalCnt(uint64_t totalCnt);
    uint64_t  getPacketTotalCnt() const;

    void setPacketLoss(double loss);
    double getPacketLoss() const;

    virtual void readFromJsonString(std::string &jsonstr);
    virtual std::string writeToJsonString() const;

private:
    uint64_t trafficInstanceId;
    RoleType role;
    ProtocolType proto;
    std::string beginTimeStamp;
    std::string endTimeStamp;
    uint64_t bytesTransferred;
    double trafficInterval;
    double trafficBandwidth;
    double trafficJitter;
    uint64_t packetLostCnt;
    uint64_t packetTotalCnt;
    double packetLoss;
};


#endif //TRAFFICER_AGENTTRAFFICREPORTMESSAGE_H
