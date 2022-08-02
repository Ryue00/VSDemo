#include "ThreadManager.h"


#include "MsgHandler.h"
#include "Test1MsgHandler.h"
#include "Test2MsgHandler.h"
#include "Thread.h"

void CThreadManager::Init(int threadNumber)
{
	for (int i = 0; i < threadNumber; i++)
	{
		m_vecThreads.push_back(new CThread());
	}
	
	m_vecThreads.push_back(new CThread(g_pTest1MsgHandler));
	m_vecThreads.push_back(new CThread(g_pTest2MsgHandler));
	std::vector<CThread*>::iterator it = m_vecThreads.begin();
	for (; it != m_vecThreads.end(); ++it)
	{
		CThread* pThread = (*it);
		pThread->Start();
	}

	std::vector<CThread*>::iterator it1 = m_vecThreads.begin();
	for (; it1 != m_vecThreads.end(); ++it1)
	{
		CThread* pThread = (*it1);
		pThread->Wait();
	}
	
}

CThreadManager::~CThreadManager()
{
}
