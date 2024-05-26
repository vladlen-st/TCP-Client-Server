#pragma once 

class IClient
{
public:
    virtual void StartClient() = 0;
    virtual ~IClient() = default;
};