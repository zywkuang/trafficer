/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include "AgentTrafficReportMessage.h"
#include "../base/Json.h"
#include "../base/Exception.h"

AgentTrafficReportMessage::AgentTrafficReportMessage()
    : Message(AGENT_TRAFFIC_REPORT),
      role(SENDER),
      proto(TCP) {

}

AgentTrafficReportMessage::~AgentTrafficReportMessage() {

}

void AgentTrafficReportMessage::setTrafficInstanceId(uint64_t tiid) {
    this->trafficInstanceId = tiid;
}

uint64_t AgentTrafficReportMessage::getTrafficInstanceId() const {
    return this->trafficInstanceId;
}

void AgentTrafficReportMessage::setRole(ROLE r) {
    this->role = r;
}

ROLE AgentTrafficReportMessage::getRole() const {
    return this->role;
}

void AgentTrafficReportMessage::setProtocol(PROTOCOL p) {
    this->proto = p;
}

PROTOCOL AgentTrafficReportMessage::getProtocol() const {
    return this->proto;
}

void AgentTrafficReportMessage::setBeginTimeStamp(std::string beginTimeStamp) {
    this->beginTimeStamp = beginTimeStamp;
}

std::string AgentTrafficReportMessage::getBeginTimeStamp() const {
    return this->beginTimeStamp;
}

void AgentTrafficReportMessage::setEndTimeStamp(std::string endTimeStamp) {
    this->endTimeStamp = endTimeStamp;
}

std::string AgentTrafficReportMessage::getEndTimeStamp() const {
    return this->endTimeStamp;
}

void AgentTrafficReportMessage::setBytesTransferred(uint64_t bytes) {
    this->bytesTransferred = bytes;
}

uint64_t AgentTrafficReportMessage::getBytesTransferred() const {
    return this->bytesTransferred;
}

void AgentTrafficReportMessage::setTrafficInterval(double interval) {
    this->trafficInterval = interval;
}

double AgentTrafficReportMessage::getTrafficInterval() const {
    return this->trafficInterval;
}

void AgentTrafficReportMessage::setTrafficBandwidth(double bandwidth) {
    this->trafficBandwidth = bandwidth;
}

double AgentTrafficReportMessage::getTrafficBandwidth() const {
    return this->trafficBandwidth;
}

void AgentTrafficReportMessage::setTrafficJitter(double jitter) {
    this->trafficJitter = jitter;
}

double AgentTrafficReportMessage::getTrafficJitter() const {
    return this->trafficJitter;
}

void AgentTrafficReportMessage::setPacketLostCnt(uint64_t lostCnt) {
    this->packetLostCnt = lostCnt;
}

uint64_t AgentTrafficReportMessage::getPacketLostCnt() const {
    return this->packetLostCnt;
}

void AgentTrafficReportMessage::setPacketTotalCnt(uint64_t totalCnt) {
    this->packetTotalCnt = totalCnt;
}

uint64_t AgentTrafficReportMessage::getPacketTotalCnt() const {
    return this->packetTotalCnt;
}

void AgentTrafficReportMessage::setPacketLoss(double loss) {
    this->packetLoss = loss;
}

double AgentTrafficReportMessage::getPacketLoss() const {
    return this->packetLoss;
}

void AgentTrafficReportMessage::readFromJsonString(std::string jsonstr) {
    JsonObject *json = cJsonParse(jsonstr.c_str());

    JsonObject *pj;

    if ((pj = cJsonGetObjectItem(json, "MsgID")) != NULL)
        this->msgId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TimeStamp")) != NULL)
        this->msgTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "TrafficID")) != NULL)
        this->trafficInstanceId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "Role")) != NULL)
        this->role = static_cast<ROLE>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "Protocol")) != NULL)
        this->proto = static_cast<PROTOCOL>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "BeginTimeStamp")) != NULL)
        this->beginTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "EndTimeStamp")) != NULL)
        this->endTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "BytesTransferred")) != NULL)
        this->bytesTransferred = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TrafficInterval")) != NULL)
        this->trafficInterval = pj->valueDouble;

    if ((pj = cJsonGetObjectItem(json, "TrafficBandwidth")) != NULL)
        this->trafficBandwidth = pj->valueDouble;

    if ((pj = cJsonGetObjectItem(json, "TrafficJitter")) != NULL)
        this->trafficJitter = pj->valueDouble;

    if ((pj = cJsonGetObjectItem(json, "PacketLostCount")) != NULL)
        this->packetLostCnt = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "PacketTotalCount")) != NULL)
        this->packetLoss = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "PacketLoss")) != NULL)
        this->packetLoss = pj->valueDouble;

    cJsonDelete(json);
}

std::string AgentTrafficReportMessage::writeToJsonString() const {
    JsonObject *json = cJsonCreateObject();

    if (json == NULL) {
        throw Exception(ENULLPOINTER, "Null Pointer Exception");
    } else {
        cJsonAddIntToObject(json, "MsgID", this->msgId);
        cJsonAddIntToObject(json, "MsgType", AGENT_TRAFFIC_REPORT);
        cJsonAddStringToObject(json, "TimeStamp", this->msgTimeStamp.c_str());
        cJsonAddIntToObject(json, "TrafficID", this->trafficInstanceId);
        cJsonAddIntToObject(json, "Role", this->role);
        cJsonAddIntToObject(json, "Protocol", this->proto);
        cJsonAddStringToObject(json, "BeginTimeStamp", this->beginTimeStamp.c_str());
        cJsonAddStringToObject(json, "EndTimeStamp", this->endTimeStamp.c_str());
        cJsonAddIntToObject(json, "BytesTransferred", this->bytesTransferred);
        cJsonAddDoubleToObject(json, "TrafficInterval", this->trafficInterval);
        cJsonAddDoubleToObject(json, "TrafficBandwidth", this->trafficBandwidth);

        if (this->proto == UDP) {
            cJsonAddDoubleToObject(json, "TrafficJitter", this->trafficJitter);
            cJsonAddIntToObject(json, "PacketLostCount", this->packetLostCnt);
            cJsonAddIntToObject(json, "PacketTotalCount", this->packetTotalCnt);
            cJsonAddDoubleToObject(json, "PacketLoss", this->packetLoss);
        }
    }

    std::string jsonStr = cJsonPrintUnformatted(json);
    cJsonDelete(json);

    return jsonStr;
}