#pragma once

#include "TCPSocketWrapper.h"
#include "IClient.h"
#include <string>

namespace general
{
    struct Configuration
    {
        std::string m_Name;
        int m_Period;
        SocketAddress m_ServerAddress;
    };

    class TcpClient : public IClient
    {
        Configuration m_Configuration;
        bool m_Stop { false };

        std::string CreateMessage() const;
        void SendMessage(std::string&& message);

    public:
        TcpClient(const Configuration& configuration) 
            : m_Configuration(configuration) 
        { };

        void StartClient() override;
    };
}