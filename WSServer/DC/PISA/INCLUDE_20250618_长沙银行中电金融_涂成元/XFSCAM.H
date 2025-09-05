/******************************************************************************
*                                                                             *
* xfscam.h      XFS - Camera (CAM) definitions                                *
*                                                                             *
*               Version 3.10 (29/11/2007)                                     *
*                                                                             *
******************************************************************************/
 
#ifndef __INC_XFSCAM__H
#define __INC_XFSCAM__H

#ifdef __cplusplus
extern "C" {
#endif
#include "XFSAPI.H"
/* be aware of alignment */
#pragma pack (push, 1)


/* values of WFSCAMCAPS.wClass */
#ifdef QT_LINUX_ARM_PISA

#define     WFS_SERVICE_NAME_CAM                "CAM" 
#define     WFS_SERVICE_VERSION_CAM	             (0x0001) /* Version 1.00 */ 
#define WFS_SERVICE_CLASS_CAM                   (10)
#else
#ifdef QT_WIN_LINUX_XFS

#define WFS_SERVICE_CLASS_CAM                   (10)
#define WFS_SERVICE_VERSION_CAM                 (0x1403) /* Version 3.20 */
#else
    
#define WFS_SERVICE_CLASS_CAM               	(10)
#define WFS_SERVICE_VERSION_CAM       			0x0001
#endif
#endif

#define WFS_SERVICE_NAME_CAM                    "CAM"
#define CAM_SERVICE_OFFSET                      (WFS_SERVICE_CLASS_CAM * 100)

/* CAM Info Commands */

#define     WFS_INF_CAM_STATUS                  (CAM_SERVICE_OFFSET + 1)
#define     WFS_INF_CAM_CAPABILITIES            (CAM_SERVICE_OFFSET + 2)

/* CAM Execute Commands */

#define     WFS_CMD_CAM_TAKE_PICTURE            (CAM_SERVICE_OFFSET + 1)
#define     WFS_CMD_CAM_RESET                   (CAM_SERVICE_OFFSET + 2)
#ifdef QT_LINUX_ARM_PISA
    #define     WFS_CMD_CAM_TAKE_PICTURE_EX         (CAM_SERVICE_OFFSET + 3)
    #if defined (QT_LINUX_ARM_UOS)
        #define     WFS_CMD_CAM_DISPLAY                 (CAM_SERVICE_OFFSET + 99)
        #define     WFS_CMD_CAM_RECORD                  (CAM_SERVICE_OFFSET + 98)
        #define     WFS_CMD_CAM_GET_SIGNATURE           (CAM_SERVICE_OFFSET + 97)
        #define     WFS_CMD_CAM_IMPORT_KEY              (CAM_SERVICE_OFFSET + 96)
        #define     WFS_CMD_CAM_TAKE_PICTURE_SIZE       (CAM_SERVICE_OFFSET + 95)
        #define     WFS_CMD_CAM_SIGNATURE_MINGW         (CAM_SERVICE_OFFSET + 94)
        #define     WFS_CMD_CAM_DISPLAY_TABLE           (CAM_SERVICE_OFFSET + 93)
        #define     WFS_CMD_CAM_DISPLAY_HC              (CAM_SERVICE_OFFSET + 91)
        #define     WFS_CMD_CAM_SIGNATURE_MIW           (CAM_SERVICE_OFFSET + 90)
        #define     WFS_CMD_CAM_TAKE_PICTURE_SCORE      (CAM_SERVICE_OFFSET + 89)
        #define     WFS_CMD_CAM_FACE_COMPARISON         (CAM_SERVICE_OFFSET + 88)
    #else
        #define     WFS_CMD_CAM_DISPLAY                 (CAM_SERVICE_OFFSET + 4)
        #define     WFS_CMD_CAM_FACE_COMPARISON         (CAM_SERVICE_OFFSET + 5)
        #define     WFS_CMD_CAM_RECORD                  (CAM_SERVICE_OFFSET + 6)
        #define     WFS_CMD_CAM_DISPLAY_HC              (CAM_SERVICE_OFFSET + 7)
        #define     WFS_CMD_CAM_IMPORT_KEY              (CAM_SERVICE_OFFSET + 8)
        #define     WFS_CMD_CAM_GENERATE_KCV            (CAM_SERVICE_OFFSET + 9)
        #define     WFS_CMD_CAM_GET_SIGNATURE           (CAM_SERVICE_OFFSET + 10)
        #define     WFS_CMD_CAM_SIGNATURE_MIW           (CAM_SERVICE_OFFSET + 90)
        #define     WFS_CMD_CAM_DISPLAY_TABLE           (CAM_SERVICE_OFFSET + 93)
        #define     WFS_CMD_CAM_SIGNATURE_MINGW         (CAM_SERVICE_OFFSET + 94)
    #endif
#endif
/* CAM Messages */

#define     WFS_USRE_CAM_MEDIATHRESHOLD         (CAM_SERVICE_OFFSET + 1)
#define     WFS_EXEE_CAM_INVALIDDATA            (CAM_SERVICE_OFFSET + 2)

/* values of WFSCAMSTATUS.fwDevice */

#define     WFS_CAM_DEVONLINE                   WFS_STAT_DEVONLINE
#define     WFS_CAM_DEVOFFLINE                  WFS_STAT_DEVOFFLINE
#define     WFS_CAM_DEVPOWEROFF                 WFS_STAT_DEVPOWEROFF
#define     WFS_CAM_DEVNODEVICE                 WFS_STAT_DEVNODEVICE
#define     WFS_CAM_DEVHWERROR                  WFS_STAT_DEVHWERROR
#define     WFS_CAM_DEVUSERERROR                WFS_STAT_DEVUSERERROR
#define     WFS_CAM_DEVBUSY                     WFS_STAT_DEVBUSY
#define     WFS_CAM_DEVFRAUDATTEMPT             WFS_STAT_DEVFRAUDATTEMPT

/* number of cameras supported/length of WFSCAMSTATUS.fwCameras field */

#define     WFS_CAM_CAMERAS_SIZE                (8)
#define     WFS_CAM_CAMERAS_MAX                 (WFS_CAM_CAMERAS_SIZE - 1)

/* indices of WFSCAMSTATUS.fwMedia[...]
              WFSCAMSTATUS.fwCameras [...]
              WFSCAMSTATUS.fwPictures[...]
              WFSCAMCAPS.fwCameras [...]
              WFSCAMTAKEPICT.wCamera             */

#define     WFS_CAM_ROOM                        (0)
#define     WFS_CAM_PERSON                      (1)
#define     WFS_CAM_EXITSLOT                    (2)
#define     WFS_CAM_EXTRA                       (3) 
/* values of WFSCAMSTATUS.fwMedia */

#define     WFS_CAM_MEDIAOK                     (0)
#define     WFS_CAM_MEDIAHIGH                   (1)
#define     WFS_CAM_MEDIAFULL                   (2)
#define     WFS_CAM_MEDIAUNKNOWN                (3)
#define     WFS_CAM_MEDIANOTSUPP                (4)

/* values of WFSCAMSTATUS.fwCameras */

#define     WFS_CAM_CAMNOTSUPP                  (0)
#define     WFS_CAM_CAMOK                       (1)
#define     WFS_CAM_CAMINOP                     (2)
#define     WFS_CAM_CAMUNKNOWN                  (3)

/* values of WFSCAMCAPS.fwType */

#define     WFS_CAM_TYPE_CAM                    (1)

/* values of WFSCAMCAPS.fwCameras */

#define     WFS_CAM_NOT_AVAILABLE               (0)
#define     WFS_CAM_AVAILABLE                   (1)

/* values of WFSCAMCAPS.fwCamData */

#define     WFS_CAM_NOTADD                      (0)
#define     WFS_CAM_AUTOADD                     (1)
#define     WFS_CAM_MANADD                      (2)

/* values of WFSCAMCAPS.fwCharSupport, WFSCAMTAKEPICT.fwCharSupport  */

#define     WFS_CAM_ASCII                       (0x0001)
#define     WFS_CAM_UNICODE                     (0x0002)
#define     WFS_CAM_CREATE                      (0) 
#define     WFS_CAM_DESTROY                     (1) 
#define     WFS_CAM_PAUSE                       (2) 
#define     WFS_CAM_RESUME                      (3) 
#define     WFS_CAM_ERASE                       (4) 
#define     WFS_CAM_PENASERASER                 (5)
#define     WFS_CAM_ERASERASPEN                 (6)  

#define     WFS_CAM_TEXT_POS_DEFAULT          (0)
#define     WFS_CAM_TEXT_POS_LEFT_TOP         (1)
#define     WFS_CAM_TEXT_POS_LEFT_BOTTOM      (2)
#define     WFS_CAM_TEXT_POS_RIGHT_TOP        (3)
#define     WFS_CAM_TEXT_POS_RIGHT_BOTTOM     (4)
#define     WFS_CAM_TEXT_POS_TOP              (5)
#define     WFS_CAM_TEXT_POS_BOTTOM           (6)
#define     WFS_CAM_TEXT_POS_CENTOR           (7)
/* XFS CAM Errors */ 
#define     WFS_CAM_BK_SHOW_DEFAULT           (0)
#define     WFS_CAM_BK_SHOW_CENTOR            (1)
#define     WFS_CAM_BK_SHOW_STRETCH           (2)

#define WFS_ERR_CAM_CAMNOTSUPP                  (-(CAM_SERVICE_OFFSET + 0))
#define WFS_ERR_CAM_MEDIAFULL                   (-(CAM_SERVICE_OFFSET + 1))
#define WFS_ERR_CAM_CAMINOP                     (-(CAM_SERVICE_OFFSET + 2))
#define WFS_ERR_CAM_CHARSETNOTSUPP              (-(CAM_SERVICE_OFFSET + 3))
#define WFS_ERR_CAM_FILEIOERROR                 (-(CAM_SERVICE_OFFSET + 4))
#define WFS_ERR_CAM_KEYNOTFOUND                 (-(CAM_SERVICE_OFFSET + 5))
#define WFS_ERR_CAM_ACCESSDENIED                (-(CAM_SERVICE_OFFSET + 6))
#define WFS_ERR_CAM_KEYINVALID                  (-(CAM_SERVICE_OFFSET + 7))
#define WFS_ERR_CAM_NOKEYRAM                    (-(CAM_SERVICE_OFFSET + 8))
#define WFS_ERR_CAM_INVALIDKEYLENGTH            (-(CAM_SERVICE_OFFSET + 9))
#define WFS_ERR_CAM_INVALID_HWND                (-(CAM_SERVICE_OFFSET + 10))
#define WFS_ERR_CAM_NOTSIGN_ERROR               (-(CAM_SERVICE_OFFSET + 11))


/* values of WFSCAMTAKEPICTSIZE.wScan_Size */
#define     WFS_CAM_SIZEALL                         (0)
#define     WFS_CAM_SIZEAUTO                        (1)
#define     WFS_CAM_SIZEA4                          (2)
#define     WFS_CAM_SIZEA5                          (3)
#define     WFS_CAM_SIZEA6                          (4)
#define     WFS_CAM_SIZEA7                          (5)
#define     WFS_CAM_SIZECALLINGCARD	                 (6)
#define     WFS_CAM_SIZEID                          (7)
#define     WFS_CAM_SIZECUSTOM                      (8)
#define     WFS_CAM_SIZEAJUSTEDTOWINDOW             (9)
#define     WFS_CAM_SIZEAJUSTEDTOFRAME              (10)
#define     WFS_CAM_SIZEAJUSTEDTOFRAMEANDCHECKFACE  (11)
/* values of WFSCAMIMPORT.wAlgorithm,WFSCAMGETSIGNATUREENCRYPT.wAlgorithm */
#define     WFS_CAM_CRYPTNONE                  (0)
#define     WFS_CAM_CRYPTDESECB                (1)
#define     WFS_CAM_CRYPTDESCBC                (2)
#define     WFS_CAM_CRYPT3DESECB               (3)
#define     WFS_CAM_CRYPT3DESCBC               (4)
#define     WFS_CAM_CRYPTSM2                   (5)
#define     WFS_CAM_CRYPTSM3                   (6)
#define     WFS_CAM_CRYPTSM4ECB                (7)
#define     WFS_CAM_CRYPTSM4CBC                (8)

/* values of WFSCAMIMPORT.wClear */
#define     WFS_CAM_CLEARNONE                  (0)
#define     WFS_CAM_CLEARKEY                   (1)
#define     WFS_CAM_CLEARALL                   (2)

/* values of WFSCAMIMPORT.wKey_Check_Mode */
#define     WFS_CAM_KCVNONE                    (0) 
#define     WFS_CAM_KCVSELF                    (1) 
#define     WFS_CAM_KCVZERO                    (2) 
/*=================================================================*/
/* CAM Info Command Structures */
/*=================================================================*/

typedef struct _wfs_cam_status
{
    WORD            fwDevice;
    WORD            fwMedia[WFS_CAM_CAMERAS_SIZE];
    WORD            fwCameras[WFS_CAM_CAMERAS_SIZE];
    USHORT          usPictures[WFS_CAM_CAMERAS_SIZE];
    LPSTR           lpszExtra;
    WORD wAntiFraudModule;
} WFSCAMSTATUS, *LPWFSCAMSTATUS;

typedef struct _wfs_cam_caps
{
    WORD            wClass;
    WORD            fwType;
    WORD            fwCameras[WFS_CAM_CAMERAS_SIZE];
    USHORT          usMaxPictures;
    WORD            fwCamData;
    USHORT          usMaxDataLength;
    WORD            fwCharSupport;
    LPSTR           lpszExtra;
    BOOL bPictureFile;
    BOOL bAntiFraudModule;
} WFSCAMCAPS, *LPWFSCAMCAPS;


/*=================================================================*/
/* CAM Execute Command Structures */
/*=================================================================*/

typedef struct _wfs_cam_take_picture
{
    WORD            wCamera;
    LPSTR           lpszCamData;
    LPWSTR          lpszUNICODECamData;
} WFSCAMTAKEPICT, *LPWFSCAMTAKEPICT;

typedef struct _WFS_hex_cam_data
{
    USHORT          usLength;
    LPBYTE          lpbData;
} WFSXCAMDATA, *LPWFSXCAMDATA;

//TODO 待确认

//typedef struct _WFS_CAM_display
//{
//WORD                     wCamera;
//WORD                     wAction;
//WORD                     wX;
//WORD                     wY;
//WORD                     wWidth;
//WORD                     wHeight;
//DWORD                    hWnd;
//WORD                     wHpixel;
//WORD                     wVpixel;
//LPSTR                    lpstrText_Data;
//LPWSTR                   lpstrUNICODE_Text_Data;
//WORD                     wFont_Width;
//WORD                     wFont_Height;
//LPSTR                    lpstrFace;
//WORD                     wTextPosition;
//LPSTR                    lpstrBackgroundFile;
//WORD                     wBkShow;
//LPSTR                    lpstrKey;
//LPSTR                    lpstrEnc_Key;
//LPWFSXCAMDATA            lpxKey_Enc_Key;
//WORD                     wAlgorithm;
//LPSTR                    lpstrExtra;
//}WFSCAMDISP, *LPWFSCAMDISP;

typedef struct _lfs_cam_display
{
    WORD                     wCamera;
    WORD                     wAction;
    WORD                     wWidth;
    WORD                     wHeight;
    WORD                     wX;
    WORD                     wY;
    DWORD                    hWnd;
}WFSCAMDISP, *LPWFSCAMDISP;

//typedef struct _WFS_CAM_take_picture_ex
//{
//WORD                     wCamera;
//LPSTR                    lpstrCam_Data;
//LPWSTR                   lpstrUNICODE_Cam_Data;
//LPSTR	    lpstrPicture_File;
//WORD                     wScan_Size;
//LPSTR                    lpstrExtra;
//} WFSCAMTAKEPICTEX, *LPWFSCAMTAKEPICTEX;

typedef struct _WFS_CAM_take_picture_ex
{
WORD                     wCamera;
LPSTR                    lpszCamData;
LPWSTR                   lpszUNICODECamData;
LPSTR                    lpstrPath;
WORD                     wScanSize;
} WFSCAMTAKEPICTEX, *LPWFSCAMTAKEPICTEX;

typedef struct _WFS_CAM_face_comparison 
{
    WORD                     wCamera;
    LPSTR                    lpstrPicture_File_A; 
    LPSTR                    lpstrPicture_File_B; 
	LPSTR					 lpstrExtra;
} WFSCAMFACECOMPARISON, *LPWFSCAMFACECOMPARISON;

typedef struct _WFS_CAM_face_comparison_out
{
      WORD                     wScore;
LPSTR                    lpstrExtra;
} WFSCAMFACECOMPARISONOUT, *LPWFSCAMFACECOMPARISONOUT;

typedef struct _WFS_CAM_display_hc
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
} WFSCAMDISPHC, *LPWFSCAMDISPHC;

typedef struct _WFS_CAM_record
{
WORD                    wCamera;
WORD                    wAction; 
WORD                    wHpixel;
WORD                    wVpixel;
WORD                    wFps;
WORD                    wAudio_Option;
LPSTR                   lpstrRecord_File;
LPSTR                   lpstrExtra;
} WFSCAMRECORD, *LPWFSCAMRECORD;

typedef struct _wfs_cam_display_table{
    WORD                wCamera;
    WORD                wAction;
    WORD                wWidth;
    WORD                wHegith;
    WORD                wX;
    WORD                wY;
    DWORD               hWnd;
    LPSTR               lpszWndTip;
    WORD                wFont_Height;
    WORD                wFont_Width;
    LPSTR                lpstrFace;
}WFSCAMDISPLAYTABLE,*LPWFSCAMDISPLAYTABLE;


typedef struct _wfs_cam_sign_data{
    WORD wStatus;
    ULONG ulData_Lengt;
    LPBYTE lpbData;
    LPSTR lpstrExtra;
}WFSCAMSIGNDATA, *LPWFSCAMSIGNDATA;

typedef struct _WFS_CAM_import
{ 
    LPSTR                   lpstrKey;
    LPSTR                   lpstrEnc_Key;
    LPWFSXCAMDATA           lpxValue;
    LPWFSXCAMDATA           lpxControl_Vector;
    WORD                    wClear;
    WORD                    wAlgorithm;
    WORD                    wKey_Check_Mode;
    LPWFSXCAMDATA           lpxKey_Check_Value;
    LPSTR                   lpstrExtra;
} WFSCAMIMPORT, *LPWFSCAMIMPORT;

typedef struct _WFS_CAM_get_signature
{
    WORD                wCamera;
    LPSTR               lpstrPicture_File;
    LPSTR               lpstrTrack_File;
    LPSTR               lpstrExtra;
} WFSCAMGETSIGNATURE, *LPWFSCAMGETSIGNATURE;

typedef struct _WFS_CAM_get_signature_out
{
    WORD                 wStatus;
    ULONG                ulData_Length;
    LPBYTE               lpbData;
    LPSTR                lpstrExtra;
} WFSCAMGETSIGNATUREOUT, *LPWFSCAMGETSIGNATUREOUT;

typedef struct _WFS_CAM_get_signature_miw_out
{
    WORD                 wStatus;
    ULONG                ulDataLength;
    LPBYTE               lpbData;
} WFSCAMGETSIGNATUREMIWOUT, *LPWFSCAMGETSIGNATUREMIWOUT;

typedef struct _WFS_CAM_get_signature_mingw_out
{
    WORD                 wStatus;
    ULONG                ulDataLength;
    LPBYTE               lpbData;
} WFSCAMGETSIGNATUREMINGWOUT, *LPWFSCAMGETSIGNATUREMINGWOUT;

typedef struct _WFS_CAM_get_signature_miw
{
    WORD                     wCamera;
    LPSTR                    lpstrPicture_File;
    LPSTR                    lpstrTrack_File;
    LPSTR                    lpstrKey;
    LPWFSXCAMDATA             lpstrEncKey;
    WORD                     wAlgorithm;
} WFSCAMGETSIGNATUREMIW, *LPWFSCAMGETSIGNATUREMIW;

typedef struct _WFS_CAM_get_signature_mingw
{
    WORD                     wCamera;
    LPSTR                    lpstrPictureFile;
    LPSTR                    lpstrTrackFile;
} WFSCAMGETSIGNATUREMINGW, *LPWFSCAMGETSIGNATUREMINGW;

/* restore alignment */
struct WFSCAMSTATUSHelper : public WFSCAMSTATUS
{
    WFSCAMSTATUSHelper() { Clear(); }
    void Copy(LPWFSCAMSTATUS lpNew)
    {
        Clear();
        memcpy(this, lpNew, sizeof(WFSCAMSTATUS));
        if (lpNew->lpszExtra != nullptr)
        {
            this->lpszExtra = szExtra;
            UINT uLen = GetLenOfSZZ(lpNew->lpszExtra);
            UINT uMaxLen = sizeof(this->szExtra) - 2;
            if (uLen > uMaxLen)
                uLen = uMaxLen;
            memcpy(this->szExtra, lpNew->lpszExtra, uLen);
        }
    }
    void Clear() { memset(this, 0x00, sizeof(WFSCAMSTATUSHelper)); }
private:
    char szExtra[2048];
};
#pragma pack (pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif  /* __INC_XFSCAM__H */
