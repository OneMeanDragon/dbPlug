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
	PluginAPI::_dragonbot_api_a				m_myApis;
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
		return m_myApis.myConfig.GetValue(file_name, key_search_string, string_out, default_value);
	}

	void con_SendData(PluginAPI::queue_structure sMessage)
	{
		m_myApis.myFunctions.SendData(sMessage);
	}

	UINT MenuGetUnusedMenuID(void)
	{
		return m_myApis.myMenu.GetNewID();
	}

	BOOL MenuAddMenu(UINT wMenuID, LPCSTR sThisPluginMenu, LPCSTR sSubMenu, PluginAPI::PluginMenuProc mFunctionAddress)
	{
		return m_myApis.myMenu.AddMenu(wMenuID, sThisPluginMenu, sSubMenu, mFunctionAddress);
	}
	//	typedef BOOL(WINAPI* RemoveMenuID)(LPCSTR sPlugMenuName, LPCSTR sPlugSubMenuName, LPUINT pMenuID);
	BOOL MenuRemove(LPCSTR sPlugMenuName, LPCSTR sPlugSubMenuName, LPUINT pMenuID)
	{
		return m_myApis.myMenu.RemoveMenu(sPlugMenuName, sPlugSubMenuName, pMenuID);
	}
};

#endif // _DBAPIM_H_INCLUDED