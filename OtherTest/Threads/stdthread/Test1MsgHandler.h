#pragma once
#include <cstddef>

#include "SharedData.h"
#include "MsgHandler.h"
class CTest1MsgHandler
	:	public CMsgHandler
{

public:
	void OnRecvInnerMsg(InnerMessage innerMsg) override;
	virtual void OnTestMsg()override;
	
};

#define g_pTest1MsgHandler Singleton<CTest1MsgHandler>::GetInstance() 