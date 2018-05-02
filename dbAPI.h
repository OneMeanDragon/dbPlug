#ifndef _DBPLUGIN_H_INCLUDED
#define _DBPLUGIN_H_INCLUDED
#pragma once

#include <windows.h>
#include <string>

#define PLUG_CFG "DATA\\PLUG.CFG"


namespace dbAPI
{
	enum _myColors {
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
	typedef enum _connection_type {
		cBotnet,
		cIrc,
		cPlug
	};
	typedef enum sirc_messagetype {
		e_privatemessage,
		e_notice,
		e_mode
	};
	typedef struct irc_queue {
		std::string nameorchannel;
		std::string smessage;
		sirc_messagetype messagetype;
	};
	typedef struct botnet_queue {
		std::string smessage;
	};
	typedef struct queue_structure {
		_connection_type q_type;
		irc_queue q_irc;
		botnet_queue q_botnet;
	};

	typedef void(WINAPI* _AppendText)(HWND RichEdit, COLORREF Color, const char* Fmt, ...);

	typedef int(WINAPI* _GetValue)(std::string file_name, std::string key_search_string, std::string &string_out, std::string default_value);
	struct config_interface {
		_GetValue GetValue;
	};
	typedef void(WINAPI* _mySendMessage)(queue_structure sMessage);
	struct connection_mis {
		_mySendMessage SendData;
	};
	struct _dragonbot_api_a {
		config_interface myConfig;
		connection_mis myFunctions;
	};

	typedef BOOL(WINAPI* _EditProcChatOut)(std::string sMessage);
	typedef BOOL(WINAPI* _IrcBotnetEventMessagesHook)(ConnectionType e_connection, EventType e_type, ReasonType e_reason,
		LPCSTR e_dragonbotname, LPCSTR e_whispername, LPCSTR e_message);

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
		_AppendText AddChat;

		/* ---- Config ---- */
		_dragonbot_api_a myApis;
		/* ---- EditProc Messages ---- */
		_EditProcChatOut _EPChatOut;
		//EditProcHook _EPChatOut;
		_IrcBotnetEventMessagesHook _IrcBotnetEventMessagesOut;
	};
}


BOOL WINAPI PluginMain(dbAPI::PluginInformation* InterfaceData);
// Export as "SetInterfaceInformation"

#endif // _BCPLUGIN_H_INCLUDED