// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.0								# //
// ================================================== //

#ifndef GOLDEN_H
#define GOLDEN_H

#include "User.h"

#define MAX_ITEM_PRIZE 100

class cGoldenArcher
{
public:
	cGoldenArcher();
	~cGoldenArcher();
	void LoadPrizeItems();
	void GoldenArcherClick(LPOBJ gObj);
	bool ChekingRena(LPOBJ gObj,int Mode);
private:
	struct
	{
		short Index;
		short ItemID;
		short RateItem;
		short MaxLvl;
		short RateSkill;
		short RateLuck;
		short MaxOpt;
		short RateExc;
		short MaxExcOpt;
	}ItemsPrize[MAX_ITEM_PRIZE];
	int MaxRateItem;
	int counter;
};

extern cGoldenArcher GoldenArcher;

#endif

