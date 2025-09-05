/*******************************************************************************
 *                                                                             *
 * lfsvdm.h      LFS - Vendor Dependent Mode (VDM) definitions                 *
 *                                                                             *
 *                     Version 1.00  -  (2020-02)                              *
 *                                                                             *
 *******************************************************************************/

#ifndef __INC_LFSVDM__H
#define __INC_LFSVDM__H

#ifdef __cplusplus
extern "C" {
#endif

#include "lfsapi.h"
/*   be aware of alignment   */
#pragma pack(push, 1)

/* values of LFSVDMCAPS.wClass */

#define LFS_SERVICE_CLASS_VDM         (7)
#define LFS_SERVICE_CLASS_VERSION_VDM (0x0001)  // Version 1.00
#define LFS_SERVICE_CLASS_NAME_VDM    "VDM"

#define VDM_SERVICE_OFFSET (LFS_SERVICE_CLASS_VDM * 100)

/* VDM Info Commands */

#define LFS_INF_VDM_STATUS           (VDM_SERVICE_OFFSET + 1)
#define LFS_INF_VDM_CAPABILITIES     (VDM_SERVICE_OFFSET + 2)
#define LFS_INF_VDM_ACTIVE_INTERFACE (VDM_SERVICE_OFFSET + 3)

/* VDM Execute Commands */

#define LFS_CMD_VDM_ENTER_MODE_REQ       (VDM_SERVICE_OFFSET + 1)
#define LFS_CMD_VDM_ENTER_MODE_ACK       (VDM_SERVICE_OFFSET + 2)
#define LFS_CMD_VDM_EXIT_MODE_REQ        (VDM_SERVICE_OFFSET + 3)
#define LFS_CMD_VDM_EXIT_MODE_ACK        (VDM_SERVICE_OFFSET + 4)
#define LFS_CMD_VDM_SET_ACTIVE_INTERFACE (VDM_SERVICE_OFFSET + 5)

/* VDM Messages */

#define LFS_SRVE_VDM_ENTER_MODE_REQ    (VDM_SERVICE_OFFSET + 1)
#define LFS_SRVE_VDM_EXIT_MODE_REQ     (VDM_SERVICE_OFFSET + 2)
#define LFS_SYSE_VDM_MODEENTERED       (VDM_SERVICE_OFFSET + 3)
#define LFS_SYSE_VDM_MODEEXITED        (VDM_SERVICE_OFFSET + 4)
#define LFS_SRVE_VDM_INTERFACE_CHANGED (VDM_SERVICE_OFFSET + 5)

/* values of LFSVDMSTATUS.wDevice */

#define LFS_VDM_DEVONLINE  LFS_STAT_DEVONLINE
#define LFS_VDM_DEVOFFLINE LFS_STAT_DEVOFFLINE

/* values of LFSVDMSTATUS.wService */

#define LFS_VDM_ENTERPENDING (0)
#define LFS_VDM_ACTIVE       (1)
#define LFS_VDM_EXITPENDING  (2)
#define LFS_VDM_INACTIVE     (3)

/* values of LFSVDMSTATUS.wActiveAccessLevel */

#define LFS_VDM_ACCESSNOTSUPPORTED (0x0000)
#define LFS_VDM_ACCESSNA           (0x0001)
#define LFS_VDM_ACCESSUNKNOWN      (0x0002)
#define LFS_VDM_ACCESSBASIC        (0x0004)
#define LFS_VDM_ACCESSINTERMEDIATE (0x0008)
#define LFS_VDM_ACCESSFULL         (0x0010)

/* values of LFSVDMACTIVEINTERFACE.wActiveInterface */

#define LFS_VDM_OPERATOR_INTERFACE (0)
#define LFS_VDM_CONSUMER_INTERFACE (1)

/* LFS VDM Errors */

#define LFS_ERR_VDM_INTERFACE_NOT_AVAILABLE (-(VDM_SERVICE_OFFSET + 0))

/*=================================================================*/
/* VDM Info Command Structures and variables */
/*=================================================================*/

typedef struct _lfs_vdm_appstatus {
  LPSTR lpszAppID;
  WORD wAppStatus;
} LFSVDMAPPSTATUS, *LPLFSVDMAPPSTATUS;

typedef struct _lfs_vdm_status {
  WORD wDevice;
  WORD wService;
  LPLFSVDMAPPSTATUS* lppAppStatus;
  LPSTR lpszExtra;
  WORD wAccessLevel;
} LFSVDMSTATUS, *LPLFSVDMSTATUS;

typedef struct _lfs_vdm_caps {
  WORD wClass;
  LPSTR lpszExtra;
  WORD fwSupportedAccessLevels;
} LFSVDMCAPS, *LPLFSVDMCAPS;

typedef struct _lfs_vdm_active_interface {
  WORD wActiveInterface;
} LFSVDMACTIVEINTERFACE, *LPLFSVDMACTIVEINTERFACE;

/*=================================================================*/
/* VDM Execute Command Structures */
/*=================================================================*/

typedef struct _lfs_vdm_enter_mode_req_cmd {
  WORD wAccessLevel;
} LFSVDMENTERMODEREQCMD, *LPLFSVDMENTERMODEREQCMD;

/*=================================================================*/
/* VDM Message Structures */
/*=================================================================*/

/*   restore alignment   */
#pragma pack(pop)

#ifdef __cplusplus
} /*extern "C"*/
#endif
#endif /* __INC_LFSVDM__H */
