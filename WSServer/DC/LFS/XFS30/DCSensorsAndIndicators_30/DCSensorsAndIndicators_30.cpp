// DCSensorsAndIndicators_30.cpp: implementation of the CDCSensorsAndIndicators_30 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCSensorsAndIndicators_30.h"
#include "../../../include/JavaScriptStringParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDCSensorsAndIndicators_30::CDCSensorsAndIndicators_30(LPCTSTR strDCName, LPCTSTR strTraceComponent)
{
	m_strDCName = strDCName;
	m_strTraceComponent = CString(strTraceComponent);
	m_DCObject.m_bWosaXFSRun = FALSE;
}

CDCSensorsAndIndicators_30::~CDCSensorsAndIndicators_30()
{
}

HRESULT CDCSensorsAndIndicators_30::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// 调用命令
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_SIU_ENABLE_EVENTS"))
	{
		bValid = TRUE;
		hResult = CMD_SIU_ENABLE_EVENTS(strSingleParam.c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_SIU_SET_PORTS"))
	{
		bValid = TRUE;
		hResult = CMD_SIU_SET_PORTS(strSingleParam.c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_SIU_SET_DOOR"))
	{
		bValid = TRUE;
		hResult = CMD_SIU_SET_DOOR(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "wdoor").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwcommand").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_SIU_SET_INDICATOR"))
	{
		bValid = TRUE;
		hResult = CMD_SIU_SET_INDICATOR((short)atol(CJSStringParam::GetStringParam(strarrParams, "windicator").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwcommand").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_SIU_SET_AUXILIARY"))
	{
		bValid = TRUE;
		hResult = CMD_SIU_SET_AUXILIARY((short)atol(CJSStringParam::GetStringParam(strarrParams, "wauxiliary").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwcommand").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_SIU_SET_GUIDLIGHT"))
	{
		bValid = TRUE;
		hResult = CMD_SIU_SET_GUIDLIGHT((short)atol(CJSStringParam::GetStringParam(strarrParams, "wguidlight").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwcommand").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_SIU_RESET"))
	{
		bValid = TRUE;
		hResult = CMD_SIU_RESET();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_SIU_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_SIU_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_SIU_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_SIU_CAPABILITIES();
	}

	return hResult;
}

CString	CDCSensorsAndIndicators_30::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[]={
		{"WFS_CMD_SIU_ENABLE_EVENTS"           ,(SIU_SERVICE_OFFSET + 1)},
		{"WFS_CMD_SIU_SET_PORTS"               ,(SIU_SERVICE_OFFSET + 2)},
		{"WFS_CMD_SIU_SET_DOOR"                ,(SIU_SERVICE_OFFSET + 3)},
		{"WFS_CMD_SIU_SET_INDICATOR"           ,(SIU_SERVICE_OFFSET + 4)},
		{"WFS_CMD_SIU_SET_AUXILIARY"           ,(SIU_SERVICE_OFFSET + 5)},
		{"WFS_CMD_SIU_SET_GUIDLIGHT"           ,(SIU_SERVICE_OFFSET + 6)},
		{"WFS_CMD_SIU_RESET"                   ,(SIU_SERVICE_OFFSET + 7)}
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

CString	CDCSensorsAndIndicators_30::GetXFSMsgStr(DWORD dwEventID)
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

		{"WFS_SRVE_SIU_PORT_STATUS"            ,(SIU_SERVICE_OFFSET + 1)},
		{"WFS_EXEE_SIU_PORT_ERROR"             ,(SIU_SERVICE_OFFSET + 2)}
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

CString	CDCSensorsAndIndicators_30::GetXFSSysEvtStr(DWORD dwEventID)
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

CString	CDCSensorsAndIndicators_30::GetXFSErrStr(HRESULT hResult)
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
		{"WFS_ERR_SIU_INVALID_PORT"         ,(-(SIU_SERVICE_OFFSET + 1))},
		{"WFS_ERR_SIU_SYNTAX"               ,(-(SIU_SERVICE_OFFSET + 2))},
		{"WFS_ERR_SIU_PORT_ERROR"           ,(-(SIU_SERVICE_OFFSET + 3))}
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

CString CDCSensorsAndIndicators_30::HandleEXEEvtResult(LPLFSRESULT lpWfsRet)
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

	CString strEvtResult;
	switch (lpWfsRet->u.event_id)
	{
		case LFS_EXEE_SIU_PORT_ERROR:
			break;
		default:
			break;
	}

	strWfsResult = string(strWfsResult.c_str()) + strEvtResult;

	return strWfsResult;
}

CString CDCSensorsAndIndicators_30::HandleSRVEvtResult(LPLFSRESULT lpWfsRet)
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

	CString strEvtResult = "";
	switch (lpWfsRet->u.event_id)
	{
		case LFS_SRVE_SIU_PORT_STATUS:
		{
			CString strResult;
			LPLFSSIUPORTEVENT lpPortEvent = (LPLFSSIUPORTEVENT)lpWfsRet->buffer;
			if (NULL == lpPortEvent)
			{
				break ;
			}

			strEvtResult = CString((NULL == lpPortEvent->extra ? 0 : strlen(lpPortEvent->extra)) + 1024, 0);
			sprintf((char *)strEvtResult.c_str(), "%s"
								"wfsresult.lpbuffer.wporttype=%d"
								"%s"
								"wfsresult.lpbuffer.wportindex=%d"
								"%s"
								"wfsresult.lpbuffer.wportstatus=%d"
								"%s"
								"wfsresult.lpbuffer.lpszextra=%s",
								GetStringSplitChar(),
								lpPortEvent->port_type,
								GetStringSplitChar(),
								lpPortEvent->port_index,
								GetStringSplitChar(),
								lpPortEvent->port_status,
								GetStringSplitChar(),
								(NULL == lpPortEvent->extra ? "NULL" : lpPortEvent->extra));

			break ;
		}
		default :
			break ;
	}

	if ("" != strEvtResult)
	{
		strWfsResult = string(strWfsResult.c_str()) + strEvtResult;
	}

	return strWfsResult;
}

CString CDCSensorsAndIndicators_30::HandleSysEvtResult(LPLFSRESULT lpWfsRet)
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
								"wfsresult.lpbuffer.dwstate=%d",
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

CString CDCSensorsAndIndicators_30::HandleCmdErr(LPLFSRESULT lpWfsRet)
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

CString CDCSensorsAndIndicators_30::HandleCmdResult(LPLFSRESULT lpWfsRet)
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
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dwcommandcode=%d",
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.command_code);
	
	CString strCmdResult = "";

	switch (lpWfsRet->u.command_code)
	{
		case LFS_CMD_SIU_ENABLE_EVENTS:
		case LFS_CMD_SIU_SET_PORTS:
		case LFS_CMD_SIU_SET_DOOR:
		case LFS_CMD_SIU_SET_INDICATOR:
		case LFS_CMD_SIU_SET_AUXILIARY:
		case LFS_CMD_SIU_SET_GUIDLIGHT:
		case LFS_CMD_SIU_RESET:
		default :
			break ;
	}

	strWfsResult = string(strWfsResult.c_str()) + strCmdResult;

	return strWfsResult;
}

CString CDCSensorsAndIndicators_30::HandleUSEREvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	return "";
}

int CDCSensorsAndIndicators_30::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
            lpWfsRet=(LPLFSRESULT)lParam;
			LFSFreeResult(lpWfsRet);
			WriteTrace(m_strTraceComponent.c_str(), OCXEVENT, "LFS_OPEN_COMPLETE");
			printf("LFS_OPEN_COMPLETE CDCSensorsAndIndicators_30\n");
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

HRESULT CDCSensorsAndIndicators_30::INF_SIU_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_SIU_STATUS,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

CString CDCSensorsAndIndicators_30::HandleInfResult(LPLFSRESULT lpWfsRet)
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

	if (LFS_INF_SIU_STATUS == lpWfsRet->u.command_code)
	{
		LPLFSSIUSTATUS lpStatus = (LPLFSSIUSTATUS)lpWfsRet->buffer;
		if (NULL == lpStatus)
		{
			return strWfsResult;
		}

		int nLoop = 0;
		CString strSensors = "";
		for (nLoop = 0; nLoop <= LFS_SIU_ENHANCEDAUDIO; nLoop ++)  // 不需要取整个数组的大小LFS_SIU_SENSORS_SIZE(32)
		{
			CString strSensor(256, 0);
			sprintf((char *)strSensor.c_str(), "%s"
							"wfsresult.lpbuffer.fwsensors[%d]=%d", 
							GetStringSplitChar(),
							nLoop, lpStatus->sensors[nLoop]);

			strSensors = string(strSensors.c_str()) + strSensor;
		}

		// #define     LFS_SIU_CABINET                     (0)
		// #define     LFS_SIU_SAFE                        (1)
		// #define     LFS_SIU_VANDALSHIELD                (2)
		CString strDoors = "";
		for (nLoop = 0; nLoop <= LFS_SIU_VANDALSHIELD; nLoop ++)  // 不需要取整个数组的大小LFS_SIU_DOORS_SIZE(16)
		{
			CString strDoor(256, 0);
			sprintf((char *)strDoor.c_str(), "%s"
							"wfsresult.lpbuffer.fwdoors[%d]=%d", 
							GetStringSplitChar(),
							nLoop, lpStatus->doors[nLoop]);

			strDoors = string(strDoors.c_str()) + strDoor;
		}

		CString strSensorsAndIndicators = "";
		for (nLoop = 0; nLoop <= LFS_SIU_HEATING; nLoop ++)  // 不需要取整个数组的大小LFS_SIU_INDICATORS_SIZE(16)
		{
			CString strIndicator(256, 0);
			sprintf((char *)strIndicator.c_str(), "%s"
								"wfsresult.lpbuffer.fwindicators[%d]=%d", 
								GetStringSplitChar(),
								nLoop, lpStatus->indicators[nLoop]);

			strSensorsAndIndicators = string(strSensorsAndIndicators.c_str()) + strIndicator;
		}

		CString strAuxiliaries = "";
		for (nLoop = 0; nLoop <= LFS_SIU_HEATING; nLoop ++)  // 不需要取整个数组的大小LFS_SIU_AUXILIARIES_SIZE(16)
		{
			CString strAuxiliarie(256, 0);
			sprintf((char *)strAuxiliarie.c_str(), "%s"
								"wfsresult.lpbuffer.fwauxiliaries[%d]=%d", 
								GetStringSplitChar(),
								nLoop, lpStatus->auxiliaries[nLoop]);

			strAuxiliaries = string(strAuxiliaries.c_str()) + strAuxiliarie;
		}

		CString strGuidLights = "";
		for (nLoop = 0; nLoop <= LFS_SIU_SCANNER; nLoop ++)  // 不需要取整个数组的大小LFS_SIU_GUIDLIGHTS_SIZE(16)
		{
			CString strGuidLight(256, 0);
			sprintf((char *)strGuidLight.c_str(), "%s"
								"wfsresult.lpbuffer.fwguidlights[%d]=%d", 
								GetStringSplitChar(),
								nLoop, lpStatus->guid_lights[nLoop]);

			strGuidLights = string(strGuidLights.c_str()) + strGuidLight;
		}

		strWfsResult = CString(strSensors.length() + strDoors.length() + strSensorsAndIndicators.length() + strAuxiliaries.length() + strGuidLights.length()
								+ (NULL == lpStatus->extra ? 0 : strlen(lpStatus->extra)) + 1024, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
							"%s"
							"wfsresult.lpbuffer.fwdevice=%d"
							"%s"
							"%s"
							"%s"
							"%s"
							"%s"
							"%s"
							"wfsresult.lpbuffer.lpszextra=%s",
							LFS_INF_SIU_STATUS,
							GetStringSplitChar(),
							lpStatus->device, 
							strSensors.c_str(),
							strDoors.c_str(),
							strSensorsAndIndicators.c_str(),
							strAuxiliaries.c_str(),
							strGuidLights.c_str(),
							GetStringSplitChar(),
							(NULL == lpStatus->extra ? "NULL" : lpStatus->extra));
	}
	else if (LFS_INF_SIU_CAPABILITIES == lpWfsRet->u.command_code)
	{
		LPLFSSIUCAPS lpCaps = (LPLFSSIUCAPS)lpWfsRet->buffer;
		if (NULL == lpCaps)
		{
			return strWfsResult;
		}

		int nLoop = 0;
		CString strSensors = "";
		for (nLoop = 0; nLoop <= LFS_SIU_ENHANCEDAUDIO; nLoop++)  // 不需要取整个数组的大小LFS_SIU_SENSORS_SIZE(32)
		{
			CString strSensor(256, 0);
			sprintf((char *)strSensor.c_str(), "%s"
				"wfsresult.lpbuffer.fwsensors[%d]=%d",
				GetStringSplitChar(),
				nLoop, lpCaps->sensors[nLoop]);

			strSensors = string(strSensors.c_str()) + strSensor;
		}

		CString strDoors = "";
		for (nLoop = 0; nLoop <= LFS_SIU_VANDALSHIELD; nLoop++)  // 不需要取整个数组的大小LFS_SIU_DOORS_SIZE(16)
		{
			CString strDoor(256, 0);
			sprintf((char *)strDoor.c_str(), "%s"
				"wfsresult.lpbuffer.fwdoors[%d]=%d",
				GetStringSplitChar(),
				nLoop, lpCaps->doors[nLoop]);

			strDoors = string(strDoors.c_str()) + strDoor;
		}

		CString strSensorsAndIndicators = "";
		for (nLoop = 0; nLoop <= LFS_SIU_HEATING; nLoop++)  // 不需要取整个数组的大小LFS_SIU_INDICATORS_SIZE(16)
		{
			CString strIndicator(256, 0);
			sprintf((char *)strIndicator.c_str(), "%s"
				"wfsresult.lpbuffer.fwindicators[%d]=%d",
				GetStringSplitChar(),
				nLoop, lpCaps->indicators[nLoop]);

			strSensorsAndIndicators = string(strSensorsAndIndicators.c_str()) + strIndicator;
		}

		CString strAuxiliaries = "";
		for (nLoop = 0; nLoop <= LFS_SIU_HEATING; nLoop++)  // 不需要取整个数组的大小LFS_SIU_AUXILIARIES_SIZE(16)
		{
			CString strAuxiliarie(256, 0);
			sprintf((char *)strAuxiliarie.c_str(), "%s"
				"wfsresult.lpbuffer.fwauxiliaries[%d]=%d",
				GetStringSplitChar(),
				nLoop, lpCaps->auxiliaries[nLoop]);

			strAuxiliaries = string(strAuxiliaries.c_str()) + strAuxiliarie;
		}

		CString strGuidLights = "";
		for (nLoop = 0; nLoop <= LFS_SIU_SCANNER; nLoop++)  // 不需要取整个数组的大小LFS_SIU_GUIDLIGHTS_SIZE(16)
		{
			CString strGuidLight(256, 0);
			sprintf((char *)strGuidLight.c_str(), "%s"
				"wfsresult.lpbuffer.fwguidlights[%d]=%d",
				GetStringSplitChar(),
				nLoop, lpCaps->guid_lights[nLoop]);

			strGuidLights = string(strGuidLights.c_str()) + strGuidLight;
		}

		strWfsResult = CString(strSensors.length() + strDoors.length() + strSensorsAndIndicators.length() + strAuxiliaries.length() + strGuidLights.length()
			+ (NULL == lpCaps->extra ? 0 : strlen(lpCaps->extra)) + 1024, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.wclass=%d"
			"%s"
			"wfsresult.lpbuffer.fwtype=%d"
			"%s"
			"%s"
			"%s"
			"%s"
			"%s"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_SIU_CAPABILITIES,
			GetStringSplitChar(),
			lpCaps->dev_class,
			GetStringSplitChar(),
			lpCaps->dev_type,
			strSensors.c_str(),
			strDoors.c_str(),
			strSensorsAndIndicators.c_str(),
			strAuxiliaries.c_str(),
			strGuidLights.c_str(),
			GetStringSplitChar(),
			(NULL == lpCaps->extra ? "NULL" : lpCaps->extra));
	}

	return strWfsResult;
}

HRESULT CDCSensorsAndIndicators_30::INF_SIU_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	CString strWfsResult = "";

	LPLFSRESULT lpWfsRet = NULL;
	hResult = LFSGetInfo(	m_DCObject.m_hService, 
							LFS_INF_SIU_CAPABILITIES, 
							NULL, 
							LFS_INDEFINITE_WAIT, 
							&lpWfsRet);

	return hResult;
}

HRESULT CDCSensorsAndIndicators_30::CMD_SIU_ENABLE_EVENTS(LPCTSTR strEnable) 
{
	HRESULT hResult = DC_ERROR;

	LFSSIUENABLE Enable = {0};

	CStringArray strarrParams;
	CString strParamKey;
	CString strParamValue;
	if (FALSE == CJSStringParam::GetStringParams(strEnable, GetStringSplitChar(), strarrParams) || TRUE == strarrParams.empty())
	{
		return hResult;
	}

	for (int nLoop = 0; nLoop < LFS_SIU_SENSORS_SIZE; nLoop ++)
	{
		strParamKey = CString(256, 0);
		sprintf((char *)strParamKey.c_str(), "enable.fwsensors[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			Enable.sensors[nLoop] = LFS_SIU_NO_CHANGE;
		}
		else
		{
			Enable.sensors[nLoop] = atoi(strParamValue.c_str());
		}
	}

	for (int nLoop = 0; nLoop < LFS_SIU_DOORS_SIZE; nLoop ++)
	{
		strParamKey = CString(256, 0);
		sprintf((char *)strParamKey.c_str(), "enable.fwdoors[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			Enable.doors[nLoop] = LFS_SIU_NO_CHANGE;
		}
		else
		{
			Enable.doors[nLoop] = atoi(strParamValue.c_str());
		}
	}

	for (int nLoop = 0; nLoop < LFS_SIU_INDICATORS_SIZE; nLoop ++)
	{
		strParamKey = CString(256, 0);
		sprintf((char *)strParamKey.c_str(), "enable.fwindicators[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			Enable.indicators[nLoop] = LFS_SIU_NO_CHANGE;
		}
		else
		{
			Enable.indicators[nLoop] = atoi(strParamValue.c_str());
		}
	}

	for (int nLoop = 0; nLoop < LFS_SIU_AUXILIARIES_SIZE; nLoop ++)
	{
		strParamKey = CString(256, 0);
		sprintf((char *)strParamKey.c_str(), "enable.fwauxiliaries[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			Enable.auxiliaries[nLoop] = LFS_SIU_NO_CHANGE;
		}
		else
		{
			Enable.auxiliaries[nLoop] = atoi(strParamValue.c_str());
		}
	}

	for (int nLoop = 0; nLoop < LFS_SIU_GUIDLIGHTS_SIZE; nLoop ++)
	{
		strParamKey = CString(256, 0);
		sprintf((char *)strParamKey.c_str(), "enable.fwguidlights[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			Enable.guid_lights[nLoop] = LFS_SIU_NO_CHANGE;
		}
		else
		{
			Enable.guid_lights[nLoop] = atoi(strParamValue.c_str());
		}
	}

	strParamKey = CString(256, 0);
	sprintf((char *)strParamKey.c_str(), "enable.lpszextra[%d]", 0);
	if (TRUE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
	{
		Enable.extra = (LPTSTR)(LPCTSTR)strParamValue.c_str();
	}

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_SIU_ENABLE_EVENTS,
								&Enable,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCSensorsAndIndicators_30::CMD_SIU_RESET() 
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_SIU_RESET,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCSensorsAndIndicators_30::CMD_SIU_SET_AUXILIARY(long lAuxiliary, long lCommand) 
{
	HRESULT hResult = DC_ERROR;

	LFSSIUSETAUXILIARY SetAuxiliary = {0};
	SetAuxiliary.auxiliary = (WORD)lAuxiliary;
	SetAuxiliary.command = (WORD)lCommand;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_SIU_SET_AUXILIARY,
								&SetAuxiliary,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCSensorsAndIndicators_30::CMD_SIU_SET_DOOR(long lDoor, long lCommand) 
{
	HRESULT hResult = DC_ERROR;

	LFSSIUSETDOOR SetDoor = {0};
	SetDoor.door = (WORD)lDoor;
	SetDoor.command = (WORD)lCommand;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_SIU_SET_DOOR,
								&SetDoor,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCSensorsAndIndicators_30::CMD_SIU_SET_GUIDLIGHT(long lGuidLight, long lCommand) 
{
	HRESULT hResult = DC_ERROR;

	LFSSIUSETGUIDLIGHT SetGuidLight = {0};
	SetGuidLight.guid_light = (WORD)lGuidLight;
	SetGuidLight.command = (WORD)lCommand;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_SIU_SET_GUIDLIGHT,
								&SetGuidLight,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCSensorsAndIndicators_30::CMD_SIU_SET_INDICATOR(long lIndicator, long lCommand) 
{
	HRESULT hResult = DC_ERROR;

	LFSSIUSETINDICATOR SetIndicator = {0};
	SetIndicator.indicator = (WORD)lIndicator;
	SetIndicator.command = (WORD)lCommand;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_SIU_SET_INDICATOR,
								&SetIndicator,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCSensorsAndIndicators_30::CMD_SIU_SET_PORTS(LPCTSTR strSetPorts) 
{
	HRESULT hResult = DC_ERROR;

	LFSSIUSETPORTS SetPorts = {0};

	CStringArray strarrParams;
	CString strParamKey;
	CString strParamValue;
	if (FALSE == CJSStringParam::GetStringParams(strSetPorts, GetStringSplitChar(), strarrParams) || TRUE == strarrParams.empty())
	{
		return hResult;
	}

	for (int nLoop = 0; nLoop < LFS_SIU_DOORS_SIZE; nLoop ++)
	{
		strParamKey = CString(256, 0);
		sprintf((char *)strParamKey.c_str(), "setports.fwdoors[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			SetPorts.doors[nLoop] = LFS_SIU_NO_CHANGE;
		}
		else
		{
			SetPorts.doors[nLoop] = atoi(strParamValue.c_str());
		}
	}

	for (int nLoop = 0; nLoop < LFS_SIU_INDICATORS_SIZE; nLoop ++)
	{
		strParamKey = CString(256, 0);
		sprintf((char *)strParamKey.c_str(), "setports.fwindicators[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			SetPorts.indicators[nLoop] = LFS_SIU_NO_CHANGE;
		}
		else
		{
			SetPorts.indicators[nLoop] = atoi(strParamValue.c_str());
		}
	}

	for (int nLoop = 0; nLoop < LFS_SIU_AUXILIARIES_SIZE; nLoop ++)
	{
		strParamKey = CString(256, 0);
		sprintf((char *)strParamKey.c_str(), "setports.fwauxiliaries[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			SetPorts.auxiliaries[nLoop] = LFS_SIU_NO_CHANGE;
		}
		else
		{
			SetPorts.auxiliaries[nLoop] = atoi(strParamValue.c_str());
		}
	}

	for (int nLoop = 0; nLoop < LFS_SIU_GUIDLIGHTS_SIZE; nLoop ++)
	{
		strParamKey = CString(256, 0);
		sprintf((char *)strParamKey.c_str(), "setports.fwguidlights[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			SetPorts.guid_lights[nLoop] = LFS_SIU_NO_CHANGE;
		}
		else
		{
			SetPorts.guid_lights[nLoop] = atoi(strParamValue.c_str());
		}
	}

	strParamKey = CString(256, 0);
	sprintf((char *)strParamKey.c_str(), "setports.lpszextra[%d]", 0);
	if (TRUE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
	{
		SetPorts.extra = (char *)strParamValue.c_str();
	}

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_SIU_SET_PORTS,
								&SetPorts,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}
