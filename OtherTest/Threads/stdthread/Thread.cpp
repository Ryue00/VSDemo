#include "Thread.h"


#include <iostream>
#include <thread>
#include "MsgHandler.h"

CThread::CThread(IRunable* run)
	:m_run(run)
{
}

CThread::~CThread()
{
	// if (m_thread.joinable())
	// {
	// 	m_thread.join();
	// }
}

void CThread::Start()
{
	std::thread thread(ThreadProc, static_cast<void*>(this));
	// std::thread thread1(&CThread::Wait,this, static_cast<void*>(this));
	m_thread = std::move(thread);
	m_threadId = m_thread.get_id();
	
}

void CThread::Run()
{
	if (!m_run)
	{
		std::cout << "线程的handler为空" << std::endl;
		return;
	}
	m_run->Run();
}

void CThread::Wait()
{
	m_thread.join();
}

void* CThread::ThreadProc(void* arg)
{
	auto* thread = static_cast<CThread*>(arg);
	thread->Run();
	return nullptr;
}
