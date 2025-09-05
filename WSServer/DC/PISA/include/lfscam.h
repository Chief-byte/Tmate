/****************************************************************************** 
*                                                                             * 
* LFScam.h  - Camera (CAM) definitions                                        * 
*                                                                             * 
* Version 1.00                                                                * 
*                                                                             * 
******************************************************************************/ 
 
#ifndef __INC_LFSCAM__H 
#define __INC_LFSCAM__H 
 
#ifdef __cplusplus 
extern "C" { 
#endif 
 
#include    "lfsapi.h" 
 
/*   be aware of alignment   */ 
#pragma pack(push,1) 
 
/* values of LFSCAMCAPS.wClass */ 
 
#define     LFS_SERVICE_CLASS_CAM               (10) 
#define     LFS_SERVICE_NAME_CAM                "CAM" 
#define     LFS_SERVICE_VERSION_CAM	             (0x0001) /* Version 1.00 */ 
 
#define     CAM_SERVICE_OFFSET                   (LFS_SERVICE_CLASS_CAM * 100) 
 
/* CAM Info Commands */ 
 
#define     LFS_INF_CAM_STATUS                  (CAM_SERVICE_OFFSET + 1) 
#define     LFS_INF_CAM_CAPABILITIES            (CAM_SERVICE_OFFSET + 2) 

 
/* CAM Execute Commands */ 
#define     LFS_CMD_CAM_TAKE_PICTURE            (CAM_SERVICE_OFFSET + 1) 
#define     LFS_CMD_CAM_RESET                   (CAM_SERVICE_OFFSET + 2) 
#define     LFS_CMD_CAM_TAKE_PICTURE_EX         (CAM_SERVICE_OFFSET + 3)
#define     LFS_CMD_CAM_DISPLAY                 (CAM_SERVICE_OFFSET + 4) 
#define     LFS_CMD_CAM_FACE_COMPARISON         (CAM_SERVICE_OFFSET + 5)
#define     LFS_CMD_CAM_RECORD                  (CAM_SERVICE_OFFSET + 6)
#define     LFS_CMD_CAM_DISPLAY_HC              (CAM_SERVICE_OFFSET + 7)
#define     LFS_CMD_CAM_IMPORT_KEY              (CAM_SERVICE_OFFSET + 8)
#define     LFS_CMD_CAM_GENERATE_KCV            (CAM_SERVICE_OFFSET + 9)
#define     LFS_CMD_CAM_GET_SIGNATURE           (CAM_SERVICE_OFFSET + 10)
 
/* CAM Messages */ 
 
#define     LFS_USRE_CAM_MEDIATHRESHOLD         (CAM_SERVICE_OFFSET + 1) 
#define     LFS_EXEE_CAM_INVALIDDATA            (CAM_SERVICE_OFFSET + 2) 
#define     LFS_USRE_CAM_STARTSIGNING           (CAM_SERVICE_OFFSET + 3)

 
/* values of LFSCAMSTATUS.fwDevice */ 
#define     LFS_CAM_DEVONLINE                   LFS_STAT_DEVONLINE 
#define     LFS_CAM_DEVOFFLINE                  LFS_STAT_DEVOFFLINE 
#define     LFS_CAM_DEVPOWEROFF                 LFS_STAT_DEVPOWEROFF 
#define     LFS_CAM_DEVNODEVICE                 LFS_STAT_DEVNODEVICE 
#define     LFS_CAM_DEVHWERROR                  LFS_STAT_DEVHWERROR 
#define     LFS_CAM_DEVUSERERROR                LFS_STAT_DEVUSERERROR 
#define     LFS_CAM_DEVBUSY                     LFS_STAT_DEVBUSY 

/* number of cameras supported/length of LFSCAMSTATUS.wCameras field */
#define     LFS_CAM_CAMERAS_SIZE               (8)
#define     LFS_CAM_CAMERAS_MAX                (LFS_CAM_CAMERAS_SIZE - 1) 

/* indices of LFSCAMSTATUS.fwMedia[...]
LFSCAMSTATUS.wCameras [...]
LFSCAMSTATUS.usPictures[...]
LFSCAMCAPS.wCameras [...]
LFSCAMTAKEPICT.wCamera */
#define     LFS_CAM_ROOM                        (0) 
#define     LFS_CAM_PERSON                      (1) 
#define     LFS_CAM_EXITSLOT                    (2) 
#define     LFS_CAM_EXTRA                       (3) 
 
/* values of LFSCAMSTATUS.fwMedia */ 
#define     LFS_CAM_MEDIAOK                     (0) 
#define     LFS_CAM_MEDIAHIGH                   (1) 
#define     LFS_CAM_MEDIAFULL                   (2) 
#define     LFS_CAM_MEDIAUNKNOWN                (3) 
#define     LFS_CAM_MEDIANOTSUPP                (4) 
 
/* values of LFSCAMSTATUS.wCameras */ 
#define     LFS_CAM_CAMNOTSUPP                  (0) 
#define     LFS_CAM_CAMOK                       (1) 
#define     LFS_CAM_CAMINOP                     (2) 
#define     LFS_CAM_CAMUNKNOWN                  (3) 

/* values of LFSCAMCAPS.fwType */
#define     LFS_CAM_TYPE_CAM                    (1)
 
/* values of LFSCAMCAPS.wCameras */
#define     LFS_CAM_NOT_AVAILABLE               (0)  
#define     LFS_CAM_AVAILABLE                   (1)  

/* values of LFSCAMCAPS.wCam_Data */ 
#define     LFS_CAM_NOTADD                      (0) 
#define     LFS_CAM_AUTOADD                     (1)  
#define     LFS_CAM_MANADD                      (2)
 
/* values of LFSCAMCAPS.wChar_Support */
#define     LFS_CAM_ASCII                       (0x0001) 
#define     LFS_CAM_UNICODE                     (0x0002) 
 
/* values of LFSCAMDISP.wAction */ 
#define     LFS_CAM_CREATE                      (0) 
#define     LFS_CAM_DESTROY                     (1) 
#define     LFS_CAM_PAUSE                       (2) 
#define     LFS_CAM_RESUME                      (3) 
#define     LFS_CAM_ERASE                       (4) 
#define     LFS_CAM_PENASERASER                 (5)
#define     LFS_CAM_ERASERASPEN                 (6)  

/* values of LFSCAMDISP.wTextPosition */ 
#define     LFS_CAM_TEXT_POS_DEFAULT          (0)
#define     LFS_CAM_TEXT_POS_LEFT_TOP         (1)
#define     LFS_CAM_TEXT_POS_LEFT_BOTTOM      (2)
#define     LFS_CAM_TEXT_POS_RIGHT_TOP        (3)
#define     LFS_CAM_TEXT_POS_RIGHT_BOTTOM     (4)
#define     LFS_CAM_TEXT_POS_TOP              (5)
#define     LFS_CAM_TEXT_POS_BOTTOM           (6)
#define     LFS_CAM_TEXT_POS_CENTOR           (7)

/* values of LFSCAMDISP.wBkShow*/
#define     LFS_CAM_BK_SHOW_DEFAULT           (0)
#define     LFS_CAM_BK_SHOW_CENTOR            (1)
#define     LFS_CAM_BK_SHOW_STRETCH           (2)

/*values  LFSCAMSIGNDATA.wStatus,
LFSCAMGETSIGNATUREPLAINOUT.wStatus,
LFSCAMGETSIGNATUREENCRYPTOUT.wStatus  */
#define     LFS_CAM_DATAOK                    (1) 
#define     LFS_CAM_DATAMISSING               (2) 
#define     LFS_CAM_DATASRCNOTSUPP            (3) 
#define     LFS_CAM_DATASRCMISSING            (4) 
 
/* CAM Errors */ 
#define     LFS_ERR_CAM_CAMNOTSUPP            (-(CAM_SERVICE_OFFSET + 0)) 
#define     LFS_ERR_CAM_MEDIAFULL             (-(CAM_SERVICE_OFFSET + 1)) 
#define     LFS_ERR_CAM_CAMINOP               (-(CAM_SERVICE_OFFSET + 2)) 
#define     LFS_ERR_CHARSETNOTSUPP            (-(CAM_SERVICE_OFFSET + 3)) 
#define     LFS_ERR_CAM_FILEIOERROR           (-(CAM_SERVICE_OFFSET + 4)) 
#define     LFS_ERR_CAM_KEYNOTFOUND           (-(CAM_SERVICE_OFFSET + 5)) 
#define     LFS_ERR_CAM_ACCESSDENIED          (-(CAM_SERVICE_OFFSET + 6)) 
#define     LFS_ERR_CAM_KEYINVALID            (-(CAM_SERVICE_OFFSET + 7)) 
#define     LFS_ERR_CAM_NOKEYRAM              (-(CAM_SERVICE_OFFSET + 8)) 
#define     LFS_ERR_CAM_INVALIDKEYLENGTH      (-(CAM_SERVICE_OFFSET + 9)) 
#define     LFS_ERR_CAM_INVALID_HWND          (-(CAM_SERVICE_OFFSET + 10))
#define     LFS_ERR_CAM_NOTSIGN_ERROR         (-(CAM_SERVICE_OFFSET + 11))


/* values of LFSCAMTAKEPICTSIZE.wScan_Size */
#define     LFS_CAM_SIZEALL                         (0)
#define     LFS_CAM_SIZEAUTO                        (1)
#define     LFS_CAM_SIZEA4                          (2)
#define     LFS_CAM_SIZEA5                          (3)
#define     LFS_CAM_SIZEA6                          (4)
#define     LFS_CAM_SIZEA7                          (5)
#define     LFS_CAM_SIZECALLINGCARD	                 (6)
#define     LFS_CAM_SIZEID                          (7)
#define     LFS_CAM_SIZECUSTOM                      (8)
#define     LFS_CAM_SIZEAJUSTEDTOWINDOW             (9)
#define     LFS_CAM_SIZEAJUSTEDTOFRAME              (10)
#define     LFS_CAM_SIZEAJUSTEDTOFRAMEANDCHECKFACE  (11)

/* values of LFSCAMIMPORT.wAlgorithm,LFSCAMGETSIGNATUREENCRYPT.wAlgorithm */
#define     LFS_CAM_CRYPTNONE                  (0)
#define     LFS_CAM_CRYPTDESECB                (1)
#define     LFS_CAM_CRYPTDESCBC                (2)
#define     LFS_CAM_CRYPT3DESECB               (3)
#define     LFS_CAM_CRYPT3DESCBC               (4)
#define     LFS_CAM_CRYPTSM2                   (5)
#define     LFS_CAM_CRYPTSM3                   (6)
#define     LFS_CAM_CRYPTSM4ECB                (7)
#define     LFS_CAM_CRYPTSM4CBC                (8)

/* values of LFSCAMIMPORT.wClear */
#define     LFS_CAM_CLEARNONE                  (0)
#define     LFS_CAM_CLEARKEY                   (1)
#define     LFS_CAM_CLEARALL                   (2)

/* values of LFSCAMIMPORT.wKey_Check_Mode */
#define     LFS_CAM_KCVNONE                    (0) 
#define     LFS_CAM_KCVSELF                    (1) 
#define     LFS_CAM_KCVZERO                    (2) 

/*=================================================================*/ 
/* CAM Info Command Structures and variables */ 
/*=================================================================*/ 
typedef struct _LFS_CAM_status 
{ 
    WORD                     wDevice; 
WORD                     wMedia[LFS_CAM_CAMERAS_SIZE];
WORD                     wCameras[LFS_CAM_CAMERAS_SIZE];
USHORT                   usPictures[LFS_CAM_CAMERAS_SIZE];
LPSTR                    lpstrExtra;
} LFSCAMSTATUS, *LPLFSCAMSTATUS; 

typedef struct _LFS_CAM_caps 
{ 
    WORD                     wClass; 
WORD                     wType;
WORD                     wCameras[LFS_CAM_CAMERAS_SIZE];
USHORT                   usMax_Pictures;
WORD                     wCam_Data;
USHORT                   usMax_Data_Length;
WORD                     wChar_Support;
LPSTR                    lpstrExtra;
BOOL                     bPicture_File;
} LFSCAMCAPS, *LPLFSCAMCAPS; 

/*=================================================================*/ 
/* CAM Execute Command Structures */ 
/*=================================================================*/ 
typedef struct _LFS_CAM_take_picture
{
WORD                     wCamera;
LPSTR                    lpstrCam_Data;
LPWSTR                   lpstrUNICODE_Cam_Data;
} LFSCAMTAKEPICT, *LPLFSCAMTAKEPICT;

typedef struct _LFS_hex_cam_data
{
USHORT                  usLength;
LPBYTE                  lpbData;
} LFSXCAMDATA, *LPLFSXCAMDATA;

typedef struct _LFS_CAM_display
{
WORD                     wCamera;
WORD                     wAction;
WORD                     wX;
WORD                     wY;
WORD                     wWidth;
WORD                     wHeight;
DWORD                    hWnd;
WORD                     wHpixel;
WORD                     wVpixel;
LPSTR                    lpstrText_Data;
LPWSTR                   lpstrUNICODE_Text_Data;
WORD                     wFont_Width;
WORD                     wFont_Height;
LPSTR                    lpstrFace;
WORD                     wTextPosition;
LPSTR                    lpstrBackgroundFile;
WORD                     wBkShow;
LPSTR                    lpstrKey;
LPSTR                    lpstrEnc_Key;
LPLFSXCAMDATA            lpxKey_Enc_Key;
WORD                     wAlgorithm;
LPSTR                    lpstrExtra;
}LFSCAMDISP, *LPLFSCAMDISP;

typedef struct _LFS_CAM_take_picture_ex
{
WORD                     wCamera;
LPSTR                    lpstrCam_Data;
LPWSTR                   lpstrUNICODE_Cam_Data;
LPSTR	    lpstrPicture_File;
WORD                     wScan_Size;
LPSTR                    lpstrExtra;
} LFSCAMTAKEPICTEX, *LPLFSCAMTAKEPICTEX;

typedef struct _LFS_CAM_face_comparison 
{
    WORD                     wCamera;
    LPSTR                    lpstrPicture_File_A; 
    LPSTR                    lpstrPicture_File_B; 
	LPSTR					 lpstrExtra;
} LFSCAMFACECOMPARISON, *LPLFSCAMFACECOMPARISON;

typedef struct _LFS_CAM_face_comparison_out
{
      WORD                     wScore;
LPSTR                    lpstrExtra;
} LFSCAMFACECOMPARISONOUT, *LPLFSCAMFACECOMPARISONOUT;

typedef struct _LFS_CAM_display_hc
{
WORD                    wCamera;
WORD                    wAction;
WORD                    wWidth; 
WORD                    wHeight;
WORD                    wX;
WORD                    wY; 
DWORD                   hWnd;
WORD                    wHpixel;
WORD                    wVpixel;
WORD                    wRotate_Angle;        
WORD                    wColor_Type;  
WORD                    wCrop_Type;       
WORD                    wCrop_Size;
LPSTR                   lpstrTex_Data;
LPSTR                    lpstrExtra;
} LFSCAMDISPHC, *LPLFSCAMDISPHC;

typedef struct _LFS_CAM_record
{
WORD                    wCamera;
WORD                    wAction; 
WORD                    wHpixel;
WORD                    wVpixel;
WORD                    wFps;
WORD                    wAudio_Option;
LPSTR                   lpstrRecord_File;
LPSTR                   lpstrExtra;
} LFSCAMRECORD, *LPLFSCAMRECORD;



typedef struct _LFS_CAM_import
{ 
LPSTR                   lpstrKey;
LPSTR                   lpstrEnc_Key;
LPLFSXCAMDATA           lpxValue;
LPLFSXCAMDATA           lpxControl_Vector;
WORD                    wClear;
WORD                    wAlgorithm;
WORD                    wKey_Check_Mode;
LPLFSXCAMDATA           lpxKey_Check_Value;
LPSTR                   lpstrExtra;
} LFSCAMIMPORT, *LPLFSCAMIMPORT;

typedef struct _LFS_CAM_get_signature
{
WORD                     wCamera;     
LPSTR                    lpstrPicture_File;
LPSTR                    lpstrTrack_File; 
LPSTR                    lpstrExtra;
} LFSCAMGETSIGNATURE, *LPLFSCAMGETSIGNATURE;

typedef struct _LFS_CAM_get_signature_out
{
WORD                     wStatus;     
ULONG                    ulData_Length;
LPBYTE                   lpbData; 
LPSTR                    lpstrExtra;
} LFSCAMGETSIGNATUREOUT, *LPLFSCAMGETSIGNATUREOUT;

/*   restore alignment   */ 
#pragma pack(pop) 

#ifdef __cplusplus 
}       /*extern "C"*/ 
#endif 

#endif  /* __INC_LFSCAM__H */ 