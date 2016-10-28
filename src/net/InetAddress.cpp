//
// Created by zjl on 10/26/16.
//

#include <arpa/inet.h>
#include <assert.h>
#include <netdb.h>
#include <stdio.h>
#include <cstring>
#include "InetAddress.h"

InetAddress::InetAddress(uint16_t portNumber, bool bIpv6) {
    if (bIpv6) {
        memset(&this->sa6Struct, 0, sizeof(struct sockaddr_in6));
        this->sa6Struct.sin6_family = AF_INET6;
        this->sa6Struct.sin6_addr = in6addr_any;
        this->sa6Struct.sin6_port = htons(portNumber);
    } else {
        memset(&this->sa4Struct, 0, sizeof(struct sockaddr_in));
        this->sa4Struct.sin_family = AF_INET;
        this->sa4Struct.sin_addr.s_addr = htonl(INADDR_ANY);
        this->sa4Struct.sin_port = htons(portNumber);
    }
}

InetAddress::InetAddress(const char *ipAddress, uint16_t portNumber, bool bIpv6) {
    if (bIpv6) {
        memset(&this->sa6Struct, 0, sizeof(struct sockaddr_in6));
        this->sa6Struct.sin6_family = AF_INET6;
        this->sa6Struct.sin6_port = htons(portNumber);

        if (inet_pton(AF_INET6, ipAddress, &this->sa6Struct.sin6_addr) <= 0) {
            printf("LOG ERROR: inet_pton ipv6 address.\n");
        }
    } else {
        memset(&this->sa4Struct, 0, sizeof(struct sockaddr_in));
        this->sa4Struct.sin_family = AF_INET;
        this->sa4Struct.sin_port = htons(portNumber);

        if (inet_pton(AF_INET, ipAddress, &this->sa4Struct.sin_addr) <= 0) {
            printf("LOG ERROR: inet_pton ipv4 address.\n");
        }
    }
}

InetAddress::InetAddress(const struct sockaddr_in &sockaddr4)
    : sa4Struct(sockaddr4) {

}

InetAddress::InetAddress(const struct sockaddr_in6 &sockaddr6)
    : sa6Struct(sockaddr6) {

}

void InetAddress::setSockAddrIn6(const struct sockaddr_in6 &addr6) {
    this->sa6Struct = addr6;
}

sa_family_t InetAddress::getAddressFamily() const {
    return this->sa4Struct.sin_family;
}

const struct sockaddr* InetAddress::getSockAddr() const {
    return static_cast<const struct sockaddr*>(static_cast<const void*>(&this->sa6Struct));
}

uint16_t InetAddress::getPortNumber() const {
    return ntohs(this->portNetEndian());
}

uint32_t InetAddress::ipNetEndian() const {
    assert(this->getAddressFamily() == AF_INET);
    return this->sa4Struct.sin_addr.s_addr;
}

uint16_t InetAddress::portNetEndian() const {
    return this->sa4Struct.sin_port;
}

const char* InetAddress::toIpString() const {
    char buf[64] = "";
    size_t size = sizeof(buf);
    if (this->getAddressFamily() == AF_INET) {
        assert(size >= INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &this->sa4Struct.sin_addr, buf, static_cast<socklen_t>(size));
    } else {
        assert(size >= INET6_ADDRSTRLEN);
        inet_ntop(AF_INET6, &this->sa6Struct.sin6_addr, buf, static_cast<socklen_t>(size));
    }

    return buf;
}

const char* InetAddress::toIpPortString() const {
    char buf[64] = "";
    size_t size = sizeof(buf);
    if (this->getAddressFamily() == AF_INET) {
        assert(size >= INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &this->sa4Struct.sin_addr, buf, static_cast<socklen_t>(size));
    } else {
        assert(size >= INET6_ADDRSTRLEN);
        inet_ntop(AF_INET6, &this->sa6Struct.sin6_addr, buf, static_cast<socklen_t>(size));
    }

    size_t end = strlen(buf);
    uint16_t port = ntohs(this->sa4Struct.sin_port);
    assert(size > end);
    snprintf(buf + end, size - end, ":%u", port);

    return buf;
}

static __thread char resolveBuffer[64 * 1024];

bool InetAddress::resolveHostName(const char *hostname, InetAddress *result) {
    assert(result != NULL);

    struct hostent hostent;
    struct hostent *pHostent;
    int herrno = 0;
    memset(&hostent, 0, sizeof(struct hostent));

    int ret = gethostbyname_r(hostname, &hostent, resolveBuffer, sizeof(resolveBuffer), &pHostent, &herrno);
    if (ret == 0 && pHostent != NULL) {
        assert(pHostent->h_addrtype == AF_INET && pHostent->h_length == sizeof(uint32_t));
        result->sa4Struct.sin_addr = *reinterpret_cast<struct in_addr*>(pHostent->h_addr_list[0]);
        return true;
    }

    if (ret)
        printf("LOG ERROR: Cannot resolve hostname %s.\n", hostname);
    return false;
}