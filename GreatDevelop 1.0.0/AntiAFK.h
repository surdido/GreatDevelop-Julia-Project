// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Tornado Lite - 7.12.XX					# //
// ================================================== //

#ifndef AntiAFK_H
#define AntiAFK_H

#include "User.h"
class cAntiAFK
{
public:
	cAntiAFK();
	~cAntiAFK();
	void SendInfo(LPOBJ gObj);
	void Load();
private:
	int ArrayMap[64];
	int ReWarning;
};

extern cAntiAFK AntiAFK;

#endif