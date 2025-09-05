/****************************************************************************** 
*                                                                             * 
* LFSalm.h  - Alarm (ALM) definitions                                         * 
*                                                                             * 
* Version 1.00                                                                * 
*                                                                             * 
******************************************************************************/ 
 
#ifndef __INC_LFSALM__H 
#define __INC_LFSALM__H 

#ifdef __cplusplus 
extern "C" { 
#endif 

#include    "lfsapi.h" 

/* be aware of alignment */ 
#pragma pack (push, 1) 

/* values of LFSALMCAPS.wClass */ 
#define   LFS_SERVICE_CLASS_ALM                  (11) 
#define   LFS_SERVICE_CLASS_VERSION_ALM          0x0001 /*Version 1.0 */ 
#define   LFS_SERVICE_CLASS_NAME_ALM             "ALM" 
#define   ALM_SERVICE_OFFSET                     (LFS_SERVICE_CLASS_ALM * 100) 

/* ALM Info Commands */ 
#define   LFS_INF_ALM_STATUS                     (ALM_SERVICE_OFFSET + 1) 
#define   LFS_INF_ALM_CAPABILITIES               (ALM_SERVICE_OFFSET + 2) 

/* ALM Execute Commands */ 
#define   LFS_CMD_ALM_SET_ALARM                  (ALM_SERVICE_OFFSET + 1) 
#define   LFS_CMD_ALM_RESET_ALARM                (ALM_SERVICE_OFFSET + 2) 
#define   LFS_CMD_ALM_RESET                      (ALM_SERVICE_OFFSET + 3) 

/* ALM Messages */ 
#define   LFS_SRVE_ALM_DEVICE_SET                (ALM_SERVICE_OFFSET + 1) 
#define   LFS_SRVE_ALM_DEVICE_RESET              (ALM_SERVICE_OFFSET + 2) 

/* values of LFSALMSTATUS.fwDevice */ 
#define   LFS_ALM_DEVONLINE                     LFS_STAT_DEVONLINE 
#define   LFS_ALM_DEVOFFLINE                    LFS_STAT_DEVOFFLINE 
#define   LFS_ALM_DEVPOWEROFF                   LFS_STAT_DEVPOWEROFF 
#define   LFS_ALM_DEVNODEVICE                   LFS_STAT_DEVNODEVICE 
#define   LFS_ALM_DEVHWERROR                    LFS_STAT_DEVHWERROR 
#define   LFS_ALM_DEVUSERERROR                  LFS_STAT_DEVUSERERROR 
#define   LFS_ALM_DEVBUSY                       LFS_STAT_DEVBUSY 
#define   LFS_ALM_DEVFRAUDATTEMPT               LFS_STAT_DEVFRAUDATTEMPT 

/*=================================================================*/ 
/* ALM Info Command Structures */ 
/*=================================================================*/ 
typedef struct _LFS_ALM_status 
{ 
    WORD                     wDevice; 
    BOOL                     bAlarm_Set;
    LPSTR                    lpstrExtra; 
} LFSALMSTATUS, *LPLFSALMSTATUS;

typedef struct _LFS_ALM_caps 
{ 
    WORD                     wClass; 
    BOOL                     bProgrammatically_Deactivate;
	LPSTR                    lpstrExtra; 
} LFSALMCAPS, *LPLFSALMCAPS;

/* restore alignment */ 
#pragma pack(pop) 

#ifdef __cplusplus 
} /*extern "C"*/ 
#endif 

#endif /* __INC_LFSALM__H */