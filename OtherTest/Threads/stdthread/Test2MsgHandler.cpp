#include "Test2MsgHandler.h"

#include <chrono>
#include <iostream>

#include "SharedData.h"

INSTANCE_IMPLEMENTATION_DEFAULT(CTest2MsgHandler)

void CTest2MsgHandler::OnRecvInnerMsg(InnerMessage innerMsg)
{
    switch (innerMsg.m_msgType)
    {
    case MSG_BUSINESS_PB_MSG:
    {

    }
    break;
    }
}

void CTest2MsgHandler::OnTestMsg()
{
    g_pSharedData.RecvMsgProcess();
}
