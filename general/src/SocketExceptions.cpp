#include "SocketExceptions.h"

general::tpc_exceptions::socket_exception::socket_exception(const std::string& what)
{
    m_ErrorMessage = what + " - errno: " + std::to_string(errno);
}

const char* general::tpc_exceptions::socket_exception::what() const throw()
{
    return m_ErrorMessage.c_str();
}

