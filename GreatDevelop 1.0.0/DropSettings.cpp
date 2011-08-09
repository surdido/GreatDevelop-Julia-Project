// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Storm & Tornado Projects 2010-2011		# //
// ================================================== //

#include "StdAfx.h" 
#include "DropSettings.h"
#include "ChatCommands.h" 
#include "Logger.h"
#include "Configs.h" 
#include "Utilits.h"

cDropSystem DropSystem;

cDropSystem::cDropSystem() // Constructor
{
}

cDropSystem::~cDropSystem() // Destructor
{
}

void cDropSystem::LoadConfig()
{
	// Clear existing config
	this->dropCountMob.clear();
	this->dropList.clear();
	this->dropListMap.clear();
	this->dropListMob.clear();
	this->dropListVar.clear();

	// Load new config
	FILE *fp;
	fp = fopen(RMSTDrop, "r");
	rewind(fp);

	if(fp == NULL)
	{
		Log.ConsoleOutPut(1, c_Cyan, t_Default, "[Drop System] System not active. Config file not found: %s", RMSTDrop);
		return;
	}

	e_confType confType = MISC; // MISC / MOBITEMCOUNT / DROPLIST
	char fpLine[255]; // config file line

	int mapId, mobId;
	s_DropSystemMob mobDropCount = {0};
	s_DropSystemItem lineDrop = {0}; // array for line parser

	while(!feof(fp))
	{
		fgets(fpLine, 255, fp);

		// Skip comments & end's
		if(fpLine[0] == '/' || strcmp(fpLine, "end") == 0 || strcmp(fpLine, "end\n") == 0 || strcmp(fpLine, "\n") == 0) continue;

		// Config Type
		if (strcmp(fpLine, "0") == 0 || strcmp(fpLine, "0\n") == 0) { confType = MOBITEMCOUNT; continue; }
		if (strcmp(fpLine, "1") == 0 || strcmp(fpLine, "1\n") == 0) { confType = DROPLIST; continue; }

		// Skip misc
		if (confType == MISC) continue;

		// Make new config
		switch (confType)
		{
			case MOBITEMCOUNT:

				sscanf_s(fpLine, "%d %d %d %d", &mobDropCount.mobId, &mobDropCount.rateCount, &mobDropCount.dropCountMin, &mobDropCount.dropCountMax);
				this->dropCountMob[mobDropCount.mobId].push_back(mobDropCount);

			break;

			case DROPLIST:

				// Map, Mob, mLvlMin, mLvlMax, %Rate, Type, Idx, minLvl, maxLvl, Dur, %Skill, %Luck, minOpt, maxOpt, %Exc, minExc, maxExc, %Anc, ancType
				sscanf_s(fpLine, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &mapId, &mobId, &lineDrop.mobLvlMin, &lineDrop.mobLvlMax, &lineDrop.dropRate, &lineDrop.iGroup, &lineDrop.iId, &lineDrop.minLvl, &lineDrop.maxLvl, &lineDrop.dur, &lineDrop.skill, &lineDrop.luck, &lineDrop.minOpt, &lineDrop.maxOpt, &lineDrop.exc, &lineDrop.minExc, &lineDrop.maxExc, &lineDrop.anc, &lineDrop.ancType);

				if (mapId == -1 && mobId == -1)
				{
					this->dropList.push_back(lineDrop);
				}
				else if (mapId == -1 && mobId != -1)
				{
					this->dropListMob[mobId].push_back(lineDrop);
				}
				else if (mapId != -1 && mobId == -1)
				{
					this->dropListMap[mapId].push_back(lineDrop);
				}
				else {
					int v = mapId * 1024 + mobId;
					this->dropListVar[v].push_back(lineDrop);
				}

			break;
		}
	}

	fclose(fp);

	Log.ConsoleOutPut(1, c_Cyan, t_Default, "[Drop System] Load sucsessfully.");
}

bool cDropSystem::DropItem(LPOBJ mObj, LPOBJ pObj)
{
	// Vars
	int mobKillerIndex = (int) pObj->m_Index;
	int mobIndex = (int) mObj->m_Index;
	int mobId = (int) mObj->Class;
	int mobLvl = (int) mObj->Level;
	int mobMap = (int) mObj->MapNumber;
	int mobX = (int) mObj->X;
	int mobY = (int) mObj->Y;

	bool itemDropped = false;

	if (this->dropCountMob[mobId].size() == 1)
	{
		// Vector vars
		int mobRateCount = this->dropCountMob[mobId].front().rateCount;
		int mobDropCountMin = this->dropCountMob[mobId].front().dropCountMin;
		int mobDropCountMax = this->dropCountMob[mobId].front().dropCountMax;

		// User input fix's
		if (mobDropCountMin > 10) mobDropCountMin = 10; // 10 max
		if (mobDropCountMin < 1) mobDropCountMin = 1; // 1 min
		if (mobDropCountMax > 10) mobDropCountMax = 10; // 10 max
		if (mobDropCountMax < 1) mobDropCountMax = 1; // 1 min
		if (mobDropCountMin > mobDropCountMax) mobDropCountMin = mobDropCountMax;

		// Items drop count
		int mobDropCountVal = (mobDropCountMin == mobDropCountMax) ? mobDropCountMin : mobDropCountMin + rand() % (mobDropCountMax - mobDropCountMin + 1);

		// Random system
		if ((rand() % 100 + 1) <= mobRateCount)
		{
			for (int i=0; i < mobDropCountVal; i++)
			{
				if (this->SearchAndDrop(mobIndex, mobId, mobLvl, mobMap, mobX, mobY, mobKillerIndex)) itemDropped = true;
			}
		}
		else {
			if (this->SearchAndDrop(mobIndex, mobId, mobLvl, mobMap, mobX, mobY, mobKillerIndex)) itemDropped = true;
		}
	}
	else {
		if (this->SearchAndDrop(mobIndex, mobId, mobLvl, mobMap, mobX, mobY, mobKillerIndex)) itemDropped = true;
	}

	return itemDropped;
}

bool cDropSystem::SearchAndDrop(int mIndex, int mobId, int mobLvl, int mobMap, int mobX, int mobY, int aIndex)
{
	// Vars
	bool itemFoud = false;
	std::vector<s_DropSystemItem>::iterator i;

	// Random system
	int rand10k = rand() % 10000 + 1;
	int d = 0;

	// DROP => Map: 123 ; Mob: 123
	//---------------------------------------------------------------------------
	int MobMapId = mobMap * 1024 + mobId;

	if (!itemFoud && this->dropListVar[MobMapId].size() > 0)
	{
		for(i = this->dropListVar[MobMapId].begin(); i < this->dropListVar[MobMapId].end(); i++)
		{
			// If this mob not in item mob lvl range = skip
			if (mobLvl < i->mobLvlMin || mobLvl > i->mobLvlMax) continue;

			if (rand10k > d && rand10k < (d + i->dropRate))
			{
				// Item founded -> Drop procedure & break
				this->CreateAndDrop(mIndex, mobMap, mobX, mobY, aIndex, *i);
				itemFoud = true;
				break;
			}
			else {
				d += i->dropRate;
			}
		}
	}

	// DROP => Map: -1 ; Mob: 123
	//---------------------------------------------------------------------------
	if (!itemFoud && this->dropListMob[mobId].size() > 0)
	{
		for(i = this->dropListMob[mobId].begin(); i < this->dropListMob[mobId].end(); i++)
		{
			// If this mob not in item mob lvl range = skip
			if (mobLvl < i->mobLvlMin || mobLvl > i->mobLvlMax) continue;

			if (rand10k > d && rand10k < (d + i->dropRate))
			{
				// Item founded -> Drop procedure & break
				this->CreateAndDrop(mIndex, mobMap, mobX, mobY, aIndex, *i);
				itemFoud = true;
				break;
			}
			else {
				d += i->dropRate;
			}
		}
	}

	// DROP => Map: 123 ; Mob: -1
	//---------------------------------------------------------------------------
	if (!itemFoud && this->dropListMap[mobMap].size() > 0)
	{
		for(i = this->dropListMap[mobMap].begin(); i < this->dropListMap[mobMap].end(); i++)
		{
			// If this mob not in item mob lvl range = skip
			if (mobLvl < i->mobLvlMin || mobLvl > i->mobLvlMax) continue;

			if (rand10k > d && rand10k < (d + i->dropRate))
			{
				// Item founded -> Drop procedure & break
				this->CreateAndDrop(mIndex, mobMap, mobX, mobY, aIndex, *i);
				itemFoud = true;
				break;
			}
			else {
				d += i->dropRate;
			}
		}
	}

	// DROP => Map: -1 ; Mob: -1
	//---------------------------------------------------------------------------
	if (!itemFoud)
	{
		for(i = this->dropList.begin(); i < this->dropList.end(); i++)
		{
			// If this mob not in item mob lvl range = skip
			if (mobLvl < i->mobLvlMin || mobLvl > i->mobLvlMax) continue;

			if (rand10k > d && rand10k < (d + i->dropRate))
			{
				// Item founded -> Drop procedure & break
				this->CreateAndDrop(mIndex, mobMap, mobX, mobY, aIndex, *i);
				itemFoud = true;
				break;
			}
			else {
				d += i->dropRate;
			}
		}
	}

	return itemFoud;
}

void cDropSystem::CreateAndDrop(int aIndex, BYTE MapNumber, BYTE x, BYTE y, int LootIndex, s_DropSystemItem&i)
{
	// User input fix's
	if (i.minLvl > i.maxLvl) i.minLvl = i.maxLvl;
	if (i.minOpt > i.maxOpt) i.minOpt = i.maxOpt;
	if (i.minExc > i.maxExc) i.minExc = i.maxExc;

	// Drop procedure
	int i_item = i.iGroup * 512 + i.iId;
	int i_lvl = (i.minLvl == i.maxLvl) ? i.minLvl : i.minLvl + rand() % (i.maxLvl - i.minLvl + 1);
	int i_skill = ((rand() % 100 + 1) <= i.skill) ? 1 : 0;
	int i_luck = ((rand() % 100 + 1) <= i.luck) ? 1 : 0;
	int i_opt = (i.minOpt == i.maxOpt) ? i.minOpt : i.minOpt + rand() % (i.maxOpt - i.minOpt + 1);

	// Exc randomizer
	int i_exc = 0;

	if ((rand() % 100 + 1) <= i.exc)
	{
		i_exc = Utilits.GenExcOpt((i.minExc == i.maxExc) ? i.minExc : i.minExc + rand() % (i.maxExc - i.minExc + 1));
	}

	// Anc randomizer
	int i_anc_type = (i.ancType == 5 || i.ancType == 10) ? i.ancType : 0;
	int i_anc = ((rand() % 100 + 1) <= i.anc) ? i_anc_type : 0;

	// Drop
	ItemSerialCreateSend(aIndex, MapNumber, x, y, i_item, i_lvl, i.dur, i_skill, i_luck, i_opt, LootIndex, i_exc, i_anc);

	// Log
	Log.ConsoleOutPut(1, c_Green, t_Default, "[Drop System] Drop Item -> Map: %d (%d;%d) Item: %d;%d", MapNumber, x, y, i.iGroup, i.iId);
}
