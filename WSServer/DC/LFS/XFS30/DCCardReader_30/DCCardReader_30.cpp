// DCCardReader.cpp: implementation of the CDCCardReader class.
//
//////////////////////////////////////////////////////////////////////

#include "DCCardReader_30.h"
#include "../../../include/JavaScriptStringParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDCCardReader_30::CDCCardReader_30(LPCTSTR strDCName, LPCTSTR strTraceComponent)
{
	m_strDCName = strDCName;
	m_strTraceComponent = CString(strTraceComponent);
	m_DCObject.m_bWosaXFSRun = FALSE;
}

CDCCardReader_30::~CDCCardReader_30()
{

}

HRESULT CDCCardReader_30::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// 调用命令
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_IDC_EJECT_CARD"))
	{
		bValid = TRUE;
		hResult = CMD_IDC_EJECT_CARD();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_IDC_RETAIN_CARD"))
	{
		bValid = TRUE;
		hResult = CMD_IDC_RETAIN_CARD();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_IDC_RESET_COUNT"))
	{
		bValid = TRUE;
		hResult = CMD_IDC_RESET_COUNT();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_IDC_READ_RAW_DATA"))
	{
		bValid = TRUE;
		hResult = CMD_IDC_READ_RAW_DATA(atol(CJSStringParam::GetStringParam(strarrParams, "lpwreaddata").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_IDC_WRITE_RAW_DATA"))
	{
		bValid = TRUE;
		hResult = CMD_IDC_WRITE_RAW_DATA(atol(CJSStringParam::GetStringParam(strarrParams, "wdatasource").c_str()),
										CJSStringParam::GetStringParam(strarrParams, "lpbdata").c_str(),
										atol(CJSStringParam::GetStringParam(strarrParams, "fwwritemethod").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_IDC_CHIP_IO"))
	{
		bValid = TRUE;
		hResult = CMD_IDC_CHIP_IO(atol(CJSStringParam::GetStringParam(strarrParams, "wchipprotocol").c_str()),
									CJSStringParam::GetStringParam(strarrParams, "lpbchipdata").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_IDC_RESET"))
	{
		bValid = TRUE;
		hResult = CMD_IDC_RESET(atol(CJSStringParam::GetStringParam(strarrParams, "lpwresetin").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_IDC_CHIP_POWER"))
	{
		bValid = TRUE;
		hResult = CMD_IDC_CHIP_POWER(atol(CJSStringParam::GetStringParam(strarrParams, "lpwchippower").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_INF_IDC_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_IDC_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_IDC_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_IDC_CAPABILITIES();
	}

	return hResult;
}

CString	CDCCardReader_30::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[]={
		{"WFS_CMD_IDC_READ_TRACK"				,IDC_SERVICE_OFFSET + 1},
		{"WFS_CMD_IDC_WRITE_TRACK"				,IDC_SERVICE_OFFSET + 2},
		{"WFS_CMD_IDC_EJECT_CARD"				,IDC_SERVICE_OFFSET + 3},
		{"WFS_CMD_IDC_RETAIN_CARD"				,IDC_SERVICE_OFFSET + 4},
		{"WFS_CMD_IDC_RESET_COUNT"				,IDC_SERVICE_OFFSET + 5},
		{"WFS_CMD_IDC_SETKEY"					,IDC_SERVICE_OFFSET + 6},
		{"WFS_CMD_IDC_READ_RAW_DATA"			,IDC_SERVICE_OFFSET + 7},
		{"WFS_CMD_IDC_WRITE_RAW_DATA"			,IDC_SERVICE_OFFSET + 8},
		{"WFS_CMD_IDC_CHIP_IO"					,IDC_SERVICE_OFFSET + 9},
		{"WFS_CMD_IDC_RESET"					,IDC_SERVICE_OFFSET + 10},
		{"WFS_CMD_IDC_CHIP_POWER"				,IDC_SERVICE_OFFSET + 11},
		{"WFS_CMD_IDC_PARSE_DATA"				,IDC_SERVICE_OFFSET + 12}
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

CString	CDCCardReader_30::GetXFSMsgStr(DWORD dwEventID)
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

		{"WFS_EXEE_IDC_INVALIDTRACKDATA"       ,(IDC_SERVICE_OFFSET + 1)},
		{"WFS_EXEE_IDC_MEDIAINSERTED"          ,(IDC_SERVICE_OFFSET + 3)},
		{"WFS_SRVE_IDC_MEDIAREMOVED"           ,(IDC_SERVICE_OFFSET + 4)},
		{"WFS_SRVE_IDC_CARDACTION"             ,(IDC_SERVICE_OFFSET + 5)},
		{"WFS_USRE_IDC_RETAINBINTHRESHOLD"     ,(IDC_SERVICE_OFFSET + 6)},
		{"WFS_EXEE_IDC_INVALIDMEDIA"           ,(IDC_SERVICE_OFFSET + 7)},
		{"WFS_EXEE_IDC_MEDIARETAINED"          ,(IDC_SERVICE_OFFSET + 8)},
		{"WFS_SRVE_IDC_MEDIADETECTED"          ,(IDC_SERVICE_OFFSET + 9)}
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

CString	CDCCardReader_30::GetXFSSysEvtStr(DWORD dwEventID)
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
	CString strRes="UNKNOWN EVT";
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

CString	CDCCardReader_30::GetXFSErrStr(HRESULT hResult)
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
		{"WFS_ERR_IDC_MEDIAJAM"						,-(IDC_SERVICE_OFFSET + 0)},
		{"WFS_ERR_IDC_NOMEDIA"						,-(IDC_SERVICE_OFFSET + 1)},
		{"WFS_ERR_IDC_MEDIARETAINED"				,-(IDC_SERVICE_OFFSET + 2)},
		{"WFS_ERR_IDC_RETAINBINFULL"				,-(IDC_SERVICE_OFFSET + 3)},
		{"WFS_ERR_IDC_INVALIDDATA"					,-(IDC_SERVICE_OFFSET + 4)},
		{"WFS_ERR_IDC_INVALIDMEDIA"					,-(IDC_SERVICE_OFFSET + 5)},
		{"WFS_ERR_IDC_FORMNOTFOUND"					,-(IDC_SERVICE_OFFSET + 6)},
		{"WFS_ERR_IDC_FORMINVALID"					,-(IDC_SERVICE_OFFSET + 7)},
		{"WFS_ERR_IDC_DATASYNTAX"					,-(IDC_SERVICE_OFFSET + 8)},
		{"WFS_ERR_IDC_SHUTTERFAIL"					,-(IDC_SERVICE_OFFSET + 9)},
		{"WFS_ERR_IDC_SECURITYFAIL"					,-(IDC_SERVICE_OFFSET + 10)},
		{"WFS_ERR_IDC_PROTOCOLNOTSUPP"				,-(IDC_SERVICE_OFFSET + 11)},
		{"WFS_ERR_IDC_ATRNOTOBTAINED"				,-(IDC_SERVICE_OFFSET + 12)},
		{"WFS_ERR_IDC_INVALIDKEY"					,-(IDC_SERVICE_OFFSET + 13)},
		{"WFS_ERR_IDC_WRITE_METHOD"					,-(IDC_SERVICE_OFFSET + 14)},
		{"WFS_ERR_IDC_CHIPPOWERNOTSUPP"				,-(IDC_SERVICE_OFFSET + 15)},
		{"WFS_ERR_IDC_CARDTOOSHORT"					,-(IDC_SERVICE_OFFSET + 16)},
		{"WFS_ERR_IDC_CARDTOOLONG"					,-(IDC_SERVICE_OFFSET + 17)}
	};

	CString strRes="UNKNOWN ERR";

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

int CDCCardReader_30::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			printf("LFS_OPEN_COMPLETE CDCCardReader_30\n");
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
		CString strWfsResult2Trace = strWfsResult;

		// 流水文件中记录数据，屏蔽卡磁道数据：一二三磁道
		for (int nLoop = 0; nLoop < 3; nLoop ++)
		{
			char szFlag[64] = {0};
			sprintf(szFlag, "wfsresult.lpbuffer[%d].lpbdata=", nLoop);
			if (-1 != strWfsResult2Trace.find(szFlag))
			{
				CString strTrack = "";
				CString strTrackNew = "";
				CString strCardNum = "";
				CString strCardNumNew = "";
				int nTrackStart = strWfsResult2Trace.find(szFlag) + strlen(szFlag);
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

					strTrackNew = string(strTrackNew.c_str()) + strCardNumNew;
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
						strTrackNew = string(strTrackNew.c_str()) + "*";
					}
				}

				if (strTrack.length() > 0 && strTrackNew.length() > 0)
				{
					char szSource[1024] = { 0 };
					sprintf(szSource, "%s%s", szFlag, strTrack.c_str());

					char szDest[1024] = { 0 };
					sprintf(szDest, "%s%s", szFlag, strTrackNew.c_str());

					// strWfsResult2Trace.Replace(strSource, strDest);
					strWfsResult2Trace = replace_all_distinct(strWfsResult2Trace, string(szSource), string(szDest));
				}
			}
		}

		CString strTrace(strWfsResult2Trace.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s",
			uMsg, GetXFSMsgStr(uMsg).c_str(), strWfsResult2Trace.c_str());
		WriteTrace(m_strTraceComponent.c_str(), OCXEVENT, strTrace.c_str());

		FireDCEvent(m_strDCName, uMsg, strWfsResult);
	}

	printf("dbus message 4\n");
    return 0L;
}

CString CDCCardReader_30::HandleCmdErr(LPLFSRESULT lpWfsRet)
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

CString CDCCardReader_30::HandleCmdResult(LPLFSRESULT lpWfsRet)
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
		case LFS_CMD_IDC_READ_RAW_DATA:
		{
			LPLFSIDCCARDDATA * lppCardData = NULL;
			lppCardData = (LPLFSIDCCARDDATA *)lpWfsRet->buffer;

			if (NULL != lppCardData)
			{
				char * pszTrack = NULL;

				for (int nLoop = 0; NULL != lppCardData[nLoop]; nLoop ++)
				{
					pszTrack = NULL;

					if ((lppCardData[nLoop]->data_length > 0 && NULL != lppCardData[nLoop]->data)
						&& lppCardData[nLoop]->data_length < 2 * 1024 * 1024)
					{
						if (LFS_IDC_CHIP == lppCardData[nLoop]->data_source
							&& lppCardData[nLoop]->data_length < 128)
						{
							pszTrack = new char[lppCardData[nLoop]->data_length * 2 + 2];
							memset(pszTrack, 0, lppCardData[nLoop]->data_length * 2 + 2);

							m_Utils.HextoStr(lppCardData[nLoop]->data, (short)lppCardData[nLoop]->data_length, pszTrack);
						}
						else
						{
							pszTrack = new char[lppCardData[nLoop]->data_length + 2];
							memset(pszTrack, 0, lppCardData[nLoop]->data_length + 2);
							memcpy(pszTrack, lppCardData[nLoop]->data, lppCardData[nLoop]->data_length);
						}
					}

					CString strCardData((NULL == pszTrack ? 0 : strlen(pszTrack)) + 1024, 0);
					sprintf((char *)strCardData.c_str(),
											"%s"
											"wfsresult.lpbuffer[%d].wdatasource=%d"
											"%s"
											"wfsresult.lpbuffer[%d].wstatus=%d"
											"%s"
											"wfsresult.lpbuffer[%d].uldatalength=%d"
											"%s"
											"wfsresult.lpbuffer[%d].lpbdata=%s",
											GetStringSplitChar(),
											nLoop, lppCardData[nLoop]->data_source,
											GetStringSplitChar(),
											nLoop, lppCardData[nLoop]->status,
											GetStringSplitChar(),
											nLoop, lppCardData[nLoop]->data_length,
											GetStringSplitChar(),
											nLoop, (NULL == pszTrack ? "NULL" : pszTrack));
					strCmdResult = string(strCmdResult.c_str()) + strCardData;

					delete[] pszTrack;
					pszTrack = NULL;
				}
			}

			break ;
		}
		case LFS_CMD_IDC_CHIP_IO:
		{
			char achHexStr[2048] = {0};

			LPLFSIDCCHIPIO lpChipData = (LPLFSIDCCHIPIO)lpWfsRet->buffer;
			if (NULL != lpChipData)
			{
				if (NULL != lpChipData->chip_data)
				{
					m_Utils.HextoStr(lpChipData->chip_data, (SHORT)lpChipData->chip_data_length, achHexStr);

					strCmdResult = CString(strlen(achHexStr) + 1024, 0);
					sprintf((char *)strCmdResult.c_str(),
										"%s"
										"wfsresult.lpbuffer.wchipprotocol=%d"
										"%s"
										"wfsresult.lpbuffer.ulchipdatalength=%d"
										"%s"
										"wfsresult.lpbuffer.lpbchipdata=%s",
										GetStringSplitChar(),
										lpChipData->chip_protocol,
										GetStringSplitChar(),
										lpChipData->chip_data_length,
										GetStringSplitChar(),
										achHexStr);
				}
			}

			break ;
		}
		case LFS_CMD_IDC_READ_TRACK:
		case LFS_CMD_IDC_WRITE_TRACK:
		case LFS_CMD_IDC_EJECT_CARD:
		case LFS_CMD_IDC_RETAIN_CARD:
		case LFS_CMD_IDC_RESET_COUNT:
		case LFS_CMD_IDC_SETKEY:
		case LFS_CMD_IDC_WRITE_RAW_DATA:
		case LFS_CMD_IDC_RESET:
		case LFS_CMD_IDC_CHIP_POWER:
		case LFS_CMD_IDC_PARSE_DATA:
			break ;
		default:
			break;
	}

	if ("" != strCmdResult)
	{
		strWfsResult = string(strWfsResult.c_str()) + strCmdResult;
	}

	return strWfsResult;
}

CString CDCCardReader_30::HandleEXEEvtResult(LPLFSRESULT lpWfsRet)
{
	/*
	#define     LFS_EXEE_IDC_INVALIDTRACKDATA       (IDC_SERVICE_OFFSET + 1)
	#define     LFS_EXEE_IDC_MEDIAINSERTED          (IDC_SERVICE_OFFSET + 3)
	#define     LFS_EXEE_IDC_INVALIDMEDIA           (IDC_SERVICE_OFFSET + 7)
	#define     LFS_EXEE_IDC_MEDIARETAINED          (IDC_SERVICE_OFFSET + 8)
	*/

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

CString CDCCardReader_30::HandleSRVEvtResult(LPLFSRESULT lpWfsRet)
{
	/*
	#define     LFS_SRVE_IDC_MEDIAREMOVED           (IDC_SERVICE_OFFSET + 4)
	#define     LFS_SRVE_IDC_CARDACTION             (IDC_SERVICE_OFFSET + 5)
	#define     LFS_SRVE_IDC_MEDIADETECTED          (IDC_SERVICE_OFFSET + 9)
	*/

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

CString CDCCardReader_30::HandleSysEvtResult(LPLFSRESULT lpWfsRet)
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

CString CDCCardReader_30::HandleUSEREvtResult(LPLFSRESULT lpWfsRet)
{
	/*
	#define     LFS_USRE_IDC_RETAINBINTHRESHOLD     (IDC_SERVICE_OFFSET + 6)
	*/

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

HRESULT CDCCardReader_30::CMD_IDC_READ_RAW_DATA(long lReadData)
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_IDC_READ_RAW_DATA,
								&lReadData,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCardReader_30::CMD_IDC_WRITE_RAW_DATA(long lDataSource, LPCTSTR strTrackData, long lWriteMode)
{
	HRESULT hResult = DC_ERROR;

	LFSIDCCARDDATA * lpCardData = NULL;
	LPLFSIDCCARDDATA lppCardData[2] = {NULL, NULL};
	lppCardData[0] = lpCardData;
	lppCardData[1] = NULL;

	// hResult = WFMAllocateBuffer(sizeof(LFSIDCCARDDATA), LFS_MEM_ZEROINIT, (void**)(&lpCardData));
	lpCardData = new LFSIDCCARDDATA();
	memset(&lpCardData, 0, sizeof(LFSIDCCARDDATA));
	hResult = LFS_SUCCESS;

	if (hResult == LFS_SUCCESS)
	{
		lpCardData->data_source = (USHORT)lDataSource;
		lpCardData->data_length = strlen(strTrackData);

		// hResult = WFMAllocateMore(lpCardData->data_length, lpCardData, (void**)(&lpCardData->data));
		lpCardData->data = new BYTE[lpCardData->data_length];
		memset(lpCardData->data, 0, lpCardData->data_length);
		hResult = LFS_SUCCESS;

		if (hResult == LFS_SUCCESS)
		{
			memset(lpCardData->data, 0, lpCardData->data_length);
			memcpy(lpCardData->data, (LPBYTE)strTrackData, lpCardData->data_length);
			lpCardData->write_method = (USHORT)lWriteMode;

			hResult = LFSAsyncExecute(	m_DCObject.m_hService,
										LFS_CMD_IDC_WRITE_RAW_DATA,
										lppCardData,
										LFS_INDEFINITE_WAIT,
										(char *)m_strDBusPath.c_str(),
										&m_RequestID);
		}

		// WFMFreeBuffer(lpCardData->data);
		delete[] lpCardData->data;
	}

	// WFMFreeBuffer(lpCardData);
	delete lpCardData;

	return hResult;
}

HRESULT CDCCardReader_30::CMD_IDC_CHIP_IO(long lProtocol, LPCTSTR strBytesHex) 
{
	HRESULT hResult = DC_ERROR;
	if (NULL == strBytesHex || 0 == strlen(strBytesHex))
	{
		return DC_ERROR;
	}

	int nLenBytes = strlen(strBytesHex) / 2;

	LPLFSIDCCHIPIO ChipIO = new LFSIDCCHIPIO();
	memset(ChipIO, 0, sizeof(LFSIDCCHIPIO));

	ChipIO->chip_data = new BYTE[nLenBytes];
	memset(ChipIO->chip_data, 0, nLenBytes);

	m_Utils.StrtoHex((PCHAR)strBytesHex, ChipIO->chip_data);
	ChipIO->chip_data_length = nLenBytes;
	ChipIO->chip_protocol = (WORD)lProtocol;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_IDC_CHIP_IO,
								ChipIO,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);
	
	delete[] ChipIO->chip_data;
	delete ChipIO;
	
	return hResult;
}

HRESULT CDCCardReader_30::CMD_IDC_RESET(long lResetIn)
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_IDC_RESET,
								&lResetIn,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCardReader_30::CMD_IDC_CHIP_POWER(long lChipPower)
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_IDC_CHIP_POWER,
								&lChipPower,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCardReader_30::INF_IDC_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_IDC_CAPABILITIES,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCCardReader_30::INF_IDC_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_IDC_STATUS,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

CString CDCCardReader_30::HandleInfResult(LPLFSRESULT lpWfsRet)
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

	if (LFS_INF_IDC_STATUS == lpWfsRet->u.command_code)
	{
		LPLFSIDCSTATUS lpStatus = (LPLFSIDCSTATUS)lpWfsRet->buffer;
		if (NULL == lpStatus)
		{
			return strWfsResult;
		}

		strWfsResult = string((NULL == lpStatus->extra ? 0 : strlen(lpStatus->extra)) + 1024, 0);
		sprintf((char *)strWfsResult.c_str(),
			"wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.fwdevice=%d"
			"%s"
			"wfsresult.lpbuffer.fwmedia=%d"
			"%s"
			"wfsresult.lpbuffer.fwretainbin=%d"
			"%s"
			"wfsresult.lpbuffer.fwsecurity=%d"
			"%s"
			"wfsresult.lpbuffer.uscards=%d"
			"%s"
			"wfsresult.lpbuffer.fwchippower=%d"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_IDC_STATUS,
			GetStringSplitChar(),
			lpStatus->device,
			GetStringSplitChar(),
			lpStatus->media,
			GetStringSplitChar(),
			lpStatus->retain_bin,
			GetStringSplitChar(),
			lpStatus->security,
			GetStringSplitChar(),
			lpStatus->cards,
			GetStringSplitChar(),
			lpStatus->chip_power,
			GetStringSplitChar(),
			(NULL == lpStatus->extra ? "NULL" : lpStatus->extra));
	}
	else if (LFS_INF_IDC_CAPABILITIES == lpWfsRet->u.command_code)
	{
		LPLFSIDCCAPS lpCaps = (LPLFSIDCCAPS)lpWfsRet->buffer;
		if (NULL == lpCaps)
		{
			return strWfsResult;
		}

		strWfsResult = string((NULL == lpCaps->extra ? 0 : strlen(lpCaps->extra)) + 1024, 0);
		sprintf((char *)strWfsResult.c_str(),
			"wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.wclass=%d"
			"%s"
			"wfsresult.lpbuffer.fwtype=%d"
			"%s"
			"wfsresult.lpbuffer.bcompound=%s"
			"%s"
			"wfsresult.lpbuffer.fwreadtracks=%d"
			"%s"
			"wfsresult.lpbuffer.fwwritetracks=%d"
			"%s"
			"wfsresult.lpbuffer.fwchipprotocols=%d"
			"%s"
			"wfsresult.lpbuffer.uscards=%d"
			"%s"
			"wfsresult.lpbuffer.fwsectype=%d"
			"%s"
			"wfsresult.lpbuffer.fwpoweronoption=%d"
			"%s"
			"wfsresult.lpbuffer.fwpoweroffoption=%d"
			"%s"
			"wfsresult.lpbuffer.bfluxsensorprogrammable=%s"
			"%s"
			"wfsresult.lpbuffer.breadwriteaccessfollowingeject=%s"
			"%s"
			"wfsresult.lpbuffer.fwwritemode=%d"
			"%s"
			"wfsresult.lpbuffer.fwchippower=%d"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_IDC_CAPABILITIES,
			GetStringSplitChar(),
			lpCaps->dev_class,
			GetStringSplitChar(),
			lpCaps->dev_type,
			GetStringSplitChar(),
			lpCaps->compound ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->read_tracks,
			GetStringSplitChar(),
			lpCaps->write_tracks,
			GetStringSplitChar(),
			lpCaps->chip_protocols,
			GetStringSplitChar(),
			lpCaps->cards,
			GetStringSplitChar(),
			lpCaps->sec_type,
			GetStringSplitChar(),
			lpCaps->power_on_option,
			GetStringSplitChar(),
			lpCaps->power_off_option,
			GetStringSplitChar(),
			lpCaps->flux_sensor_programmable ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->read_write_access_following_eject ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->write_mode,
			GetStringSplitChar(),
			lpCaps->chip_power,
			GetStringSplitChar(),
			(NULL == lpCaps->extra ? "NULL" : lpCaps->extra));
	}
	
	return strWfsResult;
}

HRESULT CDCCardReader_30::CMD_IDC_EJECT_CARD() 
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_IDC_EJECT_CARD,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCardReader_30::CMD_IDC_RETAIN_CARD()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_IDC_RETAIN_CARD,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCardReader_30::CMD_IDC_RESET_COUNT() 
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_IDC_RESET_COUNT,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}