/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/29/16
**/

#include <stdint.h>
#include "TcpMessageConnection.h"
#include "base/Exception.h"
#include "base/Logger.h"
#include "msg/AgentRegistrationMessage.h"
#include "msg/AgentHeartBeatMessage.h"
#include "msg/AgentTrafficReportMessage.h"
#include "msg/AgentCommandResponseMessage.h"
#include "msg/MccCommandRequestMessage.h"

TcpMessageConnection::TcpMessageConnection(TcpSocket *psock)
        : connSock(psock){

}

TcpMessageConnection::~TcpMessageConnection() {
    delete this->connSock;
}

TcpSocket* TcpMessageConnection::getConnSock() const {
    return this->connSock;
}

void TcpMessageConnection::sendMessageToConnection(Message *msg) {
    try {
        uint32_t mType = static_cast<uint32_t>msg->getMessageType();
        uint32_t net_mType = htonl(mType);

        std::string jsonStr = msg->writeToJsonString();
        uint32_t strLen = static_cast<uint32_t>(jsonStr.size());
        uint32_t net_strLen = htonl(strLen);

        // First: Send mType
        this->connSock->sendData(static_cast<const char *>(&net_mType), sizeof(net_mType));

        // Second: Send jsonStrLen
        this->connSock->sendData(static_cast<const char *>(&net_strLen), sizeof(net_strLen));

        // Third: Send jsonStr
        this->connSock->sendData(jsonStr.c_str(), strLen);

    } catch (Exception e) {
        LOG_ERROR(e.what());
        throw Exception(EMSGSEND, "Json String Send Exception");
    }
}

Message* TcpMessageConnection::recvMessageFromConnection() {
    Message *msg = NULL;

    try {
        uint32_t net_mType;
        this->connSock->recvData(static_cast<char *>(&net_mType), sizeof(net_mType));
        uint32_t mType = ntohl(net_mType);

        uint32_t net_strLen;
        this->connSock->recvData(static_cast<char *>(&net_strLen), sizeof(net_strLen));
        uint32_t strLen = ntohl(net_strLen);

        char *strBuf = new char[strLen + 1];
        this->connSock->recvData(strBuf, strLen);
        strBuf[strLen] = '\0';
        std::string jsonStr(strBuf);

        switch (static_cast<MessageType>(mType)) {
            case AGENT_REGISTERATION:
                msg = new AgentRegistrationMessage();
                msg->readFromJsonString(jsonStr);
                break;

            case AGENT_HEART_BEAT:
                msg = new AgentHeartBeatMessage();
                msg->readFromJsonString(jsonStr);
                break;

            case AGENT_TRAFFIC_REPORT:
                msg = new AgentTrafficReportMessage();
                msg->readFromJsonString(jsonStr);
                break;

            case AGENT_COMMAND_RESPONSE:
                msg = new AgentCommandResponseMessage();
                msg->readFromJsonString(jsonStr);
                break;

            case MCC_COMMAND_REQUEST:
                msg = new MccCommandRequestMessage();
                msg->readFromJsonString(jsonStr);
                break;

            case UNKNOWN_MESSAGE_TYPE:
            default:
                break;
        }
    } catch (Exception e) {
        LOG_ERROR(e.what());
        throw Exception(EMSGRECV, "Json String Receive Exception");
    }

    return msg;
}
