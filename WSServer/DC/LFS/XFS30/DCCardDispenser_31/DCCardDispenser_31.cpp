// DCCardDispenser_31.cpp: implementation of the CDCCardDispenser_31 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCCardDispenser_31.h"
#include "JavaScriptStringParam.h"

// #pragma comment(lib, "../../XFS310SDK/LIB/msxfs.lib")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDCCardDispenser_31::CDCCardDispenser_31(LPCTSTR strDCName)
{
	m_strDCName = strDCName;
	m_DCObject.m_bWosaXFSRun = FALSE;
}

CDCCardDispenser_31::~CDCCardDispenser_31()
{

}

HRESULT CDCCardDispenser_31::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// ��������
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_CRD_DISPENSE_CARD"))
	{
		bValid = TRUE;
		hResult = CMD_CRD_DISPENSE_CARD(atol(CJSStringParam::GetStringParam(strarrParams, "usnumber").c_str()), 
										0 != atol(CJSStringParam::GetStringParam(strarrParams, "bpresent").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CRD_EJECT_CARD"))
	{
		bValid = TRUE;
		hResult = CMD_CRD_EJECT_CARD();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CRD_RETAIN_CARD"))
	{
		bValid = TRUE;
		hResult = CMD_CRD_RETAIN_CARD(atol(CJSStringParam::GetStringParam(strarrParams, "usnumber").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CRD_RESET"))
	{
		bValid = TRUE;
		hResult = CMD_CRD_RESET(atol(CJSStringParam::GetStringParam(strarrParams, "usaction").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CRD_SET_CARD_UNIT_INFO"))
	{
		bValid = TRUE;
		hResult = CMD_CRD_SET_CARD_UNIT_INFO(strSingleParam.c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CRD_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_CRD_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CRD_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_CRD_CAPABILITIES();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CRD_CARD_UNIT_INFO"))
	{
		bValid = TRUE;
		hResult = INF_CRD_CARD_UNIT_INFO(NULL);
	}

	return hResult;
}

HRESULT CDCCardDispenser_31::CMD_CRD_DISPENSE_CARD(long lNumber, BOOL bPresent)
{
	HRESULT hResult = DC_ERROR;

	WFSCRDDISPENSE wfsCrdDispense;
	wfsCrdDispense.usNumber = (USHORT)lNumber;
	wfsCrdDispense.bPresent = bPresent;
	
	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_CRD_DISPENSE_CARD,
								&wfsCrdDispense,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);

	return hResult;
}

HRESULT CDCCardDispenser_31::CMD_CRD_SET_CARD_UNIT_INFO(LPCTSTR strCUInfo)
{
	if (NULL == strCUInfo)
	{
		return (short)DC_ERROR;
	}

	HRESULT hResult = DC_ERROR;

	// ����GET_WFS_INF_CRD_CARD_UNIT_INFO��ȡ����ṹ
	LPWFSRESULT lpResult = NULL;
	hResult = INF_CRD_CARD_UNIT_INFO((LPVOID *)&lpResult);
	if (WFS_SUCCESS != hResult || NULL == lpResult)
	{
		return (short)DC_ERROR;
	}

	LPWFSCRDCUINFO lpCardUnitInfo = (LPWFSCRDCUINFO)lpResult->lpBuffer;
	if (NULL == lpCardUnitInfo || NULL == lpCardUnitInfo->lppList)
	{
		WFSFreeResult(lpResult);
		return (short)DC_ERROR;
	}

	BOOL bEndWithNoChange = FALSE;

	CStringArray strarrParams;
	CString strParamKey;
	CString strParamValue;

	if (FALSE == CJSStringParam::GetStringParams(strCUInfo, GetStringSplitChar(), strarrParams) || TRUE == strarrParams.empty())
	{
		WFSFreeResult(lpResult);
		return (short)DC_ERROR;
	}


	int nNumOfPUCashUnits = 0;
	LPWFSCRDCARDUNIT lpList = NULL;
 	for (int nLoop = 0; nLoop < lpCardUnitInfo->usCount; nLoop ++)
	{
		lpList = lpCardUnitInfo->lppList[nLoop];
		if (NULL != lpList)
		{
			strParamKey = CString(100, 0);
			sprintf((char *)strParamKey.c_str(), "wfsresult.lpbuffer.lppList[%d].ulcount", nLoop);
			if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
			{
				WFSFreeResult(lpResult);
				return (short)DC_ERROR;
			}

			lpList->ulCount = atoi(strParamValue.c_str());
			lpList->ulInitialCount = lpList->ulCount;
			lpList->ulRetainCount = 0;
		}
	}

	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_CRD_SET_CARD_UNIT_INFO,
								lpCardUnitInfo,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);

	WFSFreeResult(lpResult);
	return hResult;
}

HRESULT CDCCardDispenser_31::CMD_CRD_EJECT_CARD() 
{
	HRESULT hResult = DC_ERROR;
	
	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_CRD_EJECT_CARD,
								NULL,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);
	
	return hResult;
}

HRESULT CDCCardDispenser_31::CMD_CRD_RETAIN_CARD(long lNumber)
{
	HRESULT hResult = DC_ERROR;
	
	WFSCRDRETAINCARD wfsCrdRetainCard;
	wfsCrdRetainCard.usNumber = (USHORT)lNumber;
	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_CRD_RETAIN_CARD,
								&wfsCrdRetainCard,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);
	
	return hResult;
}

HRESULT CDCCardDispenser_31::CMD_CRD_RESET(long lResetIn)
{
	HRESULT hResult = DC_ERROR;
	
	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_CRD_RESET,
								&lResetIn,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);
	
	return hResult;
}

HRESULT CDCCardDispenser_31::INF_CRD_STATUS()
{
	HRESULT hResult = DC_ERROR;
	
	CString strWfsResult = "";
	
	LPWFSRESULT lpWfsRet = NULL;
	hResult = WFSGetInfo(m_DCObject.m_hService, 
		WFS_INF_CRD_STATUS, 
		NULL, 
		WFS_INDEFINITE_WAIT, 
		&lpWfsRet);
	
	if (WFS_SUCCESS == hResult)
	{
		LPWFSCRDSTATUS lpStatus = (LPWFSCRDSTATUS)(lpWfsRet->lpBuffer);
		if (NULL == lpStatus)
		{
			return (short)DC_ERROR;
		}
		
		strWfsResult = CString((NULL == lpStatus->lpszExtra ? 0 : strlen(lpStatus->lpszExtra)) + 1024, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.fwdevice=%d"
			"%s"
			"wfsresult.lpbuffer.fwdispenser=%d"
			"%s"
			"wfsresult.lpbuffer.fwtransport=%d"
			"%s"
			"wfsresult.lpbuffer.fwmedia=%d"
			"%s"
			"wfsresult.lpbuffer.fwshutter=%d"
			"%s"
// 			"wfsresult.lpbuffer.dwguidlights[WFS_CRD_GUIDLIGHTS_MAX]=%ld"
// 			"%s"
			"wfsresult.lpbuffer.wdeviceposition=%d"
			"%s"
			"wfsresult.lpbuffer.uspowersaverecoverytime=%ld"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			WFS_INF_CRD_STATUS,
			GetStringSplitChar(),
			lpStatus->fwDevice,
			GetStringSplitChar(),
			lpStatus->fwDispenser,
			GetStringSplitChar(),
			lpStatus->fwTransport,
			GetStringSplitChar(),
			lpStatus->fwMedia,
			GetStringSplitChar(),
			lpStatus->fwShutter,
			GetStringSplitChar(),
// 			lpStatus->dwGuidLights[WFS_CRD_GUIDLIGHTS_MAX], 
// 			GetStringSplitChar(),
			lpStatus->wDevicePosition, 
			GetStringSplitChar(),
			lpStatus->usPowerSaveRecoveryTime, 
			GetStringSplitChar(),
			(NULL == lpStatus->lpszExtra ? "NULL" : FormatExtra(lpStatus->lpszExtra)));
	}
	
	WFSFreeResult(lpWfsRet);
	
	if ("" != strWfsResult)
	{
		CString strTrace(strWfsResult.length() + 256, 0);
	
		FireDCEvent(WFS_GETINFO_COMPLETE, strWfsResult);
		
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
			WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), strWfsResult.c_str());
		WriteTrace(OCXEVENT, strTrace);
		
		return WFS_SUCCESS;
	}

	return hResult;
}

HRESULT CDCCardDispenser_31::INF_CRD_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	LPWFSRESULT lpWfsRet = NULL;
	hResult = WFSGetInfo(	m_DCObject.m_hService,
							WFS_INF_CRD_CAPABILITIES,
							NULL,
							WFS_INDEFINITE_WAIT,
							&lpWfsRet);

	CString strTrace(256, 0);
	sprintf((char *)strTrace.c_str(), "WFSGetInfo(WFS_INF_CRD_CAPABILITIES) hResult = %ld(%s)", 
					hResult, GetXFSErrStr(hResult).c_str());
	WriteTrace(OCXGetInfo, strTrace);

	if (WFS_SUCCESS != hResult)
	{
		return hResult;
	}

	LPWFSCRDCAPS lpCaps = (LPWFSCRDCAPS)lpWfsRet->lpBuffer;
	if (NULL == lpCaps)
	{
		WFSFreeResult(lpWfsRet);
		return (short)DC_ERROR;
	}

	CString strWfsResult((NULL == lpCaps->lpszExtra ? 0 : strlen(lpCaps->lpszExtra)) + 1024, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
						"%s"
						"wfsresult.lpbuffer.wclass=%d"
						"%s"
						"wfsresult.lpbuffer.bcompound=%s"
						"%s"
						"wfsresult.lpbuffer.fwpoweronoption=%d"
						"%s"
						"wfsresult.lpbuffer.fwpoweroffoption=%d"
						"%s"
						"wfsresult.lpbuffer.bcardtakensensor=%s"
						"%s"
						"wfsresult.lpbuffer.fwdispenseto=%d"
						"%s"
// 						"wfsresult.lpbuffer.dwguidlights[WFS_CRD_GUIDLIGHTS_MAX]=%ld"
// 						"%s"
						"wfsresult.lpbuffer.bpowersavecontrol=%s"
						"%s"
						"wfsresult.lpbuffer.lpszextra=%s",
						WFS_INF_CRD_CAPABILITIES,
						GetStringSplitChar(),
						lpCaps->wClass,
						GetStringSplitChar(),
						lpCaps->bCompound ? "TRUE" : "false",
						GetStringSplitChar(),
						lpCaps->fwPowerOnOption,
						GetStringSplitChar(),
						lpCaps->fwPowerOffOption,
						GetStringSplitChar(),
						lpCaps->bCardTakenSensor ? "TRUE" : "false",
						GetStringSplitChar(),
						lpCaps->fwDispenseTo,
						GetStringSplitChar(),
// 						lpCaps->dwGuidLights[WFS_CRD_GUIDLIGHTS_SIZE],
// 						GetStringSplitChar(),
						lpCaps->bPowerSaveControl ? "TRUE" : "false",
						GetStringSplitChar(),
						(NULL == lpCaps->lpszExtra ? "NULL" : FormatExtra(lpCaps->lpszExtra)));

	WFSFreeResult(lpWfsRet);

	if ("" != strWfsResult)
	{
		FireDCEvent(WFS_GETINFO_COMPLETE, strWfsResult);

		strTrace = CString(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), strWfsResult.c_str());
		WriteTrace(OCXEVENT, strTrace);

		return WFS_SUCCESS;
	}

	return hResult;
}

HRESULT CDCCardDispenser_31::INF_CRD_CARD_UNIT_INFO(LPVOID * lppResult)
{
	HRESULT hResult = DC_ERROR;

	LPWFSRESULT lpResult = NULL;
	hResult = WFSGetInfo(	m_DCObject.m_hService,
							WFS_INF_CRD_CARD_UNIT_INFO,
							NULL,
							WFS_INDEFINITE_WAIT,
							&lpResult);

	CString strTrace(256, 0);
	sprintf((char *)strTrace.c_str(), "WFSGetInfo(WFS_INF_CRD_CARD_UNIT_INFO) hResult = %ld(%s)", 
					hResult, GetXFSErrStr(hResult).c_str());
	WriteTrace(OCXGetInfo, strTrace);

	if (WFS_SUCCESS != hResult)
	{
		return hResult;
	}

	LPWFSCRDCUINFO lpCardUnitInfo = (LPWFSCRDCUINFO)lpResult->lpBuffer;
	if (NULL == lpCardUnitInfo)
	{
		FireDCEvent(WFS_GETINFO_COMPLETE, "");

		strTrace = CString(256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), "");
		WriteTrace(OCXEVENT, strTrace);

		WFSFreeResult(lpResult);
		return hResult;
	}

	CString strWfsResult(100, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
						"%s"
						"wfsresult.lpbuffer.uscount=%d",
						WFS_INF_CRD_CARD_UNIT_INFO,
						GetStringSplitChar(),
						lpCardUnitInfo->usCount);

	LPWFSCRDCARDUNIT lpList = NULL;
	for (int nLoop = 0; nLoop < lpCardUnitInfo->usCount; nLoop ++)
	{
		lpList = lpCardUnitInfo->lppList[nLoop];
		if (NULL == lpList)
		{
			continue ;
		}

		CString strCardUnit(strlen(lpList->lpszCardName) + 1024, 0);
		sprintf((char *)strCardUnit.c_str(), "%s"
								"wfsresult.lpbuffer.lpplist[%d].usnumber=%d"
								"%s"
								"wfsresult.lpbuffer.lpplist[%d].lpszcardname=%s"
								"%s"
								"wfsresult.lpbuffer.lpplist[%d].ustype=%ld"
								"%s"
								"wfsresult.lpbuffer.lpplist[%d].ulinitialcount=%ld"
								"%s"
								"wfsresult.lpbuffer.lpplist[%d].ulcount=%ld"
								"%s"
								"wfsresult.lpbuffer.lpplist[%d].ulretaincount=%ld"
								"%s"
								"wfsresult.lpbuffer.lpplist[%d].ulthreshold=%ld"
								"%s"
								"wfsresult.lpbuffer.lpplist[%d].usstatus=%ld"
								"%s"
								"wfsresult.lpbuffer.lpplist[%d].bhardwaresensor=%s",
								GetStringSplitChar(),
								nLoop, lpList->usNumber,
								GetStringSplitChar(),
								nLoop, lpList->lpszCardName,
								GetStringSplitChar(),
								nLoop, lpList->usType,
								GetStringSplitChar(),
								nLoop, lpList->ulInitialCount,
								GetStringSplitChar(),
								nLoop, lpList->ulCount,
								GetStringSplitChar(),
								nLoop, lpList->ulRetainCount,
								GetStringSplitChar(),
								nLoop, lpList->ulThreshold,
								GetStringSplitChar(),
								nLoop, lpList->usStatus,
								GetStringSplitChar(),
								nLoop, (TRUE == lpList->bHardwareSensor ? "TRUE" : "false"));

		strWfsResult += strCardUnit;
	}

	// EXE_WFS_CMD_CRD_SET_CARD_UNIT_INFO��������ô�GET_WFS_INF_CRD_UNIT_INFO���������ڻ�ȡ���ݵ�SP�ļӳ��Ľṹ
	if (NULL != lppResult)
	{
		// �����Ҳ��ͷ�WFS���
		* (LPWFSRESULT *)lppResult = lpResult;
	}
	else
	{
		WFSFreeResult(lpResult);
	}

	if ("" != strWfsResult)
	{
		FireDCEvent(WFS_GETINFO_COMPLETE, strWfsResult);

		strTrace = CString(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), strWfsResult.c_str());
		WriteTrace(OCXEVENT, strTrace);

		return WFS_SUCCESS;
	}

	return hResult;
}

CString	CDCCardDispenser_31::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[7]={
		{"WFS_CMD_CRD_DISPENSE_CARD"           ,(CRD_SERVICE_OFFSET + 1)},
		{"WFS_CMD_CRD_EJECT_CARD"              ,(CRD_SERVICE_OFFSET + 2)},
		{"WFS_CMD_CRD_RETAIN_CARD"             ,(CRD_SERVICE_OFFSET + 3)},
		{"WFS_CMD_CRD_RESET"                   ,(CRD_SERVICE_OFFSET + 4)},
		{"WFS_CMD_CRD_SET_GUIDANCE_LIGHT"      ,(CRD_SERVICE_OFFSET + 5)},
		{"WFS_CMD_CRD_SET_CARD_UNIT_INFO"      ,(CRD_SERVICE_OFFSET + 6)},
		{"WFS_CMD_CRD_POWER_SAVE_CONTROL"      ,(CRD_SERVICE_OFFSET + 7)}
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

CString	CDCCardDispenser_31::GetXFSMsgStr(DWORD dwEventID)
{
	struct XFSMSG {
		char strMsg[128];
		DWORD iMsg;
	}XFSMsg[]={
		{"WFS_OPEN_COMPLETE"                       ,(WM_USER + 1)},
		{"WFS_CLOSE_COMPLETE"                      ,(WM_USER + 2)},
		{"WFS_LOCK_COMPLETE"                       ,(WM_USER + 3)},
		{"WFS_UNLOCK_COMPLETE"                     ,(WM_USER + 4)},
		{"WFS_REGISTER_COMPLETE"                   ,(WM_USER + 5)},
		{"WFS_DEREGISTER_COMPLETE"                 ,(WM_USER + 6)},
		{"WFS_GETINFO_COMPLETE"                    ,(WM_USER + 7)},
		{"WFS_EXECUTE_COMPLETE"                    ,(WM_USER + 8)},
		
		{"WFS_EXECUTE_EVENT"                       ,(WM_USER + 20)},
		{"WFS_SERVICE_EVENT"                       ,(WM_USER + 21)},
		{"WFS_USER_EVENT"                          ,(WM_USER + 22)},
		{"WFS_SYSTEM_EVENT"                        ,(WM_USER + 23)},
		
		{"WFS_TIMER_EVENT"                         ,(WM_USER + 100)},
		
		{"WFS_SRVE_CRD_MEDIAREMOVED"           ,(CRD_SERVICE_OFFSET + 1)},
		{"WFS_SRVE_CRD_CARDUNITINFOCHANGED"    ,(CRD_SERVICE_OFFSET + 2)},
		{"WFS_SRVE_CRD_MEDIADETECTED"          ,(CRD_SERVICE_OFFSET + 3)},
		{"WFS_USRE_CRD_CARDUNITTHRESHOLD"      ,(CRD_SERVICE_OFFSET + 4)},
		{"WFS_EXEE_CRD_CARDUNITERROR"          ,(CRD_SERVICE_OFFSET + 5)},
		{"WFS_SRVE_CRD_DEVICEPOSITION"         ,(CRD_SERVICE_OFFSET + 6)},
		{"WFS_SRVE_CRD_POWER_SAVE_CHANGE"      ,(CRD_SERVICE_OFFSET + 7)}
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

CString	CDCCardDispenser_31::GetXFSSysEvtStr(DWORD dwEventID)
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
		{"WFS_SYSE_FRAUD_ATTEMPT"                  ,9}
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

CString	CDCCardDispenser_31::GetXFSErrStr(HRESULT hResult)
{
	if (hResult >= DC_ERROR && hResult < WFS_ERR_SEQUENCE_ERROR)
	{
		return "DC_ERROR";
	}

	struct XFSERR {
		char strErr[128];
		LONG iErr;
	}XFSErr[]={
		{"WFS_SUCCESS"                             ,(0)},
		{"WFS_ERR_ALREADY_STARTED"                 ,(-1)},
		{"WFS_ERR_API_VER_TOO_HIGH"                ,(-2)},
		{"WFS_ERR_API_VER_TOO_LOW"                 ,(-3)},
		{"WFS_ERR_CANCELED"                        ,(-4)},
		{"WFS_ERR_CFG_INVALID_HKEY"                ,(-5)},
		{"WFS_ERR_CFG_INVALID_NAME"                ,(-6)},
		{"WFS_ERR_CFG_INVALID_SUBKEY"              ,(-7)},
		{"WFS_ERR_CFG_INVALID_VALUE"               ,(-8)},
		{"WFS_ERR_CFG_KEY_NOT_EMPTY"               ,(-9)},
		{"WFS_ERR_CFG_NAME_TOO_LONG"               ,(-10)},
		{"WFS_ERR_CFG_NO_MORE_ITEMS"               ,(-11)},
		{"WFS_ERR_CFG_VALUE_TOO_LONG"              ,(-12)},
		{"WFS_ERR_DEV_NOT_READY"                   ,(-13)},
		{"WFS_ERR_HARDWARE_ERROR"                  ,(-14)},
		{"WFS_ERR_INTERNAL_ERROR"                  ,(-15)},
		{"WFS_ERR_INVALID_ADDRESS"                 ,(-16)},
		{"WFS_ERR_INVALID_APP_HANDLE"              ,(-17)},
		{"WFS_ERR_INVALID_BUFFER"                  ,(-18)},
		{"WFS_ERR_INVALID_CATEGORY"                ,(-19)},
		{"WFS_ERR_INVALID_COMMAND"                 ,(-20)},
		{"WFS_ERR_INVALID_EVENT_CLASS"             ,(-21)},
		{"WFS_ERR_INVALID_HSERVICE"                ,(-22)},
		{"WFS_ERR_INVALID_HPROVIDER"               ,(-23)},
		{"WFS_ERR_INVALID_HWND"                    ,(-24)},
		{"WFS_ERR_INVALID_HWNDREG"                 ,(-25)},
		{"WFS_ERR_INVALID_POINTER"                 ,(-26)},
		{"WFS_ERR_INVALID_REQ_ID"                  ,(-27)},
		{"WFS_ERR_INVALID_RESULT"                  ,(-28)},
		{"WFS_ERR_INVALID_SERVPROV"                ,(-29)},
		{"WFS_ERR_INVALID_TIMER"                   ,(-30)},
		{"WFS_ERR_INVALID_TRACELEVEL"              ,(-31)},
		{"WFS_ERR_LOCKED"                          ,(-32)},
		{"WFS_ERR_NO_BLOCKING_CALL"                ,(-33)},
		{"WFS_ERR_NO_SERVPROV"                     ,(-34)},
		{"WFS_ERR_NO_SUCH_THREAD"                  ,(-35)},
		{"WFS_ERR_NO_TIMER"                        ,(-36)},
		{"WFS_ERR_NOT_LOCKED"                      ,(-37)},
		{"WFS_ERR_NOT_OK_TO_UNLOAD"                ,(-38)},
		{"WFS_ERR_NOT_STARTED"                     ,(-39)},
		{"WFS_ERR_NOT_REGISTERED"                  ,(-40)},
		{"WFS_ERR_OP_IN_PROGRESS"                  ,(-41)},
		{"WFS_ERR_OUT_OF_MEMORY"                   ,(-42)},
		{"WFS_ERR_SERVICE_NOT_FOUND"               ,(-43)},
		{"WFS_ERR_SPI_VER_TOO_HIGH"                ,(-44)},
		{"WFS_ERR_SPI_VER_TOO_LOW"                 ,(-45)},
		{"WFS_ERR_SRVC_VER_TOO_HIGH"               ,(-46)},
		{"WFS_ERR_SRVC_VER_TOO_LOW"                ,(-47)},
		{"WFS_ERR_TIMEOUT"                         ,(-48)},
		{"WFS_ERR_UNSUPP_CATEGORY"                 ,(-49)},
		{"WFS_ERR_UNSUPP_COMMAND"                  ,(-50)},
		{"WFS_ERR_VERSION_ERROR_IN_SRVC"           ,(-51)},
		{"WFS_ERR_INVALID_DATA"                    ,(-52)},
		{"WFS_ERR_SOFTWARE_ERROR"                  ,(-53)},
		{"WFS_ERR_CONNECTION_LOST"                 ,(-54)},
		{"WFS_ERR_USER_ERROR"                      ,(-55)},
		{"WFS_ERR_UNSUPP_DATA"                     ,(-56)},
		{"WFS_ERR_FRAUD_ATTEMPT"                   ,(-57)},
		{"WFS_ERR_SEQUENCE_ERROR"                  ,(-58)},

		{"WFS_ERR_CRD_MEDIAJAM"                    ,(-(CRD_SERVICE_OFFSET + 0))},
		{"WFS_ERR_CRD_NOMEDIA"                     ,(-(CRD_SERVICE_OFFSET + 1))},
		{"WFS_ERR_CRD_MEDIARETAINED"               ,(-(CRD_SERVICE_OFFSET + 2))},
		{"WFS_ERR_CRD_RETAINBINFULL"               ,(-(CRD_SERVICE_OFFSET + 3))},
		{"WFS_ERR_CRD_SHUTTERFAIL"                 ,(-(CRD_SERVICE_OFFSET + 4))},
		{"WFS_ERR_CRD_DEVICE_OCCUPIED"             ,(-(CRD_SERVICE_OFFSET + 5))},
		{"WFS_ERR_CRD_CARDUNITERROR"               ,(-(CRD_SERVICE_OFFSET + 6))},
		{"WFS_ERR_CRD_INVALIDCARDUNIT"             ,(-(CRD_SERVICE_OFFSET + 7))},
		{"WFS_ERR_CRD_INVALID_PORT"                ,(-(CRD_SERVICE_OFFSET + 8))},
		{"WFS_ERR_CRD_INVALIDRETAINBIN"            ,(-(CRD_SERVICE_OFFSET + 9))},
		{"WFS_ERR_CRD_POWERSAVETOOSHORT"           ,(-(CRD_SERVICE_OFFSET + 10))},
		{"WFS_ERR_CRD_POWERSAVEMEDIAPRESENT"       ,(-(CRD_SERVICE_OFFSET + 11))}
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

CString CDCCardDispenser_31::HandleCmdErr(LPWFSRESULT lpWfsRet)
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

CString CDCCardDispenser_31::HandleCmdResult(LPWFSRESULT lpWfsRet)
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
		case WFS_CMD_CRD_DISPENSE_CARD:
		case WFS_CMD_CRD_EJECT_CARD:
		case WFS_CMD_CRD_RETAIN_CARD:
		case WFS_CMD_CRD_RESET:
		case WFS_CMD_CRD_SET_CARD_UNIT_INFO:
		case WFS_CMD_CRD_SET_GUIDANCE_LIGHT:
		case WFS_CMD_CRD_POWER_SAVE_CONTROL:
			break;
		default:
			break;
	}

	if ("" != strCmdResult)
	{
		strWfsResult += strCmdResult;
	}
	
	return strWfsResult;
}

CString CDCCardDispenser_31::HandleEXEEvtResult(LPWFSRESULT lpWfsRet)
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

CString CDCCardDispenser_31::HandleSRVEvtResult(LPWFSRESULT lpWfsRet)
{
	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%ld"
		"%s"
		"wfsresult.u.dweventid=%ld",
		lpWfsRet->hResult,
		GetStringSplitChar(),
		lpWfsRet->u.dwEventID);
	
	return strWfsResult;
}

CString CDCCardDispenser_31::HandleUSEREvtResult(LPWFSRESULT lpWfsRet)
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

CString CDCCardDispenser_31::HandleSysEvtResult(LPWFSRESULT lpWfsRet)
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

int CDCCardDispenser_31::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		FireDCEvent(uMsg, strWfsResult);

		CString strTrace(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						uMsg, GetXFSMsgStr(uMsg).c_str(), strWfsResult.c_str());
		WriteTrace(OCXEVENT, strTrace);
	}

    return 0L;
}