// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Storm & Tornado Projects 2010-2011		# //
// ================================================== //

#ifndef Logger_H
#define Logger_H

extern char Message[1024];

enum sColor
{
	c_Red,		// ��������
	c_Green,	// ������
	c_Blue,		// �������
	c_Cyan,		// ���������
	c_Yellow,	// Ƹ����
	c_Magenta,	// ����������
	c_Grey		// ����� 
};

enum sLogType
{
	t_NULL,
	t_Error,
	t_Default,
	t_GM,
	t_POST,
	t_DROP,
	t_BAN,
	t_COMMANDS,
	t_GPOST,
	t_PCPOINT,
	t_IPBLOCK,
	t_Duel
};

class Logger
{
public:	   
									
	Logger();
	~Logger();		 
	void LoggerInit();	  		 
	void CheckProcent(char* message); 	
	void SaveFile(char *logString,char *Message);
	void ConsoleOutPut(int WOL, sColor Color, sLogType Type, const char* Format, ...);
	HANDLE Handle(BOOL Input);
	void CreateLog(sLogType Type,const char* Format, ...);	

};
extern Logger Log;		

#endif Logger_H