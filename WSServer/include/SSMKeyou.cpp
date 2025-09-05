// SSMKeyouCtl.cpp : Implementation of the CSSMKeyou ActiveX Control class.

#include "SSMKeyou.h"

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>

CSSMKeyou * CSSMKeyou::m_pInstance = NULL;

CSSMKeyou::CSSMKeyou()
{
	m_bSSMDServerLoaded = false;
	m_SSMContext = NULL;
	m_SSMInstance = NULL;

	m_hDll = NULL;

	m_pSSMNewContext_AutoCall = NULL;
	m_pSSMNewInstance = NULL;
	m_PSSMFreeContext = NULL;
	m_PSSMFreeInstance = NULL;
	m_pSSMGenerateSM2 = NULL;
	m_pSSMImportSM2PublicKey = NULL;
	m_pSSMEnvelopeHmac = NULL;
	m_pSSMEnvelopeHmacVerify = NULL;
	m_pSSMEnvelopeECBEncrypt = NULL;
	m_pSSMEnvelopeECBDecrypt = NULL;

	memset(&m_SM2Key_Client, 0, sizeof(m_SM2Key_Client));
	memset(&m_Publickey_Server, 0, sizeof(m_Publickey_Server));
	m_bServerPublicKey = false;
	m_bSM2KeyCreated = false;
}

CSSMKeyou::~CSSMKeyou()
{
	UnloadSSMDServer();
}

int CSSMKeyou::UnloadSSMDServer()
{
	if (NULL != m_SSMInstance)
	{
		m_PSSMFreeInstance(m_SSMInstance);
		m_SSMInstance = NULL;
	}

	if (NULL != m_SSMContext)
	{
		m_PSSMFreeContext(m_SSMContext);
		m_SSMContext = NULL;
	}

	if (m_hDll)
	{
		dlclose(m_hDll);
		m_hDll = NULL;
	}

	return 0;
}

long CSSMKeyou::LoadSSMDServer(LPCTSTR strSSMDFileFullPath) 
{
	printf("LoadSSMDServer ->\n");
	if (true == m_bSSMDServerLoaded)
	{
		printf("LoadSSMDServer <- 0\n");
		return 0;
	}

	// 加载动态库
	CString strLibFileName = "/SSA/Keyou/libssm.so";
	printf("Library File Name : %s\n", strLibFileName);

	m_hDll = dlopen(strLibFileName.c_str(), RTLD_LAZY);        // load SP so
	if (NULL == m_hDll)
	{
		printf("LoadSSMDServer(%s) failed : %s\n", strLibFileName.c_str(), dlerror());
	}
	else
	{
		printf("LoadSSMDServer(%s) success\n", strLibFileName.c_str());
	}

	m_pSSMNewContext_AutoCall = (PSSMNewContext_AutoCall)dlsym(m_hDll, "SSMNewContext_AutoCall");
	m_pSSMNewInstance = (PSSMNewInstance)dlsym(m_hDll, "SSMNewInstance");
	m_PSSMFreeContext = (PSSMFreeContext)dlsym(m_hDll, "SSMFreeContext");
	m_PSSMFreeInstance = (PSSMFreeInstance)dlsym(m_hDll, "SSMFreeInstance");
	m_pSSMGenerateSM2 = (PSSMGenerateSM2)dlsym(m_hDll, "SSMGenerateSM2");
	m_pSSMImportSM2PublicKey = (PSSMImportSM2PublicKey)dlsym(m_hDll, "SSMImportSM2PublicKey");
	m_pSSMEnvelopeHmac = (PSSMEnvelopeHmac)dlsym(m_hDll, "SSMEnvelopeHmac");
	m_pSSMEnvelopeHmacVerify = (PSSMEnvelopeHmacVerify)dlsym(m_hDll, "SSMEnvelopeHmacVerify");
	m_pSSMEnvelopeECBEncrypt = (PSSMEnvelopeECBEncrypt)dlsym(m_hDll, "SSMEnvelopeECBEncrypt");
	m_pSSMEnvelopeECBDecrypt = (PSSMEnvelopeECBDecrypt)dlsym(m_hDll, "SSMEnvelopeECBDecrypt");

	if (NULL == m_pSSMNewContext_AutoCall
		|| NULL == m_pSSMNewInstance
		|| NULL == m_PSSMFreeContext
		|| NULL == m_PSSMFreeInstance
		|| NULL == m_pSSMGenerateSM2
		|| NULL == m_pSSMImportSM2PublicKey
		|| NULL == m_pSSMEnvelopeHmac
		|| NULL == m_pSSMEnvelopeHmacVerify
		|| NULL == m_pSSMEnvelopeECBEncrypt
		|| NULL == m_pSSMEnvelopeECBDecrypt)
	{
		printf("LoadLibrary GetProcAddress failed\n");
		printf("LoadSSMDServer <- -1\n");
		return -1;
	}

	// 若SSMD程序(ssmd.exe)不在当前目录下，或者SSMD程序不在环境变量PATH目录下，需要设置SSMD的路径(路径要包含exe的名字)
	m_SSMContext = m_pSSMNewContext_AutoCall(strSSMDFileFullPath);
	if (NULL == m_SSMContext)
	{
		UnloadSSMDServer();

		printf("SSMNewContext_AutoCall error: %s\n", strSSMDFileFullPath);
		printf("LoadSSMDServer <- -1\n");
		return -1;
	}

	/*
	SSMNewInstance参数：
	context - SSM上下文
	connTimeout - 连接超时时间，可选参数。默认为3s。
	sendTimeout - 发送超时时间，可选参数。默认为3s。
	recvTimeout - 接收超时时间，可选参数。默认为3s。
	keepAlive - 长链接标识；1：长链接。0 ：短链接
	//*/

	m_SSMInstance = m_pSSMNewInstance(m_SSMContext, 0, 0, 0, 1);
	if (NULL == m_SSMInstance)
	{
		UnloadSSMDServer();

		printf("SSMNewInstance error\n");
		printf("LoadSSMDServer <- -1\n");
		return -1;
	}

	m_bSSMDServerLoaded = true;

	printf("LoadSSMDServer <- 0\n");
	return 0;
}

CString CSSMKeyou::_CreateSM2Key()
{
	printf("_CreateSM2Key ->\n");

	CString strRet = CString(1024, 0);
	/*
	if (true == m_bSM2KeyCreated)
	{
		strRet = "retcode=0;retdesc=Key already created;";
		printf("_CreateSM2Key <- : %s\n", strRet.c_str());
		return strRet;
	}
	//*/

	int ret = m_pSSMGenerateSM2(m_SSMInstance, &m_SM2Key_Client);
	if (ret < 0)
	{
		sprintf((char *)strRet.c_str(), "retcode=-1;retdesc=SSMGenerateSM2:%d;", ret);
		printf("_CreateSM2Key <- : %s\n", strRet.c_str());
		return strRet;
	}

	char * pszPublicKey = new char[m_SM2Key_Client.PublicKeyLen * 2 + 2];
	memset(pszPublicKey, 0, (m_SM2Key_Client.PublicKeyLen * 2 + 2) * sizeof(char));
	m_Utils.HextoStr((PBYTE)m_SM2Key_Client.PublicKey, m_SM2Key_Client.PublicKeyLen, pszPublicKey);

	// strRet.Format("retcode=0;publickeyvaluehex=%s;publickeylength=%d;", pszPublicKey, m_SM2Key_Client.PublicKeyLen);

	char * pszPrivateKey = new char[m_SM2Key_Client.PrivateKeyLen * 2 + 2];
	memset(pszPrivateKey, 0, (m_SM2Key_Client.PrivateKeyLen * 2 + 2) * sizeof(char));
	m_Utils.HextoStr((PBYTE)m_SM2Key_Client.PrivateKey, m_SM2Key_Client.PrivateKeyLen, pszPrivateKey);

	strRet = CString(strlen(pszPublicKey) + strlen(pszPrivateKey) + 1024, 0);
	sprintf((char *)strRet.c_str(), "retcode=0;publickeyvaluehex=%s;publickeylength=%d;privatekeyvaluehex=%s;privatekeylength=%d;",
		pszPublicKey, m_SM2Key_Client.PublicKeyLen, pszPrivateKey, m_SM2Key_Client.PrivateKeyLen);
	
	delete pszPublicKey;
	pszPublicKey = NULL;

	m_bSM2KeyCreated = true;
	printf("_CreateSM2Key <- : %s\n", strRet.c_str());
	return strRet;
}

CString CSSMKeyou::GetEnvelopeHmac(LPCTSTR strPlain) 
{
	printf("GetEnvelopeHmac ->\n");
	CString strRet = CString(1024, 0);

	if (false == m_bServerPublicKey)
	{
		sprintf((char *)strRet.c_str(), "retcode=-3;retdesc=sm2_public_key from server needed;");
		printf("GetEnvelopeHmac <- : %s\n", strRet.c_str());
		return strRet;
	}

	printf("GetEnvelopeHmac 1\n");
	SSMHashAlgorithm alg = SSMAlgorithmSM3;
	// size_t bits = 64;
	size_t bits = 128;

	SSMSecretData secretData;
	memset(&secretData, 0, sizeof(secretData));

	printf("GetEnvelopeHmac 2\n");
	SSMPadding pad = SSMPaddingPKCS7Padding;
	// SSMPadding pad = SSMPaddingNoPadding;
	unsigned char keyByPk[2048] = {0};
	size_t keyByPkLen = 0;
	unsigned char hmac[512] = {0};
	size_t hmacLen = 0;
	int ret = 0;

	printf("GetEnvelopeHmac 3\n");
	// int SSMEnvelopeHmac(SSMInstance *instance, SSMHashAlgorithm alg, size_t bits,
					// SSMAsymmetricKey *pub, SSMPadding pad,
					// unsigned char *data, size_t dataLen,
					// unsigned char *key, size_t *keyLen,
					// unsigned char *hmac, size_t hmacLen,
					// SSMSecretData *secretData)
	int result = 0;
	ret = m_pSSMEnvelopeHmac(m_SSMInstance, alg, bits, &m_Publickey_Server, pad, (unsigned char *)strPlain, strlen((char *)strPlain), keyByPk, &keyByPkLen, hmac, sizeof(hmac), &secretData);
	printf("GetEnvelopeHmac 4\n");
	if (ret < 0)
	{
		sprintf((char *)strRet.c_str(), "retcode=-10;retdesc=SSMEnvelopeHmac:%d;", ret);
		printf("GetEnvelopeHmac <- : %s\n", strRet.c_str());
		return strRet;
	}

	printf("SSMEnvelopeHmac keyByPkLen : %d, ret = %d\n", keyByPkLen, ret);

	char * pszKeyByPk = new char[keyByPkLen * 2 + 2];
	memset(pszKeyByPk, 0, (keyByPkLen * 2 + 2) * sizeof(char));
	m_Utils.HextoStr((PBYTE)keyByPk, keyByPkLen, pszKeyByPk);

	char * pszHmac = new char[ret * 2 + 2];
	memset(pszHmac, 0, (ret * 2 + 2) * sizeof(char));
	m_Utils.HextoStr((PBYTE)hmac, ret, pszHmac);

	strRet = CString(strlen(pszKeyByPk) + strlen(pszHmac) + 1024, 0);
	sprintf((char *)strRet.c_str(), "retcode=0;hmackeybypkhex=%s;hmachex=%s;", pszKeyByPk, pszHmac);

	delete pszKeyByPk;
	pszKeyByPk = NULL;

	delete pszHmac;
	pszHmac = NULL;

	printf("GetEnvelopeHmac <- : %s\n", strRet.c_str());
	return strRet;
}

CString CSSMKeyou::VerifySSMEnvelopeHmac(LPCTSTR strSourceData, LPCTSTR strHmacHex, LPCTSTR strHmacKeyByPkHex) 
{
	CString strRet = CString(1024, 0);

	int ret = 0;

	char * pszHmac = new char[strlen(strHmacHex) / 2 + 2];
	memset(pszHmac, 0, (strlen(strHmacHex) / 2 + 2) * sizeof(char));
	m_Utils.StrtoHex((PCHAR)strHmacHex, (PBYTE)pszHmac);

	char * pszHmacKeyByPk = new char[strlen(strHmacKeyByPkHex) / 2 + 2];
	memset(pszHmacKeyByPk, 0, (strlen(strHmacKeyByPkHex) / 2 + 2) * sizeof(char));
	m_Utils.StrtoHex((PCHAR)strHmacKeyByPkHex, (PBYTE)pszHmacKeyByPk);

	SSMPadding pad = SSMPaddingPKCS7Padding;
	SSMHashAlgorithm hashAlg = SSMAlgorithmSM3;
	// size_t bits = 64;
	size_t bits = 128;
	int result = 0;

	/*
	typedef int (* PSSMEnvelopeHmacVerify)(SSMInstance *instance, SSMHashAlgorithm alg, size_t bits,
	SSMAsymmetricKey *priv, SSMPadding pad,
	unsigned char *data, size_t dataLen,
	unsigned char *key, size_t keyLen,
	unsigned char *hmac, size_t hmacLen,
	int *result);
	//*/
	ret = m_pSSMEnvelopeHmacVerify(m_SSMInstance, hashAlg, bits, &m_SM2Key_Client, pad, (unsigned char *)strSourceData, strlen(strSourceData), (unsigned char *)pszHmacKeyByPk, strlen(strHmacKeyByPkHex) / 2, (unsigned char *)pszHmac, strlen(strHmacHex) / 2, &result);
 
	delete pszHmac;
	pszHmac = NULL;

	delete pszHmacKeyByPk;
	pszHmacKeyByPk = NULL;
	
	if (ret != 1)
	{
		sprintf((char *)strRet.c_str(), "retcode=-20;retdesc=SSMEnvelopeHmacVerify:%d;", ret);
		printf("VerifySSMEnvelopeHmac <- : %s\n", strRet.c_str());
		return strRet;
	}

	strRet = "retcode=0;";
	printf("VerifySSMEnvelopeHmac <- : %s\n", strRet.c_str());
	return strRet;
}

CString CSSMKeyou::ECBEncryptSSMEnvelope(LPCTSTR strPlain) 
{
	printf("ECBEncryptSSMEnvelope ->\n");
	CString strRet = CString(1024, 0);
	if (false == m_bServerPublicKey)
	{
		sprintf((char *)strRet.c_str(), "retcode=-3;retdesc=sm2_public_key from server needed;");
		printf("ECBEncryptSSMEnvelope <- : %s\n", strRet.c_str());
		return strRet;
	}

	printf("ECBEncryptSSMEnvelope 1\n");
	SSMAlgorithm alg = SSMAlgorithm_SM4;
	size_t bits = 128;
	SSMSymmetricKey key;
	SSMPadding pad = SSMPaddingPKCS7Padding;
	unsigned char keyByPk[2048] = {0};
	size_t keyByPkLen = 0;

	unsigned char * pszCipherTextBuff = new unsigned char[strlen(strPlain) * 2 + 2];
	memset(pszCipherTextBuff, 0, (strlen(strPlain) * 2 + 2) * sizeof(unsigned char));

	size_t ciphertextLen = 0;
	int ret = 0;

	memset(&key, 0, sizeof(key));

	printf("ECBEncryptSSMEnvelope 2\n");
	// int SSMEnvelopeECBEncrypt(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
	//SSMAsymmetricKey *pub, SSMPadding padding,
	//unsigned char *data, size_t dataLen,
	//unsigned char *ciphertext, size_t ciphertextLen,
	//unsigned char *keyByPk, size_t keyByPkSize,
	//size_t *keyByPkLen, SSMSymmetricKey *key)
	ret = m_pSSMEnvelopeECBEncrypt(m_SSMInstance, alg, bits, &m_Publickey_Server, pad, (unsigned char *)strPlain, strlen((char *)strPlain), pszCipherTextBuff, strlen(strPlain) * 2, keyByPk, sizeof(keyByPk), &keyByPkLen, &key);
	printf("ECBEncryptSSMEnvelope 3\n");
	if (ret < 0)
	{
		delete pszCipherTextBuff;
		pszCipherTextBuff = NULL;

		sprintf((char *)strRet.c_str(), "retcode=-30;retdesc=SSMEnvelopeECBEncrypt:%d;", ret);
		printf("ECBEncryptSSMEnvelope <- : %s\n", strRet.c_str());
		return strRet;
	}

	char * pszKeyByPk = new char[keyByPkLen * 2 + 2];
	memset(pszKeyByPk, 0, (keyByPkLen * 2 + 2) * sizeof(char));
	m_Utils.HextoStr((PBYTE)keyByPk, keyByPkLen, pszKeyByPk);

	char * pszCipherText = new char[ret * 2 + 2];
	memset(pszCipherText, 0, (ret * 2 + 2) * sizeof(char));
	m_Utils.HextoStr((PBYTE)pszCipherTextBuff, ret, pszCipherText);

	strRet = CString(strlen(pszKeyByPk) + strlen(pszCipherText) + 1024, 0);
	sprintf((char *)strRet.c_str(), "retcode=0;keybypkhex=%s;ciphertexthex=%s;", pszKeyByPk, pszCipherText);

	delete pszKeyByPk;
	pszKeyByPk = NULL;

	delete pszCipherText;
	pszCipherText = NULL;

	delete pszCipherTextBuff;
	pszCipherTextBuff = NULL;

	printf("ECBEncryptSSMEnvelope <- : %s\n", strRet.c_str());
	return strRet;
}

CString CSSMKeyou::ECBDecryptSSMEnvelope(LPCTSTR strCipherHex, LPCTSTR strKeyByPkHex) 
{
	printf("ECBDecryptSSMEnvelope ->\n");
	CString strRet = CString(1024, 0);

	int ret = 0;

	SSMAlgorithm alg = SSMAlgorithm_SM4;
	size_t bits = 128;
	SSMPadding pad = SSMPaddingPKCS7Padding;
	unsigned char keyByPk[2048] = {0};
	size_t keyByPkLen = 0;

	unsigned char * pszPlainTextBuff = new unsigned char[strlen(strCipherHex) / 2 + 2];
	memset(pszPlainTextBuff, 0, (strlen(strCipherHex) / 2 + 2) * sizeof(unsigned char));

	char * pszKeyByPk = new char[strlen(strKeyByPkHex) / 2 + 2];
	memset(pszKeyByPk, 0, (strlen(strKeyByPkHex) / 2 + 2) * sizeof(char));
	m_Utils.StrtoHex((PCHAR)strKeyByPkHex, (PBYTE)pszKeyByPk);

	char * pszCipher = new char[strlen(strCipherHex) / 2 + 2];
	memset(pszCipher, 0, (strlen(strCipherHex) / 2 + 2) * sizeof(char));
	m_Utils.StrtoHex((PCHAR)strCipherHex, (PBYTE)pszCipher);

	// int SSMEnvelopeECBEncrypt(SSMInstance *instance, SSMAlgorithm alg, size_t bits,
	//SSMAsymmetricKey *pub, SSMPadding padding,
	//unsigned char *data, size_t dataLen,
	//unsigned char *ciphertext, size_t ciphertextLen,
	//unsigned char *keyByPk, size_t keyByPkSize,
	//size_t *keyByPkLen, SSMSymmetricKey *key)
	ret = m_pSSMEnvelopeECBDecrypt(m_SSMInstance, alg, &m_SM2Key_Client, (unsigned char *)pszKeyByPk, strlen((char *)strKeyByPkHex) / 2, pad, (unsigned char *)pszCipher, strlen((char *)strCipherHex) / 2, pszPlainTextBuff, strlen(strCipherHex) / 2);
	
	delete pszKeyByPk;
	pszKeyByPk = NULL;

	delete pszCipher;
	pszCipher = NULL;

	if (ret < 0)
	{
		sprintf((char *)strRet.c_str(), "retcode=-40;retdesc=SSMEnvelopeECBDecrypt:%d;", ret);
		printf("ECBDecryptSSMEnvelope <- : %s\n", strRet.c_str());
		return strRet;
	}

	strRet = CString(strlen((char *)pszPlainTextBuff) + 1024, 0);
	sprintf((char *)strRet.c_str(), "retcode=0;plaintext=%s;", pszPlainTextBuff);
	printf("ECBDecryptSSMEnvelope <- : %s\n", strRet.c_str());
	return strRet;
}

CString CSSMKeyou::CreateSM2Key() 
{
	CString strResult = _CreateSM2Key();
	return strResult;
}

CString CSSMKeyou::SetServerSM2PublicKey(LPCTSTR strServerSM2PublicKeyHex) 
{
	printf("SetServerSM2PublicKey(%s, length:%d) ->\n", strServerSM2PublicKeyHex, strlen(strServerSM2PublicKeyHex));

	CString strRet = CString(1024, 0);
	if (strlen(strServerSM2PublicKeyHex) < (65 * 2))
	{
		sprintf((char *)strRet.c_str(), "retcode=-4;retdesc=length less than 128;");
		printf("SetServerSM2PublicKey <- : %s\n", strRet.c_str());
		return strRet;
	}

	char * pszPublicKey = new char[strlen(strServerSM2PublicKeyHex) / 2 + 2];
	memset(pszPublicKey, 0, (strlen(strServerSM2PublicKeyHex) / 2 + 2) * sizeof(char));
	m_Utils.StrtoHex((PCHAR)strServerSM2PublicKeyHex, (PBYTE)pszPublicKey);

	int ret = m_pSSMImportSM2PublicKey(m_SSMInstance, (unsigned char *)pszPublicKey, strlen(strServerSM2PublicKeyHex) / 2, &m_Publickey_Server);
	if (ret < 0)
	{
		sprintf((char *)strRet.c_str(), "retcode=-5;retdesc=SSMImportSM2PublicKey:%d;", ret);
		printf("SetServerSM2PublicKey <- : %s\n", strRet.c_str());
		return strRet;
	}

	m_bServerPublicKey = true;
	
	strRet = "retcode=0;";
	printf("SetServerSM2PublicKey <- : %s\n", strRet.c_str());
	return strRet;
}

