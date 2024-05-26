#pragma once

#include <string>
#include <exception>

namespace general
{

    namespace tpc_exceptions
    {
        class socket_exception : public std::exception
        {
            std::string m_ErrorMessage;

        public:
            explicit socket_exception(const std::string& what);

            const char* what() const throw() override;
        };
    }

}