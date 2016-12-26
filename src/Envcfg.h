/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 12/23/16
**/

#ifndef TRAFFICER_CONFIG_H
#define TRAFFICER_CONFIG_H

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

#endif //TRAFFICER_CONFIG_H
