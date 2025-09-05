/******************************************************************************
 *                                                                             *
 * xfsbcr.h    XFS - Barcode Reader (BCR) definitions                          *
 *                                                                             *
 *                Version 1.00                                                 *
 *                                                                             *
 ******************************************************************************/

#ifndef __INC_XFSBCR__H
#define __INC_XFSBCR__H

#ifdef __cplusplus
extern "C" {
#endif

#include "lfsapi.h"

/* be aware of alignment */
#pragma pack(push, 1)

/* values of LFSBCRCAPS.wClass */

#define LFS_SERVICE_CLASS_BCR         (11)
#define LFS_SERVICE_CLASS_VERSION_BCR (0x0001) /* Version 1.00 */
#define LFS_SERVICE_CLASS_NAME_BCR    "BCR"

#define BCR_SERVICE_OFFSET (LFS_SERVICE_CLASS_BCR * 100)

/* BCR Info Commands */

#define LFS_INF_BCR_STATUS       (BCR_SERVICE_OFFSET + 1)
#define LFS_INF_BCR_CAPABILITIES (BCR_SERVICE_OFFSET + 2)

/* BCR Execute Commands */

#define LFS_CMD_BCR_READ               (BCR_SERVICE_OFFSET + 1)
#define LFS_CMD_BCR_RESET              (BCR_SERVICE_OFFSET + 2)
#define LFS_CMD_BCR_SET_GUIDANCE_LIGHT (BCR_SERVICE_OFFSET + 3)
#define LFS_CMD_BCR_POWER_SAVE_CONTROL (BCR_SERVICE_OFFSET + 4)

/* BCR Messages */

#define LFS_SRVE_BCR_DEVICEPOSITION    (BCR_SERVICE_OFFSET + 1)
#define LFS_SRVE_BCR_POWER_SAVE_CHANGE (BCR_SERVICE_OFFSET + 2)

/* values of LFSBCRSTATUS.fwDevice */

#define LFS_BCR_DEVONLINE         LFS_STAT_DEVONLINE
#define LFS_BCR_DEVOFFLINE        LFS_STAT_DEVOFFLINE
#define LFS_BCR_DEVPOWEROFF       LFS_STAT_DEVPOWEROFF
#define LFS_BCR_DEVNODEVICE       LFS_STAT_DEVNODEVICE
#define LFS_BCR_DEVHWERROR        LFS_STAT_DEVHWERROR
#define LFS_BCR_DEVUSERERROR      LFS_STAT_DEVUSERERROR
#define LFS_BCR_DEVBUSY           LFS_STAT_DEVBUSY

/* values of LFSBCRSTATUS.fwBCRScanner */

#define LFS_BCR_SCANNERON      (0)
#define LFS_BCR_SCANNEROFF     (1)
#define LFS_BCR_SCANNERINOP    (2)
#define LFS_BCR_SCANNERUNKNOWN (3)

/* values of LFSBCRSTATUS.wDevicePosition
             LFSBCRDEVICEPOSITION.wPosition */

#define LFS_BCR_DEVICEINPOSITION    (0)
#define LFS_BCR_DEVICENOTINPOSITION (1)
#define LFS_BCR_DEVICEPOSUNKNOWN    (2)
#define LFS_BCR_DEVICEPOSNOTSUPP    (3)

/* values of LFSBCRCAPS.lpwSymbologies
             LFSBCRREADINPUT.lpwSymbologies
             LFSBCRREADOUTPUT.wSymbology */

#define LFS_BCR_SYM_UNKNOWN          (0)
#define LFS_BCR_SYM_EAN128           (1)
#define LFS_BCR_SYM_EAN8             (2)
#define LFS_BCR_SYM_EAN8_2           (3)
#define LFS_BCR_SYM_EAN8_5           (4)
#define LFS_BCR_SYM_EAN13            (5)
#define LFS_BCR_SYM_EAN13_2          (6)
#define LFS_BCR_SYM_EAN13_5          (7)
#define LFS_BCR_SYM_JAN13            (8)
#define LFS_BCR_SYM_UPCA             (9)
#define LFS_BCR_SYM_UPCE0            (10)
#define LFS_BCR_SYM_UPCE0_2          (11)
#define LFS_BCR_SYM_UPCE0_5          (12)
#define LFS_BCR_SYM_UPCE1            (13)
#define LFS_BCR_SYM_UPCE1_2          (14)
#define LFS_BCR_SYM_UPCE1_5          (15)
#define LFS_BCR_SYM_UPCA_2           (16)
#define LFS_BCR_SYM_UPCA_5           (17)
#define LFS_BCR_SYM_CODABAR          (18)
#define LFS_BCR_SYM_ITF              (19)
#define LFS_BCR_SYM_11               (20)
#define LFS_BCR_SYM_39               (21)
#define LFS_BCR_SYM_49               (22)
#define LFS_BCR_SYM_93               (23)
#define LFS_BCR_SYM_128              (24)
#define LFS_BCR_SYM_MSI              (25)
#define LFS_BCR_SYM_PLESSEY          (26)
#define LFS_BCR_SYM_STD2OF5          (27)
#define LFS_BCR_SYM_STD2OF5_IATA     (28)
#define LFS_BCR_SYM_PDF_417          (29)
#define LFS_BCR_SYM_MICROPDF_417     (30)
#define LFS_BCR_SYM_DATAMATRIX       (31)
#define LFS_BCR_SYM_MAXICODE         (32)
#define LFS_BCR_SYM_CODEONE          (33)
#define LFS_BCR_SYM_CHANNELCODE      (34)
#define LFS_BCR_SYM_TELEPEN_ORIGINAL (35)
#define LFS_BCR_SYM_TELEPEN_AIM      (36)
#define LFS_BCR_SYM_RSS              (37)
#define LFS_BCR_SYM_RSS_EXPANDED     (38)
#define LFS_BCR_SYM_RSS_RESTRICTED   (39)
#define LFS_BCR_SYM_COMPOSITE_CODE_A (40)
#define LFS_BCR_SYM_COMPOSITE_CODE_B (41)
#define LFS_BCR_SYM_COMPOSITE_CODE_C (42)
#define LFS_BCR_SYM_POSICODE_A       (43)
#define LFS_BCR_SYM_POSICODE_B       (44)
#define LFS_BCR_SYM_TRIOPTIC_CODE_39 (45)
#define LFS_BCR_SYM_CODABLOCK_F      (46)
#define LFS_BCR_SYM_CODE_16K         (47)
#define LFS_BCR_SYM_QRCODE           (48)
#define LFS_BCR_SYM_AZTEC            (49)
#define LFS_BCR_SYM_UKPOST           (50)
#define LFS_BCR_SYM_PLANET           (51)
#define LFS_BCR_SYM_POSTNET          (52)
#define LFS_BCR_SYM_CANADIANPOST     (53)
#define LFS_BCR_SYM_NETHERLANDSPOST  (54)
#define LFS_BCR_SYM_AUSTRALIANPOST   (55)
#define LFS_BCR_SYM_JAPANESEPOST     (56)
#define LFS_BCR_SYM_CHINESEPOST      (57)
#define LFS_BCR_SYM_KOREANPOST       (58)

/* Size and max index of dwGuidLights array */

#define LFS_BCR_GUIDLIGHTS_SIZE (32)
#define LFS_BCR_GUIDLIGHTS_MAX  (LFS_BCR_GUIDLIGHTS_SIZE - 1)

/* Indices of LFSBCRSTATUS.dwGuidLights [...]
              LFSBCRCAPS.dwGuidLights [...]
*/
#define LFS_BCR_GUIDANCE_BCR (0)

/* Values of LFSBCRSTATUS.dwGuidLights [...]
             LFSBCRCAPS.dwGuidLights [...],
             LFSBCRSETGUIDLIGHT.wGuidLight */

#define LFS_BCR_GUIDANCE_NOT_AVAILABLE (0x00000000)
#define LFS_BCR_GUIDANCE_OFF           (0x00000001)
#define LFS_BCR_GUIDANCE_ON            (0x00000002)
#define LFS_BCR_GUIDANCE_SLOW_FLASH    (0x00000004)
#define LFS_BCR_GUIDANCE_MEDIUM_FLASH  (0x00000008)
#define LFS_BCR_GUIDANCE_QUICK_FLASH   (0x00000010)
#define LFS_BCR_GUIDANCE_CONTINUOUS    (0x00000080)
#define LFS_BCR_GUIDANCE_RED           (0x00000100)
#define LFS_BCR_GUIDANCE_GREEN         (0x00000200)
#define LFS_BCR_GUIDANCE_YELLOW        (0x00000400)
#define LFS_BCR_GUIDANCE_BLUE          (0x00000800)
#define LFS_BCR_GUIDANCE_CYAN          (0x00001000)
#define LFS_BCR_GUIDANCE_MAGENTA       (0x00002000)
#define LFS_BCR_GUIDANCE_WHITE         (0x00004000)

/* values of LFSBCRSTATUS.wAntiFraudModule */

#define LFS_BCR_AFMNOTSUPP        (0)
#define LFS_BCR_AFMOK             (1)
#define LFS_BCR_AFMINOP           (2)
#define LFS_BCR_AFMDEVICEDETECTED (3)
#define LFS_BCR_AFMUNKNOWN        (4)

/* XFS BCR Errors */

#define LFS_ERR_BCR_BARCODEINVALID    (-(BCR_SERVICE_OFFSET + 0))
#define LFS_ERR_BCR_INVALID_PORT      (-(BCR_SERVICE_OFFSET + 1))
#define LFS_ERR_BCR_POWERSAVETOOSHORT (-(BCR_SERVICE_OFFSET + 2))

/*=================================================================*/
/* BCR Info Command Structures */
/*=================================================================*/
typedef struct _lfs_bcr_status {
  WORD fwDevice;
  WORD fwBCRScanner;
  DWORD dwGuidLights[LFS_BCR_GUIDLIGHTS_SIZE];
  LPSTR lpszExtra;
  WORD wDevicePosition;
  USHORT usPowerSaveRecoveryTime;
  WORD wAntiFraudModule;
} LFSBCRSTATUS, *LPLFSBCRSTATUS;

typedef struct _lfs_bcr_caps {
  WORD wClass;
  BOOL bCompound;
  BOOL bCanFilterSymbologies;
  LPWORD lpwSymbologies;
  DWORD dwGuidLights[LFS_BCR_GUIDLIGHTS_SIZE];
  LPSTR lpszExtra;
  BOOL bPowerSaveControl;
  BOOL bAntiFraudModule;
} LFSBCRCAPS, *LPLFSBCRCAPS;

/*=================================================================*/
/* BCR Execute Command Structures */
/*=================================================================*/
typedef struct _lfs_bcr_hex_data {
  USHORT usLength;
  LPBYTE lpbData;
} LFSBCRXDATA, *LPLFSBCRXDATA;

typedef struct _lfs_bcr_read_input {
  LPWORD lpwSymbologies;
} LFSBCRREADINPUT, *LPLFSBCRREADINPUT;

typedef struct _lfs_bcr_read_output {
  WORD wSymbology;
  LPLFSBCRXDATA lpxBarcodeData;
  LPSTR lpszSymbologyName;
} LFSBCRREADOUTPUT, *LPLFSBCRREADOUTPUT;

typedef struct _lfs_bcr_set_guidlight {
  WORD wGuidLight;
  DWORD dwCommand;
} LFSBCRSETGUIDLIGHT, *LPLFSBCRSETGUIDLIGHT;

typedef struct _lfs_bcr_power_save_control {
  USHORT usMaxPowerSaveRecoveryTime;
} LFSBCRPOWERSAVECONTROL, *LPLFSBCRPOWERSAVECONTROL;

/*=================================================================*/
/* BCR Message Structures */
/*=================================================================*/

typedef struct _lfs_bcr_device_position {
  WORD wPosition;
} LFSBCRDEVICEPOSITION, *LPLFSBCRDEVICEPOSITION;

typedef struct _lfs_bcr_power_save_change {
  USHORT usPowerSaveRecoveryTime;
} LFSBCRPOWERSAVECHANGE, *LPLFSBCRPOWERSAVECHANGE;

/*   restore alignment   */
#pragma pack(pop)
#ifdef __cplusplus
} /*extern "C"*/

#endif
#endif /* __INC_XFSBCR__H */
