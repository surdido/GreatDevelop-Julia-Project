// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Storm & Tornado Projects 2010-2011		# //
// ================================================== //

#ifndef GOLDENARCHER_H
#define  GOLDENARCHER_H			   

class cGoldenArcher
{
public:				 

	cGoldenArcher();
	~cGoldenArcher();

	void Golden_Archer(int aIndex);
	bool IsRena(int aIndex);
	void DelRena(int aIndex);
	DWORD GAGetRewardItem();
	void GAGiveReward(int aIndex, DWORD Item);
	void GetPoints(int aIndex);
private:
	FILE * GA;
	unsigned short *ActualRena;
	int RemainedRena;

};

extern cGoldenArcher GoldenArcher;

#endif