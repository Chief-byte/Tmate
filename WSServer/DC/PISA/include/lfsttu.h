/******************************************************************************
*                                                                             *
* LFSttu.h - Text Terminal Unit (TTU) definitions                             *
*                                                                             *
* Version 1.00                                                                  *
*                                                                             *
******************************************************************************/



#ifndef __INC_LFSTTU__H
#define __INC_LFSTTU__H

#ifdef __cplusplus
extern "C" {
#endif

#include    "lfsapi.h"

/*   be aware of alignment   */
#ifdef LFSPACK4
#pragma pack(push,4)
#else
#pragma pack(push,1)
#endif


/* LFSTTUCAPS.wClass 取值 */
#define     LFS_SERVICE_CLASS_TTU               (7)
#define     LFS_SERVICE_CLASS_NAME_TTU          "TTU"
#define     LFS_SERVICE_CLASS_VERSION_TTU       (0x0001)

#define     TTU_SERVICE_OFFSET                  (LFS_SERVICE_CLASS_TTU * 100)

/* 信息指令 */
#define     LFS_INF_TTU_STATUS                  (TTU_SERVICE_OFFSET + 1)
#define     LFS_INF_TTU_CAPABILITIES            (TTU_SERVICE_OFFSET + 2)
#define     LFS_INF_TTU_FORM_LIST               (TTU_SERVICE_OFFSET + 3)
#define     LFS_INF_TTU_QUERY_FORM              (TTU_SERVICE_OFFSET + 4)
#define     LFS_INF_TTU_QUERY_FIELD             (TTU_SERVICE_OFFSET + 5)
#define     LFS_INF_TTU_KEY_DETAIL              (TTU_SERVICE_OFFSET + 6)

/* 执行指令 */
#define     LFS_CMD_TTU_BEEP                    (TTU_SERVICE_OFFSET + 1)
#define     LFS_CMD_TTU_CLEARSCREEN             (TTU_SERVICE_OFFSET + 2)
#define     LFS_CMD_TTU_DISPLIGHT               (TTU_SERVICE_OFFSET + 3)
#define     LFS_CMD_TTU_SET_LED                 (TTU_SERVICE_OFFSET + 4)
#define     LFS_CMD_TTU_SET_RESOLUTION          (TTU_SERVICE_OFFSET + 5)
#define     LFS_CMD_TTU_WRITE_FORM              (TTU_SERVICE_OFFSET + 6)
#define     LFS_CMD_TTU_READ_FORM               (TTU_SERVICE_OFFSET + 7)
#define     LFS_CMD_TTU_WRITE                   (TTU_SERVICE_OFFSET + 8)
#define     LFS_CMD_TTU_READ                    (TTU_SERVICE_OFFSET + 9)
#define     LFS_CMD_TTU_RESET                   (TTU_SERVICE_OFFSET + 10)
#define     LFS_CMD_TTU_DEFINE_KEYS             (TTU_SERVICE_OFFSET + 11)
#define     LFS_CMD_TTU_POWER_SAVE_CONTROL      (TTU_SERVICE_OFFSET + 12)

/* 事件 */
#define    LFS_EXEE_TTU_FIELDERROR              (TTU_SERVICE_OFFSET + 1)
#define    LFS_EXEE_TTU_FIELDWARNING            (TTU_SERVICE_OFFSET + 2)
#define    LFS_EXEE_TTU_KEY                     (TTU_SERVICE_OFFSET + 3)
#define    LFS_SRVE_TTU_DEVICEPOSITION          (TTU_SERVICE_OFFSET + 4)
#define    LFS_SRVE_TTU_POWER_SAVE_CHANGE       (TTU_SERVICE_OFFSET + 5)

/* LFSTTUSTATUS.fwDevice 取值 */
#define     LFS_TTU_DEVONLINE                   LFS_STAT_DEVONLINE
#define     LFS_TTU_DEVOFFLINE                  LFS_STAT_DEVOFFLINE
#define     LFS_TTU_DEVPOWEROFF                 LFS_STAT_DEVPOWEROFF
#define     LFS_TTU_DEVBUSY                     LFS_STAT_DEVBUSY
#define     LFS_TTU_DEVNODEVICE                 LFS_STAT_DEVNODEVICE
#define     LFS_TTU_DEVHWERROR                  LFS_STAT_DEVHWERROR
#define     LFS_TTU_DEVUSERERROR                LFS_STAT_DEVUSERERROR

/* LFSTTUSTATUS.wKeyboard 取值*/
#define     LFS_TTU_KBDNA                       (0)
#define     LFS_TTU_KBDON                       (1)
#define     LFS_TTU_KBDOFF                      (2)

/* LFSTTUSTATUS.wKeyLock 取值 */
#define     LFS_TTU_KBDLOCKNA                   (0)
#define     LFS_TTU_KBDLOCKON                   (1)
#define     LFS_TTU_KBDLOCKOFF                  (2)

#define     LFS_TTU_LEDS_MAX                    (8)

/* LFSTTUSTATUS.fwLEDs 取值 */
#define     LFS_TTU_LEDNA                       (0x0000)
#define     LFS_TTU_LEDOFF                      (0x0001)
#define     LFS_TTU_LEDSLOWFLASH                (0x0002)
#define     LFS_TTU_LEDMEDIUMFLASH              (0x0004)
#define     LFS_TTU_LEDQUICKFLASH               (0x0008)
#define     LFS_TTU_LEDCONTINUOUS               (0x0080)

/* values of LFSTTUSTATUS.wDevicePosition
LFSTTUDEVICEPOSITION.wPosition */
#define LFS_TTU_DEVICEINPOSITION	(0)
#define LFS_TTU_DEVICENOTINPOSITION	(1)
#define LFS_TTU_DEVICEPOSUNKNOWN	(2)
#define LFS_TTU_DEVICEPOSNOTSUPP	(3)


/* LFSTTUCAPS.fwType 取值 */
#define     LFS_TTU_FIXED                       (0x0001)
#define     LFS_TTU_REMOVABLE                   (0x0002)

/* LFSTTUCAPS.fwCharSupport， LFSTTUWRITE.fwCharSupport 取值 */
#define     LFS_TTU_ASCII                       (0x0001)
#define     LFS_TTU_UNICODE                     (0x0002)

/* LFSTTUFRMFIELD.fwType 取值 */
#define     LFS_TTU_FIELDTEXT                   (0)
#define     LFS_TTU_FIELDINVISIBLE              (1)
#define     LFS_TTU_FIELDPASSWORD               (2)

/* LFSTTUFRMFIELD.fwClass 取值 */
#define     LFS_TTU_CLASSOPTIONAL               (0)
#define     LFS_TTU_CLASSSTATIC                 (1)
#define     LFS_TTU_CLASSREQUIRED               (2)

/* LFSTTUFRMFIELD.fwAccess 取值 */
#define     LFS_TTU_ACCESSREAD                  (0x0001)
#define     LFS_TTU_ACCESSWRITE                 (0x0002)

/* LFSTTUFRMFIELD.fwOverflow 取值 */
#define     LFS_TTU_OVFTERMINATE                (0)
#define     LFS_TTU_OVFTRUNCATE                 (1)
#define     LFS_TTU_OVFOVERWRITE                (2)

/* LFSTTUWRITE.fwMode 取值 */
#define     LFS_TTU_POSRELATIVE                 (0)
#define     LFS_TTU_POSABSOLUTE                 (1)

/* LFSTTUWRITE.fwTextAttr 取值 */
#define     LFS_TTU_TEXTUNDERLINE               (0x0001)
#define     LFS_TTU_TEXTINVERTED                (0x0002)
#define     LFS_TTU_TEXTFLASH                   (0x0004)

/* LFSTTUFRMREAD.fwEchoMode取值 */
#define     LFS_TTU_ECHOTEXT                    (0)
#define     LFS_TTU_ECHOINVISIBLE               (1)
#define     LFS_TTU_ECHOPASSWORD                (2)

#define     LFS_TTU_BEEPOFF                     (0x0001)
#define     LFS_TTU_BEEPKEYPRESS                (0x0002)
#define     LFS_TTU_BEEPEXCLAMATION             (0x0004)
#define     LFS_TTU_BEEPWARNING                 (0x0008)
#define     LFS_TTU_BEEPERROR                   (0x0010)
#define     LFS_TTU_BEEPCRITICAL                (0x0020)
#define     LFS_TTU_BEEPCONTINUOUS              (0x0080)

/*LFSTTUFIELDFAIL.wFailure 取值 */

#define    LFS_TTU_FIELDREQUIRED            (0)
#define    LFS_TTU_FIELDSTATICOVWR          (1)
#define    LFS_TTU_FIELDOVERFLOW            (2)
#define    LFS_TTU_FIELDNOTFOUND            (3)
#define    LFS_TTU_FIELDNOTREAD             (4)
#define    LFS_TTU_FIELDNOTWRITE            (5)
#define    LFS_TTU_FIELDTYPENOTSUPPORTED    (6)
#define    LFS_TTU_CHARSETFORM              (7)

/* LFSTTUKEYDETAIL.lpwCommandKeys 取值 */

#define LFS_TTU_NOKEY                     (0)
#define LFS_TTU_CK_ENTER                  (1)
#define LFS_TTU_CK_CANCEL                 (2)
#define LFS_TTU_CK_CLEAR                  (3)
#define LFS_TTU_CK_BACKSPACE              (4)
#define LFS_TTU_CK_HELP                   (5)
#define LFS_TTU_CK_00                     (6)
#define LFS_TTU_CK_000                    (7)
#define LFS_TTU_CK_ARROWUP                (8)
#define LFS_TTU_CK_ARROWDOWN              (9)
#define LFS_TTU_CK_ARROWLEFT              (10)
#define LFS_TTU_CK_ARROWRIGHT             (11)
#define LFS_TTU_CK_OEM1                   (12)
#define LFS_TTU_CK_OEM2                   (13)
#define LFS_TTU_CK_OEM3                   (14)
#define LFS_TTU_CK_OEM4                   (15)
#define LFS_TTU_CK_OEM5                   (16)
#define LFS_TTU_CK_OEM6                   (17)
#define LFS_TTU_CK_OEM7                   (18)
#define LFS_TTU_CK_OEM8                   (19)
#define LFS_TTU_CK_OEM9                   (20)
#define LFS_TTU_CK_OEM10                  (21)
#define LFS_TTU_CK_OEM11                  (22)
#define LFS_TTU_CK_OEM12                  (23)
#define LFS_TTU_CK_FDK01                  (24)
#define LFS_TTU_CK_FDK02                  (25)
#define LFS_TTU_CK_FDK03                  (26)
#define LFS_TTU_CK_FDK04                  (27)
#define LFS_TTU_CK_FDK05                  (28)
#define LFS_TTU_CK_FDK06                  (29)
#define LFS_TTU_CK_FDK07                  (30)
#define LFS_TTU_CK_FDK08                  (31)
#define LFS_TTU_CK_FDK09                  (32)
#define LFS_TTU_CK_FDK10                  (33)
#define LFS_TTU_CK_FDK11                  (34)
#define LFS_TTU_CK_FDK12                  (35)
#define LFS_TTU_CK_FDK13                  (36)
#define LFS_TTU_CK_FDK14                  (37)
#define LFS_TTU_CK_FDK15                  (38)
#define LFS_TTU_CK_FDK16                  (39)
#define LFS_TTU_CK_FDK17                  (40)
#define LFS_TTU_CK_FDK18                  (41)
#define LFS_TTU_CK_FDK19                  (42)
#define LFS_TTU_CK_FDK20                  (43)
#define LFS_TTU_CK_FDK21                  (44)
#define LFS_TTU_CK_FDK22                  (45)
#define LFS_TTU_CK_FDK23                  (46)
#define LFS_TTU_CK_FDK24                  (47)
#define LFS_TTU_CK_FDK25                  (48)
#define LFS_TTU_CK_FDK26                  (49)
#define LFS_TTU_CK_FDK27                  (50)
#define LFS_TTU_CK_FDK28                  (51)
#define LFS_TTU_CK_FDK29                  (52)
#define LFS_TTU_CK_FDK30                  (53)
#define LFS_TTU_CK_FDK31                  (54)
#define LFS_TTU_CK_FDK32                  (55)

/* 错误码 */ 

#define     LFS_ERR_TTU_FIELDERROR              (-(TTU_SERVICE_OFFSET + 1))
#define     LFS_ERR_TTU_FIELDINVALID            (-(TTU_SERVICE_OFFSET + 2))
#define     LFS_ERR_TTU_FIELDNOTFOUND           (-(TTU_SERVICE_OFFSET + 3))
#define     LFS_ERR_TTU_FIELDSPECFAILURE        (-(TTU_SERVICE_OFFSET + 4))
#define     LFS_ERR_TTU_FORMINVALID             (-(TTU_SERVICE_OFFSET + 5))
#define     LFS_ERR_TTU_FORMNOTFOUND            (-(TTU_SERVICE_OFFSET + 6))
#define     LFS_ERR_TTU_INVALIDLED              (-(TTU_SERVICE_OFFSET + 7))
#define     LFS_ERR_TTU_KEYCANCELED             (-(TTU_SERVICE_OFFSET + 8))
#define     LFS_ERR_TTU_MEDIAOVERFLOW           (-(TTU_SERVICE_OFFSET + 9))
#define     LFS_ERR_TTU_RESNOTSUPP              (-(TTU_SERVICE_OFFSET + 10))
#define     LFS_ERR_TTU_CHARSETDATA             (-(TTU_SERVICE_OFFSET + 11))
#define     LFS_ERR_TTU_KEYINVALID              (-(TTU_SERVICE_OFFSET + 12))
#define     LFS_ERR_TTU_KEYNOTSUPPORTED         (-(TTU_SERVICE_OFFSET + 13))
#define     LFS_ERR_TTU_NOACTIVEKEYS            (-(TTU_SERVICE_OFFSET + 14))
#define     LFS_ERR_TTU_POWERSAVETOOSHORT       (-(TTU_SERVICE_OFFSET + 15))
#define     LFS_ERR_TTU_POWERSAVEMEDIAPRESENT   (-(TTU_SERVICE_OFFSET + 16))

/*=================================================================*/
/*信息指令 执行指令 结构体 */
/*=================================================================*/

typedef struct _LFS_TTU_status
{
WORD				wDevice;
WORD				wKeyboard;
WORD				wKeylock;
WORD				wLEDs[LFS_TTU_LEDS_MAX];
WORD				wDisplay_SizeX;
WORD				wDisplay_SizeY;
LPSTR				lpstrExtra;
WORD 				wDevice_Position;
USHORT 				usPower_Save_Recovery_Time;
} LFSTTUSTATUS, *LPLFSTTUSTATUS;

typedef struct _LFS_TTU_resolution 
{
WORD				wSizeX; 
WORD				wSizeY;
} LFSTTURESOLUTION, *LPLFSTTURESOLUTION;

typedef struct _LFS_TTU_caps
{
WORD				wClass;
WORD				wType;
LPLFSTTURESOLUTION         *lppResolutions;
WORD				wNum_Of_LEDs;
BOOL				bKey_Lock;
BOOL				bDisplay_Light;
BOOL				bCursor;
BOOL				bForms;
WORD				wChar_Support;
LPSTR				lpstrExtra;
BOOL 				bPower_Save_Control;
} LFSTTUCAPS, *LPLFSTTUCAPS;

typedef struct _LFS_TTU_frm_header
{
LPSTR				lpstrForm_Name;
WORD				wWidth;
WORD				wHeight;
WORD				wVersion_Major;
WORD				wVersion_Minor;
WORD				wChar_Support;
LPSTR				lpstrFields;
WORD 				wLanguage_ID;
} LFSTTUFRMHEADER, *LPLFSTTUFRMHEADER;

typedef struct _LFS_TTU_query_field
{
LPSTR				lpstrForm_Name;
LPSTR				lpstrField_Name;
} LFSTTUQUERYFIELD, *LPLFSTTUQUERYFIELD;

typedef struct _LFS_TTU_frm_field
{
LPSTR				lpstrField_Name; 
WORD				wType; 
WORD				wClass; 
WORD				wAccess; 
WORD				wOverflow; 
LPSTR				lpstrFormat;
WORD 				wLanguageID;
} LFSTTUFRMFIELD, *LPLFSTTUFRMFIELD;

typedef struct _LFS_TTU_key_detail
{
LPSTR				lpstrKeys; 
LPWSTR			       lpwstrKeys;
LPWORD                      lpwCommand_Keys;
} LFSTTUKEYDETAIL, *LPLFSTTUKEYDETAIL;

typedef struct _LFS_TTU_clear_screen
{
WORD				wPositionX; 
WORD				wPositionY;
WORD				wWidth;
WORD				wHeight;
} LFSTTUCLEARSCREEN, *LPLFSTTUCLEARSCREEN;

typedef struct _LFS_TTU_disp_light
{
BOOL   			       bMode; 
} LFSTTUDISPLIGHT, *LPLFSTTUDISPLIGHT;

typedef struct _LFS_TTU_set_leds
{
WORD				wLED;
WORD				wCommand;
} LFSTTUSETLEDS, *LPLFSTTUSETLEDS;

typedef struct _LFS_TTU_write_form
{
LPSTR				lpstrForm_Name;
BOOL				bClear_Screen;
LPSTR				lpstrFields;
LPSTR				lpstrUNICODE_Fields;
} LFSTTUWRITEFORM, *LPLFSTTUWRITEFORM;

typedef struct _LFS_TTU_read_form
{
LPSTR				lpstrFields;
LPWSTR    			lpwstrUNICODE_Fields;
} LFSTTUREADFORM, *LPLFSTTUREADFORM;

typedef struct _LFS_TTU_read_form_out
{
LPSTR				lpstrFields;
LPWSTR    			lpwstrUNICODE_Fields;
} LFSTTUREADFORMOUT, *LPLFSTTUREADFORMOUT;

typedef struct _LFS_TTU_write
{
WORD			    wMode;
SHORT				wPosX;
SHORT				wPosY;
WORD				wText_Attr;
LPSTR				lpstrText;
LPWSTR    			lpwstrUNICODE_Text;
} LFSTTUWRITE, *LPLFSTTUWRITE;

typedef struct _LFS_TTU_read
{
WORD				wNum_Of_Chars;
WORD				wMode;
SHORT				wPosX;
SHORT				wPosY;
WORD				wEcho_Mode;
WORD				wEcho_Attr;
BOOL                bCursor; 
BOOL                bFlush; 
BOOL                bAuto_End; 
LPSTR				lpstrActive_Keys;
LPWSTR    			lpwszActive_UNICODE_Keys;
LPWORD			lpwActive_Command_Keys;
LPWORD			lpwTerminate_Command_Keys;
} LFSTTUREAD, *LPLFSTTUREAD;

typedef struct _LFS_TTU_read_in
{
LPSTR				lpstrInput;
LPWSTR    			lpwstrUNICODE_Input;
} LFSTTUREADIN, *LPLFSTTUREADIN;

typedef struct _LFS_TTU_def_keys
{
LPSTR	lpstrActive_Keys;
LPWSTR	       lpwszActive_UNICODE_Keys;
LPWORD	      lpwActive_CommandKeys;
LPWORD	         lpwTerminate_CommandKeys;
} LFSTTUDEFKEYS, *LPLFSTTUDEFKEYS;

typedef struct _LFS_TTU_power_save_control
{
USHORT usMax_Power_Save_Recovery_Time;
} LFSTTUPOWERSAVECONTROL, *LPLFSTTUPOWERSAVECONTROL;

/*=================================================================*/
/*事件结构体 */
/*=================================================================*/

typedef struct _LFS_ttu_field_failure
{
LPSTR				lpstrForm_Name;
LPSTR			       lpstrField_Name;
WORD                       wFailure; 

} LFSTTUFIELDFAIL, *LPLFSTTUFIELDFAIL;

typedef struct _LFS_ttu_key
{
LPSTR				lpstrKeys; 
LPWSTR			lpwstrKeys;
LPWORD                    lpwCommand_Keys;
} LFSTTUKEY, *LPLFSTTUKEY;

typedef struct _LFS_TTU_device_position
{
WORD wPosition;
} LFSTTUDEVICEPOSITION, *LPLFSTTUDEVICEPOSITION;

typedef struct _LFS_TTU_power_save_change
{
USHORT usPower_Save_Recovery_Time;
} LFSTTUPOWERSAVECHANGE, *LPLFSTTUPOWERSAVECHANGE;
/* restore alignment */
#pragma pack(pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif  /* __INC_LFSTTU__H */