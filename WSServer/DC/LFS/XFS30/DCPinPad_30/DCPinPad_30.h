// DCPinPad_XFS30.h: interface for the CDCPinPad_30 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCPINPAD_30_H__INCLUDED_)
#define AFX_DCPINPAD_30_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DC_30.h"
#include "DC.h"
#include "lfspin.h"
#include "stdafx.h"

class CDCPinPad_30 : public CDC_30  
{
public:
	// ������������
	CDCPinPad_30(LPCTSTR strDCName, LPCTSTR strTraceComponent);
	virtual ~CDCPinPad_30();

protected:
	CString	HandleCmdErr(LPLFSRESULT lpWfsRet);
	CString HandleEXEEvtResult(LPLFSRESULT lpWfsRet);
	CString HandleUSEREvtResult(LPLFSRESULT lpWfsRet);
	CString HandleSRVEvtResult(LPLFSRESULT lpWfsRet);
	CString HandleSysEvtResult(LPLFSRESULT lpWfsRet);
	CString HandleCmdResult(LPLFSRESULT lpWfsRet);
	CString HandleInfResult(LPLFSRESULT lpWfsRet);

public:
	virtual CString GetXFSErrStr(HRESULT hResult);
	virtual CString GetXFSMsgStr(DWORD dwEventID);
	virtual CString GetXFSSysEvtStr(DWORD dwEventID);
	virtual CString GetXFSCmdStr(DWORD dwCmdCode);

public:
	virtual int OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual HRESULT _CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid);

public:
	HRESULT INF_PIN_STATUS();
	HRESULT INF_PIN_CAPABILITIES();
	HRESULT INF_PIN_KEY_DETAIL(char * strKeyName);
	HRESULT INF_PIN_FUNCKEY_DETAIL();

	// ����ִ��
	HRESULT CMD_PIN_CRYPT(LPCTSTR strBytesHex, LPCTSTR strKeyName, long wMode, long wAlgorithm, short chPadChar);
	HRESULT CMD_PIN_IMPORT_KEY(LPCTSTR strKeyName, LPCTSTR strBytesHexKeyValue, LPCTSTR strEncKeyName, DWORD fwUse, LPCTSTR strBytesHexIdentification);
	HRESULT CMD_PIN_GET_PIN(short nMinLength, short nMaxLength, short nAutoEnd, ULONG active_keys, ULONG active_fdks, ULONG terminate_keys, ULONG terminate_fdks);
	HRESULT CMD_PIN_GET_PINBLOCK(WORD format, LPCTSTR strCustomerData, short chPadChar, LPCTSTR strKeyName, LPCTSTR strXORData, LPCTSTR strSecondKeyName);
	HRESULT CMD_PIN_GET_DATA(short nMaxLength, short nAutoEnd, ULONG active_keys, ULONG active_fdks, ULONG terminate_keys, ULONG terminate_fdks);
	HRESULT CMD_PIN_INITIALIZATION();
	HRESULT CMD_PIN_RESET();

	// ��Կ�ַ����֧��
	HRESULT CMD_PIN_ENC_IO(long lCommand, LPCTSTR strKeyName, LPCTSTR strDataHex, long lUse, LPCTSTR strSigKey, long lSM2SignatureAlgorithm, LPCTSTR strSignatureHex);
	HRESULT CMD_PIN_DERIVE_KEY(long wDerivationAlgorithm, LPCTSTR strKeyName, LPCTSTR strKeyGenKey, LPCTSTR strStartValueKey, LPCTSTR strBytesHexStartValue, long lPadding, LPCTSTR strBytesHexInputData, LPCTSTR strBytesHexIdentification);
	HRESULT CMD_PIN_IMPORT_KEY_EX(LPCTSTR strKeyName, LPCTSTR strBytesHexKeyValue, LPCTSTR strEncKeyName, LPCTSTR strBytesHexControlVector, DWORD fwUse, WORD wKeyCheckMode, LPCTSTR strBytesHexKeyCheckValue);
};

#endif // !defined(AFX_DCPINPAD_30_H__INCLUDED_)
