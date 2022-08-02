#pragma once
#include <thread>
#include <vector>

#include "Thread.h"


class CMsgHandler;

class CThreadManager
{
public:
	void Init(int threadNumber = 10);
	~CThreadManager();
private:
	std::vector<CThread*> m_vecThreads;
};

