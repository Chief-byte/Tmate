// DCVendorMode_30.cpp: implementation of the CDCVendorMode_30 class.
//
//////////////////////////////////////////////////////////////////////

#include "DCVendorMode_30.h"
#include "../../../include/JavaScriptStringParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDCVendorMode_30::CDCVendorMode_30(LPCTSTR strDCName, LPCTSTR strTraceComponent)
{
	m_strDCName = strDCName;
	m_strTraceComponent = CString(strTraceComponent);
	m_DCObject.m_bWosaXFSRun = FALSE;
}

CDCVendorMode_30::~CDCVendorMode_30()
{

}

HRESULT CDCVendorMode_30::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// 调用命令
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_VDM_ENTER_MODE_REQ"))
	{
		bValid = TRUE;
		hResult = CMD_VDM_ENTER_MODE_REQ();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_VDM_ENTER_MODE_ACK"))
	{
		bValid = TRUE;
		hResult = CMD_VDM_ENTER_MODE_ACK();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_VDM_EXIT_MODE_REQ"))
	{
		bValid = TRUE;
		hResult = CMD_VDM_EXIT_MODE_REQ();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_VDM_EXIT_MODE_ACK"))
	{
		bValid = TRUE;
		hResult = CMD_VDM_EXIT_MODE_ACK();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_VDM_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_VDM_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_VDM_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_VDM_CAPABILITIES();
	}

	return hResult;
}

CString	CDCVendorMode_30::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[]={
		{"WFS_CMD_VDM_ENTER_MODE_REQ"             ,(VDM_SERVICE_OFFSET + 1)},
		{"WFS_CMD_VDM_ENTER_MODE_ACK"             ,(VDM_SERVICE_OFFSET + 2)},
		{"WFS_CMD_VDM_EXIT_MODE_REQ"              ,(VDM_SERVICE_OFFSET + 3)},
		{"WFS_CMD_VDM_EXIT_MODE_ACK"              ,(VDM_SERVICE_OFFSET + 4)},
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

CString	CDCVendorMode_30::GetXFSMsgStr(DWORD dwEventID)
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

		{"WFS_SRVE_VDM_ENTER_MODE_REQ"              ,(VDM_SERVICE_OFFSET + 1)},
		{"WFS_SRVE_VDM_EXIT_MODE_REQ"               ,(VDM_SERVICE_OFFSET + 2)},
		{"WFS_SYSE_VDM_MODEENTERED"                 ,(VDM_SERVICE_OFFSET + 3)},
		{"WFS_SYSE_VDM_MODEEXITED"                  ,(VDM_SERVICE_OFFSET + 3)}
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

CString	CDCVendorMode_30::GetXFSSysEvtStr(DWORD dwEventID)
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
		{"WFS_SYSE_LOCK_REQUESTED"                 ,8},
		{"WFS_SYSE_VDM_MODEENTERED"          ,(VDM_SERVICE_OFFSET + 3)},
		{"WFS_SYSE_VDM_MODEEXITED"           ,(VDM_SERVICE_OFFSET + 4)}
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

CString	CDCVendorMode_30::GetXFSErrStr(HRESULT hResult)
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
		{"WFS_ERR_UNSUPP_DATA"				,-56}
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

int CDCVendorMode_30::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			printf("LFS_OPEN_COMPLETE CDCVendorMode_30\n");
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
			if (NULL != lpWfsRet)
			{
				strWfsResult = HandleCmdResult(lpWfsRet);
			}

			LFSFreeResult(lpWfsRet);
			break;
		case LFS_EXECUTE_EVENT:
			lpWfsRet = (LPLFSRESULT)lParam;
			if (NULL != lpWfsRet)
			{
				strWfsResult = HandleEXEEvtResult(lpWfsRet);
			}

			LFSFreeResult(lpWfsRet);
			break;
		case LFS_SERVICE_EVENT:
			lpWfsRet = (LPLFSRESULT)lParam;
			if (NULL != lpWfsRet)
			{
				strWfsResult = HandleSRVEvtResult(lpWfsRet);
			}

			LFSFreeResult(lpWfsRet);
			break;
		case LFS_USER_EVENT:
			lpWfsRet = (LPLFSRESULT)lParam;
			if (NULL != lpWfsRet)
			{
				strWfsResult = HandleUSEREvtResult(lpWfsRet);
			}

			LFSFreeResult(lpWfsRet);
			break;
		case LFS_SYSTEM_EVENT:
			lpWfsRet = (LPLFSRESULT)lParam;
			if (NULL != lpWfsRet)
			{
				strWfsResult = HandleSysEvtResult(lpWfsRet);
			}

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

CString CDCVendorMode_30::HandleCmdErr(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), 
						"wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dwcommandcode=%d",
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.command_code);
	return strWfsResult;
}

CString CDCVendorMode_30::HandleCmdResult(LPLFSRESULT lpWfsRet)
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
	case LFS_CMD_VDM_ENTER_MODE_REQ:
	case LFS_CMD_VDM_ENTER_MODE_ACK:
	case LFS_CMD_VDM_EXIT_MODE_REQ:
	case LFS_CMD_VDM_EXIT_MODE_ACK:
	default:
		break;
	}

	if ("" != strCmdResult)
	{
		strWfsResult = string(strWfsResult.c_str()) + strCmdResult;
	}

	return strWfsResult;
}

CString CDCVendorMode_30::HandleEXEEvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(),
		"wfsresult.hresult=%d"
		"%s"
		"wfsresult.u.dweventid=%d",
		lpWfsRet->result,
		GetStringSplitChar(),
		lpWfsRet->u.event_id);

	return strWfsResult;
}

CString CDCVendorMode_30::HandleSRVEvtResult(LPLFSRESULT lpWfsRet)
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
		case LFS_SRVE_VDM_ENTER_MODE_REQ:
		case LFS_SRVE_VDM_EXIT_MODE_REQ:
		default :
			break ;
	}

	if ("" != strEvtResult)
	{
		strWfsResult = string(strWfsResult.c_str()) + strEvtResult;
	}

	return strWfsResult;
}

CString CDCVendorMode_30::HandleSysEvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(),
		"wfsresult.hresult=%d"
		"%s"
		"wfsresult.u.dweventid=%d",
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

CString CDCVendorMode_30::HandleUSEREvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(),
		"wfsresult.hresult=%d"
		"%s"
		"wfsresult.u.dweventid=%d",
		lpWfsRet->result,
		GetStringSplitChar(),
		lpWfsRet->u.event_id);

	return strWfsResult;
}

HRESULT CDCVendorMode_30::INF_VDM_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_VDM_CAPABILITIES,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCVendorMode_30::INF_VDM_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_VDM_STATUS,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

CString CDCVendorMode_30::HandleInfResult(LPLFSRESULT lpWfsRet)
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
	if (LFS_INF_VDM_STATUS == lpWfsRet->u.command_code)
	{
		LPLFSVDMSTATUS lpStatus = (LPLFSVDMSTATUS)lpWfsRet->buffer;
		if (NULL == lpStatus)
		{
			return strWfsResult;
		}

		LPLFSVDMAPPSTATUS * lppAppStatus = (LPLFSVDMAPPSTATUS *)lpStatus->lppAppStatus;

		CString strAppStatuses = "";

		if (NULL != lppAppStatus)
		{
			for (int nLoop = 0; NULL != lppAppStatus[nLoop]; nLoop++)
			{
				CString strAppStatus((NULL == lppAppStatus[nLoop]->lpszAppID ? 0 : strlen(lppAppStatus[nLoop]->lpszAppID)) + 1024, 0);
				sprintf((char *)strAppStatus.c_str(), "%s"
					"wfsresult.lpbuffer.lppappstatus[%d].lpszappid=%s"
					"%s"
					"wfsresult.lpbuffer.lppappstatus[%d].wappstatus=%ld",
					GetStringSplitChar(),
					nLoop, (NULL == lppAppStatus[nLoop]->lpszAppID ? "NULL" : lppAppStatus[nLoop]->lpszAppID),
					GetStringSplitChar(),
					nLoop, lppAppStatus[nLoop]->wAppStatus);

				strAppStatuses += strAppStatus;
			}
		}

		strWfsResult = string(strAppStatuses.length() + (NULL == lpStatus->lpszExtra ? 0 : strlen(lpStatus->lpszExtra)) + 1024, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.wdevice=%d"
			"%s"
			"wfsresult.lpbuffer.wservice=%d"
			"%s"  // "wfsresult.lpbuffer.lppappstatus=%d"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_VDM_STATUS,
			GetStringSplitChar(),
			lpStatus->wDevice,
			GetStringSplitChar(),
			lpStatus->wService,
			strAppStatuses.c_str(),
			GetStringSplitChar(),
			(NULL == lpStatus->lpszExtra ? "NULL" : FormatExtra(lpStatus->lpszExtra)));
	}
	else if (LFS_INF_VDM_CAPABILITIES == lpWfsRet->u.command_code)
	{
		LPLFSVDMCAPS lpCaps = (LPLFSVDMCAPS)lpWfsRet->buffer;
		if (NULL == lpCaps)
		{
			return strWfsResult;
		}

		strWfsResult = string((NULL == lpCaps->lpszExtra ? 0 : strlen(lpCaps->lpszExtra)) + 1024, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.wclass=%d"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_VDM_CAPABILITIES,
			GetStringSplitChar(),
			lpCaps->wClass,
			GetStringSplitChar(),
			(NULL == lpCaps->lpszExtra ? "NULL" : FormatExtra(lpCaps->lpszExtra)));
	}

	return strWfsResult;
}

HRESULT CDCVendorMode_30::CMD_VDM_ENTER_MODE_REQ()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(m_DCObject.m_hService,
								LFS_CMD_VDM_ENTER_MODE_REQ,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCVendorMode_30::CMD_VDM_EXIT_MODE_REQ()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(m_DCObject.m_hService,
								LFS_CMD_VDM_EXIT_MODE_REQ,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCVendorMode_30::CMD_VDM_ENTER_MODE_ACK()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(m_DCObject.m_hService,
								LFS_CMD_VDM_ENTER_MODE_ACK,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCVendorMode_30::CMD_VDM_EXIT_MODE_ACK()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(m_DCObject.m_hService,
								LFS_CMD_VDM_EXIT_MODE_ACK,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}
