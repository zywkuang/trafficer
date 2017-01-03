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

    void setTrafficInstanceId(uint64_t tiid) {
        this->trafficInstanceId = tiid;
    }
    uint64_t getTrafficInstanceId() const {
        return this->trafficInstanceId;
    }

    void setRole(RoleType r) {
        this->role = r;
    }
    RoleType getRole() const {
        return this->role;
    }

    void setProtocol(ProtocolType p) {
        this->proto = p;
    }
    ProtocolType getProtocol() const {
        return this->proto;
    }

    void setBeginTimeStamp(std::string &beginTimeStamp) {
        this->beginTimeStamp = beginTimeStamp;
    }
    const std::string &getBeginTimeStamp() const {
        return this->beginTimeStamp;
    }

    void setEndTimeStamp(std::string &endTimeStamp) {
        this->endTimeStamp = endTimeStamp;
    }
    const std::string &getEndTimeStamp() const {
        return this->endTimeStamp;
    }

    void setBytesTransferred(uint64_t bytes) {
        this->bytesTransferred = bytes;
    }
    uint64_t getBytesTransferred() const {
        return this->bytesTransferred;
    }

    void setTrafficInterval(int64_t interval) {
        this->trafficInterval = interval;
    }
    int64_t getTrafficInterval() const {
        return this->trafficInterval;
    }

    void setTrafficBandwidth(uint64_t bandwidth) {
        this->trafficBandwidth = bandwidth;
    }
    uint64_t getTrafficBandwidth() const {
        return this->trafficBandwidth;
    }

    void setTrafficJitter(double jitter) {
        this->trafficJitter = jitter;
    }
    double getTrafficJitter() const {
        return this->trafficJitter;
    }

    void setPacketLostCnt(uint64_t lostCnt) {
        this->packetLostCnt = lostCnt;
    }
    uint64_t  getPacketLostCnt() const {
        return this->packetLostCnt;
    }

    void setPacketTotalCnt(uint64_t totalCnt) {
        this->packetTotalCnt = totalCnt;
    }
    uint64_t  getPacketTotalCnt() const {
        return this->packetTotalCnt;
    }

    void setPacketLoss(double loss) {
        this->packetLoss = loss;
    }
    double getPacketLoss() const {
        return this->packetLoss;
    }

    virtual void readFromJsonString(std::string &jsonstr);
    virtual std::string writeToJsonString() const;

private:
    uint64_t trafficInstanceId;
    RoleType role;
    ProtocolType proto;
    std::string beginTimeStamp;
    std::string endTimeStamp;
    int64_t trafficInterval;    // us
    uint64_t bytesTransferred;  // Byte
    uint64_t trafficBandwidth;  // Byte/s
    uint64_t packetLostCnt;
    uint64_t packetTotalCnt;
    double packetLoss;
    double trafficJitter;
};


#endif //TRAFFICER_AGENTTRAFFICREPORTMESSAGE_H
