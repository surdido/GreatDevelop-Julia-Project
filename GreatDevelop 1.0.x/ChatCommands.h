// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.1								# //
// ================================================== //

#include "Logger.h"
#include "User.h"
#include "GMSystem.h"

#ifndef CHAT_H
#define CHAT_H


class cChat
{
public:
	cChat();
	~cChat();  
	bool ChatDataSend(LPOBJ gObj, LPBYTE aRecv);													   
	void MessageLog(int Type, sColor LogColor, sLogType LogType, LPOBJ gObj, char* Msg,...);	   
	void Message(int Type, int Index, char* Msg,...);		  
	void Message(int Index, char* Msg,...);		  
	void MessageAllLog(int Type, int Type2, sColor LogColor, sLogType LogType, LPOBJ gObj, char* Msg,...);
	void MessageAll(int Type, int Type2, char *Sender, char* Msg,...);		
	
	//void MassLog(LPOBJ gObj, LPBYTE Message);

private:			
	void AntiInject(char* message); 											  
	bool CheckCommand(LPOBJ gObj, int Config, 
						cGmSystem::Commands Command, int NeedZen, 
						int NeedPcPoint, int NeedWCoin,
						int NeedLvl, int Filled, 
						int CheckPlayer, char *CommandName,
						char *CommandUsage, char *Msg);
	void TakeCommand(LPOBJ gObj, int NeedZen, int NeedPcPoint, int NeedWCoin, char *CommandName);
	void MsgSrv(char *Sender,char* Message, int Type2);	 

	bool GgCommand(LPOBJ gObj, char* Msg);		 
	bool VosklCommand(LPOBJ gObj, char* Msg);
	bool TraceCommand(LPOBJ gObj, char *Msg);
	bool SummonCommand(LPOBJ gObj, char *Msg);
	bool DiskCommand(LPOBJ gObj, char* Msg);  
	bool Move(LPOBJ gObj, char *Msg);
	bool PostCommand(LPOBJ gObj, char *Msg);	  
	bool BanPostCommand(LPOBJ gObj, char *Msg); 
	bool UnBanPostCommand(LPOBJ gObj, char *Msg); 
	bool BanAccCommand(LPOBJ gObj, char *Msg);  
	bool UnBanAccCommand(LPOBJ gObj, char *Msg); 
	bool BanCharCommand(LPOBJ gObj, char *Msg);  
	bool UnBanCharCommand(LPOBJ gObj, char *Msg);	
	bool TimeCommand(LPOBJ gObj, char *Msg);	  
	bool SetChar(LPOBJ gObj, char *Msg);	 
	bool ReloadCommand(LPOBJ gObj, char *Msg);
	bool OnlineCommand(LPOBJ gObj, char *Msg);
	bool StatusCommand(LPOBJ gObj, char *Msg); 
	bool GmoveCommand(LPOBJ gObj, char *Msg);	
	bool SkinCommand(LPOBJ gObj, char *Msg);	
	bool DropCommand(LPOBJ gObj, char *Msg);	
	bool SetPKCommand(LPOBJ gObj, char *Msg);	
	bool LevelCommand(LPOBJ gObj, char *Msg);	
	bool PKClearCommand(LPOBJ gObj, char *Msg);	 
	bool WareCommand(LPOBJ gObj, char *Msg);	 
	bool AddCommands(LPOBJ gObj, char *Msg, int Type); 	  
	bool SetZenCommand(LPOBJ gObj, char *Msg);
};

extern cChat Chat;


#endif