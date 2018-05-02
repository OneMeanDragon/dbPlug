#include "PluginManager.h"

void PluginManager::AddPluginAddress(std::string PluginHandle, PluginIface PluginStructureAddress)
{
	PluginIterator = PluginMap.find(PluginHandle);
	if (PluginIterator != PluginMap.end()) { //Plug already exists. unload the inbound
		FreeLibrary(PluginStructureAddress.PluginLoadLib);
		return;
	} 
	PluginMap.insert(std::pair<std::string, PluginIface>(PluginHandle, PluginStructureAddress));
}
void PluginManager::RemovePluginAddress(std::string PluginHandle)
{
	PluginIterator = PluginMap.find(PluginHandle);
	if (PluginIterator == PluginMap.end()) { return; } //plug dosent exist.
	FreeLibrary((PluginMap[PluginHandle]).PluginLoadLib); //Unload the plug
	PluginMap.erase(PluginHandle);
}

void PluginManager::AddPlugin(LPCSTR PluginPath)
{
	//Does this plug already exist if so return.
	PluginIterator = PluginMap.find(std::string(PluginPath));
	if (PluginIterator != PluginMap.end()) {
		return;
	}//Plug already exists. unload the inbound

	PluginIface ThisPlug;

	ThisPlug.PluginLoadLib = LoadLibrary(PluginPath);
	if (ThisPlug.PluginLoadLib == NULL) { return; } //Failed to load (Fail = NULL) (likely cause = dll not found.)
	ThisPlug.AddChat = MasterInterface.AddChat;
	ThisPlug.Botnet_we_disconnected = MasterInterface.Botnet_we_disconnected;
	ThisPlug.CHANNEL_TITLE = MasterInterface.CHANNEL_TITLE;
	ThisPlug.myApis = MasterInterface.myApis;

	ThisPlug.irc_we_disconnected = MasterInterface.irc_we_disconnected;
	ThisPlug.MainInstance = MasterInterface.MainInstance;
	ThisPlug.MainWindow = MasterInterface.MainWindow;
	ThisPlug.RTB_CHAT = MasterInterface.RTB_CHAT;
	ThisPlug.RTB_WHISPER = MasterInterface.RTB_WHISPER;
	ThisPlug.SEND_CHAT = MasterInterface.SEND_CHAT;
	ThisPlug.USER_LIST = MasterInterface.USER_LIST;
	ThisPlug.version = MasterInterface.version;

	//We have the interface, now export it to the plug.
	PluginMain plugMain = (PluginMain)GetProcAddress(ThisPlug.PluginLoadLib, "SetInterfaceInformation");
	if (plugMain == NULL) { //Failed to get the interface function, unload now.
		FreeLibrary(ThisPlug.PluginLoadLib);
		return;
	}
	if (plugMain) { //Successful
		plugMain(&ThisPlug);
	}
	this->AddPluginAddress(std::string(PluginPath), ThisPlug);
}

void PluginManager::RemovePlugin(LPCSTR PluginPath)
{
	this->RemovePluginAddress(std::string(PluginPath));
}

void PluginManager::SendEPMessage(LPCSTR Message)
{
	PluginIterator = PluginMap.begin();
	while (PluginIterator != PluginMap.end())
	{
		if (PluginIterator->second._EPChatOut != NULL) {
			PluginIterator->second._EPChatOut(std::string(Message), PluginIterator->second.EPChatHookParam);
		}
		PluginIterator++;
	}
}

void PluginManager::SendEventMessagesHook(ConnectionType e_connection, EventType e_type, ReasonType e_reason, LPCSTR e_dragonbotname, LPCSTR e_whispername, LPCSTR e_message)
{
	PluginIterator = PluginMap.begin();
	while (PluginIterator != PluginMap.end())
	{
		if (PluginIterator->second.IrcBotnetEventMessagesHook != NULL) {
			PluginIterator->second.IrcBotnetEventMessagesHook(e_connection, e_type, e_reason, e_dragonbotname, e_whispername, e_message, PluginIterator->second.IrcBotnetEventsHookParam);
		}
		PluginIterator++;
	}
}