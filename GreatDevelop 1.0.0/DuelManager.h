// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.0								# //
// ================================================== //

#ifdef _GS
#ifndef DUELSYSTEM_H
#define DUELSYSTEM_H
#include "Prodef.h"
#include "User.h"
// ----------------------------------------------------------------------------------------------------------------
#define MAX_DUEL_WIN_POINTS	10
#define MAX_DUEL_ROOMS	    4
#define MAX_DUEL_SEPARATORS	10
#define MAX_DUEL_TIME		30
// ----------------------------------------------------------------------------------------------------------------
// ## Structures;
#pragma pack(1)
// CLIENT -> SERVER
struct PMSG_DUEL_ANSWER_START
{
	PBMSG_HEAD2 h;
	bool bDuelOK;
	BYTE NumberH;
	BYTE NumberL;
	char szName[10];
};

// ----------------------------------------------------------------------------------------------------------------
// CLIENT -> SERVER
struct PMSG_DUEL_START
{
	PBMSG_HEAD2 h;	// C1:AA
	BYTE bDuelStart;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	char szName[10];	// 6
};
// ----------------------------------------------------------------------------------------------------------------
// CLIENT -> SERVER
struct PMSG_DUEL_REQUEST_END
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char szName[10];	// 6
};
// ----------------------------------------------------------------------------------------------------------------
// CLIENT -> SERVER
struct PMSG_DUEL_REQUEST_WATCH // 0x07
{
	PBMSG_HEAD2 h;
	BYTE btRoomIndex;
	BYTE btRandomValue;
};

// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_QUESTION_START // 0x01
{
	PBMSG_HEAD2 h;
	BYTE NumberH;
	BYTE NumberL;
	BYTE szName[10];
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_REQUEST_START // 0x02
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char szName[10];	// 5
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_END // 0x03
{
	PBMSG_HEAD2 h;
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_SCORE // 0x04
{
	PBMSG_HEAD2 h;	
	BYTE NumberH1;	
	BYTE NumberL1;	
	BYTE NumberH2;	
	BYTE NumberL2;	
	BYTE btDuelScore1;	
	BYTE btDuelScore2;	
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_LIFEBAR_REFILL // 0x05
{
	PBMSG_HEAD2 h;
	BYTE btObjId01H;
	BYTE btObjId01L;
	BYTE btObjId02H;
	BYTE btObjId02L;
	BYTE btLife01;
	BYTE btLife02;
	BYTE btShield01;
	BYTE btShield02;
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_ROOMSTATUS // 0x06
{
	BYTE szName1[10];
	BYTE szName2[10];
	BYTE btDuelRunning;
	BYTE btDuelOpen;
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_STATUS // 0x06
{
	PBMSG_HEAD2 h;
	PMSG_DUEL_ROOMSTATUS pRoomStatus[MAX_DUEL_ROOMS];
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_LIFEBAR_NAME // 0x07 
{
	PBMSG_HEAD2 h;
	WORD Type; // 4
	BYTE szName1[10]; // 5
	BYTE szName2[10]; // f
	BYTE btObjId1H;
	BYTE btObjId1L;
	BYTE btObjId2H;
	BYTE btObjId2L;
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_SPEC_ADD // 0x08
{
	PBMSG_HEAD2 h;
	BYTE szName[10];
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_SPEC_DELEX // 0x09
{
	PBMSG_HEAD2 h;
	BYTE szName[10];
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_SPEC_DEL // 0x0A
{
	PBMSG_HEAD2 h;
	BYTE szName[10];
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_SPEC_LIST // 0x0B
{
	PBMSG_HEAD2 h;
	BYTE btCount;
	BYTE szName[MAX_DUEL_SEPARATORS][10];
};
// ----------------------------------------------------------------------------------------------------------------
/* Moved to ProdejNew
// SERVER -> CLIENT
struct PMSG_SERVERCMD
{
	PBMSG_HEAD2 h;
	BYTE subcode;	// 3
	BYTE CmdType;	// 4
	BYTE X;	// 5
	BYTE Y;	// 6
};
*/
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_FINISH // 0x0C
{
	PBMSG_HEAD2 h;
	BYTE szWinner[10];
	BYTE szLooser[10];
};
// ----------------------------------------------------------------------------------------------------------------
// SERVER -> CLIENT
struct PMSG_DUEL_LIFEBAR_INIT // 0x0D
{
	PBMSG_HEAD2 h;
	BYTE Unknow00;
};
// ----------------------------------------------------------------------------------------------------------------
#pragma pack()
// ----------------------------------------------------------------------------------------------------------------
// ## Structure;
struct DUEL_ROOM
{

	BOOL	RoomFree;
	BOOL	DuelWaiting;
	// ----
	LPOBJ	szlpObjOne;
	BYTE	szPointsOne;
	// ----
	LPOBJ	szlpObjTy;
	BYTE	szPointsTy;
	// ----
	LPOBJ	szSeparators[MAX_DUEL_SEPARATORS];
	// ----
	DWORD	dwTicketCount;
	DWORD	dwStartTime;
	// ----
	BOOL	szWinner;

};
// ----------------------------------------------------------------------------------------------------------------
//##Structure;
static const struct DUEL_RESPAWN_RECTS
{
	int LowX;
	int LowY;
	int HighX;
	int HighY;
}
// ----------------------------------------------------------------------------------------------------------------
g_DuelRespawns [MAX_DUEL_ROOMS] = 
{
	{89, 62, 110, 81},
	{89, 113, 110, 130},
	{141, 63, 163, 82},
	{142, 111, 163, 131	}
};
// ----------------------------------------------------------------------------------------------------------------
//## Class;
class DuelSystem
{
	// ----
private:
	DWORD UpdateTickCount;
	DWORD UpdateLifebarTime;
	// ----
public:
	DUEL_ROOM	g_DuelRooms[MAX_DUEL_ROOMS];
	// ----
	DuelSystem(void);
	~DuelSystem(void);
	// ----
	void Run();
	void DuelProtocolCore(LPOBJ lpObj, unsigned char * lpPacket);
	void KillUserProc ( LPOBJ lpObj, LPOBJ lpTarget);
	int GetUserDuelRoom(LPOBJ lpObj);
	int GetFreeRoomIndex();
	DWORD _DuelThread(void *param);
	// ----
	static void RunThread(LPVOID param)
	{
		while(true)
		{
			DuelSystem* This = (DuelSystem*)param;
			// ----
			This->Run();
			// ----
			Sleep(1000);
		}
	}
	// ----
	void DuelCreateThread()
	{
		DWORD ThreadID;
		// ----
		HANDLE dThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RunThread, (LPVOID)this, 0, &ThreadID);
		// ----
		if(!dThread)
		{
			MessageBoxA(0, "Cannot start Duel System", "Error", MB_OK | MB_ICONERROR);
			exit(0);
		}

	}
	// ----
	bool IsDuelEnable(int aIndex);
	bool DuelCheck(LPOBJ lpObj);
	bool DuelCheck(LPOBJ lpObj, LPOBJ lpObj2);
	void UserDuelInfoReset(LPOBJ lpObj);
	void RoomReset(short iRoom, bool dontMove = false, bool dontSendEnd = false);
	void RemoveUser(LPOBJ lpObj);
	void SetDuelOption(int lpObj, BOOL bState);
	bool IsOnDuel(int lpObj);
	bool IsOnDuel2(int lpObj, int lpObj2);
	void PlayerScore(LPOBJ lpObj);
	int GetSpectatorCount(short iRoom);
	void SendDuelStatus(LPOBJ lpObj);
	void UpdateDuelScore(short iRoom);
	void WinnerBuff(LPOBJ lpObj);
	void DeletePotion(LPOBJ lpObj);
	bool IsSpectacor(short index);
	// ----
	void RecvDuelRequest(LPOBJ lpObj, PMSG_DUEL_REQUEST_START* lpMsg);
	void RecvDuelAnswer(LPOBJ lpObj, PMSG_DUEL_ANSWER_START* lpMsg);
	void RecvWatchRequest(LPOBJ lpObj, PMSG_DUEL_REQUEST_WATCH* lpMsg);
	void RespawnDuelers(LPOBJ lpObj, LPOBJ lpTargetObj);
	void SendRefuseDuel(LPOBJ lpObj);
	// ----

	static void TimerThreadEP(void * pThis) 
	{ 
		DuelSystem * pt = (DuelSystem*)pThis; 
	}
	// ----
	void SendEndDuel(LPOBJ lpObj);
	void SendEndDuelNotification(LPOBJ lpObj, char* Winner, char* Looser);
	void SendLifebarStatus(short iRoom);
	void SendLifebarStatus(LPOBJ lpObj, int iRoom);
	void SendLifebarInit(LPOBJ lpObj, int iRoom);
	void SendSpectatorList(short iRoom);
	void SendSpectatorList(LPOBJ lpObj, int iRoom);
	void SendSpectatorAdd(short iSpecIndex, int iRoom);
	void SendSpectatorRemove(short iSpecIndex, int iRoom);

	void DuelSetInfo(int aIndex);
	void SaveDuel(char FirstAcc[11], char FirstName[11], char SecondAcc[11], char SecondName[11], int Point1, int Point2);
	bool SetDuelState(int aIndex, char AccountID[11], char Name[11]);
};
// ----------------------------------------------------------------------------------------------------------------
extern DuelSystem g_DuelSystem;

	bool HookSetDuelOption(int lpObj, BOOL bState);
	bool HookIsDuelEnable(int aIndex);
	bool HookIsOnDuel(int lpObj, int lpObj2);
	bool HookDuelCheck1(LPOBJ lpObj);
	bool HookDuelCheck2(LPOBJ lpObj, LPOBJ lpTargetObj);
	void GSgObjUserDie(OBJECTSTRUCT *lpObj, OBJECTSTRUCT *lpTargetObj);
// ----------------------------------------------------------------------------------------------------------------
#endif
// ----------------------------------------------------------------------------------------------------------------
#endif



