#ifndef _SSM_H__
#define _SSM_H__

#ifdef __cplusplus
#define EXTERNC_START \
    extern "C"        \
    {
#else
#define EXTERNC_START
#endif

#ifdef __cplusplus
#define EXTERNC_END }
#else
#define EXTERNC_END
#endif

#include <stdio.h>
#include <stddef.h>

EXTERNC_START

#ifdef WIN32
#define snprintf _snprintf
#define popen _popen
#define pclose _pclose

#ifdef ssm_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#else
#define DLL_API 
#endif


#define SSM_VERSION "1.0.18"


typedef enum
{
    SSMPaddingNoPadding,
    SSMPaddingZeroPadding,
    SSMPaddingPKCS7Padding,
    SSMPaddingISO10126Padding,

    SSMPaddingPKCS1Padding,
    SSMPaddingPKCS8Padding,
    SSMPaddingOAEPPadding,
    SSMPaddingPSSPadding
} SSMPadding;

typedef enum
{
    SSMAlgorithm_SM4,
    SSMAlgorithm_AES,
    SSMAlgorithm_DES,
    SSMAlgorithm_RSA,
    SSMAlgorithm_SM2,
    SSMAlgorithm_ECC
} SSMAlgorithm;

typedef enum
{
    SSMAlgorithmSM3,
    SSMAlgorithmSHA1,
    SSMAlgorithmSHA224,
    SSMAlgorithmSHA256,
    SSMAlgorithmSHA384,
    SSMAlgorithmSHA512,
    SSMAlgorithmSHA3_224,
    SSMAlgorithmSHA3_256,
    SSMAlgorithmSHA3_384,
    SSMAlgorithmSHA3_512,
    SSMAlgorithmSHA512_224,
    SSMAlgorithmSHA512_256,
    SSMAlgorithmMD5
} SSMHashAlgorithm;

typedef enum
{
    SSMKeyBits_64 = 64,
    SSMKeyBits_128 = 128,
    SSMKeyBits_192 = 192,
    SSMKeyBits_256 = 256
} SSMKeyBits;

typedef enum
{
    SSMEncryptModeECB,
    SSMEncryptModeCBC,
    SSMEncryptModeCFB,
    SSMEncryptModeOFB,
    SSMEncryptModeCTR,
    SSMEncryptModeGCM
} SSMEncryptMode;

typedef struct
{
    SSMAlgorithm Algorithm;
    SSMKeyBits bits;
    unsigned char Key[64];
    int KeyLen;
    char KeyID[128];
} SSMSymmetricKey;

typedef struct
{
    SSMAlgorithm Algorithm;
    unsigned char PublicKey[1024];
    int PublicKeyLen;
    unsigned char PrivateKey[4096];
    int PrivateKeyLen;
    char KeyID[128];
} SSMAsymmetricKey;

typedef struct
{
    unsigned char Data[512];
    size_t DataLen;
    char KeyID[128];
} SSMSecretData;

typedef enum
{
    SSMBlockTypeOnly,
    SSMBlockTypeFirst,
    SSMBlockTypeMiddle,
    SSMBlockTypeLast
} SSMBlockType;

typedef enum
{
    SSMSM2EncryptModeC1C3C2,
    SSMSM2EncryptModeC1C2C3
} SSMSM2EncryptMode;

typedef struct {
	int Expiration; // 有效期，秒数
	int Export; //允许导出
} SSMKeyAttributes;

/**
 * @brief 创建密钥对象
 *
 */
/*
DLL_API void SSMInitSecretData(const unsigned char *data, size_t dataLen, SSMSecretData *secretData);
DLL_API void SSMInitSecretDataByID(const char *keyID, SSMSecretData *secretData);
DLL_API void SSMInitSymmetricKey(const unsigned char *keyValue, size_t keyValueLen, SSMAlgorithm alg, SSMSymmetricKey *key);
DLL_API void SSMInitSymmetricKeyByID(const char *keyID, SSMSymmetricKey *key);
DLL_API void SSMInitPublicKey(const unsigned char *publicKey, size_t publicKeyLen, SSMAlgorithm alg, SSMAsymmetricKey *key);
DLL_API void SSMInitPublicKeyByID(const char *keyID, SSMAsymmetricKey *key);
DLL_API void SSMInitPrivateKey(const unsigned char *privateKey, size_t privateKeyLen, SSMAlgorithm alg, SSMAsymmetricKey *key);
DLL_API void SSMInitPrivateKeyByID(const char *keyID, SSMAsymmetricKey *key);
//*/

/**
 * @brief SSM Instance 客户端
 *
 */

typedef struct SSMContext SSMContext;
typedef struct SSMInstance SSMInstance;

/*
DLL_API SSMContext *SSMNewContext(const char *server_host);
DLL_API SSMContext *SSMNewContext_AutoCall(const char *ssmdDir);
DLL_API SSMContext *SSMNewContext_AutoCall_Debug(const char *ssmdDir);
DLL_API SSMContext *SSMNewContext_AutoCallForCSSP(const char *ssmdDir, const char *csspAddr, const char *timeout);
DLL_API SSMContext *SSMNewContext_AutoCallForCSSP_Debug(const char *ssmdDir, const char *csspAddr, const char *timeout);

DLL_API SSMInstance *SSMNewInstance(SSMContext *context, int connTimeout, int sendTimeout, int recvTimeout, int keepAlive);

DLL_API SSMInstance *SSMNewInstanceForCSSP(SSMContext *context, const char *accessKey, const char *secretKey, int connTimeout, int sendTimeout, int recvTimeout, int keepAlive);

DLL_API void SSMFreeContext(SSMContext *context);

DLL_API void SSMFreeInstance(SSMInstance *instance);

DLL_API int SSMVersion(SSMInstance *instance, SSMAsymmetricKey *pub,
                unsigned char *name, size_t nameSize,
                unsigned char *version, size_t versionSize,
                unsigned char *apiVersion, size_t apiVersionSize,
                unsigned char *buildtime, size_t buildtimeSize,
                int *official);
//*/
typedef SSMContext * (* PSSMNewContext_AutoCall)(const char *ssmdDir);
typedef SSMInstance * (* PSSMNewInstance)(SSMContext *context, int connTimeout, int sendTimeout, int recvTimeout, int keepAlive);
typedef void (* PSSMFreeContext)(SSMContext *context);
typedef void (* PSSMFreeInstance)(SSMInstance *instance);

/**
 * @brief 销毁密钥库
 *
 */
DLL_API int SSMReset(SSMInstance *instance);


/**
 * @brief 生成密钥
 *
 */
/*
DLL_API int SSMGenerateSM2(SSMInstance *instance, SSMAsymmetricKey *asymmetricKey);

DLL_API int SSMGenerateRSA(SSMInstance *instance, int bits, int exponent, SSMAsymmetricKey *asymmetricKey);
DLL_API int SSMGenerateECC(SSMInstance *instance, int bits, SSMAsymmetricKey *asymmetricKey);

DLL_API int SSMGenerateSM4(SSMInstance *instance, SSMSymmetricKey *symmetricKey);
DLL_API int SSMGenerateAES(SSMInstance *instance, int bits, SSMSymmetricKey *symmetricKey);
DLL_API int SSMGenerateDES(SSMInstance *instance, int bits, SSMSymmetricKey *symmetricKey);
//*/
typedef int (* PSSMGenerateSM2)(SSMInstance *instance, SSMAsymmetricKey *asymmetricKey);

/**
 * @brief 创建密钥对象
 *
 */
/*
DLL_API int SSMCreateSM4(SSMInstance *instance, SSMKeyAttributes *attr, SSMSymmetricKey *symmetricKey);
DLL_API int SSMCreateAES(SSMInstance *instance, int bits, SSMKeyAttributes *attr, SSMSymmetricKey *symmetricKey);
DLL_API int SSMCreateDES(SSMInstance *instance, int bits, SSMKeyAttributes *attr, SSMSymmetricKey *symmetricKey);

DLL_API int SSMCreateSM2(SSMInstance *instance, SSMKeyAttributes *attr, SSMAsymmetricKey *asymmetricKey);
DLL_API int SSMCreateRSA(SSMInstance *instance, int bits, int exponent, SSMKeyAttributes *attr, SSMAsymmetricKey *asymmetricKey);
DLL_API int SSMCreateECC(SSMInstance *instance, int bits, SSMKeyAttributes *attr, SSMAsymmetricKey *asymmetricKey);
DLL_API int SSMCreateSecret(SSMInstance *instance, int length, SSMKeyAttributes *attr, SSMSecretData *secretData);
//*/
typedef int (* PSSMCreateSM2)(SSMInstance *instance, SSMKeyAttributes *attr, SSMAsymmetricKey *asymmetricKey);

/**
 * @brief 销毁密钥
 *
 */
/*
DLL_API int SSMDestroySymmetricKey(SSMInstance *instance, char *keyId);
DLL_API int SSMDestroyPublicKey(SSMInstance *instance, char *keyId);
DLL_API int SSMDestroyPrivateKey(SSMInstance *instance, char *keyId);
DLL_API int SSMDestroySecret(SSMInstance *instance, char *keyId);
//*/

/**
 * @brief 导入密钥
 *
 */
/*
DLL_API int SSMImportSM4(SSMInstance *instance, unsigned char *keyValue, int keyValueLen, SSMSymmetricKey *key);
DLL_API int SSMImportAES(SSMInstance *instance, unsigned char *keyValue, int keyValueLen, SSMSymmetricKey *key);
DLL_API int SSMImportDES(SSMInstance *instance, unsigned char *keyValue, int keyValueLen, SSMSymmetricKey *key);
DLL_API int SSMImportSM2PublicKey(SSMInstance *instance, unsigned char *publicKey, int publicKeyLen, SSMAsymmetricKey *key);
DLL_API int SSMImportRSAPublicKey(SSMInstance *instance, unsigned char *publicKey, int publicKeyLen, SSMAsymmetricKey *key);
DLL_API int SSMImportECCPublicKey(SSMInstance *instance, unsigned char *publicKey, int publicKeyLen, SSMAsymmetricKey *key);
DLL_API int SSMImportSecret(SSMInstance *instance, unsigned char *secret, int secretLen, SSMSecretData *secretData);
//*/
typedef int (* PSSMImportSM2PublicKey)(SSMInstance *instance, unsigned char *publicKey, int publicKeyLen, SSMAsymmetricKey *key);

/**
 * @brief 导出密钥
 *
 */
/*
DLL_API int SSMExportSM4(SSMInstance *instance, unsigned char *keyID, SSMSymmetricKey *key);
DLL_API int SSMExportAES(SSMInstance *instance, unsigned char *keyID, SSMSymmetricKey *key);
DLL_API int SSMExportDES(SSMInstance *instance, unsigned char *keyID, SSMSymmetricKey *key);
DLL_API int SSMExportSM2PublicKey(SSMInstance *instance, unsigned char *keyID, SSMAsymmetricKey *key);
DLL_API int SSMExportRSAPublicKey(SSMInstance *instance, unsigned char *keyID, SSMAsymmetricKey *key);
DLL_API int SSMExportECCPublicKey(SSMInstance *instance, unsigned char *keyID, SSMAsymmetricKey *key);
DLL_API int SSMExportSecret(SSMInstance *instance, unsigned char *keyID, SSMSecretData *secretData);
//*/
typedef int (* PSSMExportSM2PublicKey)(SSMInstance *instance, unsigned char *keyID, SSMAsymmetricKey *key);

/**
 * @brief hash计算
 *
 */
/*
DLL_API int SSMSM3(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSM3Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSM3Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
               SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSM3HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSM3HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
               SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSM3HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSM3Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
               SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSM3Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSM3HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
               SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSM3HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA1(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSHA1Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSHA1Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
                SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA1HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA1HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
                SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA1HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA1Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSHA1Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSHA1HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA1HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA224(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSHA224Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSHA224Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData, unsigned char *hmacData);
            
DLL_API int SSMSHA224HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA224HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA224HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA224Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSHA224Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSHA224HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA224HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA256(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSHA256Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSHA256Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA256HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA256HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA256HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA256Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSHA256Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSHA256HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA256HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA384(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSHA384Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSHA384Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA384HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA384HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA384HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA384Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSHA384Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSHA384HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA384HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA512(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSHA512Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSHA512Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA512HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA512HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA512HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA512Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSHA512Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSHA512HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                  SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA512HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_224(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSHA3_224Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSHA3_224Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA3_224HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA3_224HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_224HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_224Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSHA3_224Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSHA3_224HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_224HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_256(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSHA3_256Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSHA3_256Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA3_256HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA3_256HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_256HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_256Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSHA3_256Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSHA3_256HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_256HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_384(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSHA3_384Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSHA3_384Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA3_384HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA3_384HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_384HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_384Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSHA3_384Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSHA3_384HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_384HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_512(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSHA3_512Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSHA3_512Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA3_512HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA3_512HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_512HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_512Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSHA3_512Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSHA3_512HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                    SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA3_512HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA512_224(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSHA512_224Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSHA512_224Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
                      SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA512_224HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA512_224HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
                      SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA512_224HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA512_224Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                      SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSHA512_224Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSHA512_224HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                      SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA512_224HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA512_256(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMSHA512_256Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMSHA512_256Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
                      SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA512_256HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMSHA512_256HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
                      SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);
        
DLL_API int SSMSHA512_256HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA512_256Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                      SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData);

DLL_API int SSMSHA512_256Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMSHA512_256HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
                      SSMSecretData *secretData,SSMPadding padding, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMSHA512_256HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMMD5(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash);

DLL_API int SSMMD5Verify(SSMInstance *instance, unsigned char *data, size_t data_len, unsigned char *hash, size_t hashLen);

DLL_API int SSMMD5Hmac(SSMInstance *instance, unsigned char *data, size_t data_len,
              SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMMD5HmacStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData);

DLL_API int SSMMD5HmacVerify(SSMInstance *instance, unsigned char *data, size_t data_len,
              SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMMD5HmacVerifyStream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMMD5Hmac_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
              SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMMD5Hmac_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData);

DLL_API int SSMMD5HmacVerify_Padding(SSMInstance *instance, unsigned char *data, size_t data_len,
              SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);

DLL_API int SSMMD5HmacVerify_Padding_Stream(SSMInstance *instance, FILE *reader, SSMSecretData *secretData, SSMPadding pad, unsigned char *hmacData, size_t hmacLen);
//*/
typedef int (* PSSMSM3HmacVerify)(SSMInstance *instance, unsigned char *data, size_t data_len,
               SSMSecretData *secretData, unsigned char *hmacData, size_t hmacLen);

/**
 * @brief 计算MAC
 *
 */
/*
DLL_API int SSMCMAC(SSMInstance *instance, SSMSymmetricKey *key, unsigned char *data, int dataLen, unsigned char *mac, int macSize);

DLL_API int SSMCBCMAC(SSMInstance *instance, SSMSymmetricKey *key, unsigned char *data, int dataLen, unsigned char *mac, int macSize);

DLL_API int SSMX9_9MAC(SSMInstance *instance, SSMSymmetricKey *key, unsigned char *data, int dataLen, unsigned char *mac, int macSize);

DLL_API int SSMX9_19MAC(SSMInstance *instance, SSMSymmetricKey *key, unsigned char *data, int dataLen, unsigned char *mac, int macSize);
//*/

/**
 * @brief 对称密钥加密
 *
 */
/*
DLL_API int SSMSymECBEncrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey, SSMPadding padding,
                     unsigned char *data, size_t dataLen, unsigned char *out, size_t outSize);

DLL_API int SSMSymECBEncryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey, SSMPadding padding,
                           FILE *reader, FILE *writer);

DLL_API int SSMSymECBDecrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey, SSMPadding padding,
                     unsigned char *data, size_t dataLen, unsigned char *out, size_t outSize);

DLL_API int SSMSymECBDecryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey, SSMPadding padding,
                           FILE *reader, FILE *writer);

DLL_API int SSMSymCBCEncrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey, SSMPadding padding,
                     unsigned char *data, size_t dataLen,
                     unsigned char *iv, size_t ivLen,
                     unsigned char *out, size_t outSize);

DLL_API int SSMSymCBCEncryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey, SSMPadding padding,
                           FILE *reader, FILE *writer, unsigned char *outiv, size_t *outivLen);

DLL_API int SSMSymCBCDecrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey, SSMPadding padding,
                     unsigned char *data, size_t dataLen,
                     unsigned char *iv, size_t ivLen,
                     unsigned char *out, size_t outSize);

DLL_API int SSMSymCBCDecryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey, SSMPadding padding,
                           unsigned char *iv, size_t ivLen,
                           FILE *reader, FILE *writer);

DLL_API int SSMSymOFBEncrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                     unsigned char *data, size_t dataLen,
                     unsigned char *iv, size_t ivLen,
                     unsigned char *out, size_t outLen,
                     unsigned char *outiv, size_t *outivLen);

DLL_API int SSMSymOFBEncryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                           FILE *reader, FILE *writer, unsigned char *outiv, size_t *outivLen);

DLL_API int SSMSymOFBDecrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                     unsigned char *data, size_t dataLen,
                     unsigned char *iv, size_t ivLen,
                     unsigned char *out, size_t outLen);

DLL_API int SSMSymOFBDecryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                           FILE *reader, FILE *writer, unsigned char *iv, size_t ivLen);

DLL_API int SSMSymCFBEncrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                     unsigned char *data, size_t dataLen,
                     unsigned char *iv, size_t ivLen,
                     unsigned char *out, size_t outLen,
                     unsigned char *outiv, size_t *outivLen);

DLL_API int SSMSymCFBEncryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                           FILE *reader, FILE *writer, unsigned char *outiv, size_t *outivLen);

DLL_API int SSMSymCFBDecrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                     unsigned char *data, size_t dataLen,
                     unsigned char *iv, size_t ivLen,
                     unsigned char *out, size_t outLen);

DLL_API int SSMSymCFBDecryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                           FILE *reader, FILE *writer, unsigned char *iv, size_t ivLen);

DLL_API int SSMSymCTREncrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                     unsigned char *data, size_t dataLen,
                     unsigned char *iv, size_t ivLen,
                     unsigned char *out, size_t outLen,
                     unsigned char *outiv, size_t *outivLen);

DLL_API int SSMSymCTREncryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                           FILE *reader, FILE *writer, unsigned char *outiv, size_t *outivLen);

DLL_API int SSMSymCTRDecrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                     unsigned char *data, size_t dataLen,
                     unsigned char *iv, size_t ivLen,
                     unsigned char *out, size_t outLen);

DLL_API int SSMSymCTRDecryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                           FILE *reader, FILE *writer, unsigned char *iv, size_t ivLen);

DLL_API int SSMSymGCMEncrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey, unsigned char *data, size_t dataLen,
                     unsigned char *additionalData, size_t additionalDataLen,
                     unsigned char *iv, size_t ivLen,
                     unsigned char *out, size_t outLen,
                     unsigned char *outIv, size_t *outIvLen);

DLL_API int SSMSymGCMEncryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                           unsigned char *additionalData, size_t additionalDataLen,
                           FILE *reader, FILE *writer,
                           unsigned char *outIv, size_t *outIvLen);

DLL_API int SSMSymGCMDecrypt(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                     unsigned char *data, size_t dataLen,
                     unsigned char *iv, size_t ivLen,
                     unsigned char *additionalData, size_t additionalDataLen,
                     unsigned char *out, size_t outLen);

DLL_API int SSMSymGCMDecryptStream(SSMInstance *instance, SSMSymmetricKey *symmetricKey,
                           unsigned char *iv, size_t ivLen,
                           unsigned char *additionalData, size_t additionalDataLen,
                           FILE *reader, FILE *writer);
//*/

/**
 * @brief 数字信封
 *
 */
/*
DLL_API int SSMEnvelopeECBEncrypt(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub, SSMPadding padding,
                          unsigned char *data, size_t dataLen,
                          unsigned char *ciphertext, size_t ciphertextSize,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeECBEncryptStream(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub, SSMPadding padding,
                          FILE *reader, FILE *writer,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeECBDecrypt(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          SSMPadding padding,
                          unsigned char *data, size_t dataLen,
                          unsigned char *plaintext, size_t plainSize);

DLL_API int SSMEnvelopeECBDecryptStream(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          SSMPadding padding,
                          FILE *reader, FILE *writer);

DLL_API int SSMEnvelopeCBCEncrypt(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub, SSMPadding padding,
                          unsigned char *data, size_t dataLen,
                          unsigned char *ciphertext, size_t ciphertextSize,
                          unsigned char *iv, size_t *ivLen,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeCBCEncryptStream(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub, SSMPadding padding,
                          FILE *reader, FILE *writer,
                          unsigned char *iv, size_t *ivLen,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeCBCDecrypt(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          SSMPadding padding,
                          unsigned char *data, size_t dataLen,
                          unsigned char *iv, size_t ivLen,
                          unsigned char *plaintext, size_t plainSize);

DLL_API int SSMEnvelopeCBCDecryptStream(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          SSMPadding padding,
                          unsigned char *iv, size_t ivLen,
                          FILE *reader, FILE *writer);

DLL_API int SSMEnvelopeOFBEncrypt(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub,
                          unsigned char *data, size_t dataLen,
                          unsigned char *ciphertext, size_t ciphertextSize,
                          unsigned char *iv, size_t *ivLen,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeOFBEncryptStream(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub,
                          FILE *reader, FILE *writer,
                          unsigned char *iv, size_t *ivLen,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeOFBDecrypt(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          unsigned char *data, size_t dataLen,
                          unsigned char *iv, size_t ivLen,
                          unsigned char *plaintext, size_t plainSize);

DLL_API int SSMEnvelopeOFBDecryptStream(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          unsigned char *iv, size_t ivLen,
                          FILE *reader, FILE *writer);

DLL_API int SSMEnvelopeCFBEncrypt(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub,
                          unsigned char *data, size_t dataLen,
                          unsigned char *ciphertext, size_t ciphertextSize,
                          unsigned char *iv, size_t *ivLen,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeCFBEncryptStream(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub,
                          FILE *reader, FILE *writer,
                          unsigned char *iv, size_t *ivLen,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeCFBDecrypt(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          unsigned char *data, size_t dataLen,
                          unsigned char *iv, size_t ivLen,
                          unsigned char *plaintext, size_t plainSize);

DLL_API int SSMEnvelopeCFBDecryptStream(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          unsigned char *iv, size_t ivLen,
                          FILE *reader, FILE *writer);

DLL_API int SSMEnvelopeCTREncrypt(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub,
                          unsigned char *data, size_t dataLen,
                          unsigned char *ciphertext, size_t ciphertextSize,
                          unsigned char *iv, size_t *ivLen,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeCTREncryptStream(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub,
                          FILE *reader, FILE *writer,
                          unsigned char *iv, size_t *ivLen,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeCTRDecrypt(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          unsigned char *data, size_t dataLen,
                          unsigned char *iv, size_t ivLen,
                          unsigned char *plaintext, size_t plainSize);

DLL_API int SSMEnvelopeCTRDecryptStream(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          unsigned char *iv, size_t ivLen,
                          FILE *reader, FILE *writer);

DLL_API int SSMEnvelopeGCMEncrypt(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub,
                          unsigned char *data, size_t dataLen,
                          unsigned char *additionalData, size_t additionalDataLen,
                          unsigned char *ciphertext, size_t ciphertextSize,
                          unsigned char *iv, size_t *ivLen,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeGCMEncryptStream(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub,
                          FILE *reader, FILE *writer,
                          unsigned char *additionalData, size_t additionalDataLen,
                          unsigned char *iv, size_t *ivLen,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);

DLL_API int SSMEnvelopeGCMDecrypt(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          unsigned char *data, size_t dataLen,
                          unsigned char *iv, size_t ivLen,
                          unsigned char *additionalData, size_t additionalDataLen,
                          unsigned char *plaintext, size_t plainSize);

DLL_API int SSMEnvelopeGCMDecryptStream(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          unsigned char *iv, size_t ivLen,
                          unsigned char *additionalData, size_t additionalDataLen,
                          FILE *reader, FILE *writer);

DLL_API int SSMEnvelopeHmac(SSMInstance *instance, SSMHashAlgorithm alg, size_t bits,
                    SSMAsymmetricKey *pub, SSMPadding pad,
                    unsigned char *data, size_t dataLen,
                    unsigned char *key, size_t *keyLen,
                    unsigned char *hmac, size_t hmacLen,
                    SSMSecretData *secretData);

DLL_API int SSMEnvelopeHmacVerify(SSMInstance *instance, SSMHashAlgorithm alg, size_t bits,
                    SSMAsymmetricKey *priv, SSMPadding pad,
                    unsigned char *data, size_t dataLen,
                    unsigned char *key, size_t keyLen,
                    unsigned char *hmac, size_t hmacLen,
                    int *result);

DLL_API int SSMEnvelopeHmacStream(SSMInstance *instance, SSMHashAlgorithm alg, size_t bits,
                    SSMAsymmetricKey *pub, SSMPadding pad,
                    FILE *reader,
                    unsigned char *key, size_t *keyLen,
                    unsigned char *hmac, size_t hmacLen,
                    SSMSecretData *secretData);

DLL_API int SSMEnvelopeHmacVerifyStream(SSMInstance *instance, SSMHashAlgorithm alg, size_t bits,
                   SSMAsymmetricKey *priv, SSMPadding pad,
                    FILE *reader,
                    unsigned char *key, size_t keyLen,
                    unsigned char *hmac, size_t hmacLen,
                    int *result);
//*/
typedef int (* PSSMEnvelopeECBEncrypt)(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
                          SSMAsymmetricKey *pub, SSMPadding padding,
                          unsigned char *data, size_t dataLen,
                          unsigned char *ciphertext, size_t ciphertextSize,
                          unsigned char *keyByPk, size_t keyByPkSize,
                          size_t *keyByPkLen, SSMSymmetricKey *key);
typedef int (* PSSMEnvelopeECBDecrypt)(SSMInstance *instance, SSMAlgorithm alg,
                          SSMAsymmetricKey *priv,
                          unsigned char *keyByPk, size_t keyByPkLen,
                          SSMPadding padding,
                          unsigned char *data, size_t dataLen,
                          unsigned char *plaintext, size_t plainSize);
typedef int (* PSSMEnvelopeHmac)(SSMInstance *instance, SSMHashAlgorithm alg, size_t bits,
                    SSMAsymmetricKey *pub, SSMPadding pad,
                    unsigned char *data, size_t dataLen,
                    unsigned char *key, size_t *keyLen,
                    unsigned char *hmac, size_t hmacLen,
                    SSMSecretData *secretData);
typedef int (* PSSMEnvelopeHmacVerify)(SSMInstance *instance, SSMHashAlgorithm alg, size_t bits,
                    SSMAsymmetricKey *priv, SSMPadding pad,
                    unsigned char *data, size_t dataLen,
                    unsigned char *key, size_t keyLen,
                    unsigned char *hmac, size_t hmacLen,
                    int *result);


/**
 * @brief 非对称密钥加解密
 *
 */
/*
DLL_API int SSMSM2Encrypt(SSMInstance *instance, SSMAsymmetricKey *pub,
                  unsigned char *data, size_t dataLen,
                  SSMSM2EncryptMode mode,
                  unsigned char *cipher, size_t cipherSize);

DLL_API int SSMSM2Decrypt(SSMInstance *instance, SSMAsymmetricKey *priv,
                  unsigned char *data, size_t dataLen,
                  SSMSM2EncryptMode mode,
                  unsigned char *plain, size_t plainSize);

DLL_API int SSMRSAEncryptPKCS1v15(SSMInstance *instance, SSMAsymmetricKey *pub,
                          unsigned char *data, size_t dataLen,
                          unsigned char *cipher, size_t cipherSize);
DLL_API int SSMRSADecryptPKCS1v15(SSMInstance *instance, SSMAsymmetricKey *priv,
                          unsigned char *data, size_t dataLen,
                          unsigned char *plain, size_t plainSize);

DLL_API int SSMRSAEncryptOAEP(SSMInstance *instance, SSMAsymmetricKey *pub,
                      unsigned char *data, size_t dataLen,
                      SSMHashAlgorithm hashAlgorithm,
                      unsigned char *label, size_t labelLen,
                      unsigned char *cipher, size_t cipherSize);
DLL_API int SSMRSADecryptOAEP(SSMInstance *instance, SSMAsymmetricKey *priv,
                      unsigned char *data, size_t dataLen,
                      SSMHashAlgorithm hashAlgorithm,
                      unsigned char *label, size_t labelLen,
                      unsigned char *plain, size_t plainSize);
//*/

/**
 * @brief 签名验签
 *
 */
/*
DLL_API int SSMSM2Sign(SSMInstance *instance, SSMAsymmetricKey *priv,
               unsigned char *data, size_t dataLen,
               unsigned char *uid, size_t uidLen,
               unsigned char *sign, size_t signSize);
DLL_API int SSMSM2Verify(SSMInstance *instance, SSMAsymmetricKey *pub,
                 unsigned char *data, size_t dataLen,
                 unsigned char *uid, size_t uidLen,
                 unsigned char *sign, size_t signLen,
                 int *result);

DLL_API int SSMRSASignPKCS1v15(SSMInstance *instance, SSMAsymmetricKey *priv,
                       unsigned char *data, size_t dataLen,
                       SSMHashAlgorithm hashAlgorithm,
                       unsigned char *sign, size_t signSize);
DLL_API int SSMRSAVerifyPKCS1v15(SSMInstance *instance, SSMAsymmetricKey *pub,
                         SSMHashAlgorithm hashAlgorithm,
                         unsigned char *data, size_t dataLen,
                         unsigned char *sign, size_t signLen,
                         int *result);
DLL_API int SSMRSASignPSS(SSMInstance *instance, SSMAsymmetricKey *priv,
                  unsigned char *data, size_t dataLen,
                  SSMHashAlgorithm hashAlgorithm,
                  int saltLength,
                  unsigned char *sign, size_t signSize);
DLL_API int SSMRSAVerifyPSS(SSMInstance *instance, SSMAsymmetricKey *pub,
                    unsigned char *data, size_t dataLen,
                    unsigned char *sign, size_t signLen,
                    SSMHashAlgorithm hashAlgorithm,
                    int saltLength,
                    int *result);
//*/

/**
 * @brief 安全随机数
 *
 */
/*
DLL_API int SSMRandomRead(SSMInstance *instance, unsigned char *b, size_t datalen);
//*/
EXTERNC_END
#endif
