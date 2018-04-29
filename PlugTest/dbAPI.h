#ifndef _DBPLUGIN_H_INCLUDED
#define _DBPLUGIN_H_INCLUDED
#pragma once

#include <windows.h>
#include <string>

#define PLUG_CFG "DATA\\PLUG.CFG"


namespace dbAPI
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
	typedef void(WINAPI* _AppendText)(HWND RichEdit, COLORREF Color, const char* Fmt, ...);

	typedef int(WINAPI* _GetValue)(std::string file_name, std::string key_search_string, std::string &string_out, std::string default_value);
	struct _config_interface {
		_GetValue GetValue;
	};

	typedef BOOL(WINAPI*_EditProcChatOut)(std::string sMessage);

	/* ---- INTERFACE ---- */
	struct PluginInformation {
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
		_AppendText AddChat;

		/* ---- Config ---- */
		_config_interface Config;
		/* ---- EditProc Messages ---- */
		_EditProcChatOut _EPChatOut;
	};
}


BOOL WINAPI PluginMain(dbAPI::PluginInformation* InterfaceData);
// Export as "SetInterfaceInformation"

#endif // _BCPLUGIN_H_INCLUDED