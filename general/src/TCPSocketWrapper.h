#pragma once

#include <iostream>

#include "SocketUtils.h"
#include "SocketExceptions.h"

namespace general
{
    class TCPSocketWrapper
    {
        int m_SocketFd;
        
        TCPSocketWrapper();
        TCPSocketWrapper(int socketFd);
        TCPSocketWrapper(const SocketAddress& socketAddress);
        void Bind(const SocketAddress& socketAddress) const;

    public:
        static std::shared_ptr<TCPSocketWrapper> CreateServerSocket(const Address& address);

        static std::shared_ptr<TCPSocketWrapper> CreateClientSocket();
        static std::shared_ptr<TCPSocketWrapper> CreateClientSocket(int socketFd);

        void Listen(int backlog) const;
        void Connect(const SocketAddress& serverAddress) const;
        int Accept() const;
        int Recv(void* outBuffer, size_t bufferSize) const;
        int Send(void* inBuffer, size_t bufferSize) const;
        void Close() const;
        
        int GetSocketFd() const { return m_SocketFd; } 

        ~TCPSocketWrapper() {  Close(); }
    };
}