// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # GreatDevelop 1.0.1								# //
// ================================================== // 

#include "Stdafx.h"
#include "SQL.h"  
#include "Logger.h"
#include "ChatCommands.h"
CSQLEx MySQL;

CSQLEx::CSQLEx()
{
}

CSQLEx::~CSQLEx()
{
    this->Disconnect();
}

void CSQLEx::Load()
{
	int nSQLVer = GetPrivateProfileInt("SQL", "SQLServerVersion", 2000, GreatDevelopGS);
	if(nSQLVer == 2000)szDriver="{SQL Server}";
	else szDriver="{SQL Native Client}";
	GetPrivateProfileStringA("SQL","SQLServerIP","127.0.0.1",szServer,sizeof(szServer),GreatDevelopGS);
	GetPrivateProfileStringA("SQL","SQLServerIP","127.0.0.1",szServer2,sizeof(szServer2),GreatDevelopGS);
	GetPrivateProfileStringA("SQL","SQLLogin","sa",szUser,sizeof(szUser),GreatDevelopGS);
	GetPrivateProfileStringA("SQL","SQLPass","PASS",szPassword,sizeof(szPassword),GreatDevelopGS);
	GetPrivateProfileStringA("SQL","SQLDB","MuOnline",szDatabase,sizeof(szDatabase),GreatDevelopGS);

	if(!this->Connect())
	{
#ifdef _GS
		MessageBoxA(NULL,"Failed to connect!!\nCheck 'GameServer.ini'","GreatDevelop SQL Error!!",MB_OK);
#endif
#ifdef _GS_CS
		MessageBoxA(NULL,"Failed to connect!!\nCheck 'GameServerCS.ini'","GreatDevelop SQL Error!!",MB_OK);
#endif
		::ExitProcess(0);
	} 
}

void CSQLEx::CheckColumns()
{								   	
	struct Temp
	{  
		char AddQuery[255];
		char Column[35];	  
		char Table[35];
	};									  

	Temp Query[] = {	{"ALTER TABLE Character ADD [DuelWins] [int] DEFAULT (0) NOT NULL"
							,"DuelWins","Character"},	 

						{"ALTER TABLE Character ADD [DuelLoses] [int] DEFAULT (0) NOT NULL"
							,"DuelLoses","Character"},

						{"ALTER TABLE Character ADD [DuelsTotal] [int] DEFAULT (0) NOT NULL"
							,"DuelsTotal","Character"},
											
						{"ALTER TABLE Character ADD [LastDuel] [datetime] NULL"
							,"LastDuel","Character"},
																
						{"ALTER TABLE Character ADD [BanPost] [tinyint] DEFAULT (0) NOT NULL"
							,"BanPost","Character"}, 													   

						{"ALTER TABLE warehouse ADD [UsedSlot][int] NULL"
							,"UsedSlot","warehouse"},		   

						{"ALTER TABLE warehouse ADD [Items01][varbinary](1920) NULL"
							,"Items01","warehouse"},		

						{"ALTER TABLE warehouse ADD [Items02][varbinary](1920) NULL"
							,"Items02","warehouse"},		

						{"ALTER TABLE warehouse ADD [Items03][varbinary](1920) NULL"
							,"Items03","warehouse"},		

						{"ALTER TABLE warehouse ADD [Items04][varbinary](1920) NULL"
							,"Items04","warehouse"},		

						{"ALTER TABLE warehouse ADD [Items05][varbinary](1920) NULL"
							,"Items05","warehouse"},															   																   
													   
						{"ALTER TABLE MEMB_STAT ADD [OnlineHours][int] DEFAULT (0) NOT NULL"
							,"OnlineHours","MEMB_STAT"}, 
					};
							
	for(int i = 0; i < (sizeof Query / sizeof Query[0]); i++)
	{	
		CheckColumn(szDatabase, Query[i].Column, Query[i].Table, Query[i].AddQuery, szDatabase);
	}	
}

void CSQLEx::CheckColumn(char* Base, char* Column, char* Table, char* AddQuery, ...)
{	
	char Temp[255];	 
	Temp[0] = 0;
	va_list pArguments;
	va_start(pArguments, AddQuery);
	vsprintf_s(Temp, AddQuery, pArguments);
	va_end(pArguments);

	char Result[255];
	Result[0] = 0;
	Execute("SELECT COLUMN_NAME FROM [%s].INFORMATION_SCHEMA.Columns where COLUMN_NAME = '%s' and TABLE_NAME = '%s'", Base, Column, Table);
	GetString(Result);
	if(strcmp(Result, Column))
	{ 
		Execute(Temp);	
		Log.ConsoleOutPut(0, c_Red, t_Error, "GreatDevelop SQL Error!! \n Can't find %s column in %s table.\nSucsessfully added %s column in %s table \n \n", Column, Table, Column, Table);
	}
}


bool CSQLEx::Connect()
{
    if(this->m_bConnected == 1)
	{
        return false;
	}

    if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&this->m_SQLEnvironment)) == 0)
    {
	    return false;
    }

    if(SQL_SUCCEEDED(SQLSetEnvAttr(this->m_SQLEnvironment,SQL_ATTR_ODBC_VERSION,(void *)SQL_OV_ODBC3,0)) == 0)
    {
        this->FreeHandle();	
        return false;
    }

    if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC,this->m_SQLEnvironment,&this->m_SQLConnection)) == 0)
    {
        this->FreeHandle();	 
        return false;
    }

    SQLSetConnectOption(this->m_SQLConnection,SQL_LOGIN_TIMEOUT,5);	   
    SQLSetConnectOption(this->m_SQLConnection,SQL_CURSOR_TYPE,SQL_CURSOR_STATIC);

	SQLCHAR szConStrIn[1024],szConStrOut[1024];
    SQLSMALLINT iConOutSize = 0;

	sprintf((char*)szConStrIn,"DRIVER=%s; SERVER=%s; UID=%s; PWD=%s; DATABASE=%s;",szDriver,szServer2,szUser,szPassword,szDatabase);

    SQLRETURN Connect = SQLDriverConnect(this->m_SQLConnection,NULL,szConStrIn,SQL_NTS,szConStrOut,sizeof(szConStrOut),&iConOutSize,SQL_DRIVER_NOPROMPT);

    if(SQL_SUCCEEDED(Connect) == 0) 
    {
		this->FreeHandle();	 
        return false;
    }

    this->m_bConnected = 1;

    return true;
}

bool CSQLEx::ConnectExt()
{
    if(this->m_bConnected == 1)
		return false;

    if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&this->m_SQLEnvironment)) == 0)
	    return false;

    if(SQL_SUCCEEDED(SQLSetEnvAttr(this->m_SQLEnvironment,SQL_ATTR_ODBC_VERSION,(void *)SQL_OV_ODBC3,0)) == 0)
    {
        this->FreeHandle();	 
        return false;
    }

    if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC,this->m_SQLEnvironment,&this->m_SQLConnection)) == 0)
    {
        this->FreeHandle();	
        return false;
    }

    SQLSetConnectOption(this->m_SQLConnection,SQL_LOGIN_TIMEOUT,5);		   
    SQLSetConnectOption(this->m_SQLConnection,SQL_CURSOR_TYPE,SQL_CURSOR_STATIC);

	SQLCHAR szConStrIn[1024],szConStrOut[1024];
    SQLSMALLINT iConOutSize = 0;

	sprintf((char*)szConStrIn,"DRIVER=%s; SERVER=%s; UID=%s; PWD=%s; DATABASE=%s;",szDriver,szServer2,szUser,szPassword,szDatabase);

    SQLRETURN Connect = SQLDriverConnect(this->m_SQLConnection,NULL,szConStrIn,SQL_NTS,szConStrOut,sizeof(szConStrOut),&iConOutSize,SQL_DRIVER_NOPROMPT);

    if(SQL_SUCCEEDED(Connect) == 0) 
    {
		this->FreeHandle();	   
        return false;
    }

    this->m_bConnected = 1;

    return true;
}

void CSQLEx::Disconnect()
{
    if(this->m_bConnected == 1)
    {
        SQLDisconnect(this->m_SQLConnection); 
		this->FreeHandle();
    }

    this->m_SQLConnection = NULL;
    this->m_SQLEnvironment = NULL;

    this->m_bConnected = 0;
}

void CSQLEx::FreeHandle()
{
    if(this->m_SQLConnection != NULL)
	    SQLFreeHandle(SQL_HANDLE_DBC,this->m_SQLConnection);
	
	if(this->m_SQLEnvironment != NULL)
	    SQLFreeHandle(SQL_HANDLE_ENV,this->m_SQLEnvironment);
}

bool CSQLEx::Execute(char* szQuery,...)
{
	if(this->m_bConnected == 0)
	{
        return false;
	}

    if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT,this->m_SQLConnection,&this->m_STMT)) == 0)
    {
	    return false;
	}

	char szTemp[1024];

	va_list pArguments;

	va_start(pArguments,szQuery);
	vsprintf(szTemp,szQuery,pArguments);
	va_end(pArguments);

    if(SQL_SUCCEEDED(SQLPrepare(this->m_STMT,(unsigned char*)szTemp,strlen(szTemp))) == 0)
    {
	    return false;
	}
			
	SQLRETURN Execute = SQLExecute(this->m_STMT);

    if(Execute == SQL_SUCCESS || Execute == SQL_SUCCESS_WITH_INFO || Execute == SQL_NO_DATA)
    {
	    if(SQLRowCount(this->m_STMT,&this->m_RowCount) != SQL_SUCCESS)
		{
		    this->m_RowCount = 0;
		}

		if(SQLNumResultCols(this->m_STMT,(SQLSMALLINT*)&this->m_ColCount) != SQL_SUCCESS)
		{
		    this->m_ColCount = 0;
		}

		return true;
	}

	return false;
}


char* CSQLEx::GetLastError()
{
	char szError[1024];

    SQLCHAR     szState[20];
	SQLINTEGER  iNativeError;
	SQLSMALLINT iOutErrorSize;

	SQLError(this->m_SQLEnvironment,this->m_SQLConnection,this->m_STMT,szState,&iNativeError,(SQLCHAR*)szError,sizeof(szError),&iOutErrorSize);

    return &szError[0];
}

int CSQLEx::GetRow()
{
    return this->m_RowCount;
}

int CSQLEx::GetCol()
{
	return this->m_ColCount;
}

int CSQLEx::GetInt()
{
    long lSize,lResult=0;

    while(true)
	{
	    if(SQL_SUCCEEDED(SQLFetch(this->m_STMT)) == 0)
		    break;
		
		if(SQL_SUCCEEDED(SQLGetData(this->m_STMT,1,SQL_C_LONG,&lResult,sizeof(long),&lSize)) == 0)
		    break;
		
		return lResult;
	}

	return 0;
}

void CSQLEx::GetString(char *msg)
{
    long lSize;
	char lResult[1024];

	while(true)
	{
		if(SQL_SUCCEEDED(SQLFetch(this->m_STMT)) == 0)
			break;

		if(SQL_SUCCEEDED(SQLGetData(this->m_STMT, 1, SQL_C_CHAR, &lResult,sizeof(lResult),&lSize)) == 0)
		{
			break;
		}
		else
		{
			memcpy(msg,lResult,lSize);
			msg[lSize] = '\0';
		}
	}
}

bool CSQLEx::FetchRow(char* out,int len)
{
	long lSize;

    while(true)
	{
		if(SQL_SUCCEEDED(SQLFetch(this->m_STMT)) == 0)
			break;

		for(int n=0;n < this->m_ColCount;n++)
		    if(SQL_SUCCEEDED(SQLGetData(this->m_STMT,(n+1),SQL_C_CHAR,&out[n],len,&lSize)) == 0)
			    break;
		
		return 1;
	}

	return 0;
}