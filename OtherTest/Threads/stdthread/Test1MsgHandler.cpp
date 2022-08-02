#include "Test1MsgHandler.h"

#include <chrono>
#include <iostream>

#include "SharedData.h"

INSTANCE_IMPLEMENTATION_DEFAULT(CTest1MsgHandler)

void CTest1MsgHandler::OnRecvInnerMsg(InnerMessage innerMsg)
{
    switch (innerMsg.m_msgType)
    {
    case MSG_BUSINESS_PB_MSG:
    {

    }
    break;
    }
}

void CTest1MsgHandler::OnTestMsg()
{
    g_pSharedData.SendMsgProcess();
}
