// DCPinPad_30.cpp: implementation of the CDCPinPad_30 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCPinPad_30.h"
#include "../../../include/JavaScriptStringParam.h"
#include "XFSPINCHN.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDCPinPad_30::CDCPinPad_30(LPCTSTR strDCName, LPCTSTR strTraceComponent)
{
	m_strDCName = strDCName;
	m_strTraceComponent = CString(strTraceComponent);
	m_DCObject.m_bWosaXFSRun = FALSE;
}

CDCPinPad_30::~CDCPinPad_30()
{
}

HRESULT CDCPinPad_30::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// 调用命令
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_PIN_CRYPT"))
	{
		bValid = TRUE;
		hResult = CMD_PIN_CRYPT(CJSStringParam::GetStringParam(strarrParams, "lpbdata").c_str(),
								CJSStringParam::GetStringParam(strarrParams, "lpskey").c_str(),
								atol(CJSStringParam::GetStringParam(strarrParams, "wmode").c_str()), 
								atol(CJSStringParam::GetStringParam(strarrParams, "walgorithm").c_str()), 
								(short)atol(CJSStringParam::GetStringParam(strarrParams, "bpadding").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PIN_IMPORT_KEY"))
	{
		bValid = TRUE;
		hResult = CMD_PIN_IMPORT_KEY(	CJSStringParam::GetStringParam(strarrParams, "lpskey").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpbdata_keyvalue").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpsenckey").c_str(),
										atol(CJSStringParam::GetStringParam(strarrParams, "fwuse").c_str()), 
										CJSStringParam::GetStringParam(strarrParams, "lpbdata_identification").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PIN_GET_PIN"))
	{
		bValid = TRUE;
		hResult = CMD_PIN_GET_PIN(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "usminlen").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "usmaxlen").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "bautoend").c_str()), 
									atol(CJSStringParam::GetStringParam(strarrParams, "ulactivekeys").c_str()), 
									atol(CJSStringParam::GetStringParam(strarrParams, "ulactivefdks").c_str()), 
									atol(CJSStringParam::GetStringParam(strarrParams, "ulterminatekeys").c_str()),
									atol(CJSStringParam::GetStringParam(strarrParams, "ulterminatefdks").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PIN_GET_PINBLOCK"))
	{
		bValid = TRUE;
		hResult = CMD_PIN_GET_PINBLOCK(	(WORD)atol(CJSStringParam::GetStringParam(strarrParams, "wformat").c_str()), 
										CJSStringParam::GetStringParam(strarrParams, "lpscustomerdata").c_str(),
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "bpadding").c_str()), 
										CJSStringParam::GetStringParam(strarrParams, "lpskey").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpsxordata").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpskeyenckey").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PIN_GET_DATA"))
	{
		bValid = TRUE;
		hResult = CMD_PIN_GET_DATA(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "usmaxlen").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "bautoend").c_str()), 
									atol(CJSStringParam::GetStringParam(strarrParams, "ulactivekeys").c_str()), 
									atol(CJSStringParam::GetStringParam(strarrParams, "ulactivefdks").c_str()), 
									atol(CJSStringParam::GetStringParam(strarrParams, "ulterminatekeys").c_str()),
									atol(CJSStringParam::GetStringParam(strarrParams, "ulterminatefdks").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PIN_INITIALIZATION"))
	{
		bValid = TRUE;
		hResult = CMD_PIN_INITIALIZATION();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PIN_RESET"))
	{
		bValid = TRUE;
		hResult = CMD_PIN_RESET();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PIN_ENC_IO"))
	{
		bValid = TRUE;
		hResult = CMD_PIN_ENC_IO((short)atol(CJSStringParam::GetStringParam(strarrParams, "lcommand").c_str()),
			CJSStringParam::GetStringParam(strarrParams, "lpskey").c_str(),
			CJSStringParam::GetStringParam(strarrParams, "lpskeydatahex").c_str(),
			atol(CJSStringParam::GetStringParam(strarrParams, "luse").c_str()),
			CJSStringParam::GetStringParam(strarrParams, "lpssigkey").c_str(),
			atol(CJSStringParam::GetStringParam(strarrParams, "lsm2signaturealgorithm").c_str()),
			CJSStringParam::GetStringParam(strarrParams, "lpssigkeydatahex").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PIN_DERIVE_KEY"))
	{
		bValid = TRUE;
		hResult = CMD_PIN_DERIVE_KEY((short)atol(CJSStringParam::GetStringParam(strarrParams, "wderivationalgorithm").c_str()),
			CJSStringParam::GetStringParam(strarrParams, "lpskey").c_str(),
			CJSStringParam::GetStringParam(strarrParams, "lpskeygenkey").c_str(),
			CJSStringParam::GetStringParam(strarrParams, "lpsstartvaluekey").c_str(),
			CJSStringParam::GetStringParam(strarrParams, "lpsstartvaluedatahex").c_str(),
			atol(CJSStringParam::GetStringParam(strarrParams, "lpadding").c_str()),
			CJSStringParam::GetStringParam(strarrParams, "lpsinputdatahex").c_str(),
			CJSStringParam::GetStringParam(strarrParams, "lpsidentificationdatahex").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_INF_PIN_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_PIN_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_PIN_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_PIN_CAPABILITIES();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_PIN_FUNCKEY_DETAIL"))
	{
		bValid = TRUE;
		hResult = INF_PIN_FUNCKEY_DETAIL();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_PIN_KEY_DETAIL"))
	{
		bValid = TRUE;
		hResult = INF_PIN_KEY_DETAIL((LPTSTR)(LPCTSTR)CJSStringParam::GetStringParam(strarrParams, "lpskeyname").c_str());
	}

	return hResult;
}

HRESULT CDCPinPad_30::INF_PIN_KEY_DETAIL(char * strKeyName)
{
	HRESULT hResult = DC_ERROR;

	LPSTR		lpsKeyName = NULL;
	if (NULL != strKeyName && strlen(strKeyName) > 0 )
	{
		lpsKeyName = new char[64];
		memset(lpsKeyName, 0, 64);

		hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
			LFS_INF_PIN_KEY_DETAIL,
			lpsKeyName,
			LFS_INDEFINITE_WAIT,
			(char *)m_strDBusPath.c_str(),
			&m_RequestID);

		delete[] lpsKeyName;
	}
	else
	{
		hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
			LFS_INF_PIN_KEY_DETAIL,
			NULL,
			LFS_INDEFINITE_WAIT,
			(char *)m_strDBusPath.c_str(),
			&m_RequestID);
	}
	
	return hResult;
}

HRESULT CDCPinPad_30::INF_PIN_FUNCKEY_DETAIL() 
{
	HRESULT hResult = DC_ERROR;

	ULONG ulFDKMask = 0xFFFFFFFF;
	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_PIN_FUNCKEY_DETAIL,
		&ulFDKMask,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCPinPad_30::INF_PIN_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_PIN_STATUS,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

CString CDCPinPad_30::HandleInfResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strTrace;

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(),
		"wfsresult.hresult=%d"
		"%s"
		"wfsresult.u.dwcommandcode=%d",
		lpWfsRet->result,
		GetStringSplitChar(),
		lpWfsRet->u.command_code);

	if (LFS_SUCCESS != lpWfsRet->result)
	{
		return strWfsResult;
	}

	if (LFS_INF_PIN_STATUS == lpWfsRet->u.command_code)
	{
		LPLFSPINSTATUS lpStatus = (LPLFSPINSTATUS)lpWfsRet->buffer;
		if (NULL != lpStatus)
		{
			strWfsResult = CString((NULL == lpStatus->extra ? 0 : strlen(lpStatus->extra)) + 1024, 0);
			sprintf((char *)strWfsResult.c_str(), 	"wfsresult.u.dwcommandcode=%d"
									"%s"
									"wfsresult.lpbuffer.fwdevice=%d"
									"%s"
									"wfsresult.lpbuffer.fwencstat=%d"
									"%s"
									"wfsresult.lpbuffer.lpszextra=%s",
									LFS_INF_PIN_STATUS,
									GetStringSplitChar(),
									lpStatus->device,
									GetStringSplitChar(),
									lpStatus->enc_stat,
									GetStringSplitChar(),
									(NULL == lpStatus->extra ? "NULL" : lpStatus->extra));
		}
	}
	else if (LFS_INF_PIN_CAPABILITIES == lpWfsRet->u.command_code)
	{
		LPLFSPINCAPS lpCaps = (LPLFSPINCAPS)lpWfsRet->buffer;
		if (NULL != lpCaps)
		{
			strWfsResult = CString((NULL == lpCaps->extra ? 0 : strlen(lpCaps->extra)) + 2048, 0);
			sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
				"%s"
				"wfsresult.lpbuffer.wclass=%d"
				"%s"
				"wfsresult.lpbuffer.fwtype=%d"
				"%s"
				"wfsresult.lpbuffer.bcompound=%s"
				"%s"
				"wfsresult.lpbuffer.uskeynum=%d"
				"%s"
				"wfsresult.lpbuffer.fwalgorithms=%d"
				"%s"
				"wfsresult.lpbuffer.fwpinformats=%d"
				"%s"
				"wfsresult.lpbuffer.fwderivationalgorithms=%d"
				"%s"
				"wfsresult.lpbuffer.fwpresentationalgorithms=%d"
				"%s"
				"wfsresult.lpbuffer.fwdisplay=%d"
				"%s"
				"wfsresult.lpbuffer.bidconnect=%s"
				"%s"
				"wfsresult.lpbuffer.fwidkey=%d"
				"%s"
				"wfsresult.lpbuffer.fwvalidationalgorithms=%d"
				"%s"
				"wfsresult.lpbuffer.fwkeycheckmodes=%d"
				"%s"
				"wfsresult.lpbuffer.lpszextra=%s",
				LFS_INF_PIN_CAPABILITIES,
				GetStringSplitChar(),
				lpCaps->dev_class,
				GetStringSplitChar(),
				lpCaps->dev_type,
				GetStringSplitChar(),
				lpCaps->compound ? "TRUE" : "false",
				GetStringSplitChar(),
				lpCaps->key_num,
				GetStringSplitChar(),
				lpCaps->algorithms,
				GetStringSplitChar(),
				lpCaps->pin_formats,
				GetStringSplitChar(),
				lpCaps->derivation_algorithms,
				GetStringSplitChar(),
				lpCaps->presentation_algorithms,
				GetStringSplitChar(),
				lpCaps->display,
				GetStringSplitChar(),
				lpCaps->id_connect ? "TRUE" : "false",
				GetStringSplitChar(),
				lpCaps->id_key,
				GetStringSplitChar(),
				lpCaps->validation_algorithms,
				GetStringSplitChar(),
				lpCaps->key_check_modes,
				GetStringSplitChar(),
				(NULL == lpCaps->extra ? "NULL" : lpCaps->extra));
		}
	}
	else if (LFS_INF_PIN_FUNCKEY_DETAIL == lpWfsRet->u.command_code)
	{
		LPLFSPINFUNCKEYDETAIL lpFK = (LPLFSPINFUNCKEYDETAIL)lpWfsRet->buffer;
		if (NULL != lpFK)
		{
			// 数字键盘按键
			strWfsResult = CString(256, 0);
			sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
				"%s"
				"wfsresult.lpbuffer.ulfuncmask=0x%x"
				"%s"
				"wfsresult.lpbuffer.usnumberfdks=0x%x",
				LFS_INF_PIN_FUNCKEY_DETAIL,
				GetStringSplitChar(),
				lpFK->func_mask,
				GetStringSplitChar(),
				lpFK->number_fdks);

			// 功能键盘按键
			for (int nLoop = 0; nLoop < lpFK->number_fdks; nLoop++)
			{
				CString strFunctionPad(256, 0);
				sprintf((char *)strFunctionPad.c_str(), "%s"
					"wfsresult.lpbuffer.lppfdks[%d].ulfdk=%d",
					GetStringSplitChar(),
					nLoop, lpFK->fdks[nLoop]->fdk);

				strWfsResult = string(strWfsResult.c_str()) + strFunctionPad;
			}
		}
	}
	else if (LFS_INF_PIN_KEY_DETAIL == lpWfsRet->u.command_code)
	{
		LPLFSPINKEYDETAIL * lppKDetails = (LPLFSPINKEYDETAIL *)lpWfsRet->buffer;
		if (NULL != lppKDetails)
		{
			for (int nLoop = 0; NULL != lppKDetails[nLoop]; nLoop++)
			{
				CString strKDetails((NULL == lppKDetails[nLoop]->key_name ? 0 : strlen(lppKDetails[nLoop]->key_name)) + 2048, 0);
				sprintf((char *)strKDetails.c_str(), "%s"
					"wfsresult.lpbuffer[%d].lpskeyname=%s"
					"%s"
					"wfsresult.lpbuffer[%d].bloaded=%s"
					"%s"
					"wfsresult.lpbuffer[%d].fwuse=%d",
					GetStringSplitChar(),
					nLoop, (NULL == lppKDetails[nLoop]->key_name ? "NULL" : lppKDetails[nLoop]->key_name),
					GetStringSplitChar(),
					nLoop, (TRUE == lppKDetails[nLoop]->loaded ? "TRUE" : "false"),
					GetStringSplitChar(),
					nLoop, lppKDetails[nLoop]->use);

				strWfsResult = string(strWfsResult.c_str()) + strKDetails;
			}
		}
	}

	return strWfsResult;
}

HRESULT CDCPinPad_30::INF_PIN_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_PIN_CAPABILITIES,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCPinPad_30::CMD_PIN_CRYPT(LPCTSTR strBytesHex, LPCTSTR strKeyName, long wMode, long wAlgorithm, short chPadChar) 
{
	if (NULL == strKeyName || NULL == strBytesHex || strlen(strBytesHex) == 0)
	{
		return -1;
	}

	HRESULT hResult = DC_ERROR;

	LPLFSPINCRYPT lpCrypt = NULL;
	char achKeyValue[64] = {0};
	char achHexKeyValue[64] = {0};

	CString strKeyValue = "";
	CString strTmp = "";

	/*
	if (LFS_SUCCESS != WFMAllocateBuffer(sizeof(LFSPINCRYPT), LFS_MEM_ZEROINIT, (void **)&lpCrypt))
	{
		return (short)DC_ERROR;
	}
	if (LFS_SUCCESS != WFMAllocateBuffer(strlen(strKeyName) + 1, LFS_MEM_ZEROINIT, (void **)&lpCrypt->key))
	{
		WFMFreeBuffer(lpCrypt);
		return (short)DC_ERROR;
	}
	if (LFS_SUCCESS != WFMAllocateBuffer(sizeof(LFSXDATA), LFS_MEM_ZEROINIT, (void **)&lpCrypt->crypt_data))
	{
		WFMFreeBuffer(lpCrypt->key);
		WFMFreeBuffer(lpCrypt);
		return (short)DC_ERROR;
	}
	if (LFS_SUCCESS != WFMAllocateBuffer(strlen(strBytesHex) / 2, LFS_MEM_ZEROINIT, (void **)&lpCrypt->crypt_data->data))
	{		
		WFMFreeBuffer(lpCrypt->crypt_data);
		WFMFreeBuffer(lpCrypt->key);
		WFMFreeBuffer(lpCrypt);
		return (short)DC_ERROR;
	}
	//*/
	lpCrypt = new LFSPINCRYPT();
	memset(lpCrypt, 0, sizeof(LFSPINCRYPT));

	lpCrypt->key = new char[strlen(strKeyName) + 1];
	memset(lpCrypt->key, 0, strlen(strKeyName) + 1);

	lpCrypt->crypt_data = new LFSXDATA();
	memset(lpCrypt->crypt_data, 0, sizeof(LFSXDATA));

	lpCrypt->crypt_data->data = new BYTE[strlen(strBytesHex) / 2];
	memset(lpCrypt->crypt_data->data, 0, strlen(strBytesHex) / 2);


	int nLenBytes = strlen(strBytesHex) / 2;
	BYTE * pszValue = new BYTE[nLenBytes];
	memset(pszValue, 0, nLenBytes);
	m_Utils.StrtoHex((LPTSTR)(LPCTSTR)strBytesHex, pszValue);

	lpCrypt->mode = (WORD)wMode;
	strcpy((char*)lpCrypt->key, strKeyName);
	lpCrypt->key_enc_key = NULL;
	// lpCrypt->algorithm = (WORD)wAlgorithm;
	lpCrypt->algorithm = LFS_PIN_CRYPTSM4;  // 固定使用国密算法SM4
	lpCrypt->start_value_key = NULL;
	lpCrypt->start_value = NULL;
	lpCrypt->padding = (BYTE)chPadChar;
	lpCrypt->compression = 0x00;
	
	lpCrypt->crypt_data->length = strlen(strBytesHex) / 2;
	memcpy((char *)lpCrypt->crypt_data->data, pszValue, lpCrypt->crypt_data->length);
	
	delete[] pszValue;
	pszValue = NULL;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PIN_CRYPT,
								lpCrypt,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);
	
	// WFMFreeBuffer(lpCrypt->crypt_data->data);
	delete[] lpCrypt->crypt_data->data;
	// WFMFreeBuffer(lpCrypt->crypt_data);
	delete lpCrypt->crypt_data;
	// WFMFreeBuffer(lpCrypt->key);
	delete[] lpCrypt->key;
	// WFMFreeBuffer(lpCrypt);
	delete lpCrypt;

	return hResult;
}

HRESULT CDCPinPad_30::CMD_PIN_GET_DATA(short nMaxLength, short nAutoEnd, ULONG active_keys, ULONG active_fdks, ULONG terminate_keys, ULONG terminate_fdks)
{
	if (0 == active_keys)
	{
		return -1;
	}

	HRESULT hResult = DC_ERROR;

	LPLFSPINGETDATA lpPinGetData = NULL;

	// WFMAllocateBuffer(sizeof(LFSPINGETDATA), LFS_MEM_ZEROINIT, (void **)&lpPinGetData);
	lpPinGetData = new LFSPINGETDATA();
	memset(lpPinGetData, 0, sizeof(LFSPINGETDATA));

	lpPinGetData->max_len = nMaxLength;
	if (nAutoEnd == 0)
	{
		lpPinGetData->auto_end = FALSE;
	}
	else
	{
		lpPinGetData->auto_end = TRUE;
	}

	lpPinGetData->terminate_keys = terminate_keys;
	lpPinGetData->terminate_fdks = terminate_fdks;
	lpPinGetData->active_keys = active_keys | lpPinGetData->terminate_keys;
	lpPinGetData->active_fdks = active_fdks | lpPinGetData->terminate_fdks;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PIN_GET_DATA,
								lpPinGetData,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	// WFMFreeBuffer(lpPinGetData);
	delete lpPinGetData;

	return hResult;
}

HRESULT CDCPinPad_30::CMD_PIN_GET_PIN(short nMinLength, short nMaxLength, short nAutoEnd, ULONG active_keys, ULONG active_fdks, ULONG terminate_keys, ULONG terminate_fdks) 
{
	if (0 == active_keys)
	{
		return -1;
	}

	HRESULT hResult = DC_ERROR;

	LPLFSPINGETPIN lpGetPin;	

	// WFMAllocateBuffer(sizeof(LFSPINGETPIN), LFS_MEM_ZEROINIT, (void **)&lpGetPin);
	lpGetPin = new LFSPINGETPIN();
	memset(lpGetPin, 0, sizeof(LFSPINGETPIN));

	lpGetPin->min_len = nMinLength;
	lpGetPin->max_len = nMaxLength;

	if (0 == nAutoEnd)
	{
		lpGetPin->auto_end = FALSE;
	}
    else
	{
		lpGetPin->auto_end = TRUE;
	}
	
	lpGetPin->echo = '*';
	
	lpGetPin->terminate_keys = terminate_keys;
	lpGetPin->terminate_fdks = terminate_fdks;
	lpGetPin->active_keys = active_keys | lpGetPin->terminate_keys;
	lpGetPin->active_fdks = active_fdks | lpGetPin->terminate_fdks;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PIN_GET_PIN,
								lpGetPin,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	// WFMFreeBuffer(lpGetPin);
	delete lpGetPin;

	return hResult;
}

HRESULT CDCPinPad_30::CMD_PIN_GET_PINBLOCK(WORD format, LPCTSTR strCustomerData, short chPadChar, LPCTSTR strKeyName, LPCTSTR strXORData, LPCTSTR strSecondKeyName) 
{
	if (NULL == strCustomerData || NULL == strKeyName) 
	{
		return -1;
	}

	CString _strCustomerData = strCustomerData;
	if (_strCustomerData.length() > 5)
	{
		_strCustomerData = _strCustomerData.substr(0, _strCustomerData.length() - 5) + "****" + _strCustomerData.substr(_strCustomerData.length() - 1, 1);
	}

	HRESULT hResult = DC_ERROR;

	LPLFSPINBLOCK lpPinBlock = NULL;
					
	// WFMAllocateBuffer(sizeof(LFSPINBLOCK), LFS_MEM_ZEROINIT, (void **)&lpPinBlock);
	lpPinBlock = new LFSPINBLOCK();
	memset(lpPinBlock, 0, sizeof(LFSPINBLOCK));

	if (NULL != strKeyName && strlen(strKeyName) > 0)
	{
		// WFMAllocateBuffer(strlen(strKeyName) + 3 + 1, LFS_MEM_ZEROINIT, (void **)&lpPinBlock->key);
		lpPinBlock->key = new char[strlen(strKeyName) + 3 + 1];
		memset(lpPinBlock->key, 0, strlen(strKeyName) + 3 + 1);

		strcpy(lpPinBlock->key, strKeyName);
	}
	else
	{
		lpPinBlock->key = NULL;
	}
	
	if (NULL != strCustomerData && strlen(strCustomerData) > 0)
	{
		// WFMAllocateBuffer(strlen(strCustomerData) + 1, LFS_MEM_ZEROINIT, (void **)&lpPinBlock->customer_data);
		lpPinBlock->customer_data = new char[strlen(strCustomerData) + 1];
		memset(lpPinBlock->customer_data, 0, strlen(strCustomerData) + 1);

		strcpy(lpPinBlock->customer_data, strCustomerData);
	}
	else
	{
		lpPinBlock->customer_data = NULL;
	}
	
	if (NULL != strXORData && strlen(strXORData) > 0)
	{
		// WFMAllocateBuffer(strlen(strXORData) + 1, LFS_MEM_ZEROINIT, (void **)&lpPinBlock->xor_data);
		lpPinBlock->xor_data = new char[strlen(strXORData) + 1];
		memset(lpPinBlock->xor_data, 0, strlen(strXORData) + 1);

		strcpy(lpPinBlock->xor_data, strXORData);
	}
	else
	{
		lpPinBlock->xor_data = NULL;
	}

	if (NULL != strSecondKeyName && strlen(strSecondKeyName) > 0)
	{
		// WFMAllocateBuffer(strlen(strSecondKeyName) + 1, LFS_MEM_ZEROINIT, (void **)&lpPinBlock->key_enc_key);
		lpPinBlock->key_enc_key = new char[strlen(strSecondKeyName) + 1];
		memset(lpPinBlock->key_enc_key, 0, strlen(strSecondKeyName) + 1);

		strcpy(lpPinBlock->key_enc_key, strSecondKeyName);
	}
	else
	{
		lpPinBlock->key_enc_key = NULL;
	}
	
	lpPinBlock->padding = (BYTE)chPadChar;
	lpPinBlock->format = format;
	lpPinBlock->algorithm = LFS_PIN_CRYPTSM4; // 固定使用国密算法SM4

	hResult = LFSAsyncExecute(m_DCObject.m_hService,
		LFS_CMD_PIN_GET_PINBLOCK,
		lpPinBlock,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	if (NULL != lpPinBlock->key)
	{
		// WFMFreeBuffer(lpPinBlock->key);
		delete[] lpPinBlock->key;
	}

	if (NULL != lpPinBlock->key_enc_key)
	{
		// WFMFreeBuffer(lpPinBlock->key_enc_key);
		delete[] lpPinBlock->key_enc_key;
	}

	if (NULL != lpPinBlock->xor_data)
	{
		// WFMFreeBuffer(lpPinBlock->xor_data);
		delete[] lpPinBlock->xor_data;
	}

	if (NULL != lpPinBlock->customer_data)
	{
		// WFMFreeBuffer(lpPinBlock->customer_data);
		delete[] lpPinBlock->customer_data;
	}

	// WFMFreeBuffer(lpPinBlock);
	delete lpPinBlock;

	return hResult;
}

HRESULT CDCPinPad_30::CMD_PIN_IMPORT_KEY(LPCTSTR strKeyName, LPCTSTR strBytesHexKeyValue, LPCTSTR strEncKeyName, DWORD fwUse, LPCTSTR strBytesHexIdentification) 
{
	if (NULL == strKeyName || NULL == strBytesHexKeyValue || 0 == fwUse) 
	{
		return -1;
	}
	
	HRESULT hResult = DC_ERROR;

	LPLFSPINIMPORT lpImport = NULL;
	char achKeyValue[64] = {0};
	char achIdent[64] = {0};

	m_Utils.StrtoHex((LPTSTR)strBytesHexKeyValue, (UCHAR *)achKeyValue);
	m_Utils.StrtoHex((LPTSTR)strBytesHexIdentification, (UCHAR *)achIdent);

	// WFMAllocateBuffer(sizeof(LFSPINIMPORT), LFS_MEM_ZEROINIT, (void **)&lpImport);
	lpImport = new LFSPINIMPORT();
	memset(lpImport, 0, sizeof(LFSPINIMPORT));

	if (NULL != strBytesHexIdentification && strlen(strBytesHexIdentification) > 0)
	{
		// WFMAllocateBuffer(sizeof(LFSXDATA), LFS_MEM_ZEROINIT, (void **)&lpImport->ident);
		lpImport->ident = new LFSXDATA();
		memset(lpImport->ident, 0, sizeof(LFSXDATA));

		// WFMAllocateBuffer(64, LFS_MEM_ZEROINIT, (void **)&lpImport->ident->data);
		lpImport->ident->data = new BYTE[64];
		memset(lpImport->ident->data, 0, 64);

		lpImport->ident->length = strlen(strBytesHexIdentification) / 2;
		memcpy((CHAR *)lpImport->ident->data, achIdent, lpImport->ident->length);
	}
	else
	{
		lpImport->ident = NULL;
	}

	// WFMAllocateBuffer(sizeof(LFSXDATA), LFS_MEM_ZEROINIT, (void **)&lpImport->value);
	lpImport->value = new LFSXDATA();
	memset(lpImport->value, 0, sizeof(LFSXDATA));

	// WFMAllocateBuffer(64, LFS_MEM_ZEROINIT, (void **)&lpImport->value->data);
	lpImport->value->data = new BYTE[64];
	memset(lpImport->value->data, 0, 64);

	lpImport->value->length = strlen(strBytesHexKeyValue) / 2;
	memcpy((char *)lpImport->value->data, achKeyValue, lpImport->value->length);

	// WFMAllocateBuffer(64, LFS_MEM_ZEROINIT, (void **)&lpImport->key);
	lpImport->key = new char[64];
	memset(lpImport->key, 0, 64);

	strcpy((char *)lpImport->key, strKeyName);

	if (NULL != strEncKeyName && strlen(strEncKeyName) > 0)
	{
		// WFMAllocateBuffer(64, LFS_MEM_ZEROINIT, (void **)&lpImport->enc_key);
		lpImport->enc_key = new char[64];
		memset(lpImport->enc_key, 0, 64);

		strcpy(lpImport->enc_key, strEncKeyName);
	}
	else
	{
		lpImport->enc_key = NULL;
	}

	lpImport->use = (WORD)(fwUse | LFS_PIN_USESM4);

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PIN_IMPORT_KEY,
								lpImport,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	if (NULL != strBytesHexIdentification && strlen(strBytesHexIdentification) > 0)
	{
		// WFMFreeBuffer(lpImport->ident->data);
		delete[] lpImport->ident->data;

		// WFMFreeBuffer(lpImport->ident);
		delete lpImport->ident;
	}

	// WFMFreeBuffer(lpImport->value->data);
	delete[] lpImport->value->data;

	// WFMFreeBuffer(lpImport->value);
	delete lpImport->value;

	// WFMFreeBuffer(lpImport->key);
	delete[] lpImport->key;

	if (NULL != strEncKeyName && strlen(strEncKeyName) > 0)
	{
		// WFMFreeBuffer(lpImport->enc_key);
		delete[] lpImport->enc_key;
	}
	
	// WFMFreeBuffer(lpImport);
	delete lpImport;

	return hResult;
}

HRESULT CDCPinPad_30::CMD_PIN_INITIALIZATION() 
{
	HRESULT hResult = DC_ERROR;

	LPLFSPININIT lpInit = NULL;

	// WFMAllocateBuffer(sizeof(LFSPININIT), LFS_MEM_ZEROINIT, (void **)&lpInit);
	lpInit = new LFSPININIT();
	memset(lpInit, 0, sizeof(LFSPININIT));

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PIN_INITIALIZATION,
								lpInit,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	// WFMFreeBuffer(lpInit);
	delete lpInit;

	return hResult;
}

HRESULT CDCPinPad_30::CMD_PIN_RESET() 
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PIN_RESET,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

int CDCPinPad_30::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (FALSE == m_DCObject.m_bWosaXFSRun && LFS_OPEN_COMPLETE != uMsg)  // 异步打开模块时，会返回模块打开成功事件
	{
		return -1;
	}

    LPLFSRESULT lpWfsRet = NULL;

	CString strWfsResult = "";

	switch (uMsg)
    {
        case LFS_OPEN_COMPLETE:
			m_bIsOenCompleted = TRUE;
            lpWfsRet = (LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);
			WriteTrace(m_strTraceComponent.c_str(), OCXEVENT, "LFS_OPEN_COMPLETE");
			printf("LFS_OPEN_COMPLETE CDCPinPad_30\n");
			break;
        case LFS_CLOSE_COMPLETE:
            lpWfsRet = (LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);
			break;
        case LFS_LOCK_COMPLETE:
            lpWfsRet = (LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);
			break;
        case LFS_UNLOCK_COMPLETE:
            lpWfsRet = (LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);
			break;
        case LFS_REGISTER_COMPLETE:
            lpWfsRet = (LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);
			break;
        case LFS_DEREGISTER_COMPLETE:
            lpWfsRet = (LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);
			break;
        case LFS_GETINFO_COMPLETE:
			lpWfsRet = (LPLFSRESULT)lParam;
			if (NULL != lpWfsRet)
			{
				strWfsResult = HandleInfResult(lpWfsRet);
			}

			LFSFreeResult(lpWfsRet);
			break;
		case LFS_EXECUTE_COMPLETE:
			lpWfsRet = (LPLFSRESULT)lParam;
			strWfsResult = HandleCmdResult(lpWfsRet);
			LFSFreeResult(lpWfsRet);
			break;
        case LFS_EXECUTE_EVENT:
			lpWfsRet = (LPLFSRESULT)lParam;
			strWfsResult = HandleEXEEvtResult(lpWfsRet);
			LFSFreeResult(lpWfsRet);
			break;
        case LFS_SERVICE_EVENT:
			lpWfsRet = (LPLFSRESULT)lParam;
			strWfsResult = HandleSRVEvtResult(lpWfsRet);
			LFSFreeResult(lpWfsRet);
			break ;
        case LFS_USER_EVENT:
			lpWfsRet = (LPLFSRESULT)lParam;
			strWfsResult = HandleUSEREvtResult(lpWfsRet);
			LFSFreeResult(lpWfsRet);
			break ;
		case LFS_SYSTEM_EVENT:
			lpWfsRet = (LPLFSRESULT)lParam;
			strWfsResult = HandleSysEvtResult(lpWfsRet);
			LFSFreeResult(lpWfsRet);
			break;
        case LFS_TIMER_EVENT:
			break;
		default:
			break;
	}

	if ("" != strWfsResult)
	{
		CString strTrace(strWfsResult.length() + 256, 0);

		// 屏蔽敏感信息
		// 1、PinBlock
		std::string strWfsResultLog = strWfsResult;
		if (-1 != strWfsResultLog.find("wfsresult.lpbuffer.lpbdata="))
		{
			strWfsResultLog = strWfsResultLog.substr(0, strWfsResultLog.find("wfsresult.lpbuffer.lpbdata="))
							+ "wfsresult.lpbuffer.lpbdata==***;";

			sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s",
				uMsg, GetXFSMsgStr(uMsg).c_str(), strWfsResultLog.c_str());
		}
		else
		{
			sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s",
				uMsg, GetXFSMsgStr(uMsg).c_str(), strWfsResult.c_str());
		}

		WriteTrace(m_strTraceComponent.c_str(), OCXEVENT, strTrace.c_str());
		
		FireDCEvent(m_strDCName, uMsg, strWfsResult);
	}

	return 0;
}

CString CDCPinPad_30::HandleCmdErr(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dwcommandcode=%d",
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.command_code);
	return strWfsResult;
}

CString CDCPinPad_30::HandleCmdResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	HRESULT hResult = lpWfsRet->result;
	if (LFS_SUCCESS != hResult)
	{
		return HandleCmdErr(lpWfsRet);
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dwcommandcode=%d",
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.command_code);

	DWORD dwCmdCode = lpWfsRet->u.command_code;
	
	CString strCmdResult = "";

	switch (lpWfsRet->u.command_code)
	{
		case LFS_CMD_PIN_CRYPT:
		{
			LPLFSXDATA lpxCryptData = (LPLFSXDATA)lpWfsRet->buffer;
			if (NULL != lpxCryptData && lpxCryptData->length > 0)
			{
				char * pszHexStr = new char[lpxCryptData->length * 2 + 2];
				memset(pszHexStr, 0, lpxCryptData->length * 2 + 2);
				m_Utils.HextoStr(	lpxCryptData->data, 
									lpxCryptData->length, 
									pszHexStr);

				strCmdResult = CString(strlen(pszHexStr) + 256, 0);
				sprintf((char *)strCmdResult.c_str(), 
									"%s"
									"wfsresult.lpbuffer.lpbdata=%s",
									GetStringSplitChar(),
									pszHexStr);
				delete pszHexStr;
				pszHexStr = NULL;
			}

			break ;
		}
		case LFS_CMD_PIN_GET_PIN:
		{
			LPLFSPINENTRY lpEntry = (LPLFSPINENTRY)lpWfsRet->buffer;
			if (NULL != lpEntry)
			{
				strCmdResult = CString(256, 0);
				sprintf((char *)strCmdResult.c_str(), 	"%s"
										"wfsresult.lpbuffer.usdigits=%d"
										"%s"
										"wfsresult.lpbuffer.wcompletion=%d",
										GetStringSplitChar(),
										lpEntry->digits,
										GetStringSplitChar(),
										lpEntry->completion);
			}

			break;
		}
		case LFS_CMD_PIN_GET_DATA:
		{
			CString		 strEnteredData = "";
			BOOL		 bIsFDK = FALSE;
			
			LPLFSPINDATA lpPinData = (LPLFSPINDATA)lpWfsRet->buffer;
			if (NULL != lpPinData)
			{
				strCmdResult = CString(256, 0);
				sprintf((char *)strCmdResult.c_str(), "%s"
									"wfsresult.lpbuffer.uskeys=%d"
									"%s"
									"wfsresult.lpbuffer.wcompletion=%d",
									GetStringSplitChar(),
									lpPinData->keys,
									GetStringSplitChar(),
									lpPinData->completion);

				for (int nLoop = 0; nLoop < lpPinData->keys; nLoop ++)
				{
					CString strTemp(256, 0);
					sprintf((char *)strTemp.c_str(), "%s"
									"wfsresult.lpbuffer.lppinkeys[%d].uldigit=%d",
									GetStringSplitChar(),
									nLoop, lpPinData->pin_keys[nLoop]->digit);
					strCmdResult = string(strCmdResult.c_str()) + strTemp;
				}
			}

			break;
		}
		case LFS_CMD_PIN_GET_PINBLOCK:
		{
			LPLFSXDATA lpxPinBlock = (LPLFSXDATA)lpWfsRet->buffer;
			if (NULL != lpxPinBlock)
			{
				char achPINBlock[64] = { 0 };

				m_Utils.HextoStr(lpxPinBlock->data, lpxPinBlock->length, achPINBlock);

				strCmdResult = CString(strlen(achPINBlock) + 256, 0);
				sprintf((char *)strCmdResult.c_str(), "%s"
					"wfsresult.lpbuffer.uslength=%d"
					"%s"
					"wfsresult.lpbuffer.lpbdata=%s",
					GetStringSplitChar(),
					lpxPinBlock->length,
					GetStringSplitChar(),
					achPINBlock);
			}

			break;
		}
		case LFS_CMD_PIN_IMPORT_KEY:
		case LFS_CMD_PIN_INITIALIZATION:
		case LFS_CMD_PIN_LOCAL_DES:
		case LFS_CMD_PIN_LOCAL_EUROCHEQUE:
		case LFS_CMD_PIN_LOCAL_VISA:
		case LFS_CMD_PIN_CREATE_OFFSET:
		// case LFS_CMD_PIN_DERIVE_KEY:
		case LFS_CMD_PIN_PRESENT_IDC:
		case LFS_CMD_PIN_LOCAL_BANKSYS:
		case LFS_CMD_PIN_BANKSYS_IO:
		case LFS_CMD_PIN_RESET:
		case LFS_CMD_PIN_HSM_SET_TDATA:
		case LFS_CMD_PIN_SECURE_MSG_SEND:
		case LFS_CMD_PIN_SECURE_MSG_RECEIVE:
		case LFS_CMD_PIN_GET_JOURNAL:
		case LFS_CMD_PIN_IMPORT_KEY_EX:
		// case LFS_CMD_PIN_ENC_IO:
		case LFS_CMD_PIN_HSM_INIT:
		case LFS_CMD_PIN_IMPORT_RSA_PUBLIC_KEY:
		case LFS_CMD_PIN_EXPORT_RSA_ISSUER_SIGNED_ITEM:
		case LFS_CMD_PIN_IMPORT_RSA_SIGNED_DES_KEY:
		case LFS_CMD_PIN_GENERATE_RSA_KEY_PAIR:
		case LFS_CMD_PIN_EXPORT_RSA_EPP_SIGNED_ITEM:
		case LFS_CMD_PIN_LOAD_CERTIFICATE:
		case LFS_CMD_PIN_GET_CERTIFICATE:
		case LFS_CMD_PIN_REPLACE_CERTIFICATE:
		case LFS_CMD_PIN_START_KEY_EXCHANGE:
		case LFS_CMD_PIN_IMPORT_RSA_ENCIPHERED_PKCS7_KEY:
		case LFS_CMD_PIN_EMV_IMPORT_PUBLIC_KEY:
		case LFS_CMD_PIN_DIGEST:
			break;
		case LFS_CMD_PIN_ENC_IO:
		{
			LPLFSPINENCIO lpEncIoOut = (LPLFSPINENCIO)lpWfsRet->buffer;
			if (NULL != lpEncIoOut)
			{
				strCmdResult = CString(256, 0);
				sprintf((char *)strCmdResult.c_str(), "%s"
					"wfsresult.lpbuffer.wprotocol=%d"
					"%s"
					"wfsresult.lpbuffer.uldatalength=%d",
					GetStringSplitChar(),
					lpEncIoOut->protocol,
					GetStringSplitChar(),
					lpEncIoOut->data_length);

				if (NULL != lpEncIoOut->data)
				{
					LPPROTCHNIMPORTSM2PUBLICKEYOUT lpKeyOut = (LPPROTCHNIMPORTSM2PUBLICKEYOUT)lpEncIoOut->data;
					if (NULL != lpKeyOut)
					{
						int usLength = 0;
						char achDataHexStr[1024] = { 0 };
						if (NULL != lpKeyOut->lpxKeyCheckValue)
						{
							usLength = lpKeyOut->lpxKeyCheckValue->length;

							m_Utils.HextoStr(lpKeyOut->lpxKeyCheckValue->data,
								usLength,
								achDataHexStr);
						}

						CString strKeyOut = CString(1024, 0);
						sprintf((char *)strKeyOut.c_str(), "%s"
							"wfsresult.lpbuffer.wcommand=%d"
							"%s"
							"wfsresult.lpbuffer.wresult=%d"
							"%s"
							"wfsresult.lpbuffer.dwsm2keycheckmode=%d"
							"%s"
							"wfsresult.lpbuffer.lpxkeycheckvalue.uslength=%d"
							"%s"
							"wfsresult.lpbuffer.lpxkeycheckvalue.lpbdata=%s",
							GetStringSplitChar(),
							lpKeyOut->wCommand,
							GetStringSplitChar(),
							lpKeyOut->wResult,
							GetStringSplitChar(),
							lpKeyOut->dwSM2KeyCheckMode,
							GetStringSplitChar(),
							usLength,
							GetStringSplitChar(),
							achDataHexStr);
						strCmdResult = string(strCmdResult.c_str()) + strKeyOut;
					}
				}
			}

			break;
		}
		case LFS_CMD_PIN_DERIVE_KEY:
		{
			LPLFSXDATA lpxCryptDataOut = (LPLFSXDATA)lpWfsRet->buffer;
			if (NULL != lpxCryptDataOut)
			{
				char achDataHexStr[1024] = { 0 };
				m_Utils.HextoStr(lpxCryptDataOut->data,
					lpxCryptDataOut->length,
					achDataHexStr);

				strCmdResult = CString(1024, 0);
				sprintf((char *)strCmdResult.c_str(), "%s"
					"wfsresult.lpbuffer.uslength=%d"
					"%s"
					"wfsresult.lpbuffer.lpbdata=%s",
					GetStringSplitChar(),
					lpxCryptDataOut->length,
					GetStringSplitChar(),
					achDataHexStr);
			}

			break;
		}
		default:
			break;
 	}

	if ("" != strCmdResult)
	{
		strWfsResult = string(strWfsResult.c_str()) + strCmdResult;
	}

	return strWfsResult;
}

CString CDCPinPad_30::HandleEXEEvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dweventid=%d",
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.event_id);

	CString strCmdEvent = "";

	switch (lpWfsRet->u.event_id)
	{
		case LFS_EXEE_PIN_KEY:
		{
			LPLFSPINKEY lpKey = (LPLFSPINKEY)lpWfsRet->buffer;
			if (NULL != lpKey)
			{
				strCmdEvent = CString(256, 0);
				sprintf((char *)strCmdEvent.c_str(), "%s"
									"wfsresult.lpbuffer.wcompletion=%d"
									"%s"
									"wfsresult.lpbuffer.uldigit=%d",
									GetStringSplitChar(),
									lpKey->completion,
									GetStringSplitChar(),
									lpKey->digit);
			}
			break ;
		}
		default:
			break ;
	}

	if ("" != strCmdEvent)
	{
		strWfsResult = string(strWfsResult.c_str()) + strCmdEvent;
	}

	return strWfsResult;
}

CString CDCPinPad_30::HandleSRVEvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dweventid=%d",
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.event_id);

	return strWfsResult;
}

CString CDCPinPad_30::HandleSysEvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dweventid=%d",
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.event_id);

	CString strSysEvent = "";

	switch(lpWfsRet->u.event_id)
	{
		case LFS_SYSE_DEVICE_STATUS:
		{
			LPLFSDEVSTATUS lpDevStatus = (LPLFSDEVSTATUS)lpWfsRet->buffer;
			if (NULL == lpDevStatus)
			{
				break ;
			}

			strSysEvent = CString((NULL == lpDevStatus->physical_name ? 0 : strlen(lpDevStatus->physical_name))
								+ (NULL == lpDevStatus->workstation_name ? 0 : strlen(lpDevStatus->workstation_name)) + 1024, 0);
			sprintf((char *)strSysEvent.c_str(), 	"%s"
								"wfsresult.lpbuffer.lpszphysicalname=%s"
								"%s"
								"wfsresult.lpbuffer.lpszworkstationname=%s"
								"%s"
								"wfsresult.lpbuffer.dwState=%d",
								GetStringSplitChar(),
								(NULL == lpDevStatus->physical_name ? "NULL" : lpDevStatus->physical_name),
								GetStringSplitChar(),
								(NULL == lpDevStatus->workstation_name ? "NULL" : lpDevStatus->workstation_name),
								GetStringSplitChar(),
								lpDevStatus->state);
			break ;
		}
		case LFS_SYSE_HARDWARE_ERROR:
		case LFS_SYSE_SOFTWARE_ERROR:
		case LFS_SYSE_USER_ERROR:
		{
			LPLFSHWERROR lpWfsHwError = (LPLFSHWERROR)lpWfsRet->buffer; 
			if (NULL == lpWfsHwError)
			{
				break ;
			}

			if (lpWfsHwError->size > 0 && NULL != lpWfsHwError->description)
			{
				strSysEvent = CString((NULL == lpWfsHwError->logical_name ? 0 : strlen(lpWfsHwError->logical_name))
									+ (NULL == lpWfsHwError->physical_name ? 0 : strlen(lpWfsHwError->physical_name))
									+ (NULL == lpWfsHwError->workstation_name ? 0 : strlen(lpWfsHwError->workstation_name))
									+ (NULL == lpWfsHwError->app_id ? 0 : strlen(lpWfsHwError->app_id))
									+ lpWfsHwError->size + 2048, 0);

				sprintf((char *)strSysEvent.c_str(), 	"%s"
									"wfsresult.lpbuffer.lpszlogicalname=%s"
									"%s"
									"wfsresult.lpbuffer.lpszphysicalname=%s"
									"%s"
									"wfsresult.lpbuffer.lpszworkstationname=%s"
									"%s"
									"wfsresult.lpbuffer.lpszappid=%s"
									"%s"
									"wfsresult.lpbuffer.dwaction=%d"
									"%s"
									"wfsresult.lpbuffer.dwsize=%d"
									"%s"
									"wfsresult.lpbuffer.lpbdescription=%s",
									GetStringSplitChar(),
									(NULL == lpWfsHwError->logical_name ? "NULL" : lpWfsHwError->logical_name),
									GetStringSplitChar(),
									(NULL == lpWfsHwError->physical_name ? "NULL" : lpWfsHwError->physical_name),
									GetStringSplitChar(),
									(NULL == lpWfsHwError->workstation_name ? "NULL" : lpWfsHwError->workstation_name),
									GetStringSplitChar(),
									(NULL == lpWfsHwError->app_id ? "NULL" : lpWfsHwError->app_id),
									GetStringSplitChar(),
									lpWfsHwError->action,
									GetStringSplitChar(),
									lpWfsHwError->size,
									GetStringSplitChar(),
									CString((LPCSTR)lpWfsHwError->description, lpWfsHwError->size).c_str());
			}
			break ;
		}
		case LFS_SYSE_APP_DISCONNECT:
		{
			CloseDC();
			m_DCObject.m_bWosaXFSRun=FALSE;

			break ;
		}
		default:
			break ;
	}

	if ("" != strSysEvent)
	{
		strWfsResult = string(strWfsResult.c_str()) + strSysEvent;
	}

	return strWfsResult;
}

CString CDCPinPad_30::HandleUSEREvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dweventid=%d",
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.event_id);

	return strWfsResult;
}

CString	CDCPinPad_30::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[48];
		DWORD iCmd;
	}XFSCmd[]={
		{"WFS_CMD_PIN_CRYPT"				,PIN_SERVICE_OFFSET + 1},
		{"WFS_CMD_PIN_IMPORT_KEY"		    ,PIN_SERVICE_OFFSET + 3},
		{"WFS_CMD_PIN_GET_PIN"              ,PIN_SERVICE_OFFSET + 5},
		{"WFS_CMD_PIN_GET_PINBLOCK"         ,PIN_SERVICE_OFFSET + 7},
		{"WFS_CMD_PIN_GET_DATA"             ,PIN_SERVICE_OFFSET + 8},
		{"WFS_CMD_PIN_INITIALIZATION"       ,PIN_SERVICE_OFFSET + 9},
		{"WFS_CMD_PIN_LOCAL_DES"            ,PIN_SERVICE_OFFSET + 10},
		{"WFS_CMD_PIN_LOCAL_EUROCHEQUE"     ,PIN_SERVICE_OFFSET + 11},
		{"WFS_CMD_PIN_LOCAL_VISA"           ,PIN_SERVICE_OFFSET + 12},
		{"WFS_CMD_PIN_CREATE_OFFSET"        ,PIN_SERVICE_OFFSET + 13},
		{"WFS_CMD_PIN_DERIVE_KEY"           ,PIN_SERVICE_OFFSET + 14},
		{"WFS_CMD_PIN_PRESENT_IDC"          ,PIN_SERVICE_OFFSET + 15},
		{"WFS_CMD_PIN_LOCAL_BANKSYS"        ,PIN_SERVICE_OFFSET + 16},
		{"WFS_CMD_PIN_BANKSYS_IO"           ,PIN_SERVICE_OFFSET + 17},
		{"WFS_CMD_PIN_RESET"                ,PIN_SERVICE_OFFSET + 18},
		{"WFS_CMD_PIN_HSM_SET_TDATA"        ,PIN_SERVICE_OFFSET + 19},
		{"WFS_CMD_PIN_SECURE_MSG_SEND"      ,PIN_SERVICE_OFFSET + 20},
		{"WFS_CMD_PIN_SECURE_MSG_RECEIVE"   ,PIN_SERVICE_OFFSET + 21},
		{"WFS_CMD_PIN_GET_JOURNAL"          ,PIN_SERVICE_OFFSET + 22},
		{"WFS_CMD_PIN_IMPORT_KEY_EX"        ,PIN_SERVICE_OFFSET + 23},
		{"WFS_CMD_PIN_ENC_IO"               ,PIN_SERVICE_OFFSET + 24},
		{"WFS_CMD_PIN_HSM_INIT"             ,PIN_SERVICE_OFFSET + 25},
		{"WFS_CMD_PIN_IMPORT_RSA_PUBLIC_KEY"	            ,PIN_SERVICE_OFFSET + 26},
		{"WFS_CMD_PIN_EXPORT_RSA_ISSUER_SIGNED_ITEM"   	    ,PIN_SERVICE_OFFSET + 27},
		{"WFS_CMD_PIN_IMPORT_RSA_SIGNED_DES_KEY" 			,PIN_SERVICE_OFFSET + 28},
		{"WFS_CMD_PIN_GENERATE_RSA_KEY_PAIR"				,PIN_SERVICE_OFFSET + 29},
		{"WFS_CMD_PIN_EXPORT_RSA_EPP_SIGNED_ITEM"			,PIN_SERVICE_OFFSET + 30},
		{"WFS_CMD_PIN_LOAD_CERTIFICATE"     				,PIN_SERVICE_OFFSET + 31},
		{"WFS_CMD_PIN_GET_CERTIFICATE"      				,PIN_SERVICE_OFFSET + 32},
		{"WFS_CMD_PIN_REPLACE_CERTIFICATE"  				,PIN_SERVICE_OFFSET + 33},
		{"WFS_CMD_PIN_START_KEY_EXCHANGE"   				,PIN_SERVICE_OFFSET + 34},
		{"WFS_CMD_PIN_IMPORT_RSA_ENCIPHERED_PKCS7_KEY"      ,PIN_SERVICE_OFFSET + 35},
		{"WFS_CMD_PIN_EMV_IMPORT_PUBLIC_KEY"				,PIN_SERVICE_OFFSET + 36},
		{"WFS_CMD_PIN_DIGEST"              					,PIN_SERVICE_OFFSET + 37}};

	CString strRes = "UNKNOWN CMD";

	for (int i = 0; i < sizeof(XFSCmd) / sizeof(XFSCMD); i ++)
	{
		if (XFSCmd[i].iCmd == dwCmdCode )
		{
			strRes = XFSCmd[i].strCmd;
			break;
		}
	}

	return strRes;
}


CString	CDCPinPad_30::GetXFSErrStr(HRESULT hResult)
{
	if (hResult >= DC_ERROR && hResult < LFS_ERR_UNSUPP_DATA)
	{
		return "DC_ERROR";
	}

	struct XFSERR {
		char strErr[48];
		short iErr;
	}XFSErr[]={
		{	"WFS_SUCCESS"				,0},
		{	"WFS_ERR_ALREADY_STARTED"	,-1},
		{	"WFS_ERR_API_VER_TOO_HIGH"	,-2},
		{	"WFS_ERR_API_VER_TOO_LOW"	,-3},
		{	"WFS_ERR_CANCELED"			,-4},
		{	"WFS_ERR_CFG_INVALID_HKEY"	,-5},
		{	"WFS_ERR_CFG_INVALID_NAME"	,-6},
		{	"WFS_ERR_CFG_INVALID_SUBKEY",-7},
		{	"WFS_ERR_CFG_INVALID_VALUE"	,-8},
		{	"WFS_ERR_CFG_KEY_NOT_EMPTY"	,-9},
		{	"WFS_ERR_CFG_NAME_TOO_LONG"	,-10},
		{	"WFS_ERR_CFG_NO_MORE_ITEMS"	,-11},
		{	"WFS_ERR_CFG_VALUE_TOO_LONG",-12},
		{	"WFS_ERR_DEV_NOT_READY"		,-13},
		{	"WFS_ERR_HARDWARE_ERROR"	,-14},
		{	"WFS_ERR_INTERNAL_ERROR"	,-15},
		{	"WFS_ERR_INVALID_ADDRESS"	,-16},
		{	"WFS_ERR_INVALID_APP_HANDLE",-17},
		{	"WFS_ERR_INVALID_BUFFER"	,-18},
		{	"WFS_ERR_INVALID_CATEGORY"	,-19},
		{	"WFS_ERR_INVALID_COMMAND"	,-20},
		{	"WFS_ERR_INVALID_EVENT_CLASS",-21},
		{	"WFS_ERR_INVALID_HSERVICE"	,-22},
		{	"WFS_ERR_INVALID_HPROVIDER"	,-23},
		{	"WFS_ERR_INVALID_HWND"		,-24},
		{	"WFS_ERR_INVALID_HWNDREG"	,-25},
		{	"WFS_ERR_INVALID_POINTER"	,-26},
		{	"WFS_ERR_INVALID_REQ_ID"	,-27},
		{	"WFS_ERR_INVALID_RESULT"	,-28},
		{	"WFS_ERR_INVALID_SERVPROV"	,-29},
		{	"WFS_ERR_INVALID_TIMER"		,-30},
		{	"WFS_ERR_INVALID_TRACELEVEL",-31},
		{	"WFS_ERR_LOCKED"			,-32},
		{	"WFS_ERR_NO_BLOCKING_CALL"	,-33},
		{	"WFS_ERR_NO_SERVPROV"		,-34},
		{	"WFS_ERR_NO_SUCH_THREAD"	,-35},
		{	"WFS_ERR_NO_TIMER"			,-36},
		{	"WFS_ERR_NOT_LOCKED"		,-37},
		{	"WFS_ERR_NOT_OK_TO_UNLOAD"	,-38},
		{	"WFS_ERR_NOT_STARTED"		,-39},
		{	"WFS_ERR_NOT_REGISTERED"	,-40},
		{	"WFS_ERR_OP_IN_PROGRESS"	,-41},
		{	"WFS_ERR_OUT_OF_MEMORY"		,-42},
		{	"WFS_ERR_SERVICE_NOT_FOUND"	,-43},
		{	"WFS_ERR_SPI_VER_TOO_HIGH"	,-44},
		{	"WFS_ERR_SPI_VER_TOO_LOW"	,-45},
		{	"WFS_ERR_SRVC_VER_TOO_HIGH"	,-46},
		{	"WFS_ERR_SRVC_VER_TOO_LOW"	,-47},
		{	"WFS_ERR_TIMEOUT"			,-48},
		{	"WFS_ERR_UNSUPP_CATEGORY"	,-49},
		{	"WFS_ERR_UNSUPP_COMMAND"	,-50},
		{	"WFS_ERR_VERSION_ERROR_IN_SRVC",-51},
		{	"WFS_ERR_INVALID_DATA"		,-52},
		{	"WFS_ERR_SOFTWARE_ERROR"	,-53},
		{	"WFS_ERR_CONNECTION_LOST"	,-54},
		{	"WFS_ERR_USER_ERROR"		,-55},
		{	"WFS_ERR_UNSUPP_DATA"		,-56},
		{"WFS_ERR_PIN_KEYNOTFOUND"           ,-(PIN_SERVICE_OFFSET + 0)}, 
		{"WFS_ERR_PIN_MODENOTSUPPORTED"      ,-(PIN_SERVICE_OFFSET + 1)}, 
		{"WFS_ERR_PIN_ACCESSDENIED"          ,-(PIN_SERVICE_OFFSET + 2)}, 
		{"WFS_ERR_PIN_INVALIDID"             ,-(PIN_SERVICE_OFFSET + 3)}, 
		{"WFS_ERR_PIN_DUPLICATEKEY"          ,-(PIN_SERVICE_OFFSET + 4)}, 
		{"WFS_ERR_PIN_KEYNOVALUE"            ,-(PIN_SERVICE_OFFSET + 6)}, 
		{"WFS_ERR_PIN_USEVIOLATION"          ,-(PIN_SERVICE_OFFSET + 7)}, 
		{"WFS_ERR_PIN_NOPIN"                 ,-(PIN_SERVICE_OFFSET + 8)}, 
		{"WFS_ERR_PIN_INVALIDKEYLENGTH"      ,-(PIN_SERVICE_OFFSET + 9)}, 
		{"WFS_ERR_PIN_KEYINVALID"            ,-(PIN_SERVICE_OFFSET + 10)},
		{"WFS_ERR_PIN_KEYNOTSUPPORTED"       ,-(PIN_SERVICE_OFFSET + 11)},
		{"WFS_ERR_PIN_NOACTIVEKEYS"          ,-(PIN_SERVICE_OFFSET + 12)},
		{"WFS_ERR_PIN_NOTERMINATEKEYS"       ,-(PIN_SERVICE_OFFSET + 14)},
		{"WFS_ERR_PIN_MINIMUMLENGTH"         ,-(PIN_SERVICE_OFFSET + 15)},
		{"WFS_ERR_PIN_PROTOCOLNOTSUPP"       ,-(PIN_SERVICE_OFFSET + 16)},
		{"WFS_ERR_PIN_INVALIDDATA"           ,-(PIN_SERVICE_OFFSET + 17)},
		{"WFS_ERR_PIN_NOTALLOWED"            ,-(PIN_SERVICE_OFFSET + 18)},
		{"WFS_ERR_PIN_NOKEYRAM"              ,-(PIN_SERVICE_OFFSET + 19)},
		{"WFS_ERR_PIN_NOCHIPTRANSACTIVE"     ,-(PIN_SERVICE_OFFSET + 20)},
		{"WFS_ERR_PIN_ALGORITHMNOTSUPP"      ,-(PIN_SERVICE_OFFSET + 21)},
		{"WFS_ERR_PIN_FORMATNOTSUPP"         ,-(PIN_SERVICE_OFFSET + 22)},
		{"WFS_ERR_PIN_HSMSTATEINVALID"       ,-(PIN_SERVICE_OFFSET + 23)},
		{"WFS_ERR_PIN_MACINVALID"            ,-(PIN_SERVICE_OFFSET + 24)},
		{"WFS_ERR_PIN_PROTINVALID"           ,-(PIN_SERVICE_OFFSET + 25)},
		{"WFS_ERR_PIN_FORMATINVALID"         ,-(PIN_SERVICE_OFFSET + 26)},
		{"WFS_ERR_PIN_CONTENTINVALID"        ,-(PIN_SERVICE_OFFSET + 27)},
		{"WFS_ERR_PIN_SIG_NOT_SUPP"          ,-(PIN_SERVICE_OFFSET + 29)},
		{"WFS_ERR_PIN_INVALID_MOD_LEN"       ,-(PIN_SERVICE_OFFSET + 31)},
		{"WFS_ERR_PIN_INVALIDCERTSTATE"      ,-(PIN_SERVICE_OFFSET + 32)},
		{"WFS_ERR_PIN_KEY_GENERATION_ERROR"  ,-(PIN_SERVICE_OFFSET + 33)},
		{"WFS_ERR_PIN_EMV_VERIFY_FAILED"     ,-(PIN_SERVICE_OFFSET + 34)},
		{"WFS_ERR_PIN_RANDOMINVALID"         ,-(PIN_SERVICE_OFFSET + 35)},
		{"WFS_ERR_PIN_SIGNATUREINVALID"      ,-(PIN_SERVICE_OFFSET + 36)},
		{"WFS_ERR_PIN_SNSCDINVALID"          ,-(PIN_SERVICE_OFFSET + 37)},
		{"WFS_ERR_PIN_NORSAKEYPAIR"          ,-(PIN_SERVICE_OFFSET + 38)}};

	CString strRes = "UNKNOWN ERROR";

	for (int i = 0; i < sizeof(XFSErr) / sizeof(XFSERR); i ++)
	{
		if (XFSErr[i].iErr == hResult )
		{
			strRes = XFSErr[i].strErr;
			break;
		}
	}

	return strRes;
}

CString	CDCPinPad_30::GetXFSMsgStr(DWORD dwEventID)
{
	struct XFSMSG {
		char strMsg[128];
		DWORD iMsg;
	}XFSMsg[]={
		{"WFS_OPEN_COMPLETE"					,(WM_USER + 1)},
		{"WFS_CLOSE_COMPLETE"					,(WM_USER + 2)},
		{"WFS_LOCK_COMPLETE"					,(WM_USER + 3)},
		{"WFS_UNLOCK_COMPLETE"					,(WM_USER + 4)},
		{"WFS_REGISTER_COMPLETE"				,(WM_USER + 5)},
		{"WFS_DEREGISTER_COMPLETE"				,(WM_USER + 6)},
		{"WFS_GETINFO_COMPLETE"					,(WM_USER + 7)},
		{"WFS_EXECUTE_COMPLETE"					,(WM_USER + 8)},

		{"WFS_EXECUTE_EVENT"					,(WM_USER + 20)},
		{"WFS_SERVICE_EVENT"					,(WM_USER + 21)},
		{"WFS_USER_EVENT"						,(WM_USER + 22)},
		{"WFS_SYSTEM_EVENT"						,(WM_USER + 23)},

		{"WFS_TIMER_EVENT"						,(WM_USER + 100)},

		{"WFS_EXEE_PIN_KEY"                  ,(PIN_SERVICE_OFFSET + 1)},
		{"WFS_SRVE_PIN_INITIALIZED"          ,(PIN_SERVICE_OFFSET + 2)},
		{"WFS_SRVE_PIN_ILLEGAL_KEY_ACCESS"   ,(PIN_SERVICE_OFFSET + 3)},
		{"WFS_SRVE_PIN_OPT_REQUIRED"         ,(PIN_SERVICE_OFFSET + 4)},
		{"WFS_SRVE_PIN_HSM_TDATA_CHANGED"    ,(PIN_SERVICE_OFFSET + 5)},
		{"WFS_SRVE_PIN_CERTIFICATE_CHANGE"   ,(PIN_SERVICE_OFFSET + 6)}
	};
	CString strRes="UNKNOWN MSG";
	for (int i = 0; i < sizeof(XFSMsg) / sizeof(XFSMSG); i ++)
	{
		if (XFSMsg[i].iMsg==dwEventID )
		{
			strRes=XFSMsg[i].strMsg;
			break;
		}
	}
	return strRes;
}

CString	CDCPinPad_30::GetXFSSysEvtStr(DWORD dwEventID)
{
	struct XFSSYSEVT {
		char strSysEvt[128];
		DWORD iSysEvt;
	}XFSSysEvt[]={
		{"WFS_SYSE_UNDELIVERABLE_MSG"              ,1},
		{"WFS_SYSE_HARDWARE_ERROR"                 ,2},
		{"WFS_SYSE_VERSION_ERROR"                  ,3},
		{"WFS_SYSE_DEVICE_STATUS"                  ,4},
		{"WFS_SYSE_APP_DISCONNECT"                 ,5},
		{"WFS_SYSE_SOFTWARE_ERROR"                 ,6},
		{"WFS_SYSE_USER_ERROR"                     ,7},
		{"WFS_SYSE_LOCK_REQUESTED"                 ,8}
	};
	CString strRes="UNKNOWN MSG";
	for (int i = 0; i < sizeof(XFSSysEvt) / sizeof(XFSSYSEVT); i ++)
	{
		if (XFSSysEvt[i].iSysEvt==dwEventID )
		{
			strRes=XFSSysEvt[i].strSysEvt;
			break;
		}
	}
	return strRes;
}

// 密钥分发相关支持
HRESULT CDCPinPad_30::CMD_PIN_ENC_IO(long lCommand, LPCTSTR strKeyName, LPCTSTR strDataHex, long lUse, LPCTSTR strSigKey, long lSM2SignatureAlgorithm, LPCTSTR strSignatureHex)
{
	if (NULL == strKeyName || NULL == strDataHex || NULL == strSigKey || NULL == strSignatureHex)
	{
		return -1;
	}

	HRESULT hResult = DC_ERROR;

	LFSPINENCIO pinEncIo = { 0 };
	PROTCHNIMPORTSM2PUBLICKEYIN InData = { 0 };

	InData.wCommand = (WORD)lCommand;  // WFS_CMD_ENC_IO_CHN_IMPORT_SM2_PUBLIC_KEY 或者 WFS_CMD_ENC_IO_CHN_IMPORT_RSA_PUBLIC_KEY

	InData.lpsKey = (LPTSTR)(LPCTSTR)strKeyName;  // 公钥名字
	InData.dwUse = (WORD)lUse;  // 公钥用法：PROT_CHN_USESM2PUBLIC 或者 WFS_PIN_USERSAPUBLIC

	// 公钥证书数据
	int nLenBytes = strlen(strDataHex) / 2;
	BYTE * pszValue = new BYTE[nLenBytes];
	memset(pszValue, 0, nLenBytes);
	m_Utils.StrtoHex((LPTSTR)(LPCTSTR)strDataHex, pszValue);

	LFSXDATA wfsxValue = { 0 };
	wfsxValue.data = pszValue;
	wfsxValue.length = nLenBytes;
	InData.lpxValue = &wfsxValue;

	InData.lpsSigKey = (NULL == strSigKey || 0 == strlen(strSigKey)) ? NULL : (LPTSTR)(LPCTSTR)strSigKey;  // NULL
	InData.dwSM2SignatureAlgorithm = lSM2SignatureAlgorithm;  // 0

	InData.lpxSignature = NULL;

	BYTE * pszSignatureValue = NULL;
	LFSXDATA wfsxSignature = { 0 };
	if (NULL != strSignatureHex && 0 != strlen(strSignatureHex))
	{
		int nLenSignature = strlen(strSignatureHex) / 2;
		pszSignatureValue = new BYTE[nLenSignature];
		memset(pszSignatureValue, 0, nLenSignature);
		m_Utils.StrtoHex((LPTSTR)(LPCTSTR)strSignatureHex, pszSignatureValue);

		wfsxSignature.data = pszSignatureValue;
		wfsxSignature.length = nLenSignature;

		InData.lpxSignature = &wfsxSignature;
	}

	pinEncIo.protocol = LFS_PIN_ENC_PROT_CHN;
	pinEncIo.data_length = sizeof(InData);
	pinEncIo.data = &InData;

	hResult = LFSAsyncExecute(m_DCObject.m_hService,
		LFS_CMD_PIN_ENC_IO,
		(LPVOID)&pinEncIo,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	if (NULL != pszValue)
	{
		delete pszValue;
		pszValue = NULL;
	}

	if (NULL != pszSignatureValue)
	{
		delete pszSignatureValue;
		pszSignatureValue = NULL;
	}

	return hResult;
}

//*
HRESULT CDCPinPad_30::CMD_PIN_DERIVE_KEY(long wDerivationAlgorithm, LPCTSTR strKeyName, LPCTSTR strKeyGenKey, LPCTSTR strStartValueKey, LPCTSTR strBytesHexStartValue, long lPadding, LPCTSTR strBytesHexInputData, LPCTSTR strBytesHexIdentification)
{
	if (NULL == strKeyName || NULL == strKeyGenKey)
	{
		return -1;
	}

	HRESULT hResult = DC_ERROR;

	LFSPINDERIVE pinderive = { 0 };
	pinderive.derivation_algorithm = (WORD)wDerivationAlgorithm;  // WFS_PIN_KEYDES 或者 WFS_PIN_KEYSM4
	pinderive.key = (NULL == strKeyName || 0 == strlen(strKeyName)) ? NULL : (LPTSTR)(LPCTSTR)strKeyName;
	pinderive.key_gen_key = (NULL == strKeyGenKey || 0 == strlen(strKeyGenKey)) ? NULL : (LPTSTR)(LPCTSTR)strKeyGenKey;  // NULL
	pinderive.start_value_key = (NULL == strStartValueKey || 0 == strlen(strStartValueKey)) ? NULL : (LPTSTR)(LPCTSTR)strStartValueKey;  // NULL

	BYTE * pszStartValue = NULL;
	pinderive.start_value = NULL;
	LFSXDATA wfsxStartValue = { 0 };
	if (NULL != strBytesHexStartValue && 0 != strlen(strBytesHexStartValue))
	{
		int nLenStartValue = strlen(strBytesHexStartValue) / 2;
		pszStartValue = new BYTE[nLenStartValue];
		memset(pszStartValue, 0, nLenStartValue);
		m_Utils.StrtoHex((LPTSTR)(LPCTSTR)strBytesHexStartValue, pszStartValue);

		wfsxStartValue.data = pszStartValue;
		wfsxStartValue.length = nLenStartValue;

		pinderive.start_value = &wfsxStartValue;
	}

	pinderive.padding = (BYTE)lPadding;

	BYTE * pszInputData = NULL;
	pinderive.input_data = NULL;
	LFSXDATA wfsxInputData = { 0 };
	if (NULL != strBytesHexInputData && 0 != strlen(strBytesHexInputData))
	{
		int nLenInputData = strlen(strBytesHexInputData) / 2;
		pszInputData = new BYTE[nLenInputData];
		memset(pszInputData, 0, nLenInputData);
		m_Utils.StrtoHex((LPTSTR)(LPCTSTR)strBytesHexInputData, pszInputData);

		wfsxStartValue.data = pszInputData;
		wfsxStartValue.length = nLenInputData;

		pinderive.input_data = &wfsxInputData;
	}

	BYTE * pszIdent = NULL;
	pinderive.ident = NULL;
	LFSXDATA wfsxIdent = { 0 };
	if (NULL != strBytesHexIdentification && 0 != strlen(strBytesHexIdentification))
	{
		int nLenIdent = strlen(strBytesHexIdentification) / 2;
		pszIdent = new BYTE[nLenIdent];
		memset(pszIdent, 0, nLenIdent);
		m_Utils.StrtoHex((LPTSTR)(LPCTSTR)strBytesHexIdentification, pszIdent);

		wfsxStartValue.data = pszIdent;
		wfsxStartValue.length = nLenIdent;

		pinderive.ident = &wfsxIdent;
	}

	hResult = LFSAsyncExecute(m_DCObject.m_hService,
		LFS_CMD_PIN_DERIVE_KEY,
		&pinderive,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	if (NULL != pszStartValue)
	{
		delete pszStartValue;
		pszStartValue = NULL;
	}

	if (NULL != pszInputData)
	{
		delete pszInputData;
		pszInputData = NULL;
	}

	if (NULL != pszIdent)
	{
		delete pszIdent;
		pszIdent = NULL;
	}

	return (short)hResult;
}
//*/

/*
HRESULT CDCPinPad_30::CMD_PIN_DERIVE_KEY(long wDerivationAlgorithm, LPCTSTR strKeyName, LPCTSTR strKeyGenKey, LPCTSTR strStartValueKey, LPCTSTR strBytesHexStartValue, long lPadding, LPCTSTR strBytesHexInputData, LPCTSTR strBytesHexIdentification)
{
	if (NULL == strKeyName || NULL == strKeyGenKey)
	{
		return -1;
	}

	printf(NULL == strKeyName ? "true\n" : "false\n");
	printf("strlen(strKeyName) = %d\n", strlen(strKeyName));
	printf("strKeyName = %s\n", strKeyName);

	HRESULT hResult = DC_ERROR;

	LFSPINDERIVE pinderive = { 0 };
	pinderive.derivation_algorithm = (WORD)wDerivationAlgorithm;  // WFS_PIN_KEYDES 或者 WFS_PIN_KEYSM4
	// pinderive.key = (NULL == strKeyName || 0 == strlen(strKeyName)) ? NULL : strdup(strKeyName);
	pinderive.key = "RandomKey";
	// pinderive.key_gen_key = (NULL == strKeyGenKey || 0 == strlen(strKeyGenKey)) ? NULL : strdup(strKeyGenKey);  // NULL
	pinderive.key_gen_key = "PublicKey";  // NULL
	// pinderive.start_value_key = (NULL == strStartValueKey || 0 == strlen(strStartValueKey)) ? NULL : strdup(strStartValueKey);  // NULL
	pinderive.start_value_key = NULL;  // NULL

	printf("pinderive.key = %s", pinderive.key);
	printf("\n");
	printf("pinderive.key_gen_key = %s", pinderive.key_gen_key);
	printf("\n");

	BYTE * pszStartValue = NULL;
	// pinderive.start_value = NULL;
	pinderive.start_value = NULL;  // NULL
	LFSXDATA wfsxStartValue = { 0 };
	if (NULL != strBytesHexStartValue && 0 != strlen(strBytesHexStartValue))
	{
		int nLenStartValue = strlen(strBytesHexStartValue) / 2;
		pszStartValue = new BYTE[nLenStartValue];
		memset(pszStartValue, 0, nLenStartValue);
		m_Utils.StrtoHex((LPTSTR)(LPCTSTR)strBytesHexStartValue, pszStartValue);

		wfsxStartValue.data = pszStartValue;
		wfsxStartValue.length = nLenStartValue;

		pinderive.start_value = &wfsxStartValue;
		printf("pinderive.start_value\n");
	}

	pinderive.padding = (BYTE)lPadding;

	BYTE * pszInputData = NULL;
	// pinderive.input_data = NULL;
	pinderive.input_data = NULL;  // NULL
	LFSXDATA wfsxInputData = { 0 };
	if (NULL != strBytesHexInputData && 0 != strlen(strBytesHexInputData))
	{
		int nLenInputData = strlen(strBytesHexInputData) / 2;
		pszInputData = new BYTE[nLenInputData];
		memset(pszInputData, 0, nLenInputData);
		m_Utils.StrtoHex((LPTSTR)(LPCTSTR)strBytesHexInputData, pszInputData);

		wfsxStartValue.data = pszInputData;
		wfsxStartValue.length = nLenInputData;

		pinderive.input_data = &wfsxInputData;
		printf("pinderive.input_data\n");
	}

	BYTE * pszIdent = NULL;
	// pinderive.ident = NULL;
	pinderive.ident = NULL;  // NULL
	LFSXDATA wfsxIdent = { 0 };
	if (NULL != strBytesHexIdentification && 0 != strlen(strBytesHexIdentification))
	{
		int nLenIdent = strlen(strBytesHexIdentification) / 2;
		pszIdent = new BYTE[nLenIdent];
		memset(pszIdent, 0, nLenIdent);
		m_Utils.StrtoHex((LPTSTR)(LPCTSTR)strBytesHexIdentification, pszIdent);

		wfsxStartValue.data = pszIdent;
		wfsxStartValue.length = nLenIdent;

		pinderive.ident = &wfsxIdent;
		printf("pinderive.ident\n");
	}

	printf("\n\n\nstruct pinderive\n");
	printf("&pinderive = %d\n", &pinderive);
	printf("&pinderive.derivation_algorithm = %d, offset = %d\n", &pinderive.derivation_algorithm, ((long)&pinderive.derivation_algorithm - (long)&pinderive));
	printf("&pinderive.key = %d, offset = %d\n", &pinderive.key, ((long)&pinderive.key - (long)&pinderive));
	printf("&pinderive.key_gen_key = %d, offset = %d\n", &pinderive.key_gen_key, ((long)&pinderive.key_gen_key - (long)&pinderive));
	printf("&pinderive.start_value_key = %d, offset = %d\n", &pinderive.start_value_key, ((long)&pinderive.start_value_key - (long)&pinderive));
	printf("&pinderive.start_value = %d, offset = %d\n", &pinderive.start_value, ((long)&pinderive.start_value - (long)&pinderive));
	printf("&pinderive.padding = %d, offset = %d\n", &pinderive.padding, ((long)&pinderive.padding - (long)&pinderive));
	printf("&pinderive.input_data = %d, offset = %d\n", &pinderive.input_data, ((long)&pinderive.input_data - (long)&pinderive));
	printf("&pinderive.ident = %d, offset = %d\n", &pinderive.ident, ((long)&pinderive.ident - (long)&pinderive));
	printf("\n\n\n");

	hResult = LFSAsyncExecute(m_DCObject.m_hService,
		LFS_CMD_PIN_DERIVE_KEY,
		&pinderive,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	if (NULL != pszStartValue)
	{
		delete pszStartValue;
		pszStartValue = NULL;
	}

	if (NULL != pszInputData)
	{
		delete pszInputData;
		pszInputData = NULL;
	}

	if (NULL != pszIdent)
	{
		delete pszIdent;
		pszIdent = NULL;
	}

	return (short)hResult;
}
//*/

HRESULT CDCPinPad_30::CMD_PIN_IMPORT_KEY_EX(LPCTSTR strKeyName, LPCTSTR strBytesHexKeyValue, LPCTSTR strEncKeyName, LPCTSTR strBytesHexControlVector, DWORD fwUse, WORD wKeyCheckMode, LPCTSTR strBytesHexKeyCheckValue)
{
	return 0;
}


