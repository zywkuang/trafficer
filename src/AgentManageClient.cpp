/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#include "AgentManageClient.h"
#include "base/Exception.h"

AgentManageClient::AgentManageClient(std::string paddr, int pport, size_t bqSize)
        : peerAddress(paddr),
          peerPort(pport),
          localAddress(""),
          localPort(TRAFFICER_MCC_CLIENT_PORT),
          mqCapacity(bqSize) {

}

AgentManageClient::AgentManageClient(std::string paddr, int pport, std::string laddr, int lport, size_t bqSize)
        : peerAddress(paddr),
          peerPort(pport),
          localAddress(laddr),
          localPort(lport),
          mqCapacity(bqSize){

}

AgentManageClient::~AgentManageClient() {

    if (this->dataStore != NULL)
        delete this->dataStore;

    if (this->messageConnection != NULL)
        delete this->messageConnection;
}

void AgentManageClient::connectMccManageServer() {
    TcpSocket *psock = this->messageConnection->getConnSock();
    psock->socketReset();

    InetAddress peerAddr(this->peerAddress, this->peerPort);
    if (this->localAddress.size() == 0) {
        psock->connectServer(peerAddr);
    } else {
        InetAddress localAddr(this->localAddress, this->localPort);
        psock->connectServer(peerAddr, localAddr);
    }
}

void AgentManageClient::initClient() {

    this->messageQueue = new BoundedBlockingQueue<Message *>(this->mqCapacity);
    this->dataStore = new AgentDataStore();
    this->messageConnection = NULL;

    this->tcpTrafficRecver.start(NULL);
    this->tcpTrafficRecver.detach();

    this->udpTrafficRecver.start(NULL);
    this->udpTrafficRecver.detach();
}

void AgentManageClient::cleanClient() {

}

void AgentManageClient::run() {
    this->initClient();

    TcpSocket *connSock = new TcpSocket();
    this->messageConnection = new TcpMessageConnection(connSock);

    while(true) {
        try {
            this->connectMccManageServer();

        } catch (Exception e) {

        }
    }

}
