#ifndef _HOOKER_H_INCLUDED
#define _HOOKER_H_INCLUDED
#pragma once

#include "dbAPIM.h"

/*
typedef enum ConnectionType
{
IRC,
BotNet
};
typedef enum EventType
{
Join,
Leave,
Quit,
Chat,
Whisper
};
typedef enum ReasonType
{
NotSpecified,
IRCKicked,
IRCBanned,
IRCParted,
IRCQuit,
BotnetKicked,
BotnetAdminKicked,
BotnetProtocolKicked,
BotnetNetworkKicked,
BotnetDisconnected,
Unknowen
};
typedef BOOL(WINAPI* _IrcBotnetEventMessagesHook)(ConnectionType e_connection, EventType e_type, ReasonType e_reason,
LPCSTR e_dragonbotname, LPCSTR e_whispername, LPCSTR e_message, LPARAM lParam);
*/

class Hooker
{
	friend BOOL WINAPI PluginMain(PluginAPI::PluginInformation* InterfaceData);

	friend class dbAPIM;

private:
	static BOOL WINAPI EPChatOutHook(std::string sMessage, LPARAM lParam);
	static BOOL WINAPI IrcBotnetEventMessageHook(PluginAPI::ConnectionType e_connection, PluginAPI::EventType e_type, PluginAPI::ReasonType e_reason, LPCSTR e_dragonbotname, LPCSTR e_whispername, LPCSTR e_message, LPARAM lParam);

protected:
	HINSTANCE m_PluginInstance;

	virtual BOOL EPChatOutHook(std::string sMessage) = 0;
	virtual BOOL IrcBotnetEventMessageHook(PluginAPI::ConnectionType e_connection, PluginAPI::EventType e_type, PluginAPI::ReasonType e_reason, LPCSTR e_dragonbotname, LPCSTR e_whispername, LPCSTR e_message) = 0;

};

#endif // _HOOKER_H_INCLUDED