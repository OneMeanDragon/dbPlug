#ifndef _P_H_INCLUDED
#define _P_H_INCLUDED
#pragma once

#include "Hooker.h"

class dbPlug : public Hooker
{
protected:
	BOOL EPChatOutHook(std::string sMessage);
	BOOL IrcBotnetEventMessageHook(PluginAPI::ConnectionType e_connection, PluginAPI::EventType e_type, PluginAPI::ReasonType e_reason, LPCSTR e_dragonbotname, LPCSTR e_whispername, LPCSTR e_message);

public:
	BOOL Initialize(); // Return FALSE to abort (if this returns FALSE, Terminate isn't called)
	void Terminate(); // Do any termination here
};



#endif // _PLUGIN_H_INCLUDED

