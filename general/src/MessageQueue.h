#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace general
{
    class MessageQueue
    {
        std::queue<std::string> m_MessageQueue;
        std::mutex m_Mutex;
        std::condition_variable m_CondVar;
    public:
        void PushMessage(std::string&& message);
        std::string PopMessage();
    };
}