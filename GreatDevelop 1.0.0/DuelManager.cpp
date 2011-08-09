// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.0								# //
// ================================================== // 

#include "StdAfx.h"  
#include "Configs.h"
#ifdef GS90
#include "DuelManager.h"
#include "User.h" 
#include "Utilits.h"
#include "Logger.h"
#include "ChatCommands.h"
#include "SQL.h"

// ----------------------------------------------------------------------------------------------------------------
DuelSystem g_DuelSystem;
// ----------------------------------------------------------------------------------------------------------------
static const struct DUEL_GATES
{
	int Gate01;
	int Gate02;
	int SeparatorGate;
} 
// ----------------------------------------------------------------------------------------------------------------

g_DuelGates[MAX_DUEL_ROOMS] =
{
	{295, 296, 303},
	{297, 298, 304},
	{299, 300, 305},
	{301, 302, 306}
};
// ----------------------------------------------------------------------------------------------------------------

DuelSystem::DuelSystem(void)
{
	ZeroMemory(&this->g_DuelRooms, sizeof(this->g_DuelRooms));
	// ----
	for(short i = 0; i < MAX_DUEL_ROOMS; ++i) 
	{
		this->g_DuelRooms[i].RoomFree	 = true;
		this->g_DuelRooms[i].DuelWaiting = false;
		this->g_DuelRooms[i].szWinner	 = false;
	}
}
// ----------------------------------------------------------------------------------------------------------------

DuelSystem::~DuelSystem(void)
{
	// ----
}
// ----------------------------------------------------------------------------------------------------------------
//## Находим игроков в руме
int DuelSystem::GetUserDuelRoom(LPOBJ lpObj)
{
	for(short i = 0; i < MAX_DUEL_ROOMS; ++i)
	{
		if(this->g_DuelRooms[i].szlpObjOne == lpObj || this->g_DuelRooms[i].szlpObjTy == lpObj) 
		{
			return i;
		}
	}
	return -1;
}
// ----------------------------------------------------------------------------------------------------------------
//## Глобальная функция
void DuelSystem::Run()
{
	for(short i = 0; i < MAX_DUEL_ROOMS; ++i)
	{
		if(this->g_DuelRooms[i].RoomFree == FALSE)
		{
			if(GetTickCount() - this->g_DuelRooms[i].dwStartTime < 5000)
			{
				continue;
			}
			// ----
			for(short u = 0; u < MAX_DUEL_SEPARATORS; u++)
			{
				if(this->g_DuelRooms[i].szSeparators[u] == NULL)
				{
					continue;
				}
				// ----
				if(Utilits.gObjIsConnected(this->g_DuelRooms[i].szSeparators[u]->m_Index))
				{
					// ----
					if(this->g_DuelRooms[i].szSeparators[u]->MapNumber != 0x40)
					{
						this->SendEndDuel(this->g_DuelRooms[i].szSeparators[u]);
						// ----
						AddBuff(this->g_DuelRooms[i].szSeparators[u], 18, 0, 0, 0, 0, 1);
						// ----
						gObjViewportListProtocolCreate(this->g_DuelRooms[i].szSeparators[u]);
						// ----
						GCStateInfoSendg(this->g_DuelRooms[i].szSeparators[u], 0, 98);
						// ----
				
						if(Config.Duel.Logging)
						{
							Log.ConsoleOutPut(1, c_Blue, t_Duel,"[Duel System] Spectator [%s] Leave [%d] Room", 
													this->g_DuelRooms[i].szSeparators[u]->Name, i + 1);
						}				
						// ----
						this->SendSpectatorRemove(u, i);
						// ----
						this->g_DuelRooms[i].szSeparators[u] = NULL;
					}
				}
				else
				{
					if(Config.Duel.Logging)
					{
						Log.ConsoleOutPut(1, c_Blue, t_Duel,"[Duel System] Spectator Leave Room [%d]", i + 1);
					}
					// ----
					this->g_DuelRooms[i].szSeparators[u] = NULL;
					// ----
					this->SendSpectatorList(i);
				}
				SendSpectatorList(i);
			}
			// ----
			if(this->g_DuelRooms[i].szlpObjOne != NULL || this->g_DuelRooms[i].szlpObjTy != NULL)
			{
				if(Utilits.gObjIsConnected(this->g_DuelRooms[i].szlpObjOne->m_Index) == FALSE || 
				   Utilits.gObjIsConnected(this->g_DuelRooms[i].szlpObjTy->m_Index)  == FALSE )
				{
					this->RoomReset(i);
					continue;
				}
				// ----
				else if((this->g_DuelRooms[i].szlpObjOne->MapNumber != 0x40 ||
					     this->g_DuelRooms[i].szlpObjTy->MapNumber  != 0x40) && 
					     this->g_DuelRooms[i].szWinner == FALSE)
				{
					this->RoomReset(i);
					continue;
				}
				// ----
				else if(this->g_DuelRooms[i].szlpObjOne->Connected < PLAYER_PLAYING ||
						this->g_DuelRooms[i].szlpObjTy->Connected  < PLAYER_PLAYING)
				{
					this->RoomReset(i);
					continue;
				}
			}
			// ----
			else
			{
				this->RoomReset(i);
				continue;
			}
			// ----
			if(this->UpdateLifebarTime < GetTickCount())
			{
				this->SendLifebarStatus(i);
				this->UpdateLifebarTime = GetTickCount() + 2000;
			}
			// ----
			if(this->g_DuelRooms[i].dwTicketCount != 0)
			{
				if(this->g_DuelRooms[i].dwTicketCount < GetTickCount())
				{
					this->RoomReset(i);
					// ---
					if(Config.Duel.Logging)
					{
						Log.ConsoleOutPut(1, c_Blue, t_Duel,"[Duel System] Room [%d] Cleaned", i + 1);
					}
				}
			}
			// ----
			if(this->g_DuelRooms[i].RoomFree == FALSE && this->g_DuelRooms[i].DuelWaiting == FALSE && 
			   this->g_DuelRooms[i].szWinner == FALSE)
			{
				for(short s = 0; s < MAX_DUEL_SEPARATORS; s++)
				{
					if(this->g_DuelRooms[i].szSeparators[s] != NULL)
					{
						if(AddTab[this->g_DuelRooms[i].szSeparators[s]->m_Index].DUEL_SpecVisible == 1)
						{
							AddBuff(this->g_DuelRooms[i].szSeparators[s], 18, 0, 0, 0, 0, -10);
							// ----
							gObjViewportListProtocolDestroy(this->g_DuelRooms[i].szSeparators[s]);
							// ----
							if(Config.Duel.Logging)
							{
								Log.ConsoleOutPut(1, c_Blue, t_Duel,"[Duel System]Character [%s] Added Invisible", 
												    this->g_DuelRooms[i].szSeparators[s]->Name);
							}
							// ----
							AddTab[this->g_DuelRooms[i].szSeparators[s]->m_Index].DUEL_SpecVisible = 0;
						}
					}
				}
			}
		}
	}
	// ----
	for(short n = 0; n < MAX_DUEL_ROOMS; n++)
	{
		if(this->g_DuelRooms[n].DuelWaiting == TRUE)
		{
			if(Utilits.gObjIsConnected(this->g_DuelRooms[n].szlpObjOne->m_Index) == FALSE || 
			   Utilits.gObjIsConnected(this->g_DuelRooms[n].szlpObjTy->m_Index)  == FALSE )
			{
				this->RoomReset(n);
				continue;
			}
			// ----
			else if(this->g_DuelRooms[n].szlpObjOne->Connected < PLAYER_PLAYING ||
					this->g_DuelRooms[n].szlpObjTy->Connected  < PLAYER_PLAYING)
			{
				this->RoomReset(n);
				continue;
			}
		}
	}
	// ----
	if(this->UpdateTickCount < GetTickCount())
	{
		for(short i = 8000; i < OBJECT_MAX; ++i)
		{
			LPOBJ lpObj    = (LPOBJ)OBJECT_POINTER(i);
			// ----
			if((lpObj->m_IfState.use) && lpObj->m_IfState.type == 20)
			{
				this->SendDuelStatus(lpObj);
			}
		}
		this->UpdateTickCount = GetTickCount() + 6000;
	}
	return;
}
// ----------------------------------------------------------------------------------------------------------------
//## Обновляем Результаты дуэля;
void DuelSystem::UpdateDuelScore(short iRoom)
{ 
	if(iRoom < 0 || iRoom > MAX_DUEL_ROOMS - 1)
	{
		return;
	}
	// ----
	int aIndex = this->g_DuelRooms[iRoom].szlpObjOne->m_Index;
	int uIndex = this->g_DuelRooms[iRoom].szlpObjTy->m_Index;
	// ----
	PMSG_DUEL_SCORE pMsg;
	// ----
	pMsg.h.c			= 0xC1;
	pMsg.h.size			= sizeof(pMsg);
	pMsg.h.headcode		= 0xAA;
	pMsg.h.subcode		= 0x04;
	pMsg.NumberH1		= SET_NUMBERH(aIndex);
	pMsg.NumberL1		= SET_NUMBERL(aIndex);
	pMsg.NumberH2		= SET_NUMBERH(uIndex);
	pMsg.NumberL2		= SET_NUMBERL(uIndex);
	pMsg.btDuelScore1	= this->g_DuelRooms[iRoom].szPointsOne;
	pMsg.btDuelScore2	= this->g_DuelRooms[iRoom].szPointsTy;
	LPOBJ gObj     = (LPOBJ)OBJECT_POINTER(aIndex);
	LPOBJ lpObj    = (LPOBJ)OBJECT_POINTER(uIndex);
	// ----
	if(Config.Duel.Logging)
	{
		Log.ConsoleOutPut(1, c_Blue, t_Duel,"[Duel System] Room [%d] Results [%s][%s] VS [%s][%s] Rank [%d] : [%d]", 
							iRoom + 1, gObj->AccountID, gObj->Name, lpObj->AccountID, lpObj->Name,
							g_DuelRooms[iRoom].szPointsOne, g_DuelRooms[iRoom].szPointsTy);
	}
	// ----
	if(g_DuelRooms[iRoom].szPointsOne >= MAX_DUEL_WIN_POINTS)
	{
		if(Config.Duel.Ranking)
		{
			SaveDuel(gObj->AccountID, gObj->Name, lpObj->AccountID,lpObj->Name,
								g_DuelRooms[iRoom].szPointsOne, g_DuelRooms[iRoom].szPointsTy);
		}	   			
	}
	// ----
	if(g_DuelRooms[iRoom].szPointsTy >= MAX_DUEL_WIN_POINTS)
	{
		if(Config.Duel.Ranking)
		{
			SaveDuel(lpObj->AccountID, lpObj->Name, gObj->AccountID, gObj->Name,
								g_DuelRooms[iRoom].szPointsTy, g_DuelRooms[iRoom].szPointsOne);
		}
	}
	// ----
	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	DataSend(uIndex, (LPBYTE)&pMsg, pMsg.h.size);
	// ----
	for(short i = 0; i < MAX_DUEL_SEPARATORS; ++i)
	{
		if(this->g_DuelRooms[iRoom].szSeparators[i] == NULL) 
		{
			continue;
		}
		DataSend(this->g_DuelRooms[iRoom].szSeparators[i]->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	}
}
// ----------------------------------------------------------------------------------------------------------------
//## Обновляем результаты чара;
void DuelSystem::PlayerScore(LPOBJ lpObj)
{
	int iRoom = this->GetUserDuelRoom(lpObj);
	// ----
	if(iRoom >= 0 && iRoom < MAX_DUEL_ROOMS)
	{
		if(this->g_DuelRooms[iRoom].szlpObjOne->m_Index == lpObj->m_Index)
		{
			this->g_DuelRooms[iRoom].szPointsOne++;
			this->UpdateDuelScore(iRoom);
		}
		// ----
		else if(this->g_DuelRooms[iRoom].szlpObjTy->m_Index == lpObj->m_Index)
		{
			this->g_DuelRooms[iRoom].szPointsTy++;
			this->UpdateDuelScore(iRoom);
		}
	}
}
// ----------------------------------------------------------------------------------------------------------------
//## Пакет для конца дуэли;
void DuelSystem::SendEndDuel(LPOBJ lpObj)
{ 
	if(lpObj == NULL)
	{
		return;
	}
	if(Utilits.gObjIsConnected(lpObj->m_Index) == FALSE)
	{ 
		return;
	}
	// ----
	BYTE lpMsgClose[5] = {0xC1, 0x05, 0xAA, 0x03, 0x00};
	// ----
	DataSend(lpObj->m_Index, &lpMsgClose[0], lpMsgClose[1]);
}
// ----------------------------------------------------------------------------------------------------------------
//## Смотрим результат Сепараторов;
int DuelSystem::GetSpectatorCount(short iRoom)
{
	if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS) 
	{
		return -1;
	}
	// ----
	int szCount = 0;
	// ----
	for(short i = 0; i < MAX_DUEL_SEPARATORS; ++i)
	{
		if(this->g_DuelRooms[iRoom].szSeparators[i] != NULL) 
		{
			szCount++;
		}
	}
	return szCount;
}
// ----------------------------------------------------------------------------------------------------------------
//## Интерфейс дуэль сепараторов;
void DuelSystem::SendDuelStatus(LPOBJ lpObj)
{
	PMSG_DUEL_STATUS pMsg;
	// ----
	pMsg.h.c		= 0xC1;
	pMsg.h.size		= sizeof(pMsg);
	pMsg.h.headcode = 0xAA;
	pMsg.h.subcode	= 0x06;
	// ----
	ZeroMemory(&pMsg.pRoomStatus, sizeof(pMsg.pRoomStatus));
	// ----
	for(short i = 0; i < MAX_DUEL_ROOMS; ++i)
	{
		if(this->g_DuelRooms[i].RoomFree == FALSE)
		{
			if(this->g_DuelRooms[i].szlpObjOne == NULL || this->g_DuelRooms[i].szlpObjTy == NULL)
			{
				continue;
			}
			// ----
			pMsg.pRoomStatus[i].btDuelRunning = TRUE;
			// ----
			int szSeparatorCount  = this->GetSpectatorCount(i);
			// ----
			if(szSeparatorCount < 0 || szSeparatorCount >= 10)
			{
				pMsg.pRoomStatus[i].btDuelOpen = FALSE;
			}
			// ----
			else
			{
				pMsg.pRoomStatus[i].btDuelOpen = TRUE;
			}
			// ----
			memcpy(&pMsg.pRoomStatus[i].szName1[0], &this->g_DuelRooms[i].szlpObjOne->Name[0], 10);
			memcpy(&pMsg.pRoomStatus[i].szName2[0], &this->g_DuelRooms[i].szlpObjTy->Name[0], 10);
		}
	}
	DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);
}
// ----------------------------------------------------------------------------------------------------------------
//## Даём Индекс пустой румы;
int DuelSystem::GetFreeRoomIndex()
{
	for(short i = 0; i < MAX_DUEL_ROOMS; ++i)
	{
		if(this->g_DuelRooms[i].RoomFree == TRUE)
		{
			if(this->g_DuelRooms[i].DuelWaiting == FALSE)
			{
				return i;	
			}
		}
	}
	return -1;
}
// ----------------------------------------------------------------------------------------------------------------
//## Обновляем Информацию дуэли;
void DuelSystem::UserDuelInfoReset(LPOBJ lpObj)
{ 
	if(lpObj == NULL) 
	{	
		return;
	}
	// ----
	int aIndex = lpObj->m_Index;
	AddTab[aIndex].DUEL_Room = -1;
	lpObj->m_iDuelUser					 = -1;
	lpObj->m_iDuelUserRequested			 = -1;
	lpObj->m_iDuelUserReserved			 = -1;
	lpObj->m_btDuelScore				 = 0;
}
// ----------------------------------------------------------------------------------------------------------------
//## Чистим руму дуэльки;
void DuelSystem::RoomReset(short iRoom, bool dontMove, bool dontSendEnd)
{
	if(this->g_DuelRooms[iRoom].szlpObjOne != NULL) //  Игрок номер 1
	{
		if(Utilits.gObjIsConnected(this->g_DuelRooms[iRoom].szlpObjOne->m_Index))
		{
			if(dontSendEnd == false)
			{
				this->SendEndDuel(this->g_DuelRooms[iRoom].szlpObjOne);
			}
			// ----
			if(this->g_DuelRooms[iRoom].szlpObjOne->MapNumber == 0x40)
			{
				if(dontMove == false)
				{
					gObjMoveGate(this->g_DuelRooms[iRoom].szlpObjOne->m_Index, 294);
				}
			}
		}
		// ----
		this->UserDuelInfoReset(this->g_DuelRooms[iRoom].szlpObjOne);
	}
	// ----
	if(this->g_DuelRooms[iRoom].szlpObjTy != NULL)  // Игрок номер 2
	{
		if(Utilits.gObjIsConnected(this->g_DuelRooms[iRoom].szlpObjTy->m_Index))
		{
			if(dontSendEnd == false)
			{
				this->SendEndDuel(this->g_DuelRooms[iRoom].szlpObjTy);
			}
			// ----
			if(this->g_DuelRooms[iRoom].szlpObjTy->MapNumber == 0x40)
			{
				if(dontMove == false)
				{
					gObjMoveGate(this->g_DuelRooms[iRoom].szlpObjTy->m_Index, 294);
				}
			}
		}
		// ----
		this->UserDuelInfoReset(this->g_DuelRooms[iRoom].szlpObjTy);
	}
	// ----
	for(short i = 0; i < MAX_DUEL_SEPARATORS; ++i)
	{
		if(this->g_DuelRooms[iRoom].szSeparators[i] != NULL)
		{
			this->SendEndDuel(this->g_DuelRooms[iRoom].szSeparators[i]);
			// ----
			AddBuff(this->g_DuelRooms[iRoom].szSeparators[i], 18, 0, 0, 0, 0, 1);
			// ----
			gObjViewportListProtocolCreate(this->g_DuelRooms[iRoom].szSeparators[i]);
			// ----
			GCStateInfoSendg(this->g_DuelRooms[iRoom].szSeparators[i], 0, 98);
			// ----
			gObjMoveGate(this->g_DuelRooms[iRoom].szSeparators[i]->m_Index, 294);
		}
		// ----
		this->g_DuelRooms[iRoom].szSeparators[i] = NULL;
	}
	this->g_DuelRooms[iRoom].szlpObjOne   = NULL;
	this->g_DuelRooms[iRoom].szPointsOne  = 0;
	// ----
	this->g_DuelRooms[iRoom].szlpObjTy    = NULL;
	this->g_DuelRooms[iRoom].szPointsTy   = 0;
	// ----
	this->g_DuelRooms[iRoom].RoomFree	  = TRUE;
	this->g_DuelRooms[iRoom].DuelWaiting  = FALSE;
	this->g_DuelRooms[iRoom].szWinner	  = FALSE;
	// ----
	this->g_DuelRooms[iRoom].dwTicketCount= 0;
	this->g_DuelRooms[iRoom].dwStartTime  = 0;
	// ----
			if(Config.Duel.Logging)
		{
	Log.ConsoleOutPut(1, c_Blue, t_Duel,"[Duel System] Room [%d] Has Restarted", iRoom +1);
			}
}
// ----------------------------------------------------------------------------------------------------------------
//## Табличка с Победителем и Проигравшим;
void DuelSystem::SendEndDuelNotification(LPOBJ lpObj, char* Winner, char* Looser)
{
	PMSG_DUEL_FINISH pMsg;
	// ----
	pMsg.h.c		= 0xC1;
	pMsg.h.size		= sizeof(pMsg);
	pMsg.h.headcode = 0xAA;
	pMsg.h.subcode	= 0x0C;
	// ----
	memcpy(pMsg.szWinner, Winner, 10);
	memcpy(pMsg.szLooser, Looser, 10);
	// ----
	DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);
}
// ----------------------------------------------------------------------------------------------------------------
//## Интерфейс сепараторов;
void DuelSystem::SendSpectatorAdd(short iSpecIndex, int iRoom)
{
	if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
	{
		return;
	}
	// ----
	if(iSpecIndex < 0 || iSpecIndex >= MAX_DUEL_SEPARATORS)
	{
		return;
	}
	// ----
	if(this->g_DuelRooms[iRoom].szSeparators[iSpecIndex] == NULL) 
	{
		return;
	}
	// ----
	if(this->g_DuelRooms[iRoom].szlpObjOne == NULL || this->g_DuelRooms[iRoom].szlpObjTy == NULL)
	{
		return;
	}
	// ----
	PMSG_DUEL_SPEC_ADD pMsg;
	// ----
	pMsg.h.c		= 0xC1;
	pMsg.h.size		= sizeof(pMsg);
	pMsg.h.headcode = 0xAA;
	pMsg.h.subcode	= 0x08;
	// ----
	memcpy(pMsg.szName, this->g_DuelRooms[iRoom].szSeparators[iSpecIndex]->Name, 10);
	// ----
	for(short i = 0; i < MAX_DUEL_SEPARATORS; ++i)
	{
		if(i == iSpecIndex) 
		{
			continue;
		}
		// ----
		if(this->g_DuelRooms[iRoom].szSeparators[i] != NULL)
		{
			DataSend(this->g_DuelRooms[iRoom].szSeparators[i]->m_Index, (BYTE*)&pMsg, pMsg.h.size);
		}
	}

}
// ----------------------------------------------------------------------------------------------------------------
//## Проверяет когда сепаратор заходит выходит;
void DuelSystem::SendSpectatorRemove(short iSpecIndex, int iRoom)
{
	if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
	{
		return;
	}
	// ----
	if(iSpecIndex < 0 || iSpecIndex >= MAX_DUEL_SEPARATORS)
	{
		return;
	}
	// ----
	if(this->g_DuelRooms[iRoom].szSeparators[iSpecIndex] == NULL)
	{
		return;
	}
	// ----
	if(this->g_DuelRooms[iRoom].szlpObjOne == NULL || this->g_DuelRooms[iRoom].szlpObjTy == NULL)
	{
		return;
	}
	// ----
	PMSG_DUEL_SPEC_ADD pMsg;
	// ----
	pMsg.h.c		= 0xC1;
	pMsg.h.size		= sizeof(pMsg);
	pMsg.h.headcode = 0xAA;
	pMsg.h.subcode  = 0x0A;
	// ----
	memcpy(pMsg.szName, this->g_DuelRooms[iRoom].szSeparators[iSpecIndex]->Name, 10);
	// ----
	for(short i = 0; i < MAX_DUEL_SEPARATORS; ++i)
	{
		if(i == iSpecIndex)
		{ 
			continue;
		}
		// ----
		if(this->g_DuelRooms[iRoom].szSeparators[i] != NULL)
		{
			DataSend(this->g_DuelRooms[iRoom].szSeparators[i]->m_Index, (BYTE*)&pMsg, pMsg.h.size);
		}
	}
}
// ----------------------------------------------------------------------------------------------------------------
//## Проверяем количество сепараторов
void DuelSystem::SendSpectatorList(short iRoom)
{
	if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
	{
		return;
	}
	// ----
	if(this->g_DuelRooms[iRoom].RoomFree == FALSE)
	{
		for(short u = 0; u < MAX_DUEL_SEPARATORS; u++)
		{
			if(this->g_DuelRooms[iRoom].szSeparators[u] != NULL)
			{
				this->SendSpectatorList(this->g_DuelRooms[iRoom].szSeparators[u], iRoom);
			}
		}
	}
}
// ----------------------------------------------------------------------------------------------------------------
//## сверяем с клиентом количество сепараторов;
void DuelSystem::SendSpectatorList(LPOBJ lpObj, int iRoom)
{
	if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
	{
		return;
	}
	// ----
	if(this->g_DuelRooms[iRoom].szlpObjOne == NULL || this->g_DuelRooms[iRoom].szlpObjTy == NULL)
	{
		return;
	}
	// ----
	PMSG_DUEL_SPEC_LIST pMsg;
	// ----
	pMsg.h.c		= 0xC1;
	pMsg.h.headcode = 0xAA;
	pMsg.h.subcode	= 0x0B;
	pMsg.btCount	= 0;
	// ----
	if(this->g_DuelRooms[iRoom].RoomFree == FALSE)
	{
		for(short u = 0; u < MAX_DUEL_SEPARATORS; u++)
		{
			if(this->g_DuelRooms[iRoom].szSeparators[u] != NULL)
			{
				memcpy(&pMsg.szName[pMsg.btCount++][0], this->g_DuelRooms[iRoom].szSeparators[u]->Name, 10);
			}
		}
	}
	pMsg.h.size = 5 + (pMsg.btCount * 10);
	// ----
	DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);
}
// ----------------------------------------------------------------------------------------------------------------
//## показываем хп сепараторам;
void DuelSystem::SendLifebarStatus(short iRoom)
{
	if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
	{
		return;
	}
	// ----
	if(this->g_DuelRooms[iRoom].szlpObjOne == NULL || this->g_DuelRooms[iRoom].szlpObjTy == NULL)
	{
		return;
	}
	// ----
	if(this->g_DuelRooms[iRoom].RoomFree == FALSE)
	{
		for(short u = 0; u < MAX_DUEL_SEPARATORS; u++)
		{
			if(this->g_DuelRooms[iRoom].szSeparators[u] != NULL)
			{
				this->SendLifebarStatus(this->g_DuelRooms[iRoom].szSeparators[u], iRoom);
			}
		}
	}
}
// ----------------------------------------------------------------------------------------------------------------
//## показываем хп сепараторам функция;
void DuelSystem::SendLifebarStatus(LPOBJ lpObj, int iRoom)
{
	if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
	{
		return;
	}
	// ----
	if(this->g_DuelRooms[iRoom].szlpObjOne == NULL || this->g_DuelRooms[iRoom].szlpObjTy == NULL)
	{
		return;
	}
	// ----
	PMSG_DUEL_LIFEBAR_REFILL pMsg;
	// ----
	pMsg.h.c		= 0xC1;
	pMsg.h.size		= sizeof(pMsg);
	pMsg.h.headcode = 0xAA;
	pMsg.h.subcode  = 0x05;
	// ----
	pMsg.btObjId01H = HIBYTE(this->g_DuelRooms[iRoom].szlpObjOne->m_Index);
	pMsg.btObjId01L = LOBYTE(this->g_DuelRooms[iRoom].szlpObjOne->m_Index);
	// ----
	pMsg.btObjId02H = HIBYTE(this->g_DuelRooms[iRoom].szlpObjTy->m_Index);
	pMsg.btObjId02L = LOBYTE(this->g_DuelRooms[iRoom].szlpObjTy->m_Index);
	// ----
	pMsg.btLife01 = (int)(this->g_DuelRooms[iRoom].szlpObjOne->Life / ((this->g_DuelRooms[iRoom].szlpObjOne->MaxLife + this->g_DuelRooms[iRoom].szlpObjOne->AddLife) / 100));
	pMsg.btLife02 = (int)(this->g_DuelRooms[iRoom].szlpObjTy->Life / ((this->g_DuelRooms[iRoom].szlpObjTy->MaxLife + this->g_DuelRooms[iRoom].szlpObjTy->AddLife) / 100));
	// ----
	pMsg.btShield01 = this->g_DuelRooms[iRoom].szlpObjOne->iShield / ((this->g_DuelRooms[iRoom].szlpObjOne->iMaxShield + this->g_DuelRooms[iRoom].szlpObjOne->iAddShield) / 100);
	pMsg.btShield02 = this->g_DuelRooms[iRoom].szlpObjTy->iShield / ((this->g_DuelRooms[iRoom].szlpObjTy->iMaxShield + this->g_DuelRooms[iRoom].szlpObjTy->iAddShield) / 100);
	// ----
	DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);

}

// ----------------------------------------------------------------------------------------------------------------
//## показываем хп сепараторам функция;
void DuelSystem::SendLifebarInit(LPOBJ lpObj, int iRoom)
{
	if(iRoom < 0 || iRoom >= MAX_DUEL_ROOMS)
	{
		return;
	}
	// ----
	if(this->g_DuelRooms[iRoom].szlpObjOne == NULL || this->g_DuelRooms[iRoom].szlpObjTy == NULL)
	{
		return;
	}
	// ----
	PMSG_DUEL_LIFEBAR_NAME pMsg2;
	// ----
	pMsg2.h.c		 = 0xC1;
	pMsg2.h.size	 = sizeof(pMsg2);
	pMsg2.h.headcode = 0xAA;
	pMsg2.h.subcode  = 0x07;
	pMsg2.Type		 = 0x00;
	// ----
	memcpy(pMsg2.szName1, this->g_DuelRooms[iRoom].szlpObjOne->Name, 10);
	memcpy(pMsg2.szName2, this->g_DuelRooms[iRoom].szlpObjTy->Name, 10);
	// ----
	pMsg2.btObjId1H = HIBYTE(this->g_DuelRooms[iRoom].szlpObjOne->m_Index);
	pMsg2.btObjId1L = LOBYTE(this->g_DuelRooms[iRoom].szlpObjOne->m_Index);
	// ----
	pMsg2.btObjId2H = HIBYTE(this->g_DuelRooms[iRoom].szlpObjTy->m_Index);
	pMsg2.btObjId2L = LOBYTE(this->g_DuelRooms[iRoom].szlpObjTy->m_Index);
	// ----
	DataSend(lpObj->m_Index, (BYTE*)&pMsg2, pMsg2.h.size);
	// ----
	PMSG_DUEL_LIFEBAR_INIT pMsg;
	// ----
	pMsg.h.c		= 0xC1;
	pMsg.h.size		= sizeof(pMsg);
	pMsg.h.headcode = 0xAA;
	pMsg.h.subcode  = 0x0D;
	// ----
	DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);
}
// ----------------------------------------------------------------------------------------------------------------
//## Процесс убиства игрока
void DuelSystem::KillUserProc(LPOBJ lpObj, LPOBJ lpTarget)
{ 
	if(!this->DuelCheck(lpObj, lpTarget))
	{
		return;
	}
	// ----
	int iDuelRoom = this->GetUserDuelRoom(lpObj);
	// ----
	if(iDuelRoom == -1)
	{
		return;
	}
	// ----
	lpTarget->KillerType = 3;
	// ----
	int Points = ((lpObj == this->g_DuelRooms[iDuelRoom].szlpObjOne) ? this->g_DuelRooms[iDuelRoom].szPointsOne : this->g_DuelRooms[iDuelRoom].szPointsTy);
	// ----
	if(Points >= MAX_DUEL_WIN_POINTS)
	{
		this->g_DuelRooms[iDuelRoom].szWinner = TRUE;
		// ----
		this->SendEndDuel(lpTarget);
		this->SendEndDuel(lpObj);
		// ----
		this->SendEndDuelNotification(lpTarget, lpObj->Name, lpTarget->Name);
		this->SendEndDuelNotification(lpObj, lpObj->Name, lpTarget->Name);
		// ----
		char Buff[256];
		// ----
		wsprintf(Buff,"You emerge triumphant over %s!", lpTarget->Name);
		GCServerMsgStringSend(Buff,lpObj->m_Index,1);
		// ----
		wsprintf(Buff,"%s has defeated you!",lpObj->Name);
		GCServerMsgStringSend(Buff,lpTarget->m_Index,1);
		// ----
		PMSG_SERVERCMD ServerCmd;
		// ----
		PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
		// ----
		ServerCmd.CmdType = 0;
		ServerCmd.X		  = (int)lpObj->X;
		ServerCmd.Y		  = (int)lpObj->Y;
		// ----
		MsgSendV2(lpObj, (unsigned char *)&ServerCmd, sizeof(ServerCmd));
		DataSend(lpObj->m_Index, (unsigned char *)&ServerCmd, sizeof(ServerCmd));
		// ----
		WinnerBuff(lpObj);
		// ----
		this->g_DuelRooms[iDuelRoom].dwTicketCount = GetTickCount() + 10000;
		// ----
		Log.ConsoleOutPut(1, c_Blue,t_Duel,"[Duel System] [%s][%s] Has Won Duel, Looser [%s][%s] Room [%d]",
								lpObj->AccountID, lpObj->Name, lpTarget->AccountID, lpTarget->Name, iDuelRoom+1);
	}
}

// ----------------------------------------------------------------------------------------------------------------
//## Протокол Дуэль системы
void DuelSystem::DuelProtocolCore(LPOBJ lpObj, unsigned char * lpPacket)
{
	PMSG_DEFAULT2* pMsg = (PMSG_DEFAULT2*)lpPacket;
	// ----
	switch(pMsg->subcode)
	{
	case 0x01:
	{
		this->RecvDuelRequest(lpObj, (PMSG_DUEL_REQUEST_START*)lpPacket);
	}
	break;
	// ----
	case 0x02:
	{
		this->RecvDuelAnswer(lpObj, (PMSG_DUEL_ANSWER_START*)lpPacket);
	}
	break;
	// ----
	case 0x07:
	{
		this->RecvWatchRequest(lpObj, (PMSG_DUEL_REQUEST_WATCH*)lpPacket);
	}
	break;
	// ----
	case 0x09:
	{
		if(lpObj->MapNumber == 0x40)
		{
			gObjMoveGate(lpObj->m_Index, 294);
		}
	}
	break;
	// ----
	Run();
	}
}
// ----------------------------------------------------------------------------------------------------------------
//## функция сепаратора для протокола
void DuelSystem::RecvWatchRequest(LPOBJ lpObj, PMSG_DUEL_REQUEST_WATCH* lpMsg)
{
	if(lpObj->m_IfState.use == 0 || lpObj->m_IfState.type != 20) 
	{
		return;
	}
	// ----
	lpObj->m_IfState.use  = 0;
	lpObj->m_IfState.type = 0;
	// ----
	if(lpMsg->btRoomIndex >= 0 && lpMsg->btRoomIndex < MAX_DUEL_ROOMS)
	{
		if(this->g_DuelRooms[lpMsg->btRoomIndex].RoomFree == TRUE) 
		{
			GCServerMsgStringSend("Sorry, but this room is free!", lpObj->m_Index, 1);
			return;
		}
		// ----
		for(short i = 0; i < MAX_DUEL_SEPARATORS; ++i)
		{
			if(this->g_DuelRooms[lpMsg->btRoomIndex].szSeparators[i] == NULL)
			{
				if(gObjMoveGate(lpObj->m_Index, g_DuelGates[lpMsg->btRoomIndex].SeparatorGate))
				{
					this->g_DuelRooms[lpMsg->btRoomIndex].szSeparators[i] = lpObj;
					// ----
					this->SendSpectatorList(lpObj, lpMsg->btRoomIndex);
					// ----
					this->SendSpectatorList(lpMsg->btRoomIndex);
					// ----
					this->SendSpectatorAdd(i, lpMsg->btRoomIndex);
					// ----
					GCServerMsgStringSend("Please sit down and watch this duel. Have fun.", lpObj->m_Index, 1);
					// ----
							if(Config.Duel.Logging)
		{
					Log.ConsoleOutPut(1, c_Blue, t_Duel,"[Duel System][%s][%s] Spectator join to room: [%d]", 
									lpObj->AccountID, lpObj->Name, lpMsg->btRoomIndex + 1);
							}
					// ----
					GCStateInfoSendg(lpObj, 1, 98);
					// ----
					this->SendLifebarInit(lpObj, lpMsg->btRoomIndex);
					// ----
					this->SendLifebarStatus(lpObj, lpMsg->btRoomIndex);
					// ----
					this->UpdateDuelScore(lpMsg->btRoomIndex);
					// ----
					AddTab[lpObj->m_Index].DUEL_SpecVisible = 1;
					// ----
					return;
				}
				GCServerMsgStringSend("Failed to move to Duel Room!", lpObj->m_Index, 1);
				return;
			}
		}
		GCServerMsgStringSend("Sorry, but this room is full!", lpObj->m_Index, 1);
		return;
	}
}
// ----------------------------------------------------------------------------------------------------------------
//## Функция для вызывания дуэли;
void DuelSystem::RecvDuelAnswer(LPOBJ lpObj, PMSG_DUEL_ANSWER_START* lpMsg)
{
	int iDuelIndex = -1;
	// ----
	int aIndex = lpObj->m_Index;
	// ----
	int iDuelRoom = AddTab[aIndex].DUEL_Room;
	// ----
	PMSG_DUEL_START pMsgSend;
	// ----
	pMsgSend.h.c		= 0xC1;
	pMsgSend.h.headcode = 0xAA;
	pMsgSend.h.subcode  = 0x01;
	pMsgSend.bDuelStart = 0;
	pMsgSend.h.size		= sizeof(pMsgSend);
	// ----
	LPOBJ gObjg    = (LPOBJ)OBJECT_POINTER(aIndex);
	// ----
	if(iDuelRoom < 0 || iDuelRoom > MAX_DUEL_ROOMS - 1) 
	{
		return;
	}
	// ----
	if(gObjg->CloseType != -1)
	{
		return;
	}
	// ----
	iDuelIndex = MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL); // aIndex Packet C1 XX AA
	// ----
	OBJECTSTRUCT *gObjs = (OBJECTSTRUCT*)OBJECT_POINTER(iDuelIndex);
	// ----
	if(iDuelIndex <= 7999 || lpObj->m_Index <= 7999)
	{
		return;
	}
	// ----
	if(OBJECT_MAXRANGE(iDuelIndex))
	{
		if(!Utilits.gObjIsConnected(iDuelIndex))
		{
			return;
		}
		// ----
		if(gObjs->Type == OBJECT_MONSTER)
		{
			return;
		}
		// ----
		if(gObjs->CloseCount >= 0)
		{
			return;
		}
		// ----
		if(lpMsg->bDuelOK)
		{
			if((gObjs->MapNumber >= 11 && gObjs->MapNumber <= 17) || gObjs->MapNumber == 52  || (gObjs->MapNumber >= 18 &&
				gObjs->MapNumber <= 23) || gObjs->MapNumber == 53 ||  gObjs->MapNumber == 9 || gObjs->MapNumber == 32 || 
				(gObjs->MapNumber >= 45 && gObjs->MapNumber <= 50))
			{
				GCServerMsgStringSend("Duels are not allowed in event maps.", lpObj->m_Index, 1);
				// ----
				this->RoomReset(iDuelRoom, true, true);
				// ----
				memcpy(pMsgSend.szName, lpObj->Name, sizeof(pMsgSend.szName));
				// ----
				DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
				// ----
				return;
			}
		}
		// ----
		if(OBJECT_MAXRANGE(lpObj->m_iDuelUser))
		{
			GCServerMsgStringSend("You are already in a Duel.", lpObj->m_Index, 1);
			GCServerMsgStringSend("In order to issue a Duel, cancel the previous request.", lpObj->m_Index, 1);
			// ----
			this->RoomReset(iDuelRoom, true, true);
			// ----
			memcpy(pMsgSend.szName, lpObj->Name, sizeof(pMsgSend.szName));
			// ----
			DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
			// ----
			return;
		}
		// ----
		if(OBJECT_MAXRANGE(lpObj->m_iDuelUserReserved))
		{
			GCServerMsgStringSend("You are already issuing a Duel challenge.", lpObj->m_Index, 1);
			// ----
			this->RoomReset(iDuelRoom, true, true);
			// ----
			memcpy(pMsgSend.szName, lpObj->Name, sizeof(pMsgSend.szName));
			// ----
			DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
			// ----
			return;
		}
		if(gObjs->m_iDuelUserReserved == lpObj->m_Index)
		{
			char szDuelName[MAX_ACCOUNT_LEN + 1]  = {0};
			char szDuelName2[MAX_ACCOUNT_LEN + 1] = {0};
			// ----
			memcpy(szDuelName, gObjs->Name, MAX_ACCOUNT_LEN);
			// ----
			szDuelName[MAX_ACCOUNT_LEN] = 0;
			// ----
			memcpy(szDuelName2, lpMsg->szName, MAX_ACCOUNT_LEN);
			// ----
			szDuelName2[MAX_ACCOUNT_LEN] = 0;
			// ----
			if(!strcmp(szDuelName, szDuelName2))
			{
				if(lpMsg->bDuelOK == false)
				{
					this->RoomReset(iDuelRoom, true, true);
					// ----
					pMsgSend.bDuelStart = 0x0F;
					// ----
					memcpy(pMsgSend.szName, lpObj->Name, sizeof(pMsgSend.szName));
					// ----
					DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
				}
				// ----
				else if (lpMsg->bDuelOK == true)
				{
					if(gObjMoveGate(lpObj->m_Index, g_DuelGates[iDuelRoom].Gate01) == false)
					{
						this->RoomReset(iDuelRoom, true, true);
						return;
					}
					// ----
					if(gObjMoveGate(iDuelIndex, g_DuelGates[iDuelRoom].Gate02) == false)
					{
						this->RoomReset(iDuelRoom, true, true);
						return;
					}
					// ----
					gObjs->m_iDuelUserReserved	= -1;
					gObjs->m_btDuelScore		= 0;
					gObjs->m_iDuelUser			= lpObj->m_Index;
					gObjs->m_iDuelTickCount		= GetTickCount();
					// ----
					this->g_DuelRooms[iDuelRoom].dwStartTime	= GetTickCount();
					this->g_DuelRooms[iDuelRoom].dwTicketCount  = GetTickCount() + (MAX_DUEL_TIME * 60000);
					// ----
					lpObj->m_iDuelUserRequested = -1;
					lpObj->m_iDuelUserReserved  = -1;
					lpObj->m_btDuelScore		= 0;
					lpObj->m_iDuelUser			= iDuelIndex;
					lpObj->m_iDuelTickCount		= GetTickCount();
					// ----
					this->g_DuelRooms[iDuelRoom].RoomFree		= FALSE;
					this->g_DuelRooms[iDuelRoom].DuelWaiting	= FALSE;
					this->g_DuelRooms[iDuelRoom].szWinner		= FALSE;
					// ----
					pMsgSend.bDuelStart		= 0;
					pMsgSend.NumberH		= SET_NUMBERH(iDuelIndex);
					pMsgSend.NumberL		= SET_NUMBERL(iDuelIndex);
					// ----
					memcpy(pMsgSend.szName, szDuelName, sizeof(pMsgSend.szName));
					// ----
					DataSend(lpObj->m_Index, (LPBYTE)&pMsgSend, pMsgSend.h.size);
					// ----
					pMsgSend.NumberH		= SET_NUMBERH(lpObj->m_Index);
					pMsgSend.NumberL		= SET_NUMBERL(lpObj->m_Index);
					// ----
					memcpy(pMsgSend.szName, lpObj->Name, sizeof(pMsgSend.szName));
					// ----
					DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
					// ----
					this->UpdateDuelScore(iDuelRoom);
					// ----
					//Chat.MessageAllLog(0, 0, c_Cyan, t_Duel, lpObj, "[Duel System] Duel Started [%s] VS [%s] on Room[%d]", lpObj->Name, gObjs->Name, iDuelRoom + 1);

					Log.ConsoleOutPut(1, c_Blue,t_Duel,"[Duel System] Duel Started [%s][%s] VS [%s][%s] on Room[%d]",
											lpObj->AccountID, lpObj->Name, gObjs->AccountID, gObjs->Name, iDuelRoom + 1);
				}
			}
			else
			{
				this->RoomReset(iDuelRoom);
				DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
				return;
			}
		}
		else
		{
			this->RoomReset(iDuelRoom);
			DataSend(iDuelIndex, (LPBYTE)&pMsgSend, pMsgSend.h.size);
			return;
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------
//## Функция Сервера для дуэль системы для клиента;
void DuelSystem::RecvDuelRequest(LPOBJ lpObj, PMSG_DUEL_REQUEST_START* lpMsg)
{
	int iDuelIndex = MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL);
	// ----
	OBJECTSTRUCT *gObjs = (OBJECTSTRUCT*)OBJECT_POINTER(iDuelIndex);
	// ----
	if(!OBJECT_MAXRANGE(iDuelIndex))
	{
		Log.ConsoleOutPut(1, c_Blue, t_Duel,"[Duel System] [%s][%s] Try duel with NO_PLAYER object!", lpObj->AccountID, lpObj->Name);
		return;
	}
	// ----
	if(iDuelIndex == lpObj->m_Index)
	{
		return;
	}
	// ----
	if(iDuelIndex <= 7999 || lpObj->m_Index <= 7999)
	{
		return;
	}
	// ----
	char Buff[256];
	// ----
	if(lpObj->CloseType != -1)
	{
		return;
	}
	// ----
	if(GetPrivateProfileInt("GameServerInfo", "NonPK", 0 , GS_CONFIG_FILE) == 1)
	{
		GCServerMsgStringSend("Dueling is not allowed in NON-PK servers.", lpObj->m_Index, 1);
		return;
	}
	// ----
	if(GetPrivateProfileInt("GameServerInfo","PkLimitFree", 1, GS_CONFIG_FILE) == 0)
	{
		if(lpObj->m_PK_Level >= 6)
		{
			GCServerMsgStringSend("An outlaw can't issue a Duel challenge.", lpObj->m_Index, 1);
			return;
		}
		// ----
		if(gObjs->m_PK_Level >= 6)
		{
			GCServerMsgStringSend("You cannot Duel with an Outlaw.", lpObj->m_Index, 1);
			return;
		}
	}
	// ----
	if(OBJECT_MAXRANGE(lpObj->m_iDuelUser))
	{
		GCServerMsgStringSend("You are already in a Duel.", lpObj->m_Index, 1);
		GCServerMsgStringSend("In order to issue a Duel, cancel the previous request.", lpObj->m_Index, 1);
		return;
	}
	// ----
	if(gObjs->MapNumber == 9 || gObjs->MapNumber == 32)
	{
		GCServerMsgStringSend("A duel is not allowed in Devil Square.", lpObj->m_Index, 1);
		return;
	}
	// ----
	if((gObjs->MapNumber >= 11 && gObjs->MapNumber <= 17) || gObjs->MapNumber == 52)
	{
		GCServerMsgStringSend("You cannot Duel inside Blood Castle.", lpObj->m_Index, 1);
		return;
	}
	// ----
	if((gObjs->MapNumber >= 18 && gObjs->MapNumber <= 23) || gObjs->MapNumber == 53)
	{
		GCServerMsgStringSend("Duels are not allowed within Chaos Castle.", lpObj->m_Index, 1);
		return;
	}
	// ----
	if((gObjs->MapNumber >= 45 && gObjs->MapNumber <= 50))
	{
		GCServerMsgStringSend("Duels are not allowed in Illusion Temple", lpObj->m_Index, 1);
		return;
	}
	// ----
	if(lpObj->Level < 30 || gObjs->Level < 30)
	{
		PMSG_DUEL_START pMsgSend;
		// ----
		pMsgSend.h.c		= 0xC1;
		pMsgSend.h.headcode = 0xAA;
		pMsgSend.h.subcode  = 0x01;
		pMsgSend.bDuelStart = 0x0C;
		pMsgSend.h.size		= sizeof(pMsgSend);
		// ----
		DataSend(lpObj->m_Index, (BYTE*)&pMsgSend, pMsgSend.h.size);
		// ----
		return;
	}
	// ----
	if(lpObj->Money < 30000 || gObjs->Money < 30000)
	{
		PMSG_DUEL_START pMsgSend;
		// ----
		pMsgSend.h.c		= 0xC1;
		pMsgSend.h.headcode = 0xAA;
		pMsgSend.h.subcode  = 0x01;
		pMsgSend.bDuelStart = 0x1e;
		pMsgSend.h.size		= sizeof(pMsgSend);
		// ----
		DataSend(lpObj->m_Index, (BYTE*)&pMsgSend, pMsgSend.h.size);
		// ----
		return;
	}
	// ----
	int iDuelRoom = this->GetFreeRoomIndex();
	// ----
	if(iDuelRoom == -1)
	{
		PMSG_DUEL_START pMsgSend;
		// ----
		pMsgSend.h.c		= 0xC1;
		pMsgSend.h.headcode = 0xAA;
		pMsgSend.h.subcode  = 0x01;
		pMsgSend.bDuelStart = 0x10;
		pMsgSend.h.size		= sizeof(pMsgSend);
		// ----
		DataSend(lpObj->m_Index, (BYTE*)&pMsgSend, pMsgSend.h.size);
		// ----
		return;
	}
	// ----
	if((GetTickCount() - gObjs->m_PacketCheckTime) < 300)
	{
		return;
	}
	// ----
	lpObj->m_PacketCheckTime = GetTickCount();
	// ----
	char szDuelName[MAX_ACCOUNT_LEN + 1]  = {0};
	char szDuelName2[MAX_ACCOUNT_LEN + 1] = {0};
	// ----
	memcpy(szDuelName, gObjs->Name, MAX_ACCOUNT_LEN);
	// ----
	szDuelName[MAX_ACCOUNT_LEN]  = 0;
	// ----
	memcpy(szDuelName2, lpMsg->szName, MAX_ACCOUNT_LEN);
	// ----
	szDuelName2[MAX_ACCOUNT_LEN] = 0;
	// ----
	if(strcmp(szDuelName, szDuelName2))
	{
		return;
	}
	// ----
	if(this->IsDuelEnable(iDuelIndex) == FALSE)
	{
		GCServerMsgStringSend("Your challenge to Duel has been refused.", lpObj->m_Index, 1);
		return;
	}
	// ----
	if(lpObj->lpGuild && lpObj->lpGuild->WarState == 1)
	{
		GCServerMsgStringSend("You cannot challenge someone to a duel while in a guild war.", lpObj->m_Index, 1);
		return;
	}
	// ----
	if(gObjs->lpGuild && gObjs->lpGuild->WarState == 1)
	{
		GCServerMsgStringSend("Your opponent cannot duel while in a guild war.", lpObj->m_Index, 1);
		return;
	}
	// ----
	if(Utilits.gObjIsConnected(iDuelIndex) == FALSE)
	{
		return;
	}
	// ----
	if(gObjs->Type == OBJECT_MONSTER)
	{
		return;
	}
	// ----
	if(gObjs->CloseCount >= 0)
	{
		return;
	}
	// ----
	for(int n = 0; n < 5; n++)
	{
		if(lpObj->SelfDefense[n] >= 0 || gObjs->SelfDefense[n] >= 0)
		{
			GCServerMsgStringSend("Self-defense is active. You cannot Duel.", lpObj->m_Index, 1);
			return;
		}
	}
	// ----
	if(lpObj->m_IfState.use > 0)
	{
		GCServerMsgStringSend("You cannot Duel while trading.", lpObj->m_Index, 1);
		return;
	}
	// ----
	if(gObjs->m_IfState.use > 0)
	{
		wsprintf(Buff, "%s is trading an item.", gObjs->Name);
		// ----
		GCServerMsgStringSend(Buff, lpObj->m_Index, 1);
		// ----
		return;
	}
	// ----
	if(OBJECT_MAXRANGE(gObjs->m_iDuelUserRequested))
	{
		wsprintf(Buff,"%s has already accepted a challenge to Duel.", gObjs->Name);
		// ----
		GCServerMsgStringSend(Buff, lpObj->m_Index, 1);
		// ----
		return;
	}
	// ----
	if(OBJECT_MAXRANGE(gObjs->m_iDuelUserReserved))
	{
		wsprintf(Buff, "%s issues a Duel challenge.", gObjs->Name);
		// ----
		GCServerMsgStringSend(Buff, lpObj->m_Index, 1);
		// ----
		return;
	}
	// ----
	if(OBJECT_MAXRANGE(gObjs->m_iDuelUser))
	{
		wsprintf(Buff, "%s is in a Duel.", gObjs->Name);
		// ----
		GCServerMsgStringSend(Buff, lpObj->m_Index, 1);
		// ----
		return;
	}
	// ----
	lpObj->m_iDuelUser						 = -1;
	lpObj->m_iDuelUserReserved				 = iDuelIndex;
	gObjs->m_iDuelUserRequested				 = lpObj->m_Index;
	int aIndex								 = lpObj->m_Index;
	// ----
	AddTab[aIndex].DUEL_Room	 = iDuelRoom;
	int uIndex								 = gObjs->m_Index;
	AddTab[uIndex].DUEL_Room	 = iDuelRoom;
	// ----
	this->g_DuelRooms[iDuelRoom].szlpObjOne  = lpObj;
	this->g_DuelRooms[iDuelRoom].szlpObjTy   = gObjs;
	this->g_DuelRooms[iDuelRoom].DuelWaiting = TRUE;
	// ----
	PMSG_DUEL_QUESTION_START pMsg;
	// ----
	pMsg.h.c			= 0xC1;
	pMsg.h.headcode		= 0xAA;
	pMsg.h.subcode		= 0x02;
	pMsg.h.size			= sizeof(pMsg);
	pMsg.NumberH		= SET_NUMBERH(lpObj->m_Index);
	pMsg.NumberL		= SET_NUMBERL(lpObj->m_Index);
	// ----
	memcpy(pMsg.szName, lpObj->Name, sizeof(pMsg.szName));
	// ----
	DataSend(iDuelIndex, (LPBYTE)&pMsg, pMsg.h.size);
	// ----
	wsprintf(Buff, "Challenged %s to a Duel.", gObjs->Name);
	// ----
	GCServerMsgStringSend(Buff, lpObj->m_Index, 1);
	// ----
			if(Config.Duel.Logging)
		{
	Log.ConsoleOutPut(1, c_Blue, t_Duel,"[Duel System][%s][%s] Requested to Start Duel to [%s][%s] on Room [%d]",
							lpObj->AccountID, lpObj->Name, gObjs->AccountID, gObjs->Name, iDuelRoom + 1);
			}
}
// ----------------------------------------------------------------------------------------------------------------
//## Смотрим если дуэль в рабочем виде;
bool DuelSystem::IsDuelEnable(int aIndex)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
	// -----
	if(OBJECT_MAXRANGE(aIndex) == FALSE)
	{
		return false;
	}
	// ----
	if(Utilits.gObjIsConnected(aIndex) == TRUE)
	{
		if((gObj->m_Option & 2) == 2)
		{
			return true;
		}
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------------------------
//## Добовляем опции;
void DuelSystem::SetDuelOption(int lpObj, BOOL bState)
{
	OBJECTSTRUCT * gObj = (OBJECTSTRUCT*)OBJECT_POINTER(lpObj);
	// ----
	if(Utilits.gObjIsConnected(lpObj) == TRUE)
	{
		if(bState == 0)
		{
			gObj->m_Option = 0;
		}
		// ----
		else
		{
			gObj->m_Option |= 2;
		}
	}
}
// ----------------------------------------------------------------------------------------------------------------
//## Проверяем если в дуэли
bool DuelSystem::IsOnDuel(int lpObj)
{
 bool bResult = false;
 // ----
 for(short i = 0; i < MAX_DUEL_ROOMS; i++)
 {
  DUEL_ROOM room = this->g_DuelRooms[i];

 if ((room.szlpObjOne != NULL && room.szlpObjOne->m_Index == lpObj) 
|| (room.szlpObjTy != NULL && room.szlpObjTy->m_Index == lpObj))
     {
         if(!room.DuelWaiting)
         bResult = true;
         // ----
        break;
     }
 }
 // ----
 return bResult;
}
// ----------------------------------------------------------------------------------------------------------------
//## Проверяем если в дуэли 2
bool DuelSystem::IsOnDuel2(int lpObj, int lpObj2)
{
 for(short i = 0; i < MAX_DUEL_ROOMS; i++)
 {
  DUEL_ROOM room = this->g_DuelRooms[i];
  // ----
  if(!room.RoomFree)
  {
   if (room.szlpObjOne != NULL && room.szlpObjOne->m_Index == lpObj)
   {
    if (room.szlpObjTy != NULL && room.szlpObjTy->m_Index == lpObj2)
    {
     return true;
    }
   }
   
   if (room.szlpObjOne != NULL && room.szlpObjOne->m_Index == lpObj2)
   {
    if (room.szlpObjTy != NULL && room.szlpObjTy->m_Index == lpObj)
    {
     return true;
    }
   }
  }
 }
 
 return false;
}
// ----------------------------------------------------------------------------------------------------------------
//## Добовляем баф винеру;
void DuelSystem::WinnerBuff(LPOBJ lpObj)
{
	if(Utilits.gObjIsConnected(lpObj->m_Index))
	{
		AddBuff(lpObj, 103, 20, 10, 0, 0, 3600);
		// ----
				if(Config.Duel.Logging)
		{
		Log.ConsoleOutPut(1, c_Blue, t_Duel,"[Duel System] Winner : [%s][%s] received a Gladiator Glory Buff",
								lpObj->AccountID, lpObj->Name);
				}
	}
}
// ----------------------------------------------------------------------------------------------------------------
//## для выхода сепараторов;
bool DuelSystem::IsSpectacor(short Index)
{
	for(short a = 0; a < MAX_DUEL_ROOMS; a++) 
	// ----
	for(short i = 0; i < MAX_DUEL_SEPARATORS; ++i)
	// ----
	if(this->g_DuelRooms[i].RoomFree == FALSE)
	{
		if(this->g_DuelRooms[a].szSeparators[i] != NULL)
		if(this->g_DuelRooms[a].szSeparators[i]->m_Index == Index)
		{
			return true;
		}
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------------------------
//## проверка для появления;
void DuelSystem::RespawnDuelers(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if(lpObj->MapNumber != 0x40 && lpTargetObj->MapNumber != 0x40)
	{
		return;
	}
}
// ----------------------------------------------------------------------------------------------------------------
//## результат проверки дуэля;
bool DuelSystem::DuelCheck(LPOBJ lpObj)
{ 
	return this->IsOnDuel(lpObj->m_Index); 
}
// ----------------------------------------------------------------------------------------------------------------
//## Результат проверки дуэля 2;
bool DuelSystem::DuelCheck(LPOBJ lpObj, LPOBJ lpObj2) 
{ 
	return this->IsOnDuel2(lpObj->m_Index, lpObj2->m_Index); 
}
// ----------------------------------------------------------------------------------------------------------------
//## отменя дуэля;
void DuelSystem::SendRefuseDuel(LPOBJ lpObj)
{ 
	if(lpObj == NULL)
	{
		return;
	}
	// ----
	PMSG_DUEL_START pMsgSend;
	// ----
	pMsgSend.h.c	= 0xC1;
	pMsgSend.h.headcode = 0xAA;
	pMsgSend.h.subcode = 0x01;
	pMsgSend.bDuelStart = 0x0F;
	pMsgSend.h.size = sizeof(pMsgSend);
	// ----
	DataSend(lpObj->m_Index, (BYTE*)&pMsgSend, pMsgSend.h.size);
}
// ----------------------------------------------------------------------------------------------------------------

bool HookSetDuelOption(int lpObj, BOOL bState)
{
	g_DuelSystem.SetDuelOption(lpObj, bState);
	return true;
}
// --------------------------------------------------------------------------------------------
bool HookIsDuelEnable(int aIndex)
{
	if(!g_DuelSystem.IsDuelEnable(aIndex))
	{
		return false;
	}
	else 
	{
		return true;
	}
}
// --------------------------------------------------------------------------------------------

bool HookIsOnDuel(int lpObj, int lpObj2) 
{
	if(!g_DuelSystem.IsOnDuel2(lpObj, lpObj2))
	{
		return false;
	}
	else 
	{
		return true;
	}
}
// --------------------------------------------------------------------------------------------

bool HookDuelCheck1(LPOBJ lpObj)
{ 
    bool bResult = false;
    // ----
    if(lpObj->Type == OBJECT_USER)
    {                                   
        if(g_DuelSystem.DuelCheck(lpObj)) 
            bResult = true;
        else
            bResult = goBjHoookLoad1(lpObj);
    }                
    return bResult;
}
// --------------------------------------------------------------------------------------------

bool HookDuelCheck2(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	bool cResult = false;
	// ----
	if(lpObj->Type == OBJECT_USER || lpTargetObj->Type == OBJECT_USER)
	{													
		if(g_DuelSystem.DuelCheck(lpObj, lpTargetObj))
			cResult = true;
		else
			goBjHoookLoad2(lpObj, lpTargetObj);
	}							
	return cResult;
}
// --------------------------------------------------------------------------------------------

void GSgObjUserDie(OBJECTSTRUCT *lpObj, OBJECTSTRUCT *lpTargetObj)
{
	if(lpObj->Type == OBJECT_USER && lpTargetObj->Type == OBJECT_USER ) 
	{
		if(g_DuelSystem.DuelCheck(lpObj, lpTargetObj))
		{
			int aIndex = lpObj->m_Index;
			int DuelRoom = AddTab[aIndex].DUEL_Room;
			g_DuelSystem.PlayerScore(lpTargetObj);
			g_DuelSystem.KillUserProc(lpTargetObj,lpObj);
			return;
		}
	}						  
	gObjUserDie(lpObj, lpTargetObj);
}
// --------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------------
// This Function For Set Duel Info in Game;
void DuelSystem::DuelSetInfo(int aIndex)
{
    // ----
    OBJECTSTRUCT * lpObj = (OBJECTSTRUCT*)OBJECT_POINTER(aIndex);
    // ----
    if(SetDuelState(aIndex, lpObj->AccountID, lpObj->Name) == FALSE)
    {
        AddTab[aIndex].DUEL_Wins = 0;
        AddTab[aIndex].DUEL_Lose = 0;
        AddTab[aIndex].DUEL_AllDuels = 0;
        // ----
        Log.ConsoleOutPut(1, c_Green, t_Duel, "[Duel System] Character [%s] Duels: [%d] Wins: [%d] Loses: [%d]", 
                                lpObj->Name, AddTab[aIndex].DUEL_AllDuels, AddTab[aIndex].DUEL_Wins,
                                AddTab[aIndex].DUEL_Lose);
    }
    else
    {
        Log.ConsoleOutPut(1, c_Green, t_Duel, "[Duel System] Character [%s] Duels: [%d] Wins: [%d] Loses: [%d]",
                                 lpObj->Name, AddTab[aIndex].DUEL_AllDuels, AddTab[aIndex].DUEL_Wins,
                                 AddTab[aIndex].DUEL_Lose);
    }
}
// --------------------------------------------------------------------------------------------

void DuelSystem::SaveDuel(char FirstAcc[11], char FirstName[11], char SecondAcc[11], char SecondName[11], int Point1, int Point2)
{
	MySQL.Execute("UPDATE Character SET DuelWins=DuelWins+1, DuelLoses=DuelLoses, LastDuel = GETDATE(),DuelsTotal = DuelsTotal+1 WHERE AccountID = '%s' AND Name = '%s'",FirstAcc, FirstName);
	MySQL.Execute("UPDATE Character SET DuelWins=DuelWins, DuelLoses=DuelLoses+1, LastDuel = GETDATE(),DuelsTotal = DuelsTotal+1 WHERE AccountID = '%s' AND Name = '%s'",SecondAcc, SecondName);
}

bool DuelSystem::SetDuelState(int aIndex, char AccountID[11], char Name[11])
{	
	MySQL.Execute("SELECT DuelWins FROM Character WHERE AccountID = '%s' AND Name = '%s'", AccountID, Name);
	int Wins = MySQL.GetInt();
	MySQL.Execute("SELECT DuelLoses FROM Character WHERE AccountID = '%s' AND Name = '%s'", AccountID, Name);
	int Lose = MySQL.GetInt();
	int All = Wins+Lose;
	AddTab[aIndex].DUEL_Wins = Wins;
	AddTab[aIndex].DUEL_Lose = Lose;
	AddTab[aIndex].DUEL_AllDuels = All;
	return true;
}
#endif