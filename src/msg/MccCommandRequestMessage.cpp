/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/26/16
**/

#include "MccCommandRequestMessage.h"
#include "../base/Json.h"
#include "../base/Exception.h"

MccCommandRequestMessage::MccCommandRequestMessage(uint64_t id)
        : Message(MCC_COMMAND_REQUEST),
          hostMccId(id),
          cmdType(UNKNOWN_COMMAND_TYPE) {

}

MccCommandRequestMessage::~MccCommandRequestMessage() {

}

void MccCommandRequestMessage::setHostMccId(uint64_t id) {
    this->hostMccId = id;
}

uint64_t MccCommandRequestMessage::getHostMccId() const {
    return this->hostMccId;
}

void MccCommandRequestMessage::setTrafficInstanceId(uint64_t trafficInstanceId) {
    this->trafficInstanceId = trafficInstanceId;
}

uint64_t MccCommandRequestMessage::getTrafficInstanceId() const {
    return this->trafficInstanceId;
}

void MccCommandRequestMessage::setCmdType(CommandType commandType) {
    this->cmdType = commandType;
}

CommandType MccCommandRequestMessage::getCmdType() const {
    return this->cmdType;
}

void MccCommandRequestMessage::setTrafficInstanceConfig(TrafficInstanceConfig &tic) {
    this->trafficInstanceConfig = tic;
}

const TrafficInstanceConfig& MccCommandRequestMessage::getTrafficInstanceConfig() const {
    return this->trafficInstanceConfig;
}

void MccCommandRequestMessage::readFromJsonString(std::string &jsonstr) {
    JsonObject *json = cJsonParse(jsonstr.c_str());

    JsonObject *pj;

    if ((pj = cJsonGetObjectItem(json, "MsgID")) != NULL)
        this->msgId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TimeStamp")) != NULL)
        this->msgTimeStamp = pj->valueString;

    if ((pj = cJsonGetObjectItem(json, "HostMCCID")) != NULL)
        this->hostMccId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "TrafficInstanceID")) != NULL)
        this->trafficInstanceId = static_cast<uint64_t>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "CommandType")) != NULL)
        this->cmdType = static_cast<CommandType>(pj->valueInt);

    if ((pj = cJsonGetObjectItem(json, "SenderHostAddress")) != NULL) {
        std::string senderHostAddress = pj->valueString;
        this->trafficInstanceConfig.setSenderHostAddress(senderHostAddress);
    }

    if ((pj = cJsonGetObjectItem(json, "RecverHostAddress")) != NULL) {
        std::string recverHostAddress = pj->valueString;
        this->trafficInstanceConfig.setRecverHostAddress(recverHostAddress);
    }

    if ((pj = cJsonGetObjectItem(json, "ServerHostPort")) != NULL)
        this->trafficInstanceConfig.setServerHostPort(static_cast<int>(pj->valueInt));

    if ((pj = cJsonGetObjectItem(json, "Role")) != NULL)
        this->trafficInstanceConfig.setRole(static_cast<RoleType>(pj->valueInt));

    if ((pj = cJsonGetObjectItem(json, "Protocol")) != NULL)
        this->trafficInstanceConfig.setProtocol(static_cast<ProtocolType>(pj->valueInt));

    if ((pj = cJsonGetObjectItem(json, "WorkDuration")) != NULL)
        this->trafficInstanceConfig.setWorkDuration(static_cast<int>(pj->valueInt));

    if ((pj = cJsonGetObjectItem(json, "ReportInterval")) != NULL)
        this->trafficInstanceConfig.setReportInterval(static_cast<int>(pj->valueInt));

    if ((pj = cJsonGetObjectItem(json, "UpdateInterval")) != NULL)
        this->trafficInstanceConfig.setUpdateIntervel(static_cast<int>(pj->valueInt));

    if ((pj = cJsonGetObjectItem(json, "SendBufSize")) != NULL)
        this->trafficInstanceConfig.setSendBufSize(static_cast<int>(pj->valueInt));

    if ((pj = cJsonGetObjectItem(json, "TcpNoDelay")) != NULL) {
        if (1 == pj->valueInt)
            this->trafficInstanceConfig.setTcpNoDelay(true);
        else
            this->trafficInstanceConfig.setTcpNoDelay(false);
    }

    if ((pj = cJsonGetObjectItem(json, "TcpMss")) != NULL)
        this->trafficInstanceConfig.setTcpMss(static_cast<int>(pj->valueInt));

    if ((pj = cJsonGetObjectItem(json, "TrafficModelType")) != NULL) {
        TrafficModelType tmt = static_cast<TrafficModelType>(pj->valueInt);
        this->trafficInstanceConfig.setTrafficModel(tmt);

        switch (tmt) {
            case STABLE_TRAFFIC:
                if ((pj = cJsonGetObjectItem(json, "StableTrafficBandwidth")) != NULL)
                    this->trafficInstanceConfig.setStableTrafficBandwidth(static_cast<uint64_t>(pj->valueInt));
                break;
            case RECTANGLE_TRAFFIC:
                if ((pj = cJsonGetObjectItem(json, "RectSupremumTrafficBandwidth")) != NULL)
                    this->trafficInstanceConfig.setRectSupremumTrafficBandwidth(static_cast<uint64_t>(pj->valueInt));

                if ((pj = cJsonGetObjectItem(json, "RectInfimumTrafficBandwidth")) != NULL)
                    this->trafficInstanceConfig.setRectInfimumTrafficBandwidth(static_cast<uint64_t>(pj->valueInt));

                if ((pj = cJsonGetObjectItem(json, "RectSupreProportion")) != NULL)
                    this->trafficInstanceConfig.setRectSupreProportion(pj->valueDouble);
                break;
            case POISSON_TRAFFIC:
                if ((pj = cJsonGetObjectItem(json, "PoissonBurstTrafficBandwidth")) != NULL)
                    this->trafficInstanceConfig.setPoissonBurstTrafficBandwidth(static_cast<uint64_t>(pj->valueInt));
                break;
            case CUSTOM_TRAFFIC:
                break;
            case UNKNOWN_TRAFFIC_MODEL:
            default:
                break;
        }
    }

    cJsonDelete(json);
}

std::string MccCommandRequestMessage::writeToJsonString() const {
    JsonObject *json = cJsonCreateObject();

    if (json == NULL) {
        throw Exception(ENULLPOINTER, "Null Pointer Exception");
    } else {
        cJsonAddIntToObject(json, "MsgID", this->msgId);
        cJsonAddIntToObject(json, "MsgType", MCC_COMMAND_REQUEST);
        cJsonAddStringToObject(json, "TimeStamp", this->msgTimeStamp.c_str());

        cJsonAddIntToObject(json, "HostMCCID", this->hostMccId);
        cJsonAddIntToObject(json, "TrafficInstanceID", this->trafficInstanceId);
        cJsonAddIntToObject(json, "CommandType", this->cmdType);
        cJsonAddStringToObject(json, "SenderHostAddress", this->trafficInstanceConfig.getSenderHostAddress().c_str());
        cJsonAddStringToObject(json, "RecverHostAddress", this->trafficInstanceConfig.getRecverHostAddress().c_str());
        cJsonAddIntToObject(json, "ServerHostPort", this->trafficInstanceConfig.getServerHostPort());
        cJsonAddIntToObject(json, "Role", this->trafficInstanceConfig.getRole());
        cJsonAddIntToObject(json, "Protocol", this->trafficInstanceConfig.getProtocol());

        cJsonAddIntToObject(json, "WorkDuration", this->trafficInstanceConfig.getWorkDuration());
        cJsonAddIntToObject(json, "ReportInterval", this->trafficInstanceConfig.getReportInterval());
        cJsonAddIntToObject(json, "UpdateInterval", this->trafficInstanceConfig.getUpdateIntervel());
        cJsonAddIntToObject(json, "SendBufSize", this->trafficInstanceConfig.getSendBufSize());
        if (this->trafficInstanceConfig.isTcpNoDelay())
            cJsonAddIntToObject(json, "TcpNoDelay", 1);
        else
            cJsonAddIntToObject(json, "TcpNoDelay", 0);
        cJsonAddIntToObject(json, "TcpMss", this->trafficInstanceConfig.getTcpMss());

        TrafficModelType tmt = this->trafficInstanceConfig.getTrafficModel();
        cJsonAddIntToObject(json, "TrafficModelType", tmt);

        switch (tmt) {
            case STABLE_TRAFFIC:
                cJsonAddIntToObject(json, "StableTrafficBandwidth", this->trafficInstanceConfig.getStableTrafficBandwidth());
                break;
            case RECTANGLE_TRAFFIC:
                cJsonAddIntToObject(json, "RectSupremumTrafficBandwidth", this->trafficInstanceConfig.getRectSupremumTrafficBandwidth());
                cJsonAddIntToObject(json, "RectInfimumTrafficBandwidth", this->trafficInstanceConfig.getRectInfimumTrafficBandwidth());
                cJsonAddDoubleToObject(json, "RectSupreProportion", this->trafficInstanceConfig.getRectSupreProportion());
                break;
            case POISSON_TRAFFIC:
                cJsonAddIntToObject(json, "PoissonBurstTrafficBandwidth", this->trafficInstanceConfig.getPoissonBurstTrafficBandwidth());
                break;
            case CUSTOM_TRAFFIC:
                break;
            case UNKNOWN_TRAFFIC_MODEL:
            default:
                break;
        }
    }

    std::string jsonStr = cJsonPrintUnformatted(json);
    cJsonDelete(json);

    return jsonStr;
}
