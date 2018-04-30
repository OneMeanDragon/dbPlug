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
	//std::map<std::string, DWORD> PluginHandleMap;
	//std::map<std::string, DWORD>::iterator PluginHandleIterator;
	void AddPluginAddress(std::string PluginHandle, PluginIface PluginStructureAddress);
	void RemovePluginAddress(std::string PluginHandle);
public:
	void AddPlugin(LPCSTR PluginPath);
	void RemovePlugin(LPCSTR PluginPath);
	void SendEPMessage(LPCSTR Message); //EditProcHook
};

#endif // _PLUGINMANAGER_H_INCLUDED
