// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.1								# //
// ================================================== //

#include "stdafx.h"
#include "Maps.h"
#include "Utilits.h"
#include "Configs.h"
cMaps Maps;	  

cMaps::cMaps()
{
}

cMaps::~cMaps()
{
}

char MapAttrName[65][24] =
{
	"..\\data\\Terrain1.att",
	"..\\data\\Terrain2.att",
	"..\\data\\Terrain3.att",
	"..\\data\\Terrain4.att",
	"..\\data\\Terrain5.att",
	"..\\data\\Terrain6.att",
	"..\\data\\Terrain7.att",
	"..\\data\\Terrain8.att",
	"..\\data\\Terrain9.att",
	"..\\data\\Terrain10.att",
	"..\\data\\Terrain11.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain25.att",
	"..\\data\\Terrain31.att",
	"..\\data\\Terrain32.att",
	"..\\data\\Terrain33.att",
	"..\\data\\Terrain34.att",
	"..\\data\\Terrain35.att",
	"..\\data\\Terrain36.att",
	"..\\data\\Terrain37.att",
	"..\\data\\Terrain38.att",
	"..\\data\\Terrain39.att",
	"..\\data\\Terrain40.att",
	"..\\data\\Terrain41.att",
	"..\\data\\Terrain42.att",
	"..\\data\\Terrain43.att",
	"..\\data\\Terrain43.att",
	"..\\data\\Terrain43.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain46.att",
	"..\\data\\Terrain52.att",
	"..\\data\\Terrain12.att",
	"..\\data\\Terrain19.att",
	"..\\data\\Terrain1.att",
	"..\\data\\Terrain1.att",
	"..\\data\\Terrain57.att",
	"..\\data\\Terrain58.att",
	"..\\data\\Terrain59.att",
	"..\\data\\Terrain59.att",
	"..\\data\\Terrain59.att",
	"..\\data\\Terrain59.att",
	"..\\data\\Terrain63.att",
	"..\\data\\Terrain64.att",
	"..\\data\\Terrain65.att",
};
#ifdef _GS
void cMaps::MapInit()
{
	BYTE NumMaps = 65;

	Utilits.SetByte(0x0059F133+2,NumMaps); // MapServ info max map change

	Utilits.SetByte(0x0050AD29,0xE9);
	Utilits.SetByte(0x0050AD2A,0xA2);
	Utilits.SetByte(0x0050AD2B,0x01);
	Utilits.SetByte(0x0050AD2C,0x00);
	Utilits.SetByte(0x0050AD2D,0x00);
	Utilits.SetByte(0x0050AD2E,0x90);

	Utilits.SetByte(0x005692F3+1,NumMaps);
	Utilits.SetByte(0x0056935E+1,NumMaps);

	Utilits.SetByte(0x0056A3BB,0xE9);
	Utilits.SetByte(0x0056A3BC,0x81);
	Utilits.SetByte(0x0056A3BD,0x0D);
	Utilits.SetByte(0x0056A3BE,0x00);
	Utilits.SetByte(0x0056A3BF,0x00);
	Utilits.SetByte(0x0056A3C0,0x89);

	Utilits.SetByte(0x0056B153+3,NumMaps);

	Utilits.SetByte(0x0056B177,0x81);
	Utilits.SetByte(0x0056B178,0xC2);
	Utilits.SetByte(0x0056B179,0x24);
	Utilits.SetByte(0x0056B17A,0x28);
	Utilits.SetByte(0x0056B17B,0x78);
	Utilits.SetByte(0x0056B17C,0x00);
	Utilits.SetByte(0x0056B17D,0x90);
	Utilits.SetByte(0x0056B17E,0x90);
	Utilits.SetByte(0x0056B17F,0x90);
	Utilits.SetByte(0x0056B180,0x90);
	Utilits.SetByte(0x0056B181,0x90);
	Utilits.SetByte(0x0056B182,0x90);
	Utilits.SetByte(0x0056B183,0x90);
	Utilits.SetByte(0x0056B184,0x90);
	Utilits.SetByte(0x0056B185,0x90);
	Utilits.SetByte(0x0056B186,0x90);
	Utilits.SetByte(0x0056B187,0x90);
	Utilits.SetByte(0x0056B188,0x90);
	Utilits.SetByte(0x0056B189,0x52);

	Utilits.SetByte(0x0059F9F9,0xEB);

	*(DWORD*)(0x0056B177+2) = (DWORD)&MapAttrName;

	Utilits.SetByte(0x0056B174+2,24);
	Utilits.SetByte(0x00503282+2,NumMaps);
	Utilits.SetByte(0x004B6C3F+3,NumMaps);
	Utilits.SetByte(0x0053A0A7+3,NumMaps);
	Utilits.SetByte(0x0053A0D7+3,NumMaps);
	Utilits.SetByte(0x0052D011+3,NumMaps);
	Utilits.SetByte(0x00430529+3,NumMaps);
	Utilits.SetByte(0x0043D05F+3,NumMaps);
}
#endif

#ifdef _GS_CS

void cMaps::MapInit()
{
	BYTE NumMaps = 65;

	Utilits.SetByte(0x005D5FC3+2,NumMaps); // MapServ info max map change

	Utilits.SetByte(0x0051C7C9,0xE9);
	Utilits.SetByte(0x0051C7CA,0xA2);
	Utilits.SetByte(0x0051C7CB,0x01);
	Utilits.SetByte(0x0051C7CC,0x00);
	Utilits.SetByte(0x0051C7CD,0x00);
	Utilits.SetByte(0x0051C7CE,0x90);

	Utilits.SetByte(0x0057C223+1,NumMaps);
	Utilits.SetByte(0x0057C28E+1,NumMaps);

	Utilits.SetByte(0x0057D349,0xE9);
	Utilits.SetByte(0x0057D34A,0x81);
	Utilits.SetByte(0x0057D34B,0x0D);
	Utilits.SetByte(0x0057D34C,0x00);
	Utilits.SetByte(0x0057D34D,0x00);
	Utilits.SetByte(0x0057D34E,0x89);

	Utilits.SetByte(0x0057E0E1+3,NumMaps);

	Utilits.SetByte(0x0057E105,0x81);
	Utilits.SetByte(0x0057E106,0xC2);
	Utilits.SetByte(0x0057E107,0x58);
	Utilits.SetByte(0x0057E108,0x6F);
	Utilits.SetByte(0x0057E109,0x7D);
	Utilits.SetByte(0x0057E10A,0x00);
	Utilits.SetByte(0x0057E10B,0x90);
	Utilits.SetByte(0x0057E10C,0x90);
	Utilits.SetByte(0x0057E10D,0x90);
	Utilits.SetByte(0x0057E10E,0x90);
	Utilits.SetByte(0x0057E10F,0x90);
	Utilits.SetByte(0x0057E110,0x90);
	Utilits.SetByte(0x0057E111,0x90);
	Utilits.SetByte(0x0057E112,0x90);
	Utilits.SetByte(0x0057E113,0x90);
	Utilits.SetByte(0x0057E114,0x90);
	Utilits.SetByte(0x0057E115,0x90);
	Utilits.SetByte(0x0057E116,0x90);
	Utilits.SetByte(0x0057E117,0x52);

	Utilits.SetByte(0x005D6889,0xEB);

	*(DWORD*)(0x0057E105+2) = (DWORD)&MapAttrName;

	Utilits.SetByte(0x0057E102+2,24);
	Utilits.SetByte(0x00514B52+2,NumMaps);
	Utilits.SetByte(0x004C7C5F+3,NumMaps);
	Utilits.SetByte(0x0054D007+3,NumMaps);
	Utilits.SetByte(0x0054D037+3,NumMaps);
	Utilits.SetByte(0x0053F88C+3,NumMaps);
	Utilits.SetByte(0x00431E89+3,NumMaps);
	Utilits.SetByte(0x0044009F+3,NumMaps);
}
#endif