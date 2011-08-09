// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.0								# //
// ================================================== //

#include "User.h"

#ifndef PROTOC_H
#define PROTOC_H	   								

bool ProtocolCore (BYTE protoNum, LPBYTE aRecv, DWORD aLen, int aIndex, DWORD Encrypt, int Serial);
void ProtocolCoreSend(int aIndex,unsigned char* aSend, int aLen);

class cProtoFunc
{
public:
	bool NPCTalkEx(LPOBJ gObj, int NpcId);
	void PlayerConnect(LPOBJ gObj); 
	void CheckRingSend(LPOBJ gObj, LPBYTE aRecv);	
	void CheckRing(LPOBJ gObj, LPBYTE aRecv);
private:			
	void LoginMsg(LPOBJ gObj);
	void RingSkin(LPOBJ gObj);
	void PkClear(LPOBJ gObj, LPOBJ NpcObj);
};
extern cProtoFunc Protocol;
#endif