#include "MessagePipe.h"
#include <map>
#include "MsgPipeManager.h"

//////////////////////////////////////////////////////////////////////////
CMessagePipe::CMessagePipe(const char* pName, int msgPoolSize, int id /*= 0*/)
{

}

int CMessagePipe::GetId()
{
	return 0;
}

unsigned CMessagePipe::GetMsgCount()
{
	return 0;
}

void CMessagePipe::SetId(int id)
{
}

bool CMessagePipe::IsOpen()
{
	return false;
}

bool CMessagePipe::IsBlock()
{
	return false;
}

void CMessagePipe::SetCanProcess(bool canProcess)
{
}

void CMessagePipe::SetName(const char* pName)
{
}

const char* CMessagePipe::GetName()
{
	return nullptr;
}

void CMessagePipe::SetMsgPoolSize(int msgPoolSize)
{
}

void CMessagePipe::SetObserver(IMessagePipeObserver* pObserver)
{
}

void CMessagePipe::Clear()
{
}

bool CMessagePipe::Open(bool canProcess)
{
	return false;
}

bool CMessagePipe::Open()
{
	return false;
}

bool CMessagePipe::Close()
{
	return false;
}

bool CMessagePipe::Send(int destPipe, int msgType)
{
	return false;
}

bool CMessagePipe::Send(int destPipe, InnerMessage& msg)
{
	return false;
}

bool CMessagePipe::PushMsg(InnerMessage& msg)
{
	return false;
}

bool CMessagePipe::Recv(int srcPipe, int msgType, InnerMessage& recvMsg)
{
	return false;
}

bool CMessagePipe::PopMsg(int srcPipe, int msgType, InnerMessage& recvMsg)
{
	return false;
}

bool CMessagePipe::WaitMsg(unsigned milliseconds)
{
	return false;
}

CMessagePipe::~CMessagePipe()
{

}
CMessagePipe* CMessagePipe::CreateNew(const char* pName, int msgPoolSize, int id /*= 0*/)
{
	CMessagePipe* pNew = new CMessagePipe(pName, msgPoolSize, id);
	return pNew;
}
