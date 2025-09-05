/******************************************************************************
*                                                                             *
* xfsadmin.h    XFS-Administration and Support functions                      *
*                                                                             *
*               Version 3.10  --  29/11/2007                                  *
*                                                                             *
******************************************************************************/

#ifndef __INC_XFSADMIN__H
#define __INC_XFSADMIN__H

#ifdef __cplusplus
extern "C" {
#endif

#include    <xfsapi.h>

/*   be aware of alignment   */
#pragma pack(push,1)


/* values of ulFlags used for WFMAllocateBuffer */

#define WFS_MEM_SHARE                        0x00000001
#define WFS_MEM_ZEROINIT                     0x00000002

/****** Support Functions ****************************************************/
#ifdef QT_LINUX_ARM_PISA
typedef VOID (*CallBack)(LPSTR lpstrObject_Name, DWORD dwEventID, UINT wParam, LONG lParam);

HRESULT extern WFSAPI WFMAllocateBuffer(ULONG ulSize, ULONG ulFlags, LPVOID *lppData);

HRESULT extern WFSAPI WFMAllocateMore(ULONG ulSize, LPVOID lpvdOriginal, LPVOID *lppData);

HRESULT extern WFSAPI WFMFreeBuffer(LPVOID lpvdData);

HRESULT extern WFSAPI WFMSetTraceLevel(HSERVICE usService, DWORD dwTrace_Level);

HRESULT extern WFSAPI WFMGetTraceLevel(HSERVICE usService, DWORD* dwTrace_Level);

HRESULT extern WFSAPI WFMSetTimer(LPSTR object_name, LPVOID context, DWORD timeval, ULONG* timer_id);

HRESULT extern WFSAPI WFMKillTimer(ULONG timer_id);

HRESULT extern WFSAPI WFMOutputTraceData(LPSTR data);

HRESULT extern WFSAPI WFMReleaseLib(HPROVIDER provider);

HRESULT extern WFSAPI WFMGetMessage(LPSTR lpstrObject_Name, DWORD* dwEventID, UINT* wParam, LONG* lParam, DWORD dwTime_Out);

HRESULT extern WFSAPI WFMPostMessage(LPSTR lpstrObject_Name, DWORD dwEventID, UINT wParam, LONG lParam, DWORD dwTime_Out);

HRESULT extern WFSAPI WFMRegCallBack(LPSTR lpstrObject_Name, CallBack *pcallback);

HRESULT extern WFSAPI WFMUnRegCallBack(LPSTR lpstrObject_Name);
#else
HRESULT extern WINAPI WFMAllocateBuffer( ULONG ulSize, ULONG ulFlags, LPVOID * lppvData);

HRESULT extern WINAPI WFMAllocateMore( ULONG ulSize, LPVOID lpvOriginal, LPVOID * lppvData);

HRESULT extern WINAPI WFMFreeBuffer( LPVOID lpvData);

HRESULT extern WINAPI WFMGetTraceLevel ( HSERVICE hService, LPDWORD lpdwTraceLevel);

HRESULT extern WINAPI WFMKillTimer( WORD wTimerID);

HRESULT extern WINAPI WFMOutputTraceData ( LPSTR lpszData);

HRESULT extern WINAPI WFMReleaseDLL ( HPROVIDER hProvider);

HRESULT extern WINAPI WFMSetTimer ( HWND hWnd, LPVOID lpContext, DWORD dwTimeVal, LPWORD lpwTimerID);

#endif

/*   restore alignment   */
#pragma pack(pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif    /* __INC_XFSADMIN__H */
