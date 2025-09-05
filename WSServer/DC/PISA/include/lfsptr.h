/******************************************************************************
*                                                                            *
* LFSptr.h - Printer and Scanning Device (PTR) definitions                   *
*                                                                            *
* Version 1.0                                                                *
*                                                                            *
******************************************************************************/

#ifndef __INC_LFSPTR__H
#define __INC_LFSPTR__H

#ifdef __cplusplus
extern "C" {
#endif

#include    "lfsapi.h"

/*  对齐方式   */
#pragma pack(push,1)


/*LFSPTRCAPS.wClass 取值 */

#define    LFS_SERVICE_CLASS_PTR            (1)
#define    LFS_SERVICE_CLASS_VERSION_PTR    (0x0001) /*Version 1.00 */
#define    LFS_SERVICE_CLASS_NAME_PTR       "PTR"

#define    PTR_SERVICE_OFFSET               (LFS_SERVICE_CLASS_PTR *100)

/*信息指令 */

#define    LFS_INF_PTR_STATUS               (PTR_SERVICE_OFFSET + 1)
#define    LFS_INF_PTR_CAPABILITIES         (PTR_SERVICE_OFFSET + 2)
#define    LFS_INF_PTR_FORM_LIST            (PTR_SERVICE_OFFSET + 3)
#define    LFS_INF_PTR_MEDIA_LIST           (PTR_SERVICE_OFFSET + 4)
#define    LFS_INF_PTR_QUERY_FORM           (PTR_SERVICE_OFFSET + 5)
#define    LFS_INF_PTR_QUERY_MEDIA          (PTR_SERVICE_OFFSET + 6)
#define    LFS_INF_PTR_QUERY_FIELD          (PTR_SERVICE_OFFSET + 7)
#define    LFS_INF_PTR_CODELINE_MAPPTRG	     (PTR_SERVICE_OFFSET + 8)
/*执行指令 */

#define    LFS_CMD_PTR_CONTROL_MEDIA        (PTR_SERVICE_OFFSET + 1)
#define    LFS_CMD_PTR_PRINT_FORM           (PTR_SERVICE_OFFSET + 2)
#define    LFS_CMD_PTR_READ_FORM            (PTR_SERVICE_OFFSET + 3)
#define    LFS_CMD_PTR_RAW_DATA             (PTR_SERVICE_OFFSET + 4)
#define    LFS_CMD_PTR_MEDIA_EXTENTS        (PTR_SERVICE_OFFSET + 5)
#define    LFS_CMD_PTR_RESET_COUNT          (PTR_SERVICE_OFFSET + 6)
#define    LFS_CMD_PTR_READ_IMAGE           (PTR_SERVICE_OFFSET + 7)
#define    LFS_CMD_PTR_RESET                (PTR_SERVICE_OFFSET + 8)
#define    LFS_CMD_PTR_RETRACT_MEDIA        (PTR_SERVICE_OFFSET + 9)
#define    LFS_CMD_PTR_DISPENSE_PAPER       (PTR_SERVICE_OFFSET + 10)
#define    LFS_CMD_PTR_SET_GUIDANCE_LIGHT   (PTR_SERVICE_OFFSET + 11)
#define    LFS_CMD_PTR_PRINT_RAW_FILE       (PTR_SERVICE_OFFSET + 12)
#define    LFS_CMD_PTR_LOAD_DEFINITION	      (PTR_SERVICE_OFFSET + 13)
#define    LFS_CMD_PTR_SUPPLY_REPLENISH	     (PTR_SERVICE_OFFSET + 14)
#define    LFS_CMD_PTR_POWER_SAVE_CONTROL   (PTR_SERVICE_OFFSET + 15)
#define    LFS_CMD_PTR_READ_IMAGE_EX        (PTR_SERVICE_OFFSET + 16)
#define    LFS_CMD_PTR_IMPORT_KEY           (PTR_SERVICE_OFFSET + 17)

/*事件 */

#define    LFS_EXEE_PTR_NOMEDIA             (PTR_SERVICE_OFFSET + 1)
#define    LFS_EXEE_PTR_MEDIAINSERTED       (PTR_SERVICE_OFFSET + 2)
#define    LFS_EXEE_PTR_FIELDERROR          (PTR_SERVICE_OFFSET + 3)
#define    LFS_EXEE_PTR_FIELDWARNING        (PTR_SERVICE_OFFSET + 4)
#define    LFS_USRE_PTR_RETRACTBINTHRESHOLD (PTR_SERVICE_OFFSET + 5)
#define    LFS_SRVE_PTR_MEDIATAKEN          (PTR_SERVICE_OFFSET + 6)
#define    LFS_USRE_PTR_PAPERTHRESHOLD      (PTR_SERVICE_OFFSET + 7)
#define    LFS_USRE_PTR_TONERTHRESHOLD      (PTR_SERVICE_OFFSET + 8)
#define    LFS_SRVE_PTR_MEDIAINSERTED       (PTR_SERVICE_OFFSET + 9)
#define    LFS_USRE_PTR_LAMPTHRESHOLD       (PTR_SERVICE_OFFSET + 10)
#define    LFS_USRE_PTR_INKTHRESHOLD        (PTR_SERVICE_OFFSET + 11)
#define    LFS_SRVE_PTR_MEDIADETECTED       (PTR_SERVICE_OFFSET + 12)
#define	   LFS_SRVE_PTR_RETRACTBINSTATUS	(PTR_SERVICE_OFFSET + 13)
#define    LFS_EXEE_PTR_MEDIAPRESENTED	      (PTR_SERVICE_OFFSET + 14)
#define    LFS_SRVE_PTR_DEFINITIONLOADED    (PTR_SERVICE_OFFSET + 15)
#define    LFS_EXEE_PTR_MEDIAREJECTED	       (PTR_SERVICE_OFFSET + 16)
#define    LFS_SRVE_PTR_MEDIAPRESENTED      (PTR_SERVICE_OFFSET + 17)
#define    LFS_SRVE_PTR_MEDIAAUTORETRACTED  (PTR_SERVICE_OFFSET + 18)
#define    LFS_SRVE_PTR_DEVICEPOSITION	      (PTR_SERVICE_OFFSET + 19)
#define    LFS_SRVE_PTR_POWER_SAVE_CHANGE   (PTR_SERVICE_OFFSET + 20)
/*LFSPTRSTATUS.wDevice取值 */
 
#define    LFS_PTR_DEVONLINE                LFS_STAT_DEVONLINE
#define    LFS_PTR_DEVOFFLINE               LFS_STAT_DEVOFFLINE
#define    LFS_PTR_DEVPOWEROFF              LFS_STAT_DEVPOWEROFF
#define    LFS_PTR_DEVNODEVICE              LFS_STAT_DEVNODEVICE
#define    LFS_PTR_DEVHWERROR               LFS_STAT_DEVHWERROR
#define    LFS_PTR_DEVUSERERROR             LFS_STAT_DEVUSERERROR
#define    LFS_PTR_DEVBUSY                  LFS_STAT_DEVBUSY
#define    LFS_PTR_DEVFRAUDATTEMPT 	         LFS_STAT_DEVFRAUDATTEMPT


/*LFSPTRSTATUS.wMedia and
LFSPTRMEDIADETECTED.wPosition
取值 */

#define    LFS_PTR_MEDIAPRESENT             (0)
#define    LFS_PTR_MEDIANOTPRESENT          (1)
#define    LFS_PTR_MEDIAJAMMED              (2)
#define    LFS_PTR_MEDIANOTSUPP             (3)
#define    LFS_PTR_MEDIAUNKNOWN             (4)
#define    LFS_PTR_MEDIAENTERING            (5)
#define    LFS_PTR_MEDIARETRACTED           (6)


/*wPaper数组的大小和下标上限  */

#define    LFS_PTR_SUPPLYSIZE    (16)
#define    LFS_PTR_SUPPLYMAX     (LFS_PTR_SUPPLYSIZE - 1)


/*LFSPTRSTATUS.wPaper[...] 数组的下标 */ 

#define    LFS_PTR_SUPPLYUPPER              (0)
#define    LFS_PTR_SUPPLYLOWER              (1)
#define    LFS_PTR_SUPPLYEXTERNAL           (2)
#define    LFS_PTR_SUPPLYAUX                (3)
#define    LFS_PTR_SUPPLYAUX2               (4)
#define    LFS_PTR_SUPPLYPARK               (5)


/*LFSPTRSTATUS.wPaper  and
LFSPTRPAPERTHRESHOLD.wPaper_Source
取值 */

#define    LFS_PTR_PAPERFULL                (0)
#define    LFS_PTR_PAPERLOW                 (1)
#define    LFS_PTR_PAPEROUT                 (2)
#define    LFS_PTR_PAPERNOTSUPP             (3)
#define    LFS_PTR_PAPERUNKNOWN             (4)
#define    LFS_PTR_PAPERJAMMED              (5)


/*LFSPTRSTATUS.wToner取值 */

#define    LFS_PTR_TONERFULL                (0)
#define    LFS_PTR_TONERLOW                 (1)
#define    LFS_PTR_TONEROUT                 (2)
#define    LFS_PTR_TONERNOTSUPP             (3)
#define    LFS_PTR_TONERUNKNOWN             (4)


/*LFSPTRSTATUS.wInk取值 */

#define    LFS_PTR_INKFULL                  (0)
#define    LFS_PTR_INKLOW                   (1)
#define    LFS_PTR_INKOUT                   (2)
#define    LFS_PTR_INKNOTSUPP               (3)
#define    LFS_PTR_INKUNKNOWN               (4)


/*LFSPTRSTATUS.wLamp取值 */

#define    LFS_PTR_LAMPOK                   (0)
#define    LFS_PTR_LAMPFADING               (1)
#define    LFS_PTR_LAMPINOP                 (2)
#define    LFS_PTR_LAMPNOTSUPP              (3)
#define    LFS_PTR_LAMPUNKNOWN              (4)


/*LFSPTRSTATUS.lppRetract_Bins and
LFSPTRBINTHRESHOLD.wRetract_Bin 
	 取值 */

#define    LFS_PTR_RETRACTBINOK             (0)
#define    LFS_PTR_RETRACTBINFULL           (1)
#define    LFS_PTR_RETRACTNOTSUPP           (2)
#define    LFS_PTR_RETRACTUNKNOWN           (3)
#define    LFS_PTR_RETRACTBINHIGH           (4)

/* additional values of LFSPTRSTATUS.lppRetract_Bins*/

#define    LFS_PTR_RETRACTBINMISSING 	       (5)

/* Size and max index of dwGuid_Lights array */

#define    LFS_PTR_GUIDLIGHTS_SIZE 	         (32)
#define    LFS_PTR_GUIDLIGHTS_MAX 	          (LFS_PTR_GUIDLIGHTS_SIZE - 1)

/* Indices of LFSPTRSTATUS.dwGuid_Lights [...]
LFSPTRCAPS.dwGuid_Lights [...] */

#define    LFS_PTR_GUIDANCE_PRINTER 	         (0)


/* Values of LFSPTRSTATUS.dwGuid_Lights [...]
LFSPTRCAPS.dwGuid_Lights [...] */

#define    LFS_PTR_GUIDANCE_NOT_AVAILABLE     (0x00000000)
#define    LFS_PTR_GUIDANCE_OFF               (0x00000001)
#define    LFS_PTR_GUIDANCE_SLOW_FLASH        (0x00000004)
#define    LFS_PTR_GUIDANCE_MEDIUM_FLASH      (0x00000008)
#define    LFS_PTR_GUIDANCE_QUICK_FLASH       (0x00000010)
#define    LFS_PTR_GUIDANCE_CONTINUOUS        (0x00000080)
#define    LFS_PTR_GUIDANCE_RED 	              (0x00000100)
#define    LFS_PTR_GUIDANCE_GREEN 	            (0x00000200)
#define    LFS_PTR_GUIDANCE_YELLOW 	           (0x00000400)
#define    LFS_PTR_GUIDANCE_BLUE 	             (0x00000800)
#define    LFS_PTR_GUIDANCE_CYAN              (0x00001000)
#define    LFS_PTR_GUIDANCE_MAGENTA 	          (0x00002000)
#define    LFS_PTR_GUIDANCE_WHITE 	            (0x00004000)

/* values of LFSPTRSTATUS.wDevice_Position
LFSPTRDEVICEPOSITION.wPosition */

#define    LFS_PTR_DEVICEINPOSITION          (0)
#define    LFS_PTR_DEVICENOTINPOSITION 	      (1)
#define    LFS_PTR_DEVICEPOSUNKNOWN 	         (2)
#define    LFS_PTR_DEVICEPOSNOTSUPP 	         (3)

/*LFSPTRCAPS.wType取值 */

#define    LFS_PTR_TYPERECEIPT              0x0001
#define    LFS_PTR_TYPEPASSBOOK             0x0002
#define    LFS_PTR_TYPEJOURNAL              0x0004
#define    LFS_PTR_TYPEDOCUMENT             0x0008
#define    LFS_PTR_TYPESCANNER              0x0010


/*LFSPTRCAPS.wDev_Resolution, LFSPTRPRINTFORM.wResolution取值 */

#define    LFS_PTR_RESLOW                   0x0001
#define    LFS_PTR_RESMED                   0x0002
#define    LFS_PTR_RESHIGH                  0x0004
#define    LFS_PTR_RESVERYHIGH              0x0008


/*LFSPTRCAPS.wRead_form 取值 */

#define    LFS_PTR_READOCR                  0x0001
#define    LFS_PTR_READMICR                 0x0002
#define    LFS_PTR_READMSF                  0x0004
#define    LFS_PTR_READBARCODE              0x0008
#define    LFS_PTR_READPAGEMARK             0x0010
#define    LFS_PTR_READIMAGE                0x0020
#define    LFS_PTR_READEMPTYLINE            0x0040


/*LFSPTRCAPS.wWrite_form 取值 */

#define    LFS_PTR_WRITETEXT                0x0001
#define    LFS_PTR_WRITEGRAPHICS            0x0002
#define    LFS_PTR_WRITEOCR                 0x0004
#define    LFS_PTR_WRITEMICR                0x0008
#define    LFS_PTR_WRITEMSF                 0x0010
#define    LFS_PTR_WRITEBARCODE             0x0020
#define    LFS_PTR_WRITESTAMP               0x0040

/*LFSPTRCAPS.wDev_Extents 取值 */

#define    LFS_PTR_EXTHORIZONTAL            0x0001
#define    LFS_PTR_EXTVERTICAL              0x0002

/*LFSPTRCAPS.wDev_Control, lpdwMedia_Control 取值 */

#define    LFS_PTR_CTRLEJECT                0x0001
#define    LFS_PTR_CTRLPERFORATE            0x0002
#define    LFS_PTR_CTRLCUT                  0x0004
#define    LFS_PTR_CTRLSKIP                 0x0008
#define    LFS_PTR_CTRLFLUSH                0x0010
#define    LFS_PTR_CTRLRETRACT              0x0020
#define    LFS_PTR_CTRLSTACK                0x0040
#define    LFS_PTR_CTRLPARTIALCUT           0x0080
#define    LFS_PTR_CTRLALARM                0x0100
#define    LFS_PTR_CTRLATPFORWARD           0x0200
#define    LFS_PTR_CTRLATPBACKWARD          0x0400
#define    LFS_PTR_CTRLTURNMEDIA            0x0800
#define    LFS_PTR_CTRLSTAMP                0x1000
#define    LFS_PTR_CTRLPARK                 0x2000
#define    LFS_PTR_CTRLEXPEL 	               0x4000
#define    LFS_PTR_CTRLEJECTTOTRANSPORT     0x8000

/*LFSPTRCAPS.wPaper_Sources,
LFSFRMMEDIA.wPaper_Sources,
LFSPTRPRINTFORM.wPaper_Sources and
LFSPTRPAPERTHRESHOLD.wPaper_Sources  
取值 */

#define    LFS_PTR_PAPERANY                 0x0001
#define    LFS_PTR_PAPERUPPER               0x0002
#define    LFS_PTR_PAPERLOWER               0x0004
#define    LFS_PTR_PAPEREXTERNAL            0x0008
#define    LFS_PTR_PAPERAUX                 0x0010
#define    LFS_PTR_PAPERAUX2                0x0020
#define    LFS_PTR_PAPERPARK                0x0040


/*LFSPTRCAPS.wImage_Type,
LFSPTRIMAGEREQUEST.wFront_Image_Type and
LFSPTRIMAGEREQUEST.wBack_Image_Type 
取值 */

#define    LFS_PTR_IMAGETIF                 0x0001
#define    LFS_PTR_IMAGEWMF                 0x0002
#define    LFS_PTR_IMAGEBMP                 0x0004
#define    LFS_PTR_IMAGEJPG                 0x0008

/*LFSPTRCAPS.wFront_Image_Color_Format,
LFSPTRCAPS.wBack_Image_Color_Format,
LFSPTRIMAGEREQUEST.wFront_Image_Color_Format and
LFSPTRIMAGEREQUEST.wBack_Image_Color_Format 
取值 */

#define    LFS_PTR_IMAGECOLORBINARY         0x0001
#define    LFS_PTR_IMAGECOLORGRAYSCALE      0x0002
#define    LFS_PTR_IMAGECOLORFULL           0x0004


/*LFSPTRCAPS.wCodeline_Format and
LFSPTRIMAGEREQUEST.wCodeline_Format
取值 */

#define    LFS_PTR_CODELINECMC7             0x0001
#define    LFS_PTR_CODELINEE13B             0x0002
#define    LFS_PTR_CODELINEOCR              0x0004


/*LFSPTRCAPS.wImage_Source,
LFSPTRIMAGEREQUEST.wImage_Source and
LFSPTRIMAGE.wImage_Source 
取值 */

#define    LFS_PTR_IMAGEFRONT               0x0001
#define    LFS_PTR_IMAGEBACK                0x0002
#define    LFS_PTR_CODELINE                 0x0004

#define    LFS_PTR_IMAGETYPE0 	              0x8000
#define    LFS_PTR_IMAGETYPE1 	              0x4000
#define    LFS_PTR_IMAGETYPE2 	              0x2000

/*LFSPTRCAPS.wChar_Support, LFSFRMHEADER.wChar_Support 取值 */

#define    LFS_PTR_UTF8	              0x0001
#define    LFS_PTR_UNICODE                  0x0002

/*LFSFRMHEADER.wBase, LFSFRMMEDIA.wBase, LFSPTRMEDIAUNIT.wBase取值 */

#define    LFS_FRM_INCH                     (0)
#define    LFS_FRM_MM                       (1)
#define    LFS_FRM_ROWCOLUMN                (2)


/*LFSFRMHEADER.wAlignment取值 */

#define    LFS_FRM_TOPLEFT                  (0)
#define    LFS_FRM_TOPRIGHT                 (1)
#define    LFS_FRM_BOTTOMLEFT               (2)
#define    LFS_FRM_BOTTOMRIGHT              (3)


/*LFSFRMHEADER.wOrientation取值 */

#define    LFS_FRM_PORTRAIT                 (0)
#define    LFS_FRM_LANDSCAPE                (1)


/*LFSFRMMEDIA.wMedia_Type 取值 */

#define    LFS_FRM_MEDIAGENERIC             (0)
#define    LFS_FRM_MEDIAPASSBOOK            (1)
#define    LFS_FRM_MEDIAMULTIPART           (2)


/*LFSFRMMEDIA.wFold_Type 取值 */

#define    LFS_FRM_FOLDNONE                 (0)
#define    LFS_FRM_FOLDHORIZONTAL           (1)
#define    LFS_FRM_FOLDVERTICAL             (2)


/*LFSFRMFIELD.wType取值 */

#define    LFS_FRM_FIELDTEXT                (0)
#define    LFS_FRM_FIELDMICR                (1)
#define    LFS_FRM_FIELDOCR                 (2)
#define    LFS_FRM_FIELDMSF                 (3)
#define    LFS_FRM_FIELDBARCODE             (4)
#define    LFS_FRM_FIELDGRAPHIC             (5)
#define    LFS_FRM_FIELDPAGEMARK            (6)


/*LFSFRMFIELD.wField_Class取值 */

#define    LFS_FRM_CLASSSTATIC              (0)
#define    LFS_FRM_CLASSOPTIONAL            (1)
#define    LFS_FRM_CLASSREQUIRED            (2)


/*LFSFRMFIELD.wAccess取值 */

#define    LFS_FRM_ACCESSREAD               0x0001
#define    LFS_FRM_ACCESSWRITE              0x0002


/*LFSFRMFIELD.wOverflow取值 */

#define    LFS_FRM_OVFTERMINATE             (0)
#define    LFS_FRM_OVFTRUNCATE              (1)
#define    LFS_FRM_OVFBESTFIT               (2)
#define    LFS_FRM_OVFOVERWRITE             (3)
#define    LFS_FRM_OVFWORDWRAP              (4)


/*LFSPTRFIELDFAIL.wFailure取值 */

#define    LFS_PTR_FIELDREQUIRED            (0)
#define    LFS_PTR_FIELDSTATICOVWR          (1)
#define    LFS_PTR_FIELDOVERFLOW            (2)
#define    LFS_PTR_FIELDNOTFOUND            (3)
#define    LFS_PTR_FIELDNOTREAD             (4)
#define    LFS_PTR_FIELDNOTWRITE            (5)
#define    LFS_PTR_FIELDHWERROR             (6)
#define    LFS_PTR_FIELDTYPENOTSUPPORTED    (7)
#define    LFS_PTR_FIELDGRAPHIC             (8)
#define    LFS_PTR_CHARSETFORM              (9)


/*LFSPTRPRINTFORM.wAlignment取值 */

#define    LFS_PTR_ALNUSEFORMDEFN           (0)
#define    LFS_PTR_ALNTOPLEFT               (1)
#define    LFS_PTR_ALNTOPRIGHT              (2)
#define    LFS_PTR_ALNBOTTOMLEFT            (3)
#define    LFS_PTR_ALNBOTTOMRIGHT           (4)


/*LFSPTRPRINTFORM.wOffset_X and LFSPTRPRINTFORM.wOffset_Y 取值*/

#define    LFS_PTR_OFFSETUSEFORMDEFN        0xffff


/*LFSPTRRAWDATA.wInput_Data 取值 */

#define    LFS_PTR_NOINPUTDATA              (0)
#define    LFS_PTR_INPUTDATA                (1)


/*LFSPTRIMAGE.wStatus取值 */

#define     LFS_PTR_DATAOK                  (0)
#define     LFS_PTR_DATASRCNOTSUPP          (1)
#define     LFS_PTR_DATASRCMISSING          (2)

/*LFSPTRBINSTATUS.wRetract_Bin 取值*/

#define     LFS_PTR_RETRACTBININSERTED       (1)
#define     LFS_PTR_RETRACTBINREMOVED 	       (2)

/*LFSPTRDEFINITIONLOADED.dwDefinition_Type取值*/

#define     LFS_PTR_FORMLOADED 	         (0x00000001)
#define     LFS_PTR_MEDIALOADED         (0x00000002)


/*LFSPTRSUPPLYREPLEN.fwSupply_Replen取值*/

#define     LFS_PTR_REPLEN_PAPERUPPER 	        (0x0001)
#define     LFS_PTR_REPLEN_PAPERLOWER 	        (0x0002)
#define     LFS_PTR_REPLEN_PAPERAUX 	          (0x0004)
#define     LFS_PTR_REPLEN_PAPERAUX2 	         (0x0008)
#define     LFS_PTR_REPLEN_TONER 	             (0x0010)
#define     LFS_PTR_REPLEN_INK 	               (0x0020)
#define     LFS_PTR_REPLEN_LAMP 	              (0x0040)

/*LFSPTRMEDIAREJECTED.wMedia_Rejected取值*/

#define     LFS_PTR_REJECT_SHORT 					(0)
#define     LFS_PTR_REJECT_LONG 					(1)
#define     LFS_PTR_REJECT_MULTIPLE 				(2)
#define     LFS_PTR_REJECT_ALIGN 					(3)
#define     LFS_PTR_REJECT_MOVETOALIGN 			(4)
#define     LFS_PTR_REJECT_SHUTTER 				(5)
#define     LFS_PTR_REJECT_ESCROW 				(6)
#define     LFS_PTR_REJECT_THICK 					(7)
#define     LFS_PTR_REJECT_OTHER 					(8)

/*LFSPTRMEDIARETRACTED.wRetract_Result取值*/

#define     LFS_PTR_AUTO_RETRACT_OK 				(0)
#define     LFS_PTR_AUTO_RETRACT_MEDIAJAMMED 		(1)

/*LFSPTRIMAGEREQUESTEX.wEncrypt_Mode取值*/

#define     LFS_PTR_NOT_ENCRYPT 	            (0)
#define     LFS_PTR_MODESM4		                (1)

/*LFSPTRIMPORTKEYEX.dwUse取值*/

#define LFS_PTR_USECRYPT                            (0x0001)
#define LFS_PTR_USEFUNCTION                         (0x0002)
#define LFS_PTR_USEMACING                           (0x0004)
#define LFS_PTR_USEKEYENCKEY                        (0x0020)
#define LFS_PTR_USENODUPLICATE                      (0x0040)
#define LFS_PTR_USESVENCKEY                         (0x0080)
#define LFS_PTR_USECONSTRUCT                        (0x0100)
#define LFS_PTR_USESECURECONSTRUCT                  (0x0200)
#define LFS_PTR_USEANSTR31MASTER                    (0x0400)

/* LFSPTRIMPORTKEYEX.wKey_Check_Mode */

#define LFS_PTR_KCVNONE                             (0x0000)
#define LFS_PTR_KCVSELF                             (0x0001)
#define LFS_PTR_KCVZERO                             (0x0002)

/*错误码 */ 

#define    LFS_ERR_PTR_FORMNOTFOUND         (-(PTR_SERVICE_OFFSET + 0))
#define    LFS_ERR_PTR_FIELDNOTFOUND        (-(PTR_SERVICE_OFFSET + 1))
#define    LFS_ERR_PTR_NOMEDIAPRESENT       (-(PTR_SERVICE_OFFSET + 2))
#define    LFS_ERR_PTR_READNOTSUPPORTED     (-(PTR_SERVICE_OFFSET + 3))
#define    LFS_ERR_PTR_FLUSHFAIL            (-(PTR_SERVICE_OFFSET + 4))
#define    LFS_ERR_PTR_MEDIAOVERFLOW        (-(PTR_SERVICE_OFFSET + 5))
#define    LFS_ERR_PTR_FIELDSPECFAILURE     (-(PTR_SERVICE_OFFSET + 6))
#define    LFS_ERR_PTR_FIELDERROR           (-(PTR_SERVICE_OFFSET + 7))
#define    LFS_ERR_PTR_MEDIANOTFOUND        (-(PTR_SERVICE_OFFSET + 8))
#define    LFS_ERR_PTR_EXTENTNOTSUPPORTED   (-(PTR_SERVICE_OFFSET + 9))
#define    LFS_ERR_PTR_MEDIAINVALID         (-(PTR_SERVICE_OFFSET + 10))
#define    LFS_ERR_PTR_FORMINVALID          (-(PTR_SERVICE_OFFSET + 11))
#define    LFS_ERR_PTR_FIELDINVALID         (-(PTR_SERVICE_OFFSET + 12))
#define    LFS_ERR_PTR_MEDIASKEWED          (-(PTR_SERVICE_OFFSET + 13))
#define    LFS_ERR_PTR_RETRACTBINFULL       (-(PTR_SERVICE_OFFSET + 14))
#define    LFS_ERR_PTR_STACKERFULL          (-(PTR_SERVICE_OFFSET + 15))
#define    LFS_ERR_PTR_PAGETURNFAIL         (-(PTR_SERVICE_OFFSET + 16))
#define    LFS_ERR_PTR_MEDIATURNFAIL        (-(PTR_SERVICE_OFFSET + 17))
#define    LFS_ERR_PTR_SHUTTERFAIL          (-(PTR_SERVICE_OFFSET + 18))
#define    LFS_ERR_PTR_MEDIAJAMMED          (-(PTR_SERVICE_OFFSET + 19))
#define    LFS_ERR_PTR_FILE_IO_ERROR        (-(PTR_SERVICE_OFFSET + 20))
#define    LFS_ERR_PTR_CHARSETDATA          (-(PTR_SERVICE_OFFSET + 21))
#define    LFS_ERR_PTR_PAPERJAMMED          (-(PTR_SERVICE_OFFSET + 22))
#define    LFS_ERR_PTR_PAPEROUT             (-(PTR_SERVICE_OFFSET + 23))
#define    LFS_ERR_PTR_INKOUT               (-(PTR_SERVICE_OFFSET + 24))
#define    LFS_ERR_PTR_TONEROUT             (-(PTR_SERVICE_OFFSET + 25))
#define    LFS_ERR_PTR_LAMPINOP             (-(PTR_SERVICE_OFFSET + 26))
#define    LFS_ERR_PTR_SOURCEINVALID        (-(PTR_SERVICE_OFFSET + 27))
#define    LFS_ERR_PTR_SEQUENCEINVALID      (-(PTR_SERVICE_OFFSET + 28))
#define    LFS_ERR_PTR_MEDIASIZE            (-(PTR_SERVICE_OFFSET + 29))
#define    LFS_ERR_PTR_INVALID_PORT 	        (-(PTR_SERVICE_OFFSET + 30))
#define    LFS_ERR_PTR_MEDIARETAINED 	       (-(PTR_SERVICE_OFFSET + 31))
#define    LFS_ERR_PTR_BLACKMARK 	           (-(PTR_SERVICE_OFFSET + 32))
#define    LFS_ERR_PTR_DEFINITIONEXISTS     (-(PTR_SERVICE_OFFSET + 33))
#define    LFS_ERR_PTR_MEDIAREJECTED 	       (-(PTR_SERVICE_OFFSET + 34))
#define    LFS_ERR_PTR_MEDIARETRACTED 	      (-(PTR_SERVICE_OFFSET + 35))
#define    LFS_ERR_PTR_MSFERROR 	            (-(PTR_SERVICE_OFFSET + 36))
#define    LFS_ERR_PTR_NOMSF 	               (-(PTR_SERVICE_OFFSET + 37))
#define    LFS_ERR_PTR_FILENOTFOUND 	        (-(PTR_SERVICE_OFFSET + 38))


/*=================================================================*/
/*信息指令结构体 */
/*=================================================================*/

typedef struct _LFS_PTR_retract_bins
{
WORD				wRetract_Bin;  
USHORT				usRetract_Count; 
} LFSPTRRETRACTBINS, *LPLFSPTRRETRACTBINS; 

typedef struct _LFS_PTR_status
{
WORD						wDevice; 
WORD						wMedia; 
WORD						wPaper[LFS_PTR_SUPPLYSIZE]; 
WORD						wToner;  
WORD						wInk; 
WORD						wLamp; 
LPLFSPTRRETRACTBINS			        *lppRetract_Bins;  
USHORT						usMedia_On_Stacker; 
LPSTR						lpstrExtra; 
DWORD						dwGuid_Lights[LFS_PTR_GUIDLIGHTS_SIZE]; 
WORD						wDevice_Position; 
USHORT						usPower_Save_Recovery_Time; 	
} LFSPTRSTATUS, *LPLFSPTRSTATUS;

typedef struct _LFS_PTR_caps
{
WORD				wClass; 
WORD				wType; 
BOOL				bCompound; 
WORD				wDev_Resolution; 
WORD				wRead_form; 
WORD				wWrite_form; 
WORD				wDev_Extents; 
WORD				wDev_Control; 
USHORT				usMax_Media_On_Stacker; 
BOOL				bAccept_Media; 
BOOL				bMulti_Page;  
WORD				wPaper_Sources; 
BOOL				bMedia_Taken;  
USHORT				usRetract_Bins;  
LPUSHORT			lpusMax_Retract;  
WORD				wImage_Type; 
WORD				wFront_Image_Color_Format;  
WORD				wBack_Image_Color_Format;  
WORD				wCodeline_Format; 
WORD				wImage_Source;  
WORD				wChar_Support;  
BOOL				bDispense_Paper;  
LPSTR				lpstrExtra; 
DWORD				dwGuid_Lights[LFS_PTR_GUIDLIGHTS_SIZE]; 
LPSTR				lpszPrinter; 
BOOL				bMedia_Presented; 
USHORT				usAuto_Retract_Period; 
BOOL				bRetract_To_Transport; 
BOOL				bPower_Save_Control; 
} LFSPTRCAPS, *LPLFSPTRCAPS; 

typedef struct _LFS_frm_header
{
LPSTR				lpstrForm_Name; 
WORD				wBase; 
WORD				wUnit_X; 
WORD				wUnit_Y; 
WORD				wWidth; 
WORD				wHeight; 
WORD				wAlignment; 
WORD				wOrientation; 
WORD				wOffset_X; 
WORD				wOffset_Y; 
WORD				wVersion_Major;  
WORD				wVersion_Minor;  
LPSTR				lpstrUser_Prompt;  
WORD				wChar_Support; 
LPSTR				lpstrFields; 
WORD				wLanguage_ID; 
} LFSFRMHEADER, *LPLFSFRMHEADER;

typedef struct _LFS_frm_media
{
WORD				wMedia_Type;  
WORD				wBase;  	
WORD				wUnit_X;  
WORD				wUnit_Y;  
WORD				wSize_Width;  
WORD				wSize_Height;  
WORD				wPage_Count;  
WORD				wLine_Count;  
WORD				wPrint_Area_X;  
WORD				wPrint_Area_Y; 
WORD				wPrint_Area_Width;  
WORD				wPrint_Area_Height;  
WORD				wRestricted_Area_X; 
WORD				wRestricted_Area_Y; 
WORD				wRestricted_Area_Width;  
WORD				wRestricted_Area_Height;  
WORD				wStagger; 
WORD				wFold_Type;  
WORD				wPaper_Sources; 
} LFSFRMMEDIA, *LPLFSFRMMEDIA;

typedef struct _LFS_PTR_query_field
{
LPSTR				lpstrForm_Name; 
LPSTR				lpstrField_Name; 
} LFSPTRQUERYFIELD, *LPLFSPTRQUERYFIELD; 

typedef struct _LFS_frm_field
{
LPSTR				lpstrField_Name;  
WORD				wIndex_Count;  
WORD				wType;  
WORD				wField_Class;  
WORD				wAccess;  
WORD				wOverflow;  
LPSTR				lpstrInitial_Value; 
LPWSTR				lpwstrUnicode_Initial_Value;  
LPSTR				lpstrFormat; 
LPWSTR				lpwstrUnicode_Format; 
WORD				wLanguage_ID; 
} LFSFRMFIELD, *LPLFSFRMFIELD;

typedef struct _LFS_PTR_hex_data
{
USHORT              usLength;
LPBYTE              lpbData;
} LFSPTRXDATA, *LPLFSPTRXDATA;

typedef struct _LFS_PTR_codeline_mapPTRg
{
WORD                 wCodeline_Format;
}LFSPTRCODELINEMAPPTRG, *LPLFSPTRCODELINEMAPPTRG;

/*=================================================================*/
/*执行指令结构体 */
/*=================================================================*/

typedef struct _LFS_PTR_print_form
{
LPSTR				lpstrForm_Name;
LPSTR				lpstrMedia_Name; 
WORD				wAlignment; 
WORD				wOffset_X;
WORD				wOffset_Y;
WORD				wResolution;
DWORD				dwMedia_Control; 
LPSTR				lpstrFields;
LPWSTR				lpwstrUnicode_Fields;
WORD				wPaper_Source;
} LFSPTRPRINTFORM, *LPLFSPTRPRINTFORM; 

typedef struct _LFS_PTR_read_form
{
LPSTR				lpstrForm_Name;  
LPSTR				lpstrField_Names;  
LPSTR				lpstrMedia_Name;  
DWORD				dwMedia_Control;
} LFSPTRREADFORM, *LPLFSPTRREADFORM; 

typedef struct _LFS_PTR_read_form_out
{
LPSTR				lpstrFields; 
LPWSTR				lpwstrUnicode_Fields;
} LFSPTRREADFORMOUT, *LPLFSPTRREADFORMOUT;

typedef struct _LFS_PTR_raw_data
{
WORD				wInput_Data;  
ULONG				ulSize; 
LPBYTE				lpbData;
} LFSPTRRAWDATA, *LPLFSPTRRAWDATA;

typedef struct _LFS_PTR_raw_data_in
{
ULONG				ulSize;
LPBYTE				lpbData;
} LFSPTRRAWDATAIN, *LPLFSPTRRAWDATAIN;

typedef struct _LFS_PTR_media_unit
{
WORD				wBase; 
WORD				wUnit_X; 
WORD				wUnit_Y;
} LFSPTRMEDIAUNIT, *LPLFSPTRMEDIAUNIT;

typedef struct _LFS_PTR_Image_Request
{
WORD				wFront_Image_Type;
WORD				wBack_Image_Type;
WORD				wFront_Image_Color_Format; 
WORD				wBack_Image_Color_Format; 
WORD				wCodeline_Format;
WORD				wImage_Source; 
LPSTR				lpstrFront_Image_File; 
LPSTR				lpstrBack_Image_File;
} LFSPTRIMAGEREQUEST, *LPLFSPTRIMAGEREQUEST;

typedef struct _LFS_PTR_Image
{
WORD				wImage_Source; 
WORD				wStatus; 
ULONG				ulData_Length; 
LPBYTE				lpbData;
} LFSPTRIMAGE, *LPLFSPTRIMAGE;

typedef struct _LFS_PTR_reset
{
DWORD				dwMedia_Control; 
USHORT				usRetract_Bin_Number;
} LFSPTRRESET, *LPLFSPTRRESET;

typedef struct _LFS_PTR_set_guidlight
{	
DWORD				dwGuid_Light;
DWORD				dwCommand;
} LFSPTRSETGUIDLIGHT, *LPLFSPTRSETGUIDLIGHT;

typedef struct _LFS_PTR_print_raw_file
{
LPSTR				lpstrFile_Name;
DWORD				dwMedia_Control;
DWORD				dwPaper_Source;
} LFSPTRPRINTRAWFILE, *LPLFSPTRPRINTRAWFILE;

typedef struct _LFS_PTR_load_definition
{
LPSTR				lpszFile_Name;
BOOL				bOver_write;
} LFSPTRLOADDEFINITION, *LPLFSPTRLOADDEFINITION;

typedef struct _LFS_PTR_supply_replen
{
WORD				fwSupply_Replen;
} LFSPTRSUPPLYREPLEN, *LPLFSPTRSUPPLYREPLEN;

typedef struct _LFS_PTR_power_save_control
{
USHORT				usMax_Power_Save_Recovery_Time;
} LFSPTRPOWERSAVECONTROL, *LPLFSPTRPOWERSAVECONTROL;

/*=================================================================*/
/*事件结构体 */
/*=================================================================*/

typedef struct _LFS_PTR_field_failure
{
LPSTR				lpstrForm_Name; 
LPSTR				lpstrField_Name; 
WORD				wFailure;

} LFSPTRFIELDFAIL, *LPLFSPTRFIELDFAIL;

typedef struct _LFS_PTR_bin_threshold
{
USHORT				usBin_Number; 
WORD				wRetract_Bin;
} LFSPTRBINTHRESHOLD, *LPLFSPTRBINTHRESHOLD;

typedef struct _LFS_PTR_paper_threshold
{
WORD				wPaper_Source;
WORD				wPaper_Threshold;
} LFSPTRPAPERTHRESHOLD, *LPLFSPTRPAPERTHRESHOLD;

typedef struct _LFS_PTR_media_detected
{
WORD				wPosition;
USHORT				usRetract_Bin_Number;
} LFSPTRMEDIADETECTED, *LPLFSPTRMEDIADETECTED;

typedef struct _LFS_PTR_bin_status
{
USHORT				usBin_Number;
WORD				wRetract_Bin;
} LFSPTRBINSTATUS, *LPLFSPTRBINSTATUS;

typedef struct _LFS_PTR_media_presented
{
USHORT				usWad_Index;
WORD				usTotal_Wads;
} LFSPTRMEDIAPRESENTED, *LPLFSPTRMEDIAPRESENTED;

typedef struct _LFS_PTR_definition_loaded
{
LPSTR				lpszDefinition_Name;
DWORD				dwDefinition_Type;
} LFSPTRDEFINITIONLOADED, *LPLFSPTRDEFINITIONLOADED;


typedef struct _LFS_PTR_media_rejected
{
WORD				wMedia_Rejected;
} LFSPTRMEDIAREJECTED, *LPLFSPTRMEDIAREJECTED;

typedef struct _LFS_PTR_media_retracted
{
WORD				wRetract_Result;
USHORT				usBin_Number;
} LFSPTRMEDIARETRACTED, *LPLFSPTRMEDIARETRACTED;

typedef struct _LFS_PTR_device_position
{
WORD				wPosition;
} LFSPTRDEVICEPOSITION, *LPLFSPTRDEVICEPOSITION;

typedef struct _LFS_PTR_power_save_change
{
USHORT				usPower_Save_Recovery_Time;
} LFSPTRPOWERSAVECHANGE, *LPLFSPTRPOWERSAVECHANGE;

typedef struct _LFS_PTR_image_request_ex
{
WORD				wFront_Image_Type; 
WORD				wBack_Image_Type;
WORD				wFront_Image_Color_Format; 
WORD				wBack_Image_Color_Format; 
WORD				wCodeline_Format;
WORD				wImage_Source; 
LPSTR				lpstrFront_Image_File; 
LPSTR				lpstrBack_Image_File;
WORD				wEncrypt_Mode;
LPSTR				lpsKey;
LPSTR				lpszFeature;
LPSTR				lpstrExtra;
} LFSPTRIMAGEREQUESTEX, *LPLFSPTRIMAGEREQUESTEX;

typedef struct _LFS_PTR_ImageEx
{
WORD				wImage_Source; 
WORD				wStatus; 
ULONG				ulData_Length; 
LPBYTE				lpbData;
LPSTR				lpszImage_Data;
WORD				wCode;
} LFSPTRIMAGEEX, *LPLFSPTRIMAGEEX;


typedef struct _LFS_PTR_codeline_mapPTRg_out
{
	WORD				wCodeline_Format;
	LPLFSPTRXDATA		lpxChar_MapPTRg;
} LFSPTRCODELINEMAPPTRGOUT, *LPLFSPTRCODELINEMAPPTRGOUT;

typedef struct _lfs_ptr_import_key
{
LPSTR				lpstrKey;
LPSTR				lpstrEnc_Key;
LPLFSPTRXDATA			lpxValue;
LPLFSPTRXDATA			lpxControl_Vector;
DWORD				dwUse;
WORD				wKey_Check_Mode;
LPLFSPTRXDATA			lpxKey_Check_Value;
LPSTR               lpstrExtra;
} LFSPTRIMPORTKEY, *LPLFSPTRIMPORTKEY;

typedef struct _LFS_PTR_media_ext
{
ULONG				ulSize_X; 
ULONG				ulSize_Y;
} LFSPTRMEDIAEXT, *LPLFSPTRMEDIAEXT;
/*  恢复对齐方式   */
#pragma pack(pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif
#endif    /*__INC_LFSPTR__H */