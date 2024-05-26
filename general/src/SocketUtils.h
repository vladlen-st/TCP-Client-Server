#pragma once

#include "SocketAddress.h"
#include "FileLogger.h"

namespace general
{    
    class SocketUtils
    {
    public:
        static SocketAddress CreateAddress(const Address& address);
        static SocketAddress CreateAddress(const std::string& address, const std::string& port);
    };
}