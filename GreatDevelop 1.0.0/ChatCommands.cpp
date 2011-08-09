// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.0								# //
// ================================================== //

#include "StdAfx.h"
#include "ChatCommands.h"
#include "User.h"
#include "Utilits.h"
#include "Logger.h"
#include "PCPoint.h"
#include "SQL.h"
#include "MoveReq.h"
#include "IpBlock.h"
#include "DropSystem.h"
cChat Chat;
						 
cChat::cChat()
{
}

cChat::~cChat()
{
}
char Messages[1024];

void cChat::AntiInject(char* message)
{
	for (UINT i = 0; i <= strlen(message); i++)
	{                          						   
		if(message[i] == '\'')		  
		{
			message[i] = ' ';
		}
	}
}

bool cChat::ChatDataSend(LPOBJ gObj,LPBYTE aRecv)
{
	//////////////////////////////////////////////////////////////////
	//				Пример добавления команды /test					//	
	//////////////////////////////////////////////////////////////////
	// 1)В файле ChatCommands.h добавить функцию команды:			//
	//		  bool TestCommand(LPOBJ gObj, char*msg);				//
	//			(параметры в скобках можно изменять)				//
	//																//
	// 2)Ниже добавить проверку на команду и запуск её функции		//
	// 		  														//
	// if (!memcmp(&aRecv[13],"/test",strlen("/test")))				//
	//	bResult = TestCommand(gObj,(char*)aRecv+13+strlen("/test"));//
	//																//
	// 3)Добавить и заполнить саму функцию команды					//
	// 																//
	// bool cChat::TestCommand(LPOBJ gObj, char*msg)				//
	// {															// 
	//   ...														//
	//   return true; // если надо чтобы протокол потом выходил 	//
	//                // из функции и не давал запускаться функции	//
	//				  // чата находящегося в ГС						//
	//				  // и false, если этого делать не надо			//
	// }															// 
	//////////////////////////////////////////////////////////////////
	
	AntiInject((char*)aRecv+13);

	bool bResult = false;		 
	if (!memcmp(&aRecv[13],"/gg",strlen("/gg")))
			bResult = GgCommand(gObj,(char*)aRecv+13+strlen("/gg"));	 
	 if (!memcmp(&aRecv[13],"!",strlen("!")))
		bResult = VosklCommand(gObj,(char*)aRecv+13+strlen("!"));	
	if (!memcmp(&aRecv[13],"/trace",strlen("/trace")))
			bResult = TraceCommand(gObj,(char*)aRecv+13+strlen("/trace"));	 
	if (!memcmp(&aRecv[13],"/disconnect",strlen("/disconnect")))
			bResult = DiskCommand(gObj,(char*)aRecv+13+strlen("/disconnect"));	  
	if (!memcmp(&aRecv[13],"/track",strlen("/track")))
			bResult = SummonCommand(gObj,(char*)aRecv+13+strlen("/track"));	
	if (!memcmp(&aRecv[13],"/move",strlen("/move")))
			bResult = Move(gObj,(char*)aRecv+13+strlen("/move"));	
	if (!memcmp(&aRecv[13],"/warp",strlen("/warp")))
			bResult = Move(gObj,(char*)aRecv+13+strlen("/warp"));	 
	if (!memcmp(&aRecv[13],"/level",strlen("/level")))
		bResult = LevelCommand(gObj,(char*)aRecv+13+strlen("/level"));	  
	if (!memcmp(&aRecv[13],"/post",strlen("/post")))
		bResult = PostCommand(gObj,(char*)aRecv+13+strlen("/post"));	
	if (!memcmp(&aRecv[13],"/banpost",strlen("/banpost")))
		bResult = BanPostCommand(gObj,(char*)aRecv+13+strlen("/banpost"));	 
	if (!memcmp(&aRecv[13],"/unbanpost",strlen("/unbanpost")))
		bResult = UnBanPostCommand(gObj,(char*)aRecv+13+strlen("/unbanpost"));	
	if (!memcmp(&aRecv[13],"/banchar",strlen("/banchar")))
		bResult = BanCharCommand(gObj,(char*)aRecv+13+strlen("/banchar"));		
	if (!memcmp(&aRecv[13],"/unbanchar",strlen("/unbanchar")))
		bResult = UnBanCharCommand(gObj,(char*)aRecv+13+strlen("/unbanchar"));	
	if (!memcmp(&aRecv[13],"/banacc",strlen("/banacc")))
		bResult = BanAccCommand(gObj,(char*)aRecv+13+strlen("/banacc"));	 
	if (!memcmp(&aRecv[13],"/unbanacc",strlen("/unbanacc")))
		bResult = UnBanAccCommand(gObj,(char*)aRecv+13+strlen("/unbanacc"));
	if (!memcmp(&aRecv[13],"/time",strlen("/time")))
		bResult = TimeCommand(gObj,(char*)aRecv+13+strlen("/time"));	 	
	if (!memcmp(&aRecv[13],"/setchar",strlen("/setchar")))
		bResult = SetChar(gObj,(char*)aRecv+13+strlen("/setchar"));	
	if (!memcmp(&aRecv[13],"/setpk",strlen("/setpk")))
		bResult = SetPKCommand(gObj,(char*)aRecv+13+strlen("/setpk"));		
	if (!memcmp(&aRecv[13],"/skin",strlen("/skin")))
		bResult = SkinCommand(gObj,(char*)aRecv+13+strlen("/skin"));	
	if (!memcmp(&aRecv[13],"/drop",strlen("/drop")))
		bResult = DropCommand(gObj,(char*)aRecv+13+strlen("/drop"));	 
	if (!memcmp(&aRecv[13],"/gmove",strlen("/gmove")))
		bResult = GmoveCommand(gObj,(char*)aRecv+13+strlen("/gmove"));	 
	if (!memcmp(&aRecv[13],"/online",strlen("/online")))
		bResult = OnlineCommand(gObj,(char*)aRecv+13+strlen("/online"));
	if (!memcmp(&aRecv[13],"/status",strlen("/status")))
		bResult = StatusCommand(gObj,(char*)aRecv+13+strlen("/status"));
	if (!memcmp(&aRecv[13],"/reload",strlen("/reload")))
		bResult = ReloadCommand(gObj,(char*)aRecv+13+strlen("/reload")); 	 
	if (!memcmp(&aRecv[13],"/pkclear",strlen("/pkclear")))
		bResult = PKClearCommand(gObj,(char*)aRecv+13+strlen("/pkclear"));	
	if (!memcmp(&aRecv[13],"/addstr",strlen("/addstr")))
		bResult = AddCommands(gObj,(char*)aRecv+13+strlen("/addstr"),0);
	if (!memcmp(&aRecv[13],"/addagi",strlen("/addagi")))
		bResult = AddCommands(gObj,(char*)aRecv+13+strlen("/addagi"),1);
	if (!memcmp(&aRecv[13],"/addvit",strlen("/addvit")))
		bResult = AddCommands(gObj,(char*)aRecv+13+strlen("/addvit"),2);
	if (!memcmp(&aRecv[13],"/addene",strlen("/addene")))
		bResult = AddCommands(gObj,(char*)aRecv+13+strlen("/addene"),3);
	if (!memcmp(&aRecv[13],"/addcmd",strlen("/addcmd")))
		bResult = AddCommands(gObj,(char*)aRecv+13+strlen("/addcmd"),4);		
	if (!memcmp(&aRecv[13],"/ware",strlen("/ware")))
		bResult = WareCommand(gObj,(char*)aRecv+13+strlen("/ware"));	
	if (!memcmp(&aRecv[13],"/setzen",strlen("/setzen")))
		bResult = SetZenCommand(gObj,(char*)aRecv+13+strlen("/setzen"));	   
				
	return bResult;												
}

void cChat::MsgSrv(char *Sender,char *Message, int Type)
{		 
	BYTE *Packet;
	Packet = (BYTE*) malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	if(Type)
		*(Packet+2) = 0x02;	  
	else				   
		*(Packet+2) = 0x00;
	memcpy((Packet+3), Sender, strlen(Sender));
	memcpy((Packet+13), Message, strlen(Message));
	int Len = (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	DataSendAll(Packet, Len);
	free (Packet);
}

void cChat::MessageLog(int Type, sColor LogColor, sLogType LogType, LPOBJ gObj, char *Msg,...)
{	
	Messages[0] = 0;
	char Temp[255]; 
	strcpy(Temp,Msg);
	va_list pArguments1;
	va_start(pArguments1, Msg);
	vsprintf_s(Messages, Temp, pArguments1);
	va_end(pArguments1); 
	GCServerMsgStringSend(Messages, gObj->m_Index, Type);
	// Type = 1 - в блоке сообщений 
	// Type = 0 - золотом по середине
	if(Type)
		Log.ConsoleOutPut(1, LogColor, LogType, "[%s:%s]: %s", gObj->AccountID, gObj->Name, Messages);
	else														
		Log.ConsoleOutPut(1, LogColor, LogType, "[GoldMessage] %s", Messages);
}						  

void cChat::Message(int Type, int Index, char *Msg,...)
{				 	   
	Messages[0] = 0;
	char Temp[255]; 
	strcpy(Temp,Msg);
	va_list pArguments1;
	va_start(pArguments1, Msg);
	vsprintf_s(Messages, Temp, pArguments1);
	va_end(pArguments1); 
	GCServerMsgStringSend(Messages, Index, Type);
	// Type = 1 - в блоке сообщений 
	// Type = 0 - золотом по середине
}

void cChat::Message(int Index, char *Msg,...)
{				 	   
	Messages[0] = 0;	
	char Temp[255]; 
	strcpy(Temp,Msg);
	va_list pArguments1;
	va_start(pArguments1, Msg);
	vsprintf_s(Messages, Temp, pArguments1);
	va_end(pArguments1); 
	GCServerMsgStringSend(Messages, Index, 1);
	// Type = 1 - в блоке сообщений 
	// Type = 0 - золотом по середине
}
					 			
void cChat::MessageAllLog(int Type, int Type2, sColor LogColor, sLogType LogType, LPOBJ gObj, char *Msg,...)
{					   
	Messages[0] = 0;
	char Temp[255]; 
	strcpy(Temp,Msg);
	va_list pArguments1;
	va_start(pArguments1, Msg);
	vsprintf_s(Messages, Temp, pArguments1);
	va_end(pArguments1); 
	if(Type == 2)
	{
		MsgSrv(gObj->Name, Messages, Type2);
	}
	else
		for(int i=OBJECT_MIN; i<=OBJECT_MAX; i++)
		{											 
			OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
			if(gObj->Connected < PLAYER_PLAYING)	continue;
			GCServerMsgStringSend(Messages, i, Type);
		}	

	if(Type)
		Log.ConsoleOutPut(1, LogColor, LogType, "[%s:%s]: %s", gObj->AccountID, gObj->Name, Messages);
	else														
		Log.ConsoleOutPut(1, LogColor, LogType, "[%s:%s][GoldMessage] %s", gObj->AccountID, gObj->Name, Messages);
}

void cChat::MessageAll(int Type, int Type2, char *Sender, char *Msg,...)
{					  
	Messages[0] = 0;
	char Temp[255]; 
	strcpy(Temp,Msg);
	va_list pArguments1;
	va_start(pArguments1, Msg);
	vsprintf_s(Messages, Temp, pArguments1);
	va_end(pArguments1); 

	if(Type == 2)
	{
		MsgSrv(Sender, Messages, Type2);
	}
	else
		for(int i=OBJECT_MIN; i<=OBJECT_MAX; i++)
		{											 
			OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(i);
			if(gObj->Connected < PLAYER_PLAYING)	continue;
			GCServerMsgStringSend(Messages, i, Type);
		}											 
}

bool cChat::CheckCommand(LPOBJ gObj, int lConfig, cGmSystem::Commands Command, 
						int NeedZen, int NeedPcPoint, int NeedWCoin,
						int NeedLvl, int Filled, int CheckPlayer, 
						char *CommandName, char *CommandUsage, char *Msg)
{
	bool bResult = false;
	
	int spaces = 0;
	for(unsigned int i = 0; i < strlen(Msg); i++)
		if(Msg[i]==' ' && Msg[i-1]!=' ')spaces++;	

	if((Filled > 0) && ((Filled > spaces) || (((strlen(Msg) < 1) || (strlen(Msg) == 1)) && (Msg[0] == ' '))))
	{				
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Usage: %s", CommandName, CommandUsage);
		return true;
	}

	if (lConfig == 0)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Function temporarily disabled.", CommandName);
		return true;
	}

	if (!GmSystem.IsCommand(Command, gObj->Name))
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] You can't use this command.", CommandName);
		return true;
	}		
					   
	if (NeedLvl > 0 && gObj->Level < NeedLvl)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] You haven't got enougth level.", CommandName);
		bResult = true;
	}

	if (NeedZen > 0 && NeedZen > gObj->Money)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] You haven't got enougth money.", CommandName);
		bResult = true;
	}					  

	if (NeedPcPoint > 0 && NeedPcPoint > AddTab[gObj->m_Index].PC_PlayerPoints)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] You need %d more PcPoints.", CommandName, NeedPcPoint - AddTab[gObj->m_Index].PC_PlayerPoints);
		bResult = true;
	}

	if (NeedWCoin > 0 && NeedWCoin > gObj->m_wCashPoint)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] You need %d more WCoins.", CommandName, NeedWCoin - gObj->m_wCashPoint);
		bResult = true;
    }
						 								  
	if(CheckPlayer > 0)
	{						
		char Target[11], Target2[11];
		int Index = 0, Index2 = 0;
		if(CheckPlayer == 1)
		{
			sscanf(Msg,"%s",&Target);
			Index = Utilits.GetPlayerIndex(Target);
		}
		else if(CheckPlayer == 2)
		{	 
			sscanf(Msg,"%s %s",&Target,&Target2);	  
			Index = Utilits.GetPlayerIndex(Target);
			Index2 = Utilits.GetPlayerIndex(Target2);
		}
	
		if(Index == -1 || Index2 == -1)
		{													
			MessageLog(1, c_Red, t_COMMANDS, gObj, "[%s] Player offline or doesn't exist!", CommandName);
			bResult = true;
		}
	}		 
	return bResult;
}			  
		
void cChat::TakeCommand(LPOBJ gObj, int NeedZen, int NeedPcPoint, int NeedWCoin, char *CommandName)
{
	if(NeedZen > 0)
	{
		gObj->Money -= NeedZen;
		GCMoneySend(gObj->m_Index, gObj->Money);
	}
	if(NeedPcPoint > 0)
	{
		PCPoint.UpdatePoints(gObj,NeedPcPoint,PC_DEL,PCPOINT);
		Chat.MessageLog(1, c_Blue, t_PCPOINT, gObj,"[%s] You payed %d PcPoints", CommandName, NeedPcPoint);
	}	
	if(NeedWCoin > 0)
	{
		PCPoint.UpdatePoints(gObj,NeedWCoin,PC_DEL,WCOIN);
		Chat.MessageLog(1, c_Blue, t_PCPOINT, gObj,"[%s] You payed %d WCoin", CommandName, NeedWCoin);
	}
}			  
 
bool cChat::GgCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsGg, GmSystem.cGg, 0, 0, 0, 0, 1, 0, "GG", "/gg <msg>", Msg))
		return true;												
							
	 Log.CheckProcent(Msg);
	MessageAllLog(0, 0,  c_Yellow, t_GPOST, gObj, "[%s]: %s", gObj->Name, Msg);	
	return true;
}			
													   
bool cChat::VosklCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, 1, GmSystem.cVoskl, 0, 0, 0, 0, 1, 0, "!", "! <msg>", Msg))
		return true;												
						
	Log.CheckProcent(Msg);
	MessageAllLog(0, 0, c_Yellow,  t_GPOST, gObj, Msg);
	return true;
}		

bool cChat::TraceCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, 1, GmSystem.cTrace, 0, 0, 0, 0, 1, 1, "Trace", "/trace <name>", Msg))
		return true;

	char Target[11];
	sscanf(Msg, "%s", &Target);

	int Index = Utilits.GetPlayerIndex(Target);
	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	gObjTeleport(gObj->m_Index, tObj->MapNumber, (int)tObj->X, (int)tObj->Y);	
	MessageLog(1, c_Green, t_GPOST, gObj, "[Trace] You successfully traced to %s",Target);
	return true;
}		

bool cChat::SummonCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, 1, GmSystem.cTrace, 0, 0, 0, 0, 1, 1, "Track", "/Track <name>", Msg))
		return true;

	char Target[11];
	sscanf(Msg, "%s", &Target);

	int Index = Utilits.GetPlayerIndex(Target);
	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	gObjTeleport(tObj->m_Index, gObj->MapNumber, (int)gObj->X, (int)gObj->Y);	
	MessageLog(1, c_Green, t_GPOST, gObj, "[Track] You successfully summoned %s",Target);
	return true;
}		

bool cChat::DiskCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, 1, GmSystem.cDisconnect, 0, 0, 0, 0, 1, 1, "DC", "/disconnect <name>", Msg))
		return true;

	char Target[11];
	sscanf(Msg, "%s", &Target);
	CloseClient(Utilits.GetPlayerIndex(Target));

	MessageLog(1, c_Green, t_GPOST, gObj, "[Disconnect] %s was disconnected.",Target);	
	return true;
}			

bool cChat::Move(LPOBJ gObj, char *Msg)
{
	char MapName[50];
	sscanf(Msg, "%s", MapName);

	int Index = -1;
	for(int i = 1; i <= MoveReq.Count; i++)
	{
		if(!_strcmpi(MapName, MoveReq.MoveReqInfo[i].MapName1) || !_strcmpi(MapName, MoveReq.MoveReqInfo[i].MapName2))
		{
			Index = i;
			break;
		}
	}
	if(Index != -1)
	{	 	
		DWORD ZenActual;
		ZenActual = (DWORD)gObj->Money;
		if(ZenActual < (DWORD)MoveReq.MoveReqInfo[Index].Zen)return true;
		DWORD ZenDec = ZenActual - (DWORD)MoveReq.MoveReqInfo[Index].Zen;			 

		if(gObj->m_PK_Level > 4)
		{
			MessageLog(1,  c_Red,  t_COMMANDS, gObj, "[Move] Fonomans can't move");
			return true;
		}

		if(gObj->Level < MoveReq.MoveReqInfo[Index].Level)
		{					 
			MessageLog(1,  c_Red,  t_COMMANDS, gObj, "[Move] You have low level!");
			return true;
		}

		gObj->Money = ZenDec;
		GCMoneySend (gObj->m_Index,ZenDec);
		gObjMoveGate(gObj->m_Index,MoveReq.MoveReqInfo[Index].Gate);   
		return true;
	}
	else
	{
		MessageLog(1,  c_Red,  t_COMMANDS, gObj, "[Move] Such map doesn't exists.");
		return true;
	}
}

bool cChat::PostCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsPost, GmSystem.NONE, Config.Commands.PostPriceZen, Config.Commands.PostPricePCPoint, Config.Commands.PostPriceWCoin, Config.Commands.PostLvl, 1, 0, "Post", "/post <msg>", Msg))
		return true;

	MySQL.Execute("SELECT BanPost FROM [%s].[dbo].[Character] WHERE Name = '%s'",MySQL.szDatabase, gObj->Name);		
	int Banned = MySQL.GetInt();
	if(Banned == 1)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[POST] You can't post.");
		return true;
	}

	TakeCommand(gObj, Config.Commands.PostPriceZen, Config.Commands.PostPricePCPoint, Config.Commands.PostPriceWCoin, "Post"); 
	switch(Config.Commands.PostColor)
	{
	case 0:
	case 1:
		MessageAllLog(2, 1, c_Yellow, t_POST, gObj, "[POST] %s", Msg);	
		break;
	case 2:
		MessageAllLog(2, 0, c_Green, t_POST, gObj, "@[POST] %s", Msg);	
		break;
	case 3:
		MessageAllLog(2, 0, c_Blue, t_POST, gObj, "~[POST] %s", Msg);	
		break;
	} 
	return true;
}


bool cChat::BanPostCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsBanPost, GmSystem.cBanPost, 0, 0, 0, 0, 2, 0, "BanPost", "/banpost <nick>", Msg))
		return true;	

	char Target[11];  


	sscanf(Msg, "%s", &Target);
	int Index = Utilits.GetPlayerIndex(Target); 
	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MySQL.Execute("SELECT BanPost FROM [%s].[dbo].[Character] WHERE Name = '%s'",MySQL.szDatabase, Target);		
	int Banned = MySQL.GetInt(); 

	if(Banned)
	{																											   
		MessageLog(1, c_Red, t_BAN, gObj, "[BanPost] %s Already Banned", Target);
	}
	else   
	{
		MessageLog(1, c_Red, t_BAN, gObj, "[BanPost] %s Added BanPosts", Target);		
	}

	MySQL.Execute("UPDATE [%s].[dbo].[Character] SET BanPost = '1' WHERE Name = '%s'",MySQL.szDatabase,  Target);
	return true;	   
}

bool cChat::UnBanPostCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsBanPost, GmSystem.cBanPost, 0, 0, 0, 0, 1, 0, "UnBanPost", "/unbanpost <nick>", Msg))
		return true;	

	char Target[11];  

	sscanf(Msg, "%s", &Target);
	int Index = Utilits.GetPlayerIndex(Target); 
	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MySQL.Execute("SELECT BanPost FROM [%s].[dbo].[Character] WHERE Name = '%s'",MySQL.szDatabase, Target);		
	int Banned = MySQL.GetInt();

	if(Banned == 0)
	{																											   
		MessageLog(1, c_Red, t_BAN, gObj, "[BanPost] %s's post is not banned", Target);
		return true;
	}
	else   
	{
		MessageLog(1, c_Red, t_BAN, gObj, "[BanPost] %s's post sucsessfuly UnBanned!", Target);
	} 

	MySQL.Execute("UPDATE [%s].[dbo].[Character] SET  BanPost = '0' WHERE Name = '%s'", MySQL.szDatabase,Target);	
	return true;	   
} 

bool cChat::BanCharCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsBanChar, GmSystem.cBanPlayer, 0, 0, 0, 0, 1, 0, "BanChar", "/banchar <nick>", Msg))
		return true;	

	char Target[11];  

	sscanf(Msg, "%s", &Target);
	int Index = Utilits.GetPlayerIndex(Target); 
	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MySQL.Execute("SELECT CtlCode FROM [%s].[dbo].[Character] WHERE Name = '%s'",MySQL.szDatabase, Target);		
	int Banned = MySQL.GetInt();

	if(Banned == 1)
	{																											   
		MessageLog(1, c_Red, t_BAN, gObj, "[BanChar] %s is already banned", Target);
		return true;
	}
	else   
	{																				 
		MySQL.Execute("UPDATE [%s].[dbo].[Character] SET CtlCode='1' WHERE Name='%s'",MySQL.szDatabase,Target);		
		MessageLog(1, c_Red, t_BAN, gObj, "[BanChar] %s banned", Target);		
	}

	CloseClient(Index);
	return true;	 
}

bool cChat::BanAccCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsBanAcc, GmSystem.cBanPlayer, 0, 0, 0, 0, 1, 0, "BanAcc", "/banacc <login> <nick>", Msg))
		return true;	

	char Target[11]; // account
	char Target2[11]; // nick

	sscanf(Msg, "%s %s", &Target, &Target2);
	int Index = Utilits.GetPlayerIndex(Target2); 
	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);


	if(Index != -1)			
	{
		CloseClient(Index);									   
		MessageLog(1, c_Red, t_BAN, gObj, "[BanAcc] %s banned, character %s disconnected.", Target, Target2);		
		MySQL.Execute("UPDATE [%s].[dbo].[MEMB_INFO] SET bloc_code='1' WHERE memb___id = '%s'",MySQL.szDatabase,Target);	
	}
	else 
		MySQL.Execute("UPDATE [%s].[dbo].[MEMB_INFO] SET bloc_code='1' WHERE memb___id = '%s'",MySQL.szDatabase,Target);	   

	return true;	 
}

bool cChat::UnBanCharCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsBanChar, GmSystem.cBanPlayer, 0, 0, 0, 0, 1, 0, "UnBanChar", "/unbanchar <nick>", Msg))
		return true;	

	char Target[11];  

	sscanf(Msg, "%s", &Target);

	MySQL.Execute("SELECT CtlCode FROM [%s].[dbo].[Character] WHERE Name = '%s'",MySQL.szDatabase, Target);
	int Banned = MySQL.GetInt();

	if(Banned == 0)
	{																											   
		MessageLog(1, c_Red, t_BAN, gObj, "[UnBanChar] %s is not baned", Target);
		return true;
	}
	else   
	{		 
		MySQL.Execute("UPDATE [%s].[dbo].[Character] SET CtlCode='0' WHERE Name='%s'",MySQL.szDatabase,Target);
		MessageLog(1, c_Red, t_BAN, gObj, "[UnBanChar] %s UnBaned", Target);		
	}
	return true;	 
}

bool cChat::UnBanAccCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsBanAcc, GmSystem.cBanPlayer, 0, 0, 0, 0, 1, 0, "UnBanAcc", "/unbanacc <login>", Msg))
		return true;	

	char Target[11];  

	sscanf(Msg, "%s", &Target);

	MySQL.Execute("SELECT bloc_code FROM [%s].[dbo].[MEMB_INFO] WHERE memb___id = '%s'",MySQL.szDatabase, Target);	
	int Banned = MySQL.GetInt();

	if(Banned == 0)
	{																											   
		MessageLog(1, c_Red, t_BAN, gObj, "[UnBanAcc] %s is not baned", Target);
		return true;
	}
	else   
	{		 																	  
		MySQL.Execute("UPDATE [%s].[dbo].[MEMB_INFO] SET bloc_code='0' WHERE memb___id = '%s'",MySQL.szDatabase,Target);  
		MessageLog(1, c_Red, t_BAN, gObj, "[UnBanAcc] %s UnBaned", Target);		
	} 

	return true;	 
}

bool cChat::TimeCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsTime, GmSystem.NONE, 0, 0, 0, 0, 0, 0, "Time", "/time", Msg))
		return true;

	SYSTEMTIME t;
	GetLocalTime(&t);
	MessageLog(1, c_Blue, t_COMMANDS, gObj, "Server Time & Date: %02d:%02d:%02d %02d-%02d-%02d.", t.wHour, t.wMinute, t.wSecond, t.wDay, t.wMonth, t.wYear);
	return true;
}


bool cChat::LevelCommand(LPOBJ gObj, char *Msg)
{					
	MessageLog(1, c_Red, t_GM, gObj, "Level: %d, Master Level: %d", gObj->Level, gObj->MLevel);
	return true;
}

bool cChat::DropCommand(LPOBJ gObj, char *Msg)
{					
	if(CheckCommand(gObj, Config.Commands.IsDrop, GmSystem.cDrop, 0, 0, 0, 0, 3, 0, "Drop", "/drop <Value> <ItemCount> <ItemType> <ItemIndex> <ItemLvl> <ItemSkill> <ItemLuck> <ItemOpt> <ItemExc> <ItemAnc>", Msg))
		return true;

	int ItemCount = 0;
	int ItemType = 0;
	int ItemIndex = 0;
	int ItemLevel = 0;
	int ItemSkill = 0;
	int ItemLuck = 0;
	int ItemOpt = 0;
	int ItemExc = 0;
	int ItemAncient = 0;

	char Target[11];
	int Index = 0;
	sscanf(Msg,"%s",&Target);
	Index = Utilits.GetPlayerIndex(Target);
	if(Index == -1)
	{	
		sscanf(Msg, "%d %d %d %d %d %d %d %d %d", &ItemCount, &ItemType, &ItemIndex, &ItemLevel, &ItemSkill, &ItemLuck, &ItemOpt, &ItemExc, &ItemAncient);
		int Item = ItemType * 512 + ItemIndex;
		if ((ItemCount < 0) || (ItemCount > 20))
			ItemCount = 1;
		if(ItemIndex < 0 || (ItemType < 0 || ItemType > 15) || (ItemLevel<0 || ItemLevel > 13) || (ItemOpt < 0 || ItemOpt > 7) || (ItemLuck < 0 || ItemLuck > 1) || (ItemSkill < 0 || ItemSkill > 1) || (ItemExc < 0 || ItemExc > 63) || (ItemAncient < 0 || ItemAncient > 40))
		{
			MessageLog(1, c_Red, t_GM, gObj, "[Drop] Usage: /drop <ItemCount> <ItemType> <ItemIndex> <ItemLvl> <ItemSkill> <ItemLuck> <ItemOpt> <ItemExc> <ItemAnc>");
			return true;
		}
		else
		{
			for (int i=0; i < ItemCount; i++ )
				ItemSerialCreateSend (gObj->m_Index, gObj->MapNumber, (int)gObj->X, (int)gObj->Y, Item, ItemLevel, 0, ItemSkill, ItemLuck, ItemOpt, gObj->m_Index, ItemExc, ItemAncient);
			MessageLog(1, c_Green, t_GM, gObj, "[Drop] %d Item Created %d %d %d %d %d %d %d %d - Success", ItemCount, ItemType, ItemIndex, ItemLevel, ItemSkill, ItemLuck, ItemOpt, ItemExc, ItemAncient);
		}
	}
	else
	{	  
		sscanf(Msg, "%s %d %d %d %d %d %d %d %d %d", &Target, &ItemCount, &ItemType, &ItemIndex, &ItemLevel, &ItemSkill, &ItemLuck, &ItemOpt, &ItemExc, &ItemAncient);
		int Item = ItemType * 512 + ItemIndex;	 
		if ((ItemCount < 0) || (ItemCount > 20))
			ItemCount = 1;
		if(ItemIndex < 0 || (ItemType < 0 || ItemType > 15) || (ItemLevel<0 || ItemLevel > 13) || (ItemOpt < 0 || ItemOpt > 7) || (ItemLuck < 0 || ItemLuck > 1) || (ItemSkill < 0 || ItemSkill > 1) || (ItemExc < 0 || ItemExc > 63) || (ItemAncient < 0 || ItemAncient > 40))
		{
			MessageLog(1, c_Red, t_GM, gObj, "[Drop] Usage: /drop <Name> <ItemCount> <ItemType> <ItemIndex> <ItemLvl> <ItemSkill> <ItemLuck> <ItemOpt> <ItemExc> <ItemAnc>");
			return true;
		}
		else
		{			  
			OBJECTSTRUCT *gUbj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);
			for (int i=0; i < ItemCount; i++ )
				ItemSerialCreateSend (gUbj->m_Index, gUbj->MapNumber, (int)gUbj->X, (int)gUbj->Y, Item, ItemLevel, 0, ItemSkill, ItemLuck, ItemOpt, gUbj->m_Index, ItemExc, ItemAncient);
			MessageLog(1, c_Green, t_GM, gObj, "[Drop] %d Item Created to %s %d %d %d %d %d %d %d %d - Success", ItemCount, gUbj->Name,ItemType, ItemIndex, ItemLevel, ItemSkill, ItemLuck, ItemOpt, ItemExc, ItemAncient);
			Message(1, gUbj->m_Index, "[Drop] You lucked by %s with %d items! Take them faster!", gObj->Name, ItemCount);
		}
	} 
	return true;
}

bool cChat::SetChar(LPOBJ gObj, char *Msg)
{
#pragma warning(disable: 4018 4244)
	if(CheckCommand(gObj, Config.Commands.IsSetChar, GmSystem.cSetZen, 0, 0, 0, 0, 2, 1, "SetChar", "/setchar <Nick> <Zen> <PCPnt> <WCoins> <AddPnt> <lvl> <Prof>", Msg))
		return true;

	DWORD Zen = 0, PCPnt = 0, WCoin = 0, AddPnt = 0, Lvl = 0, Prof = 0;
	char Target[11]; 	 
	sscanf(Msg, "%s %d %d %d %d %d %d", &Target, &Zen, &PCPnt, &WCoin, &AddPnt, &Lvl, &Prof);

	if(Zen < 0 || Zen > 2000000000)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] Zen can't be less than 0 and more than 2000000000!");
		return true;
	}	

	if(PCPnt < 0 || PCPnt > PCPoint.sPoints.MaximumPCPoints)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] PCPnt can't be less than 0 and more than %d!", PCPoint.sPoints.MaximumPCPoints);
		return true;
	}	

	if(WCoin < 0 || WCoin > PCPoint.sPoints.MaximumWCPoints)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] WCoin can't be less than 0 and more than %d!", PCPoint.sPoints.MaximumWCPoints);
		return true;
	}	

	int MaximumAddPnt;
	if(Config.Commands.MaxAddedStats == 0)MaximumAddPnt = 32000;
	else
		MaximumAddPnt = 65000;

	if(AddPnt < 0 || AddPnt > MaximumAddPnt)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] AddPnt can't be less than 0 and more than %d!", MaximumAddPnt);

		return true;
	}	

	if(Lvl < 0 || Lvl > Config.Commands.MaxLvl)
	{
		MessageLog(1, c_Red,t_GM, gObj, "[SetChar] Lvl can't be less than 0 and more than %d!", Config.Commands.MaxLvl);
		return true;
	}

	if(Prof < 0 || Prof > 3)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetChar] Lvl can't be less than 0 and more than 3!");
		return true;
	}

	int Index = Utilits.GetPlayerIndex(Target); 
	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	if(Zen > 0)
	{
		tObj->Money = Zen;
		GCMoneySend (tObj->m_Index, Zen);
	}

	if(PCPnt > 0 )
	{
		PCPoint.UpdatePoints(tObj,PCPnt,PC_ADD,PCPOINT);
	}

	if(WCoin > 0)
	{
		PCPoint.UpdatePoints(tObj,WCoin,PC_ADD,WCOIN);
	}

	if(AddPnt > 0)
	{
		tObj->LevelUpPoint += AddPnt;
	}

	if(Lvl > 0)
	{
		tObj->Level	= Lvl;
	}

	if(Prof > 0)
	{
		switch(Prof)
		{
		case 0:
			break;
		case 1:
			if(gObj->DbClass >= 0 && gObj->DbClass <= 3)gObj->DbClass = 0;
			if(gObj->DbClass >= 16 && gObj->DbClass <= 19)gObj->DbClass = 16;
			if(gObj->DbClass >= 32 && gObj->DbClass <= 35)gObj->DbClass = 32;
			if(gObj->DbClass >= 48 && gObj->DbClass <= 50)gObj->DbClass = 48;
			if(gObj->DbClass >= 64 && gObj->DbClass <= 66)gObj->DbClass = 64;
			if(gObj->DbClass >= 80 && gObj->DbClass < 83)gObj->DbClass = 80;
			else
				break;
		case 2:
			if(gObj->DbClass >= 0 && gObj->DbClass <= 3)gObj->DbClass = 1;
			if(gObj->DbClass >= 16 && gObj->DbClass <= 19)gObj->DbClass = 17;
			if(gObj->DbClass >= 32 && gObj->DbClass <= 35)gObj->DbClass = 33;
			if(gObj->DbClass >= 80 && gObj->DbClass < 83)gObj->DbClass = 81;
			else
				break;
		case 3:
			if(gObj->DbClass >= 0 && gObj->DbClass <= 3)gObj->DbClass = 3;
			if(gObj->DbClass >= 16 && gObj->DbClass <= 19)gObj->DbClass = 19;
			if(gObj->DbClass >= 32 && gObj->DbClass <= 35)gObj->DbClass = 35;
			if(gObj->DbClass >= 48 && gObj->DbClass <= 50)gObj->DbClass = 50;
			if(gObj->DbClass >= 64 && gObj->DbClass <= 66)gObj->DbClass = 66;
			if(gObj->DbClass >= 80 && gObj->DbClass < 83)gObj->DbClass = 83;
			else
				break;
		}
	}
	MessageLog(1, c_Red, t_GM, gObj, "[SetChar] You successfully changed %s character.", tObj->Name);
	MessageLog(1, c_Red, t_GM, tObj, "[SetChar] Your character was edited by %s, you must relogin!", gObj->Name);

	return true;
}			

bool cChat::OnlineCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsOnline, GmSystem.NONE, 0, 0, 0, 0, 0, 0, "Online", "/online", Msg))
		return true;

	int totGMs = Utilits.GetOnlineGMCount();
	int totPlayers = Utilits.GetOnlineCount() - totGMs;
	MessageLog(1, c_Blue, t_COMMANDS, gObj, "[ONLINE]: %d Player(s), %d GM(s)",totPlayers, totGMs);
	return true;
}

bool cChat::SetPKCommand(LPOBJ gObj, char *Msg)
{								 			
	if(CheckCommand(gObj, Config.Commands.IsSetPK, GmSystem.cSetPK, 0, 0, 0, 0, 2, 1, "SetPK", "/setpk <nick> <pklvl>", Msg))
		return true;

	char Target[11];
	int SetLevel;
	sscanf(Msg,"%s %d",&Target, &SetLevel);		

	if(SetLevel < 0 || SetLevel > 100)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetPK] PK lvl can't be less than 0 and more than 100!");
		return true;
	}			 

	int Index = Utilits.GetPlayerIndex(Target); 
	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	tObj->m_PK_Level = SetLevel;
	if(SetLevel >= 3)
		tObj->m_PK_Count = SetLevel - 3;
	GCPkLevelSend(tObj->m_Index,SetLevel);	 

	MessageLog(1, c_Red, t_GM, gObj, "[SetPK] You successfully changed %s pk.", tObj->Name);
	MessageLog(1, c_Red, t_GM, tObj, "[SetPK] Your pk was changed to %d by %s.", SetLevel, gObj->Name);
	return true;
}

bool cChat::ReloadCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsReload, GmSystem.cReload, 0, 0, 0, 0, 1, 0, "Reload", "/reload <number>", Msg))
		return true; 

		int NumberReload;
		sscanf(Msg,"%d",&NumberReload);

		switch (NumberReload)
		{
		case 0:
			{
				Config.LoadAll();
				MoveReq.MoveReqLoad();
				MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] RMST Data & MoveReq Reloaded.");
				break;
			}
		case 1:
			{
				GameMonsterAllCloseAndReload(); 
				MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] Monsters Reloaded.");
				break;
			}
		case 2:
			{
				pShopDataLoad();
				PCPoint.LoadIniConfigs();		
				MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] Shops & PCPoints Reloaded.");
				break;
			}
		case 3:
			{
				if (Config.GmSystemConfig.IsGMSystem)
				{
					GmSystem.Load();
					MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] GMSystem Reloaded.");
				}
				else
					Message(1,gObj->m_Index,"[Reload] GMSystem is disabled");
				break;
			}
		case 4:
			{
				DropSystem.LoadDropItems();
				MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] Item Drop Settings Reloaded.");
				break;
			}
		case 5:
			{
				IpBlock.LoadIpBlock();
				MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] IPBlock Reloaded.");
				break;
			}
		case 6:
			{
				Config.LoadAll();
				GameMonsterAllCloseAndReload();
				pShopDataLoad();
				IpBlock.LoadIpBlock();
				if (Config.GmSystemConfig.IsGMSystem)GmSystem.Load();
				DropSystem.LoadDropItems();
				MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Reload] All Options Reloaded.");
				break;
			}
		default:
			{
				MessageLog(1, c_Red, t_GM, gObj, "[Reload] Usage: /reload <Number>.");
				break;
			}
		} 
	return true;
}

bool cChat::StatusCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsStatus, GmSystem.cStatus, 0, 0, 0, 0, 1, 1, "Status", "/status <name>", Msg))
		return true;

	char Target[11];
	sscanf(Msg,"%s",&Target);
	int Index = Utilits.GetPlayerIndex(Target);   

	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	MessageLog(0, c_Green, t_GM, gObj, "IP Address: %s",tObj->Ip_addr);
	MessageLog(0,c_Green, t_GM, gObj,"Account: %s | Character: %s",tObj->AccountID,tObj->Name);
	MessageLog(0, c_Green, t_GM, gObj, "Level: %d | Zen: %d | Resets: %d",tObj->Level,tObj->Money, AddTab[Index].Resets);
	MessageLog(0, c_Green, t_GM, gObj, "Map: %s (%d)(%d,%d)",MoveReq.GetMapName(tObj->MapNumber),tObj->MapNumber,tObj->X,tObj->Y); 

	MessageLog(1, c_Green, t_GM, gObj, "[Status][GM] %s get your status!", gObj->Name);	  
	return true;
}

bool cChat::SkinCommand(LPOBJ gObj, char *Msg)
{  
	if(CheckCommand(gObj, Config.Commands.SkinEnabled, GmSystem.NONE, 0, 0, 0, 0, 1, 0, "Skin", "/skin <num>", Msg))
		return true;

	if(GmSystem.IsCommand(GmSystem.cSkin, gObj->Name))
	{
		int spaces = 0, NumSkin = 0;			
		char Target[11];
		for(unsigned int i=0;i < strlen(Msg);i++)
			if(Msg[i]==' ')spaces++;		
		sscanf(Msg,"%s %d",&Target, &NumSkin);
		if(strlen(Msg) <= 0 || spaces != 2 || strlen(Target) > 11)
		{  	  									 
			sscanf(Msg,"%d", &NumSkin);	 
			gObj->m_Change = NumSkin;
			gObjViewportListProtocolCreate(gObj);
			MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Skin] Your Skin successfully changed!");
			return true;
		}

		if(CheckCommand(gObj, Config.Commands.SkinEnabled, GmSystem.NONE, 0, 0, 0, 0, 1, 1, "Skin", "/skin <name> <num>", Msg))
			return true;

		int Index = Utilits.GetPlayerIndex(Target); 
		OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

		tObj->m_Change = NumSkin;
		gObjViewportListProtocolCreate(tObj);															 
		MessageLog(1, c_Red, t_GM, gObj, "[Skin] You successfully change %s Skin.", tObj->Name);
		MessageLog(1, c_Red, t_GM, tObj, "[Skin] Your Skin was changed by %s.", gObj->Name);	
	}
	else if(!Config.Commands.SkinOnlyForGm)
	{
		if(CheckCommand(gObj, Config.Commands.SkinEnabled, GmSystem.NONE, Config.Commands.SkinPriceZen, Config.Commands.SkinPricePcPoint, Config.Commands.SkinPriceWCoin, Config.Commands.SkinLevelReq, 1, 0, "Skin", "/skin <num>", Msg))
			return true;
		TakeCommand(gObj, Config.Commands.SkinPriceZen, Config.Commands.SkinPricePcPoint, Config.Commands.SkinPriceWCoin, "Skin");	
		int NumSkin;
		sscanf(Msg,"%d", &NumSkin);	 
		gObj->m_Change = NumSkin;
		gObjViewportListProtocolCreate(gObj);
		MessageLog(1, c_Blue, t_COMMANDS, gObj, "[Skin] Your Skin successfully changed!");
	}
	return true;				
}

bool cChat::GmoveCommand(LPOBJ gObj, char *Msg)
{					
	if(CheckCommand(gObj, Config.Commands.IsGmove, GmSystem.cGmove, 0, 0, 0, 0, 3, 0, "Gmove", "/gmove <map> <x> <y>", Msg))
		return true;

	char Target[11];   
	char Map[250];
	int x,y;

	int Index = 0;
	sscanf(Msg,"%s",&Target);
	Index = Utilits.GetPlayerIndex(Target);
	LPOBJ tObj;
	if(Index == -1)
	{	
		sscanf(Msg,"%s %d %d", &Map, &x, &y);
		tObj = gObj;
	}
	else
	{	  
		sscanf(Msg,"%s %s %d %d",&Target, &Map, &x, &y); 
		Index = Utilits.GetPlayerIndex(Target);  
		tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);
	} 

	int RMap;
	if(_strcmpi(Map, "0") == 0 || _strcmpi(Map, "Lorencia") == 0) RMap = 0;
	else if	(_strcmpi(Map, "1") == 0 || _strcmpi(Map, "Dungeon") == 0) RMap = 1;
	else if	(_strcmpi(Map, "2") == 0 || _strcmpi(Map, "Devias") == 0) RMap = 2;
	else if (_strcmpi(Map, "3") == 0 || _strcmpi(Map, "Noria") == 0) RMap = 3;
	else if (_strcmpi(Map, "4") == 0 || _strcmpi(Map, "Losttower") == 0) RMap = 4;
	else if (_strcmpi(Map, "6") == 0 || _strcmpi(Map, "Stadium") == 0 || _strcmpi(Map, "Arena") == 0) RMap = 6;
	else if (_strcmpi(Map, "7") == 0 || _strcmpi(Map, "Atlans") == 0) RMap = 7;
	else if (_strcmpi(Map, "8") == 0 || _strcmpi(Map, "Tarkan") == 0) RMap = 8;		
	else if (_strcmpi(Map, "10") == 0 || _strcmpi(Map, "Icarus") == 0) RMap = 10;			  
	else if (_strcmpi(Map, "24") == 0 || _strcmpi(Map, "kalima1") == 0) RMap = 24;
	else if (_strcmpi(Map, "25") == 0 || _strcmpi(Map, "kalima2") == 0) RMap = 25; 
	else if (_strcmpi(Map, "26") == 0 || _strcmpi(Map, "kalima3") == 0) RMap = 26;		
	else if (_strcmpi(Map, "27") == 0 || _strcmpi(Map, "kalima4") == 0) RMap = 27;   
	else if (_strcmpi(Map, "28") == 0 || _strcmpi(Map, "kalima5") == 0) RMap = 28;
	else if (_strcmpi(Map, "29") == 0 || _strcmpi(Map, "kalima6") == 0) RMap = 29;   
	else if (_strcmpi(Map, "30") == 0 || _strcmpi(Map, "valleyofloren") == 0) RMap = 30;
	else if (_strcmpi(Map, "31") == 0 || _strcmpi(Map, "landoftrial") == 0 || _strcmpi(Map, "landsoftrial") == 0) RMap = 31;			   
	else if (_strcmpi(Map, "33") == 0 || _strcmpi(Map, "aida") == 0) RMap = 33;			   
	else if (_strcmpi(Map, "34") == 0 || _strcmpi(Map, "crywolf") == 0) RMap = 34;			   
	else if (_strcmpi(Map, "36") == 0 || _strcmpi(Map, "kalima7") == 0) RMap = 36;			   
	else if (_strcmpi(Map, "37") == 0 || _strcmpi(Map, "kanturu") == 0) RMap = 37;			   
	else if (_strcmpi(Map, "38") == 0 || _strcmpi(Map, "kanturutruins") == 0 || _strcmpi(Map, "kantrutruins") == 0) RMap = 38;			   
	else if (_strcmpi(Map, "39") == 0 || _strcmpi(Map, "kantrutower") == 0 || _strcmpi(Map, "kanturutower") == 0) RMap = 39;			   
	else if (_strcmpi(Map, "40") == 0 || _strcmpi(Map, "silent") == 0) RMap = 40;			   
	else if (_strcmpi(Map, "41") == 0 || _strcmpi(Map, "balgasbarrack") == 0) RMap = 41;			   
	else if (_strcmpi(Map, "42") == 0 || _strcmpi(Map, "balgasrefuge") == 0) RMap = 42;			   
	else if (_strcmpi(Map, "51") == 0 || _strcmpi(Map, "elbeland") == 0) RMap = 51;			   
	else if (_strcmpi(Map, "56") == 0 || _strcmpi(Map, "swampofcalmness") == 0 || _strcmpi(Map, "calmness") == 0) RMap = 56;			   
	else if (_strcmpi(Map, "57") == 0 || _strcmpi(Map, "raklion") == 0) RMap = 57;			   
	else if (_strcmpi(Map, "58") == 0 || _strcmpi(Map, "raklionboss") == 0) RMap = 58;			   
	else if (_strcmpi(Map, "62") == 0 || _strcmpi(Map, "santatown") == 0 || _strcmpi(Map, "santa") == 0) RMap = 62;			   
	else if (_strcmpi(Map, "63") == 0 || _strcmpi(Map, "vulcanus") == 0) RMap = 63;
	else if (_strcmpi(Map, "64") == 0 || _strcmpi(Map, "coliseum") == 0) RMap = 64;
	else
	{
		MessageLog(1, c_Red, t_GM, gObj,"[GMove] Such map doesn't exist!");	
		return true;
	} 
	if(x > 255 || y > 255 || x < 0 || y < 0)
	{	 								   
		MessageLog(1, c_Red, t_GM, gObj,"[GMove] Such coords doesn't exist!");	
		return true;
	}  			
	gObjTeleport(tObj->m_Index, RMap, x, y);		
	if(tObj == gObj)		 
		MessageLog(1, c_Green, t_GM, gObj,"[GMove] You successfully moved to %s %d %d!", Map, x, y);
	else
	{	   
		MessageLog(1, c_Green, t_GM, gObj,"[GMove] You successfully move %s to %s %d %d!", tObj->Name, Map, x, y);
		MessageLog(1, c_Green, t_GM, tObj,"[GMove] You successfully moved to %s %d %d by %s!", Map, x, y, gObj->Name);
	}
	return true;
}

bool cChat::PKClearCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.ClearCommand.Enabled, GmSystem.NONE, 0, 0, 0, 0, 0, 0, "PKClear", "/pkclear", Msg))
		return true;

	if(GmSystem.IsCommand(GmSystem.cPkClear, gObj->Name))
	{
		int spaces=0;			
		char Target[11];
		for(unsigned int i=0;i < strlen(Msg);i++)
			if(Msg[i]==' ')spaces++;		
		sscanf(Msg,"%s",&Target);
		if(strlen(Msg) <= 0 || spaces != 1 || strlen(Target) > 11)
		{  	  
			if (gObj->m_PK_Level <=3)
			{												
				MessageLog(1, c_Blue, t_COMMANDS, gObj, "[PkClear] Your are not pk!");			
				return true;
			}					  
			gObj->m_PK_Level = 3;
			gObj->m_PK_Count = 0;
			GCPkLevelSend (gObj->m_Index, 3);	 
			MessageLog(1, c_Blue, t_COMMANDS, gObj, "[PkClear] Your Pk successfully cleared!");
			return true;
		}

		if(CheckCommand(gObj, Config.ClearCommand.Enabled, GmSystem.NONE, 0, 0, 0, 0, 1, 1, "PKClear", "/pkclear (nick)", Msg))
			return true;

		int Index = Utilits.GetPlayerIndex(Target); 
		OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

		if (tObj->m_PK_Level <=3)
		{												
			MessageLog(1, c_Blue, t_COMMANDS, gObj, "[PkClear] %s is not pk!", tObj->Name);			
			return true;
		}	 				   
		tObj->m_PK_Level = 3;
		tObj->m_PK_Count = 0;
		GCPkLevelSend (tObj->m_Index, 3);	 															 
		MessageLog(1, c_Red, t_GM, gObj, "[PkClear] You successfully clear %s pk.", tObj->Name);
		MessageLog(1, c_Red, t_GM, tObj, "[PkClear] Your pk was cleared by %s.", gObj->Name);	
	}
	else if(!Config.ClearCommand.OnlyForGm)
	{
		int PriceZen;
		int PricePcPoint;
		int PriceWCoin;
		switch(Config.ClearCommand.Type)
		{	   
		case 1:	
			PriceZen = (Config.ClearCommand.PriceZen * gObj->m_PK_Count); 		 
			PricePcPoint = (Config.ClearCommand.PricePcPoints * gObj->m_PK_Count);
			PriceWCoin = (Config.ClearCommand.PriceWCoins * gObj->m_PK_Count);
			break;
		case 2:	
			PriceZen = Config.ClearCommand.PriceZenForAll;			 
			PricePcPoint = Config.ClearCommand.PricePcPointsForAll;
			PriceWCoin = Config.ClearCommand.PriceWCoinsForAll;
			break;
		case 0: 
			PriceZen = 0;					 
			PricePcPoint = 0;
			PriceWCoin = 0;
			break;
		}

		if (gObj->m_PK_Level <=3)
		{												
			MessageLog(1, c_Blue, t_COMMANDS, gObj, "[PkClear] Your are not pk!");			
			return true;
		}			
		if(CheckCommand(gObj, Config.ClearCommand.Enabled, GmSystem.NONE, PriceZen, PricePcPoint, PriceWCoin, Config.ClearCommand.LevelReq, 0, 0, "PKClear", "/pkclear", Msg))
			return true;

		TakeCommand(gObj, PriceZen, PricePcPoint, PriceWCoin, "PKClear");	
		gObj->m_PK_Level = 3;
		gObj->m_PK_Count = 0;
		GCPkLevelSend (gObj->m_Index, 3);	 
		MessageLog(1, c_Blue, t_COMMANDS, gObj, "[PkClear] Your Pk successfully cleared!");
	}
	return true;				
}


bool cChat::AddCommands(LPOBJ gObj, char *Msg, int Type)
{	 
	switch(Type)
	{
	case 0:		  
		if(CheckCommand(gObj, Config.Commands.AddPointEnabled, GmSystem.NONE, Config.Commands.AddPriceZen, Config.Commands.AddPricePCPoint, Config.Commands.AddPriceWCoin, Config.Commands.AddPointLevelReq, 1, 0, "AddStats", "/addstr <num>", Msg))
			return true;
		break;
	case 1:	  
		if(CheckCommand(gObj, Config.Commands.AddPointEnabled, GmSystem.NONE, Config.Commands.AddPriceZen, Config.Commands.AddPricePCPoint, Config.Commands.AddPriceWCoin, Config.Commands.AddPointLevelReq, 1, 0, "AddStats", "/addagi <num>", Msg))
			return true;
		break;
	case 2:
		if(CheckCommand(gObj, Config.Commands.AddPointEnabled, GmSystem.NONE, Config.Commands.AddPriceZen, Config.Commands.AddPricePCPoint, Config.Commands.AddPriceWCoin, Config.Commands.AddPointLevelReq, 1, 0, "AddStats", "/addvit <num>", Msg))
			return true;
		break;
	case 3:
		if(CheckCommand(gObj, Config.Commands.AddPointEnabled, GmSystem.NONE, Config.Commands.AddPriceZen, Config.Commands.AddPricePCPoint, Config.Commands.AddPriceWCoin, Config.Commands.AddPointLevelReq, 1, 0, "AddStats", "/addene <num>", Msg))
			return true;
		break;
	case 4:
		if(CheckCommand(gObj, Config.Commands.AddPointEnabled, GmSystem.NONE, Config.Commands.AddPriceZen, Config.Commands.AddPricePCPoint, Config.Commands.AddPriceWCoin, Config.Commands.AddPointLevelReq, 1, 0, "AddStats", "/addcmd <num>", Msg))
			return true;
		break;
	}
	DWORD Points;
	sscanf(Msg,"%d",&Points);		  


	int MaxPoints = 32000;
	if(Config.Use65kStats >= 1)
		MaxPoints = -536;	

	int Stats = 0;
	bool bResult = false;
	switch (Type)
	{
	case 0x00:
		Stats = gObj->Strength;
		break;
	case 0x01:
		Stats = gObj->Dexterity;  
		break;
	case 0x02:	  
		Stats = gObj->Vitality; 
		break;	  
	case 0x03:
		Stats = gObj->Energy;	 			 
		break;
	case 0x04: 
		Stats = gObj->Leadership;	
		MaxPoints = 32000;
		break;
	}

	int MaxPointsTemp = MaxPoints; 
	if(MaxPoints > 32767)
		MaxPoints = -32768 + (MaxPoints - 32767);

	if((MaxPoints > 0) && (Stats >= MaxPoints || Stats < 0))
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[AddStats] You have max points for this type!!!");
		return true;								 
	}
	else if ((MaxPoints < 0) && (Stats < 0) && (Stats >= MaxPoints))
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[AddStats] You have max points for this type!!!");
		return true;
	}

	int StatsTemp = Stats; 
	Stats += Points;
#pragma warning(disable: 4018)
	if(gObj->LevelUpPoint < Points)
	{	
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[AddStats] You don't have enough points to add. Need %d more.", Points - gObj->LevelUpPoint);
		return true;
	}

	if((MaxPoints > 0) && (Stats > MaxPoints || Stats < 0))
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[AddStats] You can't add more than %d points for this type!!!", MaxPoints - StatsTemp);
		return true;								 
	}
	else if ((MaxPoints < 0) && (Stats < 0) && (Stats > MaxPoints))
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[AddStats] You can't add more than %d points for this type!!!", MaxPoints - StatsTemp);
		return true;
	}		

	TakeCommand(gObj, Config.Commands.AddPriceZen, Config.Commands.AddPricePCPoint, Config.Commands.AddPriceWCoin, "AddStats");
	if(Points > 200)
	{
		switch (Type)
		{
		case 0x00:
			gObj->Strength += Points;
			break;
		case 0x01:
			gObj->Dexterity += Points;  
			break;
		case 0x02:	  
			gObj->Vitality += Points; 
			break;	  
		case 0x03:
			gObj->Energy += Points;	 			 
			break;
		case 0x04:
			gObj->Leadership += Points;	  
			break;
		}
		gObj->LevelUpPoint -= Points;
		GCLevelUpMsgSend(gObj->m_Index, 0);
		Chat.MessageLog(1, c_Blue, t_COMMANDS, gObj, "[AddStats] Your %d stats added, please relogin!", Points);
	}
	else
	{
		BYTE lpMsg[5] = {0xC1,0x05,0xF3,0x06,Type};
		for(UINT i = 0; i < Points; i++)
			CGLevelUpPointAdd(lpMsg, gObj->m_Index); 
		GCLevelUpMsgSend(gObj->m_Index, 0);	  
		Chat.MessageLog(1, c_Blue, t_COMMANDS, gObj, "[AddStats] Your %d stats added, %d points left!", Points, gObj->LevelUpPoint);
	} 
	return true;
}

bool cChat::WareCommand(LPOBJ gObj, char *Msg)
{	 
	if(CheckCommand(gObj, Config.Commands.IsMultyVault, GmSystem.NONE, Config.Commands.ZenForChange, Config.Commands.PcPointForChange, Config.Commands.WCoinForChange, 0, 1, 0, "Ware", "/ware <num>", Msg))
		return true;   	 

	if(gObj->WarehouseSave != 0)
	{
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Ware] Close your vault first!");
		return true;
	}
	int WantSlot;
	sscanf(Msg, "%d", &WantSlot);
	 
	MySQL.Execute("SELECT UsedSlot FROM [%s].[dbo].[warehouse] WHERE AccountID = '%s'",MySQL.szDatabase, gObj->AccountID);
	int UsedSlot = MySQL.GetInt();
	 
	if(UsedSlot == NULL || UsedSlot == 0)
	{			   
		MySQL.Execute("UPDATE [%s].[dbo].[warehouse] SET Items01 = Items WHERE AccountID = '%s'",MySQL.szDatabase, gObj->AccountID); 
		MySQL.Execute("UPDATE [%s].[dbo].[warehouse] SET UsedSlot = 1 WHERE AccountID = '%s'",MySQL.szDatabase, gObj->AccountID); 
	}
	 
	if(WantSlot < 1 || WantSlot > Config.Commands.NumberOfVaults)
	{		  
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Ware] You can use from 1 to %d vaults!", Config.Commands.NumberOfVaults);
		return true;
	} 
	if((UsedSlot == WantSlot) || ((UsedSlot == NULL || UsedSlot == 0) && WantSlot == 1) )		 
	{		  
		MessageLog(1, c_Red, t_COMMANDS, gObj, "[Ware] You need to chose other vault number!");
		return true;
	} 
	TakeCommand(gObj, Config.Commands.ZenForChange, Config.Commands.PcPointForChange, Config.Commands.WCoinForChange, "Ware");	

	MySQL.Execute("UPDATE [%s].[dbo].[warehouse] SET Items%02d = Items WHERE AccountID = '%s'",MySQL.szDatabase, UsedSlot, gObj->AccountID);
	MySQL.Execute("UPDATE [%s].[dbo].[warehouse] SET Items = Items%02d WHERE AccountID = '%s'",MySQL.szDatabase, WantSlot, gObj->AccountID);
	MySQL.Execute("UPDATE [%s].[dbo].[warehouse] SET UsedSlot = %d WHERE AccountID = '%s'",MySQL.szDatabase, WantSlot, gObj->AccountID);

	MessageLog(1, c_Red, t_COMMANDS, gObj, "[Ware] You successfully change vault from %d to %d!", UsedSlot, WantSlot);
	return true;
}

bool cChat::SetZenCommand(LPOBJ gObj, char *Msg)
{
	if(CheckCommand(gObj, Config.Commands.IsSetZen, GmSystem.cSetZen, 0, 0, 0, 0, 2, 1, "SetZen", "/setzen <nick> <value>", Msg))
		return true;

	int Value;
	char Target[11]; 	 
	sscanf(Msg, "%s %d", &Target, &Value);	 	

	if(Value < 0 || Value > 2000000000)
	{
		MessageLog(1, c_Red, t_GM, gObj, "[SetZen] Value can't be less than 0 and more than 2000000000!");
		return true;
	}			 

	int Index = Utilits.GetPlayerIndex(Target); 
	OBJECTSTRUCT *tObj = (OBJECTSTRUCT*)OBJECT_POINTER(Index);

	tObj->Money = Value;
	GCMoneySend (tObj->m_Index, Value);		

	MessageLog(1, c_Red, t_GM, gObj, "[SetZen] You sucsessfully changed %s zen.", tObj->Name);
	MessageLog(1, c_Red, t_GM, tObj, "[SetZen] Your zen was changed to %d by %s.", Value, gObj->Name);
	return true;
}