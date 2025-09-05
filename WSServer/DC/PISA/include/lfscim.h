/******************************************************************************
*                                                                            *
* LFScim.h  - Cash-In Module (CIM) definitions                               *
*                                                                            *
* Version 1.00                                                               *
*                                                                            *
******************************************************************************/


#ifndef __INC_LFSCIM__H
#define __INC_LFSCIM__H

#ifdef __cplusplus
extern "C" {
#endif

#include "lfsapi.h"

/*  对齐方式   */
#pragma pack(push,1)

/* LFSCIMCAPS.wClass 取值*/

#define     LFS_SERVICE_CLASS_CIM               (13)
#define     LFS_SERVICE_CLASS_VERSION_CIM        0x0001
#define     LFS_SERVICE_CLASS_NAME_CIM          "CIM"
#define     CIM_SERVICE_OFFSET                   (LFS_SERVICE_CLASS_CIM * 100)

/* 信息指令 */

#define     LFS_INF_CIM_STATUS                  (CIM_SERVICE_OFFSET + 1)
#define     LFS_INF_CIM_CAPABILITIES            (CIM_SERVICE_OFFSET + 2)
#define     LFS_INF_CIM_CASH_UNIT_INFO          (CIM_SERVICE_OFFSET + 3)
#define     LFS_INF_CIM_TELLER_INFO             (CIM_SERVICE_OFFSET + 4)
#define     LFS_INF_CIM_CURRENCY_EXP            (CIM_SERVICE_OFFSET + 5)
#define     LFS_INF_CIM_BANKNOTE_TYPES          (CIM_SERVICE_OFFSET + 6)
#define     LFS_INF_CIM_CASH_IN_STATUS          (CIM_SERVICE_OFFSET + 7)
#define     LFS_INF_CIM_GET_P6_INFO             (CIM_SERVICE_OFFSET + 8)
#define     LFS_INF_CIM_GET_P6_SIGNATURE        (CIM_SERVICE_OFFSET + 9)
#define     LFS_INF_CIM_GET_ITEM_INFO 			(CIM_SERVICE_OFFSET + 10)
#define     LFS_INF_CIM_POSITION_CAPABILITIES   (CIM_SERVICE_OFFSET + 11) 
#define     LFS_INF_CIM_REPLENISH_TARGET        (CIM_SERVICE_OFFSET + 12)
#define     LFS_INF_CIM_GET_BLACKLIST           (CIM_SERVICE_OFFSET + 17)

/* 执行指令 */

#define     LFS_CMD_CIM_CASH_IN_START           (CIM_SERVICE_OFFSET + 1)
#define     LFS_CMD_CIM_CASH_IN                 (CIM_SERVICE_OFFSET + 2)
#define     LFS_CMD_CIM_CASH_IN_END             (CIM_SERVICE_OFFSET + 3)
#define     LFS_CMD_CIM_CASH_IN_ROLLBACK        (CIM_SERVICE_OFFSET + 4)
#define     LFS_CMD_CIM_RETRACT                 (CIM_SERVICE_OFFSET + 5)
#define     LFS_CMD_CIM_OPEN_SHUTTER            (CIM_SERVICE_OFFSET + 6)
#define     LFS_CMD_CIM_CLOSE_SHUTTER           (CIM_SERVICE_OFFSET + 7)
#define     LFS_CMD_CIM_SET_TELLER_INFO         (CIM_SERVICE_OFFSET + 8)
#define     LFS_CMD_CIM_SET_CASH_UNIT_INFO      (CIM_SERVICE_OFFSET + 9)
#define     LFS_CMD_CIM_START_EXCHANGE          (CIM_SERVICE_OFFSET + 10)
#define     LFS_CMD_CIM_END_EXCHANGE            (CIM_SERVICE_OFFSET + 11)
#define     LFS_CMD_CIM_OPEN_SAFE_DOOR          (CIM_SERVICE_OFFSET + 12)
#define     LFS_CMD_CIM_RESET                   (CIM_SERVICE_OFFSET + 13)
#define     LFS_CMD_CIM_CONFIGURE_CASH_IN_UNITS (CIM_SERVICE_OFFSET + 14)
#define     LFS_CMD_CIM_CONFIGURE_NOTETYPES     (CIM_SERVICE_OFFSET + 15)
#define     LFS_CMD_CIM_CREATE_P6_SIGNATURE 	(CIM_SERVICE_OFFSET + 16) 
#define     LFS_CMD_CIM_SET_GUIDANCE_LIGHT 		(CIM_SERVICE_OFFSET + 17) 
#define     LFS_CMD_CIM_CONFIGURE_NOTE_READER 	(CIM_SERVICE_OFFSET + 18) 
#define     LFS_CMD_CIM_COMPARE_P6_SIGNATURE 	(CIM_SERVICE_OFFSET + 19) 
#define     LFS_CMD_CIM_POWER_SAVE_CONTROL 		(CIM_SERVICE_OFFSET + 20) 
#define 	LFS_CMD_CIM_REPLENISH 				(CIM_SERVICE_OFFSET + 21) 
#define     LFS_CMD_CIM_SET_CASH_IN_LIMIT       (CIM_SERVICE_OFFSET + 22)
#define     LFS_CMD_CIM_CASH_UNIT_COUNT         (CIM_SERVICE_OFFSET + 23)
#define     LFS_CMD_CIM_SET_BLACKLIST           (CIM_SERVICE_OFFSET + 28)
#define     LFS_CMD_CIM_SET_CASH_IN_MODE		(CIM_SERVICE_OFFSET + 95)
#define     LFS_CMD_CIM_SET_FSN_INFO			(CIM_SERVICE_OFFSET + 96)
#define     LFS_CMD_CIM_CLEAR_FSN_FILES			(CIM_SERVICE_OFFSET + 97)
#define     LFS_CMD_CIM_GET_BANKNOTE_COUNT		(CIM_SERVICE_OFFSET + 98)
#define     LFS_CMD_CIM_CLEAR_BANKNOTE_COUNT	(CIM_SERVICE_OFFSET + 99)
/* 事件 */

#define     LFS_SRVE_CIM_SAFEDOOROPEN           (CIM_SERVICE_OFFSET + 1)
#define     LFS_SRVE_CIM_SAFEDOORCLOSED         (CIM_SERVICE_OFFSET + 2)
#define     LFS_USRE_CIM_CASHUNITTHRESHOLD      (CIM_SERVICE_OFFSET + 3)
#define     LFS_SRVE_CIM_CASHUNITINFOCHANGED    (CIM_SERVICE_OFFSET + 4)
#define     LFS_SRVE_CIM_TELLERINFOCHANGED      (CIM_SERVICE_OFFSET + 5)
#define     LFS_EXEE_CIM_CASHUNITERROR          (CIM_SERVICE_OFFSET + 6)
#define     LFS_SRVE_CIM_ITEMSTAKEN             (CIM_SERVICE_OFFSET + 7)
#define     LFS_SRVE_CIM_COUNTS_CHANGED         (CIM_SERVICE_OFFSET + 8)
#define     LFS_EXEE_CIM_INPUTREFUSE            (CIM_SERVICE_OFFSET + 9)
#define     LFS_SRVE_CIM_ITEMSPRESENTED         (CIM_SERVICE_OFFSET + 10)
#define     LFS_SRVE_CIM_ITEMSINSERTED          (CIM_SERVICE_OFFSET + 11)
#define     LFS_EXEE_CIM_NOTEERROR              (CIM_SERVICE_OFFSET + 12)
#define     LFS_EXEE_CIM_SUBCASHIN              (CIM_SERVICE_OFFSET + 13)
#define     LFS_SRVE_CIM_MEDIADETECTED          (CIM_SERVICE_OFFSET + 14)
#define     LFS_EXEE_CIM_INPUT_P6               (CIM_SERVICE_OFFSET + 15)
#define 	LFS_EXEE_CIM_INFO_AVAILABLE 		(CIM_SERVICE_OFFSET + 16) 
#define	 	LFS_EXEE_CIM_INSERTITEMS 			(CIM_SERVICE_OFFSET + 17) 
#define 	LFS_SRVE_CIM_DEVICEPOSITION 		(CIM_SERVICE_OFFSET + 18) 
#define 	LFS_SRVE_CIM_POWER_SAVE_CHANGE 		(CIM_SERVICE_OFFSET + 19) 
#define     LFS_EXEE_CIM_INCOMPLETEREPLENISH    (CIM_SERVICE_OFFSET + 20)

/* LFSCIMSTATUS.wDevice 取值 */

#define     LFS_CIM_DEVONLINE                   LFS_STAT_DEVONLINE
#define     LFS_CIM_DEVOFFLINE                  LFS_STAT_DEVOFFLINE
#define     LFS_CIM_DEVPOWEROFF                 LFS_STAT_DEVPOWEROFF
#define     LFS_CIM_DEVNODEVICE                 LFS_STAT_DEVNODEVICE
#define     LFS_CIM_DEVUSERERROR                LFS_STAT_DEVUSERERROR
#define     LFS_CIM_DEVHWERROR                  LFS_STAT_DEVHWERROR
#define     LFS_CIM_DEVBUSY                     LFS_STAT_DEVBUSY
#define 	LFS_CIM_DEVFRAUDATTEMPT 			LFS_STAT_DEVFRAUDATTEMPT
#define     LFS_CIM_CASHJAMMED                  (9)

/* LFSCIMSTATUS.wSafe_Door 取值 */

#define     LFS_CIM_DOORNOTSUPPORTED            (1)
#define     LFS_CIM_DOOROPEN                    (2)
#define     LFS_CIM_DOORCLOSED                  (3)
#define     LFS_CIM_DOORUNKNOWN                 (4)

/* LFSCIMSTATUS.wAcceptor 取值 */

#define     LFS_CIM_ACCOK                       (0)
#define     LFS_CIM_ACCCUSTATE                  (1)
#define     LFS_CIM_ACCCUSTOP                   (2)
#define     LFS_CIM_ACCCUUNKNOWN                (3)

/* LFSCIMSTATUS.wIntermediate_Stacker 取值 */

#define     LFS_CIM_ISEMPTY                     (0)
#define     LFS_CIM_ISNOTEMPTY                  (1)
#define     LFS_CIM_ISFULL                      (2)
#define     LFS_CIM_ISUNKNOWN                   (4)
#define     LFS_CIM_ISNOTSUPPORTED              (5)

#define 	LFS_CIM_GUIDLIGHTS_SIZE 			(32) 
#define 	LFS_CIM_GUIDLIGHTS_MAX 				(LFS_CIM_GUIDLIGHTS_SIZE - 1) 

/* LFSCIMSTATUS.dwGuid_Lights[...]取值 */
/* LFSCIMCAPS.dwGuid_Lights[...]取值 */

#define 	LFS_CIM_GUIDANCE_POSINNULL 			(0) 
#define 	LFS_CIM_GUIDANCE_POSINLEFT 			(1) 
#define  	LFS_CIM_GUIDANCE_POSINRIGHT 		(2) 
#define 	LFS_CIM_GUIDANCE_POSINCENTER 		(3) 
#define 	LFS_CIM_GUIDANCE_POSINTOP 			(4) 
#define 	LFS_CIM_GUIDANCE_POSINBOTTOM 		(5) 
#define 	LFS_CIM_GUIDANCE_POSINFRONT 		(6) 
#define 	LFS_CIM_GUIDANCE_POSINREAR 			(7) 
#define 	LFS_CIM_GUIDANCE_POSOUTLEFT 		(8) 
#define 	LFS_CIM_GUIDANCE_POSOUTRIGHT 		(9) 
#define 	LFS_CIM_GUIDANCE_POSOUTCENTER		(10) 
#define 	LFS_CIM_GUIDANCE_POSOUTTOP 			(11) 
#define 	LFS_CIM_GUIDANCE_POSOUTBOTTOM 		(12) 
#define 	LFS_CIM_GUIDANCE_POSOUTFRONT 		(13) 
#define 	LFS_CIM_GUIDANCE_POSOUTREAR 		(14) 
#define  	LFS_CIM_GUIDANCE_POSOUTNULL 		(15) 

#define 	LFS_CIM_GUIDANCE_NOT_AVAILABLE 		(0x00000000) 
#define 	LFS_CIM_GUIDANCE_OFF 				(0x00000001) 
#define 	LFS_CIM_GUIDANCE_SLOW_FLASH 		(0x00000004) 
#define 	LFS_CIM_GUIDANCE_MEDIUM_FLASH 		(0x00000008) 
#define 	LFS_CIM_GUIDANCE_QUICK_FLASH 		(0x00000010) 
#define 	LFS_CIM_GUIDANCE_CONTINUOUS 		(0x00000080) 
#define 	LFS_CIM_GUIDANCE_RED 				(0x00000100) 
#define 	LFS_CIM_GUIDANCE_GREEN 				(0x00000200) 
#define	 	LFS_CIM_GUIDANCE_YELLOW 			(0x00000400) 
#define 	LFS_CIM_GUIDANCE_BLUE 				(0x00000800) 
#define 	LFS_CIM_GUIDANCE_CYAN 				(0x00001000) 
#define		LFS_CIM_GUIDANCE_MAGENTA 			(0x00002000) 
#define	 	LFS_CIM_GUIDANCE_WHITE 				(0x00004000) 

/* LFSCIMSTATUS.wDevice_Position 取值*/
/* LFSCIMDEVICEPOSITION.wPosition 取值*/ 
#define	 	LFS_CIM_DEVICEINPOSITION 			(0) 
#define	 	LFS_CIM_DEVICENOTINPOSITION 		(1) 
#define	 	LFS_CIM_DEVICEPOSUNKNOWN 			(2) 
#define	 	LFS_CIM_DEVICEPOSNOTSUPP 			(3) 


/* LFSCIMSTATUS.wStacker_Items 取值 */

#define     LFS_CIM_CUSTOMERACCESS              (0)
#define     LFS_CIM_NOCUSTOMERACCESS            (1)
#define     LFS_CIM_ACCESSUNKNOWN               (2)
#define     LFS_CIM_NOITEMS                     (4)

/* LFSCIMSTATUS.wBank_Note_Reader 取值 */

#define     LFS_CIM_BNROK                       (0)
#define     LFS_CIM_BNRINOP                     (1)
#define     LFS_CIM_BNRUNKNOWN                  (2)
#define     LFS_CIM_BNRNOTSUPPORTED             (3)

/* LFSCIMSTATUS.wShutter 取值 */

#define     LFS_CIM_SHTCLOSED                   (0)
#define     LFS_CIM_SHTOPEN                     (1)
#define     LFS_CIM_SHTJAMMED                   (2)
#define     LFS_CIM_SHTUNKNOWN                  (3)
#define     LFS_CIM_SHTNOTSUPPORTED             (4)

/* LFSCIMINPOS.wPosition_Status 取值 */

#define     LFS_CIM_PSEMPTY                     (0)
#define     LFS_CIM_PSNOTEMPTY                  (1)
#define     LFS_CIM_PSUNKNOWN                   (2)
#define     LFS_CIM_PSNOTSUPPORTED              (3)
#define     LFS_CIM_PSFOREIGNITEMS 				(4) 

/* LFSCIMSTATUS.wTransport 取值 */

#define     LFS_CIM_TPOK                        (0)
#define     LFS_CIM_TPINOP                      (1)
#define     LFS_CIM_TPUNKNOWN                   (2)
#define     LFS_CIM_TPNOTSUPPORTED              (3)

/* LFSCIMSTATUS.wCash_Count_Status取值 */

#define     LFS_CIM_CASHCOUNTSTATUSOK           (0)
#define     LFS_CIM_CASHCOUNTSTATUSINOP         (1)
#define     LFS_CIM_CASHCOUNTSTATUSUNKNOWN      (2)
#define     LFS_CIM_CASHCOUNTSTATUSNOTSUPP      (3)


/* LFSCIMINPOS.wTransport_Status 取值 */

#define     LFS_CIM_TPSTATEMPTY                 (0)
#define     LFS_CIM_TPSTATNOTEMPTY              (1)
#define     LFS_CIM_TPSTATNOTEMPTYCUST          (2)
#define     LFS_CIM_TPSTATNOTEMPTY_UNK          (3)
#define     LFS_CIM_TPSTATNOTSUPPORTED          (4)

/* LFSCIMCAPS.wType 取值 */

#define     LFS_CIM_TELLERBILL                  (0)
#define     LFS_CIM_SELFSERVICEBILL             (1)
#define     LFS_CIM_TELLERCOIN                  (2)
#define     LFS_CIM_SELFSERVICECOIN             (3)

/* LFSCIMCAPS.wExchange_Type */
/* LFSCIMSTARTEX.wExchange_Type 取值 */

#define     LFS_CIM_EXBYHAND                    (0x0001)
#define     LFS_CIM_EXTOCASSETTES               (0x0002)
#define     LFS_CIM_CLEARRECYCLER               (0x0004)
#define     LFS_CIM_DEPOSITINTO                 (0x0008)

/* LFSCIMCAPS.wRetract_Transport_Actions */
/* LFSCIMCAPS.wRetract_Stacker_Actions 取值 */

#define     LFS_CIM_PRESENT                     (0x0001)
#define     LFS_CIM_RETRACT                     (0x0002)
#define     LFS_CIM_NOTSUPP                     (0x0004)
#define 	LFS_CIM_REJECT 						(0x0008) 
#define 	LFS_CIM_BILLCASSETTES 				(0x0010)

/* LFSCIMCASHIN.wType 取值 */

#define     LFS_CIM_TYPERECYCLING               (1)
#define     LFS_CIM_TYPECASHIN                  (2)
#define     LFS_CIM_TYPEREPCONTAINER            (3)
#define     LFS_CIM_TYPERETRACTCASSETTE         (4)
#define 	LFS_CIM_TYPEREJECT					(5) 
#define 	LFS_CIM_TYPECDMSPECIFIC				(6) 

/* LFSCIMCASHIN.wItem_Type */
/* LFSCIMCASHINTYPE.dwType 取值 */

#define     LFS_CIM_CITYPALL                    (0x0001)
#define     LFS_CIM_CITYPUNFIT                  (0x0002)
#define     LFS_CIM_CITYPINDIVIDUAL             (0x0004)
#define     LFS_CIM_CITYPLEVEL3                 (0x0008)
#define     LFS_CIM_CITYPLEVEL2                 (0x0010)

/* LFSCIMCASHIN.usStatus */
/* LFSCIMPHCU.usPStatus 取值 */

#define     LFS_CIM_STATCUOK                    (0)
#define     LFS_CIM_STATCUFULL                  (1)
#define     LFS_CIM_STATCUHIGH                  (2)
#define     LFS_CIM_STATCULOW                   (3)
#define     LFS_CIM_STATCUEMPTY                 (4)
#define     LFS_CIM_STATCUINOP                  (5)
#define     LFS_CIM_STATCUMISSING               (6)
#define     LFS_CIM_STATCUNOVAL                 (7)
#define     LFS_CIM_STATCUNOREF                 (8)
#define     LFS_CIM_STATCUMANIP                 (9)

/* LFSCIMSTATUS.wPositions */
/* LFSCIMCAPS.wPositions */
/* LFSCIMINPOS.wPosition */
/* LFSCIMTELLERDETAILS.wInput_Position */ 
/* LFSCIMINPUTREFUSE.wPosition */
/* LFSCIMCASHINSTART.wInput_Position 取值 */ 

#define     LFS_CIM_POSNULL                       (0x0000)
#define     LFS_CIM_POSINLEFT                     (0x0001)
#define     LFS_CIM_POSINRIGHT                    (0x0002)
#define     LFS_CIM_POSINCENTER                   (0x0004)
#define     LFS_CIM_POSINTOP                      (0x0008)
#define     LFS_CIM_POSINBOTTOM                   (0x0010)
#define     LFS_CIM_POSINFRONT                    (0x0020)
#define     LFS_CIM_POSINREAR                     (0x0040)

/* LFSCIMSTATUS.wPositions */
/* LFSCIMCAPS.wPositions */
/* LFSCIMTELLERDETAILS.wOutput_Position */ 
/* LFSCIMCASHINSTART.wOutput_Position */ 
/* LFSCIMINPUTREFUSE.wPosition */
/* LFSCIMOUTPUT.wPosition 取值 */

#define     LFS_CIM_POSOUTLEFT                     (0x0080)
#define     LFS_CIM_POSOUTRIGHT                    (0x0100)
#define     LFS_CIM_POSOUTCENTER                   (0x0200)
#define     LFS_CIM_POSOUTTOP                      (0x0400)
#define     LFS_CIM_POSOUTBOTTOM                   (0x0800)
#define     LFS_CIM_POSOUTFRONT                    (0x1000)
#define     LFS_CIM_POSOUTREAR                     (0x2000)

/* LFSCIMCASHINSTATUS.wStatus 取值 */

#define     LFS_CIM_CIOK                           (0)
#define     LFS_CIM_CIROLLBACK                     (1)
#define     LFS_CIM_CIACTIVE                       (2)
#define     LFS_CIM_CIRETRACT                      (3)
#define     LFS_CIM_CIUNKNOWN                      (4)
#define 	LFS_CIM_CIRESET 					   (5) 

/* LFSCIMCAPS.wRetract_Areas */
/* LFSCIMRETRACT.usRetract_Area 取值 */

#define     LFS_CIM_RA_RETRACT                     (0x0001)
#define     LFS_CIM_RA_TRANSPORT                   (0x0002)
#define     LFS_CIM_RA_STACKER                     (0x0004)
#define     LFS_CIM_RA_BILLCASSETTES               (0x0008)
#define     LFS_CIM_RA_NOTSUPP                     (0x0010)
#define 	LFS_CIM_RA_REJECT 					   (0x0020) 

/* LFSCIMCAPS.wCash_In_Limit  取值 */
#define 	LFS_CIM_LIMITNOTSUPP 				   (0x0000) 
#define 	LFS_CIM_LIMITBYTOTALITEMS 			   (0x0001) 
#define 	LFS_CIM_LIMITBYAMOUNT 				   (0x0002)

/* LFSCIMCAPS.wCount_Actions  取值 */
#define 	LFS_CIM_COUNTNOTSUPP 					(0x0000) 
#define 	LFS_CIM_COUNTINDIVIDUAL 				(0x0001) 
#define 	LFS_CIM_COUNTALL 						(0x0002)

/* LFSCIMCAPS.wCash_In_Mode  取值 */
#define 	LFS_CIM_CASHINMODENOTSUPP			    (0x0000)
#define 	LFS_CIM_NORMAL_MODE						(0x0001) 
#define 	LFS_CIM_RETRACT_MODE					(0x0002)
#define 	LFS_CIM_FORCE_MODE						(0x0004)		   
#define 	LFS_CIM_DIRECT_MODE						(0x0008)
#define 	LFS_CIM_CACHE_MODE						(0x0010)

/* LFSCIMP6INFO.usLevel */
/* LFSCIMP6SIGNATURE.usLevel 取值 */

#define     LFS_CIM_LEVEL_2                        (2)
#define     LFS_CIM_LEVEL_3                        (3)
#define     LFS_CIM_LEVEL_4 					   (4) 

/* LFSCIMTELLERUPDATE.usAction 取值 */

#define     LFS_CIM_CREATE_TELLER                  (1)
#define     LFS_CIM_MODIFY_TELLER                  (2)
#define     LFS_CIM_DELETE_TELLER                  (3)

/* LFSCIMCUERROR.wFailure 取值 */

#define     LFS_CIM_CASHUNITEMPTY                  (1)
#define     LFS_CIM_CASHUNITERROR                  (2)
#define     LFS_CIM_CASHUNITFULL                   (3)
#define     LFS_CIM_CASHUNITLOCKED                 (4)
#define     LFS_CIM_CASHUNITNOTCONF                (5)
#define     LFS_CIM_CASHUNITINVALID                (6)
#define     LFS_CIM_CASHUNITCONFIG                 (7)
#define     LFS_CIM_FEEDMODULEPROBLEM              (8)

/* LFSCIMP6SIGNATURE.dwOrientation 取值*/

#define     LFS_CIM_ORFRONTTOP                     (1)
#define     LFS_CIM_ORFRONTBOTTOM                  (2)
#define     LFS_CIM_ORBACKTOP                      (3)
#define     LFS_CIM_ORBACKBOTTOM                   (4)
#define     LFS_CIM_ORUNKNOWN                      (5)
#define     LFS_CIM_ORNOTSUPPORTED                 (6)

 /* LFSCIMGETITEMINFO.wItem_Info_Type 取值*/ 
#define     LFS_CIM_ITEM_SERIALNUMBER 				(0x00000001) 
#define     LFS_CIM_ITEM_SIGNATURE 					(0x00000002) 

/*  LFS_EXEE_CIM_INPUTREFUSE中lpusReason 取值 */

#define     LFS_CIM_CASHINUNITFULL              (1)
#define     LFS_CIM_INVALIDBILL                 (2)
#define     LFS_CIM_NOBILLSTODEPOSIT            (3)
#define     LFS_CIM_DEPOSITFAILURE              (4)
#define     LFS_CIM_COMMINPCOMPFAILURE          (5)
#define     LFS_CIM_STACKERFULL                 (6)
#define 	LFS_CIM_FOREIGN_ITEMS_DETECTED 		(7) 
#define 	LFS_CIM_INVALIDBUNCH 				(8) 
#define 	LFS_CIM_COUNTERFEIT 				(9) 
#define 	LFS_CIM_LIMITOVERTOTALITEMS 		(10) 
#define 	LFS_CIM_LIMITOVERAMOUNT 			(11)

/* LFS_EXEE_CIM_NOTESERROR中lpusReason 取值 */

#define     LFS_CIM_DOUBLENOTEDETECTED          (1)
#define     LFS_CIM_LONGNOTEDETECTED            (2)
#define     LFS_CIM_SKEWEDNOTE                  (3)
#define     LFS_CIM_INCORRECTCOUNT              (4)
#define     LFS_CIM_NOTESTOOCLOSE               (5)
#define 	LFS_CIM_OTHERNOTEERROR 				(6) 
#define 	LFS_CIM_SHORTNOTEDETECTED			(7) 

/* LFS_INF_CIM_POSITION_CAPABILITIES指令中wUsage的取值 */ 
#define 	LFS_CIM_POSIN 						(0x0001) 
#define 	LFS_CIM_POSREFUSE 					(0x0002) 
#define 	LFS_CIM_POSROLLBACK 				(0x0004) 

/* LFSCIMPOSITIONINFO.wAdditional_Bunches 取值*/ 
#define 	LFS_CIM_ADDBUNCHNONE 				(1) 
#define 	LFS_CIM_ADDBUNCHONEMORE 			(2) 
#define 	LFS_CIM_ADDBUNCHUNKNOWN 			(3) 

/* LFSCIMPOSITIONINFO.usBunches_Remaining 取值*/
#define 	LFS_CIM_NUMBERUNKNOWN 				(255) 

/* 错误码 */ 

#define LFS_ERR_CIM_INVALIDCURRENCY         (-(CIM_SERVICE_OFFSET + 0))
#define LFS_ERR_CIM_INVALIDTELLERID         (-(CIM_SERVICE_OFFSET + 1))
#define LFS_ERR_CIM_CASHUNITERROR           (-(CIM_SERVICE_OFFSET + 2))
#define LFS_ERR_CIM_TOOMANYITEMS            (-(CIM_SERVICE_OFFSET + 7))
#define LFS_ERR_CIM_UNSUPPOSITION           (-(CIM_SERVICE_OFFSET + 8))
#define LFS_ERR_CIM_SAFEDOOROPEN            (-(CIM_SERVICE_OFFSET + 10))
#define LFS_ERR_CIM_SHUTTERNOTOPEN          (-(CIM_SERVICE_OFFSET + 12))
#define LFS_ERR_CIM_SHUTTEROPEN             (-(CIM_SERVICE_OFFSET + 13))
#define LFS_ERR_CIM_SHUTTERCLOSED           (-(CIM_SERVICE_OFFSET + 14))
#define LFS_ERR_CIM_INVALIDCASHUNIT         (-(CIM_SERVICE_OFFSET + 15))
#define LFS_ERR_CIM_NOITEMS                 (-(CIM_SERVICE_OFFSET + 16))
#define LFS_ERR_CIM_EXCHANGEACTIVE          (-(CIM_SERVICE_OFFSET + 17))
#define LFS_ERR_CIM_NOEXCHANGEACTIVE        (-(CIM_SERVICE_OFFSET + 18))
#define LFS_ERR_CIM_SHUTTERNOTCLOSED        (-(CIM_SERVICE_OFFSET + 19))
#define LFS_ERR_CIM_ITEMSTAKEN              (-(CIM_SERVICE_OFFSET + 23))
#define LFS_ERR_CIM_CASHINACTIVE            (-(CIM_SERVICE_OFFSET + 25))
#define LFS_ERR_CIM_NOCASHINACTIVE          (-(CIM_SERVICE_OFFSET + 26))
#define LFS_ERR_CIM_POSITION_NOT_EMPTY      (-(CIM_SERVICE_OFFSET + 28))
#define LFS_ERR_CIM_INVALIDRETRACTPOSITION  (-(CIM_SERVICE_OFFSET + 34))
#define LFS_ERR_CIM_NOTRETRACTAREA          (-(CIM_SERVICE_OFFSET + 35))
#define LFS_ERR_CIM_INVALID_PORT 			(-(CIM_SERVICE_OFFSET + 36)) 
#define LFS_ERR_CIM_FOREIGN_ITEMS_DETECTED 	(-(CIM_SERVICE_OFFSET + 37)) 
#define LFS_ERR_CIM_LOADFAILED 				(-(CIM_SERVICE_OFFSET + 38)) 
#define LFS_ERR_CIM_CASHUNITNOTEMPTY 		(-(CIM_SERVICE_OFFSET + 39)) 
#define LFS_ERR_CIM_INVALIDREFSIG 			(-(CIM_SERVICE_OFFSET + 40)) 
#define LFS_ERR_CIM_INVALIDTRNSIG 			(-(CIM_SERVICE_OFFSET + 41)) 
#define LFS_ERR_CIM_POWERSAVETOOSHORT 		(-(CIM_SERVICE_OFFSET + 42)) 
#define LFS_ERR_CIM_POWERSAVEMEDIAPRESENT 	(-(CIM_SERVICE_OFFSET + 43)) 
#define LFS_ERR_CIM_TOOMANYITEMSTOCOUNT 	(-(CIM_SERVICE_OFFSET + 45)) 
#define LFS_ERR_CIM_COUNTPOSNOTEMPTY 		(-(CIM_SERVICE_OFFSET + 46))

/*=================================================================*/
/* 信息指令结构 */
/*=================================================================*/

typedef struct _LFS_CIM_in_pos
{
    WORD            wPosition;
    WORD            wShutter;
    WORD            wPosition_Status;
    WORD            wTransport;
    WORD            wTransport_Status;
} LFSCIMINPOS, * LPLFSCIMINPOS;

typedef struct _LFS_CIM_status
{
    WORD             wDevice;
    WORD             wSafe_Door; 
    WORD             wAcceptor;
    WORD             wIntermediate_Stacker; 
    WORD             wStacker_Items;
    WORD             wBank_Note_Reader;
    BOOL             bDrop_Box;
    LPLFSCIMINPOS * lppPositions;
    LPSTR            lpstrExtra;
    DWORD 			 dwGuid_Lights[LFS_CIM_GUIDLIGHTS_SIZE]; 
    WORD 			 wDevice_Position; 
    USHORT 			 usPower_Save_Recovery_Time; 
    WORD             wCash_Count_Status;
} LFSCIMSTATUS, * LPLFSCIMSTATUS;

typedef struct _LFS_CIM_caps
{
    WORD            wClass;
    WORD            wType;
    WORD            wMax_Cash_In_Items;
    BOOL            bCompound;
    BOOL            bShutter; 
    BOOL            bShutter_Control;
    BOOL            bSafe_Door; 
    BOOL            bCash_Box;
    BOOL            bRefill;
    WORD            wIntermediate_Stacker;
    BOOL            bItems_Taken_Sensor;
    BOOL            bItems_Inserted_Sensor;
    WORD            wPositions;
    WORD            wExchange_Type;
    WORD            wRetract_Areas;
    WORD            wRetract_Transport_Actions;
    WORD            wRetract_Stacker_Actions;
    LPSTR           lpstrExtra;
    DWORD 			dwGuid_Lights[LFS_CIM_GUIDLIGHTS_SIZE]; 
    DWORD 			dwItem_Info_Types; 
    BOOL 			bCompare_Signatures; 
    BOOL 			bPower_Save_Control; 
    BOOL 			bReplenish; 
    WORD 			wCash_In_Limit; 
    WORD 			wCount_Actions;
    WORD            wCash_In_Mode;
} LFSCIMCAPS, * LPLFSCIMCAPS;

typedef struct _LFS_CIM_physical_cu
{
    LPSTR           lpstrPhysical_Position_Name;
    CHAR            cUnit_ID[5];
    ULONG           ulCash_In_Count;
    ULONG           ulCount;
    ULONG           ulMaximum;
    USHORT          usPStatus;
    BOOL            bHardware_Sensors;
    LPSTR           lpstrExtra;
    ULONG 			ulInitial_Count; 
    ULONG 			ulDispensed_Count; 
    ULONG 			ulPresented_Count; 
    ULONG 			ulRetracted_Count; 
    ULONG 			ulReject_Count; 
} LFSCIMPHCU, * LPLFSCIMPHCU;

typedef struct _LFS_CIM_note_number
{
    USHORT          usNote_ID;
    ULONG           ulCount;
} LFSCIMNOTENUMBER, * LPLFSCIMNOTENUMBER;

typedef struct _LFS_CIM_note_number_list
{
    USHORT               usNum_Of_Note_Numbers;
    LPLFSCIMNOTENUMBER  *lppNote_Number;
} LFSCIMNOTENUMBERLIST, * LPLFSCIMNOTENUMBERLIST;

typedef struct _LFS_CIM_cash_in
{
    USHORT					usNumber;
    DWORD                   dwType;
    DWORD                   dwItem_Type;
    CHAR                    cUnit_ID[5];
    CHAR                    cCurrency_ID[3];
    ULONG                   ulValues;
    ULONG                   ulCash_In_Count;
    ULONG                   ulCount; 
    ULONG                   ulMaximum;
    USHORT                  usStatus;
    BOOL                    bApp_Lock;
    LPLFSCIMNOTENUMBERLIST	lpNote_Number_List;
    USHORT                  usNum_Physical_CUs;
    LPLFSCIMPHCU *			lppPhysical;
    LPSTR                   lpstrExtra;
    LPUSHORT 				lpusNote_IDs; 
    WORD 					usCDM_Type; 
    LPSTR 					lpszCash_Unit_Name; 
    ULONG 					ulInitial_Count; 
    ULONG 					ulDispensed_Count; 
    ULONG 					ulPresented_Count; 
    ULONG 					ulRetracted_Count; 
    ULONG 					ulReject_Count; 
    ULONG 					ulMinimum;
} LFSCIMCASHIN, * LPLFSCIMCASHIN;

typedef struct _LFS_CIM_cash_info
{
    USHORT              usCount;
    LPLFSCIMCASHIN     *lppCash_In;
} LFSCIMCASHINFO, * LPLFSCIMCASHINFO;

typedef struct _LFS_CIM_teller_info
{
    USHORT          usTeller_ID;
    CHAR            cCurrency_ID[3];
} LFSCIMTELLERINFO, * LPLFSCIMTELLERINFO;

typedef struct _LFS_CIM_teller_totals
{
   CHAR             cCurrency_ID[3];
   ULONG            ulItems_Received;
   ULONG            ulItems_Dispensed;
   ULONG            ulCoins_Received;
   ULONG            ulCoins_Dispensed;
   ULONG            ulCash_Box_Received;
   ULONG            ulCash_Box_Dispensed;
} LFSCIMTELLERTOTALS, * LPLFSCIMTELLERTOTALS;

typedef struct _LFS_CIM_teller_details
{
    USHORT          		usTeller_ID;
    WORD            		wInput_Position;
    WORD            		wOutput_Position;
    LPLFSCIMTELLERTOTALS 	*lppTeller_Totals;
} LFSCIMTELLERDETAILS, * LPLFSCIMTELLERDETAILS;

typedef struct _LFS_CIM_currency_exp
{
    CHAR            cCurrency_ID[3];
    SHORT           sExponent;
} LFSCIMCURRENCYEXP, * LPLFSCIMCURRENCYEXP;

typedef struct _LFS_CIM_note_type
{
    USHORT          usNote_ID;
    CHAR            cCurrency_ID[3];
    ULONG           ulValues;
    USHORT          usRelease;
    BOOL            bConfigured;
} LFSCIMNOTETYPE, * LPLFSCIMNOTETYPE;

typedef struct _LFS_CIM_note_type_list
{
    USHORT             usNum_Of_Note_Types;
    LPLFSCIMNOTETYPE  *lppNote_Types;
} LFSCIMNOTETYPELIST, * LPLFSCIMNOTETYPELIST;

typedef struct _LFS_CIM_cash_in_status
{
    WORD                    	wStatus;
    USHORT                  	usNum_Of_Refused;
    LPLFSCIMNOTENUMBERLIST  	lpNote_Number_List;
    LPSTR                   	lpstrExtra;
} LFSCIMCASHINSTATUS, * LPLFSCIMCASHINSTATUS;

typedef struct _LFS_CIM_p6_info
{
    USHORT                  	usLevel;
    LPLFSCIMNOTENUMBERLIST  	lpNote_Number_List;
    USHORT                 		usNum_Of_Signatures;
} LFSCIMP6INFO, *LPLFSCIMP6INFO;

typedef struct _LFS_CIM_get_p6_signature
{
    USHORT                  usLevel;
    USHORT                  usIndex;
} LFSCIMGETP6SIGNATURE, *LPLFSCIMGETP6SIGNATURE;

typedef struct _LFS_CIM_p6_signature 
{ 
    USHORT                 usNote_ID; 
    ULONG                  ulLength; 
    DWORD                  dwOrientation; 
    LPVOID                 lpSignature; 
} LFSCIMP6SIGNATURE, *LPLFSCIMP6SIGNATURE; 
typedef struct _LFS_CIM_get_item_info 
{ 
    USHORT    usLevel; 
    USHORT    usIndex; 
    DWORD     dwItem_Info_Type; 
} LFSCIMGETITEMINFO, *LPLFSCIMGETITEMINFO;

typedef struct _LFS_CIM_item_info 
{ 
    USHORT   			usNote_ID;
    LPWSTR    			lpszSerial_Number;
    LPLFSCIMP6SIGNATURE lpP6_Signature; 
} LFSCIMITEMINFO, *LPLFSCIMITEMINFO; 

typedef struct _LFS_CIM_item_info_summary 
{ 
    USHORT     usLevel; 
    USHORT     usNum_Of_Items; 
} LFSCIMITEMINFOSUMMARY, *LPLFSCIMITEMINFOSUMMARY;
 
typedef struct _LFS_CIM_pos_caps 
{ 
    WORD     wPosition; 
    WORD     wUsage; 
    BOOL     bShutter_Control; 
    BOOL     bItems_Taken_Sensor; 
    BOOL     bItems_Inserted_Sensor; 
    WORD     wRetract_Areas; 
    LPSTR    lpszExtra; 
} LFSCIMPOSCAPS, *LPLFSCIMPOSCAPS; 

typedef struct _LFS_CIM_pos_capabilities 
{ 
    LPLFSCIMPOSCAPS *lppPos_Capabilities; 
} LFSCIMPOSCAPABILITIES, *LPLFSCIMPOSCAPABILITIES; 
typedef struct  _LFS_CIM_replenish_info 
{ 
    USHORT 		usNumber_Source; 
} LFSCIMREPINFO, *LPLFSCIMREPINFO; 

typedef struct  _LFS_CIM_replenish_info_target 
{ 
    USHORT 		usNumber_Target; 
} LFSCIMREPINFOTARGET, *LPLFSCIMREPINFOTARGET; 

typedef struct  _LFS_CIM_replenish_info_result 
{ 
LPLFSCIMREPINFOTARGET *lppReplenish_Targets; 
} LFSCIMREPINFORES, *LPLFSCIMREPINFORES;

/*=================================================================*/
/* 执行指令结构 */
/*=================================================================*/

typedef struct _LFS_CIM_cash_in_start
{
    USHORT               usTeller_ID;
    BOOL                 bUse_Recycle_Units;
    WORD                 wOutput_Position;
    WORD                 wInput_Position;
} LFSCIMCASHINSTART, * LPLFSCIMCASHINSTART;

typedef struct _LFS_CIM_retract
{
    WORD             wOutput_Position;
    USHORT           usRetract_Area;
    USHORT           usIndex;
} LFSCIMRETRACT, * LPLFSCIMRETRACT;

typedef struct _LFS_CIM_teller_update
{
    USHORT                   usAction;
    LPLFSCIMTELLERDETAILS   lpTeller_Details;
} LFSCIMTELLERUPDATE,   * LPLFSCIMTELLERUPDATE;

typedef struct _LFS_CIM_output
{
    USHORT           usLogical_Number;
    WORD             wPosition;
    USHORT           usNumber;
} LFSCIMOUTPUT, * LPLFSCIMOUTPUT;

typedef struct _LFS_CIM_start_ex
{
    WORD             wExchange_Type;
    USHORT           usTeller_ID;
    USHORT           usCount;
    LPUSHORT         lpusCU_Num_List;
    LPLFSCIMOUTPUT   lpOutput;
} LFSCIMSTARTEX, * LPLFSCIMSTARTEX;

typedef struct _LFS_CIM_item_position
{
    USHORT             usNumber;
    LPLFSCIMRETRACT   lpRetract_Area;
    WORD               wOutput_Position;
} LFSCIMITEMPOSITION, * LPLFSCIMITEMPOSITION;

typedef struct _LFS_CIM_cash_in_type
{
    USHORT             usNumber;
    DWORD              dwType;
    LPUSHORT           lpusNote_IDs;
} LFSCIMCASHINTYPE, * LPLFSCIMCASHINTYPE;

typedef struct _LFS_CIM_set_guid_light 
{ 
    WORD 	wGuid_Light; 
    DWORD 	dwCommand; 
} LFSCIMSETGUIDLIGHT, *LPLFSCIMSETGUIDLIGHT; 

typedef struct _LFS_CIM_configure_note_reader 
{ 
    BOOL 	bLoad_Always; 
} LFSCIMCONFIGURENOTEREADER, *LPLFSCIMCONFIGURENOTEREADER; 
typedef struct _LFS_CIM_configure_note_reader_out 
{ 
    BOOL 	bReboot_Necessary; 
} LFSCIMCONFIGURENOTEREADEROUT, *LPLFSCIMCONFIGURENOTEREADEROUT; 
typedef struct _LFS_CIM_p6_compare_signature 
{ 
    LPLFSCIMP6SIGNATURE *lppP6_Reference_Signatures; 
    LPLFSCIMP6SIGNATURE *lppP6_Signatures; 
} LFSCIMP6COMPARESIGNATURE, *LPLFSCIMP6COMPARESIGNATURE; 
typedef struct _LFS_CIM_p6_signatures_index 
{ 
    USHORT 		usIndex; 
    USHORT 		usConfidence_Level; 
    ULONG 		ulLength; 
    LPVOID 		lpComparison_Data; 
} LFSCIMP6SIGNATURESINDEX, *LPLFSCIMP6SIGNATURESINDEX; 

typedef struct _LFS_CIM_P6_compare_result 
{ 
    USHORT                                        usCount; 
    LPLFSCIMP6SIGNATURESINDEX  *lppP6_Signatures_Index; 
} LFSCIMP6COMPARERESULT, *LPLFSCIMP6COMPARERESULT; 

typedef struct _LFS_CIM_power_save_control 
{ 
    USHORT usMax_Power_Save_Recovery_Time;
} LFSCIMPOWERSAVECONTROL, *LPLFSCIMPOWERSAVECONTROL; 

typedef struct _LFS_CIM_replenish_target 
{ 
    USHORT 			usNumber_Target; 
    ULONG 			ulNumber_Of_Items_To_Move; 
    BOOL 			bRemove_All; 
} LFSCIMREPTARGET, *LPLFSCIMREPTARGET; 

typedef struct _LFS_CIM_replenish 
{ 
    USHORT 				usNumber_Source; 
LPLFSCIMREPTARGET 	*lppReplenish_Targets; 
} LFSCIMREP, *LPLFSCIMREP; 

typedef struct _LFS_CIM_replenish_target_result 
{ 
    USHORT 		usNumber_Target; 
    USHORT 		usNote_ID; 
    ULONG 		ulNumber_Of_Items_Received; 
} LFSCIMREPTARGETRES, *LPLFSCIMREPTARGETRES; 

typedef struct _LFS_CIM_replenish_result 
{ 
    ULONG 	ulNumber_Of_Items_Removed; 
    ULONG 	ulNumber_Of_Items_Rejected; 
LPLFSCIMREPTARGETRES *lppReplenish_Target_Results; 
} LFSCIMREPRES, *LPLFSCIMREPRES;

typedef struct _LFS_CIM_amount_limit
{
    CHAR                     cCurrency_ID[3];
    ULONG                    ulAmount;
} LFSCIMAMOUNTLIMIT, *LPLFSCIMAMOUNTLIMIT;

typedef struct _LFS_CIM_cash_in_limit
{
    ULONG                    ulTotal_Items_Limit;
    LPLFSCIMAMOUNTLIMIT      lpAmount_Limit;
} LFSCIMCASHINLIMIT, *LPLFSCIMCASHINLIMIT;

typedef struct _LFS_CIM_count
{
    USHORT                   usCount;
    LPUSHORT                 lpusCU_Num_List;
} LFSCIMCOUNT, *LPLFSCIMCOUNT;

typedef struct _LFS_CIM_blacklist_element
{
    LPWSTR                   lpszSerial_Number;
    CHAR                     cCurrency_ID[3];
    ULONG                    ulValue;
} LFSCIMBLACKLISTELEMENT, *LPLFSCIMBLACKLISTELEMENT;

typedef struct _LFS_CIM_blacklist
{
    LPWSTR                   lpszVersion;
    USHORT                   usCount;
    LPLFSCIMBLACKLISTELEMENT *lppBlacklist_Elements;
} LFSCIMBLACKLIST, *LPLFSCIMBLACKLIST;

typedef struct __LFS_CIM_set_cash_in_mode
{
USHORT    usCash_In_Mode;
}LFSCIMSETCASHINMODE , * LPLFSCIMSETCASHINMODE ;

typedef struct _LFS_CIM_set_fsn_info
{
    USHORT               usTeller_ID;
    BYTE                 byFit_Code;
    LPSTR                lpstrFSN_Files_Path;
    LPSTR                lpszFSN_Number_Txt_Path;   
    LPSTR                lpstrFinan_Ins;
    LPSTR                lpstrEnable_Time;
    LPSTR                lpstrFinan_Inst;
    LPSTR                lpstrFinan_Inst_Outlet;         
} LFSCIMCASHSETFSNINFO , * LPLFSCIMCASHSETFSNINFO;

typedef struct _LFS_CIM_BANKNOTE_COUNT
{
    LPSTR               lpstrReal_Cash;
    LPSTR               lpstrRefused_Cash;
} LFSCIMBANKNOTECOUNT , * LPLFSCIMBANKNOTECOUNT ;

/*=================================================================*/
/* 事件结构 */
/*=================================================================*/

typedef struct _LFS_CIM_cu_error
{
    WORD               wFailure;
    LPLFSCIMCASHIN    lpCash_Unit;
} LFSCIMCUERROR, * LPLFSCIMCUERROR;

typedef struct _LFS_CIM_counts_changed
{
    USHORT            usCount;
    USHORT           *lpusCU_Num_List;
} LFSCIMCOUNTSCHANGED, * LPLFSCIMCOUNTSCHANGED;

typedef struct _LFS_CIM_input_refuse
{	
    USHORT 	usReason;
    WORD 		wPosition;
} LFSCIMINPUTREFUSE, *LPLFSCIMINPUTREFUSE;

typedef struct _LFS_CIM_position
{
    WORD 		wPosition; 
} LFSCIMPOSITION, * LPLFSCIMPOSITION;


typedef struct _LFS_CIM_position_info 
{ 
    WORD 		wPosition; 
    WORD 		wAdditional_Bunches; 
    USHORT 		usBunches_Remaining; 
} LFSCIMPOSITIONINFO, *LPLFSCIMPOSITIONINFO; 

typedef struct _LFS_CIM_device_position 
{ 
    WORD 	wPosition; 
} LFSCIMDEVICEPOSITION, *LPLFSCIMDEVICEPOSITION; 

typedef struct _LFS_CIM_power_save_change 
{ 
    USHORT 	usPower_Save_Recovery_Time; 
} LFSCIMPOWERSAVECHANGE, *LPLFSCIMPOWERSAVECHANGE; 

typedef struct _LFS_CIM_incomplete_replenish 
{ 
    LPLFSCIMREPRES 	lpReplenish; 
} LFSCIMINCOMPLETEREPLENISH, *LPLFSCIMINCOMPLETEREPLENISH;

/* 恢复对齐方式 */
#pragma pack (pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif  /* __INC_LFSCDM__H */