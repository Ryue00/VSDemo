#pragma once
#include <deque>
#include <list>
#include <mutex>

#include "Inner_Protocol.h"
#include "I_MessagePipe.h"
#include "ObjectPool.h"

#define PIPE_BLOCK_NUM			100			// 表示管道阻塞
#define PIPE_EXCEPTION_NUM		10000		// 需要关闭管道

/////////////////////////////////////////////////////////////////////////////////////////////////
class CMessagePipe
	: public IMessagePipe
{
	enum
	{
		STATE_OK,
		STATE_CLOSED
	};
public:
	static CMessagePipe* CreateNew(const char* pName, int msgPoolSize, int id = 0);
	virtual ~CMessagePipe();

protected:
	CMessagePipe(const char* pName, int msgPoolSize, int id = 0);

	/*
	 * 继承接口类{@Link IMessagePipe}
	 */
public:
	int GetId() override;
	unsigned GetMsgCount() override;
	void SetId(int id) override;
	bool IsOpen() override;
	bool IsBlock() override;
	void SetCanProcess(bool canProcess) override;
	void SetName(const char* pName) override;
	const char* GetName() override;
	void SetMsgPoolSize(int msgPoolSize) override;
	void SetObserver(IMessagePipeObserver* pObserver) override;
	void Clear() override;
	bool Open(bool canProcess) override;
	bool Open() override;
	bool Close() override;
	bool Send(int destPipe, int msgType) override;
	bool Send(int destPipe, InnerMessage& msg) override;
	bool PushMsg(InnerMessage& msg) override;
	bool Recv(int srcPipe, int msgType, InnerMessage& recvMsg) override;
	bool PopMsg(int srcPipe, int msgType, InnerMessage& recvMsg) override;
	bool WaitMsg(unsigned milliseconds) override;

protected:
	int m_id;
	// CEvent m_msgEvent;
	// CCriticalSection m_critSec;

	// 消息池,
	CInnerMsgPool* m_pInnerMsgPool;
	std::deque<InnerMessage*> m_setMsg;
	IMessagePipeObserver* m_pObserver;  // 管道观察者
};

