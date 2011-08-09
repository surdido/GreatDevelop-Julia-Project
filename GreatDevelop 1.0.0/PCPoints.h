// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Storm & Tornado Projects 2010-2011		# //
// ================================================== //
#ifndef POINTSHOP_H
#define POINTSHOP_H
// ---------------------------------------------------------------------------------------------------------
#include <windows.h>
// ---------------------------------------------------------------------------------------------------------

typedef struct PointShopStruct
{	
	int ItemIndex;
	int ItemID;	
	int X;
	int Y;
	int Skill;
	int Level;
	int Luck;
	int Opt;
	int Dur;
	int Exc;
	// ----
	int NewOpt1;
	int NewOpt2;
	int NewOpt3;
	int NewOpt4;
	int NewOpt5;
	// ----
	int SlotX;
	int Cost;
}PointShopStr;
// ---------------------------------------------------------------------------------------------------------

typedef struct PointShopMobStruct
{	
	int MobID;
	int Points;	
}PointShopMobStr;
// ---------------------------------------------------------------------------------------------------------

class ÒPointShop
{
public:
	UINT LoadConfigFile();
	int gObjCalcItems(int X, int Y);
	int MakePacket();
	void Init();
	void OpenShop(DWORD PlayerID);
	void BuyItem(DWORD PlayerID, int Position);
	void SendPoints(DWORD PlayerID, int Points);
	void GetInfo(DWORD PlayerID);
	void SetStatus(DWORD PlayerID);
	void IncreasePoints(DWORD PlayerID, int Points);
	void DecreasePoints(DWORD PlayerID, int Points);	
	void LevelUp(DWORD PlayerID, int MobID);

	void LevelUpWC(DWORD PlayerID, int MobID);
	// ----
	BOOL IsPCPointSystem;
	BYTE PCPointPacket[4680];
	BYTE PC_Shop[0x78];
	PointShopStruct Items[120];
	PointShopMobStruct pPCMobPoint[512];
	PointShopMobStruct pWCMobPoint[512];
	// ----
private:
	int HowManyItems;		 
	int MobPointRecords;
	int MobWCRecords;
	int PacketSizes;
	int SearchIndex(int Position);
	int GetRewardPoints(int MobID);
	int GetRewardCWPoints(int MobID);
};
// ---------------------------------------------------------------------------------------------------------
extern ÒPointShop PointShop;
// ---------------------------------------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------------------------------------