// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Tornado Lite - 7.12.XX					# //
// ================================================== // 

#include "StdAfx.h" 
#include "Configs.h"
#include "User.h" 
#include "IPBlock.h"
#include "Logger.h"
					  
cIpBlock IpBlock;

cIpBlock::cIpBlock()
{		  
}
cIpBlock::~cIpBlock()
{		  
}

void cIpBlock::LoadIpBlock()
{
	FILE *fp;
	BOOL bRead = FALSE;
	DWORD dwArgv = 0;
	char sLineTxt[255] = {0};
	IPBlockCount = 1;

	fp = fopen(RMSTIPBlock,"r");

	rewind(fp);
	
	while(fgets(sLineTxt, 255, fp) != NULL)
	{
		if(sLineTxt[0] == '/')continue;			
		if(sLineTxt[0] == ';')continue;
		if(sLineTxt[0] == 'e' && sLineTxt[1] == 'n' && sLineTxt[2] == 'd')continue;
		char IP[16];							
		if(strlen(sLineTxt) <= 1)continue;
								  
		sscanf(sLineTxt, "%s", IP);
		sprintf(IPBlockInfo[IPBlockCount].IP,"%s",IP);
		IPBlockCount++;
	}

	rewind(fp);
	fclose(fp);
}

bool cIpBlock::CheckIp(DWORD aIndex)
{
	OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	for(int x=1;x < IPBlockCount;x++)
	{
		if(!CheckIp2(IPBlockInfo[x].IP, gObj->Ip_addr))
		{					
			Log.ConsoleOutPut(1, c_Red, t_IPBLOCK,"[Anti-Hack] Blocked %s try to connect!!!",gObj->Ip_addr);
			CloseClient(aIndex);
			return false;
		}
	}
	return true;
} 
						  
void changestar(char*IP,int i)
{
	for(int j=strlen(IP); j>=i; j--)
		IP[j+1] = IP[j];
	IP[i] = '-';
	IP[i+1] = '1';
}

bool cIpBlock::CheckIp2(char ConfigIP[16], char GobjIP[16])
{							   
	for(int i=0; i<16;i++)
	{							  
		if(ConfigIP[i] == '.')
			ConfigIP[i] = ' ';
		if(GobjIP[i] == '.')
			GobjIP[i] = ' ';
									 
		if(ConfigIP[i] == '*')
			changestar(ConfigIP, i); 
	}

	int CIP[4];
	int GIP[4];
																	  
	sscanf(ConfigIP,"%d %d %d %d",&CIP[0],&CIP[1],&CIP[2],&CIP[3]);
	sscanf(GobjIP,"%d %d %d %d",&GIP[0],&GIP[1],&GIP[2],&GIP[3]);

	if((CIP[0] == GIP[0] || CIP[0] == -1) && 
		(CIP[1] == GIP[1] || CIP[1] == -1) &&
		(CIP[2] == GIP[2] || CIP[2] == -1) &&
		(CIP[3] == GIP[3] || CIP[3] == -1))
		return false;	
	return true;
}