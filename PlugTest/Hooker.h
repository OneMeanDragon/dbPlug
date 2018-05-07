#ifndef _HOOKER_H_INCLUDED
#define _HOOKER_H_INCLUDED
#pragma once

#include "dbAPIM.h"


class Hooker
{
	friend BOOL WINAPI PluginMain(PluginAPI::PluginInformation* InterfaceData);

	friend class dbAPIM;

private:
	static BOOL WINAPI DisconnectedHook(PluginAPI::ConnectionType e_connection, LPARAM lParam);
	static BOOL WINAPI EPChatOutHook(std::string sMessage, LPARAM lParam);
	static BOOL WINAPI IrcBotnetEventMessageHook(PluginAPI::ConnectionType e_connection, PluginAPI::EventMessageData MessageData, LPARAM lParam);

protected:
	HINSTANCE m_PluginInstance;

	virtual BOOL DisconnectedHook(PluginAPI::ConnectionType e_connection) = 0;
	virtual BOOL EPChatOutHook(std::string sMessage) = 0;
	virtual BOOL IrcBotnetEventMessageHook(PluginAPI::ConnectionType e_connection, PluginAPI::EventMessageData MessageData) = 0;

};

#endif // _HOOKER_H_INCLUDED