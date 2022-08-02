#include "MsgPipeManager.h"

// #include "utils/CommonMacro.h"
#include "I_MessagePipe.h"
#include "MessagePipe.h"

INSTANCE_IMPLEMENTATION(CMsgPipeManager)
//////////////////////////////////////////////////////////////////////////
CMsgPipeManager::CMsgPipeManager(void)
: m_pipeId(0)
{
}

CMsgPipeManager::~CMsgPipeManager(void)
{
	Clear();
}

IMessagePipe* CMsgPipeManager::CreatePipe(const char* pName, int msgPoolSize)
{
	// LOG_SYS_INFO("PipeName=%s", pName);
	// 新建通道
	IMessagePipe* pMsgPipe = CMessagePipe::CreateNew(pName, msgPoolSize);
	// CHECKF(pMsgPipe);
	pMsgPipe->SetId(++m_pipeId);
	m_vecPipe.push_back(pMsgPipe);

	return pMsgPipe;
}

bool CMsgPipeManager::DeletePipe( const int pipeId )
{	
	IMessagePipe* pMsgPipe = NULL;
	for (VEC_PIPE::iterator it = m_vecPipe.begin(); it != m_vecPipe.end(); ++it)
	{
		pMsgPipe = *it;
		if (!pMsgPipe)
		{
			continue;
		}

		if (pMsgPipe->GetId() == pipeId)
		{
            delete *it;
			m_vecPipe.erase(it);
            // LOG_SYS_NOTICE("DeletePipe pipeId=%d success.", pipeId);
			return true;
		}
	}
	return false;
}

void CMsgPipeManager::Clear()
{
	VEC_PIPE::iterator it = m_vecPipe.begin();
	for (; it != m_vecPipe.end(); ++it)
	{
		delete *it;
	}

	m_vecPipe.clear();
}

IMessagePipe* CMsgPipeManager::GetPipe(int pipeId)
{
	VEC_PIPE::iterator it = m_vecPipe.begin();
	for (; it != m_vecPipe.end(); ++it)
	{
		IMessagePipe* pPipe = (*it);
		if (!pPipe)
		{
			continue;
		}

		if (pPipe->GetId() == pipeId)
		{
			return pPipe;
		}
	}

	return NULL;
}

int CMsgPipeManager::GetPipeSize()
{
	return m_pipeId;
}
