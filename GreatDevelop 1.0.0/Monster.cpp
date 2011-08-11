// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.0								# //
// ================================================== //

#include "StdAfx.h"
#include "User.h"
#include "DropSystem.h"
#include "Utilits.h"
#include "PCPoint.h"
#include "Configs.h"

// Monster die Handler (hooked replacement for gObjMonsterDieGiveItem)
void __cdecl MonsterDie(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	PCPoint.RewardsPointsKillMob(lpTargetObj,lpObj,PCPOINT);
	PCPoint.RewardsPointsKillMob(lpTargetObj,lpObj,WCOIN);
	// Original function
	gObjMonsterDieGiveItem(lpObj, lpTargetObj);
}

#ifdef _GS
int MonsterAddAndSpawn(WORD Monster,BYTE Speed,BYTE Map,BYTE X, BYTE Y)
{
	int MobCount = *(DWORD *)(MonsterCount);

	if((MobCount + 1) < MonsterCount)
	{
		MobCount++;
		*(DWORD *)(MonsterCount) = MobCount;
		*(WORD *)(12 * MobCount + MonsterReads) = Monster;
		*(BYTE *)(12 * MobCount + MonsterReads+2) = Map;
		*(BYTE *)(12 * MobCount + MonsterReads+3) = Speed;
		*(BYTE *)(12 * MobCount + MonsterReads+4) = X;
		*(BYTE *)(12 * MobCount + MonsterReads+5) = Y;
		*(BYTE *)(12 * MobCount + MonsterReads+6) = 2;
		*(BYTE *)(12 * MobCount + MonsterReads+7) = X;
		*(BYTE *)(12 * MobCount + MonsterReads+8) = Y;

		int MobID = gObjAddMonster(*(BYTE *)(12 * MobCount + (MonsterReads+2)));
		if(MobID>=0)
		{
			int MobNr = *(WORD *)(12 * MobCount + MonsterReads);
			gObjSetPosMonster(MobID, MobCount);
			gObjSetMonster(MobID, MobNr);
		}

		return MobID;
	}else
	{		
		MessageBox(NULL,"Monster attribute max over!!", "Monsters overflow", 0);
		return -1;
	}
}
#endif

//Monster Death Control
int MygEventMonsterItemDrop(BYTE *b_MonsterDataAddr,BYTE *a_gObjAddr)
{
	// Get mIndex, aIndex & Monster & Player Objects
	PBYTE a_aIndex = 0;
	PBYTE b_mIndex = 0;

	a_aIndex = (PBYTE)a_gObjAddr;
	b_mIndex = (PBYTE)b_MonsterDataAddr;

	WORD mIndex = 0;
	WORD aIndex = 0;

	memcpy(&mIndex, b_mIndex+0x00,sizeof(WORD));
	memcpy(&aIndex, a_aIndex+0x00,sizeof(WORD));

	OBJECTSTRUCT *mObj = (OBJECTSTRUCT*) OBJECT_POINTER (mIndex);
	OBJECTSTRUCT *pObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	//ZenFixes
	if(Config.Zen.Enabled)
	{
		if(pObj->DbClass == 3 || pObj->DbClass == 19 || pObj->DbClass == 35 || pObj->DbClass == 51 || pObj->DbClass == 66 || pObj->DbClass == 83 || pObj->DbClass == 98)
		{
			int NewMoneyML = Utilits.gObjZenSingle(pObj,mObj,500,700);
			mObj->Money = (NewMoneyML/Config.Zen.MasterDivisor) * Config.Zen.MasterZen; 
		}
		else
		{
			int NewMoneyNormal = Utilits.gObjZenSingle(pObj,mObj,500,700);
			mObj->Money = (NewMoneyNormal/Config.Zen.NormalDivisor) * Config.Zen.NormalZen;
		}
	}
	//PartyZenFixes
	if(Config.PartyZen.Enabled)
	{
		if(pObj->PartyNumber != -1)
		{
			int AllPartyLevel = 0;
			int Count = 0;

			for(int i=OBJECT_MIN;i<OBJECT_MAX;i++)
			{
				OBJECTSTRUCT *gObj = (OBJECTSTRUCT*) OBJECT_POINTER (i);

				if(gObj->Connected == PLAYER_PLAYING)
				{
					if(gObj->PartyNumber == pObj->PartyNumber)
					{
						AllPartyLevel += gObj->Level;
						Count++;
					}
				}
			} 
			//Master Party
			if(pObj->DbClass == 3 || pObj->DbClass == 19 || pObj->DbClass == 35 || pObj->DbClass == 51 || pObj->DbClass == 66 || pObj->DbClass == 83 || pObj->DbClass == 98)
				mObj->Money = (mObj->Money * Config.PartyZen.MasterZen)*((AllPartyLevel/Count)/(Config.PartyZen.MasterDivisor)); 
			//Normal
			else  
				mObj->Money = (mObj->Money* Config.PartyZen.NormalZen)*((AllPartyLevel/Count)/Config.PartyZen.NormalDivisor);
		}
	}

	// Drop System
	if(DropSystem.DropItem(mObj,pObj))
	{
		return 1;
	}
	else // Default drop
	{
		int rValue = gEventMonsterItemDrop(b_MonsterDataAddr, a_gObjAddr);
		return rValue;
	}

	return 1;
}
