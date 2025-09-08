#if !defined(AFX_SSMKEYOUCTL_H__B1A81CC3_6FBB_4193_ABD6_EA35B69D9C78__INCLUDED_)
#define AFX_SSMKEYOUCTL_H__B1A81CC3_6FBB_4193_ABD6_EA35B69D9C78__INCLUDED_
#pragma once

#include "stdafx.h"
#include "lfsapi.h"
#include "Utils.h"
#include "ssm.h"

class CSSMKeyou
{
// Constructor
public:
	CSSMKeyou();

	static CSSMKeyou * GetInstance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CSSMKeyou();
		}

		return m_pInstance;
	}

protected:
	~CSSMKeyou();

	static CSSMKeyou * m_pInstance;

public:
	long LoadSSMDServer(LPCTSTR strSSMDFileFullPath);
	CString GetEnvelopeHmac(LPCTSTR strSourceData);
	CString SetServerSM2PublicKey(LPCTSTR strServerSM2PublicKeyHex);
	CString VerifySSMEnvelopeHmac(LPCTSTR strSourceData, LPCTSTR strHmacHex, LPCTSTR strHmacKeyByPkHex);
	CString ECBEncryptSSMEnvelope(LPCTSTR strPlain);
	CString ECBDecryptSSMEnvelope(LPCTSTR strCipherHex, LPCTSTR strKeyByClientPkHex);
	CString CreateSM2Key();

public:
	bool m_bUnionWinSockInited;
	bool m_bSSMDServerLoaded;
	SSMContext * m_SSMContext;
	SSMInstance * m_SSMInstance;

	void * m_hDll;
	CUtils m_Utils;

	PSSMNewContext_AutoCall m_pSSMNewContext_AutoCall;
	PSSMNewInstance m_pSSMNewInstance;
	PSSMFreeContext m_PSSMFreeContext;
	PSSMFreeInstance m_PSSMFreeInstance;
	PSSMGenerateSM2 m_pSSMGenerateSM2;
	PSSMImportSM2PublicKey m_pSSMImportSM2PublicKey;
	PSSMEnvelopeHmac m_pSSMEnvelopeHmac;
	PSSMEnvelopeHmacVerify m_pSSMEnvelopeHmacVerify;
	PSSMEnvelopeECBEncrypt m_pSSMEnvelopeECBEncrypt;
	PSSMEnvelopeECBDecrypt m_pSSMEnvelopeECBDecrypt;

	SSMAsymmetricKey m_SM2Key_Client;
	SSMAsymmetricKey m_Publickey_Server;
	bool m_bServerPublicKey;
	bool m_bSM2KeyCreated;

public:
	int UnloadSSMDServer();

	CString _CreateSM2Key();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSMKEYOUCTL_H__B1A81CC3_6FBB_4193_ABD6_EA35B69D9C78__INCLUDED)
