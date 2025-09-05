/*****************************************************************************
*	                                                                           *
* LFSpin.h - Personal Identification Number Keypad (PIN) definitions        *
*	                                                                           *
*	 Version 1.0                                                               *
*	                                                                           *
****************************************************************************/
#ifndef __INC_LFSPIN__H
#define __INC_LFSPIN__H

#ifdef __cplusplus
extern "C" {
#endif

#include    "lfsapi.h" 

/*   be aware of alignment   */
#pragma pack(push,1)

/* values of LFSPINCAPS.wClass */

#define LFS_SERVICE_CLASS_PIN                       (4)
#define LFS_SERVICE_CLASS_VERSION_PIN               (0x0001) /* Version 1.0 */
#define LFS_SERVICE_CLASS_NAME_PIN                  "PIN"

#define PIN_SERVICE_OFFSET                          (LFS_SERVICE_CLASS_PIN * 100)

/* PIN Info Commands */

#define LFS_INF_PIN_STATUS                          (PIN_SERVICE_OFFSET + 1)
#define LFS_INF_PIN_CAPABILITIES                    (PIN_SERVICE_OFFSET + 2)
#define LFS_INF_PIN_KEY_DETAIL                      (PIN_SERVICE_OFFSET + 4)
#define LFS_INF_PIN_FUNCKEY_DETAIL                  (PIN_SERVICE_OFFSET + 5)
#define LFS_INF_PIN_HSM_TDATA                       (PIN_SERVICE_OFFSET + 6)
#define LFS_INF_PIN_KEY_DETAIL_EX                   (PIN_SERVICE_OFFSET + 7)
#define LFS_INF_PIN_SECUREKEY_DETAIL                (PIN_SERVICE_OFFSET + 8)
#define LFS_INF_PIN_QUERY_LOGICAL_HSM_DETAIL        (PIN_SERVICE_OFFSET + 9)

/* PIN Command Verbs */

#define LFS_CMD_PIN_CRYPT                              (PIN_SERVICE_OFFSET + 1)
#define LFS_CMD_PIN_IMPORT_KEY                         (PIN_SERVICE_OFFSET + 3)
#define LFS_CMD_PIN_GET_PIN                            (PIN_SERVICE_OFFSET + 5)
#define LFS_CMD_PIN_GET_PINBLOCK                       (PIN_SERVICE_OFFSET + 7)
#define LFS_CMD_PIN_GET_DATA                           (PIN_SERVICE_OFFSET + 8)
#define LFS_CMD_PIN_INITIALIZATION                     (PIN_SERVICE_OFFSET + 9)
#define LFS_CMD_PIN_LOCAL_DES                          (PIN_SERVICE_OFFSET + 10)
#define LFS_CMD_PIN_LOCAL_EUROCHEQUE                   (PIN_SERVICE_OFFSET + 11)
#define LFS_CMD_PIN_LOCAL_VISA                         (PIN_SERVICE_OFFSET + 12)
#define LFS_CMD_PIN_CREATE_OFFSET                      (PIN_SERVICE_OFFSET + 13)
#define LFS_CMD_PIN_DERIVE_KEY                         (PIN_SERVICE_OFFSET + 14)
#define LFS_CMD_PIN_PRESENT_IDC                        (PIN_SERVICE_OFFSET + 15)
#define LFS_CMD_PIN_LOCAL_BANKSYS                      (PIN_SERVICE_OFFSET + 16)
#define LFS_CMD_PIN_BANKSYS_IO                         (PIN_SERVICE_OFFSET + 17)
#define LFS_CMD_PIN_RESET                              (PIN_SERVICE_OFFSET + 18)
#define LFS_CMD_PIN_HSM_SET_TDATA                      (PIN_SERVICE_OFFSET + 19)
#define LFS_CMD_PIN_SECURE_MSG_SEND                    (PIN_SERVICE_OFFSET + 20)
#define LFS_CMD_PIN_SECURE_MSG_RECEIVE                 (PIN_SERVICE_OFFSET + 21)
#define LFS_CMD_PIN_GET_JOURNAL                        (PIN_SERVICE_OFFSET + 22)
#define LFS_CMD_PIN_IMPORT_KEY_EX                      (PIN_SERVICE_OFFSET + 23)
#define LFS_CMD_PIN_ENC_IO                             (PIN_SERVICE_OFFSET + 24)
#define LFS_CMD_PIN_HSM_INIT                           (PIN_SERVICE_OFFSET + 25)
#define LFS_CMD_PIN_IMPORT_RSA_PUBLIC_KEY              (PIN_SERVICE_OFFSET + 26)
#define LFS_CMD_PIN_EXPORT_RSA_ISSUER_SIGNED_ITEM      (PIN_SERVICE_OFFSET + 27)
#define LFS_CMD_PIN_IMPORT_RSA_SIGNED_DES_KEY          (PIN_SERVICE_OFFSET + 28)
#define LFS_CMD_PIN_GENERATE_RSA_KEY_PAIR              (PIN_SERVICE_OFFSET + 29)
#define LFS_CMD_PIN_EXPORT_RSA_EPP_SIGNED_ITEM         (PIN_SERVICE_OFFSET + 30)
#define LFS_CMD_PIN_LOAD_CERTIFICATE                   (PIN_SERVICE_OFFSET + 31)
#define LFS_CMD_PIN_GET_CERTIFICATE                    (PIN_SERVICE_OFFSET + 32)
#define LFS_CMD_PIN_REPLACE_CERTIFICATE                (PIN_SERVICE_OFFSET + 33)
#define LFS_CMD_PIN_START_KEY_EXCHANGE                 (PIN_SERVICE_OFFSET + 34)
#define LFS_CMD_PIN_IMPORT_RSA_ENCIPHERED_PKCS7_KEY    (PIN_SERVICE_OFFSET + 35)
#define LFS_CMD_PIN_EMV_IMPORT_PUBLIC_KEY              (PIN_SERVICE_OFFSET + 36)
#define LFS_CMD_PIN_DIGEST                             (PIN_SERVICE_OFFSET + 37)
#define LFS_CMD_PIN_SECUREKEY_ENTRY                    (PIN_SERVICE_OFFSET + 38)
#define LFS_CMD_PIN_GENERATE_KCV                       (PIN_SERVICE_OFFSET + 39)
#define LFS_CMD_PIN_SET_GUIDANCE_LIGHT                 (PIN_SERVICE_OFFSET + 41)
#define LFS_CMD_PIN_MAINTAIN_PIN                       (PIN_SERVICE_OFFSET + 42)
#define LFS_CMD_PIN_KEYPRESS_BEEP                      (PIN_SERVICE_OFFSET + 43)
#define LFS_CMD_PIN_SET_PINBLOCK_DATA                  (PIN_SERVICE_OFFSET + 44)
#define LFS_CMD_PIN_SET_LOGICAL_HSM                    (PIN_SERVICE_OFFSET + 45)
#define LFS_CMD_PIN_IMPORT_KEYBLOCK                    (PIN_SERVICE_OFFSET + 46)
#define LFS_CMD_PIN_POWER_SAVE_CONTROL                 (PIN_SERVICE_OFFSET + 47)
#define LFS_CMD_PIN_GET_PINBLOCK_EX                    (PIN_SERVICE_OFFSET + 53)
#define LFS_CMD_PIN_CHN_DIGEST                         (PIN_SERVICE_OFFSET + 60)
#define LFS_CMD_PIN_CHN_SET_SM2_PARAM                  (PIN_SERVICE_OFFSET + 61)
#define LFS_CMD_PIN_CHN_IMPORT_SM2_PUBLIC_KEY          (PIN_SERVICE_OFFSET + 62)
#define LFS_CMD_PIN_CHN_SIGN                           (PIN_SERVICE_OFFSET + 63)
#define LFS_CMD_PIN_CHN_VERIFY                         (PIN_SERVICE_OFFSET + 64)
#define LFS_CMD_PIN_CHN_EXPORT_SM2_ISSUER_SIGNED_ITEM  (PIN_SERVICE_OFFSET + 65)
#define LFS_CMD_PIN_CHN_GENERATE_SM2_KEY_PAIR          (PIN_SERVICE_OFFSET + 66)
#define LFS_CMD_PIN_CHN_EXPORT_SM2_EPP_SIGNED_ITEM     (PIN_SERVICE_OFFSET + 67)
#define LFS_CMD_PIN_CHN_IMPORT_SM2_SIGNED_SM4_KEY      (PIN_SERVICE_OFFSET + 68)

/* PIN Messages */

#define LFS_EXEE_PIN_KEY                            (PIN_SERVICE_OFFSET + 1)
#define LFS_SRVE_PIN_INITIALIZED                    (PIN_SERVICE_OFFSET + 2)
#define LFS_SRVE_PIN_ILLEGAL_KEY_ACCESS             (PIN_SERVICE_OFFSET + 3)
#define LFS_SRVE_PIN_OPT_REQUIRED                   (PIN_SERVICE_OFFSET + 4)
#define LFS_SRVE_PIN_HSM_TDATA_CHANGED              (PIN_SERVICE_OFFSET + 5)
#define LFS_SRVE_PIN_CERTIFICATE_CHANGE             (PIN_SERVICE_OFFSET + 6)
#define LFS_SRVE_PIN_HSM_CHANGED                    (PIN_SERVICE_OFFSET + 7)
#define LFS_EXEE_PIN_ENTERDATA                      (PIN_SERVICE_OFFSET + 8)
#define LFS_SRVE_PIN_DEVICEPOSITION                 (PIN_SERVICE_OFFSET + 9)
#define LFS_SRVE_PIN_POWER_SAVE_CHANGE              (PIN_SERVICE_OFFSET + 10)

/* values of LFSPINSTATUS.fwDevice */

#define LFS_PIN_DEVONLINE                           LFS_STAT_DEVONLINE
#define LFS_PIN_DEVOFFLINE                          LFS_STAT_DEVOFFLINE
#define LFS_PIN_DEVPOWEROFF                         LFS_STAT_DEVPOWEROFF
#define LFS_PIN_DEVNODEVICE                         LFS_STAT_DEVNODEVICE
#define LFS_PIN_DEVHWERROR                          LFS_STAT_DEVHWERROR
#define LFS_PIN_DEVUSERERROR                        LFS_STAT_DEVUSERERROR
#define LFS_PIN_DEVBUSY                             LFS_STAT_DEVBUSY
#define LFS_PIN_DEVFRAUDATTEMPT                     LFS_STAT_DEVFRAUDATTEMPT

/* values of LFSPINSTATUS.fwEnc_Stat */

#define LFS_PIN_ENCREADY                            (0)
#define LFS_PIN_ENCNOTREADY                         (1)
#define LFS_PIN_ENCNOTINITIALIZED                   (2)
#define LFS_PIN_ENCBUSY                             (3)
#define LFS_PIN_ENCUNDEFINED                        (4)
#define LFS_PIN_ENCINITIALIZED                      (5)
#define LFS_PIN_ENCPINTAMPERED                      (6)

/* Size and max index of dwGuid_Lights array */

#define     LFS_PIN_GUIDLIGHTS_SIZE                 (32)
#define     LFS_PIN_GUIDLIGHTS_MAX                  (LFS_PIN_GUIDLIGHTS_SIZE - 1)

/* Indices of LFSPINSTATUS.dwGuidLights [...]
              LFSPINCAPS.dwGuidLights [...]
*/

#define     LFS_PIN_GUIDANCE_PINPAD                 (0)

/* Values of LFSPINSTATUS.dwGuidLights [...]
             LFSPINCAPS.dwGuidLights [...]
*/

#define     LFS_PIN_GUIDANCE_NOT_AVAILABLE          (0x00000000)
#define     LFS_PIN_GUIDANCE_OFF                    (0x00000001)
#define     LFS_PIN_GUIDANCE_ON                     (0x00000002)
#define     LFS_PIN_GUIDANCE_SLOW_FLASH             (0x00000004)
#define     LFS_PIN_GUIDANCE_MEDIUM_FLASH           (0x00000008)
#define     LFS_PIN_GUIDANCE_QUICK_FLASH            (0x00000010)
#define     LFS_PIN_GUIDANCE_CONTINUOUS             (0x00000080)
#define     LFS_PIN_GUIDANCE_RED                    (0x00000100)
#define     LFS_PIN_GUIDANCE_GREEN                  (0x00000200)
#define     LFS_PIN_GUIDANCE_YELLOW                 (0x00000400)
#define     LFS_PIN_GUIDANCE_BLUE                   (0x00000800)
#define     LFS_PIN_GUIDANCE_CYAN                   (0x00001000)
#define     LFS_PIN_GUIDANCE_MAGENTA                (0x00002000)
#define     LFS_PIN_GUIDANCE_WHITE                  (0x00004000)


/* values for LFSPINSTATUS.fwAuto_Beep_Mode and
LFS_CMD_PIN_KEYPRESS_BEEP lpwMode parameter */

#define LFS_PIN_BEEP_ON_ACTIVE                      (0x0001)
#define LFS_PIN_BEEP_ON_INACTIVE                    (0x0002)

/* values of LFSPINSTATUS.wDevicePosition
             LFSPINDEVICEPOSITION.wPosition */

#define     LFS_PIN_DEVICEINPOSITION                (0)
#define     LFS_PIN_DEVICENOTINPOSITION             (1)
#define     LFS_PIN_DEVICEPOSUNKNOWN                (2)
#define     LFS_PIN_DEVICEPOSNOTSUPP                (3)

/* values of LFSPINCAPS.fwType */

#define LFS_PIN_TYPEEPP                             (0x0001)
#define LFS_PIN_TYPEEDM                             (0x0002)
#define LFS_PIN_TYPEHSM                             (0x0004)
#define LFS_PIN_TYPEETS                             (0x0008)

/* values of LFSPINCAPS.fwAlgorithms, LFSPINCRYPT.wAlgorithm */

#define LFS_PIN_CRYPTDESECB                         (0x0001)
#define LFS_PIN_CRYPTDESCBC                         (0x0002)
#define LFS_PIN_CRYPTDESCFB                         (0x0004)
#define LFS_PIN_CRYPTRSA                            (0x0008)
#define LFS_PIN_CRYPTECMA                           (0x0010)
#define LFS_PIN_CRYPTDESMAC                         (0x0020)
#define LFS_PIN_CRYPTTRIDESECB                      (0x0040)
#define LFS_PIN_CRYPTTRIDESCBC                      (0x0080)
#define LFS_PIN_CRYPTTRIDESCFB                      (0x0100)
#define LFS_PIN_CRYPTTRIDESMAC                      (0x0200)
#define LFS_PIN_CRYPTMAAMAC                         (0x0400)
#define LFS_PIN_CRYPTSM4CBC                         (0x0800)
#define LFS_PIN_CRYPTSM4                            (0x1000)
#define LFS_PIN_CRYPTSM4MAC                         (0x2000) 

/* values of LFSPINCAPS.fwPin_Formats */

#define LFS_PIN_FORM3624                            (0x0001)
#define LFS_PIN_FORMANSI                            (0x0002)
#define LFS_PIN_FORMISO0                            (0x0004)
#define LFS_PIN_FORMISO1                            (0x0008)
#define LFS_PIN_FORMECI2                            (0x0010)
#define LFS_PIN_FORMECI3                            (0x0020)
#define LFS_PIN_FORMVISA                            (0x0040)
#define LFS_PIN_FORMDIEBOLD                         (0x0080)
#define LFS_PIN_FORMDIEBOLDCO                       (0x0100)
#define LFS_PIN_FORMVISA3                           (0x0200)
#define LFS_PIN_FORMBANKSYS                         (0x0400)
#define LFS_PIN_FORMEMV                             (0x0800)
#define LFS_PIN_FORMISO3                            (0x2000)

/* values of LFSPINCAPS.fwDerivation_Algorithms */

#define LFS_PIN_CHIP_ZKA                            (0x0001)


/* values of LFSPINCAPS.fwPresentation_Algorithms */

#define LFS_PIN_PRESENT_CLEAR                       (0x0001)

/* values of LFSPINCAPS.fwDisplay */

#define LFS_PIN_DISPNONE                            (1)
#define LFS_PIN_DISPLEDTHROUGH                      (2)
#define LFS_PIN_DISPDISPLAY                         (3)

/* values of LFSPINCAPS.fwIDKey */

#define LFS_PIN_IDKEYINITIALIZATION                 (0x0001)
#define LFS_PIN_IDKEYIMPORT                         (0x0002)

/* values of LFSPINCAPS.fwValidation_Algorithms */

#define LFS_PIN_DES                                 (0x0001)
#define LFS_PIN_EUROCHEQUE                          (0x0002)
#define LFS_PIN_VISA                                (0x0004)
#define LFS_PIN_DES_OFFSET                          (0x0008)
#define LFS_PIN_BANKSYS                             (0x0010)

/* values of LFSPINCAPS.fwKey_Check_Modes and
          LFSPINIMPORTKEYEX.wKey_Check_Mode */

#define LFS_PIN_KCVNONE                             (0x0000)
#define LFS_PIN_KCVSELF                             (0x0001)
#define LFS_PIN_KCVZERO                             (0x0002)

/* values of LFSPINCAPS.fwAuto_Beep */

#define LFS_PIN_BEEP_ACTIVE_AVAILABLE               (0x0001)
#define LFS_PIN_BEEP_ACTIVE_SELECTABLE              (0x0002)
#define LFS_PIN_BEEP_INACTIVE_AVAILABLE             (0x0004)
#define LFS_PIN_BEEP_INACTIVE_SELECTABLE            (0x0008)

/* values of LFSPINCAPS.fwKey_Block_Import_Formats */

#define LFS_PIN_ANSTR31KEYBLOCK                     (0x0001)

/* values of LFSPINKEYDETAIL.fwUse and values of LFSPINKEYDETAILEX.dwUse */

#define LFS_PIN_USECRYPT                            (0x0001)
#define LFS_PIN_USEFUNCTION                         (0x0002)
#define LFS_PIN_USEMACING                           (0x0004)
#define LFS_PIN_USEKEYENCKEY                        (0x0020)
#define LFS_PIN_USENODUPLICATE                      (0x0040)
#define LFS_PIN_USESVENCKEY                         (0x0080)
#define LFS_PIN_USECONSTRUCT                        (0x0100)
#define LFS_PIN_USESECURECONSTRUCT                  (0x0200)
#define LFS_PIN_USEANSTR31MASTER                    (0x0400)

/* additional values for LFSPINKEYDETAILEX.dwUse */

#define LFS_PIN_USEPINLOCAL                         (0x00010000)
#define LFS_PIN_USERSAPUBLIC                        (0x00020000)
#define LFS_PIN_USERSAPRIVATE                       (0x00040000)
#define LFS_PIN_USECHIPINFO                         (0x00100000)
#define LFS_PIN_USECHIPPIN                          (0x00200000)
#define LFS_PIN_USECHIPPS                           (0x00400000)
#define LFS_PIN_USECHIPMAC                          (0x00800000)
#define LFS_PIN_USECHIPLT                           (0x01000000)
#define LFS_PIN_USECHIPMACLZ                        (0x02000000)
#define LFS_PIN_USECHIPMACAZ                        (0x04000000)
#define LFS_PIN_USERSAPUBLICVERIFY                  (0x08000000)
#define LFS_PIN_USERSAPRIVATESIGN                   (0x10000000)

/* values of LFSPINFUNCKEYDETAIL.ulFunc_Mask */

#define LFS_PIN_FK_0                                (0x00000001)
#define LFS_PIN_FK_1                                (0x00000002)
#define LFS_PIN_FK_2                                (0x00000004)
#define LFS_PIN_FK_3                                (0x00000008)
#define LFS_PIN_FK_4                                (0x00000010)
#define LFS_PIN_FK_5                                (0x00000020)
#define LFS_PIN_FK_6                                (0x00000040)
#define LFS_PIN_FK_7                                (0x00000080)
#define LFS_PIN_FK_8                                (0x00000100)
#define LFS_PIN_FK_9                                (0x00000200)
#define LFS_PIN_FK_ENTER                            (0x00000400)
#define LFS_PIN_FK_CANCEL                           (0x00000800)
#define LFS_PIN_FK_CLEAR                            (0x00001000)
#define LFS_PIN_FK_BACKSPACE                        (0x00002000)
#define LFS_PIN_FK_HELP                             (0x00004000)
#define LFS_PIN_FK_DECPOINT                         (0x00008000)
#define LFS_PIN_FK_00                               (0x00010000)
#define LFS_PIN_FK_000                              (0x00020000)
#define LFS_PIN_FK_RES1                             (0x00040000)
#define LFS_PIN_FK_RES2                             (0x00080000)
#define LFS_PIN_FK_RES3                             (0x00100000)
#define LFS_PIN_FK_RES4                             (0x00200000)
#define LFS_PIN_FK_RES5                             (0x00400000)
#define LFS_PIN_FK_RES6                             (0x00800000)
#define LFS_PIN_FK_RES7                             (0x01000000)
#define LFS_PIN_FK_RES8                             (0x02000000)
#define LFS_PIN_FK_OEM1                             (0x04000000)
#define LFS_PIN_FK_OEM2                             (0x08000000)
#define LFS_PIN_FK_OEM3                             (0x10000000)
#define LFS_PIN_FK_OEM4                             (0x20000000)
#define LFS_PIN_FK_OEM5                             (0x40000000)
#define LFS_PIN_FK_OEM6                             (0x80000000)

/* additional values of LFSPINFUNCKEYDETAIL.ulFunc_Mask */

#define LFS_PIN_FK_UNUSED                           (0x00000000)

#define LFS_PIN_FK_A                                LFS_PIN_FK_RES1
#define LFS_PIN_FK_B                                LFS_PIN_FK_RES2
#define LFS_PIN_FK_C                                LFS_PIN_FK_RES3
#define LFS_PIN_FK_D                                LFS_PIN_FK_RES4
#define LFS_PIN_FK_E                                LFS_PIN_FK_RES5
#define LFS_PIN_FK_F                                LFS_PIN_FK_RES6
#define LFS_PIN_FK_SHIFT                            LFS_PIN_FK_RES7

/* values of LFSPINFDK.ulFDK */

#define LFS_PIN_FK_FDK01                            (0x00000001)
#define LFS_PIN_FK_FDK02                            (0x00000002)
#define LFS_PIN_FK_FDK03                            (0x00000004)
#define LFS_PIN_FK_FDK04                            (0x00000008)
#define LFS_PIN_FK_FDK05                            (0x00000010)
#define LFS_PIN_FK_FDK06                            (0x00000020)
#define LFS_PIN_FK_FDK07                            (0x00000040)
#define LFS_PIN_FK_FDK08                            (0x00000080)
#define LFS_PIN_FK_FDK09                            (0x00000100)
#define LFS_PIN_FK_FDK10                            (0x00000200)
#define LFS_PIN_FK_FDK11                            (0x00000400)
#define LFS_PIN_FK_FDK12                            (0x00000800)
#define LFS_PIN_FK_FDK13                            (0x00001000)
#define LFS_PIN_FK_FDK14                            (0x00002000)
#define LFS_PIN_FK_FDK15                            (0x00004000)
#define LFS_PIN_FK_FDK16                            (0x00008000)
#define LFS_PIN_FK_FDK17                            (0x00010000)
#define LFS_PIN_FK_FDK18                            (0x00020000)
#define LFS_PIN_FK_FDK19                            (0x00040000)
#define LFS_PIN_FK_FDK20                            (0x00080000)
#define LFS_PIN_FK_FDK21                            (0x00100000)
#define LFS_PIN_FK_FDK22                            (0x00200000)
#define LFS_PIN_FK_FDK23                            (0x00400000)
#define LFS_PIN_FK_FDK24                            (0x00800000)
#define LFS_PIN_FK_FDK25                            (0x01000000)
#define LFS_PIN_FK_FDK26                            (0x02000000)
#define LFS_PIN_FK_FDK27                            (0x04000000)
#define LFS_PIN_FK_FDK28                            (0x08000000)
#define LFS_PIN_FK_FDK29                            (0x10000000)
#define LFS_PIN_FK_FDK30                            (0x20000000)
#define LFS_PIN_FK_FDK31                            (0x40000000)
#define LFS_PIN_FK_FDK32                            (0x80000000)

/* values of LFSPINCRYPT.wMode */

#define LFS_PIN_MODEENCRYPT                         (1)
#define LFS_PIN_MODEDECRYPT                         (2)
#define LFS_PIN_MODERANDOM                          (3)

/* values of LFSPINENTRY.wCompletion */

#define LFS_PIN_COMPAUTO                            (0)
#define LFS_PIN_COMPENTER                           (1)
#define LFS_PIN_COMPCANCEL                          (2)
#define LFS_PIN_COMPCONTINUE                        (6)
#define LFS_PIN_COMPCLEAR                           (7)
#define LFS_PIN_COMPBACKSPACE                       (8)
#define LFS_PIN_COMPFDK                             (9)
#define LFS_PIN_COMPHELP                            (10)
#define LFS_PIN_COMPFK                              (11)
#define LFS_PIN_COMPCONTFDK                         (12)

/* values of LFSPINSECMSG.wProtocol */

#define LFS_PIN_PROTISOAS                           (1)
#define LFS_PIN_PROTISOLZ                           (2)
#define LFS_PIN_PROTISOPS                           (3)
#define LFS_PIN_PROTCHIPZKA                         (4)
#define LFS_PIN_PROTRAWDATA                         (5)
#define LFS_PIN_PROTPBM                             (6)
#define LFS_PIN_PROTHSMLDI                          (7)
#define LFS_PIN_PROTGENAS                           (8)
#define LFS_PIN_PROTCHIPINCHG                       (9)
#define LFS_PIN_PROTPINCMP                          (10)
#define LFS_PIN_PROTISOPINCHG                       (11)

/* values of LFSPINHSMINIT.wInit_Mode. */

#define LFS_PIN_INITTEMP                            (1)
#define LFS_PIN_INITDEFINITE                        (2)
#define LFS_PIN_INITIRREVERSIBLE                    (3)

/* values of LFSPINENCIO.wProtocol and LFSPINCAPS.fwPINENCIO_Protocols */ 

#define LFS_PIN_ENC_PROT_CH                         (0x0001) 
#define LFS_PIN_ENC_PROT_GIECB                      (0x0002) 
#define LFS_PIN_ENC_PROT_LUX                        (0x0004) 
#define LFS_PIN_ENC_PROT_CHN                          (0x0008)

/* values for LFS_SRVE_PIN_CERTIFICATE_CHANGE and LFSPINSTATUS.dwCertificate_State */

#define LFS_PIN_CERT_SECONDARY                      (0x00000002)

/* values for LFSPINSTATUS.dwCertificateState*/

#define LFS_PIN_CERT_UNKNOWN                        (0x00000000)
#define LFS_PIN_CERT_PRIMARY                        (0x00000001)
#define LFS_PIN_CERT_NOTREADY                       (0x00000004)

/* Values for LFSPINCAPS.dwRSA_Authentication_Scheme and the fast-track Capabilities 
lpszExtra parameter, REMOTE_KEY_SCHEME. */

#define LFS_PIN_RSA_AUTH_2PARTY_SIG                 (0x00000001)
#define LFS_PIN_RSA_AUTH_3PARTY_CERT                (0x00000002)

/* Values for LFSPINCAPS.dwSignature_Scheme and the fast-track Capabilities lpzExtra parameter, SIGNATURE_CAPABILITIES. */

#define LFS_PIN_SIG_GEN_RSA_KEY_PAIR                (0x00000001)
#define LFS_PIN_SIG_RANDOM_NUMBER                   (0x00000002)
#define LFS_PIN_SIG_EXPORT_EPP_ID                   (0x00000004)
#define LFS_PIN_SIG_ENHANCED_RKL                    (0x00000008)

/* values of LFSPINIMPORTRSAPUBLICKEY.dwRSA_Signature_Algorithm and 
LFSPINCAPS.dwRSA_Signature_Algorithm */

#define LFS_PIN_SIGN_NA                             (0)
#define LFS_PIN_SIGN_RSASSA_PKCS1_V1_5              (0x00000001)
#define LFS_PIN_SIGN_RSASSA_PSS                     (0x00000002)

/* values of LFSPINIMPORTRSAPUBLICKEYOUTPUT.dwRSAKey_Check_Mode */

#define LFS_PIN_RSA_KCV_NONE                        (0x00000000)
#define LFS_PIN_RSA_KCV_SHA1                        (0x00000001)
#define LFS_PIN_RSA_KCV_SHA256                      (0x00000002)

/* values of LFSPINEXPORTRSAISSUERSIGNEDITEM.wExport_Item_Type and */
/*           LFSPINEXPORTRSAEPPSIGNEDITEM.wExport_Item_Type        */

#define LFS_PIN_EXPORT_EPP_ID                       (0x0001)
#define LFS_PIN_EXPORT_PUBLIC_KEY                   (0x0002)

/* values of LFSPINIMPORTRSASIGNEDDESKEY.dwRSA_Encipher_Algorithm and 
LFSPINCAPS.dwRSACryptAlgorithm */

#define LFS_PIN_CRYPT_RSAES_PKCS1_V1_5              (0x00000001)
#define LFS_PIN_CRYPT_RSAES_OAEP                    (0x00000002)

/* values of LFSPINGENERATERSAKEYPAIR.wExponent_Value */

#define LFS_PIN_DEFAULT                             (0)
#define LFS_PIN_EXPONENT_1                          (1)
#define LFS_PIN_EXPONENT_4                          (2)
#define LFS_PIN_EXPONENT_16                         (3)

/* values of LFSPINCAPS.wDESKey_Length,                        */
/*   LFSPINIMPORTRSASIGNEDDESKEYOUTPUT.wKey_Length and         */
/*   LFSPINIMPORTRSAENCIPHEREDPKCS7KEYOUTPUT.wKey_Length       */

#define LFS_PIN_KEYSINGLE                           (0x0001)
#define LFS_PIN_KEYDOUBLE                           (0x0002)

/* values of LFSPINGETCERTIFICATE.wGet_Certificate and
LFSPINCAPS.wCertificate_Types */

#define LFS_PIN_PUBLICENCKEY                        (0x0001)
#define LFS_PIN_PUBLICVERIFICATIONKEY               (0x0002)

/* values for LFSPINEMVIMPORTPUBLICKEY.wImport_Scheme 
and LFSPINCAPS.lpwEMV_Import_Schemes */

#define LFS_PIN_EMV_IMPORT_PLAIN_CA                 (1)
#define LFS_PIN_EMV_IMPORT_CHKSUM_CA                (2)
#define LFS_PIN_EMV_IMPORT_EPI_CA                   (3)
#define LFS_PIN_EMV_IMPORT_ISSUER                   (4)
#define LFS_PIN_EMV_IMPORT_ICC                      (5)
#define LFS_PIN_EMV_IMPORT_ICC_PIN                  (6)
#define LFS_PIN_EMV_IMPORT_PKCSV1_5_CA              (7)

/* values for LFSPINDIGEST.wHash_Algorithm and LFSPINCAPS.fwEMV_Hash_Algorithm */

#define LFS_PIN_HASH_SHA1_DIGEST                    (0x0001)
#define LFS_PIN_HASH_SHA256_DIGEST                  (0x0002)

/* values of LFSPINSECUREKEYDETAIL.fwKey_Entry_Mode */

#define LFS_PIN_SECUREKEY_NOTSUPP                   (0x0000)
#define LFS_PIN_SECUREKEY_REG_SHIFT                 (0x0001)
#define LFS_PIN_SECUREKEY_REG_UNIQUE                (0x0002)
#define LFS_PIN_SECUREKEY_IRREG_SHIFT               (0x0004)
#define LFS_PIN_SECUREKEY_IRREG_UNIQUE              (0x0008)

/* PIN Errors */

#define LFS_ERR_PIN_KEYNOTFOUND                     (-(PIN_SERVICE_OFFSET + 0))
#define LFS_ERR_PIN_MODENOTSUPPORTED                (-(PIN_SERVICE_OFFSET + 1))
#define LFS_ERR_PIN_ACCESSDENIED                    (-(PIN_SERVICE_OFFSET + 2))
#define LFS_ERR_PIN_INVALIDID                       (-(PIN_SERVICE_OFFSET + 3))
#define LFS_ERR_PIN_DUPLICATEKEY                    (-(PIN_SERVICE_OFFSET + 4))
#define LFS_ERR_PIN_KEYNOVALUE                      (-(PIN_SERVICE_OFFSET + 6))
#define LFS_ERR_PIN_USEVIOLATION                    (-(PIN_SERVICE_OFFSET + 7))
#define LFS_ERR_PIN_NOPIN                           (-(PIN_SERVICE_OFFSET + 8))
#define LFS_ERR_PIN_INVALIDKEYLENGTH                (-(PIN_SERVICE_OFFSET + 9))
#define LFS_ERR_PIN_KEYINVALID                      (-(PIN_SERVICE_OFFSET + 10))
#define LFS_ERR_PIN_KEYNOTSUPPORTED                 (-(PIN_SERVICE_OFFSET + 11))
#define LFS_ERR_PIN_NOACTIVEKEYS                    (-(PIN_SERVICE_OFFSET + 12))
#define LFS_ERR_PIN_NOTERMINATEKEYS                 (-(PIN_SERVICE_OFFSET + 14))
#define LFS_ERR_PIN_MINIMUMLENGTH                   (-(PIN_SERVICE_OFFSET + 15))
#define LFS_ERR_PIN_PROTOCOLNOTSUPP                 (-(PIN_SERVICE_OFFSET + 16))
#define LFS_ERR_PIN_INVALIDDATA                     (-(PIN_SERVICE_OFFSET + 17))
#define LFS_ERR_PIN_NOTALLOWED                      (-(PIN_SERVICE_OFFSET + 18))
#define LFS_ERR_PIN_NOKEYRAM                        (-(PIN_SERVICE_OFFSET + 19))
#define LFS_ERR_PIN_NOCHIPTRANSACTIVE               (-(PIN_SERVICE_OFFSET + 20))
#define LFS_ERR_PIN_ALGORITHMNOTSUPP                (-(PIN_SERVICE_OFFSET + 21))
#define LFS_ERR_PIN_FORMATNOTSUPP                   (-(PIN_SERVICE_OFFSET + 22))
#define LFS_ERR_PIN_HSMSTATEINVALID                 (-(PIN_SERVICE_OFFSET + 23))
#define LFS_ERR_PIN_MACINVALID                      (-(PIN_SERVICE_OFFSET + 24))
#define LFS_ERR_PIN_PROTINVALID                     (-(PIN_SERVICE_OFFSET + 25))
#define LFS_ERR_PIN_FORMATINVALID                   (-(PIN_SERVICE_OFFSET + 26))
#define LFS_ERR_PIN_CONTENTINVALID                  (-(PIN_SERVICE_OFFSET + 27))
#define LFS_ERR_PIN_SIG_NOT_SUPP                    (-(PIN_SERVICE_OFFSET + 29))
#define LFS_ERR_PIN_INVALID_MOD_LEN                 (-(PIN_SERVICE_OFFSET + 31))
#define LFS_ERR_PIN_INVALIDCERTSTATE                (-(PIN_SERVICE_OFFSET + 32))
#define LFS_ERR_PIN_KEY_GENERATION_ERROR            (-(PIN_SERVICE_OFFSET + 33))
#define LFS_ERR_PIN_EMV_VERIFY_FAILED               (-(PIN_SERVICE_OFFSET + 34))
#define LFS_ERR_PIN_RANDOMINVALID                   (-(PIN_SERVICE_OFFSET + 35))
#define LFS_ERR_PIN_SIGNATUREINVALID                (-(PIN_SERVICE_OFFSET + 36))
#define LFS_ERR_PIN_SNSCDINVALID                    (-(PIN_SERVICE_OFFSET + 37))
#define LFS_ERR_PIN_NORSAKEYPAIR                    (-(PIN_SERVICE_OFFSET + 38))
#define LFS_ERR_PIN_INVALID_PORT                    (-(PIN_SERVICE_OFFSET + 39))
#define LFS_ERR_PIN_POWERSAVETOOSHORT               (-(PIN_SERVICE_OFFSET + 40))
#define LFS_ERR_PIN_INVALIDHSM                      (-(PIN_SERVICE_OFFSET + 41))
#define LFS_ERR_PIN_TOOMANYFRAMES                   (-(PIN_SERVICE_OFFSET + 42))
#define LFS_ERR_PIN_PARTIALFRAME                    (-(PIN_SERVICE_OFFSET + 43))
#define LFS_ERR_PIN_MISSINGKEYS                     (-(PIN_SERVICE_OFFSET + 44))
#define LFS_ERR_PIN_FRAMECOORD                      (-(PIN_SERVICE_OFFSET + 45))
#define LFS_ERR_PIN_KEYCOORD                        (-(PIN_SERVICE_OFFSET + 46))
#define LFS_ERR_PIN_FRAMEOVERLAP                    (-(PIN_SERVICE_OFFSET + 47))
#define LFS_ERR_PIN_KEYOVERLAP                      (-(PIN_SERVICE_OFFSET + 48))
#define LFS_ERR_PIN_TOOMANYKEYS                     (-(PIN_SERVICE_OFFSET + 49))
#define LFS_ERR_PIN_KEYALREADYDEFINED               (-(PIN_SERVICE_OFFSET + 50))
#define LFS_ERR_PIN_COMMANDUNSUPP                   (-(PIN_SERVICE_OFFSET + 51))
#define LFS_ERR_PIN_SYNCHRONIZEUNSUPP               (-(PIN_SERVICE_OFFSET + 52))
#define LFS_ERR_PIN_SIGNATUREERROR                  (-(PIN_SERVICE_OFFSET + 53))
#define LFS_ERR_PIN_NOPRIVATEKEY                    (-(PIN_SERVICE_OFFSET + 54))
#define LFS_ERR_PIN_NOSM2KEYPAIR                    (-(PIN_SERVICE_OFFSET + 55))

/* values of LFSPINCHNDIGESTIN.wHash_Algorithm */
#define LFS_PIN_HASH_SM3_DIGEST                    (0x0001)

/* values for LFSPINCHNIMPORTSM2PUBLICKEYIN.dwUse */
#define LFS_PIN_USESM2PUBLIC                       (0x00000001)
#define LFS_PIN_USESM2PUBLICVERIFY                 (0x00000002)

/* values of LFSPINCHNIMPORTSM2PUBLICKEYIN.dwSM2_Signature_Algorithm,
PINCHNEXPORTSM2ISSUERSIGNEDITEMOUT.dwSM2_Signature_Algorithm,
PINCHNEXPORTSM2EPPSIGNEDITEMIN.dwSignature_Algorithm and
PINCHNIMPORTSM2SIGNEDSM4KEY.dwSM2_Signature_Algorithm */
#define LFS_PIN_SIGN_SM2_SIGN_NA                   (0)
#define LFS_PIN_SIGN_SM2_GM_T_2012                 (0x00000001)

/* values for LFSPINCHNIMPORTSM2PUBLICKEYOUT.dwSM2_Key_Check_Mode */
#define LFS_PIN_SM2_KCV_NONE                       (0x00000001)
#define LFS_PIN_SM2_KCV_SM3                        (0x00000002)

/* values for LFSPINCHNGENERATESM2KEYOUT.dwUse */
#define LFS_PIN_USESM2PRIVATE                      (0x00000001)
#define LFS_PIN_USESM2PRIVATESIGN                  (0x00000002)

/*=================================================================*/
/* PIN Info Command Structures and variables */
/*=================================================================*/
typedef struct _lfs_hex_data
{
USHORT	usLength;
LPBYTE	lpbData;
} LFSXDATA, *LPLFSXDATA;

typedef struct _lfs_pin_status
{
WORD	wDevice;
WORD	wEnc_Stat;
LPSTR	lpstrExtra;
DWORD	                     dwGuid_Lights[LFS_PIN_GUIDLIGHTS_SIZE]; 
WORD	    wAuto_Beep_Mode; 
DWORD	        dwCertificate_State; 
WORD	      wDevice_Position; 
USHORT	               usPower_Save_Recovery_Time;  
} LFSPINSTATUS, * LPLFSPINSTATUS;

typedef struct _lfs_pin_caps
{
WORD	wClass;
WORD	wType;
BOOL	   bCompound;
USHORT	   usKey_Num;
WORD	    wAlgorithms;
WORD	      wPin_Formats;
WORD	                wDerivation_Algorithms;
WORD	                  wPresentation_Algorithms;
WORD	  wDisplay;
BOOL	    bID_Connect;
WORD	wID_Key;
WORD	               wValidation_Algorithms;
WORD	         wKey_Check_Modes;
LPSTR	  lpstrExtra;
DWORD	                       dwGuid_Lights[LFS_PIN_GUIDLIGHTS_SIZE];
BOOL	                  bPIN_Can_Persist_After_Use;
WORD	  wAuto_Beep;
LPSTR	       lpstrHSM_Vendor; 
BOOL	       bHSM_Journaling;
DWORD	                   dwRSA_Authentication_Scheme; 
DWORD	                 dwRSA_Signature_Algorithm; 
DWORD	             dwRSA_Crypt_Algorithm;
DWORD	            dwRSA_Key_Check_Mode; 
DWORD	          dwSignature_Scheme; 
LPWORD	             lpwEMV_Import_Schemes;
WORD	           wEMV_Hash_Algorithm;
BOOL	                 bKey_Import_Through_Parts;
WORD	         wENC_IO_Protocols;
BOOL	      bType_Combined;
BOOL	                   bSet_Pinblock_Data_Required; 
WORD	                 wKey_Block_Import_Formats; 
BOOL	            bPower_Save_Control;
} LFSPINCAPS, * LPLFSPINCAPS;

typedef struct _lfs_pin_key_detail
{
LPSTR         lpstrKey_Name;
WORD          wUse;
BOOL          bLoaded;
LPLFSXDATA    lpxKey_Block_Header;
} LFSPINKEYDETAIL, * LPLFSPINKEYDETAIL;

typedef struct _lfs_pin_fdk
{
    ULONG                  ulFDK;
    USHORT                 usXPosition;
    USHORT                 usYPosition;
} LFSPINFDK, *LPLFSPINFDK;

typedef struct _lfs_pin_func_key_detail
{
    ULONG                  ulFunc_Mask;
    USHORT                 usNumber_FDKs;
    LPLFSPINFDK           *lppFDKs;
} LFSPINFUNCKEYDETAIL, *LPLFSPINFUNCKEYDETAIL;

typedef struct _lfs_pin_key_detail_ex
{
    LPSTR                  lpsKey_Name;
    DWORD                  dwUse;
    BYTE                   bGeneration;
    BYTE                   bVersion;
    BYTE                   bActivating_Date[4];
    BYTE                   bExpiry_Date[4];
    BOOL                   bLoaded;
    LPLFSXDATA            lpxKey_Block_Header;
} LFSPINKEYDETAILEX, *LPLFSPINKEYDETAILEX;

/* LFS_INF_PIN_SECUREKEY_DETAIL command key layout output structure */
typedef struct _lfs_pin_hex_keys
{
    USHORT                 usX_Pos;
    USHORT                 usY_Pos;
    USHORT                 usX_Size;
    USHORT                 usY_Size;
    ULONG                  ulFK;
    ULONG                  ulShift_FK;
} LFSPINHEXKEYS, *LPLFSPINHEXKEYS;

/* LFS_INF_PIN_SECUREKEY_DETAIL command output structure */
typedef struct _lfs_pin_secure_key_detail
{
    WORD                   fwKey_Entry_Mode;
    LPLFSPINFUNCKEYDETAIL  lpFunc_Key_Detail;
    ULONG                  ulClear_FDK;
    ULONG                  ulCancel_FDK;
    ULONG                  ulBackspace_FDK;
    ULONG                  ulEnter_FDK;
    WORD                   wColumns;
    WORD                   wRows;
    LPLFSPINHEXKEYS       *lppHex_Keys;
} LFSPINSECUREKEYDETAIL, *LPLFSPINSECUREKEYDETAIL;

/*=================================================================*/
/* PIN Execute Command Structures */
/*=================================================================*/
typedef struct _lfs_pin_crypt
{
WORD	wMode;
LPSTR	   lpstrKey;
LPLFSXDATA	        lpxKey_EncKey;
    WORD	     wAlgorithm;
    LPSTR	              lpstrStart_ValueKey;
    LPLFSXDATA	         lpxStart_Value;
    BYTE	   bPadding;
    BYTE	       bCompression;
    LPLFSXDATA                   lpxCrypt_Data;
} LFSPINCRYPT, *LPLFSPINCRYPT;

typedef struct _lfs_pin_import
{
    LPSTR	lpstrKey;
    LPSTR	    lpstrEnc_Key;
    LPLFSXDATA	lpxIdent;
    LPLFSXDATA	lpxValue;
    WORD                       wUse;
} LFSPINIMPORT, * LPLFSPINIMPORT;

typedef struct _lfs_pin_derive
{
    WORD                  wDerivation_Algorithm;
    LPSTR                 lpsKey;
    LPSTR                 lpsKey_Gen_Key;
    LPSTR                 lpsStart_Value_Key;
    LPLFSXDATA            lpxStart_Value;
    BYTE                  bPadding;
    LPLFSXDATA            lpxInput_Data;
    LPLFSXDATA            lpxIdent;
 } LFSPINDERIVE, *LPLFSPINDERIVE;

typedef struct _lfs_pin_getpin
{
USHORT	usMin_Len;
USHORT	usMax_Len;
BOOL	bAuto_End;
CHAR                       cEcho;
ULONG	    ulActive_FDKs;
ULONG	    ulActive_Keys;
ULONG	       ulTerminate_FDKs;
ULONG	       ulTerminate_Keys;
} LFSPINGETPIN, * LPLFSPINGETPIN;

typedef struct _lfs_pin_entry
{
USHORT	usDigits;
WORD	   wCompletion;
} LFSPINENTRY, * LPLFSPINENTRY;

typedef struct _lfs_pin_local_des
{
    LPSTR                  lpsValidation_Data;
    LPSTR                  lpsOffset;
    BYTE                   bPadding;
    USHORT                 usMax_PIN;
    USHORT                 usVal_Digits;
    BOOL                   bNo_Leading_Zero;
    LPSTR                  lpsKey;
    LPLFSXDATA             lpxKey_Enc_Key;
    LPSTR                  lpsDec_Table;
} LFSPINLOCALDES, *LPLFSPINLOCALDES;

typedef struct _lfs_pin_create_offset
{
    LPSTR                 lpsValidation_Data;
    BYTE                  bPadding;
    USHORT                usMax_PIN;
    USHORT                usVal_Digits;
    LPSTR                 lpsKey;
    LPLFSXDATA            lpxKey_EncKey;
    LPSTR                  lpsDec_Table;
} LFSPINCREATEOFFSET, *LPLFSPINCREATEOFFSET;

typedef struct _lfs_pin_local_eurocheque
{
    LPSTR                  lpsEurocheque_Data;
    LPSTR                  lpsPVV;
    WORD                   wFirst_Enc_Digits;
    WORD                   wFirst_Enc_Offset;
    WORD                   wPVV_Digits;
    WORD                   wPVV_Offset;
    LPSTR                  lpsKey;
    LPLFSXDATA             lpxKey_Enc_Key;
    LPSTR                  lpsDec_Table;
} LFSPINLOCALEUROCHEQUE, *LPLFSPINLOCALEUROCHEQUE;

typedef struct _lfs_pin_local_visa
{
    LPSTR                  lpsPAN;
    LPSTR                  lpsPVV;
    WORD                   wPVV_Digits;
    LPSTR                  lpsKey;
    LPLFSXDATA            lpxKey_Enc_Key;
} LFSPINLOCALVISA, *LPLFSPINLOCALVISA;

typedef struct _lfs_pin_present_idc
{
    WORD                   wPresent_Algorithm;
    WORD                   wChip_Protocol;
    ULONG                  ulChip_Data_Length;
    LPBYTE                 lpbChip_Data;
    LPVOID                 lpAlgorithm_Data;
} LFSPINPRESENTIDC, *LPLFSPINPRESENTIDC;

typedef struct _lfs_pin_present_result
{
    WORD                   wChip_Protocol;
    ULONG                  ulChip_Data_Length;
    LPBYTE                 lpbChip_Data;
} LFSPINPRESENTRESULT, *LPLFSPINPRESENTRESULT;

typedef struct _lfs_pin_present_clear
{
    ULONG                  ulPIN_Pointer;
    USHORT                 usPIN_Offset;
} LFSPINPRESENTCLEAR, *LPLFSPINPRESENTCLEAR;

typedef struct _lfs_pin_block
{
LPSTR	          lpstrCustomer_Data;
LPSTR	     lpstrXOR_Data;
BYTE	 bPadding;
WORD	wFormat;
LPSTR                       lpstrKey;
LPSTR	        lpstrKey_EncKey;
} LFSPINBLOCK,*LPLFSPINBLOCK;

typedef struct _lfs_pin_get_data
{
USHORT	usMax_Len;
BOOL	bAuto_End;
ULONG	    ulActive_FDKs;
ULONG	    ulActive_Keys;
ULONG	        ulTerminate_FDKs;
ULONG	        ulTerminate_Keys;
} LFSPINGETDATA, *LPLFSPINGETDATA;


typedef struct _lfs_pin_key
{
WORD	    wCompletion;
ULONG	ulDigit;
} LFSPINKEY, *LPLFSPINKEY;

typedef struct _lfs_pin_data
{
USHORT                      usKeys;
LPLFSPINKEY	    *lpPin_Keys;
WORD	    wCompletion;
} LFSPINDATA, *LPLFSPINDATA;

typedef struct _lfs_pin_init
{
LPLFSXDATA	    lpxIdent;
LPLFSXDATA                   lpxKey;
} LFSPININIT, *LPLFSPININIT;

typedef struct _lfs_pin_local_banksys
{
    LPLFSXDATA             lpxATMVAC;
} LFSPINLOCALBANKSYS, *LPLFSPINLOCALBANKSYS;

typedef struct _lfs_pin_banksys_io
{
    ULONG                  ulLength;
    LPBYTE                 lpbData;
} LFSPINBANKSYSIO, *LPLFSPINBANKSYSIO;

typedef struct _lfs_pin_secure_message
{
    WORD                   wProtocol;
    ULONG                  ulLength;
    LPBYTE                 lpbMsg;
} LFSPINSECMSG, *LPLFSPINSECMSG;

typedef struct _lfs_pin_import_key_ex
{
LPSTR               lpstrKey;
LPSTR               lpstrEnc_Key;
LPLFSXDATA          lpxValue;
LPLFSXDATA          lpxControl_Vector;
DWORD               dwUse;
WORD                wKey_Check_Mode;
LPLFSXDATA         lpxKey_Check_Value;
} LFSPINIMPORTKEYEX, *LPLFSPINIMPORTKEYEX;

typedef struct _lfs_pin_enc_io 
{ 
WORD                    wProtocol; 
ULONG                   ulDataLength; 
LPVOID                  lpvData; 
} LFSPINENCIO, *LPLFSPINENCIO; 

/* LFS_CMD_PIN_SECUREKEY_ENTRY command input structure */
typedef struct _lfs_pin_secure_key_entry
{
USHORT                     usKey_Len;
BOOL                       bAuto_End;
ULONG                      ulActive_FDKs;
ULONG                      ulActive_Keys;
ULONG                      ulTerminate_FDKs;
ULONG                      ulTerminate_Keys;
WORD                       wVerification_Type;
} LFSPINSECUREKEYENTRY, *LPLFSPINSECUREKEYENTRY;

/* LFS_CMD_PIN_SECUREKEY_ENTRY command output structure */
typedef struct _lfs_pin_secure_key_entry_out
{
    USHORT                     usDigits;
    WORD                       wCompletion;
    LPLFSXDATA                 lpxKCV;
} LFSPINSECUREKEYENTRYOUT, *LPLFSPINSECUREKEYENTRYOUT;

/* LFS_CDM_PIN_IMPORT_KEYBLOCK command input structure */
typedef struct _lfs_pin_import_key_block
{
    LPSTR                  lpstrKey;
    LPSTR                  lpsEnc_Key;
    LPLFSXDATA             lpxKey_Block;
} LFSPINIMPORTKEYBLOCK, *LPLFSPINIMPORTKEYBLOCK;

typedef struct _lfs_pin_import_rsa_public_key
{
LPSTR                    lpstrKey;
LPLFSXDATA               lpxValue;
DWORD                    dwUse;
LPSTR	lpstrSig_Key;
DWORD	             dwRSA_Signature_Algorithm;
LPLFSXDATA	lpxSignature;
} LFSPINIMPORTRSAPUBLICKEY, *LPLFSPINIMPORTRSAPUBLICKEY;

typedef struct _lfs_pin_import_rsa_public_key_output
{
DWORD	 dwRSA_Key_Check_Mode;
LPLFSXDATA	lpxKey_Check_Value;
} LFSPINIMPORTRSAPUBLICKEYOUTPUT,*LPLFSPINIMPORTRSAPUBLICKEYOUTPUT;

typedef struct _lfs_pin_export_rsa_issuer_signed_item
{
WORD	        wExport_Item_Type;
LPSTR	lpstrName;
} LFSPINEXPORTRSAISSUERSIGNEDITEM,*LPLFSPINEXPORTRSAISSUERSIGNEDITEM;

typedef struct _lfs_pin_export_rsa_issuer_signed_item_output
{
LPLFSXDATA               lpxValue;
DWORD	            dwRSA_Signature_Algorithm;
LPLFSXDATA	lpxSignature;
} LFSPINEXPORTRSAISSUERSIGNEDITEMOUTPUT,*LPLFSPINEXPORTRSAISSUERSIGNEDITEMOUTPUT;

typedef struct _lfs_pin_import_rsa_signed_des_key
{
LPSTR                  lpstrKey;
LPSTR	lpstrDecrypt_Key;
DWORD                  dwRSA_Encipher_Algorithm;
LPLFSXDATA             lpxValue;
DWORD                  dwUse;
LPSTR                  lpstrSig_Key;
DWORD	        dwRSA_Signature_Algorithm;
LPLFSXDATA             lpxSignature;
} LFSPINIMPORTRSASIGNEDDESKEY, *LPLFSPINIMPORTRSASIGNEDDESKEY;

typedef struct _lfs_pin_import_rsa_signed_des_key_output
{
WORD                    wKey_Length;
WORD	wKey_Check_Mode;
LPLFSXDATA	  lpxKey_Check_Value;
} LFSPINIMPORTRSASIGNEDDESKEYOUTPUT,*LPLFSPINIMPORTRSASIGNEDDESKEYOUTPUT;

typedef struct _lfs_pin_generate_rsa_key
{
LPSTR                   lpstrKey;
DWORD                   dwUse;
WORD	wModulus_Length;
WORD	wExponent_Value;
} LFSPINGENERATERSAKEYPAIR, *LPLFSPINGENERATERSAKEYPAIR;

typedef struct _lfs_pin_export_rsa_epp_signed_item
{
WORD	wExport_Item_Type;
LPSTR                 lpstrName;
LPSTR                 lpstrSig_Key;
DWORD	    dwSignature_Algorithm;
} LFSPINEXPORTRSAEPPSIGNEDITEM, *LPLFSPINEXPORTRSAEPPSIGNEDITEM;

typedef struct _lfs_pin_export_rsa_epp_signed_item_output
{
LPLFSXDATA                 lpxValue;
LPLFSXDATA	        lpxSelf_Signature;
LPLFSXDATA                 lpxSignature;
} LFSPINEXPORTRSAEPPSIGNEDITEMOUTPUT,*LPLFSPINEXPORTRSAEPPSIGNEDITEMOUTPUT;

typedef struct _lfs_pin_load_certificate
{
    LPLFSXDATA             lpxLoad_Certificate;
} LFSPINLOADCERTIFICATE, *LPLFSPINLOADCERTIFICATE;

typedef struct _lfs_pin_load_certificate_output
{
    LPLFSXDATA             lpxCertificate_Data;
} LFSPINLOADCERTIFICATEOUTPUT, *LPLFSPINLOADCERTIFICATEOUTPUT;

typedef struct _lfs_pin_get_certificate
{
    WORD                   wGet_Certificate;
} LFSPINGETCERTIFICATE, *LPLFSPINGETCERTIFICATE;

typedef struct _lfs_pin_get_certificate_output
{
    LPLFSXDATA             lpxCertificate;
} LFSPINGETCERTIFICATEOUTPUT, *LPLFSPINGETCERTIFICATEOUTPUT;

typedef struct _lfs_pin_replace_certificate
{
    LPLFSXDATA             lpxReplace_Certificate;
} LFSPINREPLACECERTIFICATE, *LPLFSPINREPLACECERTIFICATE;

typedef struct _lfs_pin_replace_certificate_output
{
   LPLFSXDATA              lpxNew_Certificate_Data;
} LFSPINREPLACECERTIFICATEOUTPUT, *LPLFSPINREPLACECERTIFICATEOUTPUT;

typedef struct _lfs_pin_start_key_exchange
{
LPLFSXDATA	 lpxRandom_Item;
} LFSPINSTARTKEYEXCHANGE, *LPLFSPINSTARTKEYEXCHANGE;

typedef struct _lfs_pin_import_rsa_enciphered_pkcs7_key
{
    LPLFSXDATA             lpxImportRSA_Key_In;
    LPSTR                  lpstrKey;
    DWORD                  dwUse;
} LFSPINIMPORTRSAENCIPHEREDPKCS7KEY, *LPLFSPINIMPORTRSAENCIPHEREDPKCS7KEY;

typedef struct _lfs_pin_import_rsa_enciphered_pkcs7_key_output
{
    WORD                   wKey_Length;
    LPLFSXDATA            lpxRSA_Data;
}LFSPINIMPORTRSAENCIPHEREDPKCS7KEYOUTPUT, *LPLFSPINIMPORTRSAENCIPHEREDPKCS7KEYOUTPUT;

typedef struct _lfs_pin_emv_import_public_key
{
    LPSTR                  lpstrKey;
    DWORD                  dwUse;
    WORD                   wImport_Scheme;
    LPLFSXDATA             lpxImport_Data;
    LPSTR                  lpsSig_Key;
} LFSPINEMVIMPORTPUBLICKEY, *LPLFSPINEMVIMPORTPUBLICKEY;
typedef struct _lfs_pin_emv_import_public_key_output
{
    LPSTR                  lpsExpiry_Date;
} LFSPINEMVIMPORTPUBLICKEYOUTPUT, *LPLFSPINEMVIMPORTPUBLICKEYOUTPUT;

typedef struct _lfs_pin_digest
{
    WORD                   wHash_Algorithm;
    LPLFSXDATA             lpxDigest_Input;
} LFSPINDIGEST, *LPLFSPINDIGEST;

typedef struct _lfs_pin_digest_output
{
    LPLFSXDATA            lpxDigest_Output;
} LFSPINDIGESTOUTPUT, *LPLFSPINDIGESTOUTPUT;

typedef struct _lfs_pin_hsm_init
{
    WORD                   wInit_Mode;
    LPLFSXDATA            lpxOnline_Time;
} LFSPINHSMINIT, *LPLFSPINHSMINIT;

typedef struct _lfs_pin_generate_KCV
{
    LPSTR                  lpstrKey;
    WORD                   wKey_Check_Mode;
} LFSPINGENERATEKCV, *LPLFSPINGENERATEKCV;

typedef struct _lfs_pin_kcv
{
    LPLFSXDATA             lpxKCV;
} LFSPINKCV, *LPLFSPINKCV;

typedef struct _lfs_pin_set_guid_light
{
    WORD                   wGuid_Light;
    DWORD                  dwCommand;
} LFSPINSETGUIDLIGHT, *LPLFSPINSETGUIDLIGHT;

typedef struct _lfs_pin_maintain_pin
{
    BOOL                   bMaintain_PIN;
} LFSPINMAINTAINPIN, *LPLFSPINMAINTAINPIN;

typedef struct _lfs_pin_hsm_info
{
    WORD                   wHSM_Serial_Number;
    LPSTR                  lpsZKAID;
} LFSPINHSMINFO, *LPLFSPINHSMINFO;

typedef struct _lfs_pin_hsm_detail
{
    WORD                   wActive_Logical_HSM;
    LPLFSPINHSMINFO       *lppHSM_Info;
} LFSPINHSMDETAIL, *LPLFSPINHSMDETAIL;


typedef struct _lfs_pin_hsm_identifier
{
    WORD                   wHSM_Serial_Number;
} LFSPINHSMIDENTIFIER, *LPLFSPINHSMIDENTIFIER;

typedef struct _lfs_pin_power_save_control
{
    USHORT                 usMax_Power_Save_Recovery_Time;
} LFSPINPOWERSAVECONTROL, *LPLFSPINPOWERSAVECONTROL;


typedef struct _lfs_pin_block_ex
{  
LPSTR                lpstrCustomer_Data;
LPSTR                lpstrXOR_Data;
BYTE                 bPadding;
DWORD                dwFormat;
LPSTR                lpstrKey;
LPSTR                lpstrKey_EncKey;
DWORD                dwAlgorithm;
} LFSPINBLOCKEX, *LPLFSPINBLOCKEX;

typedef struct _lfs_pin_load_certificate_ex
{
    DWORD                  dwLoad_Option;
    DWORD                  dwSigner;
    LPLFSXDATA            lpxCertificate_Data;
} LFSPINLOADCERTIFICATEEX, *LPLFSPINLOADCERTIFICATEEX;

typedef struct _lfs_pin_load_certificate_ex_output
{
    DWORD                  dwRSA_Key_Check_Mode;
    LPLFSXDATA            lpxRSA_Data;
} LFSPINLOADCERTIFICATEEXOUTPUT, *LPLFSPINLOADCERTIFICATEEXOUTPUT;

typedef struct _lfs_pin_import_rsa_enciphered_pkcs7_key_ex
{
    LPLFSXDATA            lpxImport_RSA_Key_In;
    LPSTR                  lpstrKey;
    DWORD                  dwUse;
    DWORD                  dwCRKL_Load_Option;
} LFSPINIMPORTRSAENCIPHEREDPKCS7KEYEX, *LPLFSPINIMPORTRSAENCIPHEREDPKCS7KEYEX;

typedef struct _lfs_pin_import_rsa_enciphered_pkcs7_key_ex_output
{
    WORD                   wKey_Length;
    DWORD                  dwRSA_Key_Check_Mode;
    LPLFSXDATA             lpxRSA_Data;
    WORD                   wKeyCheck_Mode;
    LPLFSXDATA             lpxKey_Check_Value;
}LFSPINIMPORTRSAENCIPHEREDPKCS7KEYEXOUTPUT,*LPLFSPINIMPORTRSAENCIPHEREDPKCS7KEYEXOUTPUT;

typedef struct _lfs_pin_chn_digest
{
    WORD                   wHash_Algorithm;
    LPLFSXDATA             lpxDigest_Input;
} LFSPINCHNDIGEST, *LPLFSPINCHNDIGEST;

typedef struct _lfs_pin_chn_digest_output
{
LPLFSXDATA              lpxDigest_Output;
} LFSPINCHNDIGESTOUTPUT, *LPLFSPINCHNDIGESTOUTPUT;

typedef struct _lfs_pin_chn_sm2_algorithm_param
{
LPLFSXDATA                     lpxP;
LPLFSXDATA                     lpxA;
LPLFSXDATA                     lpxB;
LPLFSXDATA                     lpxN;
LPLFSXDATA                     lpxXg;
LPLFSXDATA                     lpxYg;
} LFSPINCHNSM2ALGORITHMPARAMIN, *LPLFSPINCHNSM2ALGORITHMPARAMIN;

typedef struct _lfs_pin_chn_import_sm2_public_key
{
LPSTR                     lpsKey;
LPLFSXDATA                lpxValue;
DWORD                     dwUse;
LPSTR                     lpsSig_Key;
DWORD                     dwSM2_Signature_Algorithm;
LPLFSXDATA                lpxSignature;
} LFSPINCHNIMPORTSM2PUBLICKEY, *LPLFSPINCHNIMPORTSM2PUBLICKEY;

typedef struct _lfs_pin_chn_import_sm2_public_key_output
{
DWORD                    dwSM2_Key_Check_Mode;
LPLFSXDATA               lpxKey_Check_Value;
} LFSPINCHNIMPORTSM2PUBLICKEYOUTPUT, *LPLFSPINCHNIMPORTSM2PUBLICKEYOUTPUT;

typedef struct _lfs_pin_chn_sign
{
LPSTR                     lpsKey;
LPSTR                     lpSigner_ID;
LPLFSXDATA                lpxPlaintext_Data;
} LFSPINCHNSIGN, *LPLFSPINCHNSIGN;

typedef struct _lfs_pin_chn_sign_output
{
LPLFSXDATA               lpxSign_Data;
} LFSPINCHNSIGNOUTPUT, *LPLFSPINCHNSIGNOUTPUT;

typedef struct _lfs_pin_chn_verify
{
LPSTR                     lpsKey;
LPLFSXDATA                lpxPlaintext_Data;
LPLFSXDATA                lpxSign_Data;
} LFSPINCHNVERIFY, *LPLFSPINCHNVERIFY;

typedef struct _lfs_pin_chn_export_sm2_issuer_signed_item
{
WORD                     wExport_Item_Type;
LPSTR                    lpsName;
} LFSPINCHNEXPORTSM2ISSUERSIGNEDITEM, *LPLFSPINCHNEXPORTSM2ISSUERSIGNEDITEM;

typedef struct _lfs_pin_chn_export_sm2_issuer_signed_item_output
{
LPLFSXDATA               lpxValue;
WORD                     dwSM2_Signature_Algorithm;
LPLFSXDATA               lpxSignature;
} LFSPINCHNEXPORTSM2ISSUERSIGNEDITEMOUTPUT, 
*LPLFSPINCHNEXPORTSM2ISSUERSIGNEDITEMOUTPUT;

typedef struct _lfs_pin_chn_generate_sm2_keypair
{
LPSTR                     lpsKey;
DWORD                     dwUse;
} LFSPINCHNGENERATESM2KEYPAIR, *LPLFSPINCHNGENERATESM2KEYPAIR;

typedef struct _lfs_pin_chn_export_sm2_epp_signed_item
{
WORD                     wExport_Item_Type;
LPSTR                     lpsName;
LPSTR                     lpsSig_Key;
DWORD                     dwSignature_Algorithm;
} LFSPINCHNEXPORTSM2EPPSIGNEDITEM, *LPLFSPINCHNEXPORTSM2EPPSIGNEDITEM;

typedef struct _lfs_pin_chn_export_sm2_epp_signed_item_output
{
LPLFSXDATA               lpxValue;
LPLFSXDATA               lpxSelf_Signature;
LPLFSXDATA               lpxSignature;
} LFSPINCHNEXPORTSM2EPPSIGNEDITEMOUTPUT,	*LPLFSPINCHNEXPORTSM2EPPSIGNEDITEMOUTPUT;

typedef struct _lfs_pin_chn_import_sm2_signed_sm4_key
{
LPSTR                     lpsKey;
LPSTR                     lpsDecrypt_Key;
DWORD                     dwSM2_Encipher_Algorithm;
LPLFSXDATA                lpxValue;
DWORD                     dwUse;
LPSTR                     lpsSig_Key;
DWORD                     dwSM2_Signature_Algorithm;
LPLFSXDATA                lpxSignature;
} LFSPINCHNIMPORTSM2SIGNEDSM4KEY, *LPLFSPINCHNIMPORTSM2SIGNEDSM4KEY;

typedef struct _lfs_pin_chn_import_sm2_signed_sm4_key_output
{
WORD                      wKey_Check_Mode;
LPLFSXDATA                lpxKey_Check_Value;
} LFSPINCHNIMPORTSM2SIGNEDSM4KEYOUTPUT, *LPLFSPINCHNIMPORTSM2SIGNEDSM4KEYOUTPUT;

/*=================================================================*/
/* PIN Message Structures */
/*=================================================================*/
typedef struct _lfs_pin_access
{
LPSTR	  lpstrKey_Name;
LONG	lError_Code;
} LFSPINACCESS, * LPLFSPINACCESS;

typedef struct _lfs_pin_device_position
{
    WORD                   wPosition;
} LFSPINDEVICEPOSITION, *LPLFSPINDEVICEPOSITION;

typedef struct _lfs_pin_power_save_change
{
    USHORT                 usPower_Save_Recovery_Time;
} LFSPINPOWERSAVECHANGE, *LPLFSPINPOWERSAVECHANGE;

/* restore alignment */
#pragma pack(pop)

#ifdef __cplusplus
}       /*extern "C"*/
#endif

#endif    /* __INC_LFSPIN__H */
