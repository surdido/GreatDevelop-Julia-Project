// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Tornado Lite - 7.12.XX					# //
// ================================================== //

#include "Stdafx.h" 
#include "AntiAFK.h"
#include "ChatCommands.h"
#include "User.h"
#include "Configs.h" 


cAntiAFK AntiAFK;

cAntiAFK::cAntiAFK()
{
	this->ReWarning = 0;
}

cAntiAFK::~cAntiAFK()
{

}				   


void cAntiAFK::SendInfo(LPOBJ gObj)
{
	int Index = gObj->m_Index;
	AddTab[Index].AFK_Timer++;

	if ( this->ArrayMap[gObj->MapNumber] == 0 )
	{
		AddTab[Index].AFK_Timer = 0;
	}

	if(gObj->MapNumber != AddTab[Index].AFK_MapNumber || (gObj->MapNumber > 60 && gObj->MapNumber < 65))
	{
		AddTab[Index].AFK_MapNumber = gObj->MapNumber;
		AddTab[Index].AFK_Timer = 0;
		AddTab[Index].AFK_Temp = gObj->m_TotalAttackCount;
	}	
	if(gObj->X != AddTab[Index].AFK_X)
	{
		AddTab[Index].AFK_X = gObj->X;		
		AddTab[Index].AFK_Timer = 0;	 
		AddTab[Index].AFK_Temp = gObj->m_TotalAttackCount;

	}						 
	if(gObj->Y != AddTab[Index].AFK_Y)
	{						   
		AddTab[Index].AFK_Y = gObj->Y;	 
		AddTab[Index].AFK_Timer = 0;	   
		AddTab[Index].AFK_Temp = gObj->m_TotalAttackCount;
	}

	if (gObj->m_TotalAttackCount != AddTab[Index].AFK_Temp && AddTab[Index].AFK_Timer >= Config.AntiAfkConfig.Time && ReWarning != Config.AntiAfkConfig.Warnings)
	{
		AddTab[Index].AFK_Timer = 0;	
		AddTab[Index].AFK_Temp = gObj->m_TotalAttackCount;	 
		AddTab[Index].AFK_Y = gObj->Y;	 	 
		AddTab[Index].AFK_X = gObj->X;			   
		AddTab[Index].AFK_MapNumber = gObj->MapNumber;
		this->ReWarning++; 
		Chat.MessageLog(1, c_Red, t_Default, gObj,"[AntiAfk][%s] Current Warning Number: %d",gObj->Name,ReWarning);
	}

	if(gObj->m_TotalAttackCount != AddTab[Index].AFK_Temp && AddTab[Index].AFK_Timer >= Config.AntiAfkConfig.Time)
	{			 					   
		AddTab[Index].AFK_Timer = 0;   		  
		AddTab[Index].AFK_Temp = gObj->m_TotalAttackCount;	 
		AddTab[Index].AFK_Y = gObj->Y;	 	 
		AddTab[Index].AFK_X = gObj->X;			   
		AddTab[Index].AFK_MapNumber = gObj->MapNumber; 
		Chat.MessageLog(1, c_Red, t_Default, gObj, "[AntiAfk] Warping To Lorencia Safe Zone!!!"); 
		int Rand1 = rand() % 5;
		int Rand2 = rand() % 5;
		gObjTeleport(Index,0,139 + Rand1,132 + Rand2);
		ReWarning = 0;
	}
}

void cAntiAFK::Load()
{
	FILE *antiafk;
	char buf[256];
	int nummap, value;
	bool flag = false;
	antiafk = fopen(RMSTAntiAFK,"r");
	if ( antiafk != NULL )
	{
		while ( !feof(antiafk) )
		{
			fgets(buf,256,antiafk);
			if ( buf[0] == '/' && buf[1] == '/' ) continue;
			if ( buf[1] == 'M' && buf[2] == 'a' && buf[3] == 'p') 
			{
				flag = true;
				continue;
			}
			if (flag)
			{
				sscanf(buf,"%d %d",&nummap,&value);
				this->ArrayMap[nummap] = value;
			}
		}
	}
	fclose(antiafk);
}