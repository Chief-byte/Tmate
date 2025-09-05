/*******************************************************************************
 *                                                                             *
 * lfspinchn.h   LFS - Personal Identification Number Keypad (PIN) China       *
 *                     Protocol definitions                                    *
 *                                                                             *
 *                     Version 1.00  -  (2020-02)                              *
 *                                                                             *
 *******************************************************************************/
#ifndef __INC_LFSPINCHN__H
#define __INC_LFSPINCHN__H

#ifdef __cplusplus
extern "C" {
#endif

/*   be aware of alignment   */
#pragma pack(push, 1)

/* values of PROTCHNIN.command */

#define LFS_CMD_ENC_IO_CHN_DIGEST                        (0x0001)
#define LFS_CMD_ENC_IO_CHN_SET_SM2_PARAM                 (0x0002)
#define LFS_CMD_ENC_IO_CHN_IMPORT_SM2_PUBLIC_KEY         (0x0003)
#define LFS_CMD_ENC_IO_CHN_SIGN                          (0x0004)
#define LFS_CMD_ENC_IO_CHN_VERIFY                        (0x0005)
#define LFS_CMD_ENC_IO_CHN_EXPORT_SM2_ISSUER_SIGNED_ITEM (0x0006)
#define LFS_CMD_ENC_IO_CHN_GENERATE_SM2_KEY_PAIR         (0x0007)
#define LFS_CMD_ENC_IO_CHN_EXPORT_SM2_EPP_SIGNED_ITEM    (0x0008)
#define LFS_CMD_ENC_IO_CHN_IMPORT_SM2_SIGNED_SM4_KEY     (0x0009)

#define PROT_CHN_RESULT_OFFSET (0)

/* values of PROTCHNOUT.result */

#define PROT_CHN_SUCCESS          (0)
#define PROT_CHN_ERR_INVALID_CMD  (-(PROT_CHN_RESULT_OFFSET + 1))
#define PROT_CHN_ERR_INVALID_DATA (-(PROT_CHN_RESULT_OFFSET + 2))
#define PROT_CHN_ERR_INVALID_KEY  (-(PROT_CHN_RESULT_OFFSET + 3))

/* values of PROTCHNDIGESTOUTPUT.result, PROTCHNIMPORTSM2PUBLICKEYOUT.result,
 * PROTCHNEXPORTSM2ISSUERSIGNEDITEMOUT.result,
 * PROTCHNEXPORTSM2EPPSIGNEDITEMOUT.result and
 * PROTCHNIMPORTSM2SIGNEDSM4KEYOUTPUT.result */

#define PROT_CHN_ERR_PIN_ACCESSDENIED (-(PROT_CHN_RESULT_OFFSET + 4))

/* values of PROTCHNIMPORTSM2PUBLICKEYOUT.result, PROTCHNDIGESTOUT.result,
 * PROTCHNEXPORTSM2ISSUERSIGNEDITEMOUT.result,
 * PROTCHNEXPORTSM2EPPSIGNEDITEMOUT.result and
 * PROTCHNIMPORTSM2SIGNEDSM4KEYOUTPUT.result */

#define PROT_CHN_ERR_PIN_KEYNOTFOUND (-(PROT_CHN_RESULT_OFFSET + 5))

/* values of PROTCHNIMPORTSM2PUBLICKEYOUT.result, PROTCHNDIGESTOUT.result and
 * PROTCHNIMPORTSM2SIGNEDSM4KEYOUTPUT.result */

#define PROT_CHN_ERR_PIN_USEVIOLATION     (-(PROT_CHN_RESULT_OFFSET + 6))
#define PROT_CHN_ERR_PIN_INVALIDKEYLENGTH (-(PROT_CHN_RESULT_OFFSET + 7))

/* additional values of PROTCHNIMPORTSM2PUBLICKEYOUT.result and
 * PROTCHNIMPORTSM2SIGNEDSM4KEYOUTPUT.result */

#define PROT_CHN_ERR_PIN_DUPLICATEKEY     (-(PROT_CHN_RESULT_OFFSET + 8))
#define PROT_CHN_ERR_PIN_SIG_NOT_SUPP     (-(PROT_CHN_RESULT_OFFSET + 9))
#define PROT_CHN_ERR_PIN_SIGNATUREINVALID (-(PROT_CHN_RESULT_OFFSET + 10))

/* additional values of PROTCHNSIGNOUT.result and
 * PROTCHNIMPORTSM2SIGNEDSM4KEYOUTPUT.result */

#define PROT_CHN_ERR_PIN_MODENOTSUPPORTED  (-(PROT_CHN_RESULT_OFFSET + 11))
#define PROT_CHN_ERR_PIN_KEYNOVALUE        (-(PROT_CHN_RESULT_OFFSET + 12))
#define PROT_CHN_ERR_PIN_NOCHIPTRANSACTIVE (-(PROT_CHN_RESULT_OFFSET + 13))
#define PROT_CHN_ERR_PIN_ALGORITHMNOTSUPP  (-(PROT_CHN_RESULT_OFFSET + 14))

/* values of PROTCHNVERIFYOUT.result */

#define PROT_CHN_ERR_PIN_SIGNATUREERROR (-(PROT_CHN_RESULT_OFFSET + 15))

/* values of PROTCHNEXPORTSM2ISSUERSIGNEDITEMOUT.result */

#define PROT_CHN_ERR_PIN_NOPRIVATEKEY (-(PROT_CHN_RESULT_OFFSET + 16))

/* values of PROTCHNGENERATESM2KEYOUT.result */

#define PROT_CHN_ERR_PIN_INVALID_MOD_LEN      (-(PROT_CHN_RESULT_OFFSET + 17))
#define PROT_CHN_ERR_PIN_KEY_GENERATION_ERROR (-(PROT_CHN_RESULT_OFFSET + 18))

/* values of PROTCHNEXPORTSM2EPPSIGNEDITEMOUT.result */

#define PROT_CHN_ERR_PIN_NOSM2KEYPAIR (-(PROT_CHN_RESULT_OFFSET + 19))

/* values of PROTCHNIMPORTSM2SIGNEDSM4KEYOUTPUT.result */

#define PROT_CHN_ERR_PIN_NOKEYRAM      (-(PROT_CHN_RESULT_OFFSET + 20))
#define PROT_CHN_ERR_PIN_RANDOMINVALID (-(PROT_CHN_RESULT_OFFSET + 21))

/* values of PROTCHNDIGESTIN.wHashAlgorithm */

#define PROT_CHN_HASH_SM3_DIGEST (0x0001)

/* values for PROTCHNIMPORTSM2PUBLICKEYIN.dwUse */

#define PROT_CHN_USESM2PUBLIC       (0x00000001)
#define PROT_CHN_USESM2PUBLICVERIFY (0x00000002)

/* values of PROTCHNIMPORTSM2PUBLICKEYIN.dwSM2SignatureAlgorithm,
 * PROTCHNEXPORTSM2ISSUERSIGNEDITEMOUT.dwSM2SignatureAlgorithm,
 * PROTCHNEXPORTSM2EPPSIGNEDITEMIN.dwSignatureAlgorithm and
 * PROTCHNIMPORTSM2SIGNEDSM4KEY.dwSM2SignatureAlgorithm */

#define PROT_CHN_PIN_SIGN_NA        (0)
#define PROT_CHN_SIGN_SM2_GM_T_2012 (0x00000001)

/* values for PROTCHNIMPORTSM2PUBLICKEYOUT.dwSM2KeyCheckMode */
#define PROT_CHN_SM2_KCV_NONE (0x00000001)
#define PROT_CHN_SM2_KCV_SM3  (0x00000002)

/* values for PROTCHNEXPORTSM2ISSUERSIGNEDITEMIN.wExportItemType,
 * PROTCHNEXPORTSM2EPPSIGNEDITEMIN.wExportItemType */

#define PROT_CHN_PIN_EXPORT_EPP_ID     (0x0001)
#define PROT_CHN_PIN_EXPORT_PUBLIC_KEY (0x0002)

/* values for PROTCHNGENERATESM2KEYOUT.dwUse */
#define PROT_CHN_USESM2PRIVATE     (0x00000001)
#define PROT_CHN_USESM2PRIVATESIGN (0x00000002)

// Used to type-cast specific command to access common fields
typedef struct _prot_chn_in {
  WORD command;
} PROTCHNIN, *LPPROTCHNIN;

// Used to type-cast specific response to access common fields
typedef struct _prot_chn_out {
  WORD command;
  WORD result;
} PROTCHNOUT, *LPPROTCHNOUT;

typedef struct _prot_chn_digest_in {
  WORD command;
  WORD hash_algorithm;
  LPLFSXDATA digest_input;
} PROTCHNDIGESTIN, *LPPROTCHNDIGESTIN;

typedef struct _prot_chn_digest_out {
  WORD command;
  WORD result;
  LPLFSXDATA digest_output;
  ;
} PROTCHNDIGESTOUT, *LPPROTCHNDIGESTOUT;

typedef struct _prot_chn_sm2_algorithm_param_in {
  WORD command;
  LPLFSXDATA P;
  LPLFSXDATA A;
  LPLFSXDATA B;
  LPLFSXDATA N;
  LPLFSXDATA Xg;
  LPLFSXDATA Yg;
} PROTCHNSM2ALGORITHMPARAMIN, *LPPROTCHNSM2ALGORITHMPARAMIN;

typedef struct _prot_chn_sm2_algorithm_param_out {
  WORD command;
  WORD result;
} PROTCHNSM2ALGORITHMPARAMOUT, *LPPROTCHNSM2ALGORITHMPARAMOUT;

typedef struct _prot_chn_import_sm2_public_key_in {
  WORD command;
  LPSTR key;
  LPLFSXDATA value;
  DWORD use;
  LPSTR sig_key;
  DWORD sm2_signature_algorithm;
  LPLFSXDATA signature;
} PROTCHNIMPORTSM2PUBLICKEYIN, *LPPROTCHNIMPORTSM2PUBLICKEYIN;

typedef struct _prot_chn_import_sm2_public_key_out {
  WORD command;
  WORD result;
  DWORD sm2_key_check_mode;
  LPLFSXDATA key_check_value;
} PROTCHNIMPORTSM2PUBLICKEYOUT, *LPPROTCHNIMPORTSM2PUBLICKEYOUT;

typedef struct _prot_chn_sign_in {
  WORD command;
  LPSTR key;
  LPSTR signer_id;
  LPLFSXDATA plaintext_data;
} PROTCHNSIGNIN, *LPPROTCHNSIGNIN;

typedef struct _prot_chn_sign_out {
  WORD command;
  WORD result;
  LPLFSXDATA sign_data;
} PROTCHNSIGNOUT, *LPPROTCHNSIGNOUT;

typedef struct _prot_chn_verify_in {
  WORD command;
  LPSTR key;
  LPLFSXDATA plaintext_data;
  LPLFSXDATA sign_data;
} PROTCHNVERIFYIN, *LPPROTCHNVERIFYIN;

typedef struct _prot_chn_verify_out {
  WORD command;
  WORD result;
} PROTCHNVERIFYOUT, *LPPROTCHNVERIFYOUT;

typedef struct _prot_chn_export_sm2_issuer_signed_item_in {
  WORD command;
  WORD export_item_type;
  LPSTR name;
} PROTCHNEXPORTSM2ISSUERSIGNEDITEMIN, *LPPROTCHNEXPORTSM2ISSUERSIGNEDITEMIN;

typedef struct _prot_chn_export_sm2_issuer_signed_item_out {
  WORD command;
  WORD result;
  LPLFSXDATA value;
  DWORD sm2_signature_algorithm;
  LPLFSXDATA signature;
} PROTCHNEXPORTSM2ISSUERSIGNEDITEMOUT, *LPPROTCHNEXPORTSM2ISSUERSIGNEDITEMOUT;

typedef struct _prot_chn_generate_sm2_keypair_in {
  WORD command;
  LPSTR key;
  DWORD use;
} PROTCHNGENERATESM2KEYPAIRIN, *LPPROTCHNGENERATESM2KEYPAIRIN;

typedef struct _prot_chn_generate_sm2_keypair_out {
  WORD command;
  WORD result;
} PROTCHNGENERATESM2KEYPAIROUT, *LPPROTCHNGENERATESM2KEYPAIROUT;

typedef struct _prot_chn_export_sm2_epp_signed_item_in {
  WORD command;
  WORD export_item_type;
  LPSTR name;
  LPSTR sig_key;
  DWORD signature_algorithm;
} PROTCHNEXPORTSM2EPPSIGNEDITEMIN, *LPPROTCHNEXPORTSM2EPPSIGNEDITEMIN;

typedef struct _prot_chn_export_sm2_epp_signed_item_out {
  WORD command;
  WORD result;
  LPLFSXDATA value;
  WORD sm2_signature_algorithm;
  LPLFSXDATA signature;
} PROTCHNEXPORTSM2EPPSIGNEDITEMOUT, *LPPROTCHNEXPORTSM2EPPSIGNEDITEMOUT;

typedef struct _prot_chn_import_sm2_signed_sm4_key {
  WORD command;
  LPSTR key;
  LPSTR decrypt_key;
  DWORD sm2_eEncipher_algorithm;
  LPLFSXDATA value;
  DWORD use;
  LPSTR sig_key;
  DWORD sm2_signature_algorithm;
  LPLFSXDATA signature;

} PROTCHNIMPORTSM2SIGNEDSM4KEY, *LPPROTCHNIMPORTSM2SIGNEDSM4KEY;

typedef struct _prot_chn_import_sm2_signed_sm4_key_output {
  WORD command;
  WORD result;
  WORD key_check_mode;
  LPLFSXDATA key_check_value;
} PROTCHNIMPORTSM2SIGNEDSM4KEYOUTPUT, *LPPROTCHNIMPORTSM2SIGNEDSM4KEYOUTPUT;

/* restore alignment */
#pragma pack(pop)

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* __INC_LFSPINCHN__H */
