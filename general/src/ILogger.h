#pragma once

class ILogger
{
public:
    virtual void LogMessage(const std::string& message) = 0;
    virtual ~ILogger() = default;
};