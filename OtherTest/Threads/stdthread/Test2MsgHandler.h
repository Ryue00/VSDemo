#pragma once
#include <cstddef>
#include <mutex>


#include "CommonMacro.h"
#include "MsgHandler.h"

// 初始化资源锁
// std::mutex resource_mutex;

// 初始化资源 专用
// std::once_flag resource_flag;

class CTest2MsgHandler
	:	public CMsgHandler
{
	INSTANCE_DECLARATION(CTest2MsgHandler)

// public:
// 	static CTest2MsgHandler* GetInstance()
// 	{
// 		// 双重检验锁定 可能引起 data race，恶性条件竞争
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
// 		// C++ 11 初始化保护共享数据
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
