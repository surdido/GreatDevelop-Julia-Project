// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.0								# //
// ================================================== //

#include "StdAfx.h"
#include "Configs.h"
#ifdef _GS
#include "MossGambler.h" 
#include "Prodef.h"
#include "User.h"
#include "ChatCommands.h" 
#include "Utilits.h"
#include "SQL.h"
#include "PCPoint.h"
#include "Monster.h"
Moss moss;
#define ITEMGET(x,y) ((x)*512+(y))
enum {OPT_LEVEL,OPT_SKILL,OPT_LUCK,OPT_ADD,OPT_EXC,OPT_ANC};

struct PMSG_BUYRESULT
{
	PBMSG_HEAD h;	// C1:32
	BYTE Result;	// 3
	BYTE ItemInfo[12];	// 4
};

void MossBuyDelay(void *lparam)
{
	moss.g_MossDelay = true;
	Sleep(1500);
	moss.g_MossDelay = false;
	_endthread();
}

Moss::Moss() {}
Moss::~Moss() {}

void Moss::DataSendMoss(int Index)
{
	PMSG_BUYRESULT pRez;
	pRez.h.c=0xC1;
	pRez.h.headcode=0x32;
	pRez.h.size=16;
	DataSend(Index,(LPBYTE)&pRez,pRez.h.size);
}

void Moss::LoadMoss()
{
	MossConfig.EnableMoss		= Config.GetInt(0,1,0,"Moss","EnableMoss",RMSTMossGambler); 
	if(!MossConfig.EnableMoss)return;

	MossConfig.EnableTimer		= Config.GetInt(0,1,0,"Moss","EnableTimer",RMSTMossGambler);
	MossConfig.UsePK			= Config.GetInt(0,1,0,"Moss","UsePK",RMSTMossGambler);

	MossConfig.PriceZen			= Config.GetInt(0,2000000000,100000000,"Moss","PriceZen",RMSTMossGambler);
	MossConfig.PricePCPoint		= Config.GetInt(0,1000,10,"Moss","PricePCPoint",RMSTMossGambler);
	MossConfig.PriceWCoin		= Config.GetInt(0,1000,10,"Moss","PriceWCoin",RMSTMossGambler);

	MossConfig.RandExc			= Config.GetInt(0,100,50,"Random","RandExc",RMSTMossGambler);
	MossConfig.MaxExcOpt		= Config.GetInt(0,100,6,"Random","MaxExcOpt",RMSTMossGambler);

	MossConfig.RandLevel		= Config.GetInt(0,100,85,"Random","RandLevel",RMSTMossGambler);
	MossConfig.MaxLevel			= Config.GetInt(0,100,13,"Random","MaxLevel",RMSTMossGambler);

	MossConfig.RandOptAdd		= Config.GetInt(0,100,85,"Random","RandOptAdd",RMSTMossGambler);
	MossConfig.MaxOptAdd		= Config.GetInt(0,100,7,"Random","MaxOptAdd",RMSTMossGambler);

	MossConfig.RandLuck			= Config.GetInt(0,100,50,"Random","RandLuck",RMSTMossGambler);
	MossConfig.RandSkill		= Config.GetInt(0,100,50,"Random","RandSkill",RMSTMossGambler);
	MossConfig.RandAncient		= Config.GetInt(0,100,20,"Random","RandAncient",RMSTMossGambler);
	moss.LoadItemInfo();
	if (MossConfig.EnableTimer) moss.LoadTimeConfig();
}

void Moss::LoadItemInfo()
{
	FILE *file;
	file = fopen("..\\Data\\Lang\\Kor\\Item(Kor).txt","r");

	if (file == NULL)
	{
		Log.ConsoleOutPut(0,c_Red,t_NULL,"[Moss The Gambler] Error Open Item(Kor).txt, Moss The Gambler Disabled");
		MossConfig.EnableMoss = 0;
		return;
	}

	char zBuf[1024];
	int group = 0;
	int j = 0;

	while (!feof(file))
	{
		fgets(zBuf,1024,file);

		if (!strncmp(zBuf,"//",strlen("//")) || !strncmp(zBuf,"end",strlen("end")) || zBuf[0] == 0xA ) continue;

		char c[2];
		sprintf(c,"%d",group);

		if (!strncmp(zBuf,c,strlen(c)))
		{
			group++;
			if (group > 6) break;
			j = 0;
			continue;
		}
		if (group > 0)
		{
			sscanf(zBuf,"%d ",	&ItemInfo[group-1][j].Index);	
			OrderItems[group-1] = ++j;
		}
	}
	Log.ConsoleOutPut(1,c_Blue,t_NULL,"[Moss The Gambler] Moss The Gambler Loaded succesfully");
	fclose(file);
}

void Moss::LoadTimeConfig()
{ 
	FILE * file;

	file = fopen(RMSTEventTime,"r");

	if (file == NULL)
	{
		Log.ConsoleOutPut(0,c_Red,t_NULL,"[Moss The Gambler] Error Open EventTime.dat, Timer In Moss The Gambler Disabled");
		MossConfig.EnableTimer = 0;
		return;
	}

	char zbuf[1024]; bool flag = false; int j = 0;

	while (!feof(file))
	{
		fgets(zbuf,1024,file);

		if (!strncmp(zbuf,"//",strlen("//")) || zbuf[0] == 0xA || !strncmp(zbuf,"end",strlen("end"))) continue;

		if (!strncmp(zbuf,"0",strlen("0")))
		{
			flag = true;
			continue;
		}
		if (flag)
		{
			int indexEvent,closeHour,closeMin;
			sscanf(zbuf,"%d %d %d %d",&indexEvent,&MossTimer[j].hour,&MossTimer[j].minute,&MossTimer[j].delay);
			if (indexEvent != 1) break;

			closeMin = MossTimer[j].minute + MossTimer[j].delay;
			closeHour = MossTimer[j].hour;

			while (closeMin >= 60)	{ closeMin -=60; closeHour++; }

			MossTimer[j].closehour = closeHour;
			MossTimer[j].closemin = closeMin;
			j++;
		}
	}
	this->AmountTimers = j;
	OpenedMoss = FALSE; 
}

void Moss::CheckTime()
{
	CTime t = CTime::GetCurrentTime();

	short hour,min;

	min = t.GetMinute();
	hour = t.GetHour();

	if (this->OpenedMoss == FALSE)
		this->DisappearMoss();

	if (t.GetSecond() == 0)
	{
		for (int i=0; i<AmountTimers; i++)
		{
			for (int j=1; j<6; j++)
			{
				int BeforeOpenMin, BeforeOpenHour;
				BeforeOpenMin = MossTimer[i].minute - j;
				BeforeOpenHour = MossTimer[i].hour;

				if (BeforeOpenMin < 0 ) {BeforeOpenMin += 60; BeforeOpenHour --;}

				if (hour == BeforeOpenHour && min == BeforeOpenMin)
				{
					Chat.MessageAll(0,0,NULL,"[Moss The Gambler] Moss The Gambler is Opened before %d minutes",j);
					break;
				}
			}

			if (hour == MossTimer[i].hour && min == MossTimer[i].minute)
			{
				Chat.MessageAll(0,0,NULL,"[Moss The Gambler] Is arrived!");
				this->SpawnMoss();
				this->OpenedMoss = TRUE;
			}

			if (hour == MossTimer[i].closehour && min == MossTimer[i].closemin)
			{
				Chat.MessageAll(0,0,NULL,"[Moss The Gambler] Closed!");
				this->DisappearMoss();
				this->OpenedMoss = FALSE;
			}
		}
	}
}

BOOL Moss::GetStatusMoss()
{
	if(MossTimer)
		return this->OpenedMoss;
	else
		return TRUE;
}

void Moss::SpawnMoss()
{
	MonsterAddAndSpawn(492,0,51,22,225);
}

void Moss::DisappearMoss()
{
	for(int iIndex = 0; iIndex < OBJ_MAXMONSTER; iIndex++)
	{
		OBJECTSTRUCT *mObj = (OBJECTSTRUCT*)OBJECT_POINTER(iIndex);
		if (mObj == NULL) return;
		if(mObj->Class == 492)	gObjDel(iIndex);

	}
	int MobCount = *(DWORD *)(MonsterCount);
	MobCount--;
}

BOOL Moss::BuyItem(int aIndex, unsigned char * aRecv)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);

	if (gObj->TargetShopNumber != 492) return FALSE;
	
	if (moss.GetStatusMoss() == FALSE)
	{
		Chat.Message(aIndex,"[Moss The Gambler] Moss The Gambler Close");
		return TRUE;
	}

	if ( this->g_MossDelay == true )
	{
		Chat.Message(aIndex,"[Moss The Gambler] Please wait 1.5 second after a previous purchase");
		return TRUE;
	}

	if (gObj->Money < MossConfig.PriceZen)
	{
		Chat.Message(gObj->m_Index,"[Moss The Gambler] You haven't got enough money");
		return TRUE;
	}

	if (AddTab[gObj->m_Index].PC_PlayerPoints < MossConfig.PricePCPoint)
	{
		Chat.Message(gObj->m_Index,"[Moss The Gambler] You haven't got enough PCPoint");
		return TRUE;
	}

	if (gObj->m_wCashPoint < MossConfig.PriceWCoin)
	{
		Chat.Message(gObj->m_Index,"[Moss The Gambler] You haven't got enough WCoin");
		return TRUE;
	}
	srand(GetTickCount());
	/*Узнаем какую группу оружия было выбрано*/
	if (aRecv[3] == 0 )  BuyType = 0;
	if (aRecv[3] == 2 )  { BuyType = rand()%2+1;	if (BuyType == 2) BuyType = 3;	}
	if (aRecv[3] == 4 )  BuyType = 2;
	if (aRecv[3] == 6 )  BuyType = 4;
	if (aRecv[3] == 24 ) BuyType = 5;

	int Index = rand()%OrderItems[BuyType];
	int Type = ITEMGET(BuyType,ItemInfo[BuyType][Index].Index);
	int Level	 = RandValue(OPT_LEVEL);
	int Option1	 = RandValue(OPT_SKILL);
	int Option2	 = RandValue(OPT_LUCK);
	int Option3	 = RandValue(OPT_ADD);
	int NewOption = RandValue(OPT_EXC);
	int SetOption = RandValue(OPT_ANC);

	int X,Y;
	GSItemGetSize(Type,X,Y);

	if (GSCheckInventoryEmptySpace(gObj,Y,X) == 0)
	{
		Chat.Message(gObj->m_Index,"[Moss The Gambler] You inventory is full");
		return TRUE;
	}

	int Dur = ItemGetDurability(Type,Level,NewOption,SetOption);
	ItemSerialCreateSend(gObj->m_Index,236,0,0,Type,Level,Dur,Option1,Option2,Option3,0,NewOption,SetOption);

	Log.ConsoleOutPut(0, c_Red,t_NULL,"[Moss The Gambler] %s Win [%d] %d %d %d %d %d %d",
		gObj->Name,Type,Level,Option1,Option2,Option3,NewOption,SetOption);

	if (NewOption > 0)
		Chat.Message(gObj->m_Index,"[Moss The Gambler] Congratulations, you are very lucky!!!");

	gObj->Money -= MossConfig.PriceZen;
	GCMoneySend(gObj->m_Index,gObj->Money);
	if(MossConfig.PricePCPoint > 0) PCPoint.UpdatePoints(gObj,MossConfig.PricePCPoint,PC_DEL,PCPOINT);
	if(MossConfig.PriceWCoin > 0)   PCPoint.UpdatePoints(gObj,MossConfig.PriceWCoin  ,PC_DEL,WCOIN);

	_beginthread(MossBuyDelay,0,0);
	return TRUE;
}

int Moss::RandValue(int IndexOption)
{
	int rValue;
	srand((unsigned) GetTickCount());
	switch(IndexOption)
	{
	case OPT_LEVEL:
		{
			rValue = rand()%100+1;
			rValue > MossConfig.RandLevel ?	rValue =  0 : rValue =  rand()%(MossConfig.MaxLevel + 1);
		}
		break;
	case OPT_SKILL:
		{
			rValue = rand()%100+1;
			rValue > MossConfig.RandSkill ? rValue =  0 : rValue =  1;
		}
		break;
	case OPT_LUCK:
		{
			rValue = rand()%100+1;
			rValue > MossConfig.RandLuck ? rValue =  0 : rValue =  1;
		}
		break;
	case OPT_ADD:
		{
			rValue = rand()%100+1;
			rValue > MossConfig.RandOptAdd ? rValue =  0 : rValue =  rand()%(MossConfig.MaxOptAdd + 1);
		}
		break;
	case OPT_EXC:
		{
			rValue = rand()%100+1;
			rValue > MossConfig.RandExc ? rValue =  0 : rValue =  Utilits.GenExcOpt(rand()%(MossConfig.MaxExcOpt + 1));
		}
		break;
	case OPT_ANC:
		{
			rValue = rand()%100+1;
			rValue > MossConfig.RandAncient ? rValue =  0 : rValue =  10;
		}
		break;
	}
	return rValue;
}

#endif