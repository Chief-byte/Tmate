#ifndef LFSUTILS_H
#define LFSUTILS_H

#include <wchar.h>

#include "lfsapi.h"

#include <string>

#define MAJOR(v) (v & 0xff)
#define MINOR(v) ((v & 0xff00) >> 8)

#define QS(s) qPrintable(QString::fromStdString(s))

std::string now_s();
std::string lfs_timestamp(PSYSTEMTIME ts);
char* lfs_extra(char* extra);
wchar_t* lfs_unicode_extra(wchar_t* extra);

std::string lfs_Service_class(int id);
std::string lfs_msg(int msg_id);
std::string lfs_event(int event_id);
std::string lfs_info_category(int category);
std::string lfs_exec_cmd(int cmd);
std::string lfs_error(int err);

std::string lfs_ptr_device(int device);
std::string lfs_ptr_media(int media);
std::string lfs_ptr_paper(int paper);
std::string lfs_ptr_toner(int toner);
std::string lfs_ptr_lamp(int lamp);
std::string lfs_ptr_ink(int ink);
std::string lfs_ptr_bin_status(int status);
std::string lfs_ptr_dev_type(int dev_type);
std::string lfs_ptr_resolution(int resolution);
std::string lfs_ptr_read_form(int read_form);
std::string lfs_ptr_write_form(int write_form);
std::string lfs_ptr_extents(int extents);
std::string lfs_ptr_control(int control);
std::string lfs_ptr_paper_source(int source);
std::string lfs_ptr_supply_source(int source);
std::string lfs_ptr_img_type(int img_type);
std::string lfs_ptr_img_fmt(int img_fmt);
std::string lfs_ptr_img_src(int img_src);
std::string lfs_ptr_codeline_fmt(int fmt);
std::string lfs_ptr_char_support(int support);
std::string lfs_ptr_base(int base);
std::string lfs_ptr_alignment(int alignment);
std::string lfs_ptr_orient(int orientation);
std::string lfs_ptr_media_type(int media_type);
std::string lfs_ptr_fold_type(int fold_type);
std::string lfs_ptr_field_type(int field_type);
std::string lfs_ptr_field_class(int field_class);
std::string lfs_ptr_access(int access);
std::string lfs_ptr_overflow(int overflow);
std::string lfs_ptr_print_align(int align);
std::string lfs_ptr_input_data(int input_data);
std::string lfs_ptr_status(int status);
std::string lfs_ptr_fail(int fail);

std::string lfs_pin_device(int dev);
std::string lfs_pin_enc_stat(int enc_stat);
std::string lfs_pin_dev_type(int dev_type);
std::string lfs_pin_algo(int algorithm);
std::string lfs_pin_format(int pin_format);
std::string lfs_pin_deriv_algo(int derivation_algorithm);
std::string lfs_pin_pres_algo(int presentation_algorithm);
std::string lfs_pin_display(int display);
std::string lfs_pin_id_connect(int id_connect);
std::string lfs_pin_id_key(int id_key);
std::string lfs_pin_val_algo(int validation_algorithm);
std::string lfs_pin_check_mode(int key_check_mode);
std::string lfs_pin_fdk(int fdk);
std::string lfs_pin_key_entry_mode(int key_entry_mode);
std::string lfs_pin_mode(int mode);
std::string lfs_pin_use(int use);
std::string lfs_pin_completion(int comp);
std::string lfs_pin_prot(int prot);
std::string lfs_pin_enc_prot(int prot);
std::string lfs_pin_init_mode(int mode);
std::string lfs_pin_func_mask(int key_value);

std::string lfs_siu_device(int device);
std::string lfs_siu_sensor(int sensor);
std::string lfs_siu_sensor_status(int sensor, int status);
std::string lfs_siu_door(int door);
std::string lfs_siu_door_status(int status);
std::string lfs_siu_door_status_set(int door, int status);
std::string lfs_siu_indicator(int indicator);
std::string lfs_siu_indicator_status(int status);
std::string lfs_siu_indicator_status_set(int indicator, int status);
std::string lfs_siu_aux(int aux);
std::string lfs_siu_aux_status(int aux, int status);
std::string lfs_siu_aux_status_set(int aux, int status);
std::string lfs_siu_guid(int guid);
std::string lfs_siu_guid_status(int status);
std::string lfs_siu_guid_status_set(int status);
std::string lfs_siu_type(int dev_type);
std::string lfs_siu_availability(int available);
std::string lfs_siu_sensor_avail(int sensor, int avail);
std::string lfs_siu_aux_avail(int aux, int avail);
std::string lfs_siu_aux_cmd(int aux, int cmd);
std::string lfs_siu_indicator_cmd(int indi, int cmd);
std::string lfs_siu_door_cmd(int door, int cmd);
std::string lfs_siu_enable(int enable);
std::string lfs_siu_error(int error);

std::string lfs_idc_device(int device);
std::string lfs_idc_data_source(int src, bool allow0 = true);
std::string lfs_idc_data_status(int status);
std::string lfs_idc_protocol(int prot, bool allow0 = true);
std::string lfs_idc_action(int action);
std::string lfs_idc_position(int position);
std::string lfs_idc_bin(int bin);
std::string lfs_idc_security(int security);
std::string lfs_idc_chip_power(int chip_power);
std::string lfs_idc_dev_type(int dev_type);
std::string lfs_idc_sec_type(int sec_type);
std::string lfs_idc_power_option(int power_option);
std::string lfs_idc_write_mode(int write_mode);
std::string lfs_idc_caps_chip_power(int caps_chip_power);
std::string lfs_idc_rw_action(int rw_action);
std::string lfs_idc_chip_prot(int prot);

std::string lfs_cim_dev(int dev);
std::string lfs_cim_door(int door);
std::string lfs_cim_acc(int acc);
std::string lfs_cim_int_stack(int stack);
std::string lfs_cim_stack_items(int si);
std::string lfs_cim_note_reader(int rd);
std::string lfs_cim_pos(int pos, bool allow_null = true);
std::string lfs_cim_shutter(int shutter);
std::string lfs_cim_pos_status(int status);
std::string lfs_cim_transport(int transport);
std::string lfs_cim_transport_status(int status);
std::string lfs_cim_dev_type(int t);
std::string lfs_cim_ex_type(int t);
std::string lfs_cim_retract_area(int area);
std::string lfs_cim_retract_action(int act);
std::string lfs_cim_ci_type(int t);
std::string lfs_cim_ci_item_type(int t);
std::string lfs_cim_cu_status(int status);
std::string lfs_cim_ci_status(int status);
std::string lfs_cim_failure(int fail);
std::string lfs_cim_refuse_reason(int reason);
std::string lfs_cim_note_error(int error);

std::string lfs_cdm_device(int device);
std::string lfs_cdm_door(int door);
std::string lfs_cdm_dispenser(int dispenser);
std::string lfs_cdm_is(int is);
std::string lfs_cdm_shutter(int shutter);
std::string lfs_cdm_pos(int position, bool allow_null = true);
std::string lfs_cdm_input_pos(int position);
std::string lfs_cdm_pos_status(int status);
std::string lfs_cdm_trans(int transport);
std::string lfs_cdm_trans_status(int status);
std::string lfs_cdm_dev_type(int dev_type);
std::string lfs_cdm_action(int action);
std::string lfs_cdm_ex_type(int ex_type);
std::string lfs_cdm_move_item(int item);
std::string lfs_cdm_area(int area);
std::string lfs_cdm_cu_type(int cu_type);
std::string lfs_cdm_p_status(int status);
std::string lfs_cdm_mix_type(int mix_type);
std::string lfs_cdm_sub_type(int sub_type);
std::string lfs_cdm_present_state(int state);
std::string lfs_cdm_fail(int failure);
std::string lfs_cdm_note_error(int err);
std::string lfs_cdm_teller_action(int action);

std::string lfs_vdm_device(int device);
std::string lfs_vdm_status(int status);

std::string lfs_crd_device(int device);
std::string lfs_crd_dispenser(int dispenser);
std::string lfs_crd_transport(int transport);
std::string lfs_crd_media(int meida);
std::string lfs_crd_shutter(int shutter);
std::string lfs_crd_guidlight_value(int guidLightStatus);
std::string lfs_crd_position(int position);
std::string lfs_crd_antiFraudModule(int antiFraudModule);
std::string lfs_crd_dispense_to(int dispense_to);
std::string lfs_crd_cu_status(int status);
std::string lfs_crd_cu_type(int type);
std::string lfs_crd_action(int action);
std::string lfs_crd_cu_failure(int failure);

std::string lfs_cam_device(int device);
std::string lfs_cam_cameras_source(int source);
std::string lfs_cam_media(int device);
std::string lfs_cam_status_cameras(int device);
std::string lfs_cam_dev_type(int dev_type);
std::string lfs_cam_caps_cameras(int device);
std::string lfs_cam_cam_data(int camdata);
std::string lfs_cam_char_support(int charsupport);
std::string lfs_cam_afm(int afm);
std::string lfs_cam_action(int charsupport);
std::string lfs_cam_importkey_use(int use);
std::string lfs_cam_key_check_mode(int mode);
std::string lfs_cam_signdata_status(int status);
std::string lfs_cam_scansize(int scansize);

std::string lfs_bcr_status_device(int device);
std::string lfs_bcr_status_scanner(int scanner);
std::string lfs_bcr_device_position(int position);
std::string lfs_bcr_symbologies(int symbology);
std::string lfs_bcr_guidlights_source(int source);
std::string lfs_bcr_guidlights(int guidlight);
std::string lfs_bcr_afm(int afm);


#endif  // LFSUTILS_H
