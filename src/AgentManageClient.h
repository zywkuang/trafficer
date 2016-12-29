/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_AGENTMANAGECLIENT_H
#define TRAFFICER_AGENTMANAGECLIENT_H


#include "base/Thread.h"
#include "net/TcpSocket.h"
#include "TcpMessageConnection.h"
#include "AgentMessageDispatcher.h"
#include "AgentDataStore.h"
#include "base/BoundedBlockingQueue.h"
#include "AgentTcpTrafficRecver.h"
#include "AgentUdpTrafficRecver.h"

class AgentManageClient : public Thread {
public:
    AgentManageClient(std::string paddr, int pport, size_t bqSize = DEFAULT_QUEUE_CAPACITY);
    AgentManageClient(std::string paddr, int pport, std::string laddr, int lport, size_t bqSize = DEFAULT_QUEUE_CAPACITY);
    ~AgentManageClient();

    void initClient();
    void cleanClient();

    void connectMccManageServer();

    virtual void run();

private:
    // Core Thread
    AgentMessageDispatcher messageDispatcher;
    AgentTcpTrafficRecver tcpTrafficRecver;
    AgentUdpTrafficRecver udpTrafficRecver;

    // Key Data
    AgentDataStore *dataStore;
    TcpMessageConnection *messageConnection;
    BoundedBlockingQueue<Message *> *messageQueue;

    // Internal Data
    std::string localAddress;
    int localPort;
    std::string peerAddress;
    int peerPort;
    size_t mqCapacity;
};


#endif //TRAFFICER_AGENTMANAGECLIENT_H
