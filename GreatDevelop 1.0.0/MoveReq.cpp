// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Tornado Lite - 7.12.XX					# //
// ================================================== // 

#include "StdAfx.h"
#include "MoveReq.h"
#include "User.h" 
cMoveReq MoveReq;

cMoveReq::cMoveReq()
{

}

cMoveReq::~cMoveReq()
{

}
#pragma warning(disable: 4018)
void cMoveReq::MoveReqLoad()
{
	FILE *fp;
	BOOL bRead = FALSE;
	DWORD dwArgv = 0;
	char sLineTxt[255] = {0};
	int MoveReqCount = 1;

	fp = fopen("..\\RMST\\MoveReq.txt","r");

	if(!fp)
	{
		MessageBoxA(NULL, "Cant Find MoveReq.txt!", "Error!", MB_OK);
		::ExitProcess(0);
	}
	
	rewind(fp);
	int leestatus=-1;
	
	while(fgets(sLineTxt, 255, fp) != NULL)
	{
		if(sLineTxt[0] == '/')continue;
		if(sLineTxt[0] == ';')continue;

		int n[4];
		char Name[50], Name2[50];

		sscanf(sLineTxt, "%d %s %s %d %d %d", &n[0], &Name, &Name2, &n[1], &n[2], &n[3]);

		for(int j=0; j <= strlen(Name); j++)
		{
			if(Name[j] == '"')
			{
				for(int k=j; k<=strlen(Name); k++)
				{
					Name[k] = Name[k+1];
				}
			}
		}

		for(int j=0; j <= strlen(Name2); j++)
		{
			if(Name2[j] == '"')
			{
				for(int k=j; k<=strlen(Name2); k++)
				{
					Name2[k] = Name2[k+1];
				}
			}
		}

		MoveReqInfo[MoveReqCount].Index	= n[0];				 
		strcpy(MoveReqInfo[MoveReqCount].MapName1, Name);
		strcpy(MoveReqInfo[MoveReqCount].MapName2, Name2);
		MoveReqInfo[MoveReqCount].Zen	= n[1];
		MoveReqInfo[MoveReqCount].Level	= n[2];
		MoveReqInfo[MoveReqCount].Gate	= n[3];
		MoveReqCount++;
	}

	Count = MoveReqCount;
	rewind(fp);
	fclose(fp);
	
	return;
}
char* cMoveReq::GetMapName(int MapId)
{
	switch (MapId)
	{
	case 0:
		return "Lorencia";
	case 1:
		return "Dungeon";
	case 2:
		return "Devais";
	case 3:
		return "Noria";
	case 4:
		return "Lost Tower";
	case 5:
		return "Null";
	case 6:
		return "Arena";
	case 7:
		return "Atlans";
	case 8:
		return "Tarkan";
	case 9:
		return "Devil Square";
	case 10:
		return "Icarus";
	case 30:
		return "Valley of Loren";
	case 31:
		return "Land of Trial";
	case 32:
		return "Devil Square";
	case 33:
		return "Aida";
	case 34:
		return "Crywolf";
	case 35:
		return "Null";
	case 36:
		return "Kalima";
	case 37:
		return "Kantru1";
	case 38:
		return "Kantru2";
	case 39:
		return "Kantru3";
	case 40:
		return "Silent";
	case 41:
		return "Barracks";
	case 42:
		return "Refuge";
	case 43:
		return "Null";
	case 44:
		return "Null";
	case 51:
		return "Elbeland";
	case 52:
		return "Blood Castle";
	case 53:
		return "Chaos Castle";
	case 56:
		return "Swamp of Calmness";
	case 57:
		return "Raklion";
	case 58:
		return "Raklion Boss";
	case 62:
		return "Santa Town";
	case 63:
		return "Vulcanus";
	case 64:
		return "Coliseum";
	}
	if (MapId >= 11 && MapId <= 17)
		return "Blood Castle";

	if (MapId >= 18 && MapId <= 23)
		return "Chaos Castle";

	if (MapId >= 24 && MapId <= 29)
		return "Kalima";

	if (MapId >= 45 && MapId <= 50)
		return "Illusion Temple";

	return "Unknown";
}
