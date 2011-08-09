// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Tornado Lite - 7.12.XX					# //
// ================================================== // 

#ifndef MoveReq_H
#define MoveReq_H

class cMoveReq
{
public:
	cMoveReq();
	~cMoveReq(); 

	void MoveReqLoad();
	char* GetMapName(int MapId);

	struct sMoveReq
	{
		int Index, Zen, Level, Gate;
		char MapName1[50], MapName2[50];
	}MoveReqInfo[255];
	int Count;
};
extern cMoveReq MoveReq;
#endif