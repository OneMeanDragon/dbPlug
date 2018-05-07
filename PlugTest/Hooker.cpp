#include "stdafx.h"
#include "Hooker.h"


BOOL WINAPI Hooker::EPChatOutHook(std::string sMessage, LPARAM lParam)
{
	return ((Hooker*)lParam)->EPChatOutHook(sMessage);
}

BOOL WINAPI Hooker::IrcBotnetEventMessageHook(PluginAPI::ConnectionType e_connection, PluginAPI::EventMessageData MessageData, LPARAM lParam)
{
	return ((Hooker*)lParam)->IrcBotnetEventMessageHook(e_connection, MessageData);
}

BOOL WINAPI Hooker::DisconnectedHook(PluginAPI::ConnectionType e_connection, LPARAM lParam)
{
	return ((Hooker*)lParam)->DisconnectedHook(e_connection);
}
