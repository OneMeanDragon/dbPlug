#include "stdafx.h"
#include "Hooker.h"


BOOL WINAPI Hooker::EPChatOutHook(std::string sMessage, LPARAM lParam)
{
	return ((Hooker*)lParam)->EPChatOutHook(sMessage);
}

BOOL WINAPI Hooker::IrcBotnetEventMessageHook(PluginAPI::ConnectionType e_connection, PluginAPI::EventType e_type, PluginAPI::ReasonType e_reason, LPCSTR e_dragonbotname, LPCSTR e_whispername, LPCSTR e_message, LPARAM lParam)
{
	return ((Hooker*)lParam)->IrcBotnetEventMessageHook(e_connection, e_type, e_reason, e_dragonbotname, e_whispername, e_message);
}
