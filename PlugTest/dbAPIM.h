#ifndef _DBAPIM_H_INCLUDED
#define _DBAPIM_H_INCLUDED
#pragma once

#include "DBPlugin.h"
#include "settings.h"

class dbAPIM
{
	friend BOOL WINAPI PluginMain(PluginAPI::PluginInformation* InterfaceData);

private:
	//PluginAPI::AppendText					m_AddChat;
	PluginAPI::config_interface				s_Config;
//	typedef void(WINAPI* AppendText)(HWND RichEdit, COLORREF Color, const char* Fmt, ...);
public:
	//DWORD m_Revision; // Revision number
	HINSTANCE	pl_hInst;
	HINSTANCE	db_hInst;
	HWND		db_hWnd;
	HWND		db_Listview;
	HWND		db_Chat;
	HWND		db_Whisper;
	HWND		db_ChannelTitle;
	HWND		db_SendChat;
	BOOL		db_irc_we_disconnected;
	BOOL		db_botnet_we_disconnected;

	std::string db_version;



	PluginAPI::AppendText					m_AddChat;

	int ConfigGetValue(std::string file_name, std::string key_search_string, std::string &string_out, std::string default_value)
	{
		s_Config.GetValue(file_name, key_search_string, string_out, default_value);
	}
};

#endif // _DBAPIM_H_INCLUDED