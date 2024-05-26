#include "../general/src/TCPSocketWrapper.h"
#include "../general/src/TcpServer.h"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "To few arguments\n";
        return -1;
    }

    try
    {
        int port = std::stoi(argv[1]);
        if(port <= 10000 || port >= 65535)
        {
            throw std::invalid_argument("Invalid port");
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

    general::Address address;
    address.ip = "127.0.0.1";
    address.port = argv[1];

    std::unique_ptr<general::IServer> server;

    try
    {
        server = std::unique_ptr<general::TcpServer>(new general::TcpServer(address));
    }
    catch(const general::tpc_exceptions::socket_exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }
    catch(...)
    {
        std::cout << "Something went wrong\n";
        return -1;
    }

    server->StartServer(50);

    return 0;
}