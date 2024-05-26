#pragma once

#include <iostream>
#include <fstream>
#include "ILogger.h"

class FileLogger : public ILogger
{
    std::ofstream m_Ofstream{ };
    std::string m_FilePath;

public:
    explicit FileLogger(const std::string& filePath) :
        m_FilePath(filePath)
    { };
    explicit FileLogger(std::string&& filePath) : 
        m_FilePath(filePath)
    { };

    void LogMessage(const std::string& message) override;
};