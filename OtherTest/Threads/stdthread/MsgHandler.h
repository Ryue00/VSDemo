#pragma once
#include <deque>

#include "messagepipe/I_MessagePipe.h"
#include "messagepipe/Inner_Protocol.h"

class IRunable
{
public:
    virtual void Run() = 0;
    virtual void Stop() = 0;
};

class CRunable : public IRunable
{
public:
    CRunable();

    virtual void Run() override;
    virtual void Stop() override;
    virtual void OnProcess() = 0;
    virtual void OnWait() = 0;

private:
    bool m_isStop;
};

class CMsgHandler
    : public CRunable
{
public:
    CMsgHandler() = default;
    ~CMsgHandler() = default;
    virtual void OnProcess();
    virtual void OnWait();

    virtual void OnRecvInnerMsg(InnerMessage innerMsg) = 0;
    virtual void OnTestMsg() = 0;
private:
    void ProcessInnerMsg();
protected:
    IMessagePipe* m_pMsgPipe;
	// std::mutex m_mutex;
    std::deque<int> m_testData;
	std::condition_variable m_condvar;
};

