// DCBarcode_31.cpp: implementation of the CDCBarcode_31 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCBarcode_31.h"
#include "../../include/JavaScriptStringParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDCBarcode_31::CDCBarcode_31(LPCTSTR strDCName)
{
	m_strDCName = strDCName;
	m_DCObject.m_bWosaXFSRun = FALSE;
}

CDCBarcode_31::~CDCBarcode_31()
{

}

HRESULT CDCBarcode_31::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// 调用命令
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_BCR_READ"))
	{
		bValid = TRUE;
		hResult = CMD_BCR_READ(CJSStringParam::GetStringParam(strarrParams, "lpwsymbologies").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_BCR_RESET"))
	{
		bValid = TRUE;
		hResult = CMD_BCR_RESET();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_BCR_SET_GUIDANCE_LIGHT"))
	{
		bValid = TRUE;
		hResult = CMD_BCR_SET_GUIDANCE_LIGHT(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "wguidlight").c_str()), 
												(short)atol(CJSStringParam::GetStringParam(strarrParams, "dwcommand").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_BCR_POWER_SAVE_CONTROL"))
	{
		bValid = TRUE;
		hResult = CMD_BCR_POWER_SAVE_CONTROL((short)atol(CJSStringParam::GetStringParam(strarrParams, "usmaxpowersaverecoverytime").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_INF_BCR_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_BCR_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_BCR_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_BCR_CAPABILITIES();
	}

	return hResult;
}

HRESULT CDCBarcode_31::CMD_BCR_POWER_SAVE_CONTROL(long lMaxPowerSaveRecoveryTime)
{
	HRESULT hResult = DC_ERROR;

	WFSBCRPOWERSAVECONTROL BcrPowerSaveControl = {0};
	BcrPowerSaveControl.usMaxPowerSaveRecoveryTime = (USHORT)lMaxPowerSaveRecoveryTime;

	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_BCR_POWER_SAVE_CONTROL,
								&BcrPowerSaveControl,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);

	return hResult;
}

HRESULT CDCBarcode_31::CMD_BCR_READ(LPCTSTR lpszSymbologies)
{
	HRESULT hResult = DC_ERROR;

	CStringArray strarrSymbologies;
	if (strlen(lpszSymbologies) > 0)
	{
		CUtils::SplitString(strarrSymbologies, (LPTSTR)lpszSymbologies, ",");
	}

	WORD wSymbologies[64] = {0};
	int nLoop = 0;
	list<string>::iterator iter;
	for (iter = strarrSymbologies.begin(); iter != strarrSymbologies.end(); iter++)
	{
		wSymbologies[nLoop] = atoi((*iter).c_str()), nLoop ++;
	}

	WFSBCRREADINPUT bcrreadinput = {NULL};
	if (nLoop > 0)
	{
		bcrreadinput.lpwSymbologies = wSymbologies;
	}
	else
	{
		bcrreadinput.lpwSymbologies = NULL;
	}

	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_BCR_READ,
								&bcrreadinput,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);

	return hResult;
}

HRESULT CDCBarcode_31::CMD_BCR_SET_GUIDANCE_LIGHT(long lGuidLight, long lCommand) 
{
	HRESULT hResult = DC_ERROR;

	WFSBCRSETGUIDLIGHT BcrSetGuidLight = {0};
	BcrSetGuidLight.wGuidLight = (USHORT)lGuidLight;
	BcrSetGuidLight.dwCommand = lCommand;
	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_BCR_SET_GUIDANCE_LIGHT,
								&BcrSetGuidLight,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);

	return hResult;
}

HRESULT CDCBarcode_31::CMD_BCR_RESET()
{
	HRESULT hResult = DC_ERROR;

	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_BCR_RESET,
								NULL,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);

	return hResult;
}

int CDCBarcode_31::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (FALSE == m_DCObject.m_bWosaXFSRun)
	{
		return -1;
	}

    LPWFSRESULT lpWfsRet = NULL;

	CString strWfsResult = "";

	switch (uMsg)
    {
        case WFS_OPEN_COMPLETE:
            lpWfsRet = (LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);
			break;
        case WFS_CLOSE_COMPLETE:
            lpWfsRet = (LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);
			break;
        case WFS_LOCK_COMPLETE:
            lpWfsRet = (LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);
			break;
        case WFS_UNLOCK_COMPLETE:
            lpWfsRet = (LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);
			break;
        case WFS_REGISTER_COMPLETE:
			lpWfsRet = (LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);
			break;
        case WFS_DEREGISTER_COMPLETE:
            lpWfsRet = (LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);
			break;
        case WFS_GETINFO_COMPLETE:
            lpWfsRet = (LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);
			break;
		case WFS_EXECUTE_COMPLETE:
			lpWfsRet = (LPWFSRESULT)lParam;
			if (NULL != lpWfsRet)
			{
				strWfsResult = HandleCmdResult(lpWfsRet);
			}

			WFSFreeResult(lpWfsRet);
			break;
        case WFS_EXECUTE_EVENT:
			lpWfsRet = (LPWFSRESULT)lParam;
			if (NULL != lpWfsRet)
			{
				strWfsResult = HandleEXEEvtResult(lpWfsRet);
			}

			WFSFreeResult(lpWfsRet);
			break;
        case WFS_SERVICE_EVENT:
			lpWfsRet = (LPWFSRESULT)lParam;
			if (NULL != lpWfsRet)
			{
				strWfsResult = HandleSRVEvtResult(lpWfsRet);
			}

			WFSFreeResult(lpWfsRet);
			break;
        case WFS_USER_EVENT:
			lpWfsRet = (LPWFSRESULT)lParam;
			if (NULL != lpWfsRet)
			{
				strWfsResult = HandleUSEREvtResult(lpWfsRet);
			}

			WFSFreeResult(lpWfsRet);
			break ;
		case WFS_SYSTEM_EVENT:
			lpWfsRet = (LPWFSRESULT)lParam;
			if (NULL != lpWfsRet)
			{
				strWfsResult = HandleSysEvtResult(lpWfsRet);
			}

			WFSFreeResult(lpWfsRet);
			break;
        case WFS_TIMER_EVENT:
			break;
         default:
            break;
    }

	if ("" != strWfsResult)
	{
		CString strWfsResult2Trace = strWfsResult;

		// 屏蔽磁道数据
		for (int nLoop = 0; nLoop < 3; nLoop ++)
		{
			CString strFlag(100, 0);
			sprintf((char *)strFlag.c_str(), "wfsresult.lpbuffer[%d].lpbdata=", nLoop);
			if (-1 != strWfsResult2Trace.find(strFlag))
			{
				CString strTrack = "";
				CString strTrackNew = "";
				CString strCardNum = "";
				CString strCardNumNew = "";
				int nTrackStart = strWfsResult2Trace.find(strFlag) + strFlag.length();
				int nTrackEnd = strWfsResult2Trace.find(";", nTrackStart);
				int nCardNumEnd = strWfsResult2Trace.find("=", nTrackStart);
				if (-1 != nCardNumEnd)
				{
					if (nCardNumEnd <= nTrackEnd)
					{
						strCardNum = strWfsResult2Trace.substr(nTrackStart, nCardNumEnd - nTrackStart);
					}
				}
				else if (-1 != nTrackEnd)
				{
					strCardNum = strWfsResult2Trace.substr(nTrackStart, nTrackEnd - nTrackStart);
				}

				if (strCardNum.length() > 12)
				{
					strCardNumNew = strCardNum.substr(0, strCardNum.length() - 5)
									+ "****"
									+ strCardNum.substr(strCardNum.length() - 1, 1);

					strTrackNew += strCardNumNew;
				}

				if (-1 != nTrackEnd)
				{
					strTrack = strWfsResult2Trace.substr(nTrackStart, nTrackEnd - nTrackStart);
				}
				else
				{
					strTrack = strWfsResult2Trace.substr(nTrackStart, strWfsResult2Trace.length() - nTrackStart);
				}

				if (strTrack.length() > 0 && strTrack.length() > strCardNum.length())
				{
					for (int nLoop = 0; nLoop < strTrack.length() - strCardNum.length(); nLoop ++)
					{
						strTrackNew += "*";
					}
				}

				if (strTrack.length() > 0 && strTrackNew.length() > 0)
				{
					CString strSource = strFlag + strTrack;
					CString strDest = strFlag + strTrackNew;
					// strWfsResult2Trace.Replace(strSource, strDest);
					strWfsResult2Trace = regex_replace(strWfsResult2Trace, regex(strSource), strDest);
				}
			}
		}

		CString strTrace(strWfsResult2Trace.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						uMsg, GetXFSMsgStr(uMsg).c_str(), strWfsResult2Trace);
		WriteTrace(OCXEVENT, strTrace);

		FireDCEvent(uMsg, strWfsResult);
	}

    return 0L;
}

HRESULT CDCBarcode_31::INF_BCR_STATUS()
{
	HRESULT hResult = DC_ERROR;

	CString strWfsResult = "";

	LPWFSRESULT lpWfsRet = NULL;
	hResult = WFSGetInfo(	m_DCObject.m_hService, 
							WFS_INF_BCR_STATUS, 
							NULL, 
							WFS_INDEFINITE_WAIT, 
							&lpWfsRet);

	if (WFS_SUCCESS == hResult)
	{
		LPWFSBCRSTATUS lpStatus = (LPWFSBCRSTATUS)lpWfsRet->lpBuffer;
		if (NULL == lpStatus)
		{
			return (short)DC_ERROR;
		}

		CString strGuidLight(16, 0);
		CString strGuidLights(16 * WFS_BCR_GUIDLIGHTS_SIZE + 256, 0);
		for (int nLoop = 0; nLoop < WFS_BCR_GUIDLIGHTS_SIZE; nLoop ++)
		{
			sprintf((char *)strGuidLight.c_str(), "%d", lpStatus->dwGuidLights[nLoop]);
			
			if (strGuidLights.length() > 0)
			{
				strGuidLights += ",";
			}
			strGuidLights += strGuidLight;
		}

		strWfsResult = CString(strGuidLights.length() + (NULL == lpStatus->lpszExtra ? 0 : strlen(lpStatus->lpszExtra)) + 2048, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
							"%s"
							"wfsresult.lpbuffer.fwdevice=%d"
							"%s"
							"wfsresult.lpbuffer.fwbcrscanner=%d"
							"%s"
							"wfsresult.lpbuffer.dwguidlights=%s"
							"%s"
							"wfsresult.lpbuffer.lpszextra=%s"
							"%s"
							"wfsresult.lpbuffer.wdeviceposition=%d"
							"%s"
							"wfsresult.lpbuffer.uspowersaverecoverytime=%d",
							WFS_INF_BCR_STATUS,
							GetStringSplitChar(),
							lpStatus->fwDevice,
							GetStringSplitChar(),
							lpStatus->fwBCRScanner,
							GetStringSplitChar(),
							strGuidLights,
							GetStringSplitChar(),
							(NULL == lpStatus->lpszExtra ? "NULL" : FormatExtra(lpStatus->lpszExtra)),
							GetStringSplitChar(),
							lpStatus->wDevicePosition,
							GetStringSplitChar(),
							lpStatus->usPowerSaveRecoveryTime);
	}

	WFSFreeResult(lpWfsRet);

	if ("" != strWfsResult)
	{
		CString strTrace(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), strWfsResult.c_str());
		WriteTrace(OCXEVENT, strTrace);

		FireDCEvent(WFS_GETINFO_COMPLETE, strWfsResult);

		return WFS_SUCCESS;
	}

	return hResult;
}

HRESULT CDCBarcode_31::INF_BCR_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	LPWFSRESULT lpWfsRet = NULL;
	hResult = WFSGetInfo(	m_DCObject.m_hService,
							WFS_INF_BCR_CAPABILITIES,
							NULL,
							WFS_INDEFINITE_WAIT,
							&lpWfsRet);

	if (WFS_SUCCESS != hResult)
	{
		return hResult;
	}

	LPWFSBCRCAPS lpCaps = (LPWFSBCRCAPS)lpWfsRet->lpBuffer;
	if (NULL == lpCaps)
	{
		WFSFreeResult(lpWfsRet);
		return (short)DC_ERROR;
	}

	CString strSymbology(16, 0);
	CString strSymbologies(16 * 128 + 256, 0);
	if (NULL != lpCaps->lpwSymbologies)
	{
		for (int nLoop = 0; 0 != lpCaps->lpwSymbologies[nLoop]; nLoop ++)
		{
			sprintf((char *)strSymbology.c_str(), "%d", lpCaps->lpwSymbologies[nLoop]);
			
			if (strSymbologies.length() > 0)
			{
				strSymbologies += ",";
			}
			strSymbologies += strSymbology;
		}
	}

	CString strGuidLight(16, 0);
	CString strGuidLights(16 * WFS_BCR_GUIDLIGHTS_SIZE + 256, 0);
	for (int nLoop = 0; nLoop < WFS_BCR_GUIDLIGHTS_SIZE; nLoop ++)
	{
		sprintf((char *)strGuidLight.c_str(), "%d", lpCaps->dwGuidLights[nLoop]);
		
		if (strGuidLights.length() > 0)
		{
			strGuidLights += ",";
		}
		strGuidLights += strGuidLight;
	}

	CString strWfsResult(strSymbologies.length() + strGuidLights.length() + (NULL == lpCaps->lpszExtra ? 0 : strlen(lpCaps->lpszExtra)) + 2048, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
						"%s"
						"wfsresult.lpbuffer.wclass=%d"
						"%s"
						"wfsresult.lpbuffer.bcompound=%s"
						"%s"
						"wfsresult.lpbuffer.bcanfiltersymbologies=%s"
						"%s"
						"wfsresult.lpbuffer.lpwsymbologies=%s"
						"%s"
						"wfsresult.lpbuffer.dwguidlights=%s"
						"%s"
						"wfsresult.lpbuffer.lpszextra=%s"
						"%s"
						"wfsresult.lpbuffer.bpowersavecontrol=%s",
						WFS_INF_BCR_CAPABILITIES,
						GetStringSplitChar(),
						lpCaps->wClass,
						GetStringSplitChar(),
						lpCaps->bCompound ? "TRUE" : "false",
						GetStringSplitChar(),
						lpCaps->bCanFilterSymbologies ? "TRUE" : "false",
						GetStringSplitChar(),
						strSymbologies,
						GetStringSplitChar(),
						strGuidLights,
						GetStringSplitChar(),
						(NULL == lpCaps->lpszExtra ? "NULL" : FormatExtra(lpCaps->lpszExtra)),
						GetStringSplitChar(),
						lpCaps->bPowerSaveControl ? "TRUE" : "false");

	WFSFreeResult(lpWfsRet);

	if ("" != strWfsResult)
	{
		CString strTrace(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), strWfsResult.c_str());
		WriteTrace(OCXEVENT, strTrace);

		FireDCEvent(WFS_GETINFO_COMPLETE, strWfsResult);

		return WFS_SUCCESS;
	}

	return hResult;
}

CString	CDCBarcode_31::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[]={
		{"WFS_CMD_BCR_READ"					,BCR_SERVICE_OFFSET + 1},
		{"WFS_CMD_BCR_RESET"				,BCR_SERVICE_OFFSET + 2},
		{"WFS_CMD_BCR_SET_GUIDANCE_LIGHT"	,BCR_SERVICE_OFFSET + 3},
		{"WFS_CMD_BCR_POWER_SAVE_CONTROL"	,BCR_SERVICE_OFFSET + 4}
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

CString	CDCBarcode_31::GetXFSMsgStr(DWORD dwEventID)
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

		{"WFS_SRVE_BCR_DEVICEPOSITION"			,(BCR_SERVICE_OFFSET + 1)},
		{"WFS_SRVE_BCR_POWER_SAVE_CHANGE"		,(BCR_SERVICE_OFFSET + 2)}
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

CString	CDCBarcode_31::GetXFSSysEvtStr(DWORD dwEventID)
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

CString	CDCBarcode_31::GetXFSErrStr(HRESULT hResult)
{
	if (hResult >= DC_ERROR && hResult < WFS_ERR_UNSUPP_DATA)
	{
		return "DC_ERROR";
	}

	if (hResult >= DC_ERROR && hResult < WFS_ERR_UNSUPP_DATA)
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
		{"WFS_ERR_BCR_BARCODEINVALID"		,-(BCR_SERVICE_OFFSET + 0)},
		{"WFS_ERR_BCR_INVALID_PORT"			,-(BCR_SERVICE_OFFSET + 1)},
		{"WFS_ERR_BCR_POWERSAVETOOSHORT"	,-(BCR_SERVICE_OFFSET + 2)}
	};

	CString strRes="UNKNOWN ERROR";

	for (int i = 0; i < sizeof(XFSErr) / sizeof(XFSERR); i ++)
	{
		if ( XFSErr[i].iErr==hResult )
		{
			strRes=XFSErr[i].strErr;
			break;
		}
	}
	return strRes;
}

CString CDCBarcode_31::HandleCmdErr(LPWFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dwcommandcode=%d",
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwCommandCode);
	return strWfsResult;
}

CString CDCBarcode_31::HandleCmdResult(LPWFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	if (WFS_SUCCESS != lpWfsRet->hResult)
	{
		return HandleCmdErr(lpWfsRet);
	}
	
	CString strTrace;
	
	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%ld"
						"%s"
						"wfsresult.u.dwcommandcode=%ld",
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwCommandCode);

	CString strCmdResult = "";

	switch (lpWfsRet->u.dwCommandCode)
	{
		case WFS_CMD_BCR_READ:
		{
			LPWFSBCRREADOUTPUT * lppReadOutput = NULL;
			lppReadOutput = (LPWFSBCRREADOUTPUT *)lpWfsRet->lpBuffer;

			if (NULL != lppReadOutput)
			{
				for (int nLoop = 0; NULL != lppReadOutput[nLoop]; nLoop ++)
				{
					CHAR * pszBarcodeData = NULL;
					LPWFSBCRXDATA lpxBarcodeData = lppReadOutput[nLoop]->lpxBarcodeData;
					if (NULL != lpxBarcodeData)
					{
						pszBarcodeData = new CHAR[lpxBarcodeData->usLength * 2 + 2];
						memset(pszBarcodeData, 0, lpxBarcodeData->usLength * 2 + 2);

						CUtils().HextoStr(lpxBarcodeData->lpbData, lpxBarcodeData->usLength, pszBarcodeData);
					}

					CString strReadOutput(1024, 0);
					sprintf((char *)strReadOutput.c_str(), "%s"
											"wfsresult.lpbuffer[%d].wsymbology=%d"
											"%s"
											"wfsresult.lpbuffer[%d].lpxbarcodedata=%s"
											"%s"
											"wfsresult.lpbuffer[%d].lpszsymbologyname=%s",
											GetStringSplitChar(),
											nLoop, lppReadOutput[nLoop]->wSymbology,
											GetStringSplitChar(),
											nLoop, (NULL == pszBarcodeData ? "" : pszBarcodeData),
											GetStringSplitChar(),
											nLoop, (NULL == lppReadOutput[nLoop]->lpszSymbologyName ? "" : lppReadOutput[nLoop]->lpszSymbologyName));
					if (NULL != pszBarcodeData)
					{
						delete[] pszBarcodeData;
						pszBarcodeData = NULL;
					}

					strCmdResult += strReadOutput;
				}
			}

			break ;
		}
		case WFS_CMD_BCR_SET_GUIDANCE_LIGHT:
		case WFS_CMD_BCR_RESET:
		case WFS_CMD_BCR_POWER_SAVE_CONTROL:
			break ;
		default:
			break;
	}

	if ("" != strCmdResult)
	{
		strWfsResult += strCmdResult;
	}

	return strWfsResult;
}

CString CDCBarcode_31::HandleEXEEvtResult(LPWFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%ld"
						"%s"
						"wfsresult.u.dweventid=%ld",
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEventID);

	return strWfsResult;
}

CString CDCBarcode_31::HandleSRVEvtResult(LPWFSRESULT lpWfsRet)
{
	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%ld"
						"%s"
						"wfsresult.u.dweventid=%ld",
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEventID);

	CString strSrvEvent(256, 0);

	switch(lpWfsRet->u.dwEventID)
	{
		case WFS_SRVE_BCR_DEVICEPOSITION:
		{
			LPWFSBCRDEVICEPOSITION lpDevicePosition = (LPWFSBCRDEVICEPOSITION)lpWfsRet->lpBuffer;
			if (NULL == lpDevicePosition)
			{
				break ;
			}

			sprintf((char *)strSrvEvent.c_str(), 	"%s"
								"wfsresult.lpbuffer.wposition=%d",
								GetStringSplitChar(),
								lpDevicePosition->wPosition);

			break ;
		}
		case WFS_SRVE_BCR_POWER_SAVE_CHANGE:
		{
			LPWFSBCRPOWERSAVECHANGE lpPowerSaveChange = (LPWFSBCRPOWERSAVECHANGE)lpWfsRet->lpBuffer;
			if (NULL == lpPowerSaveChange)
			{
				break ;
			}

			sprintf((char *)strSrvEvent.c_str(), 	"%s"
								"wfsresult.lpbuffer.usPowerSaveRecoveryTime=%d",
								GetStringSplitChar(),
								lpPowerSaveChange->usPowerSaveRecoveryTime);

			break ;
		}
		default:
			break ;
	}

	if ("" != strSrvEvent)
	{
		strWfsResult += strSrvEvent;
	}

	return strWfsResult;
}

CString CDCBarcode_31::HandleSysEvtResult(LPWFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%ld"
						"%s"
						"wfsresult.u.dweventid=%ld",
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEventID);

	CString strSysEvent = "";

	switch(lpWfsRet->u.dwEventID)
	{
		case WFS_SYSE_DEVICE_STATUS:
		{
			LPWFSDEVSTATUS lpDevStatus = (LPWFSDEVSTATUS)lpWfsRet->lpBuffer;
			if (NULL == lpDevStatus)
			{
				break ;
			}

			strSysEvent = CString((NULL == lpDevStatus->lpszPhysicalName ? 0 : strlen(lpDevStatus->lpszPhysicalName))
								+ (NULL == lpDevStatus->lpszWorkstationName ? 0 : strlen(lpDevStatus->lpszWorkstationName)) + 1024, 0);
			sprintf((char *)strSysEvent.c_str(), 	"%s"
								"wfsresult.lpbuffer.lpszphysicalname=%s"
								"%s"
								"wfsresult.lpbuffer.lpszworkstationname=%s"
								"%s"
								"wfsresult.lpbuffer.dwState=%d",
								GetStringSplitChar(),
								(NULL == lpDevStatus->lpszPhysicalName ? "NULL" : lpDevStatus->lpszPhysicalName),
								GetStringSplitChar(),
								(NULL == lpDevStatus->lpszWorkstationName ? "NULL" : lpDevStatus->lpszWorkstationName),
								GetStringSplitChar(),
								lpDevStatus->dwState);
			break ;
		}
		case WFS_SYSE_HARDWARE_ERROR:
		case WFS_SYSE_SOFTWARE_ERROR:
		case WFS_SYSE_USER_ERROR:
		{
			LPWFSHWERROR lpWfsHwError = (LPWFSHWERROR)lpWfsRet->lpBuffer; 
			if (NULL == lpWfsHwError)
			{
				break ;
			}

			if (lpWfsHwError->dwSize > 0 && NULL != lpWfsHwError->lpbDescription)
			{
				strSysEvent = CString((NULL == lpWfsHwError->lpszLogicalName ? 0 : strlen(lpWfsHwError->lpszLogicalName))
									+ (NULL == lpWfsHwError->lpszPhysicalName ? 0 : strlen(lpWfsHwError->lpszPhysicalName))
									+ (NULL == lpWfsHwError->lpszWorkstationName ? 0 : strlen(lpWfsHwError->lpszWorkstationName))
									+ (NULL == lpWfsHwError->lpszAppID ? 0 : strlen(lpWfsHwError->lpszAppID))
									+ lpWfsHwError->dwSize + 2048, 0);
				sprintf((char *)strSysEvent.c_str(), 	"%s"
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
									(NULL == lpWfsHwError->lpszLogicalName ? "NULL" : lpWfsHwError->lpszLogicalName),
									GetStringSplitChar(),
									(NULL == lpWfsHwError->lpszPhysicalName ? "NULL" : lpWfsHwError->lpszPhysicalName),
									GetStringSplitChar(),
									(NULL == lpWfsHwError->lpszWorkstationName ? "NULL" : lpWfsHwError->lpszWorkstationName),
									GetStringSplitChar(),
									(NULL == lpWfsHwError->lpszAppID ? "NULL" : lpWfsHwError->lpszAppID),
									GetStringSplitChar(),
									lpWfsHwError->dwAction,
									GetStringSplitChar(),
									lpWfsHwError->dwSize,
									GetStringSplitChar(),
									CString((LPCSTR)lpWfsHwError->lpbDescription, lpWfsHwError->dwSize));
			}
			break ;
		}
		case WFS_SYSE_APP_DISCONNECT:
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
		strWfsResult += strSysEvent;
	}

	return strWfsResult;
}

CString CDCBarcode_31::HandleUSEREvtResult(LPWFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%ld"
						"%s"
						"wfsresult.u.dweventid=%ld",
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEventID);

	return strWfsResult;
}