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
        // �����߳�ҵ��
        OnProcess();

        // ��������ȴ�
        OnWait();
    }
}

void CRunable::Stop()
{
    m_isStop = true;
}

void CMsgHandler::OnProcess()
{
    // �����ڲ��߳���Ϣ
    ProcessInnerMsg();

	// test �շ�
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
