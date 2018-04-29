#include "stdafx.h"
#include "p.h"


BOOL dbPlug::EPChatOutHook(std::string sMessage) //maybe i cant use string?
{
	// Add code
	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "Plug: (EPMessage) %s\r\n", sMessage.c_str());

	return FALSE;
}

BOOL dbPlug::Initialize()
{
	// Initialization code here
	return TRUE;
}

void dbPlug::Terminate()
{
	// Termination code here
}