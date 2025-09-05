/******************************************************************************
*                                                                            *
* LFScdm.h  -  Cash Dispenser Device (CDM) definitions                       *
*                                                                            *
* Version 1.00                                                               *
*                                                                            *
******************************************************************************/

#ifndef __INC_LFSCDM__H
#define __INC_LFSCDM__H

#ifdef __cplusplus
extern "C" {
#endif

#include "lfsapi.h"

/*  对齐方式   */
#pragma pack(push,1)

/* LFSCDMCAPS.wClass 取值*/

#define     LFS_SERVICE_CLASS_CDM               (3)
#define     LFS_SERVICE_CLASS_VERSION_CDM       0x0001
#define     LFS_SERVICE_CLASS_NAME_CDM          "CDM"

#define     CDM_SERVICE_OFFSET                  (LFS_SERVICE_CLASS_CDM * 100)

/* 信息指令 */

#define     LFS_INF_CDM_STATUS                  (CDM_SERVICE_OFFSET + 1)
#define     LFS_INF_CDM_CAPABILITIES            (CDM_SERVICE_OFFSET + 2)
#define     LFS_INF_CDM_CASH_UNIT_INFO          (CDM_SERVICE_OFFSET + 3)
#define     LFS_INF_CDM_TELLER_INFO             (CDM_SERVICE_OFFSET + 4)
#define     LFS_INF_CDM_CURRENCY_EXP            (CDM_SERVICE_OFFSET + 6)
#define     LFS_INF_CDM_MIX_TYPES               (CDM_SERVICE_OFFSET + 7)
#define     LFS_INF_CDM_MIX_TABLE               (CDM_SERVICE_OFFSET + 8)
#define     LFS_INF_CDM_PRESENT_STATUS          (CDM_SERVICE_OFFSET + 9)
#define     LFS_INF_CDM_GET_BLACKLIST           (CDM_SERVICE_OFFSET + 11)
#define     LFS_INF_CDM_REPLENISH_TARGET        (CDM_SERVICE_OFFSET + 98)

/* 执行指令 */

#define     LFS_CMD_CDM_DENOMINATE              (CDM_SERVICE_OFFSET + 1)
#define     LFS_CMD_CDM_DISPENSE                (CDM_SERVICE_OFFSET + 2)
#define     LFS_CMD_CDM_PRESENT                 (CDM_SERVICE_OFFSET + 3)
#define     LFS_CMD_CDM_REJECT                  (CDM_SERVICE_OFFSET + 4)
#define     LFS_CMD_CDM_RETRACT                 (CDM_SERVICE_OFFSET + 5)
#define     LFS_CMD_CDM_OPEN_SHUTTER            (CDM_SERVICE_OFFSET + 7)
#define     LFS_CMD_CDM_CLOSE_SHUTTER           (CDM_SERVICE_OFFSET + 8)
#define     LFS_CMD_CDM_SET_TELLER_INFO         (CDM_SERVICE_OFFSET + 9)
#define     LFS_CMD_CDM_SET_CASH_UNIT_INFO      (CDM_SERVICE_OFFSET + 10)
#define     LFS_CMD_CDM_START_EXCHANGE          (CDM_SERVICE_OFFSET + 11)
#define     LFS_CMD_CDM_END_EXCHANGE            (CDM_SERVICE_OFFSET + 12)
#define     LFS_CMD_CDM_OPEN_SAFE_DOOR          (CDM_SERVICE_OFFSET + 13)
#define     LFS_CMD_CDM_CALIBRATE_CASH_UNIT     (CDM_SERVICE_OFFSET + 15)
#define     LFS_CMD_CDM_SET_MIX_TABLE           (CDM_SERVICE_OFFSET + 20)
#define     LFS_CMD_CDM_RESET                   (CDM_SERVICE_OFFSET + 21)
#define     LFS_CMD_CDM_TEST_CASH_UNITS         (CDM_SERVICE_OFFSET + 22)
#define     LFS_CMD_CDM_COUNT                   (CDM_SERVICE_OFFSET + 23)
#define 	LFS_CMD_CDM_SET_GUIDANCE_LIGHT 		(CDM_SERVICE_OFFSET + 24) 
#define 	LFS_CMD_CDM_POWER_SAVE_CONTROL 		(CDM_SERVICE_OFFSET + 25) 
#define 	LFS_CMD_CDM_PREPARE_DISPENSE 		(CDM_SERVICE_OFFSET + 26) 

#define     LFS_CMD_CDM_SET_BLACKLIST           (CDM_SERVICE_OFFSET + 27)
#define     LFS_CMD_CDM_CASH_UNIT_COUNT         (CDM_SERVICE_OFFSET + 93)
#define     LFS_CMD_CDM_REPLENISH               (CDM_SERVICE_OFFSET + 94)
#define     LFS_CMD_CDM_SET_FSN_INFO		    (CDM_SERVICE_OFFSET + 95)

/*事件 */
#define     LFS_SRVE_CDM_SAFEDOOROPEN           (CDM_SERVICE_OFFSET + 1)
#define     LFS_SRVE_CDM_SAFEDOORCLOSED         (CDM_SERVICE_OFFSET + 2)
#define     LFS_USRE_CDM_CASHUNITTHRESHOLD      (CDM_SERVICE_OFFSET + 3)
#define     LFS_SRVE_CDM_CASHUNITINFOCHANGED    (CDM_SERVICE_OFFSET + 4)
#define     LFS_SRVE_CDM_TELLERINFOCHANGED      (CDM_SERVICE_OFFSET + 5)
#define     LFS_EXEE_CDM_DELAYEDDISPENSE        (CDM_SERVICE_OFFSET + 6)
#define     LFS_EXEE_CDM_STARTDISPENSE          (CDM_SERVICE_OFFSET + 7)
#define     LFS_EXEE_CDM_CASHUNITERROR          (CDM_SERVICE_OFFSET + 8)
#define     LFS_SRVE_CDM_ITEMSTAKEN             (CDM_SERVICE_OFFSET + 9)
#define     LFS_EXEE_CDM_PARTIALDISPENSE        (CDM_SERVICE_OFFSET + 10)
#define     LFS_EXEE_CDM_SUBDISPENSEOK          (CDM_SERVICE_OFFSET + 11)
#define     LFS_SRVE_CDM_ITEMSPRESENTED         (CDM_SERVICE_OFFSET + 13)
#define     LFS_SRVE_CDM_COUNTS_CHANGED         (CDM_SERVICE_OFFSET + 14)
#define     LFS_EXEE_CDM_INCOMPLETEDISPENSE     (CDM_SERVICE_OFFSET + 15)
#define     LFS_EXEE_CDM_NOTEERROR              (CDM_SERVICE_OFFSET + 16)
#define     LFS_SRVE_CDM_MEDIADETECTED          (CDM_SERVICE_OFFSET + 17)
#define 	LFS_EXEE_CDM_INPUT_P6 				(CDM_SERVICE_OFFSET + 18) 
#define 	LFS_SRVE_CDM_DEVICEPOSITION 		(CDM_SERVICE_OFFSET + 19) 
#define		LFS_SRVE_CDM_POWER_SAVE_CHANGE 		(CDM_SERVICE_OFFSET + 20) 
#define     LFS_EXEE_CDM_INCOMPLETEREPLENISH    (CDM_SERVICE_OFFSET + 98)																
/* LFSCDMSTATUS.wDevice 取值*/
#define     LFS_CDM_DEVONLINE                   LFS_STAT_DEVONLINE
#define     LFS_CDM_DEVOFFLINE                  LFS_STAT_DEVOFFLINE
#define     LFS_CDM_DEVPOWEROFF                 LFS_STAT_DEVPOWEROFF
#define     LFS_CDM_DEVNODEVICE                 LFS_STAT_DEVNODEVICE
#define     LFS_CDM_DEVHWERROR                  LFS_STAT_DEVHWERROR
#define     LFS_CDM_DEVUSERERROR                LFS_STAT_DEVUSERERROR
#define     LFS_CDM_DEVBUSY                     LFS_STAT_DEVBUSY
#define 	LFS_CDM_DEVFRAUDATTEMPT 			LFS_STAT_DEVFRAUDATTEMPT 
#define     LFS_CDM_CASHJAMMED                  (9)
/* LFSCDMSTATUS.wSafe_Door 取值*/

#define     LFS_CDM_DOORNOTSUPPORTED            (1)
#define     LFS_CDM_DOOROPEN                    (2)
#define     LFS_CDM_DOORCLOSED                  (3)
#define     LFS_CDM_DOORUNKNOWN                 (5)

/* LFSCDMSTATUS.wDispenser 取值 */

#define     LFS_CDM_DISPOK                      (0)
#define     LFS_CDM_DISPCUSTATE                 (1)
#define     LFS_CDM_DISPCUSTOP                  (2)
#define     LFS_CDM_DISPCUUNKNOWN               (3)

/* LFSCDMSTATUS.wIntermediate_Stacker 取值 */

#define     LFS_CDM_ISEMPTY                     (0)
#define     LFS_CDM_ISNOTEMPTY                  (1)
#define     LFS_CDM_ISNOTEMPTYCUST              (2)
#define     LFS_CDM_ISNOTEMPTYUNK               (3)
#define     LFS_CDM_ISUNKNOWN                   (4)
#define     LFS_CDM_ISNOTSUPPORTED              (5)

#define 	LFS_CDM_GUIDLIGHTS_SIZE 			(32) 
#define 	LFS_CDM_GUIDLIGHTS_MAX 				(LFS_CDM_GUIDLIGHTS_SIZE - 1) 

/* LFSCDMSTATUS.dwGuid_Lights[...]取值 */
/* LFSCDMCAPS.dwGuid_Lights[...]取值 */

#define 	LFS_CDM_GUIDANCE_POSOUTNULL 		(0) 
#define 	LFS_CDM_GUIDANCE_POSOUTLEFT 		(1) 
#define 	LFS_CDM_GUIDANCE_POSOUTRIGHT 		(2) 
#define		LFS_CDM_GUIDANCE_POSOUTCENTER 		(3) 
#define	 	LFS_CDM_GUIDANCE_POSOUTTOP 			(4) 
#define 	LFS_CDM_GUIDANCE_POSOUTBOTTOM 		(5) 
#define 	LFS_CDM_GUIDANCE_POSOUTFRONT 		(6) 
#define 	LFS_CDM_GUIDANCE_POSOUTREAR 		(7)

#define 	LFS_CDM_GUIDANCE_OFF 				(0x00000001) 
#define 	LFS_CDM_GUIDANCE_SLOW_FLASH 		(0x00000004) 
#define 	LFS_CDM_GUIDANCE_MEDIUM_FLASH 		(0x00000008) 
#define 	LFS_CDM_GUIDANCE_QUICK_FLASH 		(0x00000010) 
#define 	LFS_CDM_GUIDANCE_CONTINUOUS 		(0x00000080) 
#define 	LFS_CDM_GUIDANCE_RED 				(0x00000100) 
#define 	LFS_CDM_GUIDANCE_GREEN 				(0x00000200) 
#define	 	LFS_CDM_GUIDANCE_YELLOW 			(0x00000400) 
#define		LFS_CDM_GUIDANCE_BLUE 				(0x00000800) 
#define 	LFS_CDM_GUIDANCE_CYAN 				(0x00001000) 
#define 	LFS_CDM_GUIDANCE_MAGENTA 			(0x00002000) 
#define 	LFS_CDM_GUIDANCE_WHITE 				(0x00004000) 
#define 	LFS_CDM_GUIDANCE_NOT_AVAILABLE		(0x0000) 

/* LFSCDMSTATUS.wDevice_Position  取值 */
/* LFSCDMDEVICEPOSITION.wPosition   取值 */

#define 	LFS_CDM_DEVICEINPOSITION 				(0) 
#define 	LFS_CDM_DEVICENOTINPOSITION				(1) 
#define 	LFS_CDM_DEVICEPOSUNKNOWN 				(2) 
#define 	LFS_CDM_DEVICEPOSNOTSUPP 				(3) 

/* LFSCDMOUTPOS.wShutter 取值 */

#define     LFS_CDM_SHTCLOSED                   (0)
#define     LFS_CDM_SHTOPEN                     (1)
#define     LFS_CDM_SHTJAMMED                   (2)
#define     LFS_CDM_SHTUNKNOWN                  (3)
#define     LFS_CDM_SHTNOTSUPPORTED             (4)

/* LFSCDMOUTPOS.wPositionStatus 取值 */

#define     LFS_CDM_PSEMPTY                     (0)
#define     LFS_CDM_PSNOTEMPTY                  (1)
#define     LFS_CDM_PSUNKNOWN                   (2)
#define     LFS_CDM_PSNOTSUPPORTED              (3)

/* LFSCDMOUTPOS.wTransport 取值 */

#define     LFS_CDM_TPOK                        (0)
#define     LFS_CDM_TPINOP                      (1)
#define     LFS_CDM_TPUNKNOWN                   (2)
#define     LFS_CDM_TPNOTSUPPORTED              (3)

/* LFSCDMOUTPOS.wTransport_Status 取值 */

#define     LFS_CDM_TPSTATEMPTY                 (0)
#define     LFS_CDM_TPSTATNOTEMPTY              (1)
#define     LFS_CDM_TPSTATNOTEMPTYCUST          (2)
#define     LFS_CDM_TPSTATNOTEMPTY_UNK          (3)
#define     LFS_CDM_TPSTATNOTSUPPORTED          (4)

/* LFSCDMSTATUS.wCash_Count_Status取值 */

#define     LFS_CDM_CASHCOUNTSTATUSOK           (0)
#define     LFS_CDM_CASHCOUNTSTATUSINOP         (1)
#define     LFS_CDM_CASHCOUNTSTATUSUNKNOWN      (2)
#define     LFS_CDM_CASHCOUNTSTATUSNOTSUPP      (3)


/* LFSCDMCAPS.wType 取值 */

#define     LFS_CDM_TELLERBILL                  (0)
#define     LFS_CDM_SELFSERVICEBILL             (1)
#define     LFS_CDM_TELLERCOIN                  (2)
#define     LFS_CDM_SELFSERVICECOIN             (3)

/* LFSCDMCAPS.wRetract_Areas */
/* LFSCDMRETRACT.usRetract_Area 取值 */

#define     LFS_CDM_RA_RETRACT                  (0x0001)
#define     LFS_CDM_RA_TRANSPORT                (0x0002)
#define     LFS_CDM_RA_STACKER                  (0x0004)
#define     LFS_CDM_RA_REJECT                   (0x0008)
#define     LFS_CDM_RA_NOTSUPP                  (0x0010)
#define 	LFS_CDM_RA_ITEMCASSETTE 			(0x0020) 

/* LFSCDMCAPS.wRetract_Transport_Actions */
/* LFSCDMCAPS.wRetract_Stacker_Actions  取值 */

#define     LFS_CDM_PRESENT                     (0x0001)
#define     LFS_CDM_RETRACT                     (0x0002)
#define     LFS_CDM_REJECT                      (0x0004)
#define     LFS_CDM_NOTSUPP                     (0x0008)
#define 	LFS_CDM_ITEMCASSETTE 				(0x0010) 

/* LFSCDMCAPS.wMove_Items 取值 */

#define     LFS_CDM_FROMCU                      (0x0001)
#define     LFS_CDM_TOCU                        (0x0002)
#define     LFS_CDM_TOTRANSPORT                 (0x0004)

/* LFSCDMCASHUNIT.usType 取值 */

#define     LFS_CDM_TYPENA                      (1)
#define     LFS_CDM_TYPEREJECTCASSETTE          (2)
#define     LFS_CDM_TYPEBILLCASSETTE            (3)
#define     LFS_CDM_TYPECOINCYLINDER            (4)
#define     LFS_CDM_TYPECOINDISPENSER           (5)
#define     LFS_CDM_TYPERETRACTCASSETTE         (6)
#define     LFS_CDM_TYPECOUPON                  (7)
#define     LFS_CDM_TYPEDOCUMENT                (8)
#define     LFS_CDM_TYPEREPCONTAINER           (11)
#define     LFS_CDM_TYPERECYCLING              (12)

/* LFSCDMCASHUNIT.usStatus 取值 */

#define     LFS_CDM_STATCUOK                    (0)
#define     LFS_CDM_STATCUFULL                  (1)
#define     LFS_CDM_STATCUHIGH                  (2)
#define     LFS_CDM_STATCULOW                   (3)
#define     LFS_CDM_STATCUEMPTY                 (4)
#define     LFS_CDM_STATCUINOP                  (5)
#define     LFS_CDM_STATCUMISSING               (6)
#define     LFS_CDM_STATCUNOVAL                 (7)
#define     LFS_CDM_STATCUNOREF                 (8)
#define     LFS_CDM_STATCUMANIP                 (9)

/* LFSCDMMIXTYPE.usMix_Type 取值 */

#define     LFS_CDM_MIXALGORITHM                (1)
#define     LFS_CDM_MIXTABLE                    (2)

/* LFSCDMMIXTYPE.usMix_Number 取值 */

#define     LFS_CDM_INDIVIDUAL                  (0)

/* LFSCDMMIXTYPE.usSub_Type 取值 */
#define     LFS_CDM_MIX_MINIMUM_NUMBER_OF_BILLS            (1)
#define     LFS_CDM_MIX_EQUAL_EMPTYING_OF_CASH_UNITS       (2)
#define     LFS_CDM_MIX_MAXIMUM_NUMBER_OF_CASH_UNITS       (3)

/* LFSCDMPRESENTSTATUS.wPresent_State 取值 */

#define     LFS_CDM_PRESENTED                   (1)
#define     LFS_CDM_NOTPRESENTED                (2)
#define     LFS_CDM_UNKNOWN                     (3)

/* LFSCDMDISPENSE.wPosition */
/* LFSCDMCAPS.wPositions */
/* LFSCDMOUTPOS.wPosition */
/* LFSCDMTELLERPOS.wPosition */
/* LFSCDMTELLERDETAILS.wOutput_Position */
/* LFSCDMPHYSICALCU.wPosition  取值*/

#define     LFS_CDM_POSNULL                     (0x0000)
#define     LFS_CDM_POSLEFT                     (0x0001)
#define     LFS_CDM_POSRIGHT                    (0x0002)
#define     LFS_CDM_POSCENTER                   (0x0004)
#define     LFS_CDM_POSTOP                      (0x0040)
#define     LFS_CDM_POSBOTTOM                   (0x0080)
#define     LFS_CDM_POSFRONT                    (0x0800)
#define     LFS_CDM_POSREAR                     (0x1000)

/* LFSCDMPHYSICALCU.wPosition 取值*/ 
#define     LFS_CDM_POSREJECT                   (0x0100)

/* LFSCDMTELLERDETAILS.ulInput_Position 取值*/
#define     LFS_CDM_POSINLEFT                   (0x0001)
#define     LFS_CDM_POSINRIGHT                  (0x0002)
#define     LFS_CDM_POSINCENTER                 (0x0004)
#define     LFS_CDM_POSINTOP                    (0x0008)
#define     LFS_CDM_POSINBOTTOM                 (0x0010)
#define     LFS_CDM_POSINFRONT                  (0x0020)
#define     LFS_CDM_POSINREAR                   (0x0040)

/* wExchange_Type 取值*/
#define     LFS_CDM_EXBYHAND                    (0x0001)
#define     LFS_CDM_EXTOCASSETTES               (0x0002)


/* LFSCDMTELLERUPDATE.usAction 取值*/

#define     LFS_CDM_CREATE_TELLER               (1)
#define     LFS_CDM_MODIFY_TELLER               (2)
#define     LFS_CDM_DELETE_TELLER               (3)


/* LFSCDMCUERROR.wFailure 取值*/

#define     LFS_CDM_CASHUNITEMPTY               (1)
#define     LFS_CDM_CASHUNITERROR               (2)
#define     LFS_CDM_CASHUNITFULL                (4)
#define     LFS_CDM_CASHUNITLOCKED              (5)
#define     LFS_CDM_CASHUNITINVALID             (6)
#define     LFS_CDM_CASHUNITCONFIG              (7)
#define 	LFS_CDM_CASHUNITNOTCONF 			(8) 

/* LFS_EXEE_CDM_NOTESERROR中lpusReason 取值 */

#define     LFS_CDM_DOUBLENOTEDETECTED          (1)
#define     LFS_CDM_LONGNOTEDETECTED            (2)
#define     LFS_CDM_SKEWEDNOTE                  (3)
#define     LFS_CDM_INCORRECTCOUNT              (4)
#define     LFS_CDM_NOTESTOOCLOSE               (5)
#define 	LFS_CDM_OTHERNOTEERROR 				(6) 
#define 	LFS_CDM_SHORTNOTEDETECTED 			(7) 

/* LFSCDMPREPAREDISPENSE.wAction 取值*/ 
#define 	LFS_CDM_START 						(1) 
#define 	LFS_CDM_STOP 						(2) 

/* 错误码 */ 

#define LFS_ERR_CDM_INVALIDCURRENCY         (-(CDM_SERVICE_OFFSET + 0))
#define LFS_ERR_CDM_INVALIDTELLERID         (-(CDM_SERVICE_OFFSET + 1))
#define LFS_ERR_CDM_CASHUNITERROR           (-(CDM_SERVICE_OFFSET + 2))
#define LFS_ERR_CDM_INVALIDDENOMINATION     (-(CDM_SERVICE_OFFSET + 3))
#define LFS_ERR_CDM_INVALIDMIXNUMBER        (-(CDM_SERVICE_OFFSET + 4))
#define LFS_ERR_CDM_NOCURRENCYMIX           (-(CDM_SERVICE_OFFSET + 5))
#define LFS_ERR_CDM_NOTDISPENSABLE          (-(CDM_SERVICE_OFFSET + 6))
#define LFS_ERR_CDM_TOOMANYITEMS            (-(CDM_SERVICE_OFFSET + 7))
#define LFS_ERR_CDM_UNSUPPOSITION           (-(CDM_SERVICE_OFFSET + 8))
#define LFS_ERR_CDM_SAFEDOOROPEN            (-(CDM_SERVICE_OFFSET + 10))
#define LFS_ERR_CDM_SHUTTERNOTOPEN          (-(CDM_SERVICE_OFFSET + 12))
#define LFS_ERR_CDM_SHUTTEROPEN             (-(CDM_SERVICE_OFFSET + 13))
#define LFS_ERR_CDM_SHUTTERCLOSED           (-(CDM_SERVICE_OFFSET + 14))
#define LFS_ERR_CDM_INVALIDCASHUNIT         (-(CDM_SERVICE_OFFSET + 15))
#define LFS_ERR_CDM_NOITEMS                 (-(CDM_SERVICE_OFFSET + 16))
#define LFS_ERR_CDM_EXCHANGEACTIVE          (-(CDM_SERVICE_OFFSET + 17))
#define LFS_ERR_CDM_NOEXCHANGEACTIVE        (-(CDM_SERVICE_OFFSET + 18))
#define LFS_ERR_CDM_SHUTTERNOTCLOSED        (-(CDM_SERVICE_OFFSET + 19))
#define LFS_ERR_CDM_PRERRORNOITEMS          (-(CDM_SERVICE_OFFSET + 20))
#define LFS_ERR_CDM_PRERRORITEMS            (-(CDM_SERVICE_OFFSET + 21))
#define LFS_ERR_CDM_PRERRORUNKNOWN          (-(CDM_SERVICE_OFFSET + 22))
#define LFS_ERR_CDM_ITEMSTAKEN              (-(CDM_SERVICE_OFFSET + 23))
#define LFS_ERR_CDM_INVALIDMIXTABLE         (-(CDM_SERVICE_OFFSET + 27))
#define LFS_ERR_CDM_OUTPUTPOS_NOT_EMPTY     (-(CDM_SERVICE_OFFSET + 28))
#define LFS_ERR_CDM_INVALIDRETRACTPOSITION  (-(CDM_SERVICE_OFFSET + 29))
#define LFS_ERR_CDM_NOTRETRACTAREA          (-(CDM_SERVICE_OFFSET + 30))
#define LFS_ERR_CDM_NOCASHBOXPRESENT        (-(CDM_SERVICE_OFFSET + 33))
#define LFS_ERR_CDM_AMOUNTNOTINMIXTABLE     (-(CDM_SERVICE_OFFSET + 34))
#define LFS_ERR_CDM_ITEMSNOTTAKEN           (-(CDM_SERVICE_OFFSET + 35))
#define LFS_ERR_CDM_ITEMSLEFT               (-(CDM_SERVICE_OFFSET + 36))
#define LFS_ERR_CDM_INVALID_PORT 			(-(CDM_SERVICE_OFFSET + 37)) 
#define LFS_ERR_CDM_POWERSAVETOOSHORT 		(-(CDM_SERVICE_OFFSET + 38)) 
#define LFS_ERR_CDM_POWERSAVEMEDIAPRESENT 	(-(CDM_SERVICE_OFFSET + 39)) 
#define LFS_ERR_CDM_TOOMANYITEMSTOCOUNT     (-(CDM_SERVICE_OFFSET + 45))
#define LFS_ERR_CDM_COUNTPOSNOTEMPTY        (-(CDM_SERVICE_OFFSET + 46))

/*=================================================================*/
/* 信息指令结构 */
/*=================================================================*/

typedef struct _LFS_CDM_position
{
    WORD				wPosition;
    WORD				wShutter;
    WORD				wPosition_Status;
    WORD				wTransport;
    WORD				wTransport_Status;
} LFSCDMOUTPOS, * LPLFSCDMOUTPOS;

typedef struct _LFS_CDM_status
{
    WORD				wDevice;
    WORD				wSafe_Door; 
    WORD				wDispenser;
    WORD				wIntermediate_Stacker;
    LPLFSCDMOUTPOS		*lppPositions;
	LPSTR				lpstrExtra;
	DWORD               dwGuid_Lights[LFS_CDM_GUIDLIGHTS_SIZE]; 
	WORD                wDevice_Position; 
	USHORT              usPower_Save_Recovery_Time; 
    WORD                wCash_Count_Status;
} LFSCDMSTATUS, * LPLFSCDMSTATUS;

typedef struct _LFS_CDM_caps
{
    WORD				wClass;
    WORD				wType;
    WORD				wMax_Dispense_Items;
    BOOL				bCompound;
    BOOL				bShutter;
    BOOL				bShutter_Control;
    WORD				wRetract_Areas;
    WORD				wRetract_Transport_Actions;
    WORD				wRetract_Stacker_Actions;
    BOOL				bSafe_Door;
    BOOL				bCash_Box;
    BOOL				bIntermediate_Stacker;   
    BOOL				bItems_Taken_Sensor;
    WORD				wPositions;
    WORD				wMove_Items;
    WORD				wExchange_Type;
	LPSTR				lpstrExtra;
	DWORD               dwGuid_Lights[LFS_CDM_GUIDLIGHTS_SIZE];
	BOOL                bPower_Save_Control;
	BOOL                bPrepare_Dispense; 
} LFSCDMCAPS, * LPLFSCDMCAPS;

typedef struct _LFS_CDM_phcu
{
    LPSTR				lpstrPhysical_Position_Name;
    CHAR				cUnit_ID[5];
    ULONG				ulInitial_Count;
    ULONG				ulCount;
    ULONG				ulReject_Count;
    ULONG				ulMaximum;
    USHORT				usPhy_Status;
	BOOL				bHardware_Sensor;
	ULONG 				ulDispensed_Count; 
	ULONG 				ulPresented_Count; 
	ULONG 				ulRetracted_Count; 
} LFSCDMPHCU, * LPLFSCDMPHCU;

typedef struct _LFS_CDM_cash_unit
{
    USHORT				usNumber;
    USHORT				usType;
    LPSTR				lpstrCash_Unit_Name;
    CHAR				cUnit_ID[5];
    CHAR				cCurrency_ID[3];
    ULONG				ulValues;
    ULONG				ulInitial_Count;
    ULONG				ulCount;
    ULONG				ulReject_Count;
    ULONG				ulMinimum;
    ULONG				ulMaximum;
    BOOL				bApp_Lock;
    USHORT				usStatus;
    USHORT				usNumPhysical_CUs;
	LPLFSCDMPHCU		*lppPhysical;
	ULONG 				ulDispensed_Count; 
	ULONG 				ulPresented_Count; 
	ULONG 				ulRetracted_Count; 
} LFSCDMCASHUNIT, * LPLFSCDMCASHUNIT;

typedef struct _LFS_CDM_cu_info
{
    USHORT				usTeller_ID;
    USHORT				usCount;
    LPLFSCDMCASHUNIT	*lppList;
} LFSCDMCUINFO, * LPLFSCDMCUINFO;

typedef struct _LFS_CDM_teller_info
{
    USHORT				usTeller_ID;
    CHAR				cCurrency_ID[3];
} LFSCDMTELLERINFO, * LPLFSCDMTELLERINFO;

typedef struct _LFS_CDM_teller_totals
{
   CHAR				cCurrency_ID[3];
   ULONG            ulItems_Received;
   ULONG            ulItems_Dispensed;
   ULONG            ulCoins_Received;
   ULONG            ulCoins_Dispensed;
   ULONG            ulCash_Box_Received;
   ULONG            ulCash_Box_Dispensed;
} LFSCDMTELLERTOTALS, * LPLFSCDMTELLERTOTALS;

typedef struct _LFS_CDM_teller_details
{
    USHORT                usTeller_ID;
    ULONG                 ulInput_Position;
    WORD                  wOutput_Position;
    LPLFSCDMTELLERTOTALS *lppTeller_Totals;
} LFSCDMTELLERDETAILS, * LPLFSCDMTELLERDETAILS;

typedef struct _LFS_CDM_currency_exp
{
    CHAR				cCurrency_ID[3];
    SHORT				sExponent;
} LFSCDMCURRENCYEXP, * LPLFSCDMCURRENCYEXP;

typedef struct _LFS_CDM_mix_type
{
    USHORT				usMix_Number;
    USHORT				usMix_Type;
    USHORT				usSub_Type;
    LPSTR				lpstrName;
} LFSCDMMIXTYPE, * LPLFSCDMMIXTYPE;

typedef struct _LFS_CDM_mix_row
{
    ULONG			ulAmount;
    LPUSHORT		lpusMixture;
} LFSCDMMIXROW, * LPLFSCDMMIXROW;

typedef struct _LFS_CDM_mix_table
{
    USHORT				usMix_Number;
    LPSTR				lpstrName;
    USHORT				usRows;
    USHORT				usCols;
    LPULONG				lpulMix_Header;
    LPLFSCDMMIXROW		*lppMix_Rows;
} LFSCDMMIXTABLE, * LPLFSCDMMIXTABLE;

typedef struct _LFS_CDM_denomination
{
    CHAR				cCurrency_ID[3];
    ULONG				ulAmount;
    USHORT				usCount;
    LPULONG				lpulValues;
    ULONG				ulCash_Box;
} LFSCDMDENOMINATION, * LPLFSCDMDENOMINATION;
                         
typedef struct _LFS_CDM_present_status
{
    LPLFSCDMDENOMINATION	lpDenomination;
    WORD					wPresent_State;
    LPSTR					lpstrExtra;
} LFSCDMPRESENTSTATUS, * LPLFSCDMPRESENTSTATUS;

typedef struct _LFS_CDM_replenish_info
{
	USHORT	   usNumber_Source;
} LFSCDMREPINFO, *LPLFSCDMREPINFO;

typedef struct _LFS_CDM_info_target 
{ 
	USHORT    usNumber_Target; 
} LFSCDMREPINFOTARGET, *LPLFSCDMREPINFOTARGET;

typedef struct _LFS_CDM_replenish_info_result
{
	LPLFSCDMREPINFOTARGET 		*lppReplenish_Info_Targets;
} LFSCDMREPINFORES, *LPLFSCDMREPINFORES;

/*=================================================================*/
/* 执行指令结构 */
/*=================================================================*/

typedef struct _LFS_CDM_denominate
{
    USHORT					usTeller_ID;
    USHORT					usMix_Number;
    LPLFSCDMDENOMINATION	lpDenomination;
} LFSCDMDENOMINATE, * LPLFSCDMDENOMINATE;

typedef struct _LFS_CDM_dispense
{
    USHORT				usTeller_ID;
    USHORT				usMix_Number;
    WORD				wPosition;
    BOOL				bPresent;
    LPLFSCDMDENOMINATION  lpDenomination;
} LFSCDMDISPENSE, * LPLFSCDMDISPENSE;

typedef struct _LFS_CDM_physical_cu
{
    BOOL				bEmpty_All;
    WORD				wPosition;
    LPSTR				lpstrPhysical_Position_Name;
} LFSCDMPHYSICALCU, *LPLFSCDMPHYSICALCU;

typedef struct _LFS_CDM_counted_phys_cu
{
    LPSTR				lpstrPhysical_Position_Name;
    CHAR				cUnit_ID[5];
    ULONG				ulDispensed;
    ULONG				ulCounted;
    USHORT				usPhy_Status;
} LFSCDMCOUNTEDPHYSCU, *LPLFSCDMCOUNTEDPHYSCU;

typedef struct _LFS_CDM_count
{
    USHORT					usNum_Physical_CUs;
    LPLFSCDMCOUNTEDPHYSCU	*lppCounted_Phys_CUs;
} LFSCDMCOUNT, *LPLFSCDMCOUNT;

typedef struct _LFS_CDM_retract
{
    WORD					wOutput_Position;
    USHORT                	usRetract_Area;
    USHORT                	usIndex;
} LFSCDMRETRACT, * LPLFSCDMRETRACT;

typedef struct _LFS_CDM_teller_update
{
    USHORT					usAction;
    LPLFSCDMTELLERDETAILS	lpTeller_Details;
} LFSCDMTELLERUPDATE, * LPLFSCDMTELLERUPDATE;

typedef struct _LFS_CDM_start_ex
{
    WORD					wExchange_Type;
    USHORT					usTeller_ID;
    USHORT					usCount;
    LPUSHORT				lpusCU_Num_List;
} LFSCDMSTARTEX, * LPLFSCDMSTARTEX;

typedef struct _LFS_CDM_item_position
{
    USHORT					usNumber;
    LPLFSCDMRETRACT			lpRetract_Area;
    WORD					wOutput_Position;
} LFSCDMITEMPOSITION, * LPLFSCDMITEMPOSITION;

typedef struct _LFS_CDM_calibrate
{
    USHORT					usNumber;
    USHORT					usNumOfBills;
    LPLFSCDMITEMPOSITION	*lppPosition;
} LFSCDMCALIBRATE, * LPLFSCDMCALIBRATE;

typedef struct _LFS_CDM_set_guid_light 
{ 
WORD 	wGuid_Light; 
DWORD 	dwCommand; 
} LFSCDMSETGUIDLIGHT, *LPLFSCDMSETGUIDLIGHT;
 
typedef struct _LFS_CDM_power_save_control 
{ 
	USHORT usMax_Power_Save_Recovery_Time; 
} LFSCDMPOWERSAVECONTROL, *LPLFSCDMPOWERSAVECONTROL; 

typedef struct _LFS_CDM_prepare_dispense 
{ 
	WORD wAction; 
} LFSCDMPREPAREDISPENSE, *LPLFSCDMPREPAREDISPENSE; 

typedef struct _LFS_CDM_blacklist_element
{
      LPWSTR 	lpszSerial_Number;
      CHAR		cCurrency_ID[3];
      ULONG		ulValue;
} LFSCDMBLACKLISTELEMENT,*LPLFSCDMBLACKLISTELEMENT;

typedef struct _LFS_CDM_blacklist
{
	LPWSTR	   lpszVersion;
	USHORT 	   usCount;
	LPLFSCDMBLACKLISTELEMENT *lppBlacklist_Elements;
} LFSCDMBLACKLIST, *LPLFSCDMBLACKLIST;

typedef struct _LFS_CDM_replenish_target
{
	USHORT	usNumber_Target;
	ULONG	ulNumber_Of_Items_To_Move;
	BOOL	bRemove_All;
} LFSCDMREPTARGET, *LPLFSCDMREPTARGET;

typedef struct _LFS_CDM_replenish
{
	USHORT	   			usNumber_Source;
	LFSCDMREPTARGET 	*lppReplenish_Targets;
} LFSCDMREP, *LPLFSCDMREP;

typedef struct _LFS_CDM_replenish_target_result
{
	USHORT usNumber_Target;
	USHORT usNote_ID;
	ULONG ulNumber_Of_Items_Received;
} LFSCDMREPTARGETRES, *LPLFSCDMREPTARGETRES;

typedef struct _LFS_CDM_replenish_result
{
	ULONG ulNumber_Of_Items_Removed;
	ULONG ulNumber_Of_Items_Rejected;
	LPLFSCDMREPTARGETRES *lppReplenish_Target_Results;
} LFSCDMREPRES, *LPLFSCDMREPRES;

typedef struct _LFS_CDM_count_cash_unit
{
USHORT                 usCount;
LPUSHORT               lpusCU_Num_List;
}LFSCDMCOUNTCASHUNIT, *LPLFSCDMCOUNTCASHUNIT;

typedef struct _LFS_CDM_set_fsn_info
{
	USHORT               usTeller_ID;
	BYTE                 byFit_Code;
	LPSTR                lpstrFSN_Files_Path;
	LPSTR                lpszFSN_Number_Txt_Path;   
	LPSTR                lpstrFinan_Ins;
	LPSTR                lpstrEnable_Time;
	LPSTR                lpstrFinan_Inst;
	LPSTR                lpstrFinan_Inst_Outlet;         
} LFSCDMCASHSETFSNINFO , * LPLFSCDMCASHSETFSNINFO;

/*=================================================================*/
/* 事件结构*/
/*=================================================================*/
typedef struct _LFS_CDM_cu_error
{
    WORD				wFailure;
    LPLFSCDMCASHUNIT	lpCash_Unit;
} LFSCDMCUERROR, * LPLFSCDMCUERROR;

typedef struct _LFS_CDM_counts_changed
{
    USHORT				usCount;
    USHORT				*lpusCU_NumList;
} LFSCDMCOUNTSCHANGED, * LPLFSCDMCOUNTSCHANGED;

typedef struct _LFS_CDM__device_position 
{ 
    WORD wPosition; 
} LFSCDMDEVICEPOSITION, *LPLFSCDMDEVICEPOSITION; 

typedef struct _LFS_CDM_pos
{
    WORD    wPosition;
} LFSCDMPOSITION, *LPLFSCDMPOSITION;


typedef struct _LFS_CDM__power_save_change 
{ 
USHORT usPower_Save_Recovery_Time; 
} LFSCDMPOWERSAVECHANGE, *LPLFSCDMPOWERSAVECHANGE; 

typedef struct _LFS_CDM_incomplete_replenish
{
	LPLFSCDMREPRES lpReplenish;
} LFSCDMINCOMPLETEREPLENISH, *LPLFSCDMINCOMPLETEREPLENISH;

/* 恢复对齐方式 */
#pragma pack (pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif  /* __INC_LFSCDM__H */