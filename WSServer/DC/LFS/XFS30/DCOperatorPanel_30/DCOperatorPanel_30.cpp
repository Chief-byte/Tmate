// DCOperatorPanel_30.cpp: implementation of the CDCOperatorPanel_30 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCOperatorPanel_30.h"
#include "../../include/JavaScriptStringParam.h"

CDCOperatorPanel_30::CDCOperatorPanel_30(LPCTSTR strDCName, LPCTSTR strTraceComponent)
{
	m_strDCName = strDCName;
	m_strTraceComponent = CString(strTraceComponent);
	m_DCObject.m_bWosaXFSRun = FALSE;
}

CDCOperatorPanel_30::~CDCOperatorPanel_30()
{
}

HRESULT CDCOperatorPanel_30::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// 调用命令
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_TTU_BEEP"))
	{
		bValid = TRUE;
		hResult = CMD_TTU_BEEP(atol(CJSStringParam::GetStringParam(strarrParams, "lpwbeep").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_TTU_CLEARSCREEN"))
	{
		bValid = TRUE;
		hResult = CMD_TTU_CLEARSCREEN(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "wpositionx").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "wpositiony").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "wwidth").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "wheight").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_TTU_DISPLIGHT"))
	{
		bValid = TRUE;
		hResult = CMD_TTU_DISPLIGHT(atol(CJSStringParam::GetStringParam(strarrParams, "bmode").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_TTU_SET_LED"))
	{
		bValid = TRUE;
		hResult = CMD_TTU_SET_LED(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "wled").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwcommand").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_TTU_SET_RESOLUTION"))
	{
		bValid = TRUE;
		hResult = CMD_TTU_SET_RESOLUTION(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "wsizex").c_str()), 
											(short)atol(CJSStringParam::GetStringParam(strarrParams, "wsizey").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_TTU_WRITE_FORM"))
	{
		bValid = TRUE;
		hResult = CMD_TTU_WRITE_FORM(	CJSStringParam::GetStringParam(strarrParams, "lpszformname").c_str(),
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "bclearscreen").c_str()), 
										CJSStringParam::GetStringParam(strarrParams, "lpszfields").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpszunicodefields").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_TTU_READ_FORM"))
	{
		bValid = TRUE;
		hResult = CMD_TTU_READ_FORM(	CJSStringParam::GetStringParam(strarrParams, "lpszformname").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpszfieldnames").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_TTU_WRITE"))
	{
		bValid = TRUE;
		hResult = CMD_TTU_WRITE(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwmode").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "wposx").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "wposy").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwtextattr").c_str()), 
									CJSStringParam::GetStringParam(strarrParams, "lpstext").c_str(),
									CJSStringParam::GetStringParam(strarrParams, "lpsunicodetext").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_TTU_READ"))
	{
		bValid = TRUE;
		hResult = CMD_TTU_READ(	atol(CJSStringParam::GetStringParam(strarrParams, "wnumofchars").c_str()), 
								atol(CJSStringParam::GetStringParam(strarrParams, "fwmode").c_str()), 
								atol(CJSStringParam::GetStringParam(strarrParams, "wposx").c_str()), 
								atol(CJSStringParam::GetStringParam(strarrParams, "wposy").c_str()), 
								atol(CJSStringParam::GetStringParam(strarrParams, "fwechomode").c_str()), 
								atol(CJSStringParam::GetStringParam(strarrParams, "fwechoattr").c_str()),  
								atol(CJSStringParam::GetStringParam(strarrParams, "bcursor").c_str()),  
								atol(CJSStringParam::GetStringParam(strarrParams, "bflush").c_str()),  
								atol(CJSStringParam::GetStringParam(strarrParams, "bautoend").c_str()),  
								CJSStringParam::GetStringParam(strarrParams, "lpszactivekeys").c_str(),
								CJSStringParam::GetStringParam(strarrParams, "lpwszactiveunicodekeys").c_str(),
								CJSStringParam::GetStringParam(strarrParams, "lpwactivecommandkeys").c_str(),
								CJSStringParam::GetStringParam(strarrParams, "lpwterminatecommandkeys").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_TTU_RESET"))
	{
		bValid = TRUE;
		hResult = CMD_TTU_RESET();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_TTU_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_TTU_CAPABILITIES();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_TTU_FORM_LIST"))
	{
		bValid = TRUE;
		hResult = INF_TTU_FORM_LIST();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_TTU_QUERY_FORM"))
	{
		bValid = TRUE;
		hResult = INF_TTU_QUERY_FORM(CJSStringParam::GetStringParam(strarrParams, "lpszformname").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_INF_TTU_QUERY_FIELD"))
	{
		bValid = TRUE;
		hResult = INF_TTU_QUERY_FIELD(	CJSStringParam::GetStringParam(strarrParams, "lpszformname").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpszfieldname").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_INF_TTU_KEY_DETAIL"))
	{
		bValid = TRUE;
		hResult = INF_TTU_KEY_DETAIL();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_TTU_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_TTU_STATUS();
	}

	return hResult;
}

CString	CDCOperatorPanel_30::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[]={
		{"WFS_CMD_TTU_BEEP"                    ,(TTU_SERVICE_OFFSET + 1)},
		{"WFS_CMD_TTU_CLEARSCREEN"             ,(TTU_SERVICE_OFFSET + 2)},
		{"WFS_CMD_TTU_DISPLIGHT"               ,(TTU_SERVICE_OFFSET + 3)},
		{"WFS_CMD_TTU_SET_LED"                 ,(TTU_SERVICE_OFFSET + 4)},
		{"WFS_CMD_TTU_SET_RESOLUTION"          ,(TTU_SERVICE_OFFSET + 5)},
		{"WFS_CMD_TTU_WRITE_FORM"              ,(TTU_SERVICE_OFFSET + 6)},
		{"WFS_CMD_TTU_READ_FORM"               ,(TTU_SERVICE_OFFSET + 7)},
		{"WFS_CMD_TTU_WRITE"                   ,(TTU_SERVICE_OFFSET + 8)},
		{"WFS_CMD_TTU_READ"                    ,(TTU_SERVICE_OFFSET + 9)},
		{"WFS_CMD_TTU_RESET"                   ,(TTU_SERVICE_OFFSET + 10)}
	};
	CString strRes="UNKNOWN CMD";
	for (int i = 0; i < sizeof(XFSCmd) / sizeof(XFSCMD); i ++)
	{
		if( XFSCmd[i].iCmd==dwCmdCode )
		{
			strRes=XFSCmd[i].strCmd;
			break;
		}
	}
	return strRes;
}

CString	CDCOperatorPanel_30::GetXFSMsgStr(DWORD dwEventID)
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

		{"WFS_EXEE_TTU_FIELDERROR"              ,(TTU_SERVICE_OFFSET + 1)},
		{"WFS_EXEE_TTU_FIELDWARNING"            ,(TTU_SERVICE_OFFSET + 2)},
		{"WFS_EXEE_TTU_KEY"                     ,(TTU_SERVICE_OFFSET + 3)}
	};
	CString strRes="UNKNOWN MSG";
	for (int i = 0; i < sizeof(XFSMsg) / sizeof(XFSMSG); i ++)
	{
		if( XFSMsg[i].iMsg==dwEventID )
		{
			strRes=XFSMsg[i].strMsg;
			break;
		}
	}
	return strRes;
}

CString	CDCOperatorPanel_30::GetXFSSysEvtStr(DWORD dwEventID)
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
		if( XFSSysEvt[i].iSysEvt==dwEventID )
		{
			strRes=XFSSysEvt[i].strSysEvt;
			break;
		}
	}
	return strRes;
}

CString	CDCOperatorPanel_30::GetXFSErrStr(HRESULT hResult)
{
	if (hResult >= DC_ERROR && hResult < LFS_ERR_UNSUPP_DATA)
	{
		return "DC_ERROR";
	}

	struct XFSERR {
		char strErr[128];
		LONG iErr;
	}XFSErr[]={
		{"WFS_SUCCESS"						,0},
		{"WFS_ERR_ALREADY_STARTED"			,-1},
		{"WFS_ERR_API_VER_TOO_HIGH"			,-2},
		{"WFS_ERR_API_VER_TOO_LOW"			,-3},
		{"WFS_ERR_CANCELED"					,-4},
		{"WFS_ERR_CFG_INVALID_HKEY"			,-5},
		{"WFS_ERR_CFG_INVALID_NAME"			,-6},
		{"WFS_ERR_CFG_INVALID_SUBKEY"		,-7},
		{"WFS_ERR_CFG_INVALID_VALUE"		,-8},
		{"WFS_ERR_CFG_KEY_NOT_EMPTY"		,-9},
		{"WFS_ERR_CFG_NAME_TOO_LONG"		,-10},
		{"WFS_ERR_CFG_NO_MORE_ITEMS"		,-11},
		{"WFS_ERR_CFG_VALUE_TOO_LONG"		,-12},
		{"WFS_ERR_DEV_NOT_READY"			,-13},
		{"WFS_ERR_HARDWARE_ERROR"			,-14},
		{"WFS_ERR_INTERNAL_ERROR"			,-15},
		{"WFS_ERR_INVALID_ADDRESS"			,-16},
		{"WFS_ERR_INVALID_APP_HANDLE"		,-17},
		{"WFS_ERR_INVALID_BUFFER"			,-18},
		{"WFS_ERR_INVALID_CATEGORY"			,-19},
		{"WFS_ERR_INVALID_COMMAND"			,-20},
		{"WFS_ERR_INVALID_EVENT_CLASS"		,-21},
		{"WFS_ERR_INVALID_HSERVICE"			,-22},
		{"WFS_ERR_INVALID_HPROVIDER"		,-23},
		{"WFS_ERR_INVALID_HWND"				,-24},
		{"WFS_ERR_INVALID_HWNDREG"			,-25},
		{"WFS_ERR_INVALID_POINTER"			,-26},
		{"WFS_ERR_INVALID_REQ_ID"			,-27},
		{"WFS_ERR_INVALID_RESULT"			,-28},
		{"WFS_ERR_INVALID_SERVPROV"			,-29},
		{"WFS_ERR_INVALID_TIMER"			,-30},
		{"WFS_ERR_INVALID_TRACELEVEL"		,-31},
		{"WFS_ERR_LOCKED"					,-32},
		{"WFS_ERR_NO_BLOCKING_CALL"			,-33},
		{"WFS_ERR_NO_SERVPROV"				,-34},
		{"WFS_ERR_NO_SUCH_THREAD"			,-35},
		{"WFS_ERR_NO_TIMER"					,-36},
		{"WFS_ERR_NOT_LOCKED"				,-37},
		{"WFS_ERR_NOT_OK_TO_UNLOAD"			,-38},
		{"WFS_ERR_NOT_STARTED"				,-39},
		{"WFS_ERR_NOT_REGISTERED"			,-40},
		{"WFS_ERR_OP_IN_PROGRESS"			,-41},
		{"WFS_ERR_OUT_OF_MEMORY"			,-42},
		{"WFS_ERR_SERVICE_NOT_FOUND"		,-43},
		{"WFS_ERR_SPI_VER_TOO_HIGH"			,-44},
		{"WFS_ERR_SPI_VER_TOO_LOW"			,-45},
		{"WFS_ERR_SRVC_VER_TOO_HIGH"		,-46},
		{"WFS_ERR_SRVC_VER_TOO_LOW"			,-47},
		{"WFS_ERR_TIMEOUT"					,-48},
		{"WFS_ERR_UNSUPP_CATEGORY"			,-49},
		{"WFS_ERR_UNSUPP_COMMAND"			,-50},
		{"WFS_ERR_VERSION_ERROR_IN_SRVC"	,-51},
		{"WFS_ERR_INVALID_DATA"				,-52},
		{"WFS_ERR_SOFTWARE_ERROR"			,-53},
		{"WFS_ERR_CONNECTION_LOST"			,-54},
		{"WFS_ERR_USER_ERROR"				,-55},
		{"WFS_ERR_UNSUPP_DATA"				,-56},
		{"WFS_ERR_TTU_FIELDERROR"              ,(-(TTU_SERVICE_OFFSET + 1))},
		{"WFS_ERR_TTU_FIELDINVALID"            ,(-(TTU_SERVICE_OFFSET + 2))},
		{"WFS_ERR_TTU_FIELDNOTFOUND"           ,(-(TTU_SERVICE_OFFSET + 3))},
		{"WFS_ERR_TTU_FIELDSPECFAILURE"        ,(-(TTU_SERVICE_OFFSET + 4))},
		{"WFS_ERR_TTU_FORMINVALID"             ,(-(TTU_SERVICE_OFFSET + 5))},
		{"WFS_ERR_TTU_FORMNOTFOUND"            ,(-(TTU_SERVICE_OFFSET + 6))},
		{"WFS_ERR_TTU_INVALIDLED"              ,(-(TTU_SERVICE_OFFSET + 7))},
		{"WFS_ERR_TTU_KEYCANCELED"             ,(-(TTU_SERVICE_OFFSET + 8))},
		{"WFS_ERR_TTU_MEDIAOVERFLOW"           ,(-(TTU_SERVICE_OFFSET + 9))},
		{"WFS_ERR_TTU_RESNOTSUPP"              ,(-(TTU_SERVICE_OFFSET + 10))},
		{"WFS_ERR_TTU_CHARSETDATA"             ,(-(TTU_SERVICE_OFFSET + 11))},
		{"WFS_ERR_TTU_KEYINVALID"              ,(-(TTU_SERVICE_OFFSET + 12))},
		{"WFS_ERR_TTU_KEYNOTSUPPORTED"         ,(-(TTU_SERVICE_OFFSET + 13))},
		{"WFS_ERR_TTU_NOACTIVEKEYS"            ,(-(TTU_SERVICE_OFFSET + 14))}
	};

	CString strRes="UNKNOWN ERROR";

	for (int i = 0; i < sizeof(XFSErr) / sizeof(XFSERR); i ++)
	{
		if( XFSErr[i].iErr==hResult )
		{
			strRes=XFSErr[i].strErr;
			break;
		}
	}
	return strRes;
}

CString CDCOperatorPanel_30::HandleEXEEvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%ld"
						"%s"
						"wfsresult.u.dweventid=%ld",
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.event_id);

	CString strEvtResult;
	switch (lpWfsRet->u.event_id)
	{
		case LFS_EXEE_TTU_FIELDERROR:
			break ;
		case LFS_EXEE_TTU_FIELDWARNING:
			break ;
		case LFS_EXEE_TTU_KEY:
		{
			LPLFSTTUKEY lpKey = (LPLFSTTUKEY)lpWfsRet->buffer;
			if (NULL != lpKey)
			{
				WCHAR wszKey[2] = {0};
				wszKey[0] = lpKey->unicode_key;

				// widechar 转 ascii
				char * _wszKey = NULL;
				size_t sSize = wcslen(wszKey);
				int dSize = wcstombs(_wszKey, wszKey, 0) + 1;
				_wszKey = new char[dSize];
				memset(_wszKey, 0, dSize);
				wcstombs(_wszKey, wszKey, dSize);

				strEvtResult = CString(1024, 0);
				sprintf((char *)strEvtResult.c_str(), "%s"
									"wfsresult.lpbuffer.ckey=%c"
									"%s"
									"wfsresult.lpbuffer.wunicodekey=%s"
									"%s"
									"wfsresult.lpbuffer.wcommandkey=%d",
									GetStringSplitChar(),
									(LFS_TTU_NOKEY != lpKey->key ? lpKey->key : 0x3F),  // 0x3F = "?"
									GetStringSplitChar(),
									(LFS_TTU_NOKEY != lpKey->unicode_key ? _wszKey : "?"),  // "?" = 0x3F
									GetStringSplitChar(),
									(LFS_TTU_NOKEY != lpKey->command_key ? lpKey->command_key : 0x3F));  // 0x3F = "?"

				delete[] _wszKey;
			}

			break;
		}
		default:
			break;
	}

	strWfsResult += strEvtResult;

	return strWfsResult;
}

CString CDCOperatorPanel_30::HandleSRVEvtResult(LPLFSRESULT lpWfsRet)
{
	/*
		OperatorPanel无WFS_SERVICE_EVENT
	*/

	if (NULL == lpWfsRet)
	{
		return "";
	}

	return "";
}

CString CDCOperatorPanel_30::HandleSysEvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%ld"
		"%s"
		"wfsresult.u.dweventid=%ld",
		lpWfsRet->result,
		GetStringSplitChar(),
		lpWfsRet->u.event_id);

	CString strSysEvent = "";

	switch (lpWfsRet->u.event_id)
	{
	case LFS_SYSE_DEVICE_STATUS:
	{
		LPLFSDEVSTATUS lpDevStatus = (LPLFSDEVSTATUS)lpWfsRet->buffer;
		if (NULL == lpDevStatus)
		{
			break;
		}

		strSysEvent = CString((NULL == lpDevStatus->physical_name ? 0 : strlen(lpDevStatus->physical_name))
			+ (NULL == lpDevStatus->workstation_name ? 0 : strlen(lpDevStatus->workstation_name)) + 1024, 0);
		sprintf((char *)strSysEvent.c_str(), "%s"
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
		break;
	}
	case LFS_SYSE_HARDWARE_ERROR:
	case LFS_SYSE_SOFTWARE_ERROR:
	case LFS_SYSE_USER_ERROR:
	{
		LPLFSHWERROR lpWfsHwError = (LPLFSHWERROR)lpWfsRet->buffer;
		if (NULL == lpWfsHwError)
		{
			break;
		}

		if (lpWfsHwError->size > 0 && NULL != lpWfsHwError->description)
		{
			strSysEvent = CString((NULL == lpWfsHwError->logical_name ? 0 : strlen(lpWfsHwError->logical_name))
				+ (NULL == lpWfsHwError->physical_name ? 0 : strlen(lpWfsHwError->physical_name))
				+ (NULL == lpWfsHwError->workstation_name ? 0 : strlen(lpWfsHwError->workstation_name))
				+ (NULL == lpWfsHwError->app_id ? 0 : strlen(lpWfsHwError->app_id))
				+ lpWfsHwError->size + 2048, 0);

			sprintf((char *)strSysEvent.c_str(), "%s"
				"wfsresult.lpbuffer.lpszlogicalname=%s"
				"%s"
				"wfsresult.lpbuffer.lpszphysicalname=%s"
				"%s"
				"wfsresult.lpbuffer.lpszworkstationname=%s"
				"%s"
				"wfsresult.lpbuffer.lpszappid=%s"
				"%s"
				"wfsresult.lpbuffer.dwaction=%ld"
				"%s"
				"wfsresult.lpbuffer.dwsize=%ld"
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
		break;
	}
	case LFS_SYSE_APP_DISCONNECT:
	{
		CloseDC();
		m_DCObject.m_bWosaXFSRun = FALSE;

		break;
	}
	default:
		break;
	}

	if ("" != strSysEvent)
	{
		strWfsResult = string(strWfsResult.c_str()) + strSysEvent;
	}

	return strWfsResult;
}

CString CDCOperatorPanel_30::HandleUSEREvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	return "";
}

CString CDCOperatorPanel_30::HandleCmdErr(LPLFSRESULT lpWfsRet)
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

CString CDCOperatorPanel_30::HandleCmdResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	if (LFS_SUCCESS != lpWfsRet->result)
	{
		return HandleCmdErr(lpWfsRet);
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%ld"
						"%s"
						"wfsresult.u.dwcommandcode=%ld",
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.command_code);
	
	CString strCmdResult = "";

	switch (lpWfsRet->u.command_code)
	{
		case LFS_CMD_TTU_BEEP:
		case LFS_CMD_TTU_CLEARSCREEN:
		case LFS_CMD_TTU_DISPLIGHT:
		case LFS_CMD_TTU_SET_LED:
		case LFS_CMD_TTU_SET_RESOLUTION:
		case LFS_CMD_TTU_WRITE_FORM:
			break ;
		case LFS_CMD_TTU_READ_FORM:
		{
			LPLFSTTUREADFORMOUT lpReadFormOut = (LPLFSTTUREADFORMOUT)lpWfsRet->buffer;
			if (NULL == lpReadFormOut)
			{
				break ;
			}

			LPSTR lpszFields = lpReadFormOut->fields;
			LPWSTR lpszUNICODEFields = lpReadFormOut->unicode_fields;

			CString strReadFormOut;
			if (NULL != lpszFields)
			{
				for (int nLoop = 0; ; nLoop ++)
				{
					if (NULL == lpszFields[nLoop])
					{
						if (NULL == lpszFields[nLoop + 1])
						{
							break ;
						}
						else
						{
							lpszFields[nLoop] = ',';
						}
					}

					strReadFormOut = CString(strlen(lpszFields) + 256, 0);
					sprintf((char *)strReadFormOut.c_str(), "%s"
											"wfsresult.lpbuffer.lpszfields=%s",
											GetStringSplitChar(),
											lpszFields);
					strCmdResult = CString(strCmdResult.c_str()) + strReadFormOut;
				}
			}
			
			if (NULL != lpszUNICODEFields)
			{
				for (int nLoop = 0; ; nLoop ++)
				{
					if (NULL == lpszUNICODEFields[nLoop])
					{
						if (NULL == lpszUNICODEFields[nLoop + 1])
						{
							break ;
						}
						else
						{
							lpszUNICODEFields[nLoop] = L',';
						}
					}

					// widechar 转 ascii
					char * _lpszUNICODEFields = NULL;
					size_t sSize = wcslen(lpszUNICODEFields);
					int dSize = wcstombs(_lpszUNICODEFields, lpszUNICODEFields, 0) + 1;
					_lpszUNICODEFields = new char[dSize];
					memset(_lpszUNICODEFields, 0, dSize);
					wcstombs(_lpszUNICODEFields, lpszUNICODEFields, dSize);

					strReadFormOut = CString(strlen(_lpszUNICODEFields) + 256, 0);
					sprintf((char *)strReadFormOut.c_str(), "%s"
											"wfsresult.lpbuffer.lpszunicodefields=%s",
											GetStringSplitChar(),
											_lpszUNICODEFields);
					strCmdResult = CString(strCmdResult.c_str()) + strReadFormOut;

					delete[] _lpszUNICODEFields;
				}
			}
			
			break ;
		}
		case LFS_CMD_TTU_WRITE:
			break ;
		case LFS_CMD_TTU_READ:
		{
			LPLFSTTUREADIN lpReadIn = (LPLFSTTUREADIN)lpWfsRet->buffer;
			if (NULL == lpReadIn)
			{
				break ;
			}

			LPSTR lpszInput = lpReadIn->input;
			LPWSTR lpszUNICODEInput = lpReadIn->unicode_input;

			CString strReadIn(256, 0);
			if (NULL != lpszInput)
			{
				sprintf((char *)strReadIn.c_str(), "%s"
									"wfsresult.lpbuffer.lpszinput=%s",
									GetStringSplitChar(),
									lpszInput);
				strCmdResult = CString(strCmdResult.c_str()) + strReadIn;
			}
			
			if (NULL != lpszUNICODEInput)
			{
				// widechar 转 ascii
				char * _lpszUNICODEInput = NULL;
				size_t sSize = wcslen(lpszUNICODEInput);
				int dSize = wcstombs(_lpszUNICODEInput, lpszUNICODEInput, 0) + 1;
				_lpszUNICODEInput = new char[dSize];
				memset(_lpszUNICODEInput, 0, dSize);
				wcstombs(_lpszUNICODEInput, lpszUNICODEInput, dSize);

				sprintf((char *)strReadIn.c_str(), "%s"
									"wfsresult.lpbuffer.lpszunicodeinput=%s",
									GetStringSplitChar(),
									_lpszUNICODEInput);
				strCmdResult = CString(strCmdResult.c_str()) + strReadIn;
			}
			
			break ;
		}
		case LFS_CMD_TTU_RESET:
			break ;
		default :
			break ;
	}

	strWfsResult = CString(strWfsResult.c_str()) + strCmdResult;

	return strWfsResult;
}

int CDCOperatorPanel_30::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (FALSE == m_DCObject.m_bWosaXFSRun)
	{
		return -1;
	}

    LPLFSRESULT lpWfsRet = NULL;

	CString strWfsResult = "";

	switch(uMsg)
    {
        case LFS_OPEN_COMPLETE:
            lpWfsRet=(LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);			
			break;
        case LFS_CLOSE_COMPLETE:
            lpWfsRet=(LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);			
			break;
        case LFS_LOCK_COMPLETE:
            lpWfsRet=(LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);			
			break;
        case LFS_UNLOCK_COMPLETE:
            lpWfsRet=(LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);			
			break;
        case LFS_REGISTER_COMPLETE:
            lpWfsRet=(LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);			
			break;
        case LFS_DEREGISTER_COMPLETE:
            lpWfsRet=(LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);			
			break;
        case LFS_GETINFO_COMPLETE:
            lpWfsRet = (LPLFSRESULT)lParam;
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
			break;
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
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s",
			uMsg, GetXFSMsgStr(uMsg).c_str(), strWfsResult.c_str());
		WriteTrace(m_strTraceComponent.c_str(), OCXEVENT, strTrace.c_str());

		FireDCEvent(m_strDCName, uMsg, strWfsResult);
	}

	return 0L;
}

HRESULT CDCOperatorPanel_30::CMD_TTU_BEEP(long lBeep) 
{
	HRESULT hResult = DC_ERROR;

	WORD wBeep = (WORD)lBeep;
	hResult = LFSAsyncExecute(m_DCObject.m_hService,
		LFS_CMD_TTU_BEEP,
		&wBeep,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCOperatorPanel_30::CMD_TTU_CLEARSCREEN(long lPositionX, long lPositionY, long lWidth, long lHeight) 
{
	return DC_ERROR;
}

HRESULT CDCOperatorPanel_30::CMD_TTU_DISPLIGHT(long lMode) 
{
	HRESULT hResult = DC_ERROR;

	LFSTTUDISPLIGHT DispLight = {0};
	DispLight.mode = (0 == lMode ? FALSE : TRUE);
	hResult = LFSAsyncExecute(m_DCObject.m_hService,
		LFS_CMD_TTU_DISPLIGHT,
		&DispLight,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCOperatorPanel_30::CMD_TTU_READ(	long lNumOfChars, 
													long lMode, 
													long lPosX, 
													long lPosY, 
													long lEchoMode, 
													long lEchoAttr, 
													long lCursor, 
													long lFlush, 
													long lAutoEnd, 
													LPCTSTR strActiveKeys, 
													LPCTSTR strActiveUNICODEKeys, 
													LPCTSTR strActiveCommandKeys, 
													LPCTSTR strTerminateCommandKeys) 
{
	
	HRESULT hResult = DC_ERROR;

	LFSTTUREAD Read = {0};
	Read.num_of_chars = (WORD)lNumOfChars;
    Read.mode = (WORD)lMode;
    Read.pos_x = (WORD)lPosX;
    Read.pos_y = (WORD)lPosY;
    Read.echo_mode = (WORD)lEchoMode;
    Read.echo_attr = (WORD)lEchoAttr;
    Read.cursor = (0 == lCursor ? FALSE : TRUE);
    Read.flush = (0 == lFlush ? FALSE : TRUE);
    Read.auto_end = (0 == lAutoEnd ? FALSE : TRUE);

	if (NULL != strActiveKeys && strlen(strActiveKeys) > 0)
	{
		Read.active_keys = (LPTSTR)strActiveKeys;
	}

	WCHAR wszActiveUNICODEKeys[256] = {0};
	if (NULL != strActiveUNICODEKeys && strlen(strActiveUNICODEKeys) > 0)
	{
		swprintf(wszActiveUNICODEKeys, 0, L"%s", strActiveUNICODEKeys);
		Read.active_unicode_keys = wszActiveUNICODEKeys;
	}

	CStringArray strarr;
	m_Utils.SplitString(strarr, (LPTSTR)strActiveCommandKeys, ",");

	LPTSTR lpszActiveCommandKeys = (LPTSTR)strActiveCommandKeys;
    WORD warrActiveCommandKeys[64] = {0};
	list<string>::iterator iter;
	int nLoop = 0;
	for (iter = strarr.begin(); iter != strarr.end(); iter++)
	{
		warrActiveCommandKeys[nLoop ++] = atoi((*iter).c_str());
	}
	warrActiveCommandKeys[nLoop] = 0;
	Read.active_command_keys = warrActiveCommandKeys;

	// strarr.RemoveAll();
	strarr.clear();
	m_Utils.SplitString(strarr, (LPTSTR)strTerminateCommandKeys, ",");

	LPCTSTR lpszTerminateCommandKeys = strTerminateCommandKeys;
    WORD warrTerminateCommandKeys[64] = {0};
	nLoop = 0;
	for (iter = strarr.begin(); iter != strarr.end(); iter++)
	{
		warrTerminateCommandKeys[nLoop++] = atoi((*iter).c_str());
	}
	warrTerminateCommandKeys[nLoop] = 0;
    Read.terminate_command_keys = warrTerminateCommandKeys;

	hResult = LFSAsyncExecute(m_DCObject.m_hService,
		LFS_CMD_TTU_READ,
		&Read,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCOperatorPanel_30::CMD_TTU_READ_FORM(LPCTSTR strFormName, LPCTSTR strFieldNames) 
{
	return DC_ERROR;
}

HRESULT CDCOperatorPanel_30::CMD_TTU_RESET() 
{
	CString strTrace(128, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_TTU_RESET()");
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());

	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(m_DCObject.m_hService,
		LFS_CMD_TTU_RESET,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCOperatorPanel_30::CMD_TTU_SET_LED(long lLED, long lCommand) 
{
	return DC_ERROR;
}

HRESULT CDCOperatorPanel_30::CMD_TTU_SET_RESOLUTION(long lSizeX, long lSizeY) 
{
	return DC_ERROR;
}

HRESULT CDCOperatorPanel_30::CMD_TTU_WRITE(long lMode, long lPosX, long lPosY, long lTextAttr, LPCTSTR strText, LPCTSTR strUNICODEText) 
{
	return DC_ERROR;
}

HRESULT CDCOperatorPanel_30::CMD_TTU_WRITE_FORM(LPCTSTR strFormName, long lClearScreen, LPCTSTR strFields, LPCTSTR strUNICODEFields) 
{
	return DC_ERROR;
}

HRESULT CDCOperatorPanel_30::INF_TTU_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_TTU_CAPABILITIES,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCOperatorPanel_30::INF_TTU_FORM_LIST() 
{
	return DC_ERROR;
}

HRESULT CDCOperatorPanel_30::INF_TTU_KEY_DETAIL() 
{
	return DC_ERROR;
}

HRESULT CDCOperatorPanel_30::INF_TTU_QUERY_FIELD(LPCTSTR strFormName, LPCTSTR strFieldName)
{
	return DC_ERROR;
}

HRESULT CDCOperatorPanel_30::INF_TTU_QUERY_FORM(LPCTSTR strFormName)
{
	return DC_ERROR;
}

CString CDCOperatorPanel_30::HandleInfResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strTrace;

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(),
		"wfsresult.hresult=%ld"
		"%s"
		"wfsresult.u.dwcommandcode=%ld"
		"%s",
		lpWfsRet->result,
		GetStringSplitChar(),
		lpWfsRet->u.command_code,
		GetStringSplitChar());

	if (LFS_SUCCESS != lpWfsRet->result)
	{
		return strWfsResult;
	}

	if (LFS_INF_TTU_STATUS == lpWfsRet->u.command_code)
	{
		LPLFSTTUSTATUS lpStatus = (LPLFSTTUSTATUS)lpWfsRet->buffer;
		if (NULL == lpStatus)
		{
			return strWfsResult;
		}

		/*
		CString strLeds(256, 0);
		CString strLed(1024, 0);
		for (int nLoop = 0; nLoop < LFS_TTU_LEDS_MAX; nLoop++)
		{
			sprintf((char *)strLed.c_str(), "%s"
				"wfsresult.lpbuffer.wleds[%d]=%d",
				GetStringSplitChar(),
				nLoop, lpStatus->leds[nLoop]);

			strLeds = string(strLeds.c_str()) + strLed;
		}
		strWfsResult = CString(strLeds.length() + 1024, 0);
		//*/

		strWfsResult = CString(2048, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.fwdevice=%d"
			"%s"
			"wfsresult.lpbuffer.wkeyboard=%d"
			"%s"
			"wfsresult.lpbuffer.wkeylock=%d"
			"%s"  // wfsresult.lpbuffer.wleds
			"%s"
			"wfsresult.lpbuffer.wdisplaysizex=%d"
			"%s"
			"wfsresult.lpbuffer.wdisplaysizey=%d"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_TTU_STATUS,
			GetStringSplitChar(),
			lpStatus->device,
			GetStringSplitChar(),
			lpStatus->keyboard,
			GetStringSplitChar(),
			lpStatus->key_lock,
			// strLeds,
			"",
			GetStringSplitChar(),
			lpStatus->display_size_x,
			GetStringSplitChar(),
			lpStatus->display_size_y,
			GetStringSplitChar(),
			(NULL == lpStatus->extra ? "NULL" : lpStatus->extra));
	}
	else if (LFS_INF_TTU_CAPABILITIES == lpWfsRet->u.command_code)
	{
		LPLFSTTUCAPS lpCaps = (LPLFSTTUCAPS)lpWfsRet->buffer;
		if (NULL == lpCaps)
		{
			return strWfsResult;
		}

		LPLFSTTURESOLUTION * lppResolutions = lpCaps->resolutions;
		if (NULL == lppResolutions)
		{
			return strWfsResult;
		}

		/*
		CString strResolutions(256, 0);
		CString strResolution(256, 0);
		for (int nLoop = 0; NULL != lppResolutions[nLoop]; nLoop++)
		{
			sprintf((char *)strResolution.c_str(), "%s"
				"wfsresult.lpbuffer.wsizex=%d"
				"%s"
				"wfsresult.lpbuffer.wsizey=%d",
				GetStringSplitChar(),
				lppResolutions[nLoop]->size_x,
				GetStringSplitChar(),
				lppResolutions[nLoop]->size_y);

			strResolutions = string(strResolutions.c_str()) + strResolution;
		}
		strWfsResult = CString(strResolutions.length() + 1024, 0);
		//*/

		strWfsResult = CString(2048, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.wclass=%d"
			"%s"
			"wfsresult.lpbuffer.fwtype=%d"
			"%s"  // "wfsresult.lpbuffer.lppresolutions=%d"
			"%s"
			"wfsresult.lpbuffer.wnumofleds=%d"
			"%s"
			"wfsresult.lpbuffer.bkeylock=%s"
			"%s"
			"wfsresult.lpbuffer.bdisplaylight=%s"
			"%s"
			"wfsresult.lpbuffer.bcursor=%s"
			"%s"
			"wfsresult.lpbuffer.bforms=%s"
			"%s"
			"wfsresult.lpbuffer.fwcharsupport=%d"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_TTU_CAPABILITIES,
			GetStringSplitChar(),
			lpCaps->dev_class,
			GetStringSplitChar(),
			lpCaps->dev_type,
			// strResolutions,
			"", 
			GetStringSplitChar(),
			lpCaps->num_of_leds,
			GetStringSplitChar(),
			lpCaps->key_lock ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->display_light ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->cursor ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->forms ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->char_support,
			GetStringSplitChar(),
			(NULL == lpCaps->extra ? "NULL" : lpCaps->extra));
	}

	return strWfsResult;
}

HRESULT CDCOperatorPanel_30::INF_TTU_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_TTU_STATUS,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}
