/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/23/16
**/

#ifndef TRAFFICER_H
#define TRAFFICER_H

#define SOFTWARE_VERSION 0.1.0
#define MACHINE_CODE 1624
#define DEFAULT_INTERFACE "eth0"
#define RECONNECT_INTERVAL 2

// Traffic Generation Configuration
#define TRAFFIC_TCP_SENDBUF_SIZE 16384  // Bytes
#define TRAFFIC_UDP_SENDBUF_SIZE 1460   // Bytes
#define TRAFFIC_REPORT_INTERVAL 2000    // MicroSeconds
#define TRAFFIC_UPDATE_INTERVAL 500     // MicroSeconds

// Logger Configuration
#define LOG_LINE_SIZE 2048
#define LOG_BUFFER_SIZE 4096
#define LOG_FILE_NAME "trafficer.log"

// Trafficer Control Configuration
#define TRAFFICER_MCC_SERVRE_PORT 16109
#define TRAFFICER_MCC_CLIENT_PORT 21314

// Trafficer Traffic Configuration
#define TRAFFICER_UDP_SERVER_PORT 11518
#define TRAFFICER_TCP_SERVER_PORT 15332

// Message Queue Configuration
#define DEFAULT_QUEUE_CAPACITY 64

enum RoleType {
    SENDER = 0,
    RECVER,
};

enum ProtocolType {
    TCP = 0,
    UDP,
};

enum MessageType {
    AGENT_REGISTERATION = 0,
    AGENT_HEART_BEAT,
    AGENT_TRAFFIC_REPORT,
    AGENT_COMMAND_RESPONSE,
    MCC_COMMAND_REQUEST,
    UNKNOWN_MESSAGE_TYPE,
};

enum CommandType {
    CREATE_TRAFFIC_INSTANCE = 0,
    UPDATE_TRAFFIC_INSTANCE,
    DELETE_TRAFFIC_INSTANCE,
    RETRIEVE_TRAFFIC_INSTANCE,
    UNKNOWN_COMMAND_TYPE,
};

enum TrafficModelType {
    STABLE_TRAFFIC = 0,
    RECTANGLE_TRAFFIC,
    POISSON_TRAFFIC,
    CUSTOM_TRAFFIC,
    UNKNOWN_TRAFFIC_MODEL,
};

#endif //TRAFFICER_H
