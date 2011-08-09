// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Storm & Tornado Projects 2010-2011		# //
// ================================================== //
#ifndef DROPSYSTEM_H
#define DROPSYSTEM_H
#include "User.h" // need LPOBJ 
struct s_DropSystemMob
{
	int mobId;
	int rateCount;
	int dropCountMin;
	int dropCountMax;
};

struct s_DropSystemItem
{
	int mobLvlMin;
	int mobLvlMax;
	int dropRate;
	int iGroup;
	int iId;
	int minLvl;
	int maxLvl;
	int dur;
	int skill;
	int luck;
	int minOpt;
	int maxOpt;
	int exc;
	int minExc;
	int maxExc;
	int anc;
	int ancType;
};

enum e_confType {
	MISC,
	MOBITEMCOUNT,
	DROPLIST
};

class cDropSystem
{
private:
	std::map<int, std::vector<s_DropSystemMob> > dropCountMob; // dropCountMob[mobId] = vector s_DropSystemMob

	std::vector<s_DropSystemItem> dropList; // dropList = items vector
	std::map<int, std::vector<s_DropSystemItem> > dropListMap; // dropListMap[mapId] = items vertor (s_DropSystemItem)
	std::map<int, std::vector<s_DropSystemItem> > dropListMob; // dropListMob[mobId] = items vector (s_DropSystemItem)
	std::map<int, std::vector<s_DropSystemItem> > dropListVar; // dropListVar[v] = items vector; int v = mapId * 1024 + mobId;

public:
	cDropSystem();
	~cDropSystem();

	void LoadConfig();
	bool DropItem(LPOBJ mObj, LPOBJ pObj);
	bool SearchAndDrop(int mIndex, int mobId, int mobLvl, int mobMap, int mobX, int mobY, int aIndex);
	void CreateAndDrop(int aIndex, BYTE MapNumber, BYTE x, BYTE y, int LootIndex, s_DropSystemItem&i);
};

extern cDropSystem DropSystem;
#endif