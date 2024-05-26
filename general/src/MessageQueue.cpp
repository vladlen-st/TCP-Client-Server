#include "MessageQueue.h"

void general::MessageQueue::PushMessage(std::string &&message)
{
    std::lock_guard<std::mutex> locked(m_Mutex);
    m_MessageQueue.push(message);
    m_CondVar.notify_one();
}

std::string general::MessageQueue::PopMessage()
{
    std::unique_lock<std::mutex> locked(m_Mutex);
    
    m_CondVar.wait(locked, [&](){ return !m_MessageQueue.empty(); });

    auto message = m_MessageQueue.back();
    m_MessageQueue.pop();

    return message;
}