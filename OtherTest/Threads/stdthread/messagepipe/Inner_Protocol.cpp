#include "Inner_Protocol.h"
#include "I_MessagePipe.h"

//////////////////////////////////////////////////////////////////////////
// InnerMessage
InnerMessage::InnerMessage(int msgType /*= 0*/)
{
	InitData();
	this->m_msgType = msgType;
}

InnerMessage::~InnerMessage()
{
	delete(this->m_pMsgBody);
	this->m_pMsgBody = nullptr;
}

InnerMessage& InnerMessage::operator=(const InnerMessage& other)
{
	this->m_srcPipe = other.m_srcPipe;
	SetData(other.m_msgType, other.m_msgBodySize, other.m_pMsgBody);
	return *this;
}

InnerMessage::InnerMessage(int msgType, int bodySize, const char* data)
{
	InitData();
	SetData(msgType, bodySize, data);
}





void InnerMessage::InitData()
{
	m_srcPipe = 0;
	m_msgType = 0;
	m_msgBodySize = 0;
	m_pMsgBody = NULL;
}
#define MAX_MESSAGE_SIZE 100
template<typename T>
void safe_delete(T*& pT)
{
	if (NULL != pT) {
		delete pT;
		pT = NULL;
	}
}
void InnerMessage::SetData(const int msgType, const int msgBodySize, const char* pMsgBody)
{
	if (msgBodySize > MAX_MESSAGE_SIZE)
	{
		
		if (msgBodySize > 10 * MAX_MESSAGE_SIZE)
		{
			return;
		}
	}

	this->m_msgType = msgType;
	this->m_msgBodySize = msgBodySize;
	if (msgBodySize > 0)
	{
		// CHECK(pMsgBody);
		if (this->m_pMsgBody)
		{
			// 删除之前保存的数据
			safe_delete(this->m_pMsgBody);
		}
		this->m_pMsgBody = new char[msgBodySize];
		memset(this->m_pMsgBody, 0, msgBodySize);
		memcpy(this->m_pMsgBody, pMsgBody, msgBodySize);
	}
}

//////////////////////////////////////////////////////////////////////////
// CInnerMsgPool
CInnerMsgPool::CInnerMsgPool(const char* pName /*= ""*/, int poolSize /*= 0*/)
	: CObjectPool(pName)
{
	if (poolSize > 0)
	{
		Init(poolSize);
	}
}

CInnerMsgPool::~CInnerMsgPool()
{

}

//////////////////////////////////////////////////////////////////////////
//
bool SendInnerMsg(int destPipe, int innerMsgType, char* pNetMsg)
{
	return true;
}

