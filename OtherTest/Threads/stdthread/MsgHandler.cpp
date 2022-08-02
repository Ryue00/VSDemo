#include "MsgHandler.h"


#include <chrono>
#include <iostream>
CRunable::CRunable()
    : m_isStop(false)
{
}

void CRunable::Run()
{
    while (!m_isStop)
    {
        // 处理线程业务
        OnProcess();

        // 处理结束等待
        OnWait();
    }
}

void CRunable::Stop()
{
    m_isStop = true;
}

void CMsgHandler::OnProcess()
{
    // 处理内部线程消息
    ProcessInnerMsg();

	// test 收发
    OnTestMsg();
}

void CMsgHandler::OnWait()
{
}

void CMsgHandler::ProcessInnerMsg()
{
    InnerMessage innerMsg;
    // while (m_pMsgPipe->Recv(-1, -1, innerMsg))
    // {
    //     OnRecvInnerMsg(innerMsg);
    // }
}
