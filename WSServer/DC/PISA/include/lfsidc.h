/****************************************************************************** 
*                                                                             * 
* LFSidc.h  - Identification card unit (IDC) definitions                      * 
*                                                                             * 
* Version 1.00                                                                * 
*                                                                             * 
******************************************************************************/ 
 
#ifndef __INC_LFSIDC__H 
#define __INC_LFSIDC__H 
 
#ifdef __cplusplus 
extern "C" { 
#endif 
 
#include    "lfsapi.h" 
 
/*   be aware of alignment   */ 
#pragma pack(push,1) 
 
/* values of LFSIDCCAPS.wClass, LFSIDCMCRCAPS.wClass */ 
 
#define     LFS_SERVICE_CLASS_IDC               (2) 
#define     LFS_SERVICE_CLASS_NAME_IDC          "IDC" 
#define     LFS_SERVICE_CLASS_VERSION_IDC       (0x0001) /* Version 1.0 */ 
 
#define     IDC_SERVICE_OFFSET                  (LFS_SERVICE_CLASS_IDC * 100) 
 
/* IDC Info Commands */ 
 
#define     LFS_INF_IDC_STATUS                  (IDC_SERVICE_OFFSET + 1) 
#define     LFS_INF_IDC_CAPABILITIES            (IDC_SERVICE_OFFSET + 2) 
#define     LFS_INF_IDC_FORM_LIST               (IDC_SERVICE_OFFSET + 3) 
#define     LFS_INF_IDC_QUERY_FORM              (IDC_SERVICE_OFFSET + 4) 
#define     LFS_INF_IDC_QUERY_IFM_IDENTIFIER    (IDC_SERVICE_OFFSET + 5) 
#define 	LFS_INF_IDC_MCR_CAPABILITIES	  	(IDC_SERVICE_OFFSET + 51)
#define	 	LFS_INF_IDC_MCR_STATUS				(IDC_SERVICE_OFFSET + 52)
#define     LFS_INF_IDC_SLOTS_INFO	              (IDC_SERVICE_OFFSET + 53)

/* IDC Execute Commands */ 
#define     LFS_CMD_IDC_READ_TRACK              (IDC_SERVICE_OFFSET + 1) 
#define     LFS_CMD_IDC_WRITE_TRACK             (IDC_SERVICE_OFFSET + 2) 
#define     LFS_CMD_IDC_EJECT_CARD              (IDC_SERVICE_OFFSET + 3) 
#define     LFS_CMD_IDC_RETAIN_CARD             (IDC_SERVICE_OFFSET + 4) 
#define     LFS_CMD_IDC_RESET_COUNT             (IDC_SERVICE_OFFSET + 5) 
#define     LFS_CMD_IDC_SETKEY                  (IDC_SERVICE_OFFSET + 6) 
#define     LFS_CMD_IDC_READ_RAW_DATA           (IDC_SERVICE_OFFSET + 7) 
#define     LFS_CMD_IDC_WRITE_RAW_DATA          (IDC_SERVICE_OFFSET + 8) 
#define     LFS_CMD_IDC_CHIP_IO                 (IDC_SERVICE_OFFSET + 9) 
#define     LFS_CMD_IDC_RESET                   (IDC_SERVICE_OFFSET + 10) 
#define     LFS_CMD_IDC_CHIP_POWER              (IDC_SERVICE_OFFSET + 11) 
#define     LFS_CMD_IDC_PARSE_DATA              (IDC_SERVICE_OFFSET + 12) 
#define     LFS_CMD_IDC_SET_GUIDANCE_LIGHT      (IDC_SERVICE_OFFSET + 13) 
#define     LFS_CMD_IDC_POWER_SAVE_CONTROL      (IDC_SERVICE_OFFSET + 14) 
#define     LFS_CMD_IDC_RETRACT_CARD	            (IDC_SERVICE_OFFSET + 91)
#define     LFS_CMD_IDC_HANDBACK_CARD           (IDC_SERVICE_OFFSET + 92)
#define     LFS_CMD_IDC_CLEAR_RETRACT_CARD      (IDC_SERVICE_OFFSET + 93)
#define		LFS_CMD_IDC_RETAIN_SLOT_START 		(IDC_SERVICE_OFFSET + 51)
#define 	LFS_CMD_IDC_RETAIN_SLOT_END 		(IDC_SERVICE_OFFSET + 52)
#define 	LFS_CMD_IDC_EJECT_SLOT_START 		(IDC_SERVICE_OFFSET + 53)
#define 	LFS_CMD_IDC_EJECT_SLOT_END 			(IDC_SERVICE_OFFSET + 54)
#define 	LFS_CMD_IDC_MCR_RESET 				(IDC_SERVICE_OFFSET + 58)
#define 	LFS_CMD_IDC_RETAIN_SLOT_START_EX 	(IDC_SERVICE_OFFSET + 96)
#define 	LFS_CMD_IDC_MCR_RETAIN_CARD			(IDC_SERVICE_OFFSET + 97)
#define 	LFS_CMD_IDC_OPEN_SHUTTER			(IDC_SERVICE_OFFSET + 98)
#define     LFS_CMD_IDC_CLOSE_SHUTTER           (IDC_SERVICE_OFFSET + 99)

/* IDC Messages */ 

#define     LFS_EXEE_IDC_INVALIDTRACKDATA       (IDC_SERVICE_OFFSET + 1) 
#define     LFS_EXEE_IDC_MEDIAINSERTED          (IDC_SERVICE_OFFSET + 3) 
#define     LFS_SRVE_IDC_MEDIAREMOVED           (IDC_SERVICE_OFFSET + 4) 
#define     LFS_SRVE_IDC_CARDACTION             (IDC_SERVICE_OFFSET + 5) 
#define     LFS_USRE_IDC_RETAINBINTHRESHOLD     (IDC_SERVICE_OFFSET + 6) 
#define     LFS_EXEE_IDC_INVALIDMEDIA           (IDC_SERVICE_OFFSET + 7) 
#define     LFS_EXEE_IDC_MEDIARETAINED          (IDC_SERVICE_OFFSET + 8) 
#define     LFS_SRVE_IDC_MEDIADETECTED          (IDC_SERVICE_OFFSET + 9) 
#define     LFS_SRVE_IDC_RETAINBININSERTED      (IDC_SERVICE_OFFSET + 10) 
#define     LFS_SRVE_IDC_RETAINBINREMOVED       (IDC_SERVICE_OFFSET + 11) 
#define     LFS_EXEE_IDC_INSERTCARD             (IDC_SERVICE_OFFSET + 12) 
#define     LFS_SRVE_IDC_DEVICEPOSITION         (IDC_SERVICE_OFFSET + 13) 
#define     LFS_SRVE_IDC_POWER_SAVE_CHANGE      (IDC_SERVICE_OFFSET + 14) 

/* values of LFSIDCSTATUS.wDevice,LFSIDCMCRSTATUS.wDevice */ 
 
#define     LFS_IDC_DEVONLINE                   LFS_STAT_DEVONLINE 
#define     LFS_IDC_DEVOFFLINE                  LFS_STAT_DEVOFFLINE 
#define     LFS_IDC_DEVPOWEROFF                 LFS_STAT_DEVPOWEROFF 
#define     LFS_IDC_DEVNODEVICE                 LFS_STAT_DEVNODEVICE 
#define     LFS_IDC_DEVHWERROR                  LFS_STAT_DEVHWERROR 
#define     LFS_IDC_DEVUSERERROR                LFS_STAT_DEVUSERERROR 
#define     LFS_IDC_DEVBUSY                     LFS_STAT_DEVBUSY 
#define     LFS_IDC_DEVFRAUDATTEMPT             LFS_STAT_DEVFRAUDATTEMPT 
 
/* values of LFSIDCSTATUS.wMedia, LFSIDCRETAINCARD.wPosition,  */ 
/* LFSIDCCARDACT.wPosition  */ 
 
#define     LFS_IDC_MEDIAPRESENT                (1) 
#define     LFS_IDC_MEDIANOTPRESENT             (2) 
#define     LFS_IDC_MEDIAJAMMED                 (3) 
#define     LFS_IDC_MEDIANOTSUPP                (4) 
#define     LFS_IDC_MEDIAUNKNOWN                (5) 
#define     LFS_IDC_MEDIAENTERING               (6) 
#define     LFS_IDC_MEDIALATCHED                (7) 
 
/* values of LFSIDCSTATUS.wRetainBin */ 
 
#define     LFS_IDC_RETAINBINOK                 (1) 
#define     LFS_IDC_RETAINNOTSUPP               (2) 
#define     LFS_IDC_RETAINBINFULL               (3) 
#define     LFS_IDC_RETAINBINHIGH               (4) 
#define     LFS_IDC_RETAINBINMISSING            (5) 
 
/* values of LFSIDCSTATUS.wSecurity */ 
 
#define     LFS_IDC_SECNOTSUPP                  (1) 
#define     LFS_IDC_SECNOTREADY                 (2) 
#define     LFS_IDC_SECOPEN                     (3) 
 
/* values of LFSIDCSTATUS.wChipPower */ 
 
#define     LFS_IDC_CHIPONLINE                  (0) 
#define     LFS_IDC_CHIPPOWEREDOFF              (1) 
#define     LFS_IDC_CHIPBUSY                    (2) 
#define     LFS_IDC_CHIPNODEVICE                (3) 
#define     LFS_IDC_CHIPHWERROR                 (4) 
#define     LFS_IDC_CHIPNOCARD                  (5) 
#define     LFS_IDC_CHIPNOTSUPP                 (6) 
#define     LFS_IDC_CHIPUNKNOWN                 (7) 
 
/* Size and max index of dwGuidLights array */ 
#define     LFS_IDC_GUIDLIGHTS_SIZE             (32) 
#define     LFS_IDC_GUIDLIGHTS_MAX              (LFS_IDC_GUIDLIGHTS_SIZE - 1) 
 
/* Indices of LFSIDCSTATUS.dwGuidLights [...] 
              LFSIDCCAPS.dwGuidLights [...] 
*/ 
#define     LFS_IDC_GUIDANCE_CARDUNIT           (0) 
 
/* Values of LFSIDCSTATUS.dwGuidLights [...] 
             LFSIDCCAPS.dwGuidLights [...] 
*/ 
#define     LFS_IDC_GUIDANCE_NOT_AVAILABLE      (0x00000000) 
#define     LFS_IDC_GUIDANCE_OFF                (0x00000001) 
#define     LFS_IDC_GUIDANCE_ON                 (0x00000002) 
#define     LFS_IDC_GUIDANCE_SLOW_FLASH         (0x00000004) 
#define     LFS_IDC_GUIDANCE_MEDIUM_FLASH       (0x00000008) 
#define     LFS_IDC_GUIDANCE_QUICK_FLASH        (0x00000010) 
#define     LFS_IDC_GUIDANCE_CONTINUOUS         (0x00000080) 
#define     LFS_IDC_GUIDANCE_RED                (0x00000100) 
#define     LFS_IDC_GUIDANCE_GREEN              (0x00000200) 
#define     LFS_IDC_GUIDANCE_YELLOW             (0x00000400) 
#define     LFS_IDC_GUIDANCE_BLUE               (0x00000800) 
#define     LFS_IDC_GUIDANCE_CYAN               (0x00001000) 
#define     LFS_IDC_GUIDANCE_MAGENTA            (0x00002000) 
#define     LFS_IDC_GUIDANCE_WHITE              (0x00004000) 
 
/* values of LFSIDCSTATUS.wChipModule */ 
 
#define     LFS_IDC_CHIPMODOK                   (1) 
#define     LFS_IDC_CHIPMODINOP                 (2) 
#define     LFS_IDC_CHIPMODUNKNOWN              (3) 
#define     LFS_IDC_CHIPMODNOTSUPP              (4) 
 
/* values of LFSIDCSTATUS.wMagReadModule and 
             LFSIDCSTATUS.wMagWriteModule  */ 
 
#define     LFS_IDC_MAGMODOK                    (1) 
#define     LFS_IDC_MAGMODINOP                  (2) 
#define     LFS_IDC_MAGMODUNKNOWN               (3) 
#define     LFS_IDC_MAGMODNOTSUPP               (4) 
 
/* values of LFSIDCSTATUS.wFrontImageModule and 
             LFSIDCSTATUS.wBackImageModule */ 
 
#define     LFS_IDC_IMGMODOK                    (1) 
#define     LFS_IDC_IMGMODINOP                  (2) 
#define     LFS_IDC_IMGMODUNKNOWN               (3) 
#define     LFS_IDC_IMGMODNOTSUPP               (4) 
 
/* values of LFSIDCSTATUS.wDevicePosition 
             LFSIDCDEVICEPOSITION.wPosition */ 
 
#define     LFS_IDC_DEVICEINPOSITION            (0) 
#define     LFS_IDC_DEVICENOTINPOSITION         (1) 
#define     LFS_IDC_DEVICEPOSUNKNOWN            (2) 
#define     LFS_IDC_DEVICEPOSNOTSUPP            (3) 
 
/* values of LFSIDCCAPS.wType */ 
 
#define     LFS_IDC_TYPEMOTOR                   (1) 
#define     LFS_IDC_TYPESWIPE                   (2) 
#define     LFS_IDC_TYPEDIP                     (3) 
#define     LFS_IDC_TYPECONTACTLESS             (4) 
#define     LFS_IDC_TYPELATCHEDDIP              (5) 
#define     LFS_IDC_TYPEPERMANENT               (6) 
 
/* values of LFSIDCCAPS.wReadTracks, 
             LFSIDCCAPS.wWriteTracks, 
             LFSIDCCARDDATA.wDataSource, 
             LFSIDCCAPS.wChipProtocols, 
             LFSIDCCAPS.wWriteMode, 
             LFSIDCCAPS.wChipPower */ 
 
#define     LFS_IDC_NOTSUPP                     0x0000 
 
/* values of LFSIDCCAPS.wReadTracks, LFSIDCCAPS.wWriteTracks, 
             LFSIDCCARDDATA.wDataSource, 
             LFS_CMD_IDC_READ_RAW_DATA */ 
 
#define     LFS_IDC_TRACK1                      0x0001 
#define     LFS_IDC_TRACK2                      0x0002 
#define     LFS_IDC_TRACK3                      0x0004 
#define     LFS_IDC_FRONT_TRACK_1               0x0080 
 
/* further values of LFSIDCCARDDATA.wDataSource (except 
   LFS_IDC_FLUXINACTIVE), LFS_CMD_IDC_READ_RAW_DATA */ 
 
#define     LFS_IDC_CHIP                        0x0008 
#define     LFS_IDC_SECURITY                    0x0010 
#define     LFS_IDC_FLUXINACTIVE                0x0020 
#define     LFS_IDC_TRACK_WM                    0x8000 
#define     LFS_IDC_MEMORY_CHIP                 0x0040 
#define     LFS_IDC_FRONTIMAGE                  0x0100 
#define     LFS_IDC_BACKIMAGE                   0x0200 

/* values of LFSIDCCAPS.wChipProtocols */ 

#define     LFS_IDC_CHIPT0                      0x0001 
#define     LFS_IDC_CHIPT1                      0x0002 
#define     LFS_IDC_CHIP_PROTOCOL_NOT_REQUIRED  0x0004 

/* values of LFSIDCCAPS.wSecType */ 

#define     LFS_IDC_SECNOTSUPP                  (1) 
#define     LFS_IDC_SECMMBOX                    (2) 
#define     LFS_IDC_SECCIM86                    (3) 

/* values of LFSIDCCAPS.wEjectModuleEmptyType*/

#define	    LFS_EM_EMPTYSTORAGE     (1)
#define	    LFS_EM_EMPTYCAPTUREBIN  (2)
#define	    LFS_EM_EMPTYALL         (3)


/* values of LFSIDCCAPS.wPowerOnOption, LFSIDCCAPS.wPowerOffOption*/ 

#define     LFS_IDC_NOACTION                    (1) 
#define     LFS_IDC_EJECT                       (2) 
#define     LFS_IDC_RETAIN                      (3) 
#define     LFS_IDC_EJECTTHENRETAIN             (4) 
#define     LFS_IDC_READPOSITION                (5) 

/* values of LFSIDCCAPS.wWriteMode; LFSIDCWRITETRACK.wWriteMethod, 
LFSIDCCARDDATA.wWriteMethod */ 

/* Note: LFS_IDC_UNKNOWN was removed as it was an invalid value */ 
#define     LFS_IDC_LOCO                        0x0002 
#define     LFS_IDC_HICO                        0x0004 
#define     LFS_IDC_AUTO                        0x0008 

/* values of LFSIDCCAPS.wChipPower */ 

#define     LFS_IDC_CHIPPOWERCOLD               0x0002 
#define     LFS_IDC_CHIPPOWERWARM               0x0004 
#define     LFS_IDC_CHIPPOWEROFF                0x0008 

#define     LFS_IDC_SAM1	                        0x8000
#define     LFS_IDC_SAM2	                        0x4000
#define     LFS_IDC_SAM3	                        0x2000
#define     LFS_IDC_SAM4	                        0x1000
#define     LFS_IDC_SAM5	                        0x0800
#define     LFS_IDC_SAM6	                        0x0400
#define     LFS_IDC_SAM7	                        0x0200
#define     LFS_IDC_SAM8	                        0x0100

/* values of LFSIDCCAPS.wDIPMode */ 

#define     LFS_IDC_DIP_UNKNOWN                 0x0001 
#define     LFS_IDC_DIP_EXIT                    0x0002 
#define     LFS_IDC_DIP_ENTRY                   0x0004 
#define     LFS_IDC_DIP_ENTRY_EXIT              0x0008 

/* values of LFSIDCCAPS. lpwMemoryChipProtocols */ 

#define     LFS_IDC_MEM_SIEMENS4442             0x0001 
#define     LFS_IDC_MEM_GPM896                  0x0002
#define     LFS_IDC_MEM_1608                    0x0004
#define     LFS_IDC_MEM_102                     0x0008 

/* values of LFSIDCFORM.wAction */ 

#define     LFS_IDC_ACTIONREAD                  0x0001 
#define     LFS_IDC_ACTIONWRITE                 0x0002 

/* values of LFSIDCTRACKEVENT.wStatus, LFSIDCCARDDATA.wStatus */ 

#define     LFS_IDC_DATAOK                      (0) 
#define     LFS_IDC_DATAMISSING                 (1) 
#define     LFS_IDC_DATAINVALID                 (2) 
#define     LFS_IDC_DATATOOLONG                 (3) 
#define     LFS_IDC_DATATOOSHORT                (4) 
#define     LFS_IDC_DATASRCNOTSUPP              (5) 
#define     LFS_IDC_DATASRCMISSING              (6) 

/* values LFSIDCCARDACT.wAction */ 
#define     LFS_IDC_CARDRETAINED                (1) 
#define     LFS_IDC_CARDEJECTED                 (2) 
#define     LFS_IDC_CARDREADPOSITION            (3) 
#define     LFS_IDC_CARDJAMMED                  (4) 

/* values of LFSIDCCARDDATA.lpbData if security is read */ 

#define     LFS_IDC_SEC_READLEVEL1              '1' 
#define     LFS_IDC_SEC_READLEVEL2              '2' 
#define     LFS_IDC_SEC_READLEVEL3              '3' 
#define     LFS_IDC_SEC_READLEVEL4              '4' 
#define     LFS_IDC_SEC_READLEVEL5              '5' 
#define     LFS_IDC_SEC_BADREADLEVEL            '6' 
#define     LFS_IDC_SEC_NODATA                  '7' 
#define     LFS_IDC_SEC_DATAINVAL               '8' 
#define     LFS_IDC_SEC_HWERROR                 '9' 
#define     LFS_IDC_SEC_NOINIT                  'A' 

/* values of LFSIDCIFMIDENTIFIER.wIFMAuthority */ 

#define     LFS_IDC_IFMEMV                      (1) 
#define     LFS_IDC_IFMEUROPAY                  (2) 
#define     LFS_IDC_IFMVISA                     (3) 
#define     LFS_IDC_IFMGIECB                    (4) 

/* values LFSIDCCAPS.wEjectPosition, LFSIDCEJECTCARD.wEjectPosition */ 

#define     LFS_IDC_EXITPOSITION                (0x0001) 
#define     LFS_IDC_TRANSPORTPOSITION           (0x0002) 

/* values if LPLFSIDCCLEARRETRACTCARD.wNum */
#define LFS_IDC_CLEARALL                        (0)
#define LFS_IDC_CLEARONE                        (1) 

/* value of LFSIDCMCRCAPS.wType */
#define	LFS_IDC_TYPE							(10)

/* values of LFSIDCMCRSTATUS.wSlots */
#define	LFS_IDC_SLOTESMPTY						(0)
#define	LFS_IDC_SLOTSOK							(1)
#define	LFS_IDC_SLOTSFULL						(2)

/*values of LFSIDCSLOTUNITINFO.wStatus */
#define	LFS_IDC_SLOTUNIT_NOTPRESENT				(0)
#define	LFS_IDC_SLOTUNIT_PRESENT				(1)

/* values of LFSIDCEJECTSLOTOUT.wType */
#define LFS_IDC_TYPE_SLOTID						(0)
#define LFS_IDC_TYPE_CARDDATA	                   (1)
/* IDC Errors */ 

#define LFS_ERR_IDC_MEDIAJAM                    (-(IDC_SERVICE_OFFSET + 0)) 
#define LFS_ERR_IDC_NOMEDIA                     (-(IDC_SERVICE_OFFSET + 1)) 
#define LFS_ERR_IDC_MEDIARETAINED               (-(IDC_SERVICE_OFFSET + 2)) 
#define LFS_ERR_IDC_RETAINBINFULL               (-(IDC_SERVICE_OFFSET + 3)) 
#define LFS_ERR_IDC_INVALIDDATA                 (-(IDC_SERVICE_OFFSET + 4)) 
#define LFS_ERR_IDC_INVALIDMEDIA                (-(IDC_SERVICE_OFFSET + 5)) 
#define LFS_ERR_IDC_FORMNOTFOUND                (-(IDC_SERVICE_OFFSET + 6)) 
#define LFS_ERR_IDC_FORMINVALID                 (-(IDC_SERVICE_OFFSET + 7)) 
#define LFS_ERR_IDC_DATASYNTAX                  (-(IDC_SERVICE_OFFSET + 8)) 
#define LFS_ERR_IDC_SHUTTERFAIL                 (-(IDC_SERVICE_OFFSET + 9)) 
#define LFS_ERR_IDC_SECURITYFAIL                (-(IDC_SERVICE_OFFSET + 10)) 
#define LFS_ERR_IDC_PROTOCOLNOTSUPP             (-(IDC_SERVICE_OFFSET + 11)) 
#define LFS_ERR_IDC_ATRNOTOBTAINED              (-(IDC_SERVICE_OFFSET + 12)) 
#define LFS_ERR_IDC_INVALIDKEY                  (-(IDC_SERVICE_OFFSET + 13)) 
#define LFS_ERR_IDC_WRITE_METHOD                (-(IDC_SERVICE_OFFSET + 14)) 
#define LFS_ERR_IDC_CHIPPOWERNOTSUPP            (-(IDC_SERVICE_OFFSET + 15)) 
#define LFS_ERR_IDC_CARDTOOSHORT                (-(IDC_SERVICE_OFFSET + 16)) 
#define LFS_ERR_IDC_CARDTOOLONG                 (-(IDC_SERVICE_OFFSET + 17)) 
#define LFS_ERR_IDC_INVALID_PORT                (-(IDC_SERVICE_OFFSET + 18)) 
#define LFS_ERR_IDC_POWERSAVETOOSHORT           (-(IDC_SERVICE_OFFSET + 19)) 
#define LFS_ERR_IDC_POWERSAVEMEDIAPRESENT       (-(IDC_SERVICE_OFFSET + 20)) 
#define LFS_ERR_IDC_CARDPRESENT                 (-(IDC_SERVICE_OFFSET + 21))
#define LFS_ERR_IDC_POSITIONINVALID             (-(IDC_SERVICE_OFFSET + 22)) 
#define LFS_ERR_IDC_NORETRACTBIN	                (-(IDC_SERVICE_OFFSET + 21))
#define LFS_ERR_IDC_RETRACTBINFULL              (-(IDC_SERVICE_OFFSET + 22))
#define LFS_ERR_IDC_CARD_NOTFOUND               (-(IDC_SERVICE_OFFSET + 23))
#define LFS_ERR_IDC_MEDIAEXIST					(-(IDC_SERVICE_OFFSET + 52))
#define LFS_ERR_IDC_MEDIARETRACTJAM				(-(IDC_SERVICE_OFFSET + 53))
#define LFS_ERR_IDC_SLOTFULL					(-(IDC_SERVICE_OFFSET + 54))
#define LFS_ERR_IDC_SLOTNOTEXIST				(-(IDC_SERVICE_OFFSET + 55))
#define LFS_ERR_IDC_SHUTTERBLOCKED				(-(IDC_SERVICE_OFFSET + 56)) 
#define LFS_ERR_IDC_SHUTTERCLOSEFAILED			(-(IDC_SERVICE_OFFSET + 57)) 
#define LFS_ERR_IDC_SHUTTEROPENFAILED			(-(IDC_SERVICE_OFFSET + 58)) 
#define LFS_ERR_IDC_CODENOTMATCH				(-(IDC_SERVICE_OFFSET + 59))
#define 	LFS_ERR_IDC_CAPTUREIMPURITY             (-(IDC_SERVICE_OFFSET + 60))

/*=================================================================*/ 
/* IDC Info Command Structures and variables */ 
/*=================================================================*/ 
typedef struct _LFS_IDC_status 
{ 
    WORD                     wDevice; 
    WORD                     wMedia; 
    WORD                     wRetain_Bin; 
    WORD                     wSecurity; 
    USHORT                   usCards; 
    WORD                     wChip_Power; 
    LPSTR                    lpstrExtra; 
    DWORD                    dwGuid_Lights[LFS_IDC_GUIDLIGHTS_SIZE]; 
    WORD                     wChip_Module; 
    WORD                     wMag_Read_Module;
WORD                     wMag_Write_Module; 
    WORD                     wFront_Image_Module; 
    WORD                     wBack_Image_Module; 
    WORD                     wDevice_Position; 
    USHORT                   usPower_Save_Recovery_Time; 
} LFSIDCSTATUS, *LPLFSIDCSTATUS; 

typedef struct _LFS_IDC_caps 
{ 
    WORD                     wClass; 
    WORD                     wType; 
    BOOL                     bCompound; 
    WORD                     wRead_Tracks; 
    WORD                     wWrite_Tracks; 
    WORD                     wChip_Protocols; 
    USHORT                   usCards; 
    WORD                     wSec_Type; 
    WORD                     wPower_On_Option; 
    WORD                     wPower_Off_Option; 
    BOOL                     bFlux_Sensor_Programmable; 
    BOOL                     bRead_Write_Access_Following_Eject; 
    WORD                     wWrite_Mode; 
    WORD                     wChip_Power; 
    LPSTR                    lpstrExtra; 
    WORD                     wDIP_Mode; 
    LPWORD                   lpwMemory_Chip_Protocols; 
    DWORD                    dwGuid_Lights[LFS_IDC_GUIDLIGHTS_SIZE]; 
    WORD                     wEject_Position; 
    BOOL                     bPower_Save_Control; 
} LFSIDCCAPS, *LPLFSIDCCAPS; 

typedef struct _LFS_IDC_form
	{
		LPSTR	lpszForm_Name;
CHAR	cField_Separator_Track1; 
CHAR	cField_Separator_Track2; 
CHAR	cField_Separator_Track3; 
WORD	wAction;
LPSTR	lpszTracks; 
BOOL	bSecure;
LPSTR	lpszTrack1_Fields; 
LPSTR	lpszTrack2_Fields; 
LPSTR	lpszTrack3_Fields;
} LFSIDCFORM, *LPLFSIDCFORM;

typedef struct _LFS_IDC_ifm_identifier
	{
		 WORD                wIFM_Authority;
		 LPSTR               lpszIFM_Identifier;
	} LFSLFSIFMIDENTIFIER, *LPLFSIDCIFMIDENTIFIER;

/*=================================================================*/ 
/* IDC Execute Command Structures */ 
/*=================================================================*/ 
typedef struct _LFS_IDC_write_track 
{ 
    LPSTR	lpstrForm_Name;
    LPSTR	 lpstrTrack_Data; 
WORD	wWrite_Method; 
} LFSIDCWRITETRACK, *LPLFSIDCWRITETRACK;

typedef struct _LFS_IDC_retain_card 
{ 
    USHORT                   usCount; 
    WORD                     wPosition; 
} LFSIDCRETAINCARD, *LPLFSIDCRETAINCARD; 

typedef struct _LFS_IDC_setkey 
{ 
USHORT                   usKey_Len; 
    LPBYTE                   lpbKey_Value; 
} LFSIDCSETKEY, *LPLFSIDCSETKEY; 

typedef struct _LFS_IDC_card_data 
{ 
    WORD                     wData_Source; 
    WORD                     wStatus; 
    ULONG                    ulData_Length; 
    LPBYTE                   lpbData; 
    WORD                     wWrite_Method; 
} LFSIDCCARDDATA, *LPLFSIDCCARDDATA; 

typedef struct _LFS_IDC_chip_io 
{ 
    WORD                     wChip_Protocol; 
    ULONG                    ulChip_Data_Length; 
    LPBYTE                   lpbChip_Data; 
} LFSIDCCHIPIO, *LPLFSIDCCHIPIO; 

typedef struct _LFS_IDC_chip_power_out 
{ 
    ULONG                    ulChip_Data_Length; 
    LPBYTE                   lpbChip_Data; 
} LFSIDCCHIPPOWEROUT, *LPLFSIDCCHIPPOWEROUT; 

typedef struct _LFS_IDC_parse_data 
{ 
LPSTR                    lpstrForm_Name; 
LPLFSIDCCARDDATA        *lppCard_Data; 
} LFSIDCPARSEDATA, *LPLFSIDCPARSEDATA;
    
typedef struct _LFS_IDC_set_guidlight 
{ 
WORD                     wGuid_Light; 
DWORD                    dwCommand; 
} LFSIDCSETGUIDLIGHT, *LPLFSIDCSETGUIDLIGHT; 

typedef struct _LFS_IDC_eject_card 
{ 
    WORD                     wEject_Position;  
} LFSIDCEJECTCARD, *LPLFSIDCEJECTCARD; 

typedef struct _LFS_IDC_power_save_control 
{ 
USHORT                   usMax_Power_Save_Recovery_Time; 
} LFSIDCPOWERSAVECONTROL, *LPLFSIDCPOWERSAVECONTROL; 

/*=================================================================*/ 
/* IDC Message Structures */ 
/*=================================================================*/ 

typedef struct _LFS_IDC_track_event 
{ 
    WORD                     wStatus; 
    LPSTR                    lpstrTrack; 
    LPSTR                    lpstrData; 
} LFSIDCTRACKEVENT, *LPLFSIDCTRACKEVENT; 

typedef struct _LFS_IDC_card_act 
{ 
    WORD                     wAction; 
    WORD                     wPosition; 
} LFSIDCCARDACT, *LPLFSIDCCARDACT; 

typedef struct _LFS_IDC_device_position 
{ 
    WORD                     wPosition; 
} LFSIDCDEVICEPOSITION, *LPLFSIDCDEVICEPOSITION; 

typedef struct _LFS_IDC_power_save_change 
{ 
    USHORT                   usPower_Save_Recovery_Time; 
} LFSIDCPOWERSAVECHANGE, *LPLFSIDCPOWERSAVECHANGE; 

typedef struct _LFS_IDC_retract_card
{
LPSTR                 lpszCard_No;
LPSTR                 lpszRetract_Time;
} LFSIDCRETRACTCARD, * LPLFSIDCRETRACTCARD;

typedef struct _LFS_IDC_handback_card
{
LPSTR                 lpszCard_No;
} LFSIDCHANDBACKCARD, * LPLFSIDCHANDBACKCARD;

typedef struct _LFS_IDC_clear_retract_card
{
    WORD                  wNum;
} LFSIDCCLEARRETRACTCARD, * LPLFSIDCCLEARRETRACTCARD;
    
typedef struct _LFS_IDC_MCR_status
{
	WORD             wDevice;
	WORD             wSlots;
	WORD             wRetain_Bin;
	USHORT           usUse_Slots;
	WORD			 wShutter;
	LPSTR            lpstrExtra;
} LFSIDCMCRSTATUS, * LPLFSIDCMCRSTATUS;

typedef struct _LFS_IDC_MCR_caps
{
	WORD             wClass;
	WORD             wType;
	USHORT           usBig_Slots;
	USHORT           usNormal_Slots;
	LPSTR            lpstrExtra;
} LFSIDCMCRCAPS, * LPLFSIDCMCRCAPS;

typedef struct _LFS_IDC_slotsunitinfo
{
	USHORT		    usNumber;
	WORD		    wStatus;
	USHORT	     	usIsRetained;
	LPSTR		    lpszCard_Info;
	LPSTR		    lpszReatin_Card_Info;
	LPSTR		    lpszRestore_Time;
	LPSTR		    lpszRetain_Time;
	LPSTR		    lpszPosition;
	USHORT		    usSlotSize;
} LFSIDCSLOTUNITINFO, *LPLFSIDCSLOTUNITINFO;

typedef struct _LFS_IDC_slots_info
{
	USHORT                 usCount;
	LPLFSIDCSLOTUNITINFO  *lppList;
} LFSIDCSLOTSINFO, *LPLFSIDCSLOTSINFO;

typedef struct _LFS_IDC_retainslot_strart_in
{
	LPSTR             lpszData;
} LFSIDCRETAINSLOTSTARTIN, *LPLFSIDCRETAINSLOTSTARTIN;

typedef struct _LFS_IDC_retainslot_strart_out
{
	LPSTR            lpszData;
} LFSIDCRETAINSLOTSTARTOUT, *LPLFSIDCRETAINSLOTSTARTOUT;


typedef struct _LFS_IDC_retainslot
{
	LPSTR             lpszCard_Info;
	LPSTR             lpszRetain_Time;
} LFSIDCRETAINSLOT, *LPLFSIDCRETAINSLOT;

typedef struct _LFS_IDC_ejectslot
{
	WORD	             wType;
	LPSTR         	lpCmd_Data;
} LFSIDCEJECTSLOT, *LPLFSIDCEJECTSLOT;

typedef struct _LFS_IDC_ejectslotout
{ 
	WORD	             wType;
	LPSTR    	    lpCmd_Data;
} LFSIDCEJECTSLOTOUT, *LPLFSIDCEJECTSLOTOUT; 

typedef struct _LFS_IDC_retainslot_out
{
	LPSTR            lpszCard_Info;
	LPSTR            lpszRetain_Time;
	LPSTR            lpszPosition;
	WORD             wStatus;
} LFSIDCRETAINSLOTOUT, *LPLFSIDCRETAINSLOTOUT;
    
/*   restore alignment   */ 
#pragma pack(pop) 

#ifdef __cplusplus 
}       /*extern "C"*/ 
#endif 

#endif  /* __INC_LFSIDC__H */ 