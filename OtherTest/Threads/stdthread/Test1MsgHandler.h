#pragma once
#include <cstddef>


#include "CommonMacro.h"
#include "MsgHandler.h"

class CTest1MsgHandler
	:	public CMsgHandler
{
	INSTANCE_DECLARATION(CTest1MsgHandler)

public:
	void OnRecvInnerMsg(InnerMessage innerMsg) override;
	virtual void OnTestMsg()override;
	
};

#define g_pTest1MsgHandler CTest1MsgHandler::GetInstance()