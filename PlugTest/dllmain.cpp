// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "p.h"

#define kill_command "/kill testplug"

// Global objects
dbAPIM API;
dbPlug PluginInstance;
static BOOL Initialized;

HINSTANCE hInst;

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD Reason, LPVOID lpReserved)
{
    switch (Reason)
    {
    case DLL_PROCESS_ATTACH:
		hInst = hInstance;
		DisableThreadLibraryCalls(hInstance);
		return TRUE;
    case DLL_PROCESS_DETACH:
		if (Initialized)
			
			API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::red, (char *)"Plug: %s\r\n", "Good Bye World!");
			PluginInstance.Terminate();

		return TRUE;
	default:
		__assume(0); // No other cases exist thanks to DisableThreadLibraryCalls
	}
}

BOOL WINAPI PluginMain(PluginAPI::PluginInformation* InterfaceData)
{

	ZeroMemory(&API, sizeof(API));

	API.db_hInst					= InterfaceData->MainInstance;
	API.db_hWnd						= InterfaceData->MainWindow;
	API.db_Chat						= InterfaceData->RTB_CHAT;
	API.db_Whisper					= InterfaceData->RTB_WHISPER;
	API.db_Listview					= InterfaceData->USER_LIST;
	API.db_ChannelTitle				= InterfaceData->CHANNEL_TITLE;
	API.db_SendChat					= InterfaceData->SEND_CHAT;
	API.db_irc_we_disconnected		= InterfaceData->irc_we_disconnected;
	API.db_botnet_we_disconnected	= InterfaceData->Botnet_we_disconnected;
	//API.db_version					= InterfaceData->version; //Some reason a value held in std::string dosent cross in this transfer of info.
	API.m_AddChat					= InterfaceData->AddChat;
	API.s_Config					= InterfaceData->Config;

	PluginInstance.m_PluginInstance = hInst;
	
	InterfaceData->EPChatHook = &Hooker::EPChatOutHook;
	InterfaceData->EPChatHookParam = (LPARAM)&PluginInstance;

	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "Plug: %s\r\n", "Hello World!");
	return Initialized = PluginInstance.Initialize();
}