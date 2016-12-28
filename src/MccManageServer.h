/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/28/16
**/

#ifndef TRAFFICER_MCCMANAGESERVER_H
#define TRAFFICER_MCCMANAGESERVER_H

#include <map>
#include <stdint.h>
#include "base/Thread.h"
#include "net/TcpSocket.h"
#include "Trafficer.h"

class MccManageServer : public Thread {
public:
    MccManageServer();
    MccManageServer(std::string ip, int port = TRAFFICER_MCC_SERVRE_PORT);
    ~MccManageServer();

    virtual void run();

private:
    TcpSocket *serverSocket;
};


#endif //TRAFFICER_MCCMANAGESERVER_H
