cmake_minimum_required(VERSION 2.6)
project(trafficer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        src/base/Exception.cpp
        src/base/Exception.h
        src/net/InetAddress.cpp
        src/net/InetAddress.h
        src/net/Socket.cpp
        src/net/Socket.h
        src/TcpSocket.cpp
        src/TcpSocket.h
        src/base/Json.h
        src/base/Json.cpp
        src/thread/Thread.cpp
        src/thread/Thread.h
        src/thread/Mutex.cpp
        src/thread/Mutex.h
        src/base/Copyable.h
        src/base/NonCopyable.h
        src/thread/Event.cpp
        src/thread/Event.h
        src/thread/Message.cpp
        src/thread/Message.h
        src/thread/MessageQueue.cpp
        src/thread/MessageQueue.h)
add_executable(trafficer ${SOURCE_FILES})
target_link_libraries(trafficer pthread)