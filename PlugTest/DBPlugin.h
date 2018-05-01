#ifndef _BDPLUGIN_H_INCLUDED
#define _BDPLUGIN_H_INCLUDED
#pragma once

#include <windows.h>

namespace DragonBotAPI
{
	typedef enum _myColors {
		black = 0x000000L,
		green = 0x008000L,
		silver = 0xc0c0c0L,
		lime = 0x00ff00L,
		seagreen = 0x32CD32L,
		gray = 0x808080L,
		darkslategray = 0x2F4F4FL,
		olive = 0x008080L,
		white = 0xffffffL,
		yellow = 0x00CDCDL,
		maroon = 0x000080L,
		navy = 0x800000L,
		red = 0x0000eeL,
		blue = 0xCD5F3AL,
		purple = 0x800080L,
		teal = 0x808000L,
		fuchsia = 0xff00ffL,
		aqua = 0xffff00L,
		deeppurple = 0xDB7093L,
		orange = yellow
	} myColors;
}

namespace PluginAPI
{
	enum ConnectionType
	{
		IRC,
		BotNet
	};
	enum EventType
	{
		Join,
		Leave,
		Quit,
		Chat,
		User,
		Whisper
	};
	enum ReasonType
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
	// Hooks:
	typedef BOOL(WINAPI* EditProcHook)(std::string sMessage, LPARAM lParam);
	typedef BOOL(WINAPI* IrcBotnetEventMessagesHook)(ConnectionType e_connection, EventType e_type, ReasonType e_reason,
		LPCSTR e_dragonbotname, LPCSTR e_whispername, LPCSTR e_message, LPARAM lParam);

	// From DragonBot in the PluginInterfaceData Struct
	typedef void(WINAPI* AppendText)(HWND RichEdit, COLORREF Color, const char* Fmt, ...);
	typedef int(WINAPI* GetValue)(std::string file_name, std::string key_search_string, std::string &string_out, std::string default_value);
	struct config_interface {
		GetValue GetValue;
	};


	/* ---- INTERFACE ---- */
	struct PluginInformation {
		HINSTANCE PlugInstance;
		HINSTANCE MainInstance;
		HWND MainWindow;
		HWND USER_LIST;
		HWND RTB_CHAT;
		HWND RTB_WHISPER;
		HWND CHANNEL_TITLE;
		HWND SEND_CHAT;
		BOOL irc_we_disconnected;
		BOOL Botnet_we_disconnected;

		/* ---- Bots full version string from main ---- */
		std::string version;

		/* ---- shared functions ---- */
		//	_PingTime PingFunc;
		AppendText AddChat;

		/* ---- Config ---- */
		config_interface Config;

		/* ---- EditProc Messages ---- */
		EditProcHook EPChatHook;
		LPARAM EPChatHookParam;
		IrcBotnetEventMessagesHook IBEventMessageHook;
		LPARAM IBEventHookParam;
	};

}

BOOL WINAPI PluginMain(PluginAPI::PluginInformation* Information);

#endif // _BDPLUGIN_H_INCLUDED