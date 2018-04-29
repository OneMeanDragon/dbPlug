#ifndef _HOOKER_H_INCLUDED
#define _HOOKER_H_INCLUDED
#pragma once

#include "dbAPIM.h"


class Hooker
{
	friend BOOL WINAPI PluginMain(PluginAPI::PluginInformation* InterfaceData);

	friend class dbAPIM;

private:
	static BOOL WINAPI EPChatOutHook(std::string sMessage, LPARAM lParam);

protected:
	HINSTANCE m_PluginInstance;

	//typedef BOOL(WINAPI*_EditProcChatOut)(std::string sMessage);
	virtual BOOL EPChatOutHook(std::string sMessage) = 0;

};

#endif // _HOOKER_H_INCLUDED