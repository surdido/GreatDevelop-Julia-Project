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
	char Order[3];
	int MobId , temp , counter = 0, j = 0;
	bool flag = false;

	while(!feof(file))
	{
		fgets(zBuf,256,file);

		if (!strncmp(zBuf,"//",strlen("//")) || !strncmp(zBuf,"end",strlen("end")) || zBuf[0] == '\0' ) continue;

		sprintf(Order,"%d",counter);

		if (!strncmp(zBuf,Order,strlen(Order))) 
		{ 
			sscanf(zBuf,"%d %d",&temp,&MobId);
			flag = true;
			counter++;		
			j = 0;
			continue;
		}

		if (flag)
		{
			sscanf(zBuf,"%d %d %d %d %d %d %d %d %d %d %d %d",&ItemsDrop[MobId][j].Group,&ItemsDrop[MobId][j].Index,&ItemsDrop[MobId][j].RateItem,
				&ItemsDrop[MobId][j].MinLvl,&ItemsDrop[MobId][j].MaxLvl,&ItemsDrop[MobId][j].MinOpt,&ItemsDrop[MobId][j].MaxOpt,
				&ItemsDrop[MobId][j].RateSkill,&ItemsDrop[MobId][j].RateLuck,&ItemsDrop[MobId][j].RateExc,&ItemsDrop[MobId][j].MaxExcOpt,
				&ItemsDrop[MobId][j].RateAnc);
			
			ArrayMaxItem[MobId] = ++j;
		}
	}

	fclose(file);
	Log.ConsoleOutPut(1,c_Green,t_NULL,"[Drop System] Drop System Loaded");
}

bool cDropSystem::DropItem(LPOBJ mObj,LPOBJ pObj)
{
	if ( ArrayMaxItem[mObj->Class] == 0 ) return false;

	srand(GetTickCount());

	int RandomItem = rand() % ArrayMaxItem[mObj->Class];
	int RandomValue = rand() % 100 + 1;

	if (RandomValue > ItemsDrop[mObj->Class][RandomItem].RateItem) return false;

	int Level,Skill,Luck,Opt,Exc,Anc;

	/*Rand Level*/
	Level = rand() % (ItemsDrop[mObj->Class][RandomItem].MaxLvl + 1);
	if (Level < ItemsDrop[mObj->Class][RandomItem].MinLvl) Level = ItemsDrop[mObj->Class][RandomItem].MinLvl;
	/*Rand Opt*/
	Opt = rand() % (ItemsDrop[mObj->Class][RandomItem].MaxOpt + 1);
	if (Opt < ItemsDrop[mObj->Class][RandomItem].MinOpt) Opt = ItemsDrop[mObj->Class][RandomItem].MinOpt;
	/*Rand Luck*/
	Luck = rand() % 100;
	if (Luck < ItemsDrop[mObj->Class][RandomItem].RateLuck) 
		Luck = 1;
	else 
		Luck = 0;
	/*Rand Skill*/
	Skill = rand() % 100;

	if (Skill < ItemsDrop[mObj->Class][RandomItem].RateSkill) 
		Skill = 1;
	else 
		Skill = 0;
	/*Rand Exc Opt*/
	Exc = rand() % 100;
	if (Exc < ItemsDrop[mObj->Class][RandomItem].RateExc)
		Exc = Utilits.GenExcOpt(rand()%ItemsDrop[mObj->Class][RandomItem].MaxExcOpt+1);
	else
		Exc = 0;
	/*Rand Anc*/
	Anc = rand() % 100;
	if (Anc < ItemsDrop[mObj->Class][RandomItem].RateAnc)
		Anc = 5;
	else
		Anc = 0;

	int Item = ITEMGET(ItemsDrop[mObj->Class][RandomItem].Group,ItemsDrop[mObj->Class][RandomItem].Index);

	ItemSerialCreateSend (pObj->m_Index,pObj->MapNumber,(BYTE)pObj->X,(BYTE)pObj->Y,Item,Level,0,Skill,Luck,Opt,pObj->m_Index,Exc,0);

	Log.ConsoleOutPut(1,c_Green,t_DROP,"[Drop System] Near %s drop %d %d %d %d %d %d %d %d",
		pObj->Name,ItemsDrop[mObj->Class][RandomItem].Group,ItemsDrop[mObj->Class][RandomItem].Index,
		Level,Luck,Skill,Opt,Exc,Anc);

	return true;
} 