// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Storm & Tornado Projects 2010-2011		# //
// ================================================== //
#include "StdAfx.h"
#ifndef MONSTER_H
#define MONSTER_H

int MygEventMonsterItemDrop(BYTE *b_MonsterDataAddr,BYTE *a_gObjAddr);		   
void __cdecl MonsterDie(LPOBJ lpObjOfMonster, LPOBJ lpObjOfPlayer);	 
#ifdef GS90
int MonsterAddAndSpawn(WORD Monster,BYTE Speed,BYTE Map,BYTE X, BYTE Y);
#endif
#define OBJ_MAXMONSTER 7400
#endif