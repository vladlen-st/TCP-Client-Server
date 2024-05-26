#pragma once

#include "IServer.h"
#include "TCPSocketWrapper.h"
#include "MessageQueue.h"

namespace general
{
    class TcpServer : public IServer
    {
        std::shared_ptr<TCPSocketWrapper> m_ServerSocket;
        std::unique_ptr<ILogger> m_Logger;
        MessageQueue m_MessageQueue;

        void StartReceivingMessage(int socketFd);
        void StartLogging();

        std::unique_ptr<ILogger> CreateLogger() const override;
    public:
        TcpServer(const Address& address) 
            : m_Logger( CreateLogger() ), m_ServerSocket( TCPSocketWrapper::CreateServerSocket(address) )
        { }

        void StartServer(int backlog) override;
    };
}