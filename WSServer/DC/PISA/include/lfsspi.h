/******************************************************************************
*                                                                             *
* LFSspi.h  - SPI 函数、类型与定义                                            *
*                                                                             *
* Version 1.00                                                                *
*                                                                             *
******************************************************************************/

#ifndef __inc_LFSspi__h
#define __inc_LFSspi__h

#ifdef __cplusplus
extern "C" {
#endif

#include    "lfsapi.h"

typedef HANDLE HPROVIDER; 

#include "LFSadmin.h"

/*   字节对齐设置为1   */
#pragma pack(push,1)

/****** SPI 函数 *************************************************************/
HRESULT extern LFSAPI LFPCancelAsyncRequest(HSERVICE usService, REQUESTID ulRequest_ID);

HRESULT extern LFSAPI LFPClose(HSERVICE usService, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern LFSAPI LFPDeregister(HSERVICE usService, DWORD dwEvent_Class, LPSTR lpstrObject_Reg_Name, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern LFSAPI LFPExecute(HSERVICE usService, DWORD dwCommand, LPVOID lpvdCmd_Data, DWORD dwTime_Out, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern LFSAPI LFPGetInfo(HSERVICE usService, DWORD dwCategory, LPVOID lpvdQuery_Details, DWORD dwTime_Out, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern LFSAPI LFPLock(HSERVICE usService, DWORD dwTime_Out, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern LFSAPI LFPOpen(HSERVICE usService, LPSTR lpstrLogical_Name, HAPP lpvdApp_Handle, LPSTR lpstrApp_ID, DWORD dwTrace_Level, DWORD dwTime_Out, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID, HPROVIDER lpvdProvider, DWORD dwSPI_Versions_Required, LPLFSVERSION lpSPI_Version, DWORD dwSrvc_Versions_Required, LPLFSVERSION lpSrvc_Version);

HRESULT extern LFSAPI LFPRegister(HSERVICE usService, DWORD dwEvent_Class, LPSTR lpstrObject_Reg_Name, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern LFSAPI LFPSetTraceLevel(HSERVICE usService, DWORD dwTrace_Level);

HRESULT extern LFSAPI LFPUnloadService();

HRESULT extern LFSAPI LFPUnlock(HSERVICE usService, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

/*   恢复字节对齐方式   */
#pragma pack(pop)

#ifdef __cplusplus
}    /*extern "C"*/
#endif

#endif  /* __inc_LFSspi__h */