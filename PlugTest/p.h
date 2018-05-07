#ifndef _P_H_INCLUDED
#define _P_H_INCLUDED
#pragma once

#include "Hooker.h"

class dbPlug : public Hooker
{
protected:
	BOOL DisconnectedHook(PluginAPI::ConnectionType e_connection);
	BOOL EPChatOutHook(std::string sMessage);
	BOOL IrcBotnetEventMessageHook(PluginAPI::ConnectionType e_connection, PluginAPI::EventMessageData MessageData);

public:
	BOOL Initialize(); // Return FALSE to abort (if this returns FALSE, Terminate isn't called)
	void Terminate(); // Do any termination here
};



#endif // _PLUGIN_H_INCLUDED

