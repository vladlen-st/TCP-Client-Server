#include "../general/src/TCPSocketWrapper.h"
#include "../general/src/TcpClient.h"

int main(int argc, char** argv)
{
    if(argc < 4)
    {
        std::cout << "To few arguments\n";
        return -1;
    }

    int period { 0 };

    try
    {
        int port = std::stoi(argv[2]);
        if(port <= 10000 || port >= 65535)
        {
            throw std::invalid_argument("Invalid port");
        }

        period = std::stoi(argv[3]);
        if(period <= 0)
        {
            throw std::invalid_argument("Invalid period");
        }
    }
    catch(const std::invalid_argument& ex) 
    {
        std::cout << "Invalid argument was passed: " << ex.what() << std::endl;
        return -1;
    }
    catch(...)
    {
        std::cout << "Something went wrong\n";
        return -1;
    }

    general::Address adr;
    adr.ip = "127.0.0.1";
    adr.port = argv[2];

    general::Configuration configuration;
    configuration.m_Name = argv[1];
    configuration.m_Period = period;
    configuration.m_ServerAddress = general::SocketUtils::CreateAddress(adr.ip, adr.port);

    std::unique_ptr<IClient> client;

    client = std::unique_ptr<general::TcpClient>(new general::TcpClient(configuration));

    client->StartClient();

    return 0;
}