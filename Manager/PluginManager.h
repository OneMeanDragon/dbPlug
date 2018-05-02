#ifndef _PLUGINMANAGER_H_INCLUDED
#define _PLUGINMANAGER_H_INCLUDED
#pragma once

#include "includes.h"
#include <map>
#include <utility>

class PluginManager {
private:
	std::map<std::string, PluginIface> PluginMap;
	std::map<std::string, PluginIface>::iterator PluginIterator;
	void AddPluginAddress(std::string PluginHandle, PluginIface PluginStructureAddress);
	void RemovePluginAddress(std::string PluginHandle);
public:
	void AddPlugin(LPCSTR PluginPath);
	void RemovePlugin(LPCSTR PluginPath);
	//EditProcHook
	void SendEPMessage(LPCSTR Message);
	//SendEventMessagesHook (IRC - Botnet)
	void SendEventMessagesHook(ConnectionType e_connection, EventType e_type, ReasonType e_reason, LPCSTR e_dragonbotname, LPCSTR e_whispername, LPCSTR e_message);
};

#endif // _PLUGINMANAGER_H_INCLUDED
