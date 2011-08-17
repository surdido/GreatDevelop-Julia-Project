// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.0								# //
// ================================================== //

#ifndef DROPSYSTEM
#define DROPSYSTEM

#define MAX_MONSTER_ID			600
#define MAX_ITEM_FOR_MONSTER	40

#include "User.h"

class cDropSystem
{
public:
	cDropSystem();
	~cDropSystem();
	void LoadDropItems();
	bool DropItem(LPOBJ mObj,LPOBJ pObj);

private:
	struct
	{
		short Map;
		short Group;
		short Index;
		short RateItem;
		short Level;
		short Option;
		short Skill;
		short Luck;
		short Exc;
	}ItemsDrop[MAX_MONSTER_ID][MAX_ITEM_FOR_MONSTER];

	unsigned char ArrayMaxItem[MAX_MONSTER_ID];
};

extern cDropSystem DropSystem;

#endif