// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Storm & Tornado Projects 2010-2011		# //
// ================================================== //

#define WZAG_API extern "C" __declspec(dllexport)

WZAG_API bool	AGInit() ;
WZAG_API int	AGConnectSetFS() ;
WZAG_API int	AGGetClientVersion(int unknown,char * VerBuff,char * SerialBuff)  ;
WZAG_API char * AGGetDataBuffer()  ;
WZAG_API int	AGGetDataBufferSize() ;
WZAG_API void	AGGetKey(HANDLE handle,char* key,int startindex,int len)   ;
WZAG_API int	AGReleaseHandle() ;
WZAG_API int	AGRequestData(int NoneUse,int GetType)  ;
WZAG_API int	AGSetInfo(int Language,char * Partition,int un0,char * SrvVer,char* SrvName,int SrvType,char * Addr7)    ;
WZAG_API int	AGSetSubInfo()  ;