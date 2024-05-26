#include "TcpServer.h"
#include <thread>
#include <future>
#include <sstream>

void general::TcpServer::StartReceivingMessage(int socketFd)
{
    auto acceptSocket = general::TCPSocketWrapper::CreateClientSocket(socketFd);
    
    char buff[1024] = { 0 };

    int bytes { 1 };

    std::ostringstream oss;

    while((bytes = acceptSocket->Recv(buff, 1024)) > 0)
    {
        oss << buff;
        memset(buff, '\0', sizeof(buff));
    }
     
    m_MessageQueue.PushMessage(oss.str());

    acceptSocket->Close();
}

void general::TcpServer::StartLogging()
{
    while(true)
    {
        std::string message = m_MessageQueue.PopMessage();

        m_Logger->LogMessage(message);
    }
}

void general::TcpServer::StartServer(int backlog)
{
    m_ServerSocket->Listen(backlog);

    std::thread loggingThread(&TcpServer::StartLogging, this);

    while(true)
    {
        int newSocketFd = m_ServerSocket->Accept();
        if(newSocketFd <= 0)
        {
            std::cout << "Error accepting\n";
            continue;
        }

        std::async(std::launch::async, &general::TcpServer::StartReceivingMessage, this, newSocketFd);
    }

    loggingThread.join();
}

std::unique_ptr<ILogger> general::TcpServer::CreateLogger() const
{
    return std::unique_ptr<FileLogger>(new FileLogger("log.txt"));
}
