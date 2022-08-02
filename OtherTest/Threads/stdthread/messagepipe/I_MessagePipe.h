#pragma once

// 计算内部消息大小
#define	SIZEOF(x)			(sizeof(x))
#define	STRLEN(x)			(strlen(x)+1)

const int PIPE_ANY			= -1;	// 任意通道
const int MSG_ANY			= -1;	// 任意消息

// 消息管道观察者
class IMessagePipeObserver
{
public:
    // 当管道异常
    virtual void OnPipeException() = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
class InnerMessage;
class IMessagePipe
{
public:
	IMessagePipe			() {}
	virtual ~IMessagePipe	() {}

public:
	virtual int GetId() = 0;
	virtual unsigned GetMsgCount() = 0;
	virtual void SetId(int id) = 0;
	virtual bool IsOpen() = 0;
	virtual bool IsBlock() = 0;
	virtual void SetCanProcess(bool canProcess) = 0;
	// 最多31个字符
	virtual void SetName(const char* pName = "") = 0;
	virtual const char* GetName() = 0;
	// 设置消息池的大小
	virtual void SetMsgPoolSize(int msgPoolSize) = 0;
    // 设置观察者
    virtual void SetObserver(IMessagePipeObserver* pObserver) = 0;

public:
	// 清除数据
	virtual void Clear() = 0;
	// 打开消息通道，可重复调用(通道id不能修改)
	virtual bool Open(bool canProcess) = 0;
    virtual bool Open() = 0;
	// 关闭消息通道，可重复调用
	virtual bool Close() = 0;
	// 发送空消息到指定通道
	virtual bool Send(int destPipe, int msgType) = 0;
	// 发送消息到指定通道
	virtual bool Send(int destPipe, InnerMessage& msg) = 0;
	// 消息入队
	virtual bool PushMsg(InnerMessage& msg) = 0;
	// 接收指定通道(或任意通道)发来的指定消息(或任意消息)
	virtual bool Recv(int srcPipe, int msgType, InnerMessage& recvMsg) = 0;
	// 弹出指定通道(或任意通道)发来的指定消息(或任意消息)
	virtual bool PopMsg(int srcPipe, int msgType, InnerMessage& recvMsg) = 0;
	// 检查消息队列是否有消息，如没有则等待
	virtual bool WaitMsg(unsigned int milliseconds) = 0;
};
