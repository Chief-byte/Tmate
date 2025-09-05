/******************************************************************************
 *                                                                             *
 * lfscam.h      LFS - Camera (CAM) definitions                                *
 *                                                                             *
 *             Version 3.20  (March 02 2011)                                   *
 *                                                                             *
 ******************************************************************************/

#ifndef __INC_LFSCAM__H
#define __INC_LFSCAM__H

#ifdef __cplusplus
extern "C" {
#endif

#include "lfsapi.h"
#include "lfspin.h"

/* be aware of alignment */
#pragma pack(push, 1)

/* values of LFSCAMCAPS.wClass */

#define LFS_SERVICE_CLASS_CAM   (10)
#define LFS_SERVICE_VERSION_CAM (0x0001) /* Version 3.21 */
#define LFS_SERVICE_NAME_CAM    "CAM"

#define CAM_SERVICE_OFFSET (LFS_SERVICE_CLASS_CAM * 100)

/* CAM Info Commands */
#define LFS_INF_CAM_STATUS       (CAM_SERVICE_OFFSET + 1)
#define LFS_INF_CAM_CAPABILITIES (CAM_SERVICE_OFFSET + 2)

/* CAM Execute Commands */
#define LFS_CMD_CAM_TAKE_PICTURE        (CAM_SERVICE_OFFSET + 1)
#define LFS_CMD_CAM_RESET               (CAM_SERVICE_OFFSET + 2)
#define LFS_CMD_CAM_TAKE_PICTURE_EX     (CAM_SERVICE_OFFSET + 3)
#define LFS_CMD_CAM_SYNCHRONIZE_COMMAND (CAM_SERVICE_OFFSET + 4)
#define LFS_CMD_CAM_TAKE_PICTURE_CRYPT  (CAM_SERVICE_OFFSET + 82)
#define LFS_CMD_CAM_COMPARE_PICTURE     (CAM_SERVICE_OFFSET + 83)
#define LFS_CMD_CAM_GENERATE_KCV        (CAM_SERVICE_OFFSET + 84)
#define LFS_CMD_CAM_DECRYPT_SIGNATURE   (CAM_SERVICE_OFFSET + 85)  //
#define LFS_CMD_CAM_IMPORT_KEY          (CAM_SERVICE_OFFSET + 86)
#define LFS_CMD_CAM_GET_SIGNATURE       (CAM_SERVICE_OFFSET + 87)
#define LFS_CMD_CAM_RECORD              (CAM_SERVICE_OFFSET + 88)
#define LFS_CMD_CAM_DISPLAY             (CAM_SERVICE_OFFSET + 89)
#define LFS_CMD_CAM_DISPLAY_EX          (CAM_SERVICE_OFFSET + 91)

/* CAM Messages */

#define LFS_USRE_CAM_MEDIATHRESHOLD (CAM_SERVICE_OFFSET + 1)
#define LFS_EXEE_CAM_INVALIDDATA    (CAM_SERVICE_OFFSET + 2)

/* values of LFSCAMSTATUS.fwDevice */

#define LFS_CAM_DEVONLINE         LFS_STAT_DEVONLINE
#define LFS_CAM_DEVOFFLINE        LFS_STAT_DEVOFFLINE
#define LFS_CAM_DEVPOWEROFF       LFS_STAT_DEVPOWEROFF
#define LFS_CAM_DEVNODEVICE       LFS_STAT_DEVNODEVICE
#define LFS_CAM_DEVHWERROR        LFS_STAT_DEVHWERROR
#define LFS_CAM_DEVUSERERROR      LFS_STAT_DEVUSERERROR
#define LFS_CAM_DEVBUSY           LFS_STAT_DEVBUSY
#define LFS_CAM_DEVFRAUDATTEMPT   LFS_STAT_DEVFRAUDATTEMPT
#define LFS_CAM_DEVPOTENTIALFRAUD LFS_STAT_DEVPOTENTIALFRAUD

/* number of cameras supported/length of LFSCAMSTATUS.fwCameras field */

#define LFS_CAM_CAMERAS_SIZE (8)
#define LFS_CAM_CAMERAS_MAX  (LFS_CAM_CAMERAS_SIZE - 1)

/* indices of LFSCAMSTATUS.fwMedia[...]
              LFSCAMSTATUS.fwCameras [...]
              LFSCAMSTATUS.usPictures[...]
              LFSCAMCAPS.fwCameras [...]
              LFSCAMTAKEPICT.wCamera             */

#define LFS_CAM_ROOM       (0)
#define LFS_CAM_PERSON     (1)
#define LFS_CAM_EXITSLOT   (2)
#define LFS_CAM_EXTRA      (3)
#define LFS_CAM_HIGHCAMERA (4)

/* values of LFSCAMSTATUS.fwMedia */

#define LFS_CAM_MEDIAOK      (0)
#define LFS_CAM_MEDIAHIGH    (1)
#define LFS_CAM_MEDIAFULL    (2)
#define LFS_CAM_MEDIAUNKNOWN (3)
#define LFS_CAM_MEDIANOTSUPP (4)

/* values of LFSCAMSTATUS.fwCameras */

#define LFS_CAM_CAMNOTSUPP (0)
#define LFS_CAM_CAMOK      (1)
#define LFS_CAM_CAMINOP    (2)
#define LFS_CAM_CAMUNKNOWN (3)

/* values of LFSCAMCAPS.fwType */

#define LFS_CAM_TYPE_CAM (1)

/* values of LFSCAMCAPS.fwCameras */

#define LFS_CAM_NOT_AVAILABLE (0)
#define LFS_CAM_AVAILABLE     (1)

/* values of LFSCAMCAPS.fwCamData */

#define LFS_CAM_NOTADD  (0)
#define LFS_CAM_AUTOADD (1)
#define LFS_CAM_MANADD  (2)

/* values of LFSCAMCAPS.fwCharSupport */

#define LFS_CAM_ASCII   (0x0001)
#define LFS_CAM_UNICODE (0x0002)

/* values of LFSCAMSTATUS.wAntiFraudModule */

#define LFS_CAM_AFMNOTSUPP        (0)
#define LFS_CAM_AFMOK             (1)
#define LFS_CAM_AFMINOP           (2)
#define LFS_CAM_AFMDEVICEDETECTED (3)
#define LFS_CAM_AFMUNKNOWN        (4)

/* values of LPLFSCAMDISP.action */
#define LFS_CAM_CREATE  (0)
#define LFS_CAM_DESTROY (1)
#define LFS_CAM_PAUSE   (2)
#define LFS_CAM_RESUME  (3)
#define LFS_CAM_ERASE   (4)

/* values of LPLFSCAMIMPORTKEY.use */
/* values of LPLFSCAMIMPORTKEY.use */
#define LFS_CAM_USECRYPT     (0x0001)  //用于加解密计算
#define LFS_CAM_USEFUNCTION  (0x0002)  //用于轨迹数据加密
#define LFS_CAM_USEMACING    (0x0004)  //用于MAC计算
#define LFS_CAM_USEKEYENCKEY (0x0020)  //用于密钥加密
#define LFS_CAM_USECHINASM   (0x0800)  //用于国密算法

/* values of LFSCAMIMPORT.key_check_mode */
#define LFS_CAM_KCVNONE (0x0000)
#define LFS_CAM_KCVSELF (0x0001)
#define LFS_CAM_KCVZERO (0x0002)

/* values of LPLFSCAMSIGNDATA.status */
#define LFS_CAM_DATAOK         (0)
#define LFS_CAM_DATAMISSING    (1)
#define LFS_CAM_DATASRCNOTSUPP (2)
#define LFS_CAM_DATASRCMISSING (3)

/* values of LFSCAMTAKEPICT.scansize */
#define LFS_CAM_SIZEALL             (0)  // All
#define LFS_CAM_SIZEA4              (1)  // A4
#define LFS_CAM_SIZEA5              (2)  // A5
#define LFS_CAM_SIZEA6              (3)  // A6
#define LFS_CAM_SIZEA7              (4)  // A7
#define LFS_CAM_SIZECALLINGCARD     (5)  // 名片
#define LFS_CAM_SIZEID              (6)  // 身份证
#define LFS_CAM_SIZECUSTOM          (7)  // 自定义
#define LFS_CAM_SIZEAJUSTEDTOWINDOW (8)
#define LFS_CAM_SIZEAJUSTEDTOFRAME  (9)

/* LFS CAM Errors */

#define LFS_ERR_CAM_CAMNOTSUPP        (-(CAM_SERVICE_OFFSET + 0))
#define LFS_ERR_CAM_MEDIAFULL         (-(CAM_SERVICE_OFFSET + 1))
#define LFS_ERR_CAM_CAMINOP           (-(CAM_SERVICE_OFFSET + 2))
#define LFS_ERR_CAM_CHARSETNOTSUPP    (-(CAM_SERVICE_OFFSET + 3))
#define LFS_ERR_CAM_FILEIOERROR       (-(CAM_SERVICE_OFFSET + 4))
#define LFS_ERR_CAM_COMMANDUNSUPP     (-(CAM_SERVICE_OFFSET + 5))
#define LFS_ERR_CAM_SYNCHRONIZEUNSUPP (-(CAM_SERVICE_OFFSET + 6))
#define LFS_ERR_CAM_KEYNOTFOUND       (-(CAM_SERVICE_OFFSET + 99))
#define LFS_ERR_CAM_ACCESSDENIED      (-(CAM_SERVICE_OFFSET + 98))
#define LFS_ERR_CAM_DUPLICATEKEY      (-(CAM_SERVICE_OFFSET + 97))
#define LFS_ERR_CAM_KEYNOVALUE        (-(CAM_SERVICE_OFFSET + 96))
#define LFS_ERR_CAM_USEVIOLATION      (-(CAM_SERVICE_OFFSET + 95))
#define LFS_ERR_CAM_INVALIDKEYLENGTH  (-(CAM_SERVICE_OFFSET + 94))
#define LFS_ERR_CAM_NOKEYRAM          (-(CAM_SERVICE_OFFSET + 93))
#define LFS_ERR_CAM_INVALID_HWND      (-(CAM_SERVICE_OFFSET + 92))
#define LFS_ERR_CAM_NOTSIGNEROR       (-(CAM_SERVICE_OFFSET + 91))
#define LFS_ERR_CAM_SYNTAX            (-(CAM_SERVICE_OFFSET + 90))

/*=================================================================*/
/* CAM Info Command Structures */
/*=================================================================*/

typedef struct _lfs_cam_status {
  WORD fwDevice;
  WORD fwMedia[LFS_CAM_CAMERAS_SIZE];
  WORD fwCameras[LFS_CAM_CAMERAS_SIZE];
  USHORT usPictures[LFS_CAM_CAMERAS_SIZE];
  LPSTR lpszExtra;
  WORD wAntiFraudModule;
} LFSCAMSTATUS, *LPLFSCAMSTATUS;

typedef struct _lfs_cam_caps {
  WORD wClass;
  WORD fwType;
  WORD fwCameras[LFS_CAM_CAMERAS_SIZE];
  USHORT usMaxPictures;
  WORD fwCamData;
  USHORT usMaxDataLength;
  WORD fwCharSupport;
  LPSTR lpszExtra;
  BOOL bPictureFile;
  BOOL bAntiFraudModule;
  LPDWORD synchronizable_commands;
} LFSCAMCAPS, *LPLFSCAMCAPS;

/*=================================================================*/
/* CAM Execute Command Structures */
/*=================================================================*/

typedef struct _lfs_cam_take_picture {
  WORD wCamera;
  LPSTR lpszCamData;
  LPWSTR lpszUNICODECamData;
} LFSCAMTAKEPICT, *LPLFSCAMTAKEPICT;

typedef struct _lfs_cam_take_picture_ex {
  WORD wCamera;
  LPSTR lpszCamData;
  LPWSTR lpszUNICODECamData;
  LPSTR lpszPictureFile;
} LFSCAMTAKEPICTEX, *LPLFSCAMTAKEPICTEX;

typedef struct _lfs_cam_take_image_data  // Í¼ÏñÊý¾Ý
{
  WORD datalen;  // Êý¾Ý³¤¶È
  LPBYTE data;   // Êý¾Ý
} LFSCAMIMAGDATA, *LPLFSCAMIMAGDATA;
typedef struct _lfs_cam_synchronize_command {
  DWORD dwCommand;
  LPVOID lpCmdData;
} LFSCAMSYNCHRONIZECOMMAND, *LPLFSCAMSYNCHRONIZECOMMAND;

typedef struct _lfs_cam_display {
  WORD camera;
  WORD action;
  WORD width;
  WORD height;
  WORD x;
  WORD y;
  DWORD wnd;
  WORD hpixel;
  WORD vpixel;
  LPSTR text_data;  // 文本数据(预留)
} LFSCAMDISP, *LPLFSCAMDISP;

typedef struct _lfs_cam_import {
  LPSTR key;
  LPSTR enc_key;
  LPLFSXDATA indent;
  LPLFSXDATA value;
  WORD use;
  WORD key_check_mode;
  LPLFSXDATA key_check_value;
} LFSCAMIMPORT, *LPLFSCAMIMPORT;

typedef struct _lfs_cam_import_ex {
  LPSTR lpsKey;
  LPSTR lpsEncKey;
  LPLFSXDATA lpxIdent;
  LPLFSXDATA lpxValue;
  WORD fwUse;
} LFSCAMIMPORTEX, *LPLFSCAMIMPORTEX;

typedef struct _lfs_cam_get_signature {
  WORD camera;
  LPSTR cam_data;
  LPWSTR unicode_cam_data;
  LPSTR picture_file;
  DWORD wnd;
  LPSTR key;
  LPSTR enc_key;
} LFSCAMGETSIGNATURE, *LPLFSCAMGETSIGNATURE;

typedef struct _lfs_cam_sign_data {
  WORD status;
  ULONG data_length;
  LPBYTE data;
} LFSCAMSIGNDATA, *LPLFSCAMSIGNDATA;

typedef struct _lfs_cam_decrypt_signature  // 签名数据恢复图片结构体
{
  LPSTR sign_data;     // 需要恢复成图片的签名数据
  LPSTR picture_file;  // 指定恢复成图片的路径和名称
  LPSTR key;           // 工作密钥，ASCII码格式
  LPSTR enc_key;       // 主密钥索引（名称）
  WORD action;         // 恢复操作
                       // LFS_CAM_CREATE - 将恢复的签名图片显示到窗口
                       // LFS_CAM_DESTROY - 结束显示窗口
                       // LFS_CAM_PAUSE - 只恢复签名图片，不显示到窗口
  DWORD wnd;           // 图片恢复后需要显示到的窗口的句柄，
                       // 不为NULL表示窗口由应用创建，为NULL表示窗口由厂商创建
  WORD width;          // 窗口宽度
  WORD height;         // 窗口高度
  WORD x;              // 窗口左上角的x坐标（相对于屏幕）
  WORD y;              // 窗口左上角的y坐标（相对于屏幕）
} LFSCAMDECRYPTSIGNATURE, *LPLFSCAMDECRYPTSIGNATURE;

typedef struct _lfs_cam_generate_kcv {
  LPSTR key;
  WORD key_check_mode;
} LFSCAMGENERATEKCV, *LPLFSCAMGENERATEKCV;

typedef struct _lfs_cam_kcv {
  LPLFSXDATA kcv;
} LFSCAMKCV, *LPLFSCAMKCV;

typedef struct _lfs_cam_display_ex {
  WORD camera;
  WORD action;
  WORD width;
  WORD height;
  WORD x;
  WORD y;
  DWORD wnd;
  WORD hpixel;
  WORD vpixel;
  LPSTR lpszTextData;
} LFSCAMDISPEX, *LPLFSCAMDISPEX;

/// LFS_CMD_CAM_COMPARE_PICTURE 输入结构体
typedef struct _lfs_cam_compare_picture {
  LPSTR server_image_file; /*用于比对的后台照片绝对路径*/
  LPSTR local_image_file;  /*用于比对的本地照片绝对路径*/
} LFSCAMCOMPAREPICT, *LPLFSCAMCOMPAREPICT;

/// LFS_CMD_CAM_COMPARE_PICTURE 输出结构体
typedef struct _lfs_cam_compare_picture_data {
  WORD status;
  ULONG compare_data;
} LFSCAMCOMPAREPICTDATA, *LPLFSCAMCOMPAREPICTDATA;

/// LFS_CMD_CAM_TAKE_PICTURE_CRYPT 输入结构体
typedef struct _lfs_cam_take_picture_crypt {
  WORD camera; /*指定使用哪个摄像头拍照                                            */
  LPSTR cam_data;
  LPWSTR unicode_cam_data;
  LPSTR
  picture_file; /*指定拍照图像文件的绝对路径（传 NULL，本命令本地不保存照片）。          */
  DWORD
  wnd; /*指定加密照片回显的窗口句柄（本地不保存照片，照片只通过此窗口句柄回显）。 */
  LPSTR
  key;            /*指定对照片加密的密钥。                                            */
  WORD algorithm; /*加密使用的算法                                                   */
} LFSCAMTAKEPICTCRYPT, *LPLFSCAMTAKEPICTCRYPT;

/// LFS_CMD_CAM_TAKE_PICTURE_CRYPT 输出结构体
typedef struct _lfs_cam_take_pict_crypt_data {
  WORD status;      /*照片加密数据状态        */
  ULONG data_lengt; /*数据长度。             */
  LPBYTE data;      /*加密后的照片数据。      */
} LFSCAMTAKEPICTCRYPTDATA, *LPLFSCAMTAKEPICTCRYPTDATA;

/* restore alignment */
#pragma pack(pop)

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* __INC_LFSCAM_*/
