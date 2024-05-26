#include "FileLogger.h"
#include <thread>
#include <mutex>

void FileLogger::LogMessage(const std::string& message)
{
    if(!m_Ofstream.is_open())
    {
        m_Ofstream.open(m_FilePath);
    }

    m_Ofstream << message << std::endl;
}