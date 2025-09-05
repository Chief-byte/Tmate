/******************************************************************************
*                                                                             *
* LFSSIU.h - Sensors and Indicators Unit (SIU) definitions                    *
*                                                                             *
* Version 1.0 	                                                                *
*                                                                             *
******************************************************************************/

#ifndef __INC_LFSSIU__H
#define __INC_LFSSIU__H

#ifdef __cplusplus
extern "C" {
#endif

#include    "lfsapi.h"

/* be aware of alignment */
#pragma pack (push, 1)

/* values of LFSSIUCAPS.wClass */

#define       LFS_SERVICE_CLASS_SIU                    (8)

#define       LFS_SERVICE_CLASS_NAME_SIU               "SIU"
#define       LFS_SERVICE_CLASS_VERSION_SIU            (0x0001) /* Version 1.0 */

#define       SIU_SERVICE_OFFSET                        (LFS_SERVICE_CLASS_SIU * 100)

/* SIU Info Commands */

#define       LFS_INF_SIU_STATUS                       (SIU_SERVICE_OFFSET + 1)
#define       LFS_INF_SIU_CAPABILITIES                 (SIU_SERVICE_OFFSET + 2)

/* SIU Command Verbs */

#define       LFS_CMD_SIU_ENABLE_EVENTS                (SIU_SERVICE_OFFSET + 1)
#define       LFS_CMD_SIU_SET_PORTS                    (SIU_SERVICE_OFFSET + 2)
#define       LFS_CMD_SIU_SET_DOOR                     (SIU_SERVICE_OFFSET + 3)
#define       LFS_CMD_SIU_SET_INDICATOR                (SIU_SERVICE_OFFSET + 4)
#define       LFS_CMD_SIU_SET_AUXILIARY                (SIU_SERVICE_OFFSET + 5)
#define       LFS_CMD_SIU_SET_GUIDLIGHT                (SIU_SERVICE_OFFSET + 6)
#define       LFS_CMD_SIU_RESET                        (SIU_SERVICE_OFFSET + 7)
#define       LFS_CMD_SIU_POWER_SAVE_CONTROL           (SIU_SERVICE_OFFSET + 8)

/* SIU Messages */

#define       LFS_SRVE_SIU_PORT_STATUS                 (SIU_SERVICE_OFFSET + 1)
#define       LFS_EXEE_SIU_PORT_ERROR                  (SIU_SERVICE_OFFSET + 2)
#define       LFS_SRVE_SIU_POWER_SAVE_CHANGE           (SIU_SERVICE_OFFSET + 3)

/* Values of LFSSIUSTATUS.wDevice */

#define       LFS_SIU_DEVONLINE                        LFS_STAT_DEVONLINE
#define       LFS_SIU_DEVOFFLINE                       LFS_STAT_DEVOFFLINE
#define       LFS_SIU_DEVPOWEROFF                      LFS_STAT_DEVPOWEROFF
#define       LFS_SIU_DEVNODEVICE                      LFS_STAT_DEVNODEVICE
#define       LFS_SIU_DEVHWERROR                       LFS_STAT_DEVHWERROR
#define       LFS_SIU_DEVUSERERROR                     LFS_STAT_DEVUSERERROR
#define       LFS_SIU_DEVBUSY                          LFS_STAT_DEVBUSY
#define       LFS_SIU_DEVFRAUDATTEMPT                  LFS_STAT_DEVFRAUDATTEMPT

/* Size and max index of wSensors array */

#define       LFS_SIU_SENSORS_SIZE                     (32)
#define       LFS_SIU_SENSORS_MAX                      (LFS_SIU_SENSORS_SIZE - 1)

/* Size and max index of wDoors array */

#define       LFS_SIU_DOORS_SIZE                       (16)
#define       LFS_SIU_DOORS_MAX                        (LFS_SIU_DOORS_SIZE - 1)

/* Size and max index of wIndicators array */

#define       LFS_SIU_INDICATORS_SIZE                  (16)
#define       LFS_SIU_INDICATORS_MAX                   (LFS_SIU_INDICATORS_SIZE - 1)

/* Size max index of wAuxiliaries array */

#define       LFS_SIU_AUXILIARIES_SIZE                (16)
#define       LFS_SIU_AUXILIARIES_MAX                 (LFS_SIU_AUXILIARIES_SIZE - 1)

/* Size and max index of wGuid_Lights array */

#ifdef SIU_IOCOUNT_32
#define       LFS_SIU_GUIDLIGHTS_SIZE                 (32)
#define       LFS_SIU_GUIDLIGHTS_MAX                  (LFS_SIU_GUIDLIGHTS_SIZE - 1)
#else
#define       LFS_SIU_GUIDLIGHTS_SIZE                 (16)
#define       LFS_SIU_GUIDLIGHTS_MAX                  (LFS_SIU_GUIDLIGHTS_SIZE - 1)
#endif

/* Indices of LFSSIUSTATUS.wSensors [...]
            LFSSIUCAPS.wSensors [...]
            LFSSIUENABLE.wSensors [...]
            LFSSIUPORTEVENT.wPort_Index
            LFSSIUPORTERROR.wPort_Index */

#define       LFS_SIU_OPERATORSWITCH                     (0)
#define       LFS_SIU_TAMPER                             (1)
#define       LFS_SIU_INTTAMPER                          (2)
#define       LFS_SIU_SEISMIC                            (3)
#define       LFS_SIU_HEAT                               (4)
#define       LFS_SIU_PROXIMITY                          (5)
#define       LFS_SIU_AMBLIGHT                           (6)
#define       LFS_SIU_ENHANCEDAUDIO                      (7)
#define       LFS_SIU_BOOT_SWITCH                        (8)
#define       LFS_SIU_CONSUMER_DISPLAY                   (9)
#define       LFS_SIU_OPERATOR_CALL_BUTTON               (10)
#define       LFS_SIU_HANDSETSENSOR                      (11)
#define       LFS_SIU_GENERALINPUTPORT                   (12)

/* Indices of LFSSIUSTATUS.wDoors [...]
             LFSSIUCAPS.wDoors [...]
             LFSSIUENABLE.wDoors [...]
             LFSSIUSETPORT.wDoors [...]
             LFSSIUSETDOORS.wDoor
             LFSSIUPORTEVENT.wPort_Index
             LFSSIUPORTERROR.wPort_Index */

#define       LFS_SIU_CABINET                            (0)
#define       LFS_SIU_SAFE                               (1)
#define       LFS_SIU_VANDALSHIELD                       (2)
#define       LFS_SIU_CABINET_FRONT                      (3)
#define       LFS_SIU_CABINET_REAR                       (4)
#define       LFS_SIU_CABINET_LEFT                       (5)
#define       LFS_SIU_CABINET_RIGHT                      (6)

/* Indices of LFSSIUSTATUS.wIndicators [...]
             LFSSIUCAPS.wIndicators [...]
             LFSSIUENABLE.wIndicators [...]
             LFSSIUSETPORT.wIndicators [...]
             LFSSIUSETINDICATORS.wIndicator
             LFSSIUPORTEVENT.wPort_Index
             LFSSIUPORTERROR.wPort_Index */

#define       LFS_SIU_OPENCLOSE                          (0)
#define       LFS_SIU_FASCIALIGHT                        (1)
#define       LFS_SIU_AUDIO                              (2)
#define       LFS_SIU_HEATING                            (3)
#define       LFS_SIU_CONSUMER_DISPLAY_BACKLIGHT         (4)
#define       LFS_SIU_SIGNAGEDISPLAY                     (5)
#define       LFS_SIU_TRANSINDICATOR                     (6)
#define       LFS_SIU_GENERALOUTPUTPORT                  (7)

/* Indices of LFSSIUSTATUS.wAuxiliaries [...]
             LFSSIUCAPS.wAuxiliaries [...]
             LFSSIUENABLE.wAuxiliaries [...]
             LFSSIUSETPORT.wAuxiliaries [...]
             LFSSIUSETAUXILIARIES.wAuxiliary
             LFSSIUPORTEVENT.wPort_Index
             LFSSIUPORTERROR.wPort_Index */

#define       LFS_SIU_VOLUME                             (0)
#define       LFS_SIU_UPS                                (1)
#define       LFS_SIU_REMOTE_STATUS_MONITOR              (2)
#define       LFS_SIU_AUDIBLE_ALARM                      (3)
#define       LFS_SIU_ENHANCEDAUDIOCONTROL               (4)

/* Indices of LFSSIUSTATUS.wGuid_Lights [...]
             LFSSIUCAPS.wGuid_Lights [...]
             LFSSIUENABLE.wGuid_Lights [...]
             LFSSIUSETPORT.wGuid_Lights [...]
             LFSSIUSETGUIDLIGHTS.wGuidLight
             LFSSIUPORTEVENT.wPort_Index
             LFSSIUPORTERROR.wPort_Index */

#define       LFS_SIU_CARDUNIT                           (0)
#define       LFS_SIU_PINPAD                             (1)
#define       LFS_SIU_NOTESDISPENSER                     (2)
#define       LFS_SIU_COINDISPENSER                      (3)
#define       LFS_SIU_RECEIPTPRINTER                     (4)
#define       LFS_SIU_PASSBOOKPRINTER                    (5)
#define       LFS_SIU_ENVDEPOSITORY                      (6)
#define       LFS_SIU_CHEQUEUNIT                         (7)
#define       LFS_SIU_BILLACCEPTOR                       (8)
#define       LFS_SIU_ENVDISPENSER                       (9)
#define       LFS_SIU_DOCUMENTPRINTER                    (10)
#define       LFS_SIU_COINACCEPTOR                       (11)
#define       LFS_SIU_SCANNER                            (12)
#define       LFS_SIU_CHECKSCANNER                       (13)
#define       LFS_SIU_FINGERPRINT                        (14)
#define       LFS_SIU_USBCONTROL                         (15)
#define       LFS_SIU_CAMERA                             (16)
#define       LFS_SIU_HIGHCAMERA                         (17)
#define       LFS_SIU_CARDBOX                            (18)
#define       LFS_SIU_PASSBOOKREADER                     (19)
#define       LFS_SIU_ENVELOPEDEPOSITORY                 (20)
#define       LFS_SIU_UKEY                               (21)
#define       LFS_SIU_ATMOSPHERE                         (22)
#define       LFS_SIU_IDCARDREADER                       (23)
#define       LFS_SIU_RFCARDREADER                       (24)
/* Values of LFSSIUSTATUS.wSensors [...]
            LFSSIUSTATUS.wDoors [...]
            LFSSIUSTATUS.wIndicators [...]
            LFSSIUSTATUS.wAuxiliaries [...]
            LFSSIUSTATUS.wGuid_Lights [...]
            LFSSIUCAPS.wSensors [...]
            LFSSIUCAPS.wDoors [...]
            LFSSIUCAPS.wIndicators [...]
            LFSSIUCAPS.wAuxiliaries [...]
            LFSSIUCAPS.wGuid_Lights [...] */

#define       LFS_SIU_NOT_AVAILABLE                      (0x0000)
#define       LFS_SIU_AVAILABLE                          (0x0001)

/* Values of LFSSIUSTATUS.wSensors [LFS_SIU_OPERATORSWITCH]
            LFSSIUCAPS.wSensors [LFS_SIU_OPERATORSWITCH]
            LFSSIUPORTEVENT.fwPort_Status
            LFSSIUPORTERROR.fwPort_Status */

#define       LFS_SIU_RUN                                (0x0001)
#define       LFS_SIU_MAINTENANCE                        (0x0002)
#define       LFS_SIU_SUPERVISOR                         (0x0004)

/* Values of LFSSIUSTATUS.wDoors [...]


            LFSSIUSTATUS.wIndicators [LFS_SIU_OPENCLOSE]
            LFSSIUCAPS.wDoors [...]
            LFSSIUCAPS.wIndicators [LFS_SIU_OPENCLOSE]
            LFSSIUSETPORT.wDoors [...]
            LFSSIUSETPORT.wIndicators [LFS_SIU_OPENCLOSE]
            LFSSIUSETDOOR.wDoor
            LFSSIUSETINDICATOR.wCommand
            LFSSIUPORTEVENT.wPort_Status
            LFSSIUPORTERROR.wPort_Status */

#define       LFS_SIU_CLOSED                             (0x0001)
#define       LFS_SIU_OPEN                               (0x0002)
#define       LFS_SIU_LOCKED                             (0x0004)
#define       LFS_SIU_BOLTED                             (0x0008)
#define       LFS_SIU_SERVICE                            (0x0010)
#define       LFS_SIU_KEYBOARD                           (0x0020)
#define       LFS_SIU_AJAR                               (0x0040)
#define       LFS_SIU_JAMMED                             (0x0080)

/* Values of LFSSIUSTATUS.wIndicators [LFS_SIU_AUDIO]
            LFSSIUSETPORT.wIndicators [LFS_SIU_AUDIO]
            LFSSIUSETINDICATOR.wCommand
            LFSSIUPORTEVENT.wPort_Status
            LFSSIUPORTERROR.wPort_Status */

#define       LFS_SIU_KEYPRESS                           (0x0002)
#define       LFS_SIU_EXCLAMATION                        (0x0004)
#define       LFS_SIU_WARNING                            (0x0008)
#define       LFS_SIU_ERROR                              (0x0010)
#define       LFS_SIU_CRITICAL                           (0x0020)

/* Values of LFSSIUSTATUS.wSensors [LFS_SIU_CONSUMER_DISPLAY]
            LFSSIUPORTEVENT.wPort_Status
            LFSSIUPORTERROR.wPort_Status */

#define       LFS_SIU_DISPLAY_ERROR                      (0x0004)

/* Flags for LFSSIUSTATUS.wIndicators [LFS_SIU_TRANSINDICATOR]
            LFSSIUSETPORT.wIndicators [LFS_SIU_TRANSINDICATOR]
            LFSSIUSETINDICATOR.wCommand
            LFSSIUPORTEVENT.wPort_Status[LFS_SIU_TRANSINDICATOR]
            LFSSIUPORTERROR.wPort_Status[LFS_SIU_TRANSINDICATOR] */

#define       LFS_SIU_LAMP1                              (0x0001)
#define       LFS_SIU_LAMP2                              (0x0002)
#define       LFS_SIU_LAMP3                              (0x0004)
#define       LFS_SIU_LAMP4                              (0x0008)
#define       LFS_SIU_LAMP5                              (0x0010)
#define       LFS_SIU_LAMP6                              (0x0020)
#define       LFS_SIU_LAMP7                              (0x0040)
#define       LFS_SIU_LAMP8                              (0x0080)
#define       LFS_SIU_LAMP9                              (0x0100)
#define       LFS_SIU_LAMP10                             (0x0200)
#define       LFS_SIU_LAMP11                             (0x0400)
#define       LFS_SIU_LAMP12                             (0x0800)
#define       LFS_SIU_LAMP13                             (0x1000)
#define       LFS_SIU_LAMP14                             (0x2000)
#define       LFS_SIU_LAMP15                             (0x4000)
#define       LFS_SIU_LAMP16                             (0x8000)

/* Values of LFSSIUSTATUS.wAuxiliaries [LFS_SIU_REMOTE_STATUS_MONITOR]
            LFSSIUSETPORT.wAuxiliaries [LFS_SIU_REMOTE_STATUS_MONITOR]
            LFSSIUSETAUXILIARY.wCommand
            LFSSIUPORTEVENT.wPort_Status
            LFSSIUPORTERROR.wPort_Status */

#define       LFS_SIU_GREEN_LED_ON                       (0x0001)
#define       LFS_SIU_GREEN_LED_OFF                      (0x0002)
#define       LFS_SIU_AMBER_LED_ON                       (0x0004)
#define       LFS_SIU_AMBER_LED_OFF                      (0x0008)
#define       LFS_SIU_RED_LED_ON                         (0x0010)
#define       LFS_SIU_RED_LED_OFF                        (0x0020)


/* Values of LFSSIUSTATUS.wAuxiliaries [LFS_SIU_ENHANCEDAUDIOCONTROL]
            LFSSIUSETPORT.wAuxiliaries [LFS_SIU_ENHANCEDAUDIOCONTROL]
            LFSSIUSETAUXILIARY.wCommand
            LFSSIUPORTEVENT.wPort_Status
            LFSSIUPORTERROR.wPort_Status */

#define       LFS_SIU_PUBLICAUDIO_MANUAL                 (0x0001)
#define       LFS_SIU_PUBLICAUDIO_AUTO                   (0x0002)
#define       LFS_SIU_PUBLICAUDIO_SEMI_AUTO              (0x0004)
#define       LFS_SIU_PRIVATEAUDIO_MANUAL                (0x0008)
#define       LFS_SIU_PRIVATEAUDIO_AUTO                  (0x0010)
#define       LFS_SIU_PRIVATEAUDIO_SEMI_AUTO             (0x0020)

/* Values of LFSSIUSTATUS.wSensors [...]
            LFSSIUSTATUS.wIndicators [...]
            LFSSIUSTATUS.wAuxiliaries [...]
            LFSSIUSTATUS.wGuid_Lights [...]
            LFSSIUCAPS.wSensors [...]
            LFSSIUCAPS.wIndicators [...]
            LFSSIUCAPS.wGuid_Lights [...]
            LFSSIUSETPORT.wIndicators [...]
            LFSSIUSETPORT.wAuxiliaries [...]
            LFSSIUSETPORT.wGuid_Lights [...]
            LFSSIUSETINDICATORS.wCommand [...]
            LFSSIUSETAUXILIARY.wCommand [...]
            LFSSIUSETGUIDLIGHTS.wCommand [...]
            LFSSIUPORTEVENT.wPort_Status
            LFSSIUPORTERROR.wPort_Status */

#define       LFS_SIU_OFF                                (0x0001)
#define       LFS_SIU_ON                                 (0x0002)
#define       LFS_SIU_SLOW_FLASH                         (0x0004)
#define       LFS_SIU_MEDIUM_FLASH                       (0x0008)
#define       LFS_SIU_QUICK_FLASH                        (0x0010)
#define       LFS_SIU_CONTINUOUS                         (0x0080)

/* Flags for LFSSIUSTATUS.wSensors [LFS_SIU_GENERALINPUTPORT]
            LFSSIUSTATUS.wIndicators [LFS_SIU_GENERALOUTPUTPORT]
            LFSSIUSETPORT.wIndicators [LFS_SIU_GENERALOUTPUTPORT]
            LFSSIUSETINDICATOR.wCommand
            LFSSIUPORTEVENT.wPort_Status[LFS_SIU_GENERALINPUTPORT]
            LFSSIUPORTEVENT.wPort_Status[LFS_SIU_GENERALOUTPUTPORT]
            LFSSIUPORTERROR.wPort_Status[LFS_SIU_GENERALINPUTPORT]
            LFSSIUPORTERROR.wPort_Status[LFS_SIU_GENERALOUTPUTPORT] */

#define       LFS_SIU_GPP1                               (0x0001)
#define       LFS_SIU_GPP2                               (0x0002)
#define       LFS_SIU_GPP3                               (0x0004)
#define       LFS_SIU_GPP4                               (0x0008)
#define       LFS_SIU_GPP5                               (0x0010)
#define       LFS_SIU_GPP6                               (0x0020)
#define       LFS_SIU_GPP7                               (0x0040)
#define       LFS_SIU_GPP8                               (0x0080)
#define       LFS_SIU_GPP9                               (0x0100)
#define       LFS_SIU_GPP10                              (0x0200)
#define       LFS_SIU_GPP11                              (0x0400)
#define       LFS_SIU_GPP12                              (0x0800)
#define       LFS_SIU_GPP13                              (0x1000)
#define       LFS_SIU_GPP14                              (0x2000)
#define       LFS_SIU_GPP15                              (0x4000)
#define       LFS_SIU_GPP16                              (0x8000)

/* Values of LFSSIUSTATUS.wSensors [LFS_SIU_PROXIMITY]
            LFSSIUSTATUS.wSensors [LFS_SIU_ENHANCEDCONTROL]
            LFSSIUPORTEVENT.wPort_Status
            LFSSIUPORTERROR.wPort_Status */

#define       LFS_SIU_PRESENT                            (0x0001)
#define       LFS_SIU_NOT_PRESENT                        (0x0002)


/* Values of LFSSIUSTATUS.wSensors [LFS_SIU_HANDSETSENSOR] */

#define       LFS_SIU_OFF_THE_HOOK                       (0x0001)
#define       LFS_SIU_ON_THE_HOOK                        (0x0002)

/* Values of LFSSIUCAPS.wSensors [LFS_SIU_ENHANCEDAUDIO]
            LFSSIUCAPS.wSensors [LFS_SIU_HANDSETSENSOR] */

#define       LFS_SIU_MANUAL                             (0x0001)
#define       LFS_SIU_AUTO                               (0x0002)
#define       LFS_SIU_SEMI_AUTO                          (0x0004)

/* Values of LFSSIUSTATUS.wSensors [LFS_SIU_AMBLIGHT]
            LFSSIUCAPS.wSensors [LFS_SIU_AMBLIGHT]
            LFSSIUPORTEVENT.fwPort_Status
            LFSSIUPORTERROR.fwPort_Status */

#define       LFS_SIU_VERY_DARK                          (0x0001)
#define       LFS_SIU_DARK                               (0x0002)
#define       LFS_SIU_MEDIUM_LIGHT                       (0x0004)
#define       LFS_SIU_LIGHT                              (0x0008)
#define       LFS_SIU_VERY_LIGHT                         (0x0010)

/* Values of LFSSIUSTATUS.wAuxiliaries [LFS_SIU_UPS]
               LFSSIUCAPS.wAuxiliaries [LFS_SIU_UPS]
               LFSSIUPORTEVENT.wPort_Status
               LFSSIUPORTERROR.wPort_Status */

#define       LFS_SIU_LOW                                (0x0002)
#define       LFS_SIU_ENGAGED                            (0x0004)
#define       LFS_SIU_POWERING                           (0x0008)
#define       LFS_SIU_RECOVERED                          (0x0010)

/* Values of LFSSIUCAPS.wType */

#define       LFS_SIU_SENSORS                            (0x0001)
#define       LFS_SIU_DOORS                              (0x0002)
#define       LFS_SIU_INDICATORS                         (0x0004)
#define       LFS_SIU_AUXILIARIES                        (0x0008)
#define       LFS_SIU_GUIDLIGHTS                         (0x0010)

/* Values of LFSSIUCAPS.wAuxiliaries [LFS_SIU_ENHANCEDAUDIOCONTROL] */
#define       LFS_SIU_HEADSET_DETECTION                  (0x0001)
#define       LFS_SIU_MODE_CONTROLLABLE                  (0x0002)

/* Values of LFSSIUENABLE.wSensors [...]
            LFSSIUENABLE.wDoors [...]
            LFSSIUENABLE.wIndicators [...]
            LFSSIUENABLE.wAuxiliaries [...]
            LFSSIUENABLE.wGuid_Lights [...]
            LFSSIUSETPORTS.wDoors [...]
            LFSSIUSETPORTS.wIndicators [...]
            LFSSIUSETPORTS.wAuxiliaries [...]
            LFSSIUSETPORTS.wGuid_Lights [...] */

#define       LFS_SIU_NO_CHANGE                          (0x0000)
#define       LFS_SIU_ENABLE_EVENT                       (0x0001)
#define       LFS_SIU_DISABLE_EVENT                      (0x0002)

/* Values of LFSSIUSETPORTS.wDoors [...]
            LFSSIUSETDOORS.wCommand [...] */

#define       LFS_SIU_BOLT                               (0x0001)
#define       LFS_SIU_UNBOLT                             (0x0002)

/* Values of LFSSIUSETPORTS.wAuxiliaries [LFS_SIU_UPS]



       LFSSIUSETAUXILIARY.wAuxiliary [LFS_SIU_UPS] */

#define LFS_SIU_ENGAGE                                   (0x0001)
#define LFS_SIU_DISENGAGE                                (0x0002)

/* SIU Errors */

#define       LFS_ERR_SIU_INVALID_PORT                   (-(SIU_SERVICE_OFFSET + 1))
#define       LFS_ERR_SIU_SYNTAX                         (-(SIU_SERVICE_OFFSET + 2))
#define       LFS_ERR_SIU_PORT_ERROR                     (-(SIU_SERVICE_OFFSET + 3))
#define       LFS_ERR_SIU_POWERSAVETOOSHORT              (-(SIU_SERVICE_OFFSET + 4))

/*=================================================================*/
/* SIU Info Command Structures and variables */
/*=================================================================*/

typedef struct _LFS_SIU_status
{
     WORD              wDevice;
     WORD              wSensors [LFS_SIU_SENSORS_SIZE];
     WORD              wDoors [LFS_SIU_DOORS_SIZE];
     WORD              wIndicators [LFS_SIU_INDICATORS_SIZE];
     WORD              wAuxiliaries [LFS_SIU_AUXILIARIES_SIZE];
     WORD              wGuid_Lights [LFS_SIU_GUIDLIGHTS_SIZE];
     LPSTR             lpstrExtra;
     USHORT            usPower_Save_Recovery_Time;
} LFSSIUSTATUS, *LPLFSSIUSTATUS;

typedef struct _LFS_SIU_caps
{
     WORD              wClass;
     WORD              wType;
     WORD              wSensors [LFS_SIU_SENSORS_SIZE];
     WORD              wDoors [LFS_SIU_DOORS_SIZE];
     WORD              wIndicators [LFS_SIU_INDICATORS_SIZE];
     WORD              wAuxiliaries [LFS_SIU_AUXILIARIES_SIZE];
     WORD              wGuid_Lights [LFS_SIU_GUIDLIGHTS_SIZE];
     LPSTR             lpstrExtra;
     BOOL              bPower_Save_Control;
} LFSSIUCAPS, *LPLFSSIUCAPS;

/*=================================================================*/
/* SIU Execute Command Structures */
/*=================================================================*/

typedef struct _LFS_SIU_enable
{
     WORD              wSensors [LFS_SIU_SENSORS_SIZE];
     WORD              wDoors [LFS_SIU_DOORS_SIZE];
     WORD              wIndicators [LFS_SIU_INDICATORS_SIZE];
     WORD              wAuxiliaries [LFS_SIU_AUXILIARIES_SIZE];
     WORD              wGuid_Lights [LFS_SIU_GUIDLIGHTS_SIZE];
     LPSTR             lpstrExtra;
} LFSSIUENABLE, *LPLFSSIUENABLE;

typedef struct _LFS_SIU_set_ports
{
     WORD              wDoors [LFS_SIU_DOORS_SIZE];
     WORD              wIndicators [LFS_SIU_INDICATORS_SIZE];
     WORD              wAuxiliaries [LFS_SIU_AUXILIARIES_SIZE];
     WORD              wGuid_Lights [LFS_SIU_GUIDLIGHTS_SIZE];
     LPSTR             lpstrExtra;
} LFSSIUSETPORTS, *LPLFSSIUSETPORTS;

typedef struct _LFS_SIU_set_door
{
     WORD              wDoor;
     WORD              wCommand;
} LFSSIUSETDOOR, *LPLFSSIUSETDOOR;


typedef struct _LFS_SIU_set_indicator
{
     WORD              wIndicator;
     WORD              wCommand;
} LFSSIUSETINDICATOR, *LPLFSSIUSETINDICATOR;

typedef struct _LFS_SIU_set_auxiliary
{
     WORD              wAuxiliary;
     WORD              wCommand;
} LFSSIUSETAUXILIARY, *LPLFSSIUSETAUXILIARY;

typedef struct _LFS_SIU_set_guidlight
{
     WORD              wGuidLight;
     WORD              wCommand;
} LFSSIUSETGUIDLIGHT, *LPLFSSIUSETGUIDLIGHT;

typedef struct _LFS_SIU_power_save_control
{
     USHORT            usMax_Power_Save_Recovery_Time;
} LFSSIUPOWERSAVECONTROL, *LPLFSSIUPOWERSAVECONTROL;

/*=================================================================*/
/* SIU Message Structures */
/*=================================================================*/

typedef struct _LFS_SIU_port_event
{
     WORD              wPort_Type;
     WORD              wPort_Index;
     WORD              wPort_Status;
     LPSTR             lpstrExtra;
} LFSSIUPORTEVENT, *LPLFSSIUPORTEVENT;

typedef struct _LFS_SIU_port_error
{
     WORD              wPort_Type;
     WORD              wPort_Index;
     HRESULT           Port_Error;
     WORD              wPort_Status;
     LPSTR             lpstrExtra;
} LFSSIUPORTERROR, *LPLFSSIUPORTERROR;

typedef struct _LFS_SIU_power_save_change
{
     USHORT            usPower_Save_Recovery_Time;
} LFSSIUPOWERSAVECHANGE, *LPLFSSIUPOWERSAVECHANGE;

/* restore alignment */
#pragma pack (pop)

#ifdef __cplusplus
}         /*extern "C"*/
#endif

#endif  /* __INC_LFSSIU__H */
