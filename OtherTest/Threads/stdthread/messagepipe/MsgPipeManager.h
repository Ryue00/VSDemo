#pragma once
#include <vector>

class IMessagePipe;
class CMsgPipeManager
{
	typedef std::vector<IMessagePipe* > VEC_PIPE;

public:
	IMessagePipe* CreatePipe(const char* pName, int msgPoolSize);
	// 进程退出时，管道消息同时也要释放掉
	bool DeletePipe(const int pipeId);
	void Clear();
	IMessagePipe* GetPipe(int pipeId);
	int GetPipeSize();

	// inline functions
public:
	bool IsValidPipe(int pipeId) { return GetPipe(pipeId) != NULL; }

private:
	int m_pipeId;
	VEC_PIPE m_vecPipe;
};

#define g_pMsgPipeMgr	Singleton<CMsgPipeManager>::GetInstance() 

