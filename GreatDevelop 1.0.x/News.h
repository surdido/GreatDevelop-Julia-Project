// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.1								# //
// ================================================== //

#pragma once
void NewsSystem(void * lpParam);
class News
{
public:
	News();
	~News();  
	int Sections;
	struct sNews
	{
		char MSG01[50];
		char MSG02[50];
		char MSG03[50];
		float Time;
		int Type;
	};
	sNews NewsSys[20];
};
extern News g_News;
