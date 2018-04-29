#include "stdafx.h"
#include "Hooker.h"


BOOL WINAPI Hooker::EPChatOutHook(std::string sMessage, LPARAM lParam)
{
	return ((Hooker*)lParam)->EPChatOutHook(sMessage);
}

