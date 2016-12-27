/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/23/16
**/

#ifndef TRAFFICER_CONFIG_H
#define TRAFFICER_CONFIG_H

#define SOFTWARE_VERSION 0.1.0
#define MACHINE_CODE 1624

// Logger Configuration
#define LOG_FILE_NAME "trafficer.log"
#define LOG_BUFFER_SIZE 4096
#define LOG_LINE_SIZE 2048

// Traffic Recver Configuration
#define TRAFFICER_UDP_SERVER_PORT 11518
#define TRAFFICER_TCP_SERVER_PORT 15332

// Message Queue Configuration
#define MESSAGE_QUEUE_CAPACITY 64

enum MESSAGE_TYPE {
    AGENT_REGISTERATION = 0,
    AGENT_HEART_BEAT,
    AGENT_TRAFFIC_REPORT,
    AGENT_COMMAND_RESPONSE,
    MCC_COMMAND_REQUEST,
    UNKNOWN,
};

enum PROTOCOL {
    TCP = 0,
    UDP,
    SCTP,
    UNKNOWN,
};

enum ROLE {
    SENDER = 0,
    RECVER,
    UNKNOWN,
};

enum TRAFFIC_MODEL {
    STABLE_TRAFFIC = 0,
    RECTANGLE_TRAFFIC,
    POISSON_TRAFFIC,
    CUSTOM_TRAFFIC,
    UNKNOWN,
};

#endif //TRAFFICER_CONFIG_H
