#include "StdAfx.h"

#ifndef PRODEF_H
#define PRODEF_H
					 
#pragma once
#define MAKE_NUMBERW(x,y)  ( (WORD)(((BYTE)((y)&0xFF)) |   ((BYTE)((x)&0xFF)<<8 ))  ) 
#define SET_NUMBERH(x) ( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x) ( (BYTE)((DWORD)(x) & 0xFF) )

#ifndef MAX_ACCOUNT_LEN
	#define MAX_ACCOUNT_LEN	10
	#define MAX_GUILD_LEN	8
#endif

#define OBJECT_MAXRANGE(aIndex) ( ((aIndex) < 0 )?FALSE:( (aIndex) > OBJECT_MAX -1 )?FALSE:TRUE   )
			   		  
void BuxConvert(char* buf, int size);
			  
void PHeadSetB(LPBYTE lpBuf, BYTE head, int size);

void PHeadSubSetB(LPBYTE lpBuf, BYTE head, BYTE sub, int size);
// ADVANCE DEVIRVATED
struct PBMSG_HEAD	// Packet - Byte Type
{
public:
	void set ( LPBYTE lpBuf, BYTE head, BYTE size)	// line : 18
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};	// line : 22

	void setE ( LPBYTE lpBuf, BYTE head, BYTE size)	// line : 25
	{
		lpBuf[0] = 0xC3;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};	// line : 29

	BYTE c;
	BYTE size;
	BYTE headcode;
}; 

struct PBMSG_HEAD2	// Packet - Byte Type
{

public:

	void set( LPBYTE lpBuf, BYTE head, BYTE sub, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
		lpBuf[3] = sub;
	};

	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};

struct PMSG_DEFAULT2
{
	PBMSG_HEAD h;
	BYTE subcode;
};

struct PWMSG_HEAD	// Packet - Word Type
{
public:

	void set( LPBYTE lpBuf, BYTE head, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};

	void setE( LPBYTE lpBuf, BYTE head, int size)	// line : 49
	{
		lpBuf[0] = 0xC4;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};

	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
};

struct PMSG_SEND_WINDOW
{
	BYTE uHead;
	BYTE uSize;
	BYTE uPacketType;
	BYTE uNum;
}; 

struct PMSG_SERVERCMD
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	BYTE CmdType;	// 4
	BYTE X;	// 5
	BYTE Y;	// 6
};	 
							   							 
struct PMSG_CLIENTCLOSE
{
	PBMSG_HEAD h;
	BYTE SubCode;	// 3
	BYTE Flag;	// 4
};			
						
#endif