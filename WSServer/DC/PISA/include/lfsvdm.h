/**************************************************************************
*                                                                         *
* LFSvdm.h - Vendor Dependent Mode (VDM) definitions                      *
*                                                                         *
* Version 1.00                                                            *
*                                                                         *
**************************************************************************/
 
#ifndef __INC_LFSVDM__H
#define __INC_LFSVDM__H

#ifdef __cplusplus
extern "C" {
#endif

#include "lfsapi.h"

/* be aware of alignment */
#ifdef LFSPACK4
#pragma pack(push,4)
#else
#pragma pack(push,1)
#endif

/* values of LFSVDMCAPS.wClass */

#define LFS_SERVICE_CLASS_VDM             (9)
#define LFS_SERVICE_CLASS_VERSION_VDM     (0x0001) /* Version 1.0 */
#define LFS_SERVICE_CLASS_NAME_VDM        "VDM"

#define VDM_SERVICE_OFFSET                (LFS_SERVICE_CLASS_VDM * 100)

/* VDM Info Commands */

#define LFS_INF_VDM_STATUS                (VDM_SERVICE_OFFSET + 1)
#define LFS_INF_VDM_CAPABILITIES          (VDM_SERVICE_OFFSET + 2)
#define LFS_INF_VDM_ACTIVE_INTERFACE          (VDM_SERVICE_OFFSET + 3)
/* VDM Execute Commands */

#define LFS_CMD_VDM_ENTER_MODE_REQ        (VDM_SERVICE_OFFSET + 1)
#define LFS_CMD_VDM_ENTER_MODE_ACK        (VDM_SERVICE_OFFSET + 2)
#define LFS_CMD_VDM_EXIT_MODE_REQ         (VDM_SERVICE_OFFSET + 3)
#define LFS_CMD_VDM_EXIT_MODE_ACK         (VDM_SERVICE_OFFSET + 4)
#define LFS_CMD_VDM_SET_ACTIVE_INTERFACE  (VDM_SERVICE_OFFSET + 5)

/* VDM Messages */

#define LFS_SRVE_VDM_ENTER_MODE_REQ       (VDM_SERVICE_OFFSET + 1)
#define LFS_SRVE_VDM_EXIT_MODE_REQ        (VDM_SERVICE_OFFSET + 2)
#define LFS_SYSE_VDM_MODEENTERED          (VDM_SERVICE_OFFSET + 3)
#define LFS_SYSE_VDM_MODEEXITED           (VDM_SERVICE_OFFSET + 4)
#define LFS_SRVE_VDM_INTERFACECHANGED     (VDM_SERVICE_OFFSET + 5)

/* values of LFSVDMSTATUS.wDevice */
#define LFS_VDM_DEVONLINE                 LFS_STAT_DEVONLINE
#define LFS_VDM_DEVOFFLINE                LFS_STAT_DEVOFFLINE

/* values of LFSVDMSTATUS.wService */
#define LFS_VDM_ENTERPENDING              (0)
#define LFS_VDM_ACTIVE                    (1)
#define LFS_VDM_EXITPENDING               (2)
#define LFS_VDM_INACTIVE                  (3)


/* values of LFSVDMACTIVEINTERFACE.wActive_Interface */
#define LFS_VDM_CONSUMER_INTERFACE              (0)
#define LFS_VDM_OPERATOR_INTERFACE                    (1)

/*=================================================================*/
/* VDM Info Command Structures and variables */
/*=================================================================*/

typedef struct _LFS_vdm_appstatus
{
    LPSTR               lpszApp_ID;
    WORD                wApp_Status;
} LFSVDMAPPSTATUS, * LPLFSVDMAPPSTATUS;

typedef struct _LFS_vdm_status
{
     WORD               wDevice;
     WORD               wService;
     LPLFSVDMAPPSTATUS  *lppApp_Status;
     LPSTR              lpszExtra;
} LFSVDMSTATUS, *LPLFSVDMSTATUS;

typedef struct _LFS_vdm_caps
{
     WORD               wClass;
     LPSTR              lpszExtra;
} LFSVDMCAPS, * LPLFSVDMCAPS;

typedef struct _LFS_VDM_active_interface
{
	WORD wActive_Interface;
} LFSVDMACTIVEINTERFACE, *LPLFSVDMACTIVEINTERFACE;

/*=================================================================*/
/* VDM Execute Command Structures */
/*=================================================================*/

/*=================================================================*/
/* VDM Message Structures */
/*=================================================================*/

/* restore alignment */
#pragma pack(pop)

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif  /* __INC_LFSVDM__H */