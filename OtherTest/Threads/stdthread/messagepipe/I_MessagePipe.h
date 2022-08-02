#pragma once

// �����ڲ���Ϣ��С
#define	SIZEOF(x)			(sizeof(x))
#define	STRLEN(x)			(strlen(x)+1)

const int PIPE_ANY			= -1;	// ����ͨ��
const int MSG_ANY			= -1;	// ������Ϣ

// ��Ϣ�ܵ��۲���
class IMessagePipeObserver
{
public:
    // ���ܵ��쳣
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
	// ���31���ַ�
	virtual void SetName(const char* pName = "") = 0;
	virtual const char* GetName() = 0;
	// ������Ϣ�صĴ�С
	virtual void SetMsgPoolSize(int msgPoolSize) = 0;
    // ���ù۲���
    virtual void SetObserver(IMessagePipeObserver* pObserver) = 0;

public:
	// �������
	virtual void Clear() = 0;
	// ����Ϣͨ�������ظ�����(ͨ��id�����޸�)
	virtual bool Open(bool canProcess) = 0;
    virtual bool Open() = 0;
	// �ر���Ϣͨ�������ظ�����
	virtual bool Close() = 0;
	// ���Ϳ���Ϣ��ָ��ͨ��
	virtual bool Send(int destPipe, int msgType) = 0;
	// ������Ϣ��ָ��ͨ��
	virtual bool Send(int destPipe, InnerMessage& msg) = 0;
	// ��Ϣ���
	virtual bool PushMsg(InnerMessage& msg) = 0;
	// ����ָ��ͨ��(������ͨ��)������ָ����Ϣ(��������Ϣ)
	virtual bool Recv(int srcPipe, int msgType, InnerMessage& recvMsg) = 0;
	// ����ָ��ͨ��(������ͨ��)������ָ����Ϣ(��������Ϣ)
	virtual bool PopMsg(int srcPipe, int msgType, InnerMessage& recvMsg) = 0;
	// �����Ϣ�����Ƿ�����Ϣ����û����ȴ�
	virtual bool WaitMsg(unsigned int milliseconds) = 0;
};
