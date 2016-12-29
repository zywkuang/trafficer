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
#include "msg/MccCommandRequestMessage.h"

class AgentManageClient : public Thread {
public:
    AgentManageClient(std::string paddr, int pport, size_t bqSize = DEFAULT_QUEUE_CAPACITY);
    AgentManageClient(std::string paddr, int pport, std::string laddr, int lport, size_t bqSize = DEFAULT_QUEUE_CAPACITY);
    virtual ~AgentManageClient();

    void initClient();
    void cleanClient();

    void connectMccManageServer();
    void unsetConnectionAlive();
    void setConnectionAlive();

    virtual void run();

private:
    // Functions
    void handleIncomingMessage(Message *msg);
    void handleCommandRequestMessage(MccCommandRequestMessage *msg);

    void handleTrafficInstanceCreate(uint64_t tiid, const TrafficInstanceConfig &tic);
    void handleTrafficInstanceRetrieve(uint64_t tiid);
    void handleTrafficInstanceUpdate(uint64_t tiid, const TrafficInstanceConfig &tic);
    void handleTrafficInstanceDelete(uint64_t tiid);

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

    // State Data
    bool bConnectionAlive;
};


#endif //TRAFFICER_AGENTMANAGECLIENT_H
