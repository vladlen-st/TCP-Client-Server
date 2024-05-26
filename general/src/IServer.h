#pragma once 

#include <memory>

#include "ILogger.h"

namespace general
{
    class IServer
    {
    protected:
        virtual std::unique_ptr<ILogger> CreateLogger() const = 0;
        
    public:
        virtual void StartServer(int backlog) = 0;

        virtual ~IServer() = default;
    };
}