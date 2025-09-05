/*******************************************************************************
 *                                                                             *
 * lfschk.h    LFS - Check reader/scanner (CHK) definitions                    *
 *                                                                             *
 *                     Version 1.00  -  (2020-02)                              *
 *                                                                             *
 *******************************************************************************/

#ifndef __INC_LFSCHK__H
#define __INC_LFSCHK__H

#ifdef__cplusplus
extern "C" {
#endif

#include "lfsapi.h"

/*   be aware of alignment   */
#pragma pack(push, 1)

/* values of LFSCHKCAPS.wClass */

#define LFS_SERVICE_CLASS_CHK         (13)
#define LFS_SERVICE_CLASS_VERSION_CHK (0x0001)  // Version 1.00
#define LFS_SERVICE_CLASS_NAME_CHK    "CHK"

#define CHK_SERVICE_OFFSET (LFS_SERVICE_CLASS_CHK * 100)

/* CHK Info Commands */
#define LFS_INF_CHK_STATUS       (CHK_SERVICE_OFFSET + 1)
#define LFS_INF_CHK_CAPABILITIES (CHK_SERVICE_OFFSET + 2)
#define LFS_INF_CHK_FORM_LIST    (CHK_SERVICE_OFFSET + 3)
#define LFS_INF_CHK_MEDIA_LIST   (CHK_SERVICE_OFFSET + 4)
#define LFS_INF_CHK_QUERY_FORM   (CHK_SERVICE_OFFSET + 5)
#define LFS_INF_CHK_QUERY_MEDIA  (CHK_SERVICE_OFFSET + 6)
#define LFS_INF_CHK_QUERY_FIELD  (CHK_SERVICE_OFFSET + 7)
/* CHK Execute Commands */
#define LFS_CMD_CHK_PROCESS_FORM       (CHK_SERVICE_OFFSET + 1)
#define LFS_CMD_CHK_RESET              (CHK_SERVICE_OFFSET + 2)
#define LFS_CMD_CHK_SET_GUIDANCE_LIGHT (CHK_SERVICE_OFFSET + 3)
#define LFS_CMD_CHK_POWER_SAVE_CONTROL (CHK_SERVICE_OFFSET + 4)
/* CHK Events  */
#define LFS_SRVE_CHK_NOMEDIA           (CHK_SERVICE_OFFSET + 1)
#define LFS_SRVE_CHK_MEDIAINSERTED     (CHK_SERVICE_OFFSET + 2)
#define LFS_SRVE_CHK_FIELDERROR        (CHK_SERVICE_OFFSET + 3)
#define LFS_USRE_CHK_FIELDWARNING      (CHK_SERVICE_OFFSET + 4)
#define LFS_EXEE_CHK_INKTHRESHOLD      (CHK_SERVICE_OFFSET + 5)
#define LFS_SRVE_CHK_MEDIADETECTED     (CHK_SERVICE_OFFSET + 6)
#define LFS_SRVE_CHK_DEVICEPOSITION    (CHK_SERVICE_OFFSET + 7)
#define LFS_SRVE_CHK_POWER_SAVE_CHANGE (CHK_SERVICE_OFFSET + 8)
/* values of LFSCHKSTATUS.device */
#define LFS_CHK_DEVONLINE         LFS_STAT_DEVONLINE
#define LFS_CHK_DEVOFFLINE        LFS_STAT_DEVOFFLINE
#define LFS_CHK_DEVPOWEROFF       LFS_STAT_DEVPOWEROFF
#define LFS_CHK_DEVNODEVICE       LFS_STAT_DEVNODEVICE
#define LFS_CHK_DEVHWERROR        LFS_STAT_DEVHWERROR
#define LFS_CHK_DEVUSERERROR      LFS_STAT_DEVUSERERROR
#define LFS_CHK_DEVBUSY           LFS_STAT_DEVBUSY
#define LFS_CHK_DEVFRAUDATTEMPT   LFS_STAT_DEVFRAUDATTEMPT
#define LFS_CHK_DEVPOTENTIALFRAUD LFS_STAT_DEVPOTENTIALFRAUD
/* values of LFSCHKSTATUS.ink*/
#define LFS_CHK_INKFULL    (0)
#define LFS_CHK_INKLOW     (1)
#define LFS_CHK_INKOUT     (2)
#define LFS_CHK_INKNOTSUPP (3)
/* values of LFSCHKSTATUS.media*/
#define LFS_CHK_MEDIAPRESENT    (1)
#define LFS_CHK_MEDIANOTPRESENT (2)
#define LFS_CHK_MEDIAJAMMED     (3)
#define LFS_CHK_MEDIANOTSUPP    (4)
#define LFS_CHK_MEDIAUNKNOWN    (5)
#define LFS_CHK_MEDIAREQUIRED   (6)
/* Size and max index of guid_lights array */
#define LFS_CHK_GUIDLIGHTS_SIZE (32)
#define LFS_CHK_GUIDLIGHTS_MAX  (LFS_CHK_GUIDLIGHTS_SIZE - 1)
/* Indices of LFSCHKSTATUS.guid_lights [...]
              LFSCHKCAPS.guid_lights [...] */
#define LFS_CHK_GUIDANCE_CARDDISP (0)
/* Values of LFSCHKSTATUS.guid_lights[...]
             LFSCHKCAPS.guid_lights[...] */
#define LFS_CHK_GUIDANCE_NOT_AVAILABLE (0x00000000)
#define LFS_CHK_GUIDANCE_OFF           (0x00000001)
#define LFS_CHK_GUIDANCE_SLOW_FLASH    (0x00000004)
#define LFS_CHK_GUIDANCE_MEDIUM_FLASH  (0x00000008)
#define LFS_CHK_GUIDANCE_QUICK_FLASH   (0x00000010)
#define LFS_CHK_GUIDANCE_CONTINUOUS    (0x00000080)
#define LFS_CHK_GUIDANCE_RED           (0x00000100)
#define LFS_CHK_GUIDANCE_GREEN         (0x00000200)
#define LFS_CHK_GUIDANCE_YELLOW        (0x00000400)
#define LFS_CHK_GUIDANCE_BLUE          (0x00000800)
#define LFS_CHK_GUIDANCE_CYAN          (0x00001000)
#define LFS_CHK_GUIDANCE_MAGENTA       (0x00002000)
#define LFS_CHK_GUIDANCE_WHITE         (0x00004000)
/* values of LFSCHKSTATUS.device_position
             LFSCHKDEVICEPOSITION.position */
#define LFS_CHK_DEVICEINPOSITION    (0)
#define LFS_CHK_DEVICENOTINPOSITION (1)
#define LFS_CHK_DEVICEPOSUNKNOWN    (2)
#define LFS_CHK_DEVICEPOSNOTSUPP    (3)
/* values of LFSCHKSTATUS.anti_fraud_module*/
#define LFS_CHK_AFMNOTSUPP        (0)
#define LFS_CHK_AFMOK             (1)
#define LFS_CHK_AFMINOP           (2)
#define LFS_CHK_AFMDEVICEDETECTED (3)
#define LFS_CHK_AFMUNKNOWN        (4)
/*values of LFSCHKCAPS.stamp*/
#define LFS_CHK_STAMPNONE  (0)
#define LFS_CHK_STAMPFRONT (1)
#define LFS_CHK_STAMPBACK  (2)
#define LFS_CHK_STAMPBOTH  (3)
/*values of LFSCHKCAPS.image_capture */
#define LFS_CHK_ICAPNONE  (0)
#define LFS_CHK_ICAPFRONT (1)
#define LFS_CHK_ICAPBACK  (2)
#define LFS_CHK_ICAPBOTH  (3)
/*values of LFSCHKCAPS.char_support*/
#define LFS_CHK_ASCII   (0)
#define LFS_CHK_UNICODE (1)
/* values of LFSFRMHEADER.base*/
#define LFS_FRM_INCH      (0)
#define LFS_FRM_MM        (1)
#define LFS_FRM_ROWCOLUMN (2)
/* values of LFSFRMHEADER.alignment*/
#define LFS_FRM_TOPLEFT     (0)
#define LFS_FRM_TOPRIGHT    (1)
#define LFS_FRM_BOTTOMLEFT  (2)
#define LFS_FRM_BOTTOMRIGHT (3)
/* values of LFSFRMHEADER.orientatin*/
#define LFS_FRM_PORTRAIT  (0)
#define LFS_FRM_LANDSCAPE (1)
/* values of LFSFRMHEADER.char_support*/
#define LFS_PTR_ASCII   (0)
#define LFS_PTR_UNICODE (1)
/* values of LPLFSFRMMEDIA.media_type*/
#define LFS_FRM_MEDIAGENERIC   (0)
#define LFS_FRM_MEDIAPASSBOOK  (1)
#define LFS_FRM_MEDIAMULTIPART (2)
/* values of LPLFSFRMMEDIA.base*/
#define LFS_FRM_INCH      (0)
#define LFS_FRM_MM        (1)
#define LFS_FRM_ROWCOLUMN (2)
/* values of LPLFSCHKFRMFIELD.type*/
#define LFS_CHK_FIELDTEXT    (0)
#define LFS_CHK_FIELDMICR    (1)
#define LFS_CHK_FIELDOCR     (2)
#define LFS_CHK_FIELDGRAPHIC (3)
/* values of LPLFSCHKFRMFIELD.class*/
#define LFS_CHK_CLASSSTATIC   (0)
#define LFS_CHK_CLASSOPTIONAL (1)
#define LFS_CHK_CLASSREQUIRED (2)
/* values of LPLFSCHKFRMFIELD.access*/
#define LFS_CHK_ACCESSREAD  (0)
#define LFS_CHK_ACCESSWRITE (1)
/* values of LPLFSCHKINPROCESSFORM.options*/
#define LFS_CHK_OPT_AUTOFEED    (0)
#define LFS_CHK_OPT_ICAPFRONT   (1)
#define LFS_CHK_OPT_ICAPBACK    (2)
#define LFS_CHK_OPT_NO_MICR_OCR (3)
#define LFS_CHK_OPT_NO_WRITE    (4)
/* values of LPLFSCHKOUTPROCESSFORM.front_image_type*/
#define LFS_IPM_IMAGETIF (0)
#define LFS_IPM_IMAGEWMF (1)
#define LFS_IPM_IMAGEBMP (2)
/*values of LFSCHKFIELDFAIL.failure */
#define LFS_CHK_FIELDREQUIRED         (0)
#define LFS_CHK_FIELDSTATICOVWR       (1)
#define LFS_CHK_FIELDOVERFLOW         (2)
#define LFS_CHK_FIELDNOTFOUND         (3)
#define LFS_CHK_FIELDNOTREAD          (4)
#define LFS_CHK_FIELDNOTWRITE         (5)
#define LFS_CHK_FIELDHWERROR          (6)
#define LFS_CHK_FIELDTYPENOTSUPPORTED (7)
#define LFS_CHK_FIELDGRAPHIC          (8)
#define LFS_CHK_CHARSETFORM           (9)
/*=================================================================*/
/* CHK Info Command Structures and variables */
/*=================================================================*/
typedef struct_lfs_chk_status {
  WORD device;
  WORD media;
  WORD ink;
  DWORD guid_lights[LFS_CHK_GUIDLIGHTS_SIZE];
  LPSTR extra;
  WORD device_position;
  USHORT power_save_recovery_time;
  WORD anti_fraud_module;
}
LFSCHKSTATUS, *LPLFSCHKSTATUS;
typedef struct_lfs_chk_caps {
  WORD dev_class;
  WORD dev_type;
  BOOL compound;
  BOOL micr;
  BOOL ocr;
  BOOL auto_feed;
  BOOL endorser;
  BOOL encoder;
  WORD stamp;
  WORD image_capture;
  LPSTR font_names;
  LPSTR encode_names;
  WORD char_support;
  DWORD guid_lights[LFS_CHK_GUIDLIGHTS_SIZE];
  LPSTR extra;
  BOOL power_save_control;
  BOOL anti_fraud_module;
}
LFSCHKCAPS, *LPLFSCHKCAPS;
typedef struct_lfs_frm_header {
  LPSTR form_name;
  WORD base;
  WORD unit_x;
  WORD unit_y;
  WORD width;
  WORD heigh;
  WORD alignment;
  WORD orientatin;
  WORD offset_x;
  WORD offset_y;
  WORD version_major;
  WORD version_minor;
  LPSTR user_promt;
  WORD char_support;
  LPSTR fields;
  WORD language_id;
}
LFSFRMHEADER, *LPLFSFRMHEADER;
typedef struct_lfs_frm_media {
  WORD media_type;
  WORD base;
  WORD unit_x;
  WORD unit_y;
  WORD size_width;
  WORD size_height;
  WORD check_area_x;
  WORD check_area_y;
  WORD check_area_width;
  WORD check_area_height;
  WORD restricted_area_x;
  WORD restricted_area_y;
  WORD restricted_area_width;
  WORD restricted_area_height;
}
LFSFRMMEDIA, *LPLFSFRMMEDIA;
typedef struct_lfs_ptr_query_field {
  LPSTR form_name;
  LPSTR field_name;
}
LFSCHKQUERYFIELD, *LPLFSCHKQUERYFIELD;
typedef struct_lfs_chk_frm_field {
  LPSTR field_name;
  WORD type;
  WORD class;
  WORD access;
  WORD overflow;
  LPSTR initial_value;
  LPWSTR unicode_initial_value;
  LPSTR format;
  LPWSTR unicode_format;
}
LFSCHKFRMFIELD, *LPLFSCHKFRMFIELD;
/*=================================================================*/
/* CHK Execute Command Structures */
/*=================================================================*/
typedef struct_lfs_chk_in_process_form {
  LPSTR form_name;
  LPSTR media_name;
  LPSTR input_fields;
  LPSTR output_fields;
  LPWSTR unicode_output_fields;
  DWORD options;
}
LFSCHKINPROCESSFORM, *LPLFSCHKINPROCESSFORM;
typedef struct_lfs_chk_out_process_form {
  LPSTR input_fields;
  LPWSTR unicode_input_fields;
  WORD front_image_type;
  ULONG front_image_size;
  LPBYTE front_image;
  WORD back_image_type;
  ULONG back_image_size;
  LPBYTE back_image;
}
LFSCHKOUTPROCESSFORM, *LPLFSCHKOUTPROCESSFORM;
typedef struct_lfs_chk_set_guidlight {
  WORD guid_light;
  DWORD command;
}
LFSCHKSETGUIDLIGHT, *LPLFSCHKSETGUIDLIGHT;
typedef struct_lfs_chk_power_save_control {
  USHORT max_power_save_recovery_time;
}
LFSCHKPOWERSAVECONTROL, *LPLFSCHKPOWERSAVECONTROL;
/*=================================================================*/
/* CHK Message Structures */
/*=================================================================*/
typedef struct_lfs_chk_field_failure {
  LPSTR form_name;
  LPSTR field_name;
  WORD failure;
}
LFSCHKFIELDFAIL, *LPLFSCHKFIELDFAIL;
typedef struct_lfs_chk_device_position {
  WORD position;
}
LFSCHKDEVICEPOSITION, *LPLFSCHKDEVICEPOSITION;
typedef struct_lfs_chk_power_save_change {
  USHORT power_save_recovery_time;
}
LFSCHKPOWERSAVECHANGE, *LPLFSCHKPOWERSAVECHANGE;
/*   restore alignment   */
#pragma pack(pop)
#ifdef__cplusplus
} /*extern "C"*/
#endif
#endif /*__INC_LFSCHK__H */