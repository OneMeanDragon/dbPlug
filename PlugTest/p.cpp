#include "stdafx.h"
#include "p.h"

UINT MenuToggleIDPlug;
UINT MenuDebugIDPlug;

bool debugging_text = false;
bool greetings = true;

BOOL dbPlug::DisconnectedHook(PluginAPI::ConnectionType e_connection)
{
	if (debugging_text) {
		std::string m_out = "";
		switch (e_connection)
		{
			case PluginAPI::ConnectionType::BotNet:
			{
				m_out = "Botnet";
				break;
			}
			case PluginAPI::ConnectionType::IRC:
			{
				m_out = "IRC";
				break;
			}
		}
		API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::yellow, "pIRC[0x%d]: (%s) has disconnected.\r\n", API.pl_hInst, m_out.c_str());
	}
	return TRUE;
}

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
	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "Plug[0x%d]: (EPMessage) %s\r\n", API.pl_hInst, sMessage.c_str());

	return FALSE;
}

BOOL dbPlug::IrcBotnetEventMessageHook(PluginAPI::ConnectionType e_connection, PluginAPI::EventMessageData MessageData)
{
	if (e_connection == PluginAPI::ConnectionType::IRC)
	{
		switch (MessageData.t_Event)
		{
			case PluginAPI::EventType::Chat:
			{
				/*
					MessageData.e_data.m_user = user thats chatting
					MessageData.e_data.m_channel = channel name
					MessageData.e_data.m_message = chat text
				*/
				
				if (debugging_text) {
					API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pIRC[0x%d]: (%s) %s: %s\r\n", API.pl_hInst, MessageData.e_data.m_channel.c_str(), MessageData.e_data.m_user.c_str(), MessageData.e_data.m_message.c_str());
				}
				break;
			}
			case PluginAPI::EventType::Join:
			{
				/*
					MessageData.e_data.m_onlinename = dragonbots online name
					MessageData.e_data.m_user = the user that joined
					MessageData.e_data.m_channel = channel name
				*/

				if (greetings) {
					if (MessageData.e_data.m_onlinename != MessageData.e_data.m_user) {
						PluginAPI::queue_structure msgtosend;
						msgtosend.q_type = PluginAPI::_connection_type::cIrc;
						msgtosend.q_irc.messagetype = PluginAPI::sirc_messagetype::e_privatemessage;
						msgtosend.q_irc.nameorchannel = MessageData.e_data.m_user;
						msgtosend.q_irc.smessage = "Greeting and slututations (" + msgtosend.q_irc.nameorchannel + ") Welcome to [" + MessageData.e_data.m_channel + "]";
						API.con_SendData(msgtosend);
					}
				}
				if (debugging_text) {
					API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pIRC[0x%d]: [%s] (%s) has joined\r\n", API.pl_hInst, MessageData.e_data.m_channel.c_str(), MessageData.e_data.m_user.c_str());
				}
				break;
			}
			case PluginAPI::EventType::Leave:
			{
				/*
					(ReasonType::IRCKicked, e_dragonbotname = kicker, e_whispername = the kicked, (again channel, should be the reason for kick))
					(At some point ill update the EventTypes to carry Kicked / Banned) for now make due
					MessageData.e_data.m_channel = channel
					MessageData.e_data.m_user = the user that quit
					MessageData.e_data.m_reason = the reason they left (or kicked, or banned <these will be in their own event soon>)
				*/

				if (debugging_text) {
					API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pIRC[0x%d]: [%s] (%s) Left [%s]\r\n", API.pl_hInst, MessageData.e_data.m_channel.c_str(), MessageData.e_data.m_user.c_str(), MessageData.e_data.m_reason.c_str());
				}
				break;
			}
			case PluginAPI::EventType::Kicked:
			{
				/*
					MessageData.e_data.m_channel.c_str() = channel
					MessageData.e_data.m_kicker.c_str() = user doing the kick
					MessageData.e_data.m_kicked.c_str() = user that was kicked
					MessageData.e_data.m_reason.c_str() = the reason they were kicked
				*/

				if (debugging_text) {
					API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::yellow, "pIRC[0x%d]: [%s] (%s) has kicked (%s) [%s]\r\n", API.pl_hInst, MessageData.e_data.m_channel.c_str(), MessageData.e_data.m_kicker.c_str(), MessageData.e_data.m_kicked.c_str(), MessageData.e_data.m_reason.c_str());
				}
				break;
			}
			case PluginAPI::EventType::Banned:
			{
				/*
					MessageData.e_data.m_channel.c_str() = channel
					MessageData.e_data.m_kicker.c_str() = user doing the ban
					MessageData.e_data.m_kicked.c_str() = user that was banned
					MessageData.e_data.m_reason.c_str() = the reason they were banned
				*/

				if (debugging_text) {
					API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::yellow, "pIRC[0x%d]: [%s] (%s) has Banned (%s) [%s]\r\n", API.pl_hInst, MessageData.e_data.m_channel.c_str(), MessageData.e_data.m_kicker.c_str(), MessageData.e_data.m_kicked.c_str(), MessageData.e_data.m_reason.c_str());
				}
				break;
			}
			case PluginAPI::EventType::Quit:
			{
				/*
					<Sometimes we get back our own message when we quit with reason as well.>
					<Quit message has no channel, if they quit you remove them from everywhere you see them its an IRC thing>
					MessageData.e_data.m_user = the user that quit
					MessageData.e_data.m_reason = the reason they quit (which currently is blank)
				*/

				if (debugging_text) {
					API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "pIRC[0x%d]: (%s) Quit: [%s]\r\n", API.pl_hInst, MessageData.e_data.m_user.c_str(), MessageData.e_data.m_reason.c_str());
				}
				break;
			}
			case PluginAPI::EventType::Whisper:
			{
				/*
					<Yes we can chaeck if the message is comeing from us, irc allows us to whisper ourselves.>
					MessageData.e_data.m_user = the user that whispered
					MessageData.e_data.m_message = whispered message
				*/

				if (debugging_text) {
					API.m_AddChat(API.db_Whisper, DragonBotAPI::myColors::lime, "pIRC[0x%d]: (%s) Whispered: %s\r\n", API.pl_hInst, MessageData.e_data.m_user.c_str(), MessageData.e_data.m_message.c_str());
				}
				break;
			}
			case PluginAPI::EventType::Nick: //(Not added yet)
			{
				/*
					DragonBot internally keeps track of who we are via, MessageData.e_data.m_onlinename
					MessageData.e_data.m_user = the user original nick
					MessageData.e_data.m_message = the user new nickname
				*/
				if (debugging_text) {
					API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::gray, "pIRC[0x%d]: (%s) is now knowen as: %s\r\n", API.pl_hInst, MessageData.e_data.m_user.c_str(), MessageData.e_data.m_message.c_str());
				}
				break;
			}
		}
		return TRUE;
	}
	//TODO: Add Botnet to the new structure message
	return TRUE;
}


DWORD WINAPI mToggleMenuProc(LPARAM lParam)
{
	greetings = !greetings;
	if (greetings)
	{
		API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::blue, (char *)"Plug[0x%d]: %s\r\n", API.pl_hInst, "Greetings are now Enabled.");
	}
	else {
		API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::blue, (char *)"Plug[0x%d]: %s\r\n", API.pl_hInst, "Greetings are now Disabled.");
	}
	return 1;
}

DWORD WINAPI mDubugMenuProc(LPARAM lParam)
{
	debugging_text = !debugging_text;
	if (debugging_text)
	{
		API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::blue, (char *)"Plug[0x%d]: %s\r\n", API.pl_hInst, "Debugging data is now Enabled.");
	}
	else {
		API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::blue, (char *)"Plug[0x%d]: %s\r\n", API.pl_hInst, "Debugging data is now Disabled.");
	}
	return 1;
}

BOOL dbPlug::Initialize()
{
	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "Plug[0x%d]: %s\r\n", API.pl_hInst, "Hello World!");
	MenuDebugIDPlug = API.MenuGetUnusedMenuID();
	API.MenuAddMenu(MenuDebugIDPlug, "Greetings", "Debuging", mDubugMenuProc);
	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "OpenMenuID = [%i]\r\n", MenuDebugIDPlug, "Hello World!");

	MenuToggleIDPlug = API.MenuGetUnusedMenuID();
	API.MenuAddMenu(MenuToggleIDPlug, "Greetings", "Toggle", mToggleMenuProc);
	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::lime, "OpenMenuID = [%i]\r\n", MenuToggleIDPlug, "Hello World!");
	return TRUE;
}

void dbPlug::Terminate()
{
	//Remove the menus
	API.MenuRemove("Greetings", "Debuging", &MenuDebugIDPlug);
	API.MenuRemove("Greetings", "Toggle", &MenuToggleIDPlug);
	API.MenuRemove("Greetings", "", NULL);
	// Termination code here
	API.m_AddChat(API.db_Chat, DragonBotAPI::myColors::red, (char *)"Plug[0x%d]: %s\r\n", API.pl_hInst, "Good Bye World!");
}