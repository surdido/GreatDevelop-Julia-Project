// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Storm & Tornado Projects 2010-2011		# //
// ================================================== //
#include "stdafx.h"
#include "PCPoints.h"
#include "SQL.h"
#include "Logger.h"
#include "User.h"
#include "ChatCommands.h" 
#include "Configs.h"

ÒPointShop PointShop; 

void ÒPointShop::SetStatus(DWORD PlayerID) 
{
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);
    if((AddTab[PlayerID].PC_InfoMod == 1) && (AddTab[PlayerID].PC_InfoReceived == 1))
    {
        MySQL.Execute("UPDATE Character SET %s = '%d' WHERE Name = '%s'", Config.PCPointsColumn, AddTab[PlayerID].PC_PlayerPoints, gObj->Name);
		Log.ConsoleOutPut(1, c_Cyan, t_PCPOINT, "[PointShop]Account[%s] Name [%s] Credits [%d]", 
                                gObj->AccountID, gObj->Name, AddTab[PlayerID].PC_PlayerPoints);
        AddTab[PlayerID].PC_InfoMod = 0;
    }
    else
    {
        if(AddTab[PlayerID].PC_InfoReceived == 0)
        {
            GetInfo(PlayerID);
			Chat.MessageLog(1, c_Red, t_PCPOINT, gObj, "[PointShop] System Error Requesting Points Record");
        } 
        else 
        {
            Log.ConsoleOutPut(1,c_Cyan, t_PCPOINT, "[PointShop] Updated Credits Account[%s] Name [%s] Points [%d]",
                                    gObj->AccountID, gObj->Name, AddTab[PlayerID].PC_PlayerPoints);
        }
    }
}
 
UINT ÒPointShop::LoadConfigFile()
{
    DWORD dwAgr    = 0;
    char Buff[255] = {0};
    BOOL bResult   = FALSE;
    int Buffer     = -1;

    FILE *FilePath;

    HowManyItems      = 0;
    MobPointRecords   = 0;
	MobWCRecords		= 0;

    srand((unsigned)time(NULL));

    if((FilePath = fopen(RMSTPcPoints, "r")) == NULL)
    {
        MessageBox(NULL, "Cant Find PCPoints_WCoins.dat", "Error", 0);
        IsPCPointSystem = FALSE;							   
        return 0;
    } 

    IsPCPointSystem = TRUE;

    rewind(FilePath);

    while(fgets(Buff, 255, FilePath) != NULL)
    {
        if(Buff[0] == '/')
            continue;

        if(bResult == FALSE && (UINT)(Buff[0] - 0x30) == dwAgr)
            bResult = TRUE;      

        if(bResult == TRUE && strlen(Buff) < 3)
        {
            UINT q = 0;
            sscanf(Buff, "%d", &q);
            Buffer = q;
        }
        if(Buffer == 0)
        {
            if(bResult == TRUE && strlen(Buff) > 3)
            {
                if((Buff[0] == 'e') && (Buff[1] == 'n') && (Buff[2] == 'd'))
                    Buffer = -1;
                else 
                {
                    sscanf(Buff, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                    &Items[HowManyItems].ItemIndex,
                    &Items[HowManyItems].ItemID,
                    &Items[HowManyItems].X,
                    &Items[HowManyItems].Y,
                    &Items[HowManyItems].Level,
                    &Items[HowManyItems].Opt,
                    &Items[HowManyItems].Luck, 
                    &Items[HowManyItems].Skill,
                    &Items[HowManyItems].Dur,
                    &Items[HowManyItems].Exc,
                    &Items[HowManyItems].NewOpt1,
                    &Items[HowManyItems].NewOpt2,
                    &Items[HowManyItems].NewOpt3,
                    &Items[HowManyItems].NewOpt4,
                    &Items[HowManyItems].NewOpt5,
                    &Items[HowManyItems].Cost);

                    Items[HowManyItems].SlotX = gObjCalcItems(Items[HowManyItems].X, Items[HowManyItems].Y);
                    HowManyItems++;
                }
            }
        }		  
        if(Buffer == 1)
        {
            if(bResult == TRUE && strlen(Buff) > 3)
            {
                if((Buff[0] == 'e') && (Buff[1] == 'n') && (Buff[2] == 'd'))
                    Buffer = -1;
                else 
                {
                    sscanf(Buff, "%d %d",
                    &pPCMobPoint[MobPointRecords].MobID, 
                    &pPCMobPoint[MobPointRecords].Points);

                    MobPointRecords++;
                }
            }
        }
        if(Buffer == 2)
        {
            if(bResult == TRUE && strlen(Buff) > 3)
            {
                if((Buff[0] == 'e') && (Buff[1] == 'n') && (Buff[2] == 'd'))
                {
                    Buffer = -1;
                } 
                else 
                {
                    sscanf(Buff, "%d %d",
                    &pWCMobPoint[MobWCRecords].MobID, 
                    &pWCMobPoint[MobWCRecords].Points);

                    MobWCRecords++;
                }
            }
        }
    }
    rewind(FilePath);
    fclose(FilePath);			
	Log.ConsoleOutPut(1, c_Cyan, t_PCPOINT, "[PointShop] Total Items Loaded [%d]", HowManyItems);
	Log.ConsoleOutPut(1, c_Cyan, t_PCPOINT, "[PointShop] Total Monster Loaded [%d]", MobPointRecords);
	Log.ConsoleOutPut(1, c_Cyan, t_PCPOINT, "[WCoins] Total Monster WC Loaded [%d]", MobWCRecords);
	return 1;
}
 
int ÒPointShop::SearchIndex(int Position)
{
    for(int i = 0; i < HowManyItems; i++)
    {
        if(Position == Items[i].SlotX)
        {
            return i;
        }
    }
    return -1;
}
 
int ÒPointShop::gObjCalcItems(int X, int Y)
{
    int PosX = 0;
    int PosY = 0;
    int j    = -1;
    Y        -= 1;

    while(PosY < 15)
    {
        PosX = 0;
        while(PosX < 8)
        {
            if((PC_Shop[PosX + (PosY * 8)] == 0) && (PC_Shop[PosX + (PosY * 8) + X - 1] == 0) && (PosX + X - 1 < 8))
            {
                if(Y == 0)
                {
                    for( j = 0; j < X; j++)
						PC_Shop[PosX + (PosY * 8)] = 1;
                    return (PosX + (PosY * 8));
                }
                else
                {
                    if((PC_Shop[(PosX + (PosY * 8)) + (Y * 8)] == 0) && (PosX + X - 1 < 8))
                    {
                        for(j = 0; j < X; j++)
                        {
                            for(int z = 1; z <= Y; z++)
                                PC_Shop[PosX + (PosY * 8) + j + z * 8] = 1;
                            PC_Shop[PosX + (PosY * 8) + j] = 1;
                        }
                        return (PosX + (PosY * 8));
                    }
                }
            }
            PosX++;
        }
        PosY++;
    }

    return j;
}
 
int ÒPointShop::MakePacket()
{
    int PacketSize = 0;
    int PacketFlag = 0;
    int Size       = 0;

    BYTE Packet1[11] = {0xC1, 0x05, 0xD0, 0x06, 0x00, 0xC2, 0x00, 0x36, 0x31, HIBYTE(HowManyItems), LOBYTE(HowManyItems)};
    BYTE Packet2[4680];

    for(int i = 0; i < HowManyItems; i++)
    {
        int LuckOptLevel = ((Items[i].Opt / 4) + (Items[i].Luck * 4) + (Items[i].Level * 8) + (Items[i].Skill * 128));
        int ItemIndex    = Items[i].ItemIndex * 16;

        BYTE BetaPacket[13] = {Items[i].SlotX, Items[i].ItemID, LuckOptLevel, Items[i].Dur, 0x00, Items[i].Exc,
                               ItemIndex, Items[i].NewOpt1, Items[i].NewOpt2, Items[i].NewOpt3, Items[i].NewOpt4,
                               Items[i].NewOpt5, 0x00};

        PacketSize = (sizeof(BetaPacket) * (i + 1));
        memcpy(&Packet2[PacketFlag], BetaPacket, PacketSize);
        PacketFlag = PacketSize;
    }

    Size = (sizeof(Packet1) + PacketSize);

    memcpy(&PCPointPacket, Packet1, sizeof(Packet1));
    memcpy(&PCPointPacket[sizeof(Packet1)], Packet2, sizeof(Packet1) + PacketSize);

    PCPointPacket[6]    = HIBYTE(Size);
    PCPointPacket[7]    = LOBYTE(Size);

    return (sizeof(Packet1) + PacketSize);
}
 
void ÒPointShop::Init()
{
    int i = 0;

    for(i = 0; i < 120; i++)
    {
        PC_Shop[i] = 0x00;
    }
    //for(i = 0; i < OBJECT_MAX; i++)
    //{
    //    AddTab[i].PC_InfoReceived = 0;
    //    AddTab[i].PC_InfoMod      = 0;
    //    AddTab[i].PC_PlayerPoints = 0;
    //}

    LoadConfigFile();

    PacketSizes     = MakePacket();
}
 
void ÒPointShop::OpenShop(DWORD PlayerID)
{
    DataSend(PlayerID, PCPointPacket, PacketSizes);
}
 
void ÒPointShop::BuyItem(DWORD PlayerID, int Position)
{
    int i               = SearchIndex(Position);
    BOOL bResult        = FALSE;

    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);

    if(i != (-1))
    {
        if(Items[i].Cost < AddTab[PlayerID].PC_PlayerPoints)
        {
            int RewardItem = Items[i].ItemIndex * 512 + Items[i].ItemID;
            ItemSerialCreateSend(PlayerID, 235, 0, 0, (DWORD)RewardItem, Items[i].Level, Items[i].Dur, Items[i].Skill,
                                 Items[i].Luck, (Items[i].Opt / 4), -1, Items[i].Exc, 0);

            DecreasePoints(PlayerID, Items[i].Cost);

			MySQL.Execute("UPDATE Character SET %s = %s - '%d' WHERE Name= '%s'", Config.PCPointsColumn, Config.PCPointsColumn, Items[i].Cost, gObj->Name);
			bResult = TRUE;
        }
    }
    if((bResult == TRUE) && (i != (-1)))
    {
        Log.ConsoleOutPut(1, c_Cyan, t_PCPOINT, "[PointShop] Character [%s] Buy Item [%d %d] Cost [%d]",
                                gObj->Name, Items[i].ItemIndex, Items[i].ItemID, Items[i].Cost);
    } 
    else 
    {
        Log.ConsoleOutPut(1, c_Red, t_PCPOINT, "[PointShop] Character [%s] Cant Buy Item [%d %d] Cost [%d]",
                                gObj->Name, Items[i].ItemIndex, Items[i].ItemID, Items[i].Cost);
    }
}
 
void ÒPointShop::SendPoints(DWORD PlayerID, int Points)
{
    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);

    AddTab[PlayerID].PC_PlayerPoints += Points;
    if(AddTab[PlayerID].PC_PlayerPoints > Config.MaximumPCPoints)
    {
        AddTab[PlayerID].PC_PlayerPoints = Config.MaximumPCPoints;
    }

    BYTE Packet[8] = {0xC1, 0x08 , 0xD0 , 0x04 , LOBYTE(AddTab[PlayerID].PC_PlayerPoints), 
                      HIBYTE(AddTab[PlayerID].PC_PlayerPoints), LOBYTE(Config.MaximumPCPoints), HIBYTE(Config.MaximumPCPoints)};

    DataSend(PlayerID, (PBYTE)Packet, Packet[1]);  

   Log.ConsoleOutPut(1, c_Cyan, t_PCPOINT, "[PointShop] SendPoint [%s] Points [%d]",gObj->Name, AddTab[PlayerID].PC_PlayerPoints);
}
 
void ÒPointShop::IncreasePoints(DWORD PlayerID, int Points)
{
    if(AddTab[PlayerID].PC_PlayerPoints + Points > Config.MaximumPCPoints)
    {
        AddTab[PlayerID].PC_PlayerPoints = Config.MaximumPCPoints;
    }
    else
    {
        AddTab[PlayerID].PC_PlayerPoints += Points;
    }
    AddTab[PlayerID].PC_InfoMod = 1;

    BYTE Packet[8] = {0xC1, 0x08 , 0xD0 , 0x04 , LOBYTE(AddTab[PlayerID].PC_PlayerPoints) , 
                     HIBYTE(AddTab[PlayerID].PC_PlayerPoints), LOBYTE(Config.MaximumPCPoints), HIBYTE(Config.MaximumPCPoints)};

    DataSend(PlayerID, (PBYTE)Packet, Packet[1]);
}
 
void ÒPointShop::DecreasePoints(DWORD PlayerID, int Points)
{
    if(AddTab[PlayerID].PC_PlayerPoints - Points < 0)
    {
        AddTab[PlayerID].PC_PlayerPoints = 0;
    }
    else
    {
        AddTab[PlayerID].PC_PlayerPoints -= Points;
    }
    AddTab[PlayerID].PC_InfoMod = 1;

    BYTE Packet[8]  = {0xC1, 0x08, 0xD0, 0x04, LOBYTE(AddTab[PlayerID].PC_PlayerPoints), 
                      HIBYTE(AddTab[PlayerID].PC_PlayerPoints), LOBYTE(Config.MaximumPCPoints), HIBYTE(Config.MaximumPCPoints)};

    DataSend(PlayerID,(PBYTE)Packet,Packet[1]);
}
 
void ÒPointShop::GetInfo(DWORD PlayerID)
{
    AddTab[PlayerID].PC_InfoReceived   = 0;
    AddTab[PlayerID].PC_InfoMod        = 0;
    AddTab[PlayerID].PC_PlayerPoints   = 0;

    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);

    if(gObj->Connected == PLAYER_PLAYING)
    {
        if((PlayerID >= OBJECT_MIN) && (PlayerID <= OBJECT_MAX))
        {
            AddTab[PlayerID].PC_InfoReceived = 1;
			MySQL.Execute("SELECT %s FROM Character WHERE Name = '%s'", Config.PCPointsColumn, gObj->Name);
		    int Points = MySQL.GetInt();

            if(Points > Config.MaximumPCPoints)
                Points = Config.MaximumPCPoints;

            SendPoints(PlayerID, Points);
        }
    }
}
 
int ÒPointShop::GetRewardPoints(int MobID)
{
    for(int i = 0; i < MobPointRecords; i++)
    {
        if(MobID == pPCMobPoint[i].MobID)
			return pPCMobPoint[i].Points;
    }
    return 0;
}
 
void ÒPointShop::LevelUp(DWORD PlayerID, int MobID)
{
    int RecvPoints  = 0;

    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);
	     
    RecvPoints = GetRewardPoints(MobID);

    if(RecvPoints > 0)
    {	
		if(AddTab[PlayerID].PC_PlayerPoints < Config.MaximumPCPoints)
		{
            IncreasePoints(PlayerID, RecvPoints);

			Chat.MessageLog(1, c_Blue, t_PCPOINT, gObj,"[PointShop] You earned %d Points", RecvPoints);
			MySQL.Execute("UPDATE Character SET %s = %s + %d WHERE Name= '%s'", Config.PCPointsColumn, Config.PCPointsColumn, RecvPoints, gObj->Name);

            if(AddTab[PlayerID].PC_InfoReceived == 0)
                GetInfo(PlayerID);
        } 
		else 
			Chat.MessageLog(1, c_Red, t_PCPOINT, gObj,"[PointShop] You Have Maximum Points");
    }
 
}				

int ÒPointShop::GetRewardCWPoints(int MobID)
{
    for(int i = 0; i < MobWCRecords; i++)
    {
        if(MobID == pWCMobPoint[i].MobID)
			return pWCMobPoint[i].Points;
    }
    return 0;
}

void ÒPointShop::LevelUpWC(DWORD PlayerID, int MobID)
{
    int RecvPoints  = 0;

    OBJECTSTRUCT *gObj = (OBJECTSTRUCT*)OBJECT_POINTER(PlayerID);

    RecvPoints = GetRewardCWPoints(MobID);

    if(RecvPoints > 0)
    {	
		gObj->m_wCashPoint += RecvPoints;
		Chat.MessageLog(1, c_Blue, t_PCPOINT, gObj,"[WCoins] You earned %d WCoins", RecvPoints);
		MySQL.Execute("UPDATE MEMB_INFO SET %s = %s + %d WHERE memb___id = '%s'", Config.WCoinsColumn, Config.WCoinsColumn, RecvPoints, gObj->AccountID);
	}
 
}			