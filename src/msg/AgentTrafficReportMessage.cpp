/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include "AgentTrafficReportMessage.h"
#include "../base/Json.h"
#include "../base/Exception.h"
#include "../AgentDataStore.h"

AgentTrafficReportMessage::AgentTrafficReportMessage()
        : Message(AgentDataStore::agentHostUUID, AGENT_TRAFFIC_REPORT),
          role(SENDER),
          proto(TCP)  {

}

AgentTrafficReportMessage::~AgentTrafficReportMessage() {

}

void AgentTrafficReportMessage::readFromJsonString(std::string &jsonstr) {
    JsonObject *json = cJsonParse(jsonstr.c_str());

    JsonObject *pj;

    if ((pj = cJsonGetObjectItem(json, "MsgID")) != NULL)
        this->msgId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TimeStamp")) != NULL)
        this->msgTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "HostAgentID")) != NULL)
        this->hostId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TrafficID")) != NULL)
        this->trafficInstanceId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "Role")) != NULL)
        this->role = static_cast<RoleType>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "Protocol")) != NULL)
        this->proto = static_cast<ProtocolType>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "BeginTimeStamp")) != NULL)
        this->beginTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "EndTimeStamp")) != NULL)
        this->endTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "BytesTransferred")) != NULL)
        this->bytesTransferred = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TrafficInterval")) != NULL)
        this->trafficInterval = pj->valueInt;

    if ((pj = cJsonGetObjectItem(json, "TrafficBandwidth")) != NULL)
        this->trafficBandwidth = static_cast<uint64_t>(pj->valueInt);

    if (this->proto == UDP) {
        if (this->role == RECVER) {
            if ((pj = cJsonGetObjectItem(json, "TrafficJitter")) != NULL)
                this->trafficJitter = pj->valueInt;

            if ((pj = cJsonGetObjectItem(json, "PacketOutCount")) != NULL)
                this->packetOutCnt = static_cast<uint64_t>(pj->valueInt);

            if ((pj = cJsonGetObjectItem(json, "PacketOutss")) != NULL)
                this->packetOutss = pj->valueDouble;
        }

        if ((pj = cJsonGetObjectItem(json, "PacketTotalCount")) != NULL)
            this->packetTotalCnt = static_cast<uint64_t>(pj->valueInt);
    }
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

        cJsonAddIntToObject(json, "HostAgentID", this->hostId);
        cJsonAddIntToObject(json, "TrafficID", this->trafficInstanceId);
        cJsonAddIntToObject(json, "Role", this->role);
        cJsonAddIntToObject(json, "Protocol", this->proto);
        cJsonAddStringToObject(json, "BeginTimeStamp", this->beginTimeStamp.c_str());
        cJsonAddStringToObject(json, "EndTimeStamp", this->endTimeStamp.c_str());
        cJsonAddIntToObject(json, "BytesTransferred", this->bytesTransferred);
        cJsonAddIntToObject(json, "TrafficInterval", this->trafficInterval);
        cJsonAddIntToObject(json, "TrafficBandwidth", this->trafficBandwidth);

        if (this->proto == UDP) {
            if (this->role == RECVER) {
                cJsonAddIntToObject(json, "TrafficJitter", this->trafficJitter);
                cJsonAddIntToObject(json, "PacketOutCount", this->packetOutCnt);
                cJsonAddDoubleToObject(json, "PacketOutss", this->packetOutss);
            }

            cJsonAddIntToObject(json, "PacketTotalCount", this->packetTotalCnt);
        }
    }

    std::string jsonStr = cJsonPrintUnformatted(json);
    cJsonDelete(json);

    return jsonStr;
}