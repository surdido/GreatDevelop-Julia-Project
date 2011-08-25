// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.1								# //
// ================================================== //

#include "DropSystem.h"
#include "StdAfx.h"
#include "Logger.h"
#include "Utilits.h"
#include "Configs.h"

#define ITEMGET(x,y) ((x)*512+(y))

cDropSystem DropSystem;

cDropSystem::cDropSystem() {};
cDropSystem::~cDropSystem() {};

void cDropSystem::LoadDropItems()
{
	FILE *file;
	file = fopen(GreatDevelopDropSystem,"r");

	if (file == NULL)
	{
		Log.ConsoleOutPut(1,c_Green,t_NULL,"[Drop System] Drop System not loaded");
		return;
	}

	char zBuf[256];
	bool flag = false;

	while(!feof(file))
	{
		fgets(zBuf,256,file);

		if (!strncmp(zBuf,"//",strlen("//")) || !strncmp(zBuf,"end",strlen("end")) || zBuf[0] == '\0' ) continue;

		if (!strncmp(zBuf,"0",strlen("0")) ) {flag = true; continue;}

		if (flag)
		{
			int n[10];
			sscanf(zBuf,"%d %d %d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8], &n[9]);
			int MobId = n[0];
			int j = ArrayMaxItem[MobId];
			ItemsDrop[MobId][j].Map			= n[1];
			ItemsDrop[MobId][j].RateItem	= n[2];
			ItemsDrop[MobId][j].Group		= n[3];
			ItemsDrop[MobId][j].Index		= n[4];
			ItemsDrop[MobId][j].Level		= n[5];
			ItemsDrop[MobId][j].Option		= n[6];
			ItemsDrop[MobId][j].Skill		= n[7];
			ItemsDrop[MobId][j].Luck		= n[8];
			ItemsDrop[MobId][j].Exc			= n[9];
			
			ArrayMaxItem[MobId] = ++j;
		}
	}

	fclose(file);
	Log.ConsoleOutPut(1,c_Green,t_NULL,"[Drop System] Drop System Loaded");
}

bool cDropSystem::DropItem(LPOBJ mObj,LPOBJ pObj)
{
	if(ArrayMaxItem[mObj->Class] == 0) return false;

	short MapArrayItem[MAX_ITEM_FOR_MONSTER];
	short CountArrayItem = 0;

	for(int i = 0; i < ArrayMaxItem[mObj->Class]; i++)
	{
		if(ItemsDrop[mObj->Class][i].Map == mObj->MapNumber)
		{
			MapArrayItem[CountArrayItem] = i;
			CountArrayItem++;
		}
	}

	if(CountArrayItem == 0) return false;

	srand(GetTickCount());

	int RandomValue = rand() % 100 + 1;

	short RateArrayItem[MAX_ITEM_FOR_MONSTER];
	short CountRateItem = 0;

	for(int j = 0; j < CountArrayItem; j++)
	{
		if(ItemsDrop[mObj->Class][MapArrayItem[j]].RateItem >= RandomValue)
		{
			RateArrayItem[CountRateItem] = MapArrayItem[j];
			CountRateItem++;
		}
	}

	if(CountRateItem == 0) return false;

	int RandomItem = rand() % CountRateItem;	

	int Level,Skill,Luck,Opt,Exc,Group,Index;

	Group	= ItemsDrop[mObj->Class][RateArrayItem[RandomItem]].Group;
	Index	= ItemsDrop[mObj->Class][RateArrayItem[RandomItem]].Group;
	Level	= ItemsDrop[mObj->Class][RateArrayItem[RandomItem]].Level;
	Opt		= ItemsDrop[mObj->Class][RateArrayItem[RandomItem]].Option;
	Luck	= ItemsDrop[mObj->Class][RateArrayItem[RandomItem]].Luck;
	Skill	= ItemsDrop[mObj->Class][RateArrayItem[RandomItem]].Skill; 
	Exc		= ItemsDrop[mObj->Class][RateArrayItem[RandomItem]].Exc;

	int Item = ITEMGET(Group,Index);

	ItemSerialCreateSend (mObj->m_Index,mObj->MapNumber,(BYTE)mObj->X,(BYTE)mObj->Y,Item,Level,0,Skill,Luck,Opt,pObj->m_Index,Exc,0);

	Log.ConsoleOutPut(1,c_Green,t_DROP,"[Drop System] [R=%d] Near %s drop %d %d %d %d %d %d %d",RandomValue,pObj->Name,Group,Index,Level,Luck,Skill,Opt,Exc);

	return true;
} 