#pragma once

#include <iostream>
#include <memory>
#include <netdb.h>
#include <string.h>

namespace general
{
    struct Address
    {
        std::string ip;
        std::string port; 
    };

    class SocketAddress
    {
        sockaddr m_sockaddr;
        socklen_t m_socklen;
        int m_family;

    public:
        SocketAddress() = default;
        SocketAddress(sockaddr* sockaddr, socklen_t socklen, int family)
        {
            memcpy(&m_sockaddr, sockaddr, socklen);
            m_socklen = socklen;
            m_family = family;
        }
 
        const sockaddr& GetSockaddr() const { return m_sockaddr; }

        socklen_t GetSocketLen() const { return m_socklen; }

        int GetFamily() const { return m_family; }
    };
}
