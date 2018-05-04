#include "stdafx.h"
#include "p.h"

UINT MenuIdPlug;

BOOL dbPlug::EPChatOutHook(std::string sMessage) //maybe i cant use string?
{
	// Add code
	if (sMessage == "test")
	{
		PluginAPI::queue_structure msgtosend;
		msgtosend.q_type = PluginAPI::_connection_type::cIrc;
		msgtosend.q_irc.messagetype = PluginAPI::sirc_messagetype::e_privatemessage;
		msgtosend.q_irc.nameorchannel = "DonkeyFucker";
		msgtosend.q_irc.smessage = "Greeting and slututations (" + msgtosend.q_irc.nameorchannel + ")";
		API.con_SendData(msgtosend);
	}
	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "Plug[0x%d]: (EPMessage) %s\r\n", API.pl_hInst,sMessage.c_str());

	return FALSE;
}

BOOL dbPlug::IrcBotnetEventMessageHook(PluginAPI::ConnectionType e_connection, PluginAPI::EventType e_type, PluginAPI::ReasonType e_reason, LPCSTR e_dragonbotname, LPCSTR e_whispername, LPCSTR e_message)
{
	if (e_connection == PluginAPI::ConnectionType::IRC)
	{
		switch (e_type)
		{
			case PluginAPI::EventType::Chat:
			{
				API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pIRC[0x%d]: (%s) %s: %s\r\n", API.pl_hInst, e_whispername, e_dragonbotname, e_message);
				break;
			}
			case PluginAPI::EventType::Join:
			{
				PluginAPI::queue_structure msgtosend;
				msgtosend.q_type = PluginAPI::_connection_type::cIrc;
				msgtosend.q_irc.messagetype = PluginAPI::sirc_messagetype::e_privatemessage;
				msgtosend.q_irc.nameorchannel = e_whispername;
				msgtosend.q_irc.smessage = "Greeting and slututations (" + msgtosend.q_irc.nameorchannel + ") Welcome to [" + e_message + "]";
				API.con_SendData(msgtosend);
				API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pIRC[0x%d]: (%s) Joined\r\n", API.pl_hInst, e_whispername);
				break;
			}
			case PluginAPI::EventType::Leave:
			{
				API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pIRC[0x%d]: (%s) Left\r\n", API.pl_hInst, e_whispername);
				break;
			}
			case PluginAPI::EventType::Quit:
			{
				API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pIRC[0x%d]: (%s) Quit\r\n", API.pl_hInst, e_whispername);
				break;
			}
			case PluginAPI::EventType::Whisper:
			{
				API.m_AddChat(API.db_Whisper, DragonBotAPI::myColors::lime, "pIRC[0x%d]: (%s) Whispered: %s\r\n", API.pl_hInst, e_whispername, e_message);
				break;
			}
		}
		return TRUE;
	}
	if (e_connection == PluginAPI::ConnectionType::BotNet)
	{
		switch (e_type)
		{
			case PluginAPI::EventType::Chat:
			{
				API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pBotNet[0x%d]: %s: %s\r\n", API.pl_hInst, e_whispername, e_message);
				break;
			}
			case PluginAPI::EventType::Join:
			{
				API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pBotNet[0x%d]: (%s) Joined\r\n", API.pl_hInst, e_whispername);
				break;
			}
			case PluginAPI::EventType::User:
			{
				API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pBotNet[0x%d]: (%s) Joined\r\n", API.pl_hInst, e_whispername);
				break;
			}
			case PluginAPI::EventType::Leave:
			{
				API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pBotNet[0x%d]: (%s) Left\r\n", API.pl_hInst, e_whispername);
				break;
			}
			case PluginAPI::EventType::Whisper:
			{
				API.m_AddChat(API.db_Whisper, DragonBotAPI::myColors::lime, "pBotNet[0x%d]: (%s) Whispered: %s\r\n", API.pl_hInst, e_whispername, e_message);
				break;
			}
		}
		return TRUE;
	}
	return FALSE;
}


DWORD WINAPI mToggleMenuProc(LPARAM lParam)
{
	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::blue, (char *)"Plug[0x%d]: %s\r\n", API.pl_hInst, "You have clicked the Toggle menu.");
	return 1;
}


BOOL dbPlug::Initialize()
{
	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "Plug[0x%d]: %s\r\n", API.pl_hInst, "Hello World!");
	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "OpenMenuID = [%i]\r\n", API.MenuGetUnusedMenuID(), "Hello World!");
	MenuIdPlug = API.MenuGetUnusedMenuID();
	API.MenuAddMenu(MenuIdPlug, "Greetings", "Toggle", mToggleMenuProc);
	return TRUE;
}

void dbPlug::Terminate()
{
	//Remove the menus
	API.MenuRemove("Greetings", "Toggle", &MenuIdPlug);
	API.MenuRemove("Greetings", "", NULL);
	// Termination code here
	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::red, (char *)"Plug[0x%d]: %s\r\n", API.pl_hInst, "Good Bye World!");
}