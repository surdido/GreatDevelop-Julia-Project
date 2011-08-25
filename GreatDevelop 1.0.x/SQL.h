// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.1								# //
// ================================================== // 

#ifndef _SQL_H
#define _SQL_H

#include <SQL.h>
#include <SqlExt.h>

#include "User.h"

class CSQLEx
{
public:
    CSQLEx();
	virtual ~CSQLEx();

	void Load();
	bool ConnectExt();
	bool Connect();
	void Disconnect();
	bool Execute(char* szQuery,...);
	char* GetLastError();
	void FreeHandle();
	void CheckColumns();
	void CheckColumn(char* Base, char* Column, char* Table, char* AddQuery, ...);

	int GetRow();
	int GetCol();

	int GetInt();
	void GetString(char* msg);
	bool FetchRow(char* out,int len);
	char FetchArray[1024][50];
	char*szDriver;
	char szServer[50];
	char szServer2[50];
	char szUser[50];
	char szPassword[50];
	char szDatabase[50];
private:
	bool m_bConnected;
	HENV m_SQLEnvironment;
	HDBC m_SQLConnection;
	HSTMT m_STMT;
	long m_RowCount;
	long m_ColCount;
};

extern CSQLEx MySQL;

#endif