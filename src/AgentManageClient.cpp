/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include <iostream>
#include "AgentManageClient.h"
#include "base/Exception.h"
#include "base/UtilSet.h"
#include "base/TimeStamp.h"
#include "msg/AgentRegistrationMessage.h"

AgentManageClient::AgentManageClient(std::string paddr, int pport, size_t bqSize)
        : peerAddress(paddr),
          peerPort(pport),
          localAddress(""),
          localPort(TRAFFICER_MCC_CLIENT_PORT),
          mqCapacity(bqSize),
          bConnectionAlive(false) {

}

AgentManageClient::AgentManageClient(std::string paddr, int pport, std::string laddr, int lport, size_t bqSize)
        : peerAddress(paddr),
          peerPort(pport),
          localAddress(laddr),
          localPort(lport),
          mqCapacity(bqSize),
          bConnectionAlive(false){

}

AgentManageClient::~AgentManageClient() {

    if (this->dataStore != NULL)
        delete this->dataStore;

    if (this->messageConnection != NULL)
        delete this->messageConnection;
}

void AgentManageClient::unsetConnectionAlive()  {
    this->bConnectionAlive = false;
}

void AgentManageClient::setConnectionAlive()  {
    this->bConnectionAlive = true;
}

void AgentManageClient::connectMccManageServer() {
    TcpSocket *psock = this->messageConnection->getConnSock();
    psock->socketReset();

    InetAddress peerAddr(this->peerAddress, static_cast<uint16_t>(this->peerPort));
    if (this->localAddress.size() == 0) {
        psock->connectServer(peerAddr);
    } else {
        InetAddress localAddr(this->localAddress, static_cast<uint16_t>(this->localPort));
        psock->connectServer(peerAddr, localAddr);
    }

    this->setConnectionAlive();
}

void AgentManageClient::initClient() {

    // Initialize Message Queue
    this->messageQueue = new BoundedBlockingQueue<Message *>(this->mqCapacity);

    // Initialize DataStore Information
    this->dataStore = new AgentDataStore();
    this->messageConnection = NULL;

    // Launch TCP Traffic Recver
    this->tcpTrafficRecver.start(NULL);
    this->tcpTrafficRecver.detach();

    // Launch UDP Traffic Recver
    this->udpTrafficRecver.start(NULL);
    this->udpTrafficRecver.detach();
}

void AgentManageClient::cleanClient() {

}

void AgentManageClient::handleTrafficInstanceCreate(uint64_t tiid, const TrafficInstanceConfig &tic) {
    this->dataStore->createTrafficInstanceConfig(tiid, tic);

    RoleType role = tic.getRole();
    ProtocolType protocol = tic.getProtocol();

    if (role == SENDER) {
        if (protocol == TCP) {
            AgentTcpTrafficSender *patts = new AgentTcpTrafficSender(tic);
            patts->start(NULL);
            patts->detach();
            this->dataStore->insertAgentTcpTrafficSender(tiid, patts);

        } else if (protocol == UDP) {
            AgentUdpTrafficSender *pauts = new AgentUdpTrafficSender(tic, this->messageQueue);
            pauts->start(NULL);
            pauts->detach();
            this->dataStore->insertAgentUdpTrafficSender(tiid, pauts);
        }

    } else if(role == RECVER) {

    }
}

void AgentManageClient::handleTrafficInstanceUpdate(uint64_t tiid, const TrafficInstanceConfig &tic) {
    this->dataStore->updateTrafficInstanceConfig(tiid, tic);

    RoleType role = tic.getRole();
    ProtocolType protocol = tic.getProtocol();

    if (role == SENDER) {
        if (protocol == TCP) {
            AgentTcpTrafficSender *patts = NULL;
            patts = this->dataStore->retrieveAgentTcpTrafficSender(tiid);
            patts->updateTrafficConfig(tic);

        } else if (protocol == UDP) {
            AgentUdpTrafficSender *pauts = NULL;
            pauts = this->dataStore->retrieveAgentUdpTrafficSender(tiid);
            pauts->updateTrafficConfig(tic);
        }

    } else if(role == RECVER) {

    }
}

void AgentManageClient::handleTrafficInstanceRetrieve(uint64_t tiid) {
    // .......
}

void AgentManageClient::handleTrafficInstanceDelete(uint64_t tiid) {
    this->dataStore->deleteTrafficInstanceConfig(tiid);

    // ........
}

void AgentManageClient::handleCommandRequestMessage(MccCommandRequestMessage *msg) {
    CommandType cmdType = msg->getCmdType();
    uint64_t tiid = 0;

    switch (cmdType) {
        case CREATE_TRAFFIC_INSTANCE:
            TrafficInstanceConfig newtic = msg->getTrafficInstanceConfig();
            tiid = msg->getTrafficInstanceId();
            this->handleTrafficInstanceCreate(tiid, newtic);
            break;
        case RETRIEVE_TRAFFIC_INSTANCE:
            tiid = msg->getTrafficInstanceId();
            this->handleTrafficInstanceRetrieve(tiid);
            break;
        case UPDATE_TRAFFIC_INSTANCE:
            TrafficInstanceConfig uptic = msg->getTrafficInstanceConfig();
            tiid = msg->getTrafficInstanceId();
            this->handleTrafficInstanceUpdate(tiid, uptic);
            break;
        case DELETE_TRAFFIC_INSTANCE:
            tiid = msg->getTrafficInstanceId();
            this->handleTrafficInstanceDelete(tiid);
            break;
        case UNKNOWN_COMMAND_TYPE:
        default:
            break;
    }
}

void AgentManageClient::handleIncomingMessage(Message *msg) {
    switch (msg->getMessageType()) {
        case MCC_COMMAND_REQUEST:
            this->handleCommandRequestMessage(dynamic_cast<MccCommandRequestMessage *>(msg));
            break;
        default:
            break;
    }
}

void AgentManageClient::run() {
    this->initClient();

    TcpSocket *connSock = new TcpSocket();
    this->messageConnection = new TcpMessageConnection(connSock);

    while (true) {
        try {
            std::cout << "Try to connect to master control center." << std::endl;
            this->connectMccManageServer();

            std::cout << "Connected to master control center." << std::endl;

            if (this->bConnectionAlive) {
                AgentRegistrationMessage *registrationMessage = new AgentRegistrationMessage();

                registrationMessage->setHostAgentId(AgentDataStore::agentHostUUID);
                registrationMessage->setHostName(AgentDataStore::agentHostName);
                registrationMessage->setHostAddress(AgentDataStore::agentHostAddress);
                registrationMessage->setHostSysinfo(AgentDataStore::agentHostSysinfo);
                registrationMessage->setTcpTrafficerPort(TRAFFICER_TCP_SERVER_PORT);
                registrationMessage->setUdpTrafficerPort(TRAFFICER_UDP_SERVER_PORT);

                this->messageConnection->sendMessageToConnection(dynamic_cast<Message *>(registrationMessage));
                std::cout << "Registration message send successfully." << std::endl;
            }

            while (this->bConnectionAlive) {
                Message *msg = this->messageConnection->recvMessageFromConnection();
                this->handleIncomingMessage(msg);
                delete msg;
            }

        } catch (Exception e) {
            std::cout << "Exception: " << e.what() << std::endl;
            std::cout << "Reconnect in " << RECONNECT_INTERVAL << " seconds" << std::endl;
        }

        UtilSet::delaySelect(RECONNECT_INTERVAL * MICROSECOND_PER_SECOND);
    }
}
