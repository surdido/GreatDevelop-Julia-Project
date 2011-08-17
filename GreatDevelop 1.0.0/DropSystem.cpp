// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.0								# //
// ================================================== //

#include "DropSystem.h"
#include "StdAfx.h"
#include "Logger.h"
#include "Utilits.h"

#define RMSTDropSystem "..\\RMST\\DropSystem.ini"
#define ITEMGET(x,y) ((x)*512+(y))

cDropSystem DropSystem;

cDropSystem::cDropSystem() {};
cDropSystem::~cDropSystem() {};

void cDropSystem::LoadDropItems()
{
	FILE *file;
	file = fopen(RMSTDropSystem,"r");

	if (file == NULL)
	{
		Log.ConsoleOutPut(1,c_Green,t_NULL,"[Drop System] Drop System Loaded");
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

	int RandomItem = rand() % CountArrayItem;
	int RandomValue = rand() % 100 + 1;

	if (RandomValue > ItemsDrop[mObj->Class][RandomItem].RateItem) return false;

	int Level,Skill,Luck,Opt,Exc;

	Level	= ItemsDrop[mObj->Class][RandomItem].Level;
	Opt		= ItemsDrop[mObj->Class][RandomItem].Option;
	Luck	= ItemsDrop[mObj->Class][RandomItem].Luck;
	Skill	= ItemsDrop[mObj->Class][RandomItem].Skill; 
	Exc		= ItemsDrop[mObj->Class][RandomItem].Exc;

	int Item = ITEMGET(ItemsDrop[mObj->Class][RandomItem].Group,ItemsDrop[mObj->Class][RandomItem].Index);

	ItemSerialCreateSend (pObj->m_Index,pObj->MapNumber,(BYTE)pObj->X,(BYTE)pObj->Y,Item,Level,0,Skill,Luck,Opt,pObj->m_Index,Exc,0);

	Log.ConsoleOutPut(1,c_Green,t_DROP,"[Drop System] Near %s drop %d %d %d %d %d %d %d",
		pObj->Name,ItemsDrop[mObj->Class][RandomItem].Group,ItemsDrop[mObj->Class][RandomItem].Index,
		Level,Luck,Skill,Opt,Exc);

	return true;
} 