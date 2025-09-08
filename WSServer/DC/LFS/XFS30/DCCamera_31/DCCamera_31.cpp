// DCCamera_31.cpp: implementation of the CDCCamera_31 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCCamera_31.h"
#include "../../../include/JavaScriptStringParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDCCamera_31::CDCCamera_31(LPCTSTR strDCName, LPCTSTR strTraceComponent)
{
	m_strDCName = strDCName;
	m_strTraceComponent = CString(strTraceComponent);
	m_DCObject.m_bWosaXFSRun = FALSE;
}

CDCCamera_31::~CDCCamera_31()
{

}
HRESULT CDCCamera_31::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// 调用命令
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_CAM_TAKE_PICTURE"))
	{
		bValid = TRUE;
		hResult = CMD_CAM_TAKE_PICTURE(		atol(CJSStringParam::GetStringParam(strarrParams, "wcamera").c_str()), 
											CJSStringParam::GetStringParam(strarrParams, "lpszcamdata").c_str(),
											CJSStringParam::GetStringParam(strarrParams, "lpszunicodecamdata").c_str(),
											CJSStringParam::GetStringParam(strarrParams, "lpszfilepath").c_str(),
											atol(CJSStringParam::GetStringParam(strarrParams, "wscansize").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CAM_RESET"))
	{
		bValid = TRUE;
		hResult = CMD_CAM_RESET();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CAM_DISPLAY"))
	{
		bValid = TRUE;
		hResult = CMD_CAM_DISPLAY(	atol(CJSStringParam::GetStringParam(strarrParams, "wcamera").c_str()),
									atol(CJSStringParam::GetStringParam(strarrParams, "waction").c_str()),
									atol(CJSStringParam::GetStringParam(strarrParams, "wx").c_str()),
									atol(CJSStringParam::GetStringParam(strarrParams, "wy").c_str()),
									atol(CJSStringParam::GetStringParam(strarrParams, "wwidth").c_str()),
									atol(CJSStringParam::GetStringParam(strarrParams, "wheight").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CAM_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_CAM_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CAM_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_CAM_CAPABILITIES();
	}

	return hResult;
}

HRESULT CDCCamera_31::CMD_CAM_TAKE_PICTURE(long lCamera, LPCTSTR lpszCamData, LPCTSTR lpszUNICODECamData, LPCTSTR lpszFilePath, long lScanSize)
{
	HRESULT hResult = DC_ERROR;

	LFSCAMTAKEPICTEX TakePictEx = {0};
	TakePictEx.wCamera = (USHORT)lCamera;
	TakePictEx.lpszCamData = NULL;
	TakePictEx.lpszUNICODECamData = NULL;
	if (strlen(lpszCamData) > 0)
	{
		TakePictEx.lpszCamData = (LPTSTR)lpszCamData;
	}
	else if (strlen(lpszUNICODECamData) > 0)
	{
		// ascii 转 widechar
		size_t sSize = strlen(lpszUNICODECamData);
		wchar_t * _lpszUNICODECamData = NULL;
		int dSize = mbstowcs(_lpszUNICODECamData, lpszUNICODECamData, 0) + 1;
		_lpszUNICODECamData = new wchar_t[dSize];
		wmemset(_lpszUNICODECamData, 0, dSize);
		int nRet = mbstowcs(_lpszUNICODECamData, lpszUNICODECamData, sSize);

		TakePictEx.lpszUNICODECamData = _lpszUNICODECamData;
	}
	if (strlen(lpszFilePath) > 0)
	{
		TakePictEx.lpszPictureFile = (LPTSTR)lpszFilePath;
	}
	else
	{
		TakePictEx.lpszPictureFile = NULL;
	}

	// 部分厂商是按照标准XFS320协议进行，没有扩展wScanSize字段，故不能指定值，只能在结构初始化时使用默认值
	// #define     WFS_CAM_SIZEALL                      (0)
	// TakePictEx.wScanSize = lScanSize;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CAM_TAKE_PICTURE_EX,
								&TakePictEx,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCamera_31::CMD_CAM_DISPLAY(long lCamera, long lAction, long lX, long lY, long lWidth, long lHeight)
{
	HRESULT hResult = DC_ERROR;

	LFSCAMDISP disp = { 0 };
	disp.camera = (WORD)lCamera;
	disp.action = (WORD)lAction;
	disp.x = (WORD)lX;
	disp.y = (WORD)lY;
	disp.width = (WORD)lWidth;
	disp.height = (WORD)lHeight;
	disp.wnd = NULL;
	disp.hpixel = 0;
	disp.vpixel = 0;
	disp.text_data = NULL;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CAM_DISPLAY,
								&disp,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCamera_31::CMD_CAM_RESET()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CAM_RESET,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCamera_31::INF_CAM_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(	m_DCObject.m_hService,
								LFS_INF_CAM_STATUS,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCamera_31::INF_CAM_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(	m_DCObject.m_hService,
								LFS_INF_CAM_CAPABILITIES,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

CString	CDCCamera_31::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[]={
		{"WFS_CMD_CAM_TAKE_PICTURE"            ,(CAM_SERVICE_OFFSET + 1)},
		{"WFS_CMD_CAM_RESET"                   ,(CAM_SERVICE_OFFSET + 2)}
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

CString	CDCCamera_31::GetXFSMsgStr(DWORD dwEventID)
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
		
		{"WFS_USRE_CAM_MEDIATHRESHOLD"         ,(CAM_SERVICE_OFFSET + 1)},
		{"WFS_EXEE_CAM_INVALIDDATA"            ,(CAM_SERVICE_OFFSET + 2)}
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

CString	CDCCamera_31::GetXFSSysEvtStr(DWORD dwEventID)
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

CString	CDCCamera_31::GetXFSErrStr(HRESULT hResult)
{
	if (hResult >= DC_ERROR && hResult < LFS_ERR_UNSUPP_DATA)
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

		{"WFS_ERR_CAM_CAMNOTSUPP"                  ,(-(CAM_SERVICE_OFFSET + 0))},
		{"WFS_ERR_CAM_MEDIAFULL"                   ,(-(CAM_SERVICE_OFFSET + 1))},
		{"WFS_ERR_CAM_CAMINOP"                     ,(-(CAM_SERVICE_OFFSET + 2))},
		{"WFS_ERR_CAM_CHARSETNOTSUPP"              ,(-(CAM_SERVICE_OFFSET + 3))},
		{"WFS_ERR_CAM_FILEIOERROR"				   ,(-(CAM_SERVICE_OFFSET + 4))},
		{"WFS_ERR_CAM_COMMANDUNSUPP"               ,(-(CAM_SERVICE_OFFSET + 5))},
		{"WFS_ERR_CAM_SYNCHRONIZEUNSUPP"           ,(-(CAM_SERVICE_OFFSET + 6))},
		{"WFS_ERR_CAM_KEYNOTFOUND"                 ,(-(CAM_SERVICE_OFFSET + 99))},
		{"WFS_ERR_CAM_ACCESSDENIED"                ,(-(CAM_SERVICE_OFFSET + 98))},
		{"WFS_ERR_CAM_DUPLICATEKEY"                ,(-(CAM_SERVICE_OFFSET + 97))},
		{"WFS_ERR_CAM_KEYNOVALUE"                  ,(-(CAM_SERVICE_OFFSET + 96))},
		{"WFS_ERR_CAM_USEVIOLATION"                ,(-(CAM_SERVICE_OFFSET + 95))},
		{"WFS_ERR_CAM_INVALIDKEYLENGTH"            ,(-(CAM_SERVICE_OFFSET + 94))},
		{"WFS_ERR_CAM_NOKEYRAM"                    ,(-(CAM_SERVICE_OFFSET + 93))},
		{"WFS_ERR_CAM_INVALID_HWND"                ,(-(CAM_SERVICE_OFFSET + 92))},
		{"WFS_ERR_CAM_NOTSIGNEROR"                 ,(-(CAM_SERVICE_OFFSET + 91))},
		{"WFS_ERR_CAM_SYNTAX"                      ,(-(CAM_SERVICE_OFFSET + 90))}
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

CString CDCCamera_31::HandleCmdErr(LPLFSRESULT lpWfsRet)
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

CString CDCCamera_31::HandleCmdResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}
	
	if (LFS_SUCCESS != lpWfsRet->result)
	{
		return HandleCmdErr(lpWfsRet);
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
	
	CString strCmdResult = "";

	switch (lpWfsRet->u.command_code)
	{
		case LFS_CMD_CAM_TAKE_PICTURE:
		{
			LPLFSCAMIMAGDATA lppCamImagData = NULL;
			lppCamImagData = (LPLFSCAMIMAGDATA)lpWfsRet->buffer;

			if (NULL != lppCamImagData)
			{
				char * pachHexStr = new char[lppCamImagData->datalen];
				memset(pachHexStr, 0, lppCamImagData->datalen * 2 + 2);

				m_Utils.HextoStr(lppCamImagData->data, (short)lppCamImagData->datalen, pachHexStr);

				strCmdResult = CString(strlen(pachHexStr) + 256, 0);
				sprintf((char *)strCmdResult.c_str(), "%s"
													"wfsresult.lpbuffer.wdatalen=%d"
													"%s"
													"wfsresult.lpbuffer.lpdata=%s",
													GetStringSplitChar(),
													lppCamImagData->datalen,
													GetStringSplitChar(),
													pachHexStr);

				delete[] pachHexStr;
				pachHexStr = NULL;
			}
			break;
		}
		case LFS_CMD_CAM_RESET:
			break;
		default:
			break;
	}

	if ("" != strCmdResult)
	{
		strWfsResult = string(strWfsResult.c_str()) + strCmdResult;
	}
	
	return strWfsResult;
}

CString CDCCamera_31::HandleEXEEvtResult(LPLFSRESULT lpWfsRet)
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

CString CDCCamera_31::HandleSRVEvtResult(LPLFSRESULT lpWfsRet)
{
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

CString CDCCamera_31::HandleUSEREvtResult(LPLFSRESULT lpWfsRet)
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

CString CDCCamera_31::HandleSysEvtResult(LPLFSRESULT lpWfsRet)
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

int CDCCamera_31::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (FALSE == m_DCObject.m_bWosaXFSRun && LFS_OPEN_COMPLETE != uMsg)
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
			printf("LFS_OPEN_COMPLETE CDCCamera_30\n");
			break;
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
			break ;
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

CString CDCCamera_31::HandleInfResult(LPLFSRESULT lpWfsRet)
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

	if (LFS_INF_CAM_STATUS == lpWfsRet->u.command_code)
	{
		LPLFSCAMSTATUS lpStatus = (LPLFSCAMSTATUS)lpWfsRet->buffer;
		if (NULL == lpStatus)
		{
			return strWfsResult;
		}

		CString strMedia(16, 0);
		CString strMedias(16 * LFS_CAM_CAMERAS_SIZE + 256, 0);
		for (int nLoop = 0; nLoop < LFS_CAM_CAMERAS_SIZE; nLoop++)
		{
			sprintf((char *)strMedia.c_str(), "%d", lpStatus->fwMedia[nLoop]);

			if (strlen(strMedias.c_str()) > 0)
			{
				strMedias = string(strMedias.c_str()) + ",";
			}
			strMedias = string(strMedias.c_str()) + strMedia;
		}

		CString strCamera(16, 0);
		CString strCameras(16 * LFS_CAM_CAMERAS_SIZE + 256, 0);
		for (int nLoop = 0; nLoop < LFS_CAM_CAMERAS_SIZE; nLoop++)
		{
			sprintf((char *)strCamera.c_str(), "%d", lpStatus->fwCameras[nLoop]);

			if (strlen(strCameras.c_str()) > 0)
			{
				strCameras = string(strCameras.c_str()) + ",";
			}
			strCameras = string(strCameras.c_str()) + strCamera;
		}

		CString strPicture(16, 0);
		CString strPictures(16 * LFS_CAM_CAMERAS_SIZE + 256, 0);
		for (int nLoop = 0; nLoop < LFS_CAM_CAMERAS_SIZE; nLoop++)
		{
			sprintf((char *)strPicture.c_str(), "%d", lpStatus->usPictures[nLoop]);

			if (strlen(strPictures.c_str()) > 0)
			{
				strPictures = string(strPictures.c_str()) + ",";
			}
			strPictures = string(strPictures.c_str()) + strPicture;
		}

		strWfsResult = CString(strMedias.length() + strCameras.length() + strPictures.length() + (NULL == lpStatus->lpszExtra ? 0 : strlen(lpStatus->lpszExtra)) + 2048, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
												"%s"
												"wfsresult.lpbuffer.fwdevice=%d"
												"%s"
												"wfsresult.lpbuffer.fwmedia=%s"
												"%s"
												"wfsresult.lpbuffer.fwcameras=%s"
												"%s"
												"wfsresult.lpbuffer.uspictures=%s"
												"%s"
												"wfsresult.lpbuffer.lpszextra=%s",
												LFS_INF_CAM_STATUS,
												GetStringSplitChar(),
												lpStatus->fwDevice,
												GetStringSplitChar(),
												strMedias.c_str(),
												GetStringSplitChar(),
												strCameras.c_str(),
												GetStringSplitChar(),
												strPictures.c_str(),
												GetStringSplitChar(),
												(NULL == lpStatus->lpszExtra ? "NULL" : FormatExtra(lpStatus->lpszExtra)));
	}
	else if (LFS_INF_CAM_CAPABILITIES == lpWfsRet->u.command_code)
	{
		LPLFSCAMCAPS lpCaps = (LPLFSCAMCAPS)lpWfsRet->buffer;
		if (NULL == lpCaps)
		{
			return strWfsResult;
		}

		CString strCamera(16, 0);
		CString strCameras(16 * LFS_CAM_CAMERAS_SIZE + 256, 0);
		for (int nLoop = 0; nLoop < LFS_CAM_CAMERAS_SIZE; nLoop++)
		{
			sprintf((char *)strCamera.c_str(), "%d", lpCaps->fwCameras[nLoop]);

			if (strCameras.length() > 0)
			{
				strCameras = string(strCameras.c_str()) + ",";
			}
			strCameras = string(strCameras.c_str()) + strCamera;
		}

		strWfsResult = CString(strCameras.length() + (NULL == lpCaps->lpszExtra ? 0 : strlen(lpCaps->lpszExtra)) + 2048, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
												"%s"
												"wfsresult.lpbuffer.wclass=%d"
												"%s"
												"wfsresult.lpbuffer.fwtype=%d"
												"%s"
												"wfsresult.lpbuffer.fwcameras=%s"
												"%s"
												"wfsresult.lpbuffer.usmaxpictures=%d"
												"%s"
												"wfsresult.lpbuffer.fwcamdata=%d"
												"%s"
												"wfsresult.lpbuffer.usmaxdatalength=%d"
												"%s"
												"wfsresult.lpbuffer.fwcharsupport=%d"
												"%s"
												"wfsresult.lpbuffer.lpszextra=%s",
												LFS_INF_CAM_CAPABILITIES,
												GetStringSplitChar(),
												lpCaps->wClass,
												GetStringSplitChar(),
												lpCaps->fwType,
												GetStringSplitChar(),
												strCameras.c_str(),
												GetStringSplitChar(),
												lpCaps->usMaxPictures,
												GetStringSplitChar(),
												lpCaps->fwCamData,
												GetStringSplitChar(),
												lpCaps->usMaxDataLength,
												GetStringSplitChar(),
												lpCaps->fwCharSupport,
												GetStringSplitChar(),
												(NULL == lpCaps->lpszExtra ? "NULL" : FormatExtra(lpCaps->lpszExtra)));
	}

	return strWfsResult;
}
