#include "SocketUtils.h"
#include "SocketExceptions.h"

#include <string.h>

general::SocketAddress general::SocketUtils::CreateAddress(const Address& address)
{
    return CreateAddress(address.ip, address.port);
}

general::SocketAddress general::SocketUtils::CreateAddress(const std::string& address, const std::string& port)
{
    struct addrinfo hints;
    struct addrinfo* result;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_addr = nullptr;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE; 

    if(getaddrinfo(address.c_str(), port.c_str(), &hints, &result) != 0)
    {
        throw general::tpc_exceptions::socket_exception("getaddrinfo");
    }

    SocketAddress sockaddr(result->ai_addr, result->ai_addrlen, result->ai_family);

    freeaddrinfo(result);

    return sockaddr;
}