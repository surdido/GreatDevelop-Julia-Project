// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.1								# //
// ================================================== //

#include "StdAfx.h"
#include "WzAG.h"
#include "Configs.h"


FILE * fstream1, * fstream2;
char * Lsrvname, * Lsrvver,* Lpartition,* Laddrarg7,* FileBuffer, * szLanguage;
unsigned long FileLen ;
unsigned char szServerKey[19]={0x29,0x23 ,0xBE,0x00 ,0xE1,0x6C, 0xD6,0xAE,0x52,0x90,
	0x49,0xF1 ,0xF1,0xBB ,0xE9,0xEB ,0xB3,0xA6,0xDB};

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

WZAG_API int AGConnectSetFS() 
{
	_asm{
		xor eax,eax
	}
	return 0;
}

WZAG_API int AGGetClientVersion(int unknown,char * VerBuff,char * SerialBuff) 
{
	char ver[0x14];
	char serial[0x14];
	char commonlocPath[]=GreatDevelopCommon;


	GetPrivateProfileString(
		"GameServerInfo",
		"ClientExeVersion",
		"",
		&ver[0],
		0x14,
		commonlocPath
		);

	GetPrivateProfileString(
		"GameServerInfo",
		"ClientExeSerial",
		"",
		&serial[0],
		0x14,
		commonlocPath
		);
	memcpy(VerBuff,ver,0x14);
	memcpy(SerialBuff,serial,0x14);
	return 0;
}

WZAG_API char * AGGetDataBuffer()  
{
	return FileBuffer;
}

WZAG_API int AGGetDataBufferSize() 
{
	return FileLen;
}

WZAG_API void AGGetKey(HANDLE handle,char* key,int startindex,int len)
{
	memcpy(key,szServerKey,sizeof(szServerKey));
}

WZAG_API int AGReleaseHandle() 
{
	_asm{
		xor eax,eax
	}
	return 0;
}

WZAG_API int AGRequestData(int NoneUse,int GetType)  
{	
	CHAR Item[256];
	CHAR Skill[256];
	CHAR Quest[256];
	CHAR CheckSum[256];
	CHAR Monster[256];
	CHAR Gate[256];
	CHAR MonsterSetBase[256];
	CHAR Shop0[256];
	CHAR Shop1[256];
	CHAR Shop2[256];
	CHAR Shop3[256];
	CHAR Shop4[256];
	CHAR Shop5[256];
	CHAR Shop6[256];
	CHAR Shop7[256];
	CHAR Shop8[256];
	CHAR Shop9[256];
	CHAR Shop10[256];
	CHAR Shop11[256];
	CHAR Shop12[256];
	CHAR Shop13[256];
	CHAR Shop14[256];
	CHAR Shop15[256];
	CHAR Shop16[256];
	CHAR Shop17[256];
	CHAR MoveReq[256];
	CHAR ItemSetOption[256];
	CHAR ItemSetType[256];	

	char GameServerIni[] = GreatDevelopGS;
	GetPrivateProfileString("Data","Item","..\\data\\lang\\Jpn\\item(Jpn).txt",Item,256,GameServerIni);
	GetPrivateProfileString("Data","Skill","..\\data\\lang\\Jpn\\skill(Jpn).txt",Skill,256,GameServerIni);
	GetPrivateProfileString("Data","Quest","..\\data\\lang\\Jpn\\quest(Jpn).txt",Quest,256,GameServerIni);
	GetPrivateProfileString("Data","MoveReq","..\\data\\lang\\Jpn\\movereq(Jpn).txt",MoveReq,256,GameServerIni);
	GetPrivateProfileString("Data","ItemSetOption","..\\data\\lang\\Jpn\\itemsetoption(Jpn).txt",ItemSetOption,256,GameServerIni);
	GetPrivateProfileString("Data","ItemSetType","..\\data\\lang\\Jpn\\itemsettype(Jpn).txt",ItemSetType,256,GameServerIni);
	GetPrivateProfileString("Data","CheckSum","..\\data\\lang\\Jpn\\CheckSum.dat",CheckSum,256,GameServerIni);
	GetPrivateProfileString("Data","Monster","..\\data\\Monster.txt",Monster,256,GameServerIni);
	GetPrivateProfileString("Data","Gate","..\\data\\Gate.txt",Gate,256,GameServerIni);
#ifdef _GS
	GetPrivateProfileString("Data","MonsterSetBase","..\\data\\MonsterSetBase.txt",MonsterSetBase,256,GameServerIni);
#endif
#ifdef _GS_CS
	GetPrivateProfileString("Data","MonsterSetBase","..\\data\\MonsterSetBaseCS.txt",MonsterSetBase,256,GameServerIni);
#endif
	GetPrivateProfileString("Data","Shop0","..\\data\\Shops\\Shop0.txt",Shop0,256,GameServerIni);
	GetPrivateProfileString("Data","Shop1","..\\data\\Shops\\Shop1.txt",Shop1,256,GameServerIni);
	GetPrivateProfileString("Data","Shop2","..\\data\\Shops\\Shop2.txt",Shop2,256,GameServerIni);
	GetPrivateProfileString("Data","Shop3","..\\data\\Shops\\Shop3.txt",Shop3,256,GameServerIni);
	GetPrivateProfileString("Data","Shop4","..\\data\\Shops\\Shop4.txt",Shop4,256,GameServerIni);
	GetPrivateProfileString("Data","Shop5","..\\data\\Shops\\Shop5.txt",Shop5,256,GameServerIni);
	GetPrivateProfileString("Data","Shop6","..\\data\\Shops\\Shop6.txt",Shop6,256,GameServerIni);
	GetPrivateProfileString("Data","Shop7","..\\data\\Shops\\Shop7.txt",Shop7,256,GameServerIni);
	GetPrivateProfileString("Data","Shop8","..\\data\\Shops\\Shop8.txt",Shop8,256,GameServerIni);
	GetPrivateProfileString("Data","Shop9","..\\data\\Shops\\Shop9.txt",Shop9,256,GameServerIni);
	GetPrivateProfileString("Data","Shop10","..\\data\\Shops\\Shop10.txt",Shop10,256,GameServerIni);
	GetPrivateProfileString("Data","Shop11","..\\data\\Shops\\Shop11.txt",Shop11,256,GameServerIni);
	GetPrivateProfileString("Data","Shop12","..\\data\\Shops\\Shop12.txt",Shop12,256,GameServerIni);
	GetPrivateProfileString("Data","Shop13","..\\data\\Shops\\Shop13.txt",Shop13,256,GameServerIni);
	GetPrivateProfileString("Data","Shop14","..\\data\\Shops\\Shop14.txt",Shop14,256,GameServerIni);
	GetPrivateProfileString("Data","Shop15","..\\data\\Shops\\Shop15.txt",Shop15,256,GameServerIni);
	GetPrivateProfileString("Data","Shop16","..\\data\\Shops\\Shop16.txt",Shop16,256,GameServerIni);
	GetPrivateProfileString("Data","Shop17","..\\data\\Shops\\Shop17.txt",Shop17,256,GameServerIni);

	char * filename ={0};

	switch (GetType)
	{
		//Item
	case 0x00:
		filename="..\\data\\lang\\Kor\\item(Kor).txt";
		break;
	case 0x01:
		filename=Item;
		break;
		//Skill
	case 0x02:
		filename="..\\data\\lang\\Kor\\skill(Kor).txt";
		break;
	case 0x03:
		filename=Skill;
		break;
		//Quest
	case 0x04:
		filename="..\\data\\lang\\Kor\\quest(Kor).txt";
		break;
	case 0x05:
		filename=Quest;
		break;
		//Checksum
	case 0x06:
		filename=CheckSum;
		break;
		//Monster
	case 0x07:
		filename=Monster;
		break;
		//Gates
	case 0x08:	
		filename=Gate;
		break;
		//Position of Monsters
	case 0x09:
		filename=MonsterSetBase;
		break;
		//Reserved for GameGuard
	case 0x0A:
		break;
		//Shops
	case 0x0B:
		filename=Shop0;
		break;
	case 0x0C:
		filename=Shop1;
		break;
	case 0x0D:
		filename=Shop2;
		break;
	case 0x0E:
		filename=Shop3;
		break;
	case 0x0F:
		filename=Shop4;
		break;
	case 0x10:
		filename=Shop5;
		break;
	case 0x11:
		filename=Shop6;
		break;
	case 0x12:
		filename=Shop7;
		break;
	case 0x13:
		filename=Shop8;
		break;
	case 0x14:
		filename=Shop9;
		break;
	case 0x15:
		filename=Shop10;
		break;		
	case 0x16:
		filename=Shop11;
		break;
	case 0x17:
		filename=Shop12;
		break;
	case 0x18:
		filename="..\\data\\lang\\Kor\\movereq(kor).txt";
		break;
	case 0x19:
		filename=MoveReq;
		break;
	case 0x1A: 
		filename="..\\data\\lang\\Kor\\itemsetoption(Kor).txt";
		break;
	case 0x1B:
		filename=ItemSetOption;
		break;
	case 0x1C:
		filename="..\\data\\lang\\Kor\\itemsettype(Kor).txt";
		break;
	case 0x1D:
		filename=ItemSetType;
		break;
	case 0x1E:
		filename=Shop13;
		break;
	case 0x1F:
		filename=Shop14;
		break;
	case 0x20:
		filename=Shop15;
		break;
	case 0x21:
		filename=Shop16;
		break;
	case 0x22:
		filename=Shop17;
		break;
	default:
		filename="Error!" ;
		::ExitProcess(0);
		break;

	}
	if  ( fstream1=fopen(filename,"rb") )
	{
		fseek(fstream1,0,SEEK_END);
		if (FileLen=ftell(fstream1) )
		{
			fseek(fstream1,0,SEEK_SET ) ;
			FileBuffer =new char[FileLen+1];
			fread(FileBuffer,FileLen,1,fstream1);
		}
		else
		{
			MessageBox( NULL, filename,"Error.", MB_OK );
			::ExitProcess(0);
		}
		fclose(fstream1);
	}

	else
	{
		MessageBox( NULL, filename,"Error.", MB_OK );
		::ExitProcess(0);
	} 
	return 0;
}

WZAG_API int AGSetInfo(int Language, char * Partition, int un0, char * SrvVer, char* SrvName, int SrvType, char * Addr7)
{
	switch(Language)
	{
	case 0:
		{
			szLanguage = "Kor";
			break;
		}
	case 2:
		{
			szLanguage = "Jpn";
			break;
		}
	default:
		{
			MessageBoxA(0, "Language Selected is not Supported\nChange Language in CommonServer.cfg", "Error", MB_OK | MB_ICONERROR);
			::ExitProcess(0);
			break;
		}
	}

	Lsrvname=SrvName;
	Lsrvver=SrvVer;
	Lpartition=Partition;
	Laddrarg7=Addr7;
	return 0;			
}

WZAG_API int AGSetSubInfo() 
{
	_asm{
		xor eax,eax
	}
	return 0;
}
