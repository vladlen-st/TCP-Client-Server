#include "TcpClient.h"
#include "SocketExceptions.h"

#include <sstream>
#include <iomanip>
#include <thread>

std::string general::TcpClient::CreateMessage() const
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;

    oss << std::put_time(&tm, "[%Y-%m-%d %H:%M:%S.%MS]");
    oss << " " << m_Configuration.m_Name;

    return oss.str();
}

void general::TcpClient::SendMessage(std::string&& message)
{
    try
    {
        auto socket = TCPSocketWrapper::CreateClientSocket();

        socket->Connect(m_Configuration.m_ServerAddress);

        socket->Send(&message[0], message.size());

        socket->Close();
    }
    catch(const tpc_exceptions::socket_exception& ex)
    {
        std::cout << ex.what() << std::endl;
        m_Stop = true;
    }
    catch(...)
    {
        std::cout << "Something went wrong\n";
        m_Stop = true;
    }
}

void general::TcpClient::StartClient()
{
    while(!m_Stop)
    {
        SendMessage( CreateMessage() );
        
        std::this_thread::sleep_for(std::chrono::seconds(m_Configuration.m_Period));
    }
}