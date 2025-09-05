/******************************************************************************
*                                                                             *
* xfsspi.h      XFS - SPI functions, types, and definitions                   *
*                                                                             *
*               Version 3.20  (March 02 2011)                                 *
*                                                                             *
******************************************************************************/

#ifndef __inc_xfsspi__h
#define __inc_xfsspi__h

#ifdef __cplusplus
extern "C" {
#endif

#include <xfsapi.h>

typedef HANDLE HPROVIDER;
#ifdef QT_LINUX_ARM_PISA
#include "WFSadmin.h"
#else
#include <xfsconf.h>
#include <xfsadmin.h>
#endif

/*   be aware of alignment   */
#pragma pack(push,1)

/****** SPI functions ********************************************************/
#ifdef QT_LINUX_ARM_PISA

HRESULT extern WFSAPI LFPCancelAsyncRequest(HSERVICE usService, REQUESTID ulRequest_ID);

HRESULT extern WFSAPI LFPClose(HSERVICE usService, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern WFSAPI LFPDeregister(HSERVICE usService, DWORD dwEvent_Class, LPSTR lpstrObject_Reg_Name, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern WFSAPI LFPExecute(HSERVICE usService, DWORD dwCommand, LPVOID lpvdCmd_Data, DWORD dwTime_Out, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern WFSAPI LFPGetInfo(HSERVICE usService, DWORD dwCategory, LPVOID lpvdQuery_Details, DWORD dwTime_Out, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern WFSAPI LFPLock(HSERVICE usService, DWORD dwTime_Out, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern WFSAPI LFPOpen(HSERVICE usService, LPSTR lpstrLogical_Name, HAPP lpvdApp_Handle, LPSTR lpstrApp_ID, DWORD dwTrace_Level, DWORD dwTime_Out, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID, HPROVIDER lpvdProvider, DWORD dwSPI_Versions_Required, LPWFSVERSION lpSPI_Version, DWORD dwSrvc_Versions_Required, LPWFSVERSION lpSrvc_Version);

HRESULT extern WFSAPI LFPRegister(HSERVICE usService, DWORD dwEvent_Class, LPSTR lpstrObject_Reg_Name, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

HRESULT extern WFSAPI LFPSetTraceLevel(HSERVICE usService, DWORD dwTrace_Level);

HRESULT extern WFSAPI LFPUnloadService();

HRESULT extern WFSAPI LFPUnlock(HSERVICE usService, LPSTR lpstrObject_Name, REQUESTID ulRequest_ID);

#else
HRESULT extern WINAPI WFPCancelAsyncRequest ( HSERVICE hService, REQUESTID RequestID);

HRESULT extern WINAPI WFPClose ( HSERVICE hService, HWND hWnd, REQUESTID ReqID);

HRESULT extern WINAPI WFPDeregister ( HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);

HRESULT extern WINAPI WFPExecute ( HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

HRESULT extern WINAPI WFPGetInfo ( HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

HRESULT extern WINAPI WFPLock ( HSERVICE hService, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID);

HRESULT extern WINAPI WFPOpen ( HSERVICE hService, LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, HWND hWnd, REQUESTID ReqID, HPROVIDER hProvider, DWORD dwSPIVersionsRequired, LPWFSVERSION lpSPIVersion, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion);

HRESULT extern WINAPI WFPRegister ( HSERVICE hService,  DWORD dwEventClass, HWND hWndReg, HWND hWnd, REQUESTID ReqID);

HRESULT extern WINAPI WFPSetTraceLevel ( HSERVICE hService, DWORD dwTraceLevel);

HRESULT extern WINAPI WFPUnloadService (  );

HRESULT extern WINAPI WFPUnlock ( HSERVICE hService, HWND hWnd, REQUESTID ReqID);
#endif

/*   restore alignment   */
#pragma pack(pop)

#ifdef __cplusplus
}    /*extern "C"*/
#endif

#endif  /* __inc_xfsspi__h */
