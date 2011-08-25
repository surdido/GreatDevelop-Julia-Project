// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.1								# //
// ================================================== //

#include "User.h" 
#ifdef _GS
#ifndef MOSS_H
#define MOSS_H 
class Moss
{
public:
	Moss();
	~Moss();
	void LoadMoss();  
	void LoadMainConfig();
	void LoadItemInfo();
	void LoadTimeConfig();
	void DataSendMoss(int Index);

	void SpawnMoss();
	void DisappearMoss();

	BOOL BuyItem(int aIndex, unsigned char * aRecv);

	void FillingCItemStruct();

	int RandValue(int IndexOption);
	int GetItem(int group);
	void ItemByteConvert(unsigned char* buf, CItem item);

	void GetNameItem(char* input,char *output);

	void CheckTime();
	BOOL GetStatusMoss();
	bool g_MossDelay;
	BOOL OpenedMoss;

	struct 
	{
		int EnableMoss;
		int EnableTimer;
		int UsePK;
		int PriceZen;
		int PricePCPoint;
		int PriceWCoin;
		int RandExc;
		int MaxExcOpt;
		int RandLevel;
		int MaxLevel;
		int RandOptAdd;
		int MaxOptAdd;
		int RandLuck;
		int RandSkill;
		int RandAncient;
	}MossConfig;
private:
	struct
	{
		int Index;
		char Name[50];
	}ItemInfo[6][100];
	short OrderItems[6];
	struct 
	{
		int hour;
		int minute;
		int delay;
		int closehour;
		int closemin;
	}MossTimer[128];

	int AmountTimers;
	int BuyType;  
}; 
extern Moss moss; 
#endif
#endif