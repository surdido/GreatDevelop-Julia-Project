// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Tornado Lite - 7.12.XX					# //
// ================================================== //


#ifndef CONFIGS_H
#define CONFIGS_H

//#define GS90
#define GSCS90
#define dVersion 2

//Function Defines //
#ifdef GS90
#define RMSTGS										".\\GameServer.ini"
#define GSSIZE										4452946
#define GetToken									0x00402CA2
#define GetNumber									0x00407257
#define ShopExcellentMod_Hook1						0x0055C6D4
#define ShopExcellentMod_Exit1						0x0055C6DF
#define ShopExcellentMod_Hook2						0x0055BC05
#define ShopExcellentMod_Exit2						0x0055BC0A
#define MonsterCount 0x7D95B94
#define MonsterReads 0x7D800B6
#define GSCheckInventoryEmptySpace ((int(*) (LPOBJ lpObj, int iItemHeight, int iItemWidth)) 0x0051C770 ) 
#define GSItemGetSize		((void(*) (int index, int & width, int & height)) 0x00558AE0 )
#define gObjDel				((void(*) (int)) 0x00403AE4)
#define gObjAddMonster		((short(*)(int iMapNumber)) 0x00508910)
#define gObjSetPosMonster	((int(*)(int aIndex, int PosTableNum)) 0x00506870)
#define gObjSetMonster		((int(*)(int aIndex, int MonsterClass)) 0x00506CA0)
#define goBjHoookLoad1 ((bool(*) (LPOBJ)) 0x0053E7E0)
#define goBjHoookLoad2 ((int(*) (LPOBJ, LPOBJ)) 0x0053E860)	   		
#define gObjInventoryDeleteItem ((void(*)(int,int)) 0x00402464)				   
#define gObjMonsterDieGiveItem ((int(*) ( LPOBJ , LPOBJ )) 0x004050DD)
#define GCInventoryItemDeleteSend ((void(*)(int,int,unsigned char)) 0x00403AE9)
#define GCServerMsgStringSend ((void(*) (char * Texto,DWORD PlayerID,int Type)) 0x004066B3)
#define GCStateInfoSendg ((void(*)(OBJECTSTRUCT *lpObj, BYTE State, BYTE ViewSkillState)) 0x004040A2) //duel
#define gObjViewportListProtocolDestroy ((void(*)(OBJECTSTRUCT* lpObj)) 0x00402F5E)	//duel
#define gObjMoveGate ((int(*)(int aIndex, int Gate)) 0x00405C9A) //duel
#define gObjUserDie ((void(*)(OBJECTSTRUCT *lpObj,OBJECTSTRUCT *lpTargetObj)) 0x0050F7F0) //duel
#define gGetItemNumber ((DWORD(*)()) 0x0051A900);
#define gObjShopBuyInventoryInsertItem ((int(*)(int, CItem)) 0x0051B520) //moss
#define ItemGetDurability ((int(*)(short index, int itemLevel, int ExellentItem, int SetItem)) 0x00558B80) //moss
#define gObjTeleport ((void(*) (int,unsigned char,unsigned char,unsigned char)) 0x00403382)
#define AddBuff ((void(*)(LPOBJ lpObj,BYTE state, BYTE ViewSkillState,int TargetIndex, int IsSkill, int a6, int Time  )) 0x0060A360)
#define CloseClient ((void(*)(DWORD))0x0040788D) 
#define gObjViewportListProtocolCreate ((void(*)(OBJECTSTRUCT* tObj))0x0052F870) // Skin
#define MsgSendV2 ((void(*)(LPOBJ lpObj, unsigned char* Msg, int size))0x00438540)	 
#define DataSend ((void(*) (DWORD PlayerID,PBYTE Packet,DWORD Size)) 0x004B3370)
#define DataRecv ((void(*) (BYTE,PBYTE,DWORD,DWORD,...)) 0x004368E0)
#define DataSendAll ((void(*)(PBYTE lpMsg, int iMsgSize)) 0x0040729D)
#define ItemSerialCreateSend ((int(*)(int aIndex, BYTE MapNumber, BYTE x, BYTE y, int type, BYTE level, BYTE dur, BYTE Op1, BYTE Op2, BYTE Op3, int LootIndex, BYTE NewOption, BYTE SetOption)) 0x00407004)
#define GCKillPlayerExpSend ((void(*)(int aIndex, int TargetIndex, int exp, int AttackDamage, BOOL MSBFlag)) 0x00455EC0)
#define gObjCalCharacter ((void(*)(int)) 0x004E8AC0)
#define CloseClient ((void(*)(DWORD))0x0040788D)   
#define GCEquipmentSend	((void(*)(int)) 0x0043C7B0)
#define GCItemListSend	((void(*)(int)) 0x0042E780)
#define gObjMakePreviewCharSet ((void(*)(int)) 0x005263D0)
#define gObjGameClose ((BOOL(*)(int)) 0x00509940)  	
#define GCMoneySend ((void(*) (DWORD,int)) 0x004075EA)
#define GSGOBJGetIndex ((short(*)(SOCKET, char* ip)) 0x00508460)
#define gEventMonsterItemDrop ((int(*) (BYTE*,BYTE*)) 0x00420330)
#define GCPkLevelSend ((void(*)(int,unsigned char)) 0x0043C2F0)
#define pShopDataLoad ((void(*)()) 0x0055C7F0)
#define GameMonsterAllCloseAndReload ((void(*)()) 0x0040759F)
#define CGLevelUpPointAdd ((int(*)(BYTE * Arg1,DWORD PlayerID)) 0x004073DD)
#define GCLevelUpMsgSend ((void(*)(int, unsigned char)) 0x0043BDC0)
#define gObjLevelUpPointAdd ((bool(*)(BYTE type, OBJECTSTRUCT* lpObj)) 0x0050D990) 	 
#endif

#ifdef GSCS90
#define RMSTGS										".\\GameServerCS.ini"
#define GSSIZE										4689920
#define GetToken									0x00402C02
#define GetNumber									0x00407B2B
#define ShopExcellentMod_Hook1						0x0056F6F4
#define ShopExcellentMod_Exit1						0x0056F6FF
#define ShopExcellentMod_Hook2						0x0056EC25
#define ShopExcellentMod_Exit2						0x0056EC2A
#define gObjMoveGate ((int(*)(int aIndex, int Gate)) 0x00545170) //duel
#define gObjTeleport ((void(*) (int,unsigned char,unsigned char,unsigned char)) 0x0040341D)
#define CloseClient ((void(*)(DWORD))0x0040822E)	
#define DataRecv ((void(*) (BYTE,PBYTE,DWORD,DWORD,...)) 0x00439900)
#define GCServerMsgStringSend ((void(*) (char * Texto,DWORD PlayerID,int Type)) 0x00406E0B)
#define ItemSerialCreateSend ((int(*)(DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD)) 0x00407897)
#define gObjViewportListProtocolCreate ((void(*)(OBJECTSTRUCT* tObj))0x00542310) // Skin
#define DataSendAll ((void(*)(PBYTE lpMsg, int iMsgSize)) 0x00407B71)				
#define gObjMonsterDieGiveItem ((int(*) ( LPOBJ , LPOBJ )) 0x0040556F)
#define GCKillPlayerExpSend ((void(*)(int aIndex, int TargetIndex, int exp, int AttackDamage, BOOL MSBFlag)) 0x004584A0)
#define DataSend ((void(*) (DWORD PlayerID,PBYTE Packet,DWORD Size)) 0x004C4390)
#define gObjMakePreviewCharSet ((void(*)(int)) 0x005389B0)
#define GCItemListSend	((void(*)(int)) 0x004300E0)
#define GCEquipmentSend	((void(*)(int)) 0x0043F830)
#define gObjCalCharacter ((void(*)(int)) 0x004FA660)
#define GCMoneySend ((void(*) (DWORD,int)) 0x00407F45)
#define GSGOBJGetIndex ((short(*)(SOCKET, char* ip)) 0x00519F00) 
#define gEventMonsterItemDrop ((int(*) (BYTE*,BYTE*)) 0x00421D50)
#define GCInventoryItemDeleteSend ((void(*)(int,int,unsigned char)) 0x00403C7E)
#define gObjInventoryDeleteItem ((void(*)(int,int)) 0x004022AC)
#define GCPkLevelSend ((void(*)(int,unsigned char)) 0x00405722) 
#define GameMonsterAllCloseAndReload ((void(*)()) 0x00407EEB)
#define pShopDataLoad ((void(*)()) 0x00407360)
#define GCLevelUpMsgSend ((void(*)(int, unsigned char)) 0x0043EE00)
#define CGLevelUpPointAdd ((int(*)(BYTE * Arg1,DWORD PlayerID)) 0x00407CED)
#define gObjLevelUpPointAdd ((bool(*)(BYTE type, OBJECTSTRUCT* lpObj)) 0x0051F9A0) 
#endif


//Configs Defines //
#define GS_CONFIG_FILE		".\\Data\\ServerInfo.dat" 
#define RMSTCommon			"..\\RMST\\Common.ini"
#define RMSTNews			".\\News.txt"
#define RMSTGM				".\\GMSystem.txt"
#define RMSTPkClear			"..\\RMST\\PkClearGuard.ini"
#define RMSTCmd				"..\\RMST\\Commands.ini"
#define RMSTEvents			"..\\RMST\\Events.ini"
#define RMSTArcher			"..\\RMST\\GoldenArcher.txt"
#define RMSTItems			"..\\RMST\\Items.ini"		
#define RMSTSkills			"..\\RMST\\Skills.ini"   
#define RMSTDrop			"..\\RMST\\ItemDropSettings.txt" 
#define RMSTIPBlock			".\\IPBlock.txt" 
#define RMSTAntiAFK			"..\\RMST\\AntiAFK.txt"
#define RMSTPets			"..\\RMST\\Pets.ini" 
#define RMSTPcPoints		"..\\RMST\\PCPoints_WCoins.dat" 
#define RMSTMossGambler		"..\\RMST\\MossGambler.ini"
#define RMSTEventTime		"..\\RMST\\EventTime.dat"
#define RMSTChatLogs		"..\\RMST\\ChatLogs"
#define RMSTConsoleLogs		"..\\RMST\\ConsoleLogs" 
#define RMSTLog				".\\Log" 


#ifdef GS90
//================================================//
// Maximum Level							      //
//================================================//
#define GS_NOEXP_LEVEL				0x0056A352
#define GS_MAX_LEVEL1				0x004E8435
#define GS_MAX_LEVEL2				0x0050D1DA
#define GS_MAX_LEVEL3				0x00582C77
#define GS_MAX_LEVEL4				0x005938F7
#define GS_MAX_LEVEL5				0x005C27F9
#define GS_MAX_MASTERLEVEL          0x004F77BF
#define GS_ML_POINTS				0x004F7984

//================================================//
// Maximum Zen								      //
//================================================//
#define MaxZen						(0x0053F2F7+3)
#define MaxZen1						(0x00452F23+3)
#define MaxZen2						(0x00453019+3)
#define MaxZen3						(0x00452F4F+2)

//================================================//
// Ancient Item Drop Rate					      //
//================================================//
#define	GS_ANCREWARD_SKILL_RATE		0x0053F39F
#define GS_ANCREWARD_LUCK_RATE		0x0053F3A6
#define GS_ANCRANDOM_SKILL_RATE		0x0053F5DF
#define	GS_ANCRANDOM_LUCK_RATE		0x0053F5E6

//================================================//
// Devil Square PartyExp					      //
//================================================//
#define GS_DS_PARTYDIFFEXP_3		0x00478870
#define GS_DS_PARTYDIFFEXP_4		0x0047887F
#define GS_DS_PARTYDIFFEXP_5		0x0047888E
#define GS_DS_PARTYEXP_2			0x004788A6
#define GS_DS_PARTYEXP_3			0x004788B5
#define GS_DS_PARTYEXP_4			0x004788C4
#define GS_DS_PARTYEXP_5			0x004788D3

//================================================//
// Skills Div								      //
//================================================//
#define GS_BERSERKER_DIV1			0x004E5B07
#define GS_BERSERKER_DIV2			0x004E5B1F
#define GS_BERSERKER_DIV3			0x004E5B34
#define GS_DAMAGEREF_DIV1			0x004E4314
#define GS_DAMAGEREF_DIV2			0x004E432C
#define GS_CRITICALDMG_COMMAND		0x004DFA44
#define GS_CRITICALDMG_ENERGY		0x004DFA64
#define GS_CRITICALDMG_TIME			0x004DFA87

//================================================//
//Transformation Rings						      //
//================================================//
#define GS_TRANSFORMATIONRING1	(0x004DBCA4+3)
#define GS_TRANSFORMATIONRING2	(0x004DBCAD+3)
#define GS_TRANSFORMATIONRING3	(0x004DBCB6+3)
#define GS_TRANSFORMATIONRING4	(0x004DBCBF+3)
#define GS_TRANSFORMATIONRING5	(0x004DBCC8+3)
#define GS_TRANSFORMATIONRING6	(0x004DBCD1+3)

//================================================//
//Summon Orbs								      //
//================================================//
#define GS_SUMMONORB1			(0x004DA297+1)
#define GS_SUMMONORB2 			(0x004DA2C8+1)
#define GS_SUMMONORB3			(0x004DA2F9+1)
#define GS_SUMMONORB4			(0x004DA32A+1)
#define GS_SUMMONORB5			(0x004DA35B+1)
#define GS_SUMMONORB6			(0x004DA38C+1)
#define GS_SUMMONORB7			(0x004DA3C0+1)

//================================================//
//Jewel Prices								      //
//================================================//
#define GS_BLESS_PRICE			(0x0055219E+3)
#define GS_SOUL_PRICE			(0x005521C0+3)
#define GS_CHAOS_PRICE			(0x005521E1+3)
#define GS_LIFE_PRICE			(0x00552203+3)
#define GS_CREATION_PRICE		(0x00552225+3)
#define GS_GUARDIAN_PRICE		(0x005522FF+3)
#define GS_FRUITS_PRICE			(0x005522A0+3)
#define GS_MONARCH_PRICE		(0x005522CE+3)
#define GS_FEATHER_PRICE		(0x005522DE+3)
#define GS_BLESSPOT_PRICE		(0x00552337+2)
#define GS_SOULPOT_PRICE		(0x0055235D+2)

#define GS_KUNDUN_ITEM_NUMB		(0x0041DFFA+6)
#define GS_KUNDUN_ANC_PERCT		(0x0041E1C5+2)


//================================================//
//Chaos Castle									  //
//================================================//
#define GS_CCPLAYER				(0x00594890+3) 

#define GS_CCREWARD1			(0x00597D69+3) 
#define GS_CCREWARD2			(0x00597D23+3)
#define GS_CCREWARD3			(0x00597C9F+3)
#define GS_CCREWARD4			(0x00597C59+3)

//================================================//
//Illusion Temple								  //
//================================================//
#define GS_ITPLAYER			(0x005DE535+6)
#define GS_IT_DROP_ID       (0x005E6713+1)
#define GS_IT_GROUP_ID      (0x005E6715+1)
#define GS_IT_ITEM_LVL      (0x005E6732+1)
#define GS_IT_ITEM_DUR      (0x005E6730+1)
#define GS_IT_ITEM_SKL      (0x005E672E+1)
#define GS_IT_ITEM_LCK      (0x005E672C+1)
#define GS_IT_ITEM_LIF      (0x005E672A+1)
#define GS_IT_ITEM_EXC      (0x005E6724+1)
#define GS_IT_ITEM_ANC      (0x005E6722+1)

//================================================//
//Item Looting Time								  //
//================================================//
#define GS_ITEM_TIME1       (0x004BB23A+1)
#define GS_ITEM_TIME2       (0x004BB3EB+1)

//================================================//
//Guild Alliance Members						  //
//================================================//
#define GS_GUILDALLIANCE		(0x00467E0D+2)

//================================================//
//GS UDP Port									  //
//================================================//
#define GS_UDP_PORT				(0x0056A21F+1)

//================================================//
//Jewel Rates									  //
//================================================//
#define GS_SOUL_RATE_NORMAL		(0x005370C3+3)
#define GS_SOUL_RATE_SPECIAL	(0x00537082+3)
#define GS_SOUL_RATE_SOCKET		(0x005370B7+3)
#define GS_SOUL_LUCK_ADD		(0x0053701C+2)
#define GS_JOL_FAIL_RATE		(0x005378D7+3)

//================================================//
//Blood Castle Reward                             //
//================================================//
#define GS_BC_DROP_ID			(0x0058810B+1)
#define GS_BC_DROP_GROUP		(0x0058810D+1)
#define GS_BC_ITEM_LVL			(0x005881B2+1)
#define GS_BC_ITEM_DUR			(0x005881B0+1)
#define GS_BC_ITEM_SKL			(0x005881AE+1)
#define GS_BC_ITEM_LCK			(0x005881AC+1)
#define GS_BC_ITEM_LIF			(0x005881AA+1)
#define GS_BC_ITEM_EXC			(0x005881A4+1)
#define GS_BC_ITEM_ANC			(0x005881A2+1)

//================================================//
//Chaos Machine Rates						      //
//================================================//
#define GS_CM_MIX_10_NORMAL		(0x005EB63F+6)
#define GS_CM_MIX_10_SPECIAL	(0x005EB65B+6)
#define GS_CM_MIX_10_SOCKET		(0x005EB678+6)
#define GS_CM_MIX_11_12_NORMAL	(0x005EB6CF+6)
#define GS_CM_MIX_11_12_SPECIAL	(0x005EB6EC+6)
#define GS_CM_MIX_11_12_SOCKET	(0x005EB709+6)
#define GS_CM_MIX_13_NORMAL		(0x005EB761+6)
#define GS_CM_MIX_13_SPECIAL	(0x005EB77E+6)
#define GS_CM_MIX_13_SOCKET		(0x005EB79A+6)
#define GS_CM_MIX_10_LUCK		(0x005EB7E7+6)
#define GS_CM_MIX_11_13_LUCK	(0x005EB7F3+6)
#define GS_CM_MIX_LUCK_ADD		(0x005EB7D8+2)
#define DEFAULTMIXRATE			(0x005EB7A9+6)

//================================================//
//Dark Lord Pet Rates							  //
//================================================//
#define GS_DARK_HORSE			(0x005EDE9C+6)
#define GS_DARK_HORSE_PRICE		(0x005EDEBB+3)
#define GS_DARK_SPIRIT			(0x005EE59D+6)
#define GS_DARK_SPIRIT_PRICE	(0x005EE5BC+3)

//================================================//
//Item Drop Rates								  //
//================================================//
#define GS_EXC_DROP_RATE           (0x0041F0E1+1)
#define GS_EXC_SKILL_RATE           (0x0041F4EA+6)
#define GS_EXC_LUCK_RATE           (0x0041F4F4+6)
#define GS_SKILL_RATE                (0x0041F543+6)
#define GS_LUCK_RATE                (0x0041F54D+6)

//================================================//
//Level Up Points							      //
//================================================//
#define GS_LVL_UP_DL1			(0x0050D3BB+2)
#define GS_LVL_UP_DL2			(0x00582DF4+2)
#define GS_LVL_UP_DL3			(0x00593A74+2)
#define GS_LVL_UP_DL4			(0x005C2976+2)
#define GS_LVL_UP_DL5			(0x005E7102+2)
#define GS_LVL_UP_MG1			(0x0050D3E3+2)
#define GS_LVL_UP_MG2			(0x00582DF4+2) 
#define GS_LVL_UP_MG3			(0x00593A74+2) 
#define GS_LVL_UP_MG4			(0x005C2976+2)
#define GS_LVL_UP_MG5			(0x005E7102+2)
#define GS_LVL_UP_NORMAL1		(0x0050D3FA+2)
#define GS_LVL_UP_NORMAL2		(0x00582E25+2)
#define GS_LVL_UP_NORMAL3		(0x00593AA5+2) 
#define GS_LVL_UP_NORMAL4		(0x005C29A7+2) 
#define GS_LVL_UP_NORMAL5		(0x005E7132+2) 
#define GS_LVL_UP_QUEST1		(0x0050D41E+2) 
#define GS_LVL_UP_QUEST2		(0x00582E6E+2) 
#define GS_LVL_UP_QUEST3		(0x00593AEE+2) 
#define GS_LVL_UP_QUEST4		(0x005C29F0+2)
#define GS_LVL_UP_QUEST5		(0x005E717C+2)

//================================================//
//White Wizard Event Reward						  //
//================================================//
#define GS_WW_DROP_ID       (0x004834D6+1)
#define GS_WW_GROUP_ID      (0x004834D8+1)
#define GS_WW_ITEM_LVL      (0x004834F5+1)
#define GS_WW_ITEM_DUR      (0x004834F3+1)
#define GS_WW_ITEM_SKL      (0x004834F1+1)
#define GS_WW_ITEM_LCK      (0x004834EF+1)
#define GS_WW_ITEM_LIF      (0x004834ED+1)
#define GS_WW_ITEM_EXC      (0x004834E7+1)
#define GS_WW_ITEM_ANC      (0x004834E5+1)

//================================================//
//Chaos Machine Mixes							  //
//================================================//
#define GS_WINGLVL1MIX		(0x005ED2EA+6)
#define GS_WINGLVL2MIX		(0x005ED2F6+6)
#define GS_WINGLVL3MIX11	(0x005F27B0+6)
#define GS_WINGLVL3MIX12	(0x005F27BC+6)
#define GS_WINGLVL3MIX21	(0x005F2EB2+6)
#define GS_WINGLVL3MIX22	(0x005F2EBE+6)
#define GS_SETITEMMIX1 (0x005F3C7B+6)
#define GS_SETITEMMIX2 (0x005F3C87+6)
#define GS_DINO_MIX (0x005EC455+6)

//================================================//
//Party Exp										  //
//================================================//
#define GS_PARTYEXP_2_NORMAL	(0x0051701E+3)
#define GS_PARTYEXP_3_NORMAL	(0x0051702D+3)
#define GS_PARTYEXP_4_NORMAL	(0x0051703C+3)
#define GS_PARTYEXP_5_NORMAL	(0x0051704B+3)
#define GS_PARTYEXP_3_SET		(0x00516FE8+3) 
#define GS_PARTYEXP_4_SET		(0x00516FF7+3)
#define GS_PARTYEXP_5_SET		(0x00517006+3)

//================================================//
// Skills										  //
//================================================//
#define GS_TWISTINGSLASH_USELV      (0x004A806B+7)
#define GS_RAGEFULBLOW_USELV        (0x004A8084+7)
#define GS_DEATHSTAB_USELV          (0x004A809D+7)
#define GS_IMPALE_USELV             (0x004A80B6+7)
#define GS_INNERSTRENGTH_USELV      (0x004A80CF+7)
#define GS_PENETRATION_USELV        (0x004A80E8+7)

#define GS_MSNORMAL01				(0x004DB03D+1) 
#define GS_MSNORMAL02				(0x004DB05D+1) 
#define GS_MSMASTER01				(0x004FAA9A+1)
#define GS_MSMASTER02				(0x004FAABA+1)
#define NormalManaShieldTime1		(0x004DB082+1) 


#define MasterManaShieldTime2		(0x004FAB15+1)

#define NormalGreatForitiuteVit01	(0x004DAD67+1)
#define NormalGreatForitiuteVit02	(0x004DADD7+1)
#define NormalGreatForitiuteVit03	(0x004DAE67+1)

#define MasterGreatForitiuteVit01	(0x004FB405+1)
#define MasterGreatForitiuteVit02	(0x004FB478+1)
#define MasterGreatForitiuteVit03	(0x004FB50D+1)

#define NormalGreatForitiuteTime	(0x004DADB1+1)
#define MasterGreatForitiuteTime	(0x004FB452+1)
//
#define GS_GFNORMAL02				(0x004DAD87+1)
#define GS_GFMASTER02				(0x004FB425+1)

//================================================//
//PK Kill Limit									  //
//================================================//
#define GS_PKBugLimitFix1 (0x004D69F9+2) 
#define GS_PKBugLimitFix2 (0x004D6DD8+2) 
#define GS_PKBugLimitFix3 (0x004D6E66+2) 

//================================================//
//Misc											  //
//================================================//
#define GS_MAPEXPLORER			(0x0057A4ED+7)
#define GUARD_SAY        (0x00771CEC+12)
#define LogAdd ((void(*) (BYTE,char*,...)) 0x0040732E) 
#endif

#ifdef GSCS90
//================================================//
// Maximum Level							      //
//================================================//
#define MaxZen						( 0x005521C7+3 ) 
#define MaxZen1						( 0x00455223+3 ) 
#define MaxZen2						( 0x00455319+3 )
#define MaxZen3						( 0x0045524F+2 )
#define GS_MAX_MASTERLEVEL          0x00508C6F
#define GS_ML_POINTS				0x00508E34

//================================================//
// Maximum Zen								      //
//================================================//
#define GS_NOEXP_LEVEL				0x0057D2E0
#define GS_MAX_LEVEL1				0x004F9FD5
#define GS_MAX_LEVEL2				0x0051F1EA
#define GS_MAX_LEVEL3				0x00596097
#define GS_MAX_LEVEL4				0x005A6D17
#define GS_MAX_LEVEL5				0x005FA039

//================================================//
// Ancient Item Drop Rate					      //
//================================================//
#define GS_ANCREWARD_SKILL_RATE		0x0055226F
#define GS_ANCREWARD_LUCK_RATE		0x00552276
#define GS_ANCRANDOM_SKILL_RATE		0x005524AF
#define	GS_ANCRANDOM_LUCK_RATE		0x005524B6

//================================================//
// Skills Div								      //
//================================================//
#define GS_BERSERKER_DIV1			0x004F7517
#define GS_BERSERKER_DIV2			0x004F752F
#define GS_BERSERKER_DIV3			0x004F7544
#define GS_DAMAGEREF_DIV1			0x004F5B34
#define GS_DAMAGEREF_DIV2			0x004F5B4C
#define GS_CRITICALDMG_COMMAND		0x004F10E4
#define GS_CRITICALDMG_ENERGY		0x004F1104
#define GS_CRITICALDMG_TIME			0x004F1127

//================================================//
//Transformation Rings						      //
//================================================//
#define GS_TRANSFORMATIONRING1	(0x004ED034+3) 
#define GS_TRANSFORMATIONRING2	(0x004ED03D+3)
#define GS_TRANSFORMATIONRING3	(0x004ED046+3)
#define GS_TRANSFORMATIONRING4	(0x004ED04F+3)
#define GS_TRANSFORMATIONRING5	(0x004ED058+3)
#define GS_TRANSFORMATIONRING6	(0x004ED061+3)

//================================================//
//Summon Orbs								      //
//================================================//
#define GS_SUMMONORB1			(0x004EB627+1) 
#define GS_SUMMONORB2 			(0x004EB658+1)
#define GS_SUMMONORB3			(0x004EB689+1) 
#define GS_SUMMONORB4			(0x004EB6BA+1)
#define GS_SUMMONORB5			(0x004EB6EB+1) 
#define GS_SUMMONORB6			(0x004EB71C+1)
#define GS_SUMMONORB7			(0x004EB750+1) 

//================================================//
//Jewel Prices								      //
//================================================//
#define GS_BLESS_PRICE			(0x005651BE+3)
#define GS_SOUL_PRICE			(0x005651E0+3)
#define GS_CHAOS_PRICE			(0x00565201+3)
#define GS_LIFE_PRICE			(0x00565223+3)
#define GS_CREATION_PRICE		(0x00565245+3)
#define GS_GUARDIAN_PRICE		(0x0056531F+3)
#define GS_FRUITS_PRICE			(0x005652C0+3)
#define GS_MONARCH_PRICE		(0x005652EE+3)
#define GS_FEATHER_PRICE		(0x005652FE+3)
#define GS_BLESSPOT_PRICE		(0x00565357+2)
#define GS_SOULPOT_PRICE		(0x0056537D+2) 

//================================================//
//Guild Alliance Members						  //
//================================================//
#define GS_GUILDALLIANCE		(0x00468DCD+2)

//================================================//
//GS UDP Port									  //
//================================================//
#define GS_UDP_PORT				(0x0057D1AD+1)

//================================================//
//Jewel Rates									  //
//================================================//
#define GS_SOUL_RATE_NORMAL		(0x0054A023+3)
#define GS_SOUL_RATE_SPECIAL	(0x00549FE2+3)
#define GS_SOUL_RATE_SOCKET		(0x0054A017+3)
#define GS_SOUL_LUCK_ADD		(0x00549F7C+2)
#define GS_JOL_FAIL_RATE		(0x0054A837+3)

//================================================//
//Chaos Machine Rates						      //
//================================================//
#define GS_CM_MIX_10_NORMAL		(0x006203AF+6)
#define GS_CM_MIX_10_SPECIAL	(0x006203CB+6)
#define GS_CM_MIX_10_SOCKET		(0x006203E8+6)
#define GS_CM_MIX_11_12_NORMAL	(0x0062043F+6)
#define GS_CM_MIX_11_12_SPECIAL	(0x0062045C+6)
#define GS_CM_MIX_11_12_SOCKET	(0x00620479+6) 
#define GS_CM_MIX_13_NORMAL		(0x006204D1+6)
#define GS_CM_MIX_13_SPECIAL	(0x006204EE+6)
#define GS_CM_MIX_13_SOCKET		(0x0062050A+6)
#define GS_CM_MIX_10_LUCK		(0x00620557+6)
#define GS_CM_MIX_11_13_LUCK	(0x00620563+6)
#define GS_CM_MIX_LUCK_ADD		(0x00620548+2)
#define DEFAULTMIXRATE			(0x00620519+6)

//================================================//
//Dark Lord Pet Rates							  //
//================================================//
#define GS_DARK_HORSE			(0x00622C0C+6)
#define GS_DARK_HORSE_PRICE		(0x00622C2B+3)
#define GS_DARK_SPIRIT			(0x0062330D+6)
#define GS_DARK_SPIRIT_PRICE	(0x0062332C+3)

//================================================//
//Item Drop Rates								  //
//================================================//
#define GS_EXC_DROP_RATE          (0x00420B3A+1)
#define GS_EXC_SKILL_RATE         (0x00420F43+6)
#define GS_EXC_LUCK_RATE          (0x00420F4D+6)
#define GS_SKILL_RATE             (0x00420F9C+6)
#define GS_LUCK_RATE              (0x00420FA6+6) 

//================================================//
//Item Looting Time								  //
//================================================//
#define GS_ITEM_TIME1       (0x004CC25A+1)
#define GS_ITEM_TIME2       (0x004CC40B+1)

//================================================//
//Level Up Points							      //
//================================================//
#define GS_LVL_UP_DL1			(0x0051F3CB+2)
#define GS_LVL_UP_DL2			(0x00596214+2) 
#define GS_LVL_UP_DL3			(0x005A6E94+2)
#define GS_LVL_UP_DL4			(0x005FA1B6+2)
#define GS_LVL_UP_DL5			(0x0061BE82+2)

#define GS_LVL_UP_MG1			(0x0051F3F3+2) 
#define GS_LVL_UP_MG2			(0x00596214+2)
#define GS_LVL_UP_MG3			(0x005A6E94+2)
#define GS_LVL_UP_MG4			(0x005FA1B6+2)
#define GS_LVL_UP_MG5			(0x0061BE82+2)

#define GS_LVL_UP_NORMAL1		(0x0051F40A+2) 
#define GS_LVL_UP_NORMAL2		(0x00596245+2)
#define GS_LVL_UP_NORMAL3		(0x005A6EC5+2) 
#define GS_LVL_UP_NORMAL4		(0x005FA1E7+2) 
#define GS_LVL_UP_NORMAL5		(0x0061BEB2+2)

#define GS_LVL_UP_QUEST1		(0x0051F42E+2)
#define GS_LVL_UP_QUEST2		(0x0059628E+2)
#define GS_LVL_UP_QUEST3		(0x005A6F0E+2) 
#define GS_LVL_UP_QUEST4		(0x005FA230+2)
#define GS_LVL_UP_QUEST5		(0x0061BEFC+2) 

//================================================//
//Chaos Machine Mixes							  //
//================================================//
#define GS_WINGLVL1MIX			(0x0062205A+6) 
#define GS_WINGLVL2MIX			(0x00622066+6) 
#define GS_WINGLVL3MIX21		(0x006284F2+6) 
#define GS_WINGLVL3MIX22		(0x006284FE+6) 
#define GS_WINGLVL3MIX11		(0x00627DF0+6)
#define GS_WINGLVL3MIX12		(0x00627DFC+6) 
#define GS_SETITEMMIX1			(0x006292BB+6)
#define GS_SETITEMMIX2			(0x006292C7+6)
#define GS_DINO_MIX				(0x006211C5+6) 

//================================================//
//Party Exp										  //
//================================================//
#define GS_PARTYEXP_2_NORMAL	(0x0052920E+3)
#define GS_PARTYEXP_3_NORMAL	(0x0052921D+3)
#define GS_PARTYEXP_4_NORMAL	(0x0052922C+3)
#define GS_PARTYEXP_5_NORMAL	(0x0052923B+3) 
#define GS_PARTYEXP_3_SET		(0x005291D8+3)
#define GS_PARTYEXP_4_SET		(0x005291E7+3)
#define GS_PARTYEXP_5_SET		(0x005291F6+3)

//================================================//
// Skills										  //
//================================================//
#define GS_TWISTINGSLASH_USELV      (0x004B908B+7)
#define GS_RAGEFULBLOW_USELV        (0x004B90A4+7)
#define GS_DEATHSTAB_USELV          (0x004B90BD+7)
#define GS_IMPALE_USELV             (0x004B90D6+7)
#define GS_INNERSTRENGTH_USELV      (0x004B90EF+7)
#define GS_PENETRATION_USELV        (0x004B9108+7)

#define GS_MSNORMAL01				(0x004EC3CD+1)
#define GS_MSNORMAL02				(0x004EC3ED+1)
#define GS_MSMASTER01				(0x0050BF4A+1)
#define GS_MSMASTER02				(0x0050BF6A+1)
#define NormalManaShieldTime1		(0x004EC412+1)
#define MasterManaShieldTime2		(0x0050BFC5+1)

#define NormalGreatForitiuteVit01   (0x004EC0F7+1)	
#define NormalGreatForitiuteVit02	(0x004EC167+1)
#define NormalGreatForitiuteVit03	(0x004EC1F7+1) 


#define MasterGreatForitiuteVit01	(0x0050C915+1)
#define MasterGreatForitiuteVit02	(0x0050C988+1)
#define MasterGreatForitiuteVit03	(0x0050CA1D+1)

#define GS_GFNORMAL02               (0x004EC0F7+1)
#define GS_GFMASTER02				(0x0050C935+1)
#define NormalGreatForitiuteTime	(0x004EC141+1) 
#define MasterGreatForitiuteTime	(0x0050C962+1)
//================================================//
//PK Kill Limit									  //
//================================================//
#define GS_PKBugLimitFix1 (0x004E7BD9+2) 
#define GS_PKBugLimitFix2 (0x004E7FB8+2) 
#define GS_PKBugLimitFix3 (0x004E8055+2) 

//================================================//
// Castle Siege & Crywolf Offsets				  //
//================================================//
#define GSCS_LOT_MAXPRICE			0x0046D352
#define GSCS_SENIOR_MAXZEN1			0x00435B57
#define GSCS_SENIOR_MAXZEN2			0x00435B75
#define GSCS_LORDMIX_MAXUSE			0x00624585
#define GSCS_CRYWOLF_REWARD_ELF		0x005F623F
#define GSCS_CRYWOLF_REWARD_TOP5	0x005F633F

//================================================//
//Map Explorer									  //
//Defines The Max Number of Maps			      //
//Configurable On GameServerCS					  //
//================================================//
#define GS_MAPEXPLORER			(0x0058D777+7) // Default 22
#define LogAdd ((void(*) (BYTE,char*,...)) 0x00407C07) 
#endif

class cConfigs
{
private:
	void LoadGmSystem();  									 
	void LoadAntiAfk();	
	void LoadDuel();
	void LoadNotice();
	void LoadPets();
	void LoadArcher();
	void LoadCommands();
	void LoadPkClearGuard();
	void ZenFixes();
	void PartyZenFixes();
	void LoadNews();
public:			 
	cConfigs();
	~cConfigs();
	void LoadFixes();	
	void LoadConfigsInGS();
	void LoadAll();
	long GetInt(long Min, long Max, long Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FolderName);
	char GetChar(long Min, long Max, unsigned char Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FolderName);

	#ifdef GS90
	int EldaradoEventType;
	int CCAllowingPlayers;
	int BCAllowingPlayers;
	int BCEnterMasterType;
	int DSAllowingPlayers; 
	#endif

	int UseChecksum;	  
	int PersonalIDFix;	 
	int GuildIDFix;
	int DisableLogs;
	int AllowExeAnc;
	int AllowJohAnc;
	int AllowExeSock;
	int MaxLifeOpt;
	int Use65kStats;
	int CSSkillsOnNOrmal;
	int Enable65kStats;
	int DumpFile;

	char ResetColumn[25];	

	int IsNews;
	char ConnectNotice[100];	
	int ConnectInfo; 
	struct sCommands
	{
		int MaxLvl; 
		int IsGg;
		int IsPost;

		int PostLvl;
		DWORD MaxAddedStats;
		DWORD PostPriceZen;	
		int PostPricePCPoint;
		int PostPriceWCoin;
		int PostColor;  

		int IsBanPost;
		int IsBanAcc;
		int IsBanChar;
		int IsDrop;
		int IsReload;
		int IsGmove; 
		int IsSetPK;
		int IsTime;
		int IsOnline; 
		int IsZenDrop;
		int IsStatus;
		int IsSetChar; 
		int IsSetZen;

		int SkinEnabled;
		int SkinOnlyForGm;
		int SkinLevelReq;
		DWORD SkinPriceZen;
		int SkinPricePcPoint;
		int SkinPriceWCoin;

		int IsMultyVault;
		int NumberOfVaults;	   
		DWORD ZenForChange;
		int PcPointForChange;
		int WCoinForChange;

		int AddPointEnabled;
		int AddPointLevelReq;  
		DWORD AddPriceZen; 
		int AddPricePCPoint;
		int AddPriceWCoin;
	}Commands;

	struct sPkClear
	{
		int Enabled;
		int NpcId;	  
		int OnlyForGm;
		int Type;	
		DWORD PriceZen;
		DWORD PriceZenForAll;	  
		int PricePcPoints;
		int PricePcPointsForAll;	   
		int PriceWCoins;
		int PriceWCoinsForAll;
		int LevelReq;
	};	

	sPkClear ClearNpc;			 
	sPkClear ClearCommand;


	struct sGmConfig
	{	  
		int IsGMSystem;
		int IsGMInDB;
	}GmSystemConfig;	 

	struct sDuel
	{
		int Enabled;
		int Ranking;
		int Logging;
	}Duel;

	struct sAntiAfkConfig
	{
		int Enabled;
		int Time;
		int Warnings;
	}AntiAfkConfig;

	struct sArcher
	{
		int Enabled;
		int ZenReward;
		int WCoinsReward;
		int PCPointsReward;
		int NeedRenaAmount; 
	}Archer;

	struct cZen
	{
		int	Enabled;
		int MasterDivisor;
		int NormalDivisor;
		int	MasterZen;
		int NormalZen;

	};

	cZen Zen;			 
	cZen PartyZen; 

	int GuildRes;
	int GuildLevel;

	struct sPanda
	{
		int PetPandaDefense;
		int PetPandaAttackDamageMinLeft;
		int PetPandaAttackDamageMaxLeft;
		int PetPandaAttackDamageMinRight;
		int PetPandaAttackDamageMaxRight;
		int PetPandaMagicDamageMin;
		int PetPandaMagicDamageMax;
		int PetPandaMagicSpeed;
		int PetPandaAttackSpeed;
		int PetPandaExpirence;
		int PetPandaMLExpirence;

		int PandaRingDefense;
		int PandaRingAttackDamageMinLeft;
		int PandaRingAttackDamageMaxLeft;
		int PandaRingAttackDamageMinRight;
		int PandaRingAttackDamageMaxRight;
		int PandaRingMagicDamageMin;
		int PandaRingMagicDamageMax;
		int PandaRingMagicSpeed;
		int PandaRingAttackSpeed;
		int PandaRingExpirence;
		int PandaRingMLExpirence;
	}Panda;
};
extern cConfigs Config;

#endif