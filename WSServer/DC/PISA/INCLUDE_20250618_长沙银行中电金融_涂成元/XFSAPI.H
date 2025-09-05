/************************************************************************
 *                                                                       *
 * xfsapi.h      XFS - API functions, types, and definitions             *
 *                                                                       *
 *               Version 3.00  --  10/18/00                              *
 *                                                                       *
 ************************************************************************/

#ifndef __inc_xfsapi__h
#define __inc_xfsapi__h

// #ifdef __cplusplus
// extern "C" {
// #endif

/*   be aware of alignment   */
#pragma pack(push, 1)

//#include <sys/types.h>
#include <pthread.h>
#define LFSAPI                                  __attribute__((__cdecl__))
#define WFSAPI  LFSAPI
typedef int (WFSAPI* WFSBLOCKINGHOOK)(void);
typedef WFSBLOCKINGHOOK *LPWFSBLOCKINGHOOK;
/****** Common *********************************************************/
#include "QtTypeDef.h"

// 计算扩展状态长度
inline UINT GetLenOfSZZ(const char *lpszz)
{
    const char *p = lpszz;
    while (true)
    {
        if (p == nullptr || (p + 1) == nullptr)
            return 0;
        if ((*p == 0x00) && (*(p + 1) == 0x00))
            break;
        p++;
    }
    return (UINT)((p - lpszz) + 2);
}

/****** d-bus 名称与 DM_USER 定义 ****************************************/

#define LFS_MGR_DBUS_NAME_PREF   "org.lfs.manager"
#define LFS_MGR_DBUS_INTF_NAME   "org.lfs.windows_compatible_intf"
#define LFS_MGR_DBUS_METHOD_NAME "event_callback"

/****** String lengths **************************************************/

#define WFSDDESCRIPTION_LEN 256
#define WFSDSYSSTATUS_LEN   256

/****** Values of WFSDEVSTATUS.fwState **********************************/

#define WFS_STAT_DEVONLINE    (0)
#define WFS_STAT_DEVOFFLINE   (1)
#define WFS_STAT_DEVPOWEROFF  (2)
#define WFS_STAT_DEVNODEVICE  (3)
#define WFS_STAT_DEVHWERROR   (4)
#define WFS_STAT_DEVUSERERROR (5)
#define WFS_STAT_DEVBUSY      (6)
#define WFS_STAT_DEVFRAUDATTEMPT                (7)
#define WFS_STAT_DEVPOTENTIALFRAUD              (8)

/****** Value of WFS_DEFAULT_HAPP ***************************************/

#define WFS_DEFAULT_HAPP (0)

/****** Data Structures *************************************************/
typedef struct _wfs_result
{
    REQUESTID RequestID;
    HSERVICE hService;
    SYSTEMTIME tsTimestamp;
    HRESULT hResult;
    union {
        DWORD dwCommandCode;
        DWORD dwEventID;
    } u;
    LPVOID lpBuffer;
} WFSRESULT, LFSRESULT, * LPLFSRESULT, *LPWFSRESULT;

typedef struct _wfsversion
{
    WORD wVersion;
    WORD wLowVersion;
    WORD wHighVersion;
    CHAR szDescription[WFSDDESCRIPTION_LEN + 1];
    CHAR szSystemStatus[WFSDSYSSTATUS_LEN + 1];
} WFSVERSION, LFSVERSION, * LPLFSVERSION, *LPWFSVERSION;

/****** Message Structures **********************************************/

typedef struct _wfs_devstatus
{
    LPSTR lpszPhysicalName;
    LPSTR lpszWorkstationName;
    DWORD dwState;
} WFSDEVSTATUS, *LPWFSDEVSTATUS, LFSDEVSTATUS, * LPLFSDEVSTATUS;

typedef struct _wfs_undevmsg
{
    LPSTR lpszLogicalName;
    LPSTR lpszWorkstationName;
    LPSTR lpszAppID;
    DWORD dwSize;
    LPBYTE lpbDescription;
    DWORD dwMsg;
    LPWFSRESULT lpWFSResult;
} WFSUNDEVMSG, *LPWFSUNDEVMSG;

typedef struct _wfs_appdisc
{
    LPSTR lpszLogicalName;
    LPSTR lpszWorkstationName;
    LPSTR lpszAppID;
} WFSAPPDISC, *LPWFSAPPDISC;

typedef struct _wfs_hwerror
{
    LPSTR lpszLogicalName;
    LPSTR lpszPhysicalName;
    LPSTR lpszWorkstationName;
    LPSTR lpszAppID;
    DWORD dwAction;
    DWORD dwSize;
    LPBYTE lpbDescription;
} WFSHWERROR, *LPWFSHWERROR;

typedef struct _wfs_vrsnerror
{
    LPSTR lpszLogicalName;
    LPSTR lpszWorkstationName;
    LPSTR lpszAppID;
    DWORD dwSize;
    LPBYTE lpbDescription;
    LPWFSVERSION lpWFSVersion;
} WFSVRSNERROR, *LPWFSVRSNERROR, LFSVRSNERROR, * LPLFSVRSNERROR;

/****** Error codes ******************************************************/

#define WFS_SUCCESS                   (0)
#define WFS_ERR_ALREADY_STARTED       (-1)
#define WFS_ERR_API_VER_TOO_HIGH      (-2)
#define WFS_ERR_API_VER_TOO_LOW       (-3)
#define WFS_ERR_CANCELED              (-4)
#define WFS_ERR_CFG_INVALID_HKEY      (-5)
#define WFS_ERR_CFG_INVALID_NAME      (-6)
#define WFS_ERR_CFG_INVALID_SUBKEY    (-7)
#define WFS_ERR_CFG_INVALID_VALUE     (-8)
#define WFS_ERR_CFG_KEY_NOT_EMPTY     (-9)
#define WFS_ERR_CFG_NAME_TOO_LONG     (-10)
#define WFS_ERR_CFG_NO_MORE_ITEMS     (-11)
#define WFS_ERR_CFG_VALUE_TOO_LONG    (-12)
#define WFS_ERR_DEV_NOT_READY         (-13)
#define WFS_ERR_HARDWARE_ERROR        (-14)
#define WFS_ERR_INTERNAL_ERROR        (-15)
#define WFS_ERR_INVALID_ADDRESS       (-16)
#define WFS_ERR_INVALID_APP_HANDLE    (-17)
#define WFS_ERR_INVALID_BUFFER        (-18)
#define WFS_ERR_INVALID_CATEGORY      (-19)
#define WFS_ERR_INVALID_COMMAND       (-20)
#define WFS_ERR_INVALID_EVENT_CLASS   (-21)
#define WFS_ERR_INVALID_HSERVICE      (-22)
#define WFS_ERR_INVALID_HPROVIDER     (-23)
#define WFS_ERR_INVALID_HWND          (-24)
#define WFS_ERR_INVALID_HWNDREG       (-25)
#define WFS_ERR_INVALID_POINTER       (-26)
#define WFS_ERR_INVALID_REQ_ID        (-27)
#define WFS_ERR_INVALID_RESULT        (-28)
#define WFS_ERR_INVALID_SERVPROV      (-29)
#define WFS_ERR_INVALID_TIMER         (-30)
#define WFS_ERR_INVALID_TRACELEVEL    (-31)
#define WFS_ERR_LOCKED                (-32)
#define WFS_ERR_NO_BLOCKING_CALL      (-33)
#define WFS_ERR_NO_SERVPROV           (-34)
#define WFS_ERR_NO_SUCH_THREAD        (-35)
#define WFS_ERR_NO_TIMER              (-36)
#define WFS_ERR_NOT_LOCKED            (-37)
#define WFS_ERR_NOT_OK_TO_UNLOAD      (-38)
#define WFS_ERR_NOT_STARTED           (-39)
#define WFS_ERR_NOT_REGISTERED        (-40)
#define WFS_ERR_OP_IN_PROGRESS        (-41)
#define WFS_ERR_OUT_OF_MEMORY         (-42)
#define WFS_ERR_SERVICE_NOT_FOUND     (-43)
#define WFS_ERR_SPI_VER_TOO_HIGH      (-44)
#define WFS_ERR_SPI_VER_TOO_LOW       (-45)
#define WFS_ERR_SRVC_VER_TOO_HIGH     (-46)
#define WFS_ERR_SRVC_VER_TOO_LOW      (-47)
#define WFS_ERR_TIMEOUT               (-48)
#define WFS_ERR_UNSUPP_CATEGORY       (-49)
#define WFS_ERR_UNSUPP_COMMAND        (-50)
#define WFS_ERR_VERSION_ERROR_IN_SRVC (-51)
#define WFS_ERR_INVALID_DATA          (-52)
#define WFS_ERR_SOFTWARE_ERROR        (-53)
#define WFS_ERR_CONNECTION_LOST       (-54)
#define WFS_ERR_USER_ERROR            (-55)
#define WFS_ERR_UNSUPP_DATA           (-56)
#define LFS_ERR_FRAUD_ATTEMPT                  (-57)
#define WFS_INDEFINITE_WAIT 0
#define LFS_ERR_SEQUENCE_ERROR                  (-58)
#define LFS_INDEFINITE_WAIT                     (0)
/****** Messages ********************************************************/

/* Message-No = (WM_USER + No) */

#ifdef QT_WIN32
    #define WM_USER 0x0400
#else
    #define WM_USER 0x0400
#endif

#define WFS_OPEN_COMPLETE       (WM_USER + 1)
#define WFS_CLOSE_COMPLETE      (WM_USER + 2)
#define WFS_LOCK_COMPLETE       (WM_USER + 3)
#define WFS_UNLOCK_COMPLETE     (WM_USER + 4)
#define WFS_REGISTER_COMPLETE   (WM_USER + 5)
#define WFS_DEREGISTER_COMPLETE (WM_USER + 6)
#define WFS_GETINFO_COMPLETE    (WM_USER + 7)
#define WFS_EXECUTE_COMPLETE    (WM_USER + 8)

#define LFS_OPEN_COMPLETE                       WFS_OPEN_COMPLETE
#define LFS_CLOSE_COMPLETE                      WFS_CLOSE_COMPLETE
#define LFS_LOCK_COMPLETE                       WFS_LOCK_COMPLETE
#define LFS_UNLOCK_COMPLETE                     WFS_UNLOCK_COMPLETE
#define LFS_REGISTER_COMPLETE                   WFS_REGISTER_COMPLETE
#define LFS_DEREGISTER_COMPLETE                 WFS_DEREGISTER_COMPLETE
#define LFS_GETINFO_COMPLETE                    WFS_GETINFO_COMPLETE
#define LFS_EXECUTE_COMPLETE                    WFS_EXECUTE_COMPLETE
#define WFS_EXECUTE_EVENT (WM_USER + 20)
#define WFS_SERVICE_EVENT (WM_USER + 21)
#define WFS_USER_EVENT    (WM_USER + 22)
#define WFS_SYSTEM_EVENT  (WM_USER + 23)

#define WFS_TIMER_EVENT (WM_USER + 100)

/****** Event Classes ***************************************************/

#define SERVICE_EVENTS (1)
#define USER_EVENTS    (2)
#define SYSTEM_EVENTS  (4)
#define EXECUTE_EVENTS (8)

/****** System Event IDs ************************************************/

#define WFS_SYSE_UNDELIVERABLE_MSG (1)
#define WFS_SYSE_HARDWARE_ERROR    (2)
#define WFS_SYSE_VERSION_ERROR     (3)
#define WFS_SYSE_DEVICE_STATUS     (4)
#define WFS_SYSE_APP_DISCONNECT    (5)
#define WFS_SYSE_SOFTWARE_ERROR    (6)
#define WFS_SYSE_USER_ERROR        (7)
#define WFS_SYSE_LOCK_REQUESTED    (8)

/****** XFS Trace Level ********************************************/

#define WFS_TRACE_API     0x00000001
#define WFS_TRACE_ALL_API 0x00000002
#define WFS_TRACE_SPI     0x00000004
#define WFS_TRACE_ALL_SPI 0x00000008
#define WFS_TRACE_MGR     0x00000010

/****** XFS Error Actions ********************************************/

#define WFS_ERR_ACT_NOACTION (0x0000)
#define WFS_ERR_ACT_RESET    (0x0001)
#define WFS_ERR_ACT_SWERROR  (0x0002)
#define WFS_ERR_ACT_CONFIG   (0x0004)
#define WFS_ERR_ACT_HWCLEAR  (0x0008)
#define WFS_ERR_ACT_HWMAINT  (0x0010)
#define WFS_ERR_ACT_SUSPEND  (0x0020)

/*   restore alignment   */

#ifdef QT_LINUX_ARM_PISA


HRESULT extern WFSAPI WFSCancelAsyncRequest(HSERVICE usService, REQUESTID ulRequest_ID);

HRESULT extern WFSAPI WFSCancelBlockingCall(ULONG dwThread_ID);

HRESULT extern WFSAPI WFSCleanUp();

HRESULT extern WFSAPI WFSClose(HSERVICE usService);

HRESULT extern WFSAPI WFSAsyncClose(HSERVICE usService, LPSTR lpstrObject_Name, LPREQUESTID ulRequest_ID);

HRESULT extern WFSAPI WFSCreateAppHandle(LPHAPP lphdApp_Handle);

HRESULT extern WFSAPI WFSDeregister(HSERVICE usService, DWORD dwEvent_Class, LPSTR lpstrObject_Reg_Name);

HRESULT extern WFSAPI WFSAsyncDeregister(HSERVICE usService, DWORD dwEvent_Class, LPSTR lpstrObject_Reg_Name, LPSTR lpstrObject_Name, LPREQUESTID ulRequest_ID);

HRESULT extern WFSAPI WFSDestroyAppHandle(HAPP lpstrApp_Handle);

HRESULT extern WFSAPI WFSExecute(HSERVICE usService, DWORD dwCommand, LPVOID lpvdCmd_Data, DWORD dwTime_Out, LPWFSRESULT *lppResult);

HRESULT extern WFSAPI WFSAsyncExecute(HSERVICE usService, DWORD dwCommand, LPVOID lpvdCmd_Data, DWORD dwTime_Out, LPSTR lpstrObject_Name, LPREQUESTID ulRequest_ID);

HRESULT extern WFSAPI WFSFreeResult(LPWFSRESULT lpResult);

HRESULT extern WFSAPI WFSGetInfo(HSERVICE usService, DWORD dwCategory, LPVOID lpvdQuery_Details, DWORD dwTime_Out, LPWFSRESULT *lppResult);

HRESULT extern WFSAPI WFSAsyncGetInfo(HSERVICE usService, DWORD dwCategory, LPVOID lpvdQuery_Details, DWORD dwTime_Out, LPSTR lpstrObject_Name, LPREQUESTID ulRequest_ID);

BOOL extern WFSAPI WFSIsBlocking();

HRESULT extern WFSAPI WFSLock(HSERVICE usService, DWORD dwTime_Out, LPWFSRESULT *lppResult);

HRESULT extern WFSAPI WFSAsyncLock(HSERVICE usService, DWORD dwTime_Out, LPSTR lpstrObject_Name,  LPREQUESTID ulRequest_ID);

HRESULT extern WFSAPI WFSOpen(LPSTR lpstrLogical_Name, HAPP lpvdApp_Handle, LPSTR lpstrApp_ID, DWORD dwTrace_Level, DWORD dwTime_Out, DWORD dwSrvc_Versions_Required, LPWFSVERSION lpSrvc_Version , LPWFSVERSION lpSPI_Version, LPHSERVICE lpusService);

HRESULT extern WFSAPI WFSAsyncOpen(LPSTR lpstrLogical_Name, HAPP lpvdApp_Handle, LPSTR lpstrApp_ID, DWORD dwTrace_Level, DWORD dwTime_Out, LPHSERVICE lpusService, LPSTR lpstrObject_Name, DWORD dwSrvc_Versions_Required, LPWFSVERSION lpSrvc_Version, LPWFSVERSION lpSPI_Version, LPREQUESTID ulRequest_ID);

HRESULT extern WFSAPI WFSRegister(HSERVICE usService, DWORD dwEvent_Class, LPSTR lpstrObject_Reg_Name);

HRESULT extern WFSAPI WFSAsyncRegister(HSERVICE usService, DWORD dwEvent_Class, LPSTR lpstrObject_Reg_Name, LPSTR lpstrObject_Name, LPREQUESTID ulRequest_ID);

HRESULT extern WFSAPI WFSSetBlockingHook(WFSBLOCKINGHOOK lpBlock_Func, LPWFSBLOCKINGHOOK lppPrev_Func);

HRESULT extern WFSAPI WFSStartUp(DWORD dwVersions_Required, LPWFSVERSION lpWFS_Version);

HRESULT extern WFSAPI WFSUnhookBlockingHook();

HRESULT extern WFSAPI WFSUnlock(HSERVICE usService);

HRESULT extern WFSAPI WFSAsyncUnlock(HSERVICE usService, LPSTR lpstrObject_Name, LPREQUESTID ulRequest_ID);
#endif 
#pragma pack(pop)

// #ifdef __cplusplus
// }       /*extern "C"*/
// #endif

#endif /* __inc_xfsapi__h */
