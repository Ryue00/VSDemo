#pragma once
#include <cstddef>
#include <mutex>


#include "CommonMacro.h"
#include "MsgHandler.h"

// ��ʼ����Դ��
// std::mutex resource_mutex;

// ��ʼ����Դ ר��
// std::once_flag resource_flag;

class CTest2MsgHandler
	:	public CMsgHandler
{
	INSTANCE_DECLARATION(CTest2MsgHandler)

// public:
// 	static CTest2MsgHandler* GetInstance()
// 	{
// 		// ˫�ؼ������� �������� data race��������������
// 		// if (nullptr == s_pInstance)
// 		// {
// 		// 	std::lock_guard<std::mutex> lk(resource_mutex);
// 		// 	if (nullptr == s_pInstance)x`
// 		// 	{
// 		// 		s_pInstance = new CTest2MsgHandler();
// 		// 	}
// 		// }
// 		// return s_pInstance;
//
// 		// C++ 11 ��ʼ��������������
// 		// std::call_once(resource_flag, []() {s_pInstance = new CTest2MsgHandler(); });
// 		// return s_pInstance;
// 	}
// protected:
// 	CTest2MsgHandler();
// public:
// 	virtual ~CTest2MsgHandler();
// protected:
// 	static CTest2MsgHandler* s_pInstance;
public:
	virtual void OnRecvInnerMsg(InnerMessage innerMsg);
	virtual void OnTestMsg()override;
};

#define g_pTest2MsgHandler CTest2MsgHandler::GetInstance()
