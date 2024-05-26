#include "TCPSocketWrapper.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace general;

std::shared_ptr<TCPSocketWrapper> TCPSocketWrapper::CreateServerSocket(const Address& address)
{
    auto socketAddress = SocketUtils::CreateAddress(address.ip, address.port);

    struct make_shared_enabler : public TCPSocketWrapper 
    {
        make_shared_enabler(const SocketAddress& socketAddress) 
            : TCPSocketWrapper(socketAddress) {}
    };

    auto serverSocket = std::make_shared<make_shared_enabler>(socketAddress);
    serverSocket->Bind(socketAddress);

    return serverSocket;
}

std::shared_ptr<TCPSocketWrapper> TCPSocketWrapper::CreateClientSocket()
{
    struct make_shared_enabler : public TCPSocketWrapper {};
    return std::make_shared<make_shared_enabler>();
}

std::shared_ptr<TCPSocketWrapper> TCPSocketWrapper::CreateClientSocket(int socketFd)
{
    struct make_shared_enabler : public TCPSocketWrapper 
    {
        make_shared_enabler(int socketFd) 
            : TCPSocketWrapper(socketFd) {}
    };

    return std::make_shared<make_shared_enabler>(socketFd);
}

TCPSocketWrapper::TCPSocketWrapper()
{
    if((m_SocketFd = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
    {
        throw tpc_exceptions::socket_exception("creating socket");
    }
}

TCPSocketWrapper::TCPSocketWrapper(int socketFd) 
    : m_SocketFd(socketFd)
{ }

TCPSocketWrapper::TCPSocketWrapper(const SocketAddress& socketAddress) 
{
    if((m_SocketFd = socket(socketAddress.GetFamily(), SOCK_STREAM, 0)) <= 0)
    {
        throw tpc_exceptions::socket_exception("creating socket");
    }
}

void TCPSocketWrapper::Bind(const SocketAddress& socketAddress) const
{
    if(bind(m_SocketFd, &socketAddress.GetSockaddr(), socketAddress.GetSocketLen()) < 0)
    {
        throw tpc_exceptions::socket_exception("binding socket");
    }
}

void TCPSocketWrapper::Listen(int backlog) const
{
    if(listen(m_SocketFd, backlog) < 0)
    {
        throw tpc_exceptions::socket_exception("listening socket");
    }
}

void TCPSocketWrapper::Connect(const SocketAddress& serverAddress) const
{
    if(connect(m_SocketFd, &serverAddress.GetSockaddr(), serverAddress.GetSocketLen()) < 0)
    {
        throw tpc_exceptions::socket_exception("connecting socket");
    }
}

int TCPSocketWrapper::Accept() const
{
    int sockFd;
    if((sockFd = accept(m_SocketFd, nullptr, nullptr)) < 0)
    {
        throw tpc_exceptions::socket_exception("accepting socket");
    }

    return sockFd;
}

int TCPSocketWrapper::Recv(void* outBuffer, size_t bufferSize) const
{
    int bytes = recv(m_SocketFd, outBuffer, bufferSize - 1, 0);

    if(bytes < 0)
    {
        throw tpc_exceptions::socket_exception("receiving data socket");
    }

    return bytes;
}

int TCPSocketWrapper::Send(void* inBuffer, size_t bufferSize) const
{
    int bytes = send(m_SocketFd, inBuffer, bufferSize, 0);

    if(bytes < 0)
    {
        throw tpc_exceptions::socket_exception("sending data socket");
    }

    return bytes;
}

void TCPSocketWrapper::Close() const
{
    close(m_SocketFd);
}