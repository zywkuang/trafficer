cmake_minimum_required(VERSION 2.6)
project(trafficer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        src/net/InetAddress.cpp
        src/net/InetAddress.h
        src/net/Socket.cpp
        src/net/Socket.h
        src/net/TcpSocket.cpp
        src/net/TcpSocket.h
        src/base/Exception.cpp
        src/base/Exception.h
        src/base/Json.h
        src/base/Json.cpp
        src/base/Thread.cpp
        src/base/Thread.h
        src/base/Mutex.cpp
        src/base/Mutex.h
        src/base/Copyable.h
        src/base/NonCopyable.h
        src/base/Event.cpp
        src/base/Event.h
        src/msg/Message.cpp
        src/msg/Message.h
        src/msg/MessageQueue.cpp
        src/msg/MessageQueue.h
        src/net/UdpSocket.cpp
        src/net/UdpSocket.h
        src/base/Logger.h
        src/base/Logger.cpp
        src/Trafficer.h
        src/base/TimeStamp.cpp
        src/base/TimeStamp.h
        src/msg/AgentRegistrationMessage.cpp
        src/msg/AgentRegistrationMessage.h
        src/msg/AgentHeartBeatMessage.cpp
        src/msg/AgentHeartBeatMessage.h
        src/msg/AgentTrafficReportMessage.cpp
        src/msg/AgentTrafficReportMessage.h
        src/msg/AgentCommandResponseMessage.cpp
        src/msg/AgentCommandResponseMessage.h
        src/msg/MccCommandRequestMessage.cpp
        src/msg/MccCommandRequestMessage.h
        src/model/AbstractTrafficModel.cpp
        src/model/AbstractTrafficModel.h
        src/base/UtilSet.cpp src/base/UtilSet.h
        src/TrafficInstanceConfig.cpp
        src/TrafficInstanceConfig.h
        )
add_executable(trafficer ${SOURCE_FILES})
target_link_libraries(trafficer pthread)