/**
  * Organization: UESTC-KB310
  * Author: zjl
  * Date: 10/28/16
**/

#ifndef TRAFFICER_INETADDRESS_H
#define TRAFFICER_INETADDRESS_H

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string>
#include "../base/Copyable.h"

class InetAddress : public Copyable {
public:
    explicit InetAddress(uint16_t portNumber = 1024, bool bIpv6 = false);
    explicit InetAddress(std::string ipAddress, uint16_t portNumber, bool bIpv6 = false);

    explicit InetAddress(const struct sockaddr_in  &sockaddr4);
    explicit InetAddress(const struct sockaddr_in6 &sockaddr6);

    ~InetAddress();

    void setSockAddrIn6(const struct sockaddr_in6 &addr6);

    uint32_t ipNetEndian() const;
    uint16_t portNetEndian() const;

    sa_family_t getAddressFamily() const;
    const struct sockaddr* getSockAddr() const;
    std::string getIpString() const;
    uint16_t getPortNumber() const;

    std::string toIpPortString() const;

    // Resolve hostname to IP address, not changing port or sin_family
    static bool resolveHostName(std::string hostname, InetAddress *result);

private:
    union {
        struct sockaddr_in  sa4Struct;
        struct sockaddr_in6 sa6Struct;
    };
};

#endif //TRAFFICER_INETADDRESS_H
