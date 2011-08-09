// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.0								# //
// ================================================== //

#include "StdAfx.h"
#include "Configs.h"
#include "Logger.h"
#include "GMSystem.h"
#include "AntiAFK.h"
#include "News.h"
#include "SQL.h"
#include "DropSystem.h"
#include "Archer.h"
#include "PCPoint.h"
#include "MossGambler.h"
cConfigs Config;	  

cConfigs::cConfigs()
{
}

cConfigs::~cConfigs()
{
}

void cConfigs::LoadGmSystem()
{		  					   
	GmSystemConfig.IsGMSystem	= GetInt(0, 1, 0, "GMSystem", "IsGMSystem",	RMSTGM);		
	if(!GmSystemConfig.IsGMSystem)return;
	GmSystemConfig.IsGMInDB	= GetInt(0, 1, 0, "GMSystem", "IsGMInDB",	RMSTGM);
	GmSystem.Load();
} 


void cConfigs::LoadNews()
{
	IsNews						= GetInt(0, 1,					1,		"News",			"NewsSystemEnabled",			RMSTNews);
	if(!IsNews)return;
	_beginthread(NewsSystem, 0, NULL);
}

void cConfigs::ZenFixes()
{
	Zen.Enabled						= GetInt(0, 1,					1,		"ZenSettings",	"NewFormulaEnabled",			RMSTCommon);
	if(!Zen.Enabled)return;
	Zen.MasterZen					= GetInt(0, 65535,				20,		"ZenSettings",	"AddZen_ML",			RMSTCommon);
	Zen.NormalZen					= GetInt(0, 65535,				20,		"ZenSettings",	"AddZen_Normal",		RMSTCommon);
	Zen.MasterDivisor				= GetInt(0, 65535,				20,		"ZenSettings",	"Zen_MasterDivisor",	RMSTCommon);
	Zen.NormalDivisor				= GetInt(0, 65535,				20,		"ZenSettings",	"Zen_NormalDivisor",	RMSTCommon);
}

void cConfigs::PartyZenFixes()
{
	PartyZen.Enabled					= GetInt(0, 1,					1,		"PartyZenSettings",	"NewFormulaEnabled",	RMSTCommon);
	if(!PartyZen.Enabled)return;
	PartyZen.MasterZen					= GetInt(0, 65535,				20,		"PartyZenSettings",	"AddZen_ML",			RMSTCommon);
	PartyZen.NormalZen					= GetInt(0, 65535,				20,		"PartyZenSettings",	"AddZen_Normal",		RMSTCommon);
	PartyZen.MasterDivisor				= GetInt(0, 65535,				20,		"PartyZenSettings",	"Zen_MasterDivisor",	RMSTCommon);
	PartyZen.NormalDivisor				= GetInt(0, 65535,				20,		"PartyZenSettings",	"Zen_NormalDivisor",	RMSTCommon);
}

void cConfigs::LoadPets()
{		  																									   
	Panda.PetPandaDefense				= GetInt(0, 1000,			10,		"Panda",		"PetPandaDefense",				RMSTPets);
	Panda.PetPandaAttackDamageMinLeft	= GetInt(0, 1000,			10,		"Panda",		"PetPandaAttackDamageMinLeft",	RMSTPets);
	Panda.PetPandaAttackDamageMaxLeft	= GetInt(0, 1000,			10,		"Panda",		"PetPandaAttackDamageMaxLeft",	RMSTPets);
	Panda.PetPandaAttackDamageMinRight	= GetInt(0, 1000,			10,		"Panda",		"PetPandaAttackDamageMinRight",	RMSTPets);
	Panda.PetPandaAttackDamageMaxRight	= GetInt(0, 1000,			10,		"Panda",		"PetPandaAttackDamageMaxRight",	RMSTPets);
	Panda.PetPandaMagicDamageMin		= GetInt(0, 1000,			10,		"Panda",		"PetPandaMagicDamageMin",		RMSTPets);
	Panda.PetPandaMagicDamageMax		= GetInt(0, 1000,			10,		"Panda",		"PetPandaMagicDamageMax",		RMSTPets);
	Panda.PetPandaMagicSpeed			= GetInt(0, 1000,			10,		"Panda",		"PetPandaMagicSpeed",			RMSTPets);
	Panda.PetPandaAttackSpeed			= GetInt(0, 1000,			10,		"Panda",		"PetPandaAttackSpeed",			RMSTPets);

	Panda.PandaRingDefense				= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingDefense",				RMSTPets);
	Panda.PandaRingAttackDamageMinLeft	= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingAttackDamageMinLeft",	RMSTPets);
	Panda.PandaRingAttackDamageMaxLeft	= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingAttackDamageMaxLeft",	RMSTPets);
	Panda.PandaRingAttackDamageMinRight	= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingAttackDamageMinRight",RMSTPets);
	Panda.PandaRingAttackDamageMaxRight	= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingAttackDamageMaxRight",RMSTPets);
	Panda.PandaRingMagicDamageMin		= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingMagicDamageMin",		RMSTPets);
	Panda.PandaRingMagicDamageMax		= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingMagicDamageMax",		RMSTPets);
	Panda.PandaRingMagicSpeed			= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingMagicSpeed",			RMSTPets);
	Panda.PandaRingAttackSpeed			= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingAttackSpeed",			RMSTPets);
																										  
	Panda.PetPandaExpirence				= GetInt(0, 10000,			100,	"Panda",		"PetPandaExpirence",			RMSTPets);
	Panda.PetPandaMLExpirence			= GetInt(0, 10000,			100,	"Panda",		"PetPandaMLExpirence",			RMSTPets);

	Panda.PandaRingExpirence			= GetInt(0, 10000,			100,	"PandaRing",	"PandaRingExpirence",			RMSTPets);
	Panda.PandaRingMLExpirence			= GetInt(0, 10000,			100,	"PandaRing",	"PandaRingMLExpirence",			RMSTPets);
}

void cConfigs::LoadNotice()
{	
	ConnectInfo					= GetInt(0, 1,					1,		"Connect",		"ConnectInfo",					RMSTGS);
	GetPrivateProfileString("Connect","ConnectNotice","Powered by RMST Tornado 7.10.xx",ConnectNotice,sizeof(ConnectNotice),RMSTGS); 
} 

void cConfigs::LoadDuel()
{		  			   
	Duel.Enabled					= GetInt(0, 1,					1,		"DuelManager",	"DuelEnabled",					RMSTCommon);  
	if(!Duel.Enabled)return;
	Duel.Ranking					= GetInt(0, 1,					0,		"DuelManager",	"DuelRanking",					RMSTCommon);
	Duel.Logging					= GetInt(0, 1,					1,		"DuelManager",	"DuelLogging",					RMSTCommon);
}

void cConfigs::LoadConfigsInGS()
{								  	 

	#ifdef GS90
	DWORD *LoreGuard = (DWORD*)GUARD_SAY;
	char Lore[25];
	GetPrivateProfileString("Connect","GuardSay","Don't waste my time!",Lore,25,RMSTGS);
	memset(&LoreGuard[0],0,25);
	memcpy(&LoreGuard[0],Lore,strlen(Lore));
	#endif

	DWORD dword;
	BYTE byte;

	dword = GetInt(300, 1000, 400,"LevelSettings", "MaxLevel", RMSTCommon);
	*(unsigned int*) GS_MAX_LEVEL1 = dword;
	*(unsigned int*) GS_MAX_LEVEL2 = dword;
	*(unsigned int*) GS_MAX_LEVEL3 = dword;
	*(unsigned int*) GS_MAX_LEVEL4 = dword;
	*(unsigned int*) GS_MAX_LEVEL5 = dword;

	*(unsigned int*) GS_NOEXP_LEVEL = GetInt(401, 1001, 401,"LevelSettings", "MaxXPLevel", RMSTCommon);
	*(unsigned int*) GS_MAX_MASTERLEVEL = GetInt(1, 400, 200,"LevelSettings", "MaxMasterLevel", RMSTCommon);

	dword = GetInt(0, 360, 120,"ItemDropRates", "LootingTime", RMSTItems);
	*(unsigned int*) GS_ITEM_TIME1 =	1000 * dword;
	*(unsigned int*) GS_ITEM_TIME2 =	1000 * dword;

	*(unsigned int*) GS_TRANSFORMATIONRING1 = GetInt(0, 600, 2,"TransformationRings","TransformRing1",RMSTItems);
	*(unsigned int*) GS_TRANSFORMATIONRING2 = GetInt(0, 600, 7,"TransformationRings","TransformRing2",RMSTItems);
	*(unsigned int*) GS_TRANSFORMATIONRING3 = GetInt(0, 600, 14,"TransformationRings","TransformRing3",RMSTItems);
	*(unsigned int*) GS_TRANSFORMATIONRING4 = GetInt(0, 600, 8,"TransformationRings","TransformRing4",RMSTItems);
	*(unsigned int*) GS_TRANSFORMATIONRING5 = GetInt(0, 600, 9,"TransformationRings","TransformRing5",RMSTItems);
	*(unsigned int*) GS_TRANSFORMATIONRING6 = GetInt(0, 600, 41,"TransformationRings","TransformRing6",RMSTItems);

	*(unsigned char*) GS_SUMMONORB1 = GetChar(0, 600, 26,"SummonOrbs","OrbSummon1",RMSTItems);
	*(unsigned char*) GS_SUMMONORB2 = GetChar(0, 600, 32,"SummonOrbs","OrbSummon2",RMSTItems);
	*(unsigned char*) GS_SUMMONORB3 = GetChar(0, 600, 21,"SummonOrbs","OrbSummon3",RMSTItems);
	*(unsigned char*) GS_SUMMONORB4 = GetChar(0, 600, 20,"SummonOrbs","OrbSummon4",RMSTItems);
	*(unsigned char*) GS_SUMMONORB5 = GetChar(0, 600, 10,"SummonOrbs","OrbSummon5",RMSTItems);
	*(unsigned char*) GS_SUMMONORB6 = GetChar(0, 600, 150,"SummonOrbs","OrbSummon6",RMSTItems);
	*(unsigned char*) GS_SUMMONORB7 =  GetChar(0, 600, 151,"SummonOrbs","OrbSummon7",RMSTItems);

	
	*(unsigned int*) GS_BLESS_PRICE = GetInt(0, 2000000000, 6000000,"JewelPrices","JewelOfBlessPrice",RMSTItems);
 	*(unsigned int*) GS_SOUL_PRICE = GetInt(0, 2000000000, 9000000,"JewelPrices","JewelOfSoulPrice",RMSTItems);
	*(unsigned int*) GS_CHAOS_PRICE = GetInt(0, 2000000000, 810000,"JewelPrices","JewelOfChaosPrice",RMSTItems);
	*(unsigned int*) GS_LIFE_PRICE =  GetInt(0, 2000000000, 45000000,"JewelPrices","JewelOfLifePrice",RMSTItems);
	*(unsigned int*) GS_CREATION_PRICE = GetInt(0, 2000000000, 36000000,"JewelPrices","JewelOfCreationPrice",RMSTItems);
	*(unsigned int*) GS_GUARDIAN_PRICE = GetInt(0, 2000000000, 60000000,"JewelPrices","JewelOfGuardianPrice",RMSTItems);
	*(unsigned int*) GS_FRUITS_PRICE = GetInt(0, 2000000000, 33000000,"JewelPrices","FruitPrice",RMSTItems);
	*(unsigned int*) GS_MONARCH_PRICE = GetInt(0, 2000000000, 750000,"JewelPrices","CrestOfMonarchPrice",RMSTItems);
	*(unsigned int*) GS_FEATHER_PRICE = GetInt(0, 2000000000, 180000,"JewelPrices","LochsFeatherPrice",RMSTItems);
	*(unsigned int*) GS_BLESSPOT_PRICE = GetInt(0, 2000000000, 900000,"JewelPrices","PotionOfBlessPrice",RMSTItems);
	*(unsigned int*) GS_SOULPOT_PRICE = GetInt(0, 2000000000, 450000,"JewelPrices","PotionOfSoulPrice",RMSTItems);
#ifdef GS90
	*(unsigned int*) GS_KUNDUN_ANC_PERCT = GetInt(0,10000,25,"Kundun","KundunDropAncRate",RMSTItems);
	*(unsigned char*) GS_KUNDUN_ITEM_NUMB = GetChar(0,20,3,"Kundun","KundunDropItemCount",RMSTItems);

	*(unsigned char*) GS_CCPLAYER = GetChar(0,20,2,"ChaosCastle","ChaosCastleMinPlayers",RMSTEvents);
	
	*(unsigned char*) GS_CCREWARD1 = GetChar(0,15,14,"ChaosCastle","ChaosCastleRewardType1IndexID",RMSTEvents) * 512 + GetChar(0,255,16,"ChaosCastle","ChaosCastleRewardType1GroupID",RMSTEvents);
	*(unsigned char*) GS_CCREWARD2 = GetChar(0,15,14,"ChaosCastle","ChaosCastleRewardType1IndexID",RMSTEvents) * 512 + GetChar(0,255,13,"ChaosCastle","ChaosCastleRewardType1GroupID",RMSTEvents);
	*(unsigned char*) GS_CCREWARD3 = GetChar(0,15,14,"ChaosCastle","ChaosCastleRewardType1IndexID",RMSTEvents) * 512 + GetChar(0,255,22,"ChaosCastle","ChaosCastleRewardType1GroupID",RMSTEvents);
	*(unsigned char*) GS_CCREWARD4 = GetChar(0,15,14,"ChaosCastle","ChaosCastleRewardType1IndexID",RMSTEvents) * 512 + GetChar(0,255,14,"ChaosCastle","ChaosCastleRewardType1GroupID",RMSTEvents); 
	

	*(unsigned char*) GS_ITPLAYER = GetChar(0,20,4,"IllusionTemple","ItMinPlayers",RMSTEvents);
	
	*(unsigned char*) GS_IT_DROP_ID = GetChar(0,15,15,"IllusionTemple","ItDropID",RMSTEvents);
	*(unsigned char*) GS_IT_GROUP_ID = GetChar(0,255,12,"IllusionTemple","ItDropGroup",RMSTEvents);
	*(unsigned char*) GS_IT_ITEM_LVL = GetChar(0,15,0,"IllusionTemple","ItDropLevel",RMSTEvents);
	*(unsigned char*) GS_IT_ITEM_SKL =  GetChar(0,1,0,"IllusionTemple","ItDropWithSkill",RMSTEvents);
	*(unsigned char*) GS_IT_ITEM_LCK = GetChar(0,1,0,"IllusionTemple","ItDropWithLuck",RMSTEvents);
	*(unsigned char*) GS_IT_ITEM_LIF = GetChar(0,7,0,"IllusionTemple","ItDropLifeAdd",RMSTEvents);
	*(unsigned char*) GS_IT_ITEM_EXC = GetChar(0,63,0,"IllusionTemple","ItDropExcOpt",RMSTEvents);
	*(unsigned char*) GS_IT_ITEM_ANC = GetChar(0,255,0,"IllusionTemple","ItDropAncOpt",RMSTEvents);

	*(unsigned char *) GS_BC_DROP_ID = GetChar(0,15,15,"BloodCastle","BcDropID",RMSTEvents);
	*(unsigned char *) GS_BC_DROP_GROUP = GetChar(0,255,12,"BloodCastle","BcDropGroup",RMSTEvents);
	*(unsigned char *) GS_BC_ITEM_LVL = GetChar(0,15,0,"BloodCastle","BcDropLevel",RMSTEvents);
	*(unsigned char *) GS_BC_ITEM_SKL = GetChar(0,1,0,"BloodCastle","BcDropWithSkill",RMSTEvents);
	*(unsigned char *) GS_BC_ITEM_LCK = GetChar(0,1,0,"BloodCastle","BcDropWithLuck",RMSTEvents);
	*(unsigned char *) GS_BC_ITEM_LIF = GetChar(0,7,0,"BloodCastle","BcDropLifeAdd",RMSTEvents);
	*(unsigned char *) GS_BC_ITEM_EXC = GetChar(0,63,0,"BloodCastle","BcDropExcOpt",RMSTEvents);
	*(unsigned char *) GS_BC_ITEM_ANC = GetChar(0,255,0,"BloodCastle","BcDropAncOpt",RMSTEvents);

	*(unsigned char *) GS_WW_DROP_ID = GetChar(0,15,13,"WhiteWizard","WizardDropItemID",RMSTEvents);
	*(unsigned char *) GS_WW_GROUP_ID = GetChar(0,255,20,"WhiteWizard","WizardDropGroup",RMSTEvents);
	*(unsigned char *) GS_WW_ITEM_LVL = GetChar(0,15,0,"WhiteWizard","WizardDropLevel",RMSTEvents);
	*(unsigned char *) GS_WW_ITEM_SKL = GetChar(0,1,0,"WhiteWizard","WizardDropWithSkill",RMSTEvents);
	*(unsigned char *) GS_WW_ITEM_LCK = GetChar(0,1,0,"WhiteWizard","WizardDropWithLuck",RMSTEvents);
	*(unsigned char *) GS_WW_ITEM_LIF = GetChar(0,7,0,"WhiteWizard","WizardDropLifeAdd",RMSTEvents);
	*(unsigned char *) GS_WW_ITEM_EXC = GetChar(0,63,0,"WhiteWizard","WizardDropExcOpt",RMSTEvents);
	*(unsigned char *) GS_WW_ITEM_ANC = GetChar(0,255,0,"WhiteWizard","WizardDropAncOpt",RMSTEvents);
	
#endif
	*(unsigned char*) GS_GUILDALLIANCE = GetChar(0,50,20,"Guild","GuildAllianceMinPlayers",RMSTCommon);

	*(unsigned char*) GS_PKBugLimitFix1 = GetChar(0, 1000, 20,"PKOptions", "PKKillLimit", RMSTCommon);
    *(unsigned char*) GS_PKBugLimitFix2 = GetChar(0, 1000, 20,"PKOptions", "PKKillLimit", RMSTCommon);
    *(unsigned char*) GS_PKBugLimitFix3 = GetChar(0, 1000, 20,"PKOptions", "PKKillLimit", RMSTCommon);

	*(unsigned int*) GS_UDP_PORT = GetInt(0, 99999, 60006,"Connect","UDP-Port",RMSTGS);

	*(unsigned char*) GS_SOUL_RATE_NORMAL = GetChar(0,100,60,"JewelRates","SoulSuccessRateNormal",RMSTItems);
	*(unsigned char*) GS_SOUL_RATE_SPECIAL = GetChar(0,100,50,"JewelRates","SoulSuccessRateSpecial",RMSTItems);
	*(unsigned char*) GS_SOUL_RATE_SOCKET = GetChar(0,100,40,"JewelRates","SoulSuccessRateSocket",RMSTItems);
	*(unsigned char*) GS_SOUL_LUCK_ADD = GetChar(0,100,20,"JewelRates","SoulSuccessRateLuck",RMSTItems);
	*(unsigned char*) GS_JOL_FAIL_RATE = GetChar(0,100,50,"JewelRates","LifeFailRate",RMSTItems);

	byte = GetChar(0, 100, 60,"ChaosMachineMixes", "ChaosMix10Rate", RMSTItems);
	*(unsigned char*)  GS_CM_MIX_10_NORMAL = byte;
	*(unsigned char*)  GS_CM_MIX_10_SPECIAL = byte;
	*(unsigned char*)  GS_CM_MIX_10_SOCKET = byte;
	byte = GetChar(0, 100, 50,"ChaosMachineMixes", "ChaosMix11_12Rate", RMSTItems);
	*(unsigned char*)  GS_CM_MIX_11_12_NORMAL = byte;
	*(unsigned char*)  GS_CM_MIX_11_12_SPECIAL = byte;
	*(unsigned char*)  GS_CM_MIX_11_12_SOCKET = byte;
	byte = GetChar(0, 100, 40,"ChaosMachineMixes", "ChaosMix13Rate", RMSTItems);
	*(unsigned char*)  GS_CM_MIX_13_NORMAL = byte;
	*(unsigned char*)  GS_CM_MIX_13_SPECIAL = byte;
	*(unsigned char*)  GS_CM_MIX_13_SOCKET = byte;
	byte = GetChar(0, 100, 75,"ChaosMachineMixes", "ChaosMixWithLuck", RMSTItems);
	*(unsigned char*) GS_CM_MIX_10_LUCK = byte;
	*(unsigned char*) GS_CM_MIX_11_13_LUCK = byte;
	*(unsigned char*) GS_CM_MIX_LUCK_ADD = GetChar(0, 100, 20,"ChaosMachineMixes","ChaosMixRateIncreaseWithLuck",RMSTItems);
	*(unsigned char*) DEFAULTMIXRATE = GetChar(0, 100, 45,"ChaosMachineMixes","ChaosMixDefaultRate",RMSTItems);
	*(unsigned char*) GS_WINGLVL1MIX = GetChar(0, 100, 90,"ChaosMachineMixes","WingMixLvl1SuccessRate",RMSTItems);
	*(unsigned char*) GS_WINGLVL2MIX = GetChar(0, 100, 90,"ChaosMachineMixes","WingMixLvl2SuccessRate",RMSTItems);
	byte = GetChar(0, 100, 60,"ChaosMachineMixes","CondorMixSuccessRate",RMSTItems);
	*(unsigned char *) GS_WINGLVL3MIX11 = byte;
	*(unsigned char *) GS_WINGLVL3MIX12 = byte;
	byte = GetChar(0, 100, 40,"ChaosMachineMixes","WingMixLvl3SuccessRate",RMSTItems);
	*(unsigned char *) GS_WINGLVL3MIX21 = byte;
	*(unsigned char *) GS_WINGLVL3MIX22 = byte;

	*(unsigned char*) GS_SETITEMMIX1 = GetChar(0, 100, 80,"ChaosMachineMixes","380LevelMixSuccessRate",RMSTItems);
	*(unsigned char*) GS_SETITEMMIX2 = GetChar(0, 100, 80,"ChaosMachineMixes","380LevelMixSuccessRate",RMSTItems);
	*(unsigned int*) GS_DINO_MIX = GetInt(0, 100, 70,"ChaosMachineMixes","DinorantMixSuccessRate",RMSTItems);
	
	*(unsigned int*) GS_DARK_HORSE = GetInt(0, 100, 60,"DLPets","DarkHorseMixSuccessRate",RMSTItems);
	*(unsigned int*) GS_DARK_HORSE_PRICE = GetInt(0, 2000000000, 5000000,"DLPets","DarkHorseMixPrice",RMSTItems);
   	*(unsigned int*) GS_DARK_SPIRIT = GetInt(0, 100, 60,"DLPets","DarkSpiritMixSuccessRate",RMSTItems);
	*(unsigned int*) GS_DARK_SPIRIT_PRICE = GetInt(0, 2000000000, 1000000,"DLPets","DarkSpiritMixPrice",RMSTItems);

	*(unsigned int*) GS_EXC_DROP_RATE = GetInt(0, 2000, 2000,"ItemDropRates","ExcDropRate",RMSTItems);
	*(unsigned int*) GS_EXC_SKILL_RATE = GetInt(0, 100, 100,"ItemDropRates","ExcSkillDropRate",RMSTItems);
	*(unsigned int*) GS_EXC_LUCK_RATE = GetInt(0, 100, 1,"ItemDropRates","ExcLuckDropRate",RMSTItems);
	*(unsigned int*) GS_SKILL_RATE = GetInt(0, 100, 6,"ItemDropRates","NormalSkillDropRate",RMSTItems);
	*(unsigned int*) GS_LUCK_RATE = GetInt(0, 100, 4,"ItemDropRates","NormalLuckDropRate",RMSTItems);
	*(unsigned char*) GS_ANCREWARD_SKILL_RATE = GetChar(0, 100, 6,"ItemDropRates","AncientRewardSkillDropRate",RMSTItems);
	*(unsigned char*) GS_ANCREWARD_LUCK_RATE = GetChar(0, 100, 4,"ItemDropRates","AncientRewardLuckDropRate",RMSTItems);
	*(unsigned char*) GS_ANCRANDOM_SKILL_RATE = GetChar(0, 100, 6,"ItemDropRates","AncientRandomSkillDropRate",RMSTItems);
	*(unsigned char*) GS_ANCRANDOM_LUCK_RATE = GetChar(0, 100, 4,"ItemDropRates","AncientRandomLuckDropRate",RMSTItems);


	byte = GetChar(0, 20, 7,"LevelUpPoints","LevelUpPointsForDl",RMSTCommon);
	*(unsigned char*) GS_LVL_UP_DL1 = byte;
	*(unsigned char*) GS_LVL_UP_DL2 = byte;
	*(unsigned char*) GS_LVL_UP_DL3 = byte;
	*(unsigned char*) GS_LVL_UP_DL4 = byte;
	*(unsigned char*) GS_LVL_UP_DL5 = byte;

	byte = GetChar(0, 20, 7,"LevelUpPoints","LevelUpPointsForMg",RMSTCommon);
	*(unsigned char*) GS_LVL_UP_MG1 = byte;
	*(unsigned char*) GS_LVL_UP_MG2 = byte;
	*(unsigned char*) GS_LVL_UP_MG3 = byte;
	*(unsigned char*) GS_LVL_UP_MG4 = byte;
	*(unsigned char*) GS_LVL_UP_MG5 = byte;

	byte = GetChar(0, 20, 5,"LevelUpPoints","LevelUpPointsForDkElfDwSum",RMSTCommon);
	*(unsigned char*) GS_LVL_UP_NORMAL1 = byte;
	*(unsigned char*) GS_LVL_UP_NORMAL2 = byte;
	*(unsigned char*) GS_LVL_UP_NORMAL3 = byte;
	*(unsigned char*) GS_LVL_UP_NORMAL4 = byte;
	*(unsigned char*) GS_LVL_UP_NORMAL5 = byte;

	byte = GetChar(0, 5, 1,"LevelUpPoints","ExtraPointsAfterMarlonQuest",RMSTCommon);
	*(unsigned char*) GS_LVL_UP_QUEST1 = byte;
	*(unsigned char*) GS_LVL_UP_QUEST2 = byte;
	*(unsigned char*) GS_LVL_UP_QUEST3 = byte;
	*(unsigned char*) GS_LVL_UP_QUEST4 = byte;
	*(unsigned char*) GS_LVL_UP_QUEST5 = byte;

	*(unsigned char*) GS_ML_POINTS = GetChar(0, 20, 1,"LevelUpPoints","MasterlvlPoints",RMSTCommon);

	*(unsigned int *) GS_TWISTINGSLASH_USELV = GetInt(0,5000,80,"SkillLevel", "TwistingSlashMinLevel", RMSTSkills);
	*(unsigned int *) GS_RAGEFULBLOW_USELV = GetInt(0,5000,170,"SkillLevel", "RagefulBlowMinLevel", RMSTSkills);
	*(unsigned int *) GS_DEATHSTAB_USELV = GetInt(0,5000,160,"SkillLevel", "DeathStabMinLevel", RMSTSkills);
	*(unsigned int *) GS_IMPALE_USELV = GetInt(0,5000,25,"SkillLevel", "ImapleMinLevel", RMSTSkills) ;
	*(unsigned int *) GS_INNERSTRENGTH_USELV = GetInt(0,5000,120,"SkillLevel", "GreaterFortitudeMinLevel", RMSTSkills) ;
	*(unsigned int *) GS_PENETRATION_USELV = GetInt(0,5000,130,"SkillLevel", "PenetrationMinLevel", RMSTSkills) ;

	*(unsigned int *) GS_MSNORMAL01 = GetInt(0,10000,250,"ManaShield", "ManaShieldAgiNormal", RMSTSkills) ;
	*(unsigned int *) GS_MSNORMAL02 = GetInt(0,10000,200,"ManaShield", "ManaShieldEneNormal", RMSTSkills) ;
	*(unsigned int *) GS_MSMASTER01 = GetInt(0,10000,50,"ManaShield", "ManaShieldAgiMaster", RMSTSkills) ;
	*(unsigned int *) GS_MSMASTER02 = GetInt(0,10000,50,"ManaShield", "ManaShieldEneMaster", RMSTSkills) ; 

	*(unsigned int *) NormalManaShieldTime1 = GetInt(0,10000,40,"ManaShield", "ManaShieldTime", RMSTSkills) ;
	*(unsigned int *) MasterManaShieldTime2 = GetInt(0,10000,40,"ManaShield", "ManaShieldTimeMaster", RMSTSkills) ;


	dword =  GetInt(0,5000,150,"GreatFortitude", "GreatFortitudeVitNormal", RMSTSkills);
	*(unsigned int *) NormalGreatForitiuteVit01 = dword;
	*(unsigned int *) NormalGreatForitiuteVit02 = dword;
	*(unsigned int *) NormalGreatForitiuteVit03 = dword;
	*(unsigned int *) GS_GFNORMAL02 = GetInt(0,5000,100,"GreatFortitude", "GreatFortitudeEneNormal", RMSTSkills) ;

	dword =  GetInt(0,5000,150,"GreatFortitude", "GreatFortitudeVitMaster", RMSTSkills);
	*(unsigned int *) MasterGreatForitiuteVit01 = dword;
	*(unsigned int *) MasterGreatForitiuteVit02 = dword;
	*(unsigned int *) MasterGreatForitiuteVit03 = dword;
	*(unsigned int *) GS_GFMASTER02 = GetInt(0,5000,100,"GreatFortitude", "GreatFortitudeEneMaster", RMSTSkills) ;

	*(unsigned int *) NormalGreatForitiuteTime = GetInt(0,10000,10,"GreatFortitude", "GreatFortitudeTime", RMSTSkills) ;
	*(unsigned int *) MasterGreatForitiuteTime = GetInt(0,10000,10,"GreatFortitude", "GreatFortitudeMaster", RMSTSkills) ;


	*(unsigned int*) GS_BERSERKER_DIV1 = GetInt(0,5000,20,"Berserker","BerserkerDiv1",RMSTSkills);
	*(unsigned int*) GS_BERSERKER_DIV2 = GetInt(0,5000,30,"Berserker","BerserkerDiv2",RMSTSkills);
	*(unsigned int*) GS_BERSERKER_DIV3 = GetInt(0,5000,60,"Berserker","BerserkerDiv3",RMSTSkills);
	*(unsigned int*) GS_DAMAGEREF_DIV1 = GetInt(0,5000,42,"DamageRef","DamageRefDiv1",RMSTSkills);
	*(unsigned int*) GS_DAMAGEREF_DIV2 = GetInt(0,5000,25,"DamageRef","DamageRefDiv2",RMSTSkills);

	*(unsigned int*) GS_CRITICALDMG_COMMAND = GetInt(0,5000,25,"CriticalDmg","CriticalDmgLeaderShip",RMSTSkills);
	*(unsigned int*) GS_CRITICALDMG_ENERGY = GetInt(0,5000,30,"CriticalDmg","CriticalDmgEnergy",RMSTSkills);
	*(unsigned int*) GS_CRITICALDMG_TIME = GetInt(0,5000,10,"CriticalDmg","CriticalDmgTime",RMSTSkills);

	*(unsigned int*) MaxZen  = GetInt(0, 2000000000, 2000000000,"MaximumZen", "MaxZenInBag", RMSTCommon);

	dword = GetInt(0, 2000000000, 1000000000,"MaximumZen", "MaxZenInVault", RMSTCommon);
	*(unsigned int*) MaxZen1 = dword;
	*(unsigned int*) MaxZen2 = dword;
	*(unsigned int*) MaxZen3 = dword;

	*(unsigned int *) GS_PARTYEXP_2_NORMAL = GetInt(0,5000,160,"PartyExp","NormalParty2Exp",RMSTCommon);
	*(unsigned int *) GS_PARTYEXP_3_NORMAL = GetInt(0,5000,180,"PartyExp","NormalParty3Exp",RMSTCommon);
	*(unsigned int *) GS_PARTYEXP_4_NORMAL = GetInt(0,5000,200,"PartyExp","NormalParty4Exp",RMSTCommon);
	*(unsigned int *) GS_PARTYEXP_5_NORMAL = GetInt(0,5000,220,"PartyExp","NormalParty5Exp",RMSTCommon);
	*(unsigned int *) GS_PARTYEXP_3_SET = GetInt(0,5000,230,"PartyExp","SetParty3Exp",RMSTCommon);
	*(unsigned int *) GS_PARTYEXP_4_SET = GetInt(0,5000,270,"PartyExp","SetParty4Exp",RMSTCommon);
	*(unsigned int *) GS_PARTYEXP_5_SET  = GetInt(0,5000,300,"PartyExp","SetParty5Exp",RMSTCommon);
#ifdef GS90
	*(unsigned int*) GS_DS_PARTYEXP_2 = GetInt(0,5000,160,"DevilSquare","DevilSquarePartyExp2Players",RMSTEvents);
	*(unsigned int*) GS_DS_PARTYEXP_3 = GetInt(0,5000,180,"DevilSquare","DevilSquarePartyExp3Players",RMSTEvents);
	*(unsigned int*) GS_DS_PARTYEXP_4 = GetInt(0,5000,200,"DevilSquare","DevilSquarePartyExp4Players",RMSTEvents);
	*(unsigned int*) GS_DS_PARTYEXP_5 = GetInt(0,5000,220,"DevilSquare","DevilSquarePartyExp5Players",RMSTEvents);
	*(unsigned int*) GS_DS_PARTYDIFFEXP_3 = GetInt(0,5000,230,"DevilSquare","DevilSquareSetPartyExp3Players",RMSTEvents);
	*(unsigned int*) GS_DS_PARTYDIFFEXP_4 = GetInt(0,5000,270,"DevilSquare","DevilSquareSetPartyExp4Players",RMSTEvents);
	*(unsigned int*) GS_DS_PARTYDIFFEXP_5 = GetInt(0,5000,300,"DevilSquare","DevilSquareSetPartyExp5Players",RMSTEvents);
#endif
#ifdef GSCS90
	*(unsigned int*) GSCS_LOT_MAXPRICE = GetInt(0,1000000000,300000,"CastleSiege","CSLandOfTrialMaxPayment",RMSTEvents);
	*(unsigned char*) GSCS_LORDMIX_MAXUSE  = GetChar(0,5000,0,"CastleSiege","CSLordMixMaxUsePerDay",RMSTEvents);

	*(unsigned char*) GSCS_CRYWOLF_REWARD_ELF = GetChar(0,15,14,"CryWolf","CrywolfAltarElfRewardIndexID",RMSTEvents) * 512 + GetChar(0,255,13,"CryWolf","CrywolfAltarElfRewardGroupID",RMSTEvents);
	*(unsigned char*) GSCS_CRYWOLF_REWARD_TOP5 = GetChar(0,15,14,"CryWolf","CrywolfTop5RewardIndexID",RMSTEvents) * 512 + GetChar(0,255,13,"CryWolf","CrywolfTop5RewardGroupID",RMSTEvents);
	
	dword = GetInt(0,1000000000,200000000,"CastleSiege","CSSeniorMaxCash",RMSTEvents);
	*(unsigned int*) GSCS_SENIOR_MAXZEN1 = dword;
	*(unsigned int*) GSCS_SENIOR_MAXZEN2 = dword;
#endif 
}	
void cConfigs::LoadFixes()
{

	#ifdef GS90
	EldaradoEventType	= GetInt(0, 1, 0,"EldaradoEvent", "EldaradoEventType", RMSTEvents);
	CCAllowingPlayers	= GetInt(0, 2, 0,"ChaosCastle", "ChaosCastleAllowingPlayers", RMSTEvents);
	BCAllowingPlayers	= GetInt(0, 2, 0,"BloodCastle", "BloodCastleAllowingPlayers", RMSTEvents);
	BCEnterMasterType	= GetInt(0, 1, 0,"BloodCastle", "BloodCastleMasterEnterType", RMSTEvents);
	DSAllowingPlayers	= GetInt(0, 2, 0,"DevilSquare", "DevilSquareAllowingPlayers", RMSTEvents); 
	#endif

	UseChecksum		= GetInt(0, 1, 0, "CheckSum", "UseCheckSum", RMSTCommon);	  
	PersonalIDFix	= GetInt(0, 1, 1, "Bypasseres", "PersonalIDBypasser", RMSTCommon);
	GuildIDFix		= GetInt(0, 1, 1, "Bypasseres", "GuildIDBypasser", RMSTCommon);
	DisableLogs		= GetInt(0, 1, 0, "Logs", "DisableLogs", RMSTCommon);
	AllowExeAnc		= GetInt(0, 1, 1, "SpecialItem", "AllowExeAnc", RMSTItems);	
	AllowJohAnc		= GetInt(0, 1, 1, "SpecialItem", "AllowJohAnc", RMSTItems);
	AllowExeSock	= GetInt(0, 1, 1, "SpecialItem", "AllowExeSock", RMSTItems);
	MaxLifeOpt		= GetInt(0, 1, 1, "SpecialItem", "MaxLifeOpt", RMSTItems);
	Use65kStats		= GetInt(0, 1, 0, "AddCommand", "Enable65kStats", RMSTCmd);  
	CSSkillsOnNOrmal = GetInt(0, 1, 1, "Skills", "CSSkillsOnNOrmal", RMSTSkills);    
	Enable65kStats	= GetInt(0, 1, 0, "AddCommand",	"Enable65kStats", RMSTCmd);	
	DumpFile		= GetInt(0, 1, 0, "Dump", "EnableCrashDump",RMSTCommon);
}

void cConfigs::LoadAntiAfk()
{		  			  
	AntiAfkConfig.Enabled	= GetInt(0, 1,		1,		"AntiAFK",		"AntiAFKEnabled",		RMSTAntiAFK);  
	if(!AntiAfkConfig.Enabled)
		return;
	AntiAfkConfig.Time		= GetInt(0, 32000,	300,	"AntiAFK",		"AntiAFKTimer",			RMSTAntiAFK);
	AntiAfkConfig.Warnings	= GetInt(0, 5,		3,		"AntiAFK",		"AntiAFKWarnings",		RMSTAntiAFK);	  
	AntiAFK.Load();
}

void cConfigs::LoadArcher()
{		  		 
	Archer.Enabled				= GetInt(0, 1,						1,		"GoldenArcher",	"ArcherEnabled",		RMSTArcher);	
	
	if(Archer.Enabled)
	{	
		Archer.NeedRenaAmount	= GetInt(0, 250,								7,		"GoldenArcher", "RenasCount",			RMSTArcher); 	   
		Archer.WCoinsReward		= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	1,		"GoldenArcher", "WCoinsReward",			RMSTArcher);
		Archer.PCPointsReward	= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	1,		"GoldenArcher", "PCPointsReward",		RMSTArcher);	   
		Archer.ZenReward		= GetInt(0, 2000000000,							100000, "GoldenArcher", "ZenReward",			RMSTArcher);
		GoldenArcher.LoadPrizeItems();
	}
}

void cConfigs::LoadCommands()
{	
	Commands.MaxLvl						= GetInt(300, 1000, 400,"LevelSettings", "MaxLevel", RMSTCommon);
	//		drop		//
	Commands.IsDrop						= GetInt(0,	1,					1,		"Drop",			"DropEnabled",					RMSTCmd);

	//		Reload		//
	Commands.IsReload					= GetInt(0,	1,					1,		"Reload",			"ReloadEnabled",					RMSTCmd);

	//		gmove		//
	Commands.IsGmove					= GetInt(0,	1,					1,		"Gmove",		"GmoveEnabled",					RMSTCmd);	 

	//		setpk
	Commands.IsSetPK					= GetInt(0, 1,					1,		"SetPK",		"SetPKEnabled",					RMSTCmd);  
	
	//		setzen
	Commands.IsSetZen					= GetInt(0, 1,					1,		"SetZen",		"SetZenEnabled",				RMSTCmd); 

	//		gg			//																	 	
	Commands.IsGg						= GetInt(0, 1,					1,		"GPost",		"GgEnabled",					RMSTCmd);	

	//		time		//
	Commands.IsTime						= GetInt(0, 1,					1,		"Time",			"TimeEnabled",					RMSTCmd);  

	//		online		//
	Commands.IsOnline					= GetInt(0, 1,					1,		"OnlineCommand","OnlineEnabled",				RMSTCmd); 

	//		status		//
	Commands.IsStatus					= GetInt(0, 1,					1,		"Status",		"StatusEnabled",				RMSTCmd); 

	//		SetChar		//
	Commands.IsSetChar					= GetInt(0, 1,					1,		"SetChar",		"SetCharEnabled",				RMSTCmd);
	//		bans		//
	Commands.IsBanPost					= GetInt(0, 1,					1,		"Bans",			"BanPostEnabled",				RMSTCmd);	
	Commands.IsBanChar					= GetInt(0, 1,					1,		"Bans",			"BanCharEnabled",				RMSTCmd);	
	Commands.IsBanAcc					= GetInt(0, 1,					1,		"Bans",			"BanAccEnabled",				RMSTCmd);  	\

	//		skin		//
	Commands.SkinEnabled				= GetInt(0, 1,									1,		"Skin",			"SkinEnabled",					RMSTCmd);
	Commands.SkinOnlyForGm				= GetInt(0, 1,									0,		"Skin",			"SkinOnlyForGm",				RMSTCmd);
	Commands.SkinLevelReq				= GetInt(0, Commands.MaxLvl,					250,	"Skin",			"SkinLevelReq",					RMSTCmd);
	Commands.SkinPriceZen				= GetInt(0, 2000000000,							100000,	"Skin",			"SkinPriceZen",					RMSTCmd);
	Commands.SkinPricePcPoint			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	1,		"Skin",			"SkinPricePcPoint",				RMSTCmd);
	Commands.SkinPriceWCoin				= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	1,		"Skin",			"SkinPriceWCoin",				RMSTCmd);	

	//		post		//	 
	Commands.IsPost						= GetInt(0, 1,									1,		"Post",			"PostEnabled",					RMSTCmd); 
	Commands.PostLvl					= GetInt(0, Commands.MaxLvl,					1,		"Post",			"PostLevelReq",					RMSTCmd);				  
	Commands.PostPriceZen				= GetInt(0, 2000000000,							10000,	"Post",			"PostPriceZen",					RMSTCmd);		 
	Commands.PostPricePCPoint			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	0,		"Post",			"PostPricePcPoint",				RMSTCmd);	 
	Commands.PostPriceWCoin				= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	0,		"Post",			"PostPriceWCoin",				RMSTCmd);												
	Commands.PostColor					= GetInt(1, 3,									1,		"Post",			"PostColor",					RMSTCmd);  

	//		add			//
	Commands.AddPointEnabled			= GetInt(0, 1,									1,		"AddCommand",	"AddPointEnabled",				RMSTCmd);
	Commands.AddPointLevelReq			= GetInt(0, Commands.MaxLvl,					0,		"AddCommand",	"AddPointLevelReq",				RMSTCmd);			   	
	Commands.AddPriceZen				= GetInt(0, 2000000000,							10000,	"AddCommand",	"AddPriceZen",					RMSTCmd);		 
	Commands.AddPricePCPoint			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	0,		"AddCommand",	"AddPricePCPoint",				RMSTCmd);	 
	Commands.AddPriceWCoin				= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	0,		"AddCommand",	"AddPriceWCoin",				RMSTCmd);	 
	Commands.MaxAddedStats				= GetInt(0, 65000,								0,		"AddCommand",	"MaxAddedStats",				RMSTCmd);

	//		ware		//
	Commands.IsMultyVault				= GetInt(0,	1,									1,		"MultyVault",	"IsMultyVault",					RMSTCmd);  
	Commands.NumberOfVaults				= GetInt(2,	99,									3,		"MultyVault",	"NumberOfVaults",				RMSTCmd); 
	Commands.ZenForChange				= GetInt(0,	2000000000,							10000,	"MultyVault",	"ZenForChange",					RMSTCmd);
	Commands.PcPointForChange			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	0,		"MultyVault",	"PcPointForChange",				RMSTCmd);
	Commands.WCoinForChange				= GetInt(0,	PCPoint.sPoints.MaximumWCPoints,	0,		"MultyVault",	"WCoinForChange",				RMSTCmd);

	//		pkclear		//	
	ClearCommand.Enabled				= GetInt(0, 1,									1,		"PkClear",		"PkClearEnabled",				RMSTCmd);
	ClearCommand.OnlyForGm				= GetInt(0, 1,									0,		"PkClear",		"PkClearOnlyForGm",				RMSTCmd);
	ClearCommand.Type					= GetInt(0, 2,									1,		"PkClear",		"PKClearType",					RMSTCmd);	 																													
	ClearCommand.PriceZen				= GetInt(0, 2000000000,							100000, "PkClear",		"PkClearPriceZen",				RMSTCmd);	 
	ClearCommand.PriceZenForAll			= GetInt(0, 2000000000,							1000000,"PkClear",		"PkClearPriceZenForAll",		RMSTCmd);
	ClearCommand.PricePcPoints			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	20,		"PkClear",		"PkClearPricePcPoints",			RMSTCmd);	 
	ClearCommand.PricePcPointsForAll	= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	200,	"PkClear",		"PkClearPricePcPointsForAll",	RMSTCmd);
	ClearCommand.PriceWCoins			= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	2,		"PkClear",		"PkClearPriceWCoins",			RMSTCmd);	 
	ClearCommand.PriceWCoinsForAll		= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	20,		"PkClear",		"PkClearPriceWCoinsForAll",		RMSTCmd);
	ClearCommand.LevelReq				= GetInt(0, Commands.MaxLvl,					100,	"PkClear",		"PkClearLevelReq",				RMSTCmd);  
}

void cConfigs::LoadPkClearGuard()
{						  
	ClearNpc.Enabled				= GetInt(0, 1,					1,		"PkClearGuard",		"LoadPkGuard",						RMSTPkClear);
	if(!ClearNpc.Enabled)
		return;

	ClearNpc.NpcId					= GetInt(0, 32000,								249,	"PkClearGuard",		"PkClearGuardId",					RMSTPkClear);	   				 
	ClearNpc.Type					= GetInt(0, 2,									1,		"PkClearGuard",		"PKClearGuardType",					RMSTPkClear);																															
	ClearNpc.PriceZen				= GetInt(0, 2000000000,							100000,	"PkClearGuard",		"PkClearGuardPriceZen",				RMSTPkClear);	 
	ClearNpc.PriceZenForAll			= GetInt(0, 2000000000,							1000000,"PkClearGuard",		"PkClearGuardPriceZenForAll",		RMSTPkClear);
	ClearNpc.PricePcPoints			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	20,		"PkClearGuard",		"PkClearGuardPricePcPoints",		RMSTPkClear);	 
	ClearNpc.PricePcPointsForAll	= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	200,	"PkClearGuard",		"PkClearGuardPricePcPointsForAll",	RMSTPkClear);	
	ClearNpc.PriceWCoins			= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	2,		"PkClearGuard",		"PkClearGuardPriceWCoins",			RMSTPkClear);	 
	ClearNpc.PriceWCoinsForAll		= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	20,		"PkClearGuard",		"PkClearGuardPriceWCoinsForAll",	RMSTPkClear);	   
	ClearNpc.LevelReq				= GetInt(0, 400,								100,	"PkClearGuard",		"PkClearGuardLevelReq",				RMSTPkClear);
}	   

void cConfigs::LoadAll()
{
	PCPoint.LoadIniConfigs();
	ZenFixes();
	PartyZenFixes();
	LoadGmSystem();
	LoadAntiAfk();
	LoadDuel();
	LoadNotice();
	LoadArcher();
	LoadNews(); 
	LoadCommands();
	LoadPkClearGuard();
	DropSystem.LoadDropItems();
#ifdef GS90
	moss.LoadMoss();
#endif
		
	//
	GuildRes				= GetInt(0, 32767, 5,"GuildMaster", "GuildCreateReset", RMSTCommon);
	GuildLevel				= GetInt(0, 400, 320,"GameServerInfo", "GuildCreateLevel", "..\\Data\\CommonServer.cfg");
	//
}

long cConfigs::GetInt(long Min, long Max, long Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FolderName)
{
	long lResult;
	char Message[250];
	char Message2[50];

	WIN32_FIND_DATAA wfd;
	if (FindFirstFileA(FolderName, &wfd) == INVALID_HANDLE_VALUE)
	{				
		wsprintf(Message,"Can't find file!\nTaked default value for %s(%ld)", ConfigName, Default);
		wsprintf(Message2,"Error configs in %s!", FolderName); 
			Log.ConsoleOutPut(0, c_Red, t_Error, "%s, \n %s \n \n", Message, Message2);
		lResult = Default;
	}
	else
		lResult = GetPrivateProfileInt(BlockName, ConfigName, -100500, FolderName);

	if(lResult == -100500)
	{	   
		wsprintf(Message,"Can't find '%s' in [%s] section!\nTaked default value for %s(%ld)", ConfigName, BlockName, ConfigName, Default);
		wsprintf(Message2,"Error configs in %s!", FolderName); 
			Log.ConsoleOutPut(0, c_Red, t_Error, "%s, \n %s", Message, Message2);
		lResult = Default;
	}

	if(lResult < Min || lResult > Max)
	{
		wsprintf(Message,"%s(%d) in [%s] is out of range!\nMin = %ld\t\tMax = %ld\nTaked default value(%ld)", ConfigName, lResult, BlockName, Min, Max, Default);
		wsprintf(Message2,"Error configs in %s!", FolderName); 
			Log.ConsoleOutPut(0, c_Red, t_Error, "%s, \n %s \n \n", Message, Message2);
		lResult = Default;
	} 
	return lResult;
}

char cConfigs::GetChar(long Min, long Max, unsigned char Default, LPCSTR BlockName, LPCSTR ConfigName, LPCSTR FolderName)
{
	unsigned char cResult;
	char Message[250];
	char Message2[50];

	WIN32_FIND_DATAA wfd;
	if (FindFirstFileA(FolderName, &wfd) == INVALID_HANDLE_VALUE)
	{				
		wsprintf(Message,"Can't find file!\nTaked default value for %s(%ld)", ConfigName, Default);
		wsprintf(Message2,"Error configs in %s!", FolderName); 
			Log.ConsoleOutPut(0, c_Red, t_Error, "%s, \n %s \n \n", Message, Message2);
		cResult = Default;
	}
	else
		cResult = GetPrivateProfileInt(BlockName, ConfigName, -100500, FolderName);

	if(cResult == -100500)
	{	   
		wsprintf(Message,"Can't find '%s' in [%s] section!\nTaked default value for %s(%ld)", ConfigName, BlockName, ConfigName, Default);
		wsprintf(Message2,"Error configs in %s!", FolderName); 
		Log.ConsoleOutPut(0, c_Red, t_Error, "%s, \n %s \n \n", Message, Message2);
		cResult = Default;
	}

	if(cResult < Min || cResult > Max)
	{
		wsprintf(Message,"%s(%d) in [%s] is out of range!\nMin = %ld\t\tMax = %ld\nTaked default value(%ld)", ConfigName, cResult, BlockName, Min, Max, Default);
		wsprintf(Message2,"Error configs in %s!", FolderName); 
		Log.ConsoleOutPut(0, c_Red, t_Error, "%s, \n %s \n \n", Message, Message2);
		cResult = Default;
	}
	return cResult;
}