//
// Created by zjl on 10/26/16.
//

#ifndef TRAFFICER_INETADDRESS_H
#define TRAFFICER_INETADDRESS_H

#include <netinet/in.h>
#include <netinet/tcp.h>
#include "../base/Copyable.h"

class InetAddress : public Copyable {
public:
    explicit InetAddress(uint16_t portNumber = 1024, bool bIpv6 = false);
    InetAddress(const char *ipAddress, uint16_t portNumber = 1024, bool bIpv6 = false);

    explicit InetAddress(const struct sockaddr_in  &sockaddr4);
    explicit InetAddress(const struct sockaddr_in6 &sockaddr6);

    void setSockAddrIn6(const struct sockaddr_in6 &addr6);

    sa_family_t getAddressFamily() const;
    const struct sockaddr* getSockAddr() const;
    uint16_t getPortNumber() const;

    uint32_t ipNetEndian() const;
    uint16_t portNetEndian() const;

    const char* toIpString() const;
    const char* toIpPortString() const;

    // Resolve hostname to IP address, not changing port or sin_family
    static bool resolveHostName(const char *hostname, InetAddress *result);

private:
    union {
        struct sockaddr_in  sa4Struct;
        struct sockaddr_in6 sa6Struct;
    };
};

#endif //TRAFFICER_INETADDRESS_H
