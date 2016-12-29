/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/29/16
**/

#ifndef TRAFFICER_TCPMANAGECONNECTION_H
#define TRAFFICER_TCPMANAGECONNECTION_H

#include "net/TcpSocket.h"
#include "msg/Message.h"

class TcpMessageConnection : public NonCopyable {
public:
    TcpMessageConnection(TcpSocket *psock);
    ~TcpMessageConnection();

    Message *recvMessageFromConnection();
    void sendMessageToConnection(Message *msg);

    TcpSocket *getConnSock() const;

private:
    TcpSocket *connSock;
};


#endif //TRAFFICER_TCPMANAGECONNECTION_H
