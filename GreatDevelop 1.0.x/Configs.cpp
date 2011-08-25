// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.1								# //
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
	GmSystemConfig.IsGMSystem	= GetInt(0, 1, 0, "GMSystem", "IsGMSystem",	GreatDevelopGM);		
	if(!GmSystemConfig.IsGMSystem)return;
	GmSystemConfig.IsGMInDB	= GetInt(0, 1, 0, "GMSystem", "IsGMInDB",	GreatDevelopGM);
	GmSystem.Load();
} 


void cConfigs::LoadNews()
{
	IsNews						= GetInt(0, 1,					1,		"News",			"NewsSystemEnabled",			GreatDevelopNews);
	if(!IsNews)return;
	_beginthread(NewsSystem, 0, NULL);
}

void cConfigs::ZenFixes()
{
	Zen.Enabled						= GetInt(0, 1,					1,		"ZenSettings",	"NewFormulaEnabled",			GreatDevelopCommon);
	if(!Zen.Enabled)return;
	Zen.MasterZen					= GetInt(0, 65535,				20,		"ZenSettings",	"AddZen_ML",			GreatDevelopCommon);
	Zen.NormalZen					= GetInt(0, 65535,				20,		"ZenSettings",	"AddZen_Normal",		GreatDevelopCommon);
	Zen.MasterDivisor				= GetInt(0, 65535,				20,		"ZenSettings",	"Zen_MasterDivisor",	GreatDevelopCommon);
	Zen.NormalDivisor				= GetInt(0, 65535,				20,		"ZenSettings",	"Zen_NormalDivisor",	GreatDevelopCommon);
}

void cConfigs::PartyZenFixes()
{
	PartyZen.Enabled					= GetInt(0, 1,					1,		"PartyZenSettings",	"NewFormulaEnabled",	GreatDevelopCommon);
	if(!PartyZen.Enabled)return;
	PartyZen.MasterZen					= GetInt(0, 65535,				20,		"PartyZenSettings",	"AddZen_ML",			GreatDevelopCommon);
	PartyZen.NormalZen					= GetInt(0, 65535,				20,		"PartyZenSettings",	"AddZen_Normal",		GreatDevelopCommon);
	PartyZen.MasterDivisor				= GetInt(0, 65535,				20,		"PartyZenSettings",	"Zen_MasterDivisor",	GreatDevelopCommon);
	PartyZen.NormalDivisor				= GetInt(0, 65535,				20,		"PartyZenSettings",	"Zen_NormalDivisor",	GreatDevelopCommon);
}

void cConfigs::LoadPets()
{		  																									   
	Panda.PetPandaDefense				= GetInt(0, 1000,			10,		"Panda",		"PetPandaDefense",				GreatDevelopPets);
	Panda.PetPandaAttackDamageMinLeft	= GetInt(0, 1000,			10,		"Panda",		"PetPandaAttackDamageMinLeft",	GreatDevelopPets);
	Panda.PetPandaAttackDamageMaxLeft	= GetInt(0, 1000,			10,		"Panda",		"PetPandaAttackDamageMaxLeft",	GreatDevelopPets);
	Panda.PetPandaAttackDamageMinRight	= GetInt(0, 1000,			10,		"Panda",		"PetPandaAttackDamageMinRight",	GreatDevelopPets);
	Panda.PetPandaAttackDamageMaxRight	= GetInt(0, 1000,			10,		"Panda",		"PetPandaAttackDamageMaxRight",	GreatDevelopPets);
	Panda.PetPandaMagicDamageMin		= GetInt(0, 1000,			10,		"Panda",		"PetPandaMagicDamageMin",		GreatDevelopPets);
	Panda.PetPandaMagicDamageMax		= GetInt(0, 1000,			10,		"Panda",		"PetPandaMagicDamageMax",		GreatDevelopPets);
	Panda.PetPandaMagicSpeed			= GetInt(0, 1000,			10,		"Panda",		"PetPandaMagicSpeed",			GreatDevelopPets);
	Panda.PetPandaAttackSpeed			= GetInt(0, 1000,			10,		"Panda",		"PetPandaAttackSpeed",			GreatDevelopPets);

	Panda.PandaRingDefense				= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingDefense",				GreatDevelopPets);
	Panda.PandaRingAttackDamageMinLeft	= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingAttackDamageMinLeft",	GreatDevelopPets);
	Panda.PandaRingAttackDamageMaxLeft	= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingAttackDamageMaxLeft",	GreatDevelopPets);
	Panda.PandaRingAttackDamageMinRight	= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingAttackDamageMinRight",GreatDevelopPets);
	Panda.PandaRingAttackDamageMaxRight	= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingAttackDamageMaxRight",GreatDevelopPets);
	Panda.PandaRingMagicDamageMin		= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingMagicDamageMin",		GreatDevelopPets);
	Panda.PandaRingMagicDamageMax		= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingMagicDamageMax",		GreatDevelopPets);
	Panda.PandaRingMagicSpeed			= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingMagicSpeed",			GreatDevelopPets);
	Panda.PandaRingAttackSpeed			= GetInt(0, 1000,			10,		"PandaRing",	"PandaRingAttackSpeed",			GreatDevelopPets);
																										  
	Panda.PetPandaExpirence				= GetInt(0, 10000,			100,	"Panda",		"PetPandaExpirence",			GreatDevelopPets);
	Panda.PetPandaMLExpirence			= GetInt(0, 10000,			100,	"Panda",		"PetPandaMLExpirence",			GreatDevelopPets);

	Panda.PandaRingExpirence			= GetInt(0, 10000,			100,	"PandaRing",	"PandaRingExpirence",			GreatDevelopPets);
	Panda.PandaRingMLExpirence			= GetInt(0, 10000,			100,	"PandaRing",	"PandaRingMLExpirence",			GreatDevelopPets);
}

void cConfigs::LoadNotice()
{	
	ConnectInfo					= GetInt(0, 1,					1,		"Connect",		"ConnectInfo",					GreatDevelopGS);
	GetPrivateProfileString("Connect","ConnectNotice","Powered by GreatDevelop 1.0.1",ConnectNotice,sizeof(ConnectNotice),GreatDevelopGS); 
} 

void cConfigs::LoadDuel()
{		  			   
	Duel.Enabled					= GetInt(0, 1,					1,		"DuelManager",	"DuelEnabled",					GreatDevelopCommon);  
	if(!Duel.Enabled)return;
	Duel.Ranking					= GetInt(0, 1,					0,		"DuelManager",	"DuelRanking",					GreatDevelopCommon);
	Duel.Logging					= GetInt(0, 1,					1,		"DuelManager",	"DuelLogging",					GreatDevelopCommon);
}

void cConfigs::LoadConfigsInGS()
{								  	 

	#ifdef _GS
	DWORD *LoreGuard = (DWORD*)GUARD_SAY;
	char Lore[25];
	GetPrivateProfileString("Connect","GuardSay","Don't waste my time!",Lore,25,GreatDevelopGS);
	memset(&LoreGuard[0],0,25);
	memcpy(&LoreGuard[0],Lore,strlen(Lore));
	#endif

	DWORD dword;
	BYTE byte;

	dword = GetInt(300, 1000, 400,"LevelSettings", "MaxLevel", GreatDevelopCommon);
	*(unsigned int*) GS_MAX_LEVEL1 = dword;
	*(unsigned int*) GS_MAX_LEVEL2 = dword;
	*(unsigned int*) GS_MAX_LEVEL3 = dword;
	*(unsigned int*) GS_MAX_LEVEL4 = dword;
	*(unsigned int*) GS_MAX_LEVEL5 = dword;

	*(unsigned int*) GS_NOEXP_LEVEL = GetInt(401, 1001, 401,"LevelSettings", "MaxXPLevel", GreatDevelopCommon);
	*(unsigned int*) GS_MAX_MASTERLEVEL = GetInt(1, 400, 200,"LevelSettings", "MaxMasterLevel", GreatDevelopCommon);

	dword = GetInt(0, 360, 120,"ItemDropRates", "LootingTime", GreatDevelopItems);
	*(unsigned int*) GS_ITEM_TIME1 =	1000 * dword;
	*(unsigned int*) GS_ITEM_TIME2 =	1000 * dword;

	*(unsigned int*) GS_TRANSFORMATIONRING1 = GetInt(0, 600, 2,"TransformationRings","TransformRing1",GreatDevelopItems);
	*(unsigned int*) GS_TRANSFORMATIONRING2 = GetInt(0, 600, 7,"TransformationRings","TransformRing2",GreatDevelopItems);
	*(unsigned int*) GS_TRANSFORMATIONRING3 = GetInt(0, 600, 14,"TransformationRings","TransformRing3",GreatDevelopItems);
	*(unsigned int*) GS_TRANSFORMATIONRING4 = GetInt(0, 600, 8,"TransformationRings","TransformRing4",GreatDevelopItems);
	*(unsigned int*) GS_TRANSFORMATIONRING5 = GetInt(0, 600, 9,"TransformationRings","TransformRing5",GreatDevelopItems);
	*(unsigned int*) GS_TRANSFORMATIONRING6 = GetInt(0, 600, 41,"TransformationRings","TransformRing6",GreatDevelopItems);

	*(unsigned char*) GS_SUMMONORB1 = GetChar(0, 600, 26,"SummonOrbs","OrbSummon1",GreatDevelopItems);
	*(unsigned char*) GS_SUMMONORB2 = GetChar(0, 600, 32,"SummonOrbs","OrbSummon2",GreatDevelopItems);
	*(unsigned char*) GS_SUMMONORB3 = GetChar(0, 600, 21,"SummonOrbs","OrbSummon3",GreatDevelopItems);
	*(unsigned char*) GS_SUMMONORB4 = GetChar(0, 600, 20,"SummonOrbs","OrbSummon4",GreatDevelopItems);
	*(unsigned char*) GS_SUMMONORB5 = GetChar(0, 600, 10,"SummonOrbs","OrbSummon5",GreatDevelopItems);
	*(unsigned char*) GS_SUMMONORB6 = GetChar(0, 600, 150,"SummonOrbs","OrbSummon6",GreatDevelopItems);
	*(unsigned char*) GS_SUMMONORB7 =  GetChar(0, 600, 151,"SummonOrbs","OrbSummon7",GreatDevelopItems);

	
	*(unsigned int*) GS_BLESS_PRICE = GetInt(0, 2000000000, 6000000,"JewelPrices","JewelOfBlessPrice",GreatDevelopItems);
 	*(unsigned int*) GS_SOUL_PRICE = GetInt(0, 2000000000, 9000000,"JewelPrices","JewelOfSoulPrice",GreatDevelopItems);
	*(unsigned int*) GS_CHAOS_PRICE = GetInt(0, 2000000000, 810000,"JewelPrices","JewelOfChaosPrice",GreatDevelopItems);
	*(unsigned int*) GS_LIFE_PRICE =  GetInt(0, 2000000000, 45000000,"JewelPrices","JewelOfLifePrice",GreatDevelopItems);
	*(unsigned int*) GS_CREATION_PRICE = GetInt(0, 2000000000, 36000000,"JewelPrices","JewelOfCreationPrice",GreatDevelopItems);
	*(unsigned int*) GS_GUARDIAN_PRICE = GetInt(0, 2000000000, 60000000,"JewelPrices","JewelOfGuardianPrice",GreatDevelopItems);
	*(unsigned int*) GS_FRUITS_PRICE = GetInt(0, 2000000000, 33000000,"JewelPrices","FruitPrice",GreatDevelopItems);
	*(unsigned int*) GS_MONARCH_PRICE = GetInt(0, 2000000000, 750000,"JewelPrices","CrestOfMonarchPrice",GreatDevelopItems);
	*(unsigned int*) GS_FEATHER_PRICE = GetInt(0, 2000000000, 180000,"JewelPrices","LochsFeatherPrice",GreatDevelopItems);
	*(unsigned int*) GS_BLESSPOT_PRICE = GetInt(0, 2000000000, 900000,"JewelPrices","PotionOfBlessPrice",GreatDevelopItems);
	*(unsigned int*) GS_SOULPOT_PRICE = GetInt(0, 2000000000, 450000,"JewelPrices","PotionOfSoulPrice",GreatDevelopItems);
#ifdef _GS
	*(unsigned int*) GS_KUNDUN_ANC_PERCT = GetInt(0,10000,25,"Kundun","KundunDropAncRate",GreatDevelopItems);
	*(unsigned char*) GS_KUNDUN_ITEM_NUMB = GetChar(0,20,3,"Kundun","KundunDropItemCount",GreatDevelopItems);

	*(unsigned char*) GS_CCPLAYER = GetChar(0,20,2,"ChaosCastle","ChaosCastleMinPlayers",GreatDevelopEvents);
	
	*(unsigned char*) GS_CCREWARD1 = GetChar(0,15,14,"ChaosCastle","ChaosCastleRewardType1IndexID",GreatDevelopEvents) * 512 + GetChar(0,255,16,"ChaosCastle","ChaosCastleRewardType1GroupID",GreatDevelopEvents);
	*(unsigned char*) GS_CCREWARD2 = GetChar(0,15,14,"ChaosCastle","ChaosCastleRewardType1IndexID",GreatDevelopEvents) * 512 + GetChar(0,255,13,"ChaosCastle","ChaosCastleRewardType1GroupID",GreatDevelopEvents);
	*(unsigned char*) GS_CCREWARD3 = GetChar(0,15,14,"ChaosCastle","ChaosCastleRewardType1IndexID",GreatDevelopEvents) * 512 + GetChar(0,255,22,"ChaosCastle","ChaosCastleRewardType1GroupID",GreatDevelopEvents);
	*(unsigned char*) GS_CCREWARD4 = GetChar(0,15,14,"ChaosCastle","ChaosCastleRewardType1IndexID",GreatDevelopEvents) * 512 + GetChar(0,255,14,"ChaosCastle","ChaosCastleRewardType1GroupID",GreatDevelopEvents); 
	

	*(unsigned char*) GS_ITPLAYER = GetChar(0,20,4,"IllusionTemple","ItMinPlayers",GreatDevelopEvents);
	
	*(unsigned char*) GS_IT_DROP_ID = GetChar(0,15,15,"IllusionTemple","ItDropID",GreatDevelopEvents);
	*(unsigned char*) GS_IT_GROUP_ID = GetChar(0,255,12,"IllusionTemple","ItDropGroup",GreatDevelopEvents);
	*(unsigned char*) GS_IT_ITEM_LVL = GetChar(0,15,0,"IllusionTemple","ItDropLevel",GreatDevelopEvents);
	*(unsigned char*) GS_IT_ITEM_SKL =  GetChar(0,1,0,"IllusionTemple","ItDropWithSkill",GreatDevelopEvents);
	*(unsigned char*) GS_IT_ITEM_LCK = GetChar(0,1,0,"IllusionTemple","ItDropWithLuck",GreatDevelopEvents);
	*(unsigned char*) GS_IT_ITEM_LIF = GetChar(0,7,0,"IllusionTemple","ItDropLifeAdd",GreatDevelopEvents);
	*(unsigned char*) GS_IT_ITEM_EXC = GetChar(0,63,0,"IllusionTemple","ItDropExcOpt",GreatDevelopEvents);
	*(unsigned char*) GS_IT_ITEM_ANC = GetChar(0,255,0,"IllusionTemple","ItDropAncOpt",GreatDevelopEvents);

	*(unsigned char *) GS_BC_DROP_ID = GetChar(0,15,15,"BloodCastle","BcDropID",GreatDevelopEvents);
	*(unsigned char *) GS_BC_DROP_GROUP = GetChar(0,255,12,"BloodCastle","BcDropGroup",GreatDevelopEvents);
	*(unsigned char *) GS_BC_ITEM_LVL = GetChar(0,15,0,"BloodCastle","BcDropLevel",GreatDevelopEvents);
	*(unsigned char *) GS_BC_ITEM_SKL = GetChar(0,1,0,"BloodCastle","BcDropWithSkill",GreatDevelopEvents);
	*(unsigned char *) GS_BC_ITEM_LCK = GetChar(0,1,0,"BloodCastle","BcDropWithLuck",GreatDevelopEvents);
	*(unsigned char *) GS_BC_ITEM_LIF = GetChar(0,7,0,"BloodCastle","BcDropLifeAdd",GreatDevelopEvents);
	*(unsigned char *) GS_BC_ITEM_EXC = GetChar(0,63,0,"BloodCastle","BcDropExcOpt",GreatDevelopEvents);
	*(unsigned char *) GS_BC_ITEM_ANC = GetChar(0,255,0,"BloodCastle","BcDropAncOpt",GreatDevelopEvents);

	*(unsigned char *) GS_WW_DROP_ID = GetChar(0,15,13,"WhiteWizard","WizardDropItemID",GreatDevelopEvents);
	*(unsigned char *) GS_WW_GROUP_ID = GetChar(0,255,20,"WhiteWizard","WizardDropGroup",GreatDevelopEvents);
	*(unsigned char *) GS_WW_ITEM_LVL = GetChar(0,15,0,"WhiteWizard","WizardDropLevel",GreatDevelopEvents);
	*(unsigned char *) GS_WW_ITEM_SKL = GetChar(0,1,0,"WhiteWizard","WizardDropWithSkill",GreatDevelopEvents);
	*(unsigned char *) GS_WW_ITEM_LCK = GetChar(0,1,0,"WhiteWizard","WizardDropWithLuck",GreatDevelopEvents);
	*(unsigned char *) GS_WW_ITEM_LIF = GetChar(0,7,0,"WhiteWizard","WizardDropLifeAdd",GreatDevelopEvents);
	*(unsigned char *) GS_WW_ITEM_EXC = GetChar(0,63,0,"WhiteWizard","WizardDropExcOpt",GreatDevelopEvents);
	*(unsigned char *) GS_WW_ITEM_ANC = GetChar(0,255,0,"WhiteWizard","WizardDropAncOpt",GreatDevelopEvents);
	
#endif
	*(unsigned char*) GS_GUILDALLIANCE = GetChar(0,50,20,"Guild","GuildAllianceMinPlayers",GreatDevelopCommon);

	*(unsigned char*) GS_PKBugLimitFix1 = GetChar(0, 1000, 20,"PKOptions", "PKKillLimit", GreatDevelopCommon);
    *(unsigned char*) GS_PKBugLimitFix2 = GetChar(0, 1000, 20,"PKOptions", "PKKillLimit", GreatDevelopCommon);
    *(unsigned char*) GS_PKBugLimitFix3 = GetChar(0, 1000, 20,"PKOptions", "PKKillLimit", GreatDevelopCommon);

	*(unsigned int*) GS_UDP_PORT = GetInt(0, 99999, 60006,"Connect","UDP-Port",GreatDevelopGS);

	*(unsigned char*) GS_SOUL_RATE_NORMAL = GetChar(0,100,60,"JewelRates","SoulSuccessRateNormal",GreatDevelopItems);
	*(unsigned char*) GS_SOUL_RATE_SPECIAL = GetChar(0,100,50,"JewelRates","SoulSuccessRateSpecial",GreatDevelopItems);
	*(unsigned char*) GS_SOUL_RATE_SOCKET = GetChar(0,100,40,"JewelRates","SoulSuccessRateSocket",GreatDevelopItems);
	*(unsigned char*) GS_SOUL_LUCK_ADD = GetChar(0,100,20,"JewelRates","SoulSuccessRateLuck",GreatDevelopItems);
	*(unsigned char*) GS_JOL_FAIL_RATE = GetChar(0,100,50,"JewelRates","LifeFailRate",GreatDevelopItems);

	byte = GetChar(0, 100, 60,"ChaosMachineMixes", "ChaosMix10Rate", GreatDevelopItems);
	*(unsigned char*)  GS_CM_MIX_10_NORMAL = byte;
	*(unsigned char*)  GS_CM_MIX_10_SPECIAL = byte;
	*(unsigned char*)  GS_CM_MIX_10_SOCKET = byte;
	byte = GetChar(0, 100, 50,"ChaosMachineMixes", "ChaosMix11_12Rate", GreatDevelopItems);
	*(unsigned char*)  GS_CM_MIX_11_12_NORMAL = byte;
	*(unsigned char*)  GS_CM_MIX_11_12_SPECIAL = byte;
	*(unsigned char*)  GS_CM_MIX_11_12_SOCKET = byte;
	byte = GetChar(0, 100, 40,"ChaosMachineMixes", "ChaosMix13Rate", GreatDevelopItems);
	*(unsigned char*)  GS_CM_MIX_13_NORMAL = byte;
	*(unsigned char*)  GS_CM_MIX_13_SPECIAL = byte;
	*(unsigned char*)  GS_CM_MIX_13_SOCKET = byte;
	byte = GetChar(0, 100, 75,"ChaosMachineMixes", "ChaosMixWithLuck", GreatDevelopItems);
	*(unsigned char*) GS_CM_MIX_10_LUCK = byte;
	*(unsigned char*) GS_CM_MIX_11_13_LUCK = byte;
	*(unsigned char*) GS_CM_MIX_LUCK_ADD = GetChar(0, 100, 20,"ChaosMachineMixes","ChaosMixRateIncreaseWithLuck",GreatDevelopItems);
	*(unsigned char*) DEFAULTMIXRATE = GetChar(0, 100, 45,"ChaosMachineMixes","ChaosMixDefaultRate",GreatDevelopItems);
	*(unsigned char*) GS_WINGLVL1MIX = GetChar(0, 100, 90,"ChaosMachineMixes","WingMixLvl1SuccessRate",GreatDevelopItems);
	*(unsigned char*) GS_WINGLVL2MIX = GetChar(0, 100, 90,"ChaosMachineMixes","WingMixLvl2SuccessRate",GreatDevelopItems);
	byte = GetChar(0, 100, 60,"ChaosMachineMixes","CondorMixSuccessRate",GreatDevelopItems);
	*(unsigned char *) GS_WINGLVL3MIX11 = byte;
	*(unsigned char *) GS_WINGLVL3MIX12 = byte;
	byte = GetChar(0, 100, 40,"ChaosMachineMixes","WingMixLvl3SuccessRate",GreatDevelopItems);
	*(unsigned char *) GS_WINGLVL3MIX21 = byte;
	*(unsigned char *) GS_WINGLVL3MIX22 = byte;

	*(unsigned char*) GS_SETITEMMIX1 = GetChar(0, 100, 80,"ChaosMachineMixes","380LevelMixSuccessRate",GreatDevelopItems);
	*(unsigned char*) GS_SETITEMMIX2 = GetChar(0, 100, 80,"ChaosMachineMixes","380LevelMixSuccessRate",GreatDevelopItems);
	*(unsigned int*) GS_DINO_MIX = GetInt(0, 100, 70,"ChaosMachineMixes","DinorantMixSuccessRate",GreatDevelopItems);
	
	*(unsigned int*) GS_DARK_HORSE = GetInt(0, 100, 60,"DLPets","DarkHorseMixSuccessRate",GreatDevelopItems);
	*(unsigned int*) GS_DARK_HORSE_PRICE = GetInt(0, 2000000000, 5000000,"DLPets","DarkHorseMixPrice",GreatDevelopItems);
   	*(unsigned int*) GS_DARK_SPIRIT = GetInt(0, 100, 60,"DLPets","DarkSpiritMixSuccessRate",GreatDevelopItems);
	*(unsigned int*) GS_DARK_SPIRIT_PRICE = GetInt(0, 2000000000, 1000000,"DLPets","DarkSpiritMixPrice",GreatDevelopItems);

	*(unsigned int*) GS_EXC_DROP_RATE = GetInt(0, 2000, 2000,"ItemDropRates","ExcDropRate",GreatDevelopItems);
	*(unsigned int*) GS_EXC_SKILL_RATE = GetInt(0, 100, 100,"ItemDropRates","ExcSkillDropRate",GreatDevelopItems);
	*(unsigned int*) GS_EXC_LUCK_RATE = GetInt(0, 100, 1,"ItemDropRates","ExcLuckDropRate",GreatDevelopItems);
	*(unsigned int*) GS_SKILL_RATE = GetInt(0, 100, 6,"ItemDropRates","NormalSkillDropRate",GreatDevelopItems);
	*(unsigned int*) GS_LUCK_RATE = GetInt(0, 100, 4,"ItemDropRates","NormalLuckDropRate",GreatDevelopItems);
	*(unsigned char*) GS_ANCREWARD_SKILL_RATE = GetChar(0, 100, 6,"ItemDropRates","AncientRewardSkillDropRate",GreatDevelopItems);
	*(unsigned char*) GS_ANCREWARD_LUCK_RATE = GetChar(0, 100, 4,"ItemDropRates","AncientRewardLuckDropRate",GreatDevelopItems);
	*(unsigned char*) GS_ANCRANDOM_SKILL_RATE = GetChar(0, 100, 6,"ItemDropRates","AncientRandomSkillDropRate",GreatDevelopItems);
	*(unsigned char*) GS_ANCRANDOM_LUCK_RATE = GetChar(0, 100, 4,"ItemDropRates","AncientRandomLuckDropRate",GreatDevelopItems);


	byte = GetChar(0, 20, 7,"LevelUpPoints","LevelUpPointsForDl",GreatDevelopCommon);
	*(unsigned char*) GS_LVL_UP_DL1 = byte;
	*(unsigned char*) GS_LVL_UP_DL2 = byte;
	*(unsigned char*) GS_LVL_UP_DL3 = byte;
	*(unsigned char*) GS_LVL_UP_DL4 = byte;
	*(unsigned char*) GS_LVL_UP_DL5 = byte;

	byte = GetChar(0, 20, 7,"LevelUpPoints","LevelUpPointsForMg",GreatDevelopCommon);
	*(unsigned char*) GS_LVL_UP_MG1 = byte;
	*(unsigned char*) GS_LVL_UP_MG2 = byte;
	*(unsigned char*) GS_LVL_UP_MG3 = byte;
	*(unsigned char*) GS_LVL_UP_MG4 = byte;
	*(unsigned char*) GS_LVL_UP_MG5 = byte;

	byte = GetChar(0, 20, 5,"LevelUpPoints","LevelUpPointsForDkElfDwSum",GreatDevelopCommon);
	*(unsigned char*) GS_LVL_UP_NORMAL1 = byte;
	*(unsigned char*) GS_LVL_UP_NORMAL2 = byte;
	*(unsigned char*) GS_LVL_UP_NORMAL3 = byte;
	*(unsigned char*) GS_LVL_UP_NORMAL4 = byte;
	*(unsigned char*) GS_LVL_UP_NORMAL5 = byte;

	byte = GetChar(0, 5, 1,"LevelUpPoints","ExtraPointsAfterMarlonQuest",GreatDevelopCommon);
	*(unsigned char*) GS_LVL_UP_QUEST1 = byte;
	*(unsigned char*) GS_LVL_UP_QUEST2 = byte;
	*(unsigned char*) GS_LVL_UP_QUEST3 = byte;
	*(unsigned char*) GS_LVL_UP_QUEST4 = byte;
	*(unsigned char*) GS_LVL_UP_QUEST5 = byte;

	*(unsigned char*) GS_ML_POINTS = GetChar(0, 20, 1,"LevelUpPoints","MasterlvlPoints",GreatDevelopCommon);

	*(unsigned int *) GS_TWISTINGSLASH_USELV = GetInt(0,5000,80,"SkillLevel", "TwistingSlashMinLevel", GreatDevelopSkills);
	*(unsigned int *) GS_RAGEFULBLOW_USELV = GetInt(0,5000,170,"SkillLevel", "RagefulBlowMinLevel", GreatDevelopSkills);
	*(unsigned int *) GS_DEATHSTAB_USELV = GetInt(0,5000,160,"SkillLevel", "DeathStabMinLevel", GreatDevelopSkills);
	*(unsigned int *) GS_IMPALE_USELV = GetInt(0,5000,25,"SkillLevel", "ImapleMinLevel", GreatDevelopSkills) ;
	*(unsigned int *) GS_INNERSTRENGTH_USELV = GetInt(0,5000,120,"SkillLevel", "GreaterFortitudeMinLevel", GreatDevelopSkills) ;
	*(unsigned int *) GS_PENETRATION_USELV = GetInt(0,5000,130,"SkillLevel", "PenetrationMinLevel", GreatDevelopSkills) ;

	*(unsigned int *) GS_MSNORMAL01 = GetInt(0,10000,250,"ManaShield", "ManaShieldAgiNormal", GreatDevelopSkills) ;
	*(unsigned int *) GS_MSNORMAL02 = GetInt(0,10000,200,"ManaShield", "ManaShieldEneNormal", GreatDevelopSkills) ;
	*(unsigned int *) GS_MSMASTER01 = GetInt(0,10000,50,"ManaShield", "ManaShieldAgiMaster", GreatDevelopSkills) ;
	*(unsigned int *) GS_MSMASTER02 = GetInt(0,10000,50,"ManaShield", "ManaShieldEneMaster", GreatDevelopSkills) ; 

	*(unsigned int *) NormalManaShieldTime1 = GetInt(0,10000,40,"ManaShield", "ManaShieldTime", GreatDevelopSkills) ;
	*(unsigned int *) MasterManaShieldTime2 = GetInt(0,10000,40,"ManaShield", "ManaShieldTimeMaster", GreatDevelopSkills) ;


	dword =  GetInt(0,5000,150,"GreatFortitude", "GreatFortitudeVitNormal", GreatDevelopSkills);
	*(unsigned int *) NormalGreatForitiuteVit01 = dword;
	*(unsigned int *) NormalGreatForitiuteVit02 = dword;
	*(unsigned int *) NormalGreatForitiuteVit03 = dword;
	*(unsigned int *) GS_GFNORMAL02 = GetInt(0,5000,100,"GreatFortitude", "GreatFortitudeEneNormal", GreatDevelopSkills) ;

	dword =  GetInt(0,5000,150,"GreatFortitude", "GreatFortitudeVitMaster", GreatDevelopSkills);
	*(unsigned int *) MasterGreatForitiuteVit01 = dword;
	*(unsigned int *) MasterGreatForitiuteVit02 = dword;
	*(unsigned int *) MasterGreatForitiuteVit03 = dword;
	*(unsigned int *) GS_GFMASTER02 = GetInt(0,5000,100,"GreatFortitude", "GreatFortitudeEneMaster", GreatDevelopSkills) ;

	*(unsigned int *) NormalGreatForitiuteTime = GetInt(0,10000,10,"GreatFortitude", "GreatFortitudeTime", GreatDevelopSkills) ;
	*(unsigned int *) MasterGreatForitiuteTime = GetInt(0,10000,10,"GreatFortitude", "GreatFortitudeMaster", GreatDevelopSkills) ;


	*(unsigned int*) GS_BERSERKER_DIV1 = GetInt(0,5000,20,"Berserker","BerserkerDiv1",GreatDevelopSkills);
	*(unsigned int*) GS_BERSERKER_DIV2 = GetInt(0,5000,30,"Berserker","BerserkerDiv2",GreatDevelopSkills);
	*(unsigned int*) GS_BERSERKER_DIV3 = GetInt(0,5000,60,"Berserker","BerserkerDiv3",GreatDevelopSkills);
	*(unsigned int*) GS_DAMAGEREF_DIV1 = GetInt(0,5000,42,"DamageRef","DamageRefDiv1",GreatDevelopSkills);
	*(unsigned int*) GS_DAMAGEREF_DIV2 = GetInt(0,5000,25,"DamageRef","DamageRefDiv2",GreatDevelopSkills);

	*(unsigned int*) GS_CRITICALDMG_COMMAND = GetInt(0,5000,25,"CriticalDmg","CriticalDmgLeaderShip",GreatDevelopSkills);
	*(unsigned int*) GS_CRITICALDMG_ENERGY = GetInt(0,5000,30,"CriticalDmg","CriticalDmgEnergy",GreatDevelopSkills);
	*(unsigned int*) GS_CRITICALDMG_TIME = GetInt(0,5000,10,"CriticalDmg","CriticalDmgTime",GreatDevelopSkills);

	*(unsigned int*) MaxZen  = GetInt(0, 2000000000, 2000000000,"MaximumZen", "MaxZenInBag", GreatDevelopCommon);

	dword = GetInt(0, 2000000000, 1000000000,"MaximumZen", "MaxZenInVault", GreatDevelopCommon);
	*(unsigned int*) MaxZen1 = dword;
	*(unsigned int*) MaxZen2 = dword;
	*(unsigned int*) MaxZen3 = dword;

	*(unsigned int *) GS_PARTYEXP_2_NORMAL = GetInt(0,5000,160,"PartyExp","NormalParty2Exp",GreatDevelopCommon);
	*(unsigned int *) GS_PARTYEXP_3_NORMAL = GetInt(0,5000,180,"PartyExp","NormalParty3Exp",GreatDevelopCommon);
	*(unsigned int *) GS_PARTYEXP_4_NORMAL = GetInt(0,5000,200,"PartyExp","NormalParty4Exp",GreatDevelopCommon);
	*(unsigned int *) GS_PARTYEXP_5_NORMAL = GetInt(0,5000,220,"PartyExp","NormalParty5Exp",GreatDevelopCommon);
	*(unsigned int *) GS_PARTYEXP_3_SET = GetInt(0,5000,230,"PartyExp","SetParty3Exp",GreatDevelopCommon);
	*(unsigned int *) GS_PARTYEXP_4_SET = GetInt(0,5000,270,"PartyExp","SetParty4Exp",GreatDevelopCommon);
	*(unsigned int *) GS_PARTYEXP_5_SET  = GetInt(0,5000,300,"PartyExp","SetParty5Exp",GreatDevelopCommon);
#ifdef _GS
	*(unsigned int*) GS_DS_PARTYEXP_2 = GetInt(0,5000,160,"DevilSquare","DevilSquarePartyExp2Players",GreatDevelopEvents);
	*(unsigned int*) GS_DS_PARTYEXP_3 = GetInt(0,5000,180,"DevilSquare","DevilSquarePartyExp3Players",GreatDevelopEvents);
	*(unsigned int*) GS_DS_PARTYEXP_4 = GetInt(0,5000,200,"DevilSquare","DevilSquarePartyExp4Players",GreatDevelopEvents);
	*(unsigned int*) GS_DS_PARTYEXP_5 = GetInt(0,5000,220,"DevilSquare","DevilSquarePartyExp5Players",GreatDevelopEvents);
	*(unsigned int*) GS_DS_PARTYDIFFEXP_3 = GetInt(0,5000,230,"DevilSquare","DevilSquareSetPartyExp3Players",GreatDevelopEvents);
	*(unsigned int*) GS_DS_PARTYDIFFEXP_4 = GetInt(0,5000,270,"DevilSquare","DevilSquareSetPartyExp4Players",GreatDevelopEvents);
	*(unsigned int*) GS_DS_PARTYDIFFEXP_5 = GetInt(0,5000,300,"DevilSquare","DevilSquareSetPartyExp5Players",GreatDevelopEvents);
#endif
#ifdef _GS_CS
	*(unsigned int*) GSCS_LOT_MAXPRICE = GetInt(0,1000000000,300000,"CastleSiege","CSLandOfTrialMaxPayment",GreatDevelopEvents);
	*(unsigned char*) GSCS_LORDMIX_MAXUSE  = GetChar(0,5000,0,"CastleSiege","CSLordMixMaxUsePerDay",GreatDevelopEvents);

	*(unsigned char*) GSCS_CRYWOLF_REWARD_ELF = GetChar(0,15,14,"CryWolf","CrywolfAltarElfRewardIndexID",GreatDevelopEvents) * 512 + GetChar(0,255,13,"CryWolf","CrywolfAltarElfRewardGroupID",GreatDevelopEvents);
	*(unsigned char*) GSCS_CRYWOLF_REWARD_TOP5 = GetChar(0,15,14,"CryWolf","CrywolfTop5RewardIndexID",GreatDevelopEvents) * 512 + GetChar(0,255,13,"CryWolf","CrywolfTop5RewardGroupID",GreatDevelopEvents);
	
	dword = GetInt(0,1000000000,200000000,"CastleSiege","CSSeniorMaxCash",GreatDevelopEvents);
	*(unsigned int*) GSCS_SENIOR_MAXZEN1 = dword;
	*(unsigned int*) GSCS_SENIOR_MAXZEN2 = dword;
#endif 
}	
void cConfigs::LoadFixes()
{

	#ifdef _GS
	EldaradoEventType	= GetInt(0, 1, 0,"EldaradoEvent", "EldaradoEventType", GreatDevelopEvents);
	CCAllowingPlayers	= GetInt(0, 2, 0,"ChaosCastle", "ChaosCastleAllowingPlayers", GreatDevelopEvents);
	BCAllowingPlayers	= GetInt(0, 2, 0,"BloodCastle", "BloodCastleAllowingPlayers", GreatDevelopEvents);
	BCEnterMasterType	= GetInt(0, 1, 0,"BloodCastle", "BloodCastleMasterEnterType", GreatDevelopEvents);
	DSAllowingPlayers	= GetInt(0, 2, 0,"DevilSquare", "DevilSquareAllowingPlayers", GreatDevelopEvents); 
	#endif

	UseChecksum		= GetInt(0, 1, 0, "CheckSum", "UseCheckSum", GreatDevelopCommon);	  
	PersonalIDFix	= GetInt(0, 1, 1, "Bypasseres", "PersonalIDBypasser", GreatDevelopCommon);
	GuildIDFix		= GetInt(0, 1, 1, "Bypasseres", "GuildIDBypasser", GreatDevelopCommon);
	DisableLogs		= GetInt(0, 1, 0, "Logs", "DisableLogs", GreatDevelopCommon);
	AllowExeAnc		= GetInt(0, 1, 1, "SpecialItem", "AllowExeAnc", GreatDevelopItems);	
	AllowJohAnc		= GetInt(0, 1, 1, "SpecialItem", "AllowJohAnc", GreatDevelopItems);
	AllowExeSock	= GetInt(0, 1, 1, "SpecialItem", "AllowExeSock", GreatDevelopItems);
	MaxLifeOpt		= GetInt(0, 1, 1, "SpecialItem", "MaxLifeOpt", GreatDevelopItems);
	CSSkillsOnNOrmal = GetInt(0, 1, 1, "Skills", "CSSkillsOnNOrmal", GreatDevelopSkills);    
	Enable65kStats	= GetInt(0, 1, 0, "AddCommand",	"Enable65kStats", GreatDevelopCmd);	
	DumpFile		= GetInt(0, 1, 0, "Dump", "EnableCrashDump",GreatDevelopCommon);
}

void cConfigs::LoadAntiAfk()
{		  			  
	AntiAfkConfig.Enabled	= GetInt(0, 1,		1,		"AntiAFK",		"AntiAFKEnabled",		GreatDevelopAntiAFK);  
	if(!AntiAfkConfig.Enabled)
		return;
	AntiAfkConfig.Time		= GetInt(0, 32000,	300,	"AntiAFK",		"AntiAFKTimer",			GreatDevelopAntiAFK);
	AntiAfkConfig.Warnings	= GetInt(0, 5,		3,		"AntiAFK",		"AntiAFKWarnings",		GreatDevelopAntiAFK);	  
	AntiAFK.Load();
}

void cConfigs::LoadArcher()
{		  		 
	Archer.Enabled				= GetInt(0, 1,						1,		"GoldenArcher",	"ArcherEnabled",		GreatDevelopArcher);	
	
	if(Archer.Enabled)
	{	
		Archer.NeedRenaAmount	= GetInt(0, 250,								7,		"GoldenArcher", "RenasCount",			GreatDevelopArcher); 	   
		Archer.WCoinsReward		= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	1,		"GoldenArcher", "WCoinsReward",			GreatDevelopArcher);
		Archer.PCPointsReward	= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	1,		"GoldenArcher", "PCPointsReward",		GreatDevelopArcher);	   
		Archer.ZenReward		= GetInt(0, 2000000000,							100000, "GoldenArcher", "ZenReward",			GreatDevelopArcher);
		GoldenArcher.LoadPrizeItems();
	}
}

void cConfigs::LoadCommands()
{	
	Commands.MaxLvl						= GetInt(300, 1000, 400,"LevelSettings", "MaxLevel", GreatDevelopCommon);
	//		drop		//
	Commands.IsDrop						= GetInt(0,	1,					1,		"Drop",			"DropEnabled",					GreatDevelopCmd);

	//		Reload		//
	Commands.IsReload					= GetInt(0,	1,					1,		"Reload",			"ReloadEnabled",					GreatDevelopCmd);

	//		gmove		//
	Commands.IsGmove					= GetInt(0,	1,					1,		"Gmove",		"GmoveEnabled",					GreatDevelopCmd);	 

	//		setpk
	Commands.IsSetPK					= GetInt(0, 1,					1,		"SetPK",		"SetPKEnabled",					GreatDevelopCmd);  
	
	//		setzen
	Commands.IsSetZen					= GetInt(0, 1,					1,		"SetZen",		"SetZenEnabled",				GreatDevelopCmd); 

	//		gg			//																	 	
	Commands.IsGg						= GetInt(0, 1,					1,		"GPost",		"GgEnabled",					GreatDevelopCmd);	

	//		time		//
	Commands.IsTime						= GetInt(0, 1,					1,		"Time",			"TimeEnabled",					GreatDevelopCmd);  

	//		online		//
	Commands.IsOnline					= GetInt(0, 1,					1,		"OnlineCommand","OnlineEnabled",				GreatDevelopCmd); 

	//		status		//
	Commands.IsStatus					= GetInt(0, 1,					1,		"Status",		"StatusEnabled",				GreatDevelopCmd); 

	//		SetChar		//
	Commands.IsSetChar					= GetInt(0, 1,					1,		"SetChar",		"SetCharEnabled",				GreatDevelopCmd);
	//		bans		//
	Commands.IsBanPost					= GetInt(0, 1,					1,		"Bans",			"BanPostEnabled",				GreatDevelopCmd);	
	Commands.IsBanChar					= GetInt(0, 1,					1,		"Bans",			"BanCharEnabled",				GreatDevelopCmd);	
	Commands.IsBanAcc					= GetInt(0, 1,					1,		"Bans",			"BanAccEnabled",				GreatDevelopCmd);  	

	//		skin		//
	Commands.SkinEnabled				= GetInt(0, 1,									1,		"Skin",			"SkinEnabled",					GreatDevelopCmd);
	Commands.SkinOnlyForGm				= GetInt(0, 1,									0,		"Skin",			"SkinOnlyForGm",				GreatDevelopCmd);
	Commands.SkinLevelReq				= GetInt(0, Commands.MaxLvl,					250,	"Skin",			"SkinLevelReq",					GreatDevelopCmd);
	Commands.SkinPriceZen				= GetInt(0, 2000000000,							100000,	"Skin",			"SkinPriceZen",					GreatDevelopCmd);
	Commands.SkinPricePcPoint			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	1,		"Skin",			"SkinPricePcPoint",				GreatDevelopCmd);
	Commands.SkinPriceWCoin				= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	1,		"Skin",			"SkinPriceWCoin",				GreatDevelopCmd);	

	//		post		//	 
	Commands.IsPost						= GetInt(0, 1,									1,		"Post",			"PostEnabled",					GreatDevelopCmd); 
	Commands.PostLvl					= GetInt(0, Commands.MaxLvl,					1,		"Post",			"PostLevelReq",					GreatDevelopCmd);				  
	Commands.PostPriceZen				= GetInt(0, 2000000000,							10000,	"Post",			"PostPriceZen",					GreatDevelopCmd);		 
	Commands.PostPricePCPoint			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	0,		"Post",			"PostPricePcPoint",				GreatDevelopCmd);	 
	Commands.PostPriceWCoin				= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	0,		"Post",			"PostPriceWCoin",				GreatDevelopCmd);												
	Commands.PostColor					= GetInt(1, 3,									1,		"Post",			"PostColor",					GreatDevelopCmd);  

	//		add			//
	Commands.AddPointEnabled			= GetInt(0, 1,									1,		"AddCommand",	"AddPointEnabled",				GreatDevelopCmd);
	Commands.AddPointLevelReq			= GetInt(0, Commands.MaxLvl,					0,		"AddCommand",	"AddPointLevelReq",				GreatDevelopCmd);			   	
	Commands.AddPriceZen				= GetInt(0, 2000000000,							10000,	"AddCommand",	"AddPriceZen",					GreatDevelopCmd);		 
	Commands.AddPricePCPoint			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	0,		"AddCommand",	"AddPricePCPoint",				GreatDevelopCmd);	 
	Commands.AddPriceWCoin				= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	0,		"AddCommand",	"AddPriceWCoin",				GreatDevelopCmd);	 
	Commands.MaxAddedStats				= GetInt(0, 65000,								0,		"AddCommand",	"MaxAddedStats",				GreatDevelopCmd);

	//		ware		//
	Commands.IsMultyVault				= GetInt(0,	1,									1,		"MultyVault",	"IsMultyVault",					GreatDevelopCmd);  
	Commands.NumberOfVaults				= GetInt(2,	99,									3,		"MultyVault",	"NumberOfVaults",				GreatDevelopCmd); 
	Commands.ZenForChange				= GetInt(0,	2000000000,							10000,	"MultyVault",	"ZenForChange",					GreatDevelopCmd);
	Commands.PcPointForChange			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	0,		"MultyVault",	"PcPointForChange",				GreatDevelopCmd);
	Commands.WCoinForChange				= GetInt(0,	PCPoint.sPoints.MaximumWCPoints,	0,		"MultyVault",	"WCoinForChange",				GreatDevelopCmd);

	//		pkclear		//	
	ClearCommand.Enabled				= GetInt(0, 1,									1,		"PkClear",		"PkClearEnabled",				GreatDevelopCmd);
	ClearCommand.OnlyForGm				= GetInt(0, 1,									0,		"PkClear",		"PkClearOnlyForGm",				GreatDevelopCmd);
	ClearCommand.Type					= GetInt(0, 2,									1,		"PkClear",		"PKClearType",					GreatDevelopCmd);	 																													
	ClearCommand.PriceZen				= GetInt(0, 2000000000,							100000, "PkClear",		"PkClearPriceZen",				GreatDevelopCmd);	 
	ClearCommand.PriceZenForAll			= GetInt(0, 2000000000,							1000000,"PkClear",		"PkClearPriceZenForAll",		GreatDevelopCmd);
	ClearCommand.PricePcPoints			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	20,		"PkClear",		"PkClearPricePcPoints",			GreatDevelopCmd);	 
	ClearCommand.PricePcPointsForAll	= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	200,	"PkClear",		"PkClearPricePcPointsForAll",	GreatDevelopCmd);
	ClearCommand.PriceWCoins			= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	2,		"PkClear",		"PkClearPriceWCoins",			GreatDevelopCmd);	 
	ClearCommand.PriceWCoinsForAll		= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	20,		"PkClear",		"PkClearPriceWCoinsForAll",		GreatDevelopCmd);
	ClearCommand.LevelReq				= GetInt(0, Commands.MaxLvl,					100,	"PkClear",		"PkClearLevelReq",				GreatDevelopCmd);  
}

void cConfigs::LoadPkClearGuard()
{						  
	ClearNpc.Enabled				= GetInt(0, 1,					1,		"PkClearGuard",		"LoadPkGuard",						GreatDevelopPkClear);
	if(!ClearNpc.Enabled)
		return;

	ClearNpc.NpcId					= GetInt(0, 32000,								249,	"PkClearGuard",		"PkClearGuardId",					GreatDevelopPkClear);	   				 
	ClearNpc.Type					= GetInt(0, 2,									1,		"PkClearGuard",		"PKClearGuardType",					GreatDevelopPkClear);																															
	ClearNpc.PriceZen				= GetInt(0, 2000000000,							100000,	"PkClearGuard",		"PkClearGuardPriceZen",				GreatDevelopPkClear);	 
	ClearNpc.PriceZenForAll			= GetInt(0, 2000000000,							1000000,"PkClearGuard",		"PkClearGuardPriceZenForAll",		GreatDevelopPkClear);
	ClearNpc.PricePcPoints			= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	20,		"PkClearGuard",		"PkClearGuardPricePcPoints",		GreatDevelopPkClear);	 
	ClearNpc.PricePcPointsForAll	= GetInt(0, PCPoint.sPoints.MaximumPCPoints,	200,	"PkClearGuard",		"PkClearGuardPricePcPointsForAll",	GreatDevelopPkClear);	
	ClearNpc.PriceWCoins			= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	2,		"PkClearGuard",		"PkClearGuardPriceWCoins",			GreatDevelopPkClear);	 
	ClearNpc.PriceWCoinsForAll		= GetInt(0, PCPoint.sPoints.MaximumWCPoints,	20,		"PkClearGuard",		"PkClearGuardPriceWCoinsForAll",	GreatDevelopPkClear);	   
	ClearNpc.LevelReq				= GetInt(0, 400,								100,	"PkClearGuard",		"PkClearGuardLevelReq",				GreatDevelopPkClear);
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
#ifdef _GS
	moss.LoadMoss();
#endif
		
	//
	GuildRes				= GetInt(0, 32767, 5,"GuildMaster", "GuildCreateReset", GreatDevelopCommon);
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