/******************************************************************************
*                                                                             *
* LFScrd.h - Card Dispenser (CRD) definitions                                 *
*                                                                             *
* Version 1.00                                                                *
*                                                                             *
******************************************************************************/

#ifndef __INC_LFSCRD__H
#define __INC_LFSCRD__H

#ifdef __cplusplus
extern "C" {
#endif

#include    "lfsapi.h"

/*   be aware of alignment   */
#pragma pack(push,1)

/* values of LFSCRDCAPS.wClass */

#define     LFS_SERVICE_CLASS_CRD               (14)
#define     LFS_SERVICE_CLASS_VERSION_CRD       (0x0001) /* Version 1.0 */
#define     LFS_SERVICE_CLASS_NAME_CRD          "CRD"

#define     CRD_SERVICE_OFFSET                   (LFS_SERVICE_CLASS_CRD * 100)

#define     LFS_CRD_SLOT_SIZE                   (2000)

/* CRD Info Commands */

#define     LFS_INF_CRD_STATUS                  (CRD_SERVICE_OFFSET + 1)
#define     LFS_INF_CRD_CAPABILITIES            (CRD_SERVICE_OFFSET + 2)
#define     LFS_INF_CRD_CARD_UNIT_INFO          (CRD_SERVICE_OFFSET + 3)
#define     LFS_INF_CRD_SLOT_INFO               (CRD_SERVICE_OFFSET + 4)

/* CRD Execute Commands */

#define     LFS_CMD_CRD_DISPENSE_CARD           (CRD_SERVICE_OFFSET + 1)
#define     LFS_CMD_CRD_EJECT_CARD              (CRD_SERVICE_OFFSET + 2)
#define     LFS_CMD_CRD_RETAIN_CARD             (CRD_SERVICE_OFFSET + 3)
#define     LFS_CMD_CRD_RESET                   (CRD_SERVICE_OFFSET + 4)
#define     LFS_CMD_CRD_SET_GUIDANCE_LIGHT      (CRD_SERVICE_OFFSET + 5)
#define     LFS_CMD_CRD_SET_CARD_UNIT_INFO      (CRD_SERVICE_OFFSET + 6)
#define     LFS_CMD_CRD_POWER_SAVE_CONTROL      (CRD_SERVICE_OFFSET + 7)
#define     LFS_CMD_CRD_SLOT_DEPOSIT            (CRD_SERVICE_OFFSET + 8)
#define     LFS_CMD_CRD_SLOT_DISPENSE           (CRD_SERVICE_OFFSET + 9) 
#define     LFS_CMD_CRD_MOVE_CARD	            (CRD_SERVICE_OFFSET + 50)

/* CRD Events  */

#define     LFS_SRVE_CRD_MEDIAREMOVED           (CRD_SERVICE_OFFSET + 1)
#define     LFS_SRVE_CRD_CARDUNITINFOCHANGED    (CRD_SERVICE_OFFSET + 2)
#define     LFS_SRVE_CRD_MEDIADETECTED          (CRD_SERVICE_OFFSET + 3)
#define     LFS_USRE_CRD_CARDUNITTHRESHOLD      (CRD_SERVICE_OFFSET + 4)
#define     LFS_EXEE_CRD_CARDUNITERROR          (CRD_SERVICE_OFFSET + 5)
#define     LFS_SRVE_CRD_DEVICEPOSITION         (CRD_SERVICE_OFFSET + 6)
#define     LFS_SRVE_CRD_POWER_SAVE_CHANGE      (CRD_SERVICE_OFFSET + 7)

/* values of LFSCRDSTATUS.wDevice */

#define     LFS_CRD_DEVONLINE                    LFS_STAT_DEVONLINE
#define     LFS_CRD_DEVOFFLINE                   LFS_STAT_DEVOFFLINE
#define     LFS_CRD_DEVPOWEROFF                  LFS_STAT_DEVPOWEROFF
#define     LFS_CRD_DEVNODEVICE                  LFS_STAT_DEVNODEVICE
#define     LFS_CRD_DEVHWERROR                   LFS_STAT_DEVHWERROR
#define     LFS_CRD_DEVUSERERROR                 LFS_STAT_DEVUSERERROR
#define     LFS_CRD_DEVBUSY                      LFS_STAT_DEVBUSY
#define     LFS_CRD_DEVFRAUDATTEMPT              LFS_STAT_DEVFRAUDATTEMPT

/* values of LFSCRDSTATUS.wDispenser */

#define     LFS_CRD_DISPCUOK                    (0)
#define     LFS_CRD_DISPCUSTATE                 (1)
#define     LFS_CRD_DISPCUSTOP                  (2)
#define     LFS_CRD_DISPCUUNKNOWN               (3)

/* values of LFSCRDSTATUS.wMedia,
             LFSCRDRETAINCARD.wPosition, and
             LFSCRDMEDIADETECTED.wPosition */

#define     LFS_CRD_MEDIAPRESENT                (1)
#define     LFS_CRD_MEDIANOTPRESENT            (2)
#define     LFS_CRD_MEDIAJAMMED                (3)
#define     LFS_CRD_MEDIANOTSUPP               (4)
#define     LFS_CRD_MEDIAUNKNOWN               (5)
#define     LFS_CRD_MEDIAEXITING               (6)
#define     LFS_CRD_MEDIARETAINED              (7)

/* values of LFSCRDSTATUS.wTransport */

#define     LFS_CRD_TPOK                        (0)
#define     LFS_CRD_TPINOP                      (1)
#define     LFS_CRD_TPUNKNOWN                   (2)
#define     LFS_CRD_TPNOTSUPPORTED              (3)

/* Size and max index of dwGuid_Lights array */

#define     LFS_CRD_GUIDLIGHTS_SIZE            (32)
#define     LFS_CRD_GUIDLIGHTS_MAX             (LFS_CRD_GUIDLIGHTS_SIZE - 1)

/* Indices of LFSCRDSTATUS.dwGuid_Lights [...]
              LFSCRDCAPS.dwGuid_Lights [...] */

#define     LFS_CRD_GUIDANCE_CARDDISP           (0)

/* Values of LFSCRDSTATUS.dwGuid_Lights [...]
             LFSCRDCAPS.dwGuid_Lights [...] */

#define     LFS_CRD_GUIDANCE_NOT_AVAILABLE      (0x00000000)
#define     LFS_CRD_GUIDANCE_OFF                (0x00000001)
#define     LFS_CRD_GUIDANCE_SLOW_FLASH         (0x00000004)
#define     LFS_CRD_GUIDANCE_MEDIUM_FLASH       (0x00000008)
#define     LFS_CRD_GUIDANCE_QUICK_FLASH        (0x00000010)
#define     LFS_CRD_GUIDANCE_CONTINUOUS         (0x00000080)
#define     LFS_CRD_GUIDANCE_RED                (0x00000100)
#define     LFS_CRD_GUIDANCE_GREEN              (0x00000200)
#define     LFS_CRD_GUIDANCE_YELLOW             (0x00000400)
#define     LFS_CRD_GUIDANCE_BLUE               (0x00000800)
#define     LFS_CRD_GUIDANCE_CYAN               (0x00001000)
#define     LFS_CRD_GUIDANCE_MAGENTA            (0x00002000)
#define     LFS_CRD_GUIDANCE_WHITE              (0x00004000)

/* values of LFSCRDSTATUS.wDevice_Position
             LFSCRDDEVICEPOSITION.wPosition */

#define     LFS_CRD_DEVICEINPOSITION             (0)
#define     LFS_CRD_DEVICENOTINPOSITION          (1)
#define     LFS_CRD_DEVICEPOSUNKNOWN             (2)
#define     LFS_CRD_DEVICEPOSNOTSUPP             (3)

/*values of LFSCRDCAPS.wDispense_To */

#define     LFS_CRD_DISPTO_CONSUMER             (0x0001)
#define     LFS_CRD_DISPTO_TRANSPORT            (0x0002)

/*values of LFSCRDCARDUNIT.usStatus */

#define    LFS_CRD_STATCUOK                     (0)
#define    LFS_CRD_STATCULOW                    (1)
#define    LFS_CRD_STATCUEMPTY                  (2)
#define    LFS_CRD_STATCUINOP                   (3)
#define    LFS_CRD_STATCUMISSING                (4)
#define    LFS_CRD_STATCUHIGH                   (5)
#define    LFS_CRD_STATCUFULL                   (6)
#define    LFS_CRD_STATCUUNKNOWN                (7)

/*values of LFSCRDCARDUNIT.usType */

#define    LFS_CRD_SUPPLYBIN                    (1)
#define    LFS_CRD_RETAINBIN                    (2)

/* values of LFSCRDSTATUS.wShutter */

#define     LFS_CRD_SHTCLOSED                  (0)
#define     LFS_CRD_SHTOPEN                    (1)
#define     LFS_CRD_SHTJAMMED                  (2)
#define     LFS_CRD_SHTUNKNOWN                 (3)
#define     LFS_CRD_SHTNOTSUPPORTED            (4)

/* values of LFSCRDCAPS.wPower_On_Option,
             LFSCRDCAPS.wPower_Off_Option,
             LFSCRDRESET.usAction  */

#define     LFS_CRD_NOACTION                    (1)
#define     LFS_CRD_EJECT                       (2)
#define     LFS_CRD_RETAIN                      (3)
#define     LFS_CRD_EJECTTHENRETAIN             (4)

/*values of LFSCRDCUERROR.wFailure */

#define LFS_CRD_CARDUNITEMPTY                   (1)
#define LFS_CRD_CARDUNITERROR                   (2)
#define LFS_CRD_CARDUNITINVALID                 (3)

/* values of LFSCRDSLOTUNIT.wSlot_Status */
#define LFS_CRD_SLOT_MEDIAPRESENT               (1)
#define LFS_CRD_SLOT_MEDIANOTPRESENT            (2)
#define LFS_CRD_SLOT_MEDIAUNKNOW                (3)

/* LFS CRD Errors */

#define LFS_ERR_CRD_MEDIAJAM                    (-(CRD_SERVICE_OFFSET + 0))
#define LFS_ERR_CRD_NOMEDIA                     (-(CRD_SERVICE_OFFSET + 1))
#define LFS_ERR_CRD_MEDIARETAINED               (-(CRD_SERVICE_OFFSET + 2))
#define LFS_ERR_CRD_RETAINBINFULL               (-(CRD_SERVICE_OFFSET + 3))
#define LFS_ERR_CRD_SHUTTERFAIL                 (-(CRD_SERVICE_OFFSET + 4))
#define LFS_ERR_CRD_DEVICE_OCCUPIED             (-(CRD_SERVICE_OFFSET + 5))
#define LFS_ERR_CRD_CARDUNITERROR               (-(CRD_SERVICE_OFFSET + 6))
#define LFS_ERR_CRD_INVALIDCARDUNIT             (-(CRD_SERVICE_OFFSET + 7))
#define LFS_ERR_CRD_INVALID_PORT                (-(CRD_SERVICE_OFFSET + 8))
#define LFS_ERR_CRD_INVALIDRETAINBIN            (-(CRD_SERVICE_OFFSET + 9))
#define LFS_ERR_CRD_POWERSAVETOOSHORT           (-(CRD_SERVICE_OFFSET + 10))
#define LFS_ERR_CRD_POWERSAVEMEDIAPRESENT       (-(CRD_SERVICE_OFFSET + 11))
#define LFS_ERR_CRD_MEDIA_EXIST	                 (-(CRD_SERVICE_OFFSET + 12))
#define LFS_ERR_CRD_MEDIA_NOTEXIST              (-(CRD_SERVICE_OFFSET + 13))
/*=================================================================*/
/* CRD Info Command Structures and variables */
/*=================================================================*/

typedef struct _LFS_CRD_status
{
    WORD                  wDevice;
    WORD                  wDispenser;
    WORD                  wTransport;
    WORD                  wMedia;
    WORD                  wShutter;
    LPSTR                 lpstrExtra;
    DWORD                 dwGuid_Lights[LFS_CRD_GUIDLIGHTS_SIZE];
    WORD                  wDevice_Position;
    USHORT                usPower_Save_Recovery_Time;
} LFSCRDSTATUS, * LPLFSCRDSTATUS;

typedef struct _LFS_CRD_caps
{
    WORD                  wClass;
    BOOL                  bCompound;
    WORD                  wPower_On_Option;
    WORD                  wPower_Off_Option;
    BOOL                  bCard_Taken_Sensor;
    WORD                  wDispense_To;
    LPSTR                 lpstrExtra;
    DWORD                 dwGuid_Lights[LFS_CRD_GUIDLIGHTS_SIZE];
    BOOL                  bPower_Save_Control;
} LFSCRDCAPS, * LPLFSCRDCAPS;

typedef struct _LFS_CRD_cardunit
{
USHORT                    usNumber;
LPSTR                     lpstrCard_Name;
USHORT				      usCard_Type;
ULONG                     ulInitial_Count;
ULONG                     ulCount;
ULONG                     ulRetain_Count;
ULONG                     ulThreshold;
USHORT                    usStatus;
BOOL                      bHardware_Sensor;
} LFSCRDCARDUNIT, *LPLFSCRDCARDUNIT;

typedef struct _LFS_CRD_cu_info
{
USHORT                   usCount;
LPLFSCRDCARDUNIT         *lppList;
} LFSCRDCUINFO, *LPLFSCRDCUINFO;

typedef struct _LFS_crd_slot_info
{
USHORT                 usReal_Total_Slot_Count;
WORD                   wSlot_Status[LFS_CRD_SLOT_SIZE];
}LFSCRDSLOTINFO, *LPLFSCRDSLOTINFO;

/*=================================================================*/
/* CRD Execute Command Structures */
/*=================================================================*/

typedef struct _LFS_CRD_dispense
{
USHORT                  usNumber;
BOOL                    bPresent;
} LFSCRDDISPENSE, *LPLFSCRDDISPENSE;

typedef struct _LFS_CRD_retain_card
{
USHORT                  usNumber;
} LFSCRDRETAINCARD, *LPLFSCRDRETAINCARD;

typedef struct _LFS_CRD_reset
{
USHORT                usAction;
} LFSCRDRESET, *LPLFSCRDRESET;

typedef struct _LFS_CRD_set_guidlight
{
    WORD                  wGuid_Light;
    DWORD                 dwCommand;
} LFSCRDSETGUIDLIGHT, *LPLFSCRDSETGUIDLIGHT;

typedef struct _LFS_CRD_power_save_control
{
    USHORT	           usMax_Power_Save_Recovery_Time;
} LFSCRDPOWERSAVECONTROL, *LPLFSCRDPOWERSAVECONTROL;

typedef struct _LFS_crd_slot_deposit
{
    USHORT	usSlot_No;
}LFSCRDSLOTDEPOSIT,*LPLFSCRDSLOTDEPOSIT;

typedef struct _LFS_crd_slot_dispense
{
    USHORT	usSlot_No;
    BOOL	bPresent;
}LFSCRDSLOTDISPENSE,*LPLFSCRDSLOTDISPENSE;

/*=================================================================*/
/* CRD Message Structures */
/*=================================================================*/

typedef struct _LFS_CRD_media_detected
{
    WORD                  wPosition;
    USHORT                usNumber;
} LFSCRDMEDIADETECTED, *LPLFSCRDMEDIADETECTED;

typedef struct _LFS_CRD_cu_error
{
    WORD                  wFailure;
    LPLFSCRDCARDUNIT     lpCard_Unit;
} LFSCRDCUERROR, *LPLFSCRDCUERROR;

typedef struct _LFS_CRD_device_position
{
    WORD                  wPosition;
} LFSCRDDEVICEPOSITION, *LPLFSCRDDEVICEPOSITION;

typedef struct _LFS_CRD_power_save_change
{
    USHORT                usPower_Save_Recovery_Time;
} LFSCRDPOWERSAVECHANGE, *LPLFSCRDPOWERSAVECHANGE;

/*   restore alignment   */
#pragma pack(pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif  /* __INC_LFSCRD__H */