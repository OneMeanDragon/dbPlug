#include "stdafx.h"
#include "p.h"


BOOL dbPlug::EPChatOutHook(std::string sMessage) //maybe i cant use string?
{
	// Add code
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
				API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pIRC[0x%d]: %s: %s\r\n", API.pl_hInst, e_whispername, e_message);
				break;
			}
			case PluginAPI::EventType::Join:
			{
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

BOOL dbPlug::Initialize()
{
	// Initialization code here
	return TRUE;
}

void dbPlug::Terminate()
{
	// Termination code here
}