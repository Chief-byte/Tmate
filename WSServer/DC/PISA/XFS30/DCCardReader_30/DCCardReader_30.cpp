// DCCardReader.cpp: implementation of the CDCCardReader class.
//
//////////////////////////////////////////////////////////////////////

#include "DCCardReader_30.h"
// #include "JavaScriptStringParam.h"
#include "JavaScriptStringParam.h"

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
	// ��������
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
	if (FALSE == m_DCObject.m_bWosaXFSRun && LFS_OPEN_COMPLETE != uMsg)  // �첽��ģ��ʱ���᷵��ģ��򿪳ɹ��¼�
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

		// ��ˮ�ļ��м�¼���ݣ����ο��ŵ����ݣ�һ�����ŵ�
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

				if (strlen(strCardNum.c_str()) > 12)
				{
					strCardNumNew = strCardNum.substr(0, strlen(strCardNum.c_str()) - 5)
									+ "****"
									+ strCardNum.substr(strlen(strCardNum.c_str()) - 1, 1);

					strTrackNew = string(strTrackNew.c_str()) + strCardNumNew;
				}

				if (-1 != nTrackEnd)
				{
					strTrack = strWfsResult2Trace.substr(nTrackStart, nTrackEnd - nTrackStart);
				}
				else
				{
					strTrack = strWfsResult2Trace.substr(nTrackStart, strlen(strWfsResult2Trace.c_str()) - nTrackStart);
				}

				if (strlen(strTrack.c_str()) > 0 && strlen(strTrack.c_str()) > strlen(strCardNum.c_str()))
				{
					for (int nLoop = 0; nLoop < strlen(strTrack.c_str()) - strlen(strCardNum.c_str()); nLoop ++)
					{
						strTrackNew = string(strTrackNew.c_str()) + "*";
					}
				}

				if (strlen(strTrack.c_str()) > 0 && strlen(strTrackNew.c_str()) > 0)
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

		CString strTrace(strlen(strWfsResult2Trace.c_str()) + 256, 0);
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
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwCommand_Code);
	return strWfsResult;
}

CString CDCCardReader_30::HandleCmdResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	if (LFS_SUCCESS != lpWfsRet->hResult)
	{
		return HandleCmdErr(lpWfsRet);
	}
	
	CString strTrace;
	
	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(),
						"wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dwcommandcode=%d",
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwCommand_Code);
	
	CString strCmdResult = "";

	switch (lpWfsRet->u.dwCommand_Code)
	{
		case LFS_CMD_IDC_READ_RAW_DATA:
		{
			LPLFSIDCCARDDATA * lppCardData = NULL;
			lppCardData = (LPLFSIDCCARDDATA *)lpWfsRet->lpvdBuffer;

			if (NULL != lppCardData)
			{
				char * pszTrack = NULL;

				for (int nLoop = 0; NULL != lppCardData[nLoop]; nLoop ++)
				{
					pszTrack = NULL;

					if ((lppCardData[nLoop]->ulData_Length > 0 && NULL != lppCardData[nLoop]->lpbData)
						&& lppCardData[nLoop]->ulData_Length < 2 * 1024 * 1024)
					{
						if (LFS_IDC_CHIP == lppCardData[nLoop]->wData_Source
							// && lppCardData[nLoop]->ulData_Length < 128)  // 20250620 �е���ڻ���LFS_IDC_CHIP�����˳���Ϊ512
							&& lppCardData[nLoop]->ulData_Length < 8 * 1024)
						{
							pszTrack = new char[lppCardData[nLoop]->ulData_Length * 2 + 2];
							memset(pszTrack, 0, lppCardData[nLoop]->ulData_Length * 2 + 2);

							m_Utils.HextoStr(lppCardData[nLoop]->lpbData, (short)lppCardData[nLoop]->ulData_Length, pszTrack);
						}
						else
						{
							pszTrack = new char[lppCardData[nLoop]->ulData_Length + 2];
							memset(pszTrack, 0, lppCardData[nLoop]->ulData_Length + 2);
							memcpy(pszTrack, lppCardData[nLoop]->lpbData, lppCardData[nLoop]->ulData_Length);
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
											nLoop, lppCardData[nLoop]->wData_Source,
											GetStringSplitChar(),
											nLoop, lppCardData[nLoop]->wStatus,
											GetStringSplitChar(),
											nLoop, lppCardData[nLoop]->ulData_Length,
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

			LPLFSIDCCHIPIO lpChipData = (LPLFSIDCCHIPIO)lpWfsRet->lpvdBuffer;
			if (NULL != lpChipData)
			{
				if (NULL != lpChipData->lpbChip_Data)
				{
					m_Utils.HextoStr(lpChipData->lpbChip_Data, (SHORT)lpChipData->ulChip_Data_Length, achHexStr);

					strCmdResult = CString(strlen(achHexStr) + 1024, 0);
					sprintf((char *)strCmdResult.c_str(),
										"%s"
										"wfsresult.lpbuffer.wchipprotocol=%d"
										"%s"
										"wfsresult.lpbuffer.ulchipdatalength=%d"
										"%s"
										"wfsresult.lpbuffer.lpbchipdata=%s",
										GetStringSplitChar(),
										lpChipData->wChip_Protocol,
										GetStringSplitChar(),
										lpChipData->ulChip_Data_Length,
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
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEvent_ID);

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
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEvent_ID);

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
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEvent_ID);

	CString strSysEvent = "";

	switch(lpWfsRet->u.dwEvent_ID)
	{
		case LFS_SYSE_DEVICE_STATUS:
		{
			LPLFSDEVSTATUS lpDevStatus = (LPLFSDEVSTATUS)lpWfsRet->lpvdBuffer;
			if (NULL == lpDevStatus)
			{
				break ;
			}

			strSysEvent = CString((NULL == lpDevStatus->lpstrPhysical_Name ? 0 : strlen(lpDevStatus->lpstrPhysical_Name))
								+ (NULL == lpDevStatus->lpstrWorkstation_Name ? 0 : strlen(lpDevStatus->lpstrWorkstation_Name)) + 1024, 0);
			sprintf((char *)strSysEvent.c_str(), 	"%s"
								"wfsresult.lpbuffer.lpszphysicalname=%s"
								"%s"
								"wfsresult.lpbuffer.lpszworkstationname=%s"
								"%s"
								"wfsresult.lpbuffer.dwState=%d",
								GetStringSplitChar(),
								(NULL == lpDevStatus->lpstrPhysical_Name ? "NULL" : lpDevStatus->lpstrPhysical_Name),
								GetStringSplitChar(),
								(NULL == lpDevStatus->lpstrWorkstation_Name ? "NULL" : lpDevStatus->lpstrWorkstation_Name),
								GetStringSplitChar(),
								lpDevStatus->dwState);
			break ;
		}
		case LFS_SYSE_HARDWARE_ERROR:
		case LFS_SYSE_SOFTWARE_ERROR:
		case LFS_SYSE_USER_ERROR:
		{
			LPLFSHWERROR lpWfsHwError = (LPLFSHWERROR)lpWfsRet->lpvdBuffer; 
			if (NULL == lpWfsHwError)
			{
				break ;
			}

			if (lpWfsHwError->dwSize > 0 && NULL != lpWfsHwError->lpbDescription)
			{
				strSysEvent = CString((NULL == lpWfsHwError->lpstrLogical_Name ? 0 : strlen(lpWfsHwError->lpstrLogical_Name))
									+ (NULL == lpWfsHwError->lpstrPhysical_Name ? 0 : strlen(lpWfsHwError->lpstrPhysical_Name))
									+ (NULL == lpWfsHwError->lpstrWorkstation_Name ? 0 : strlen(lpWfsHwError->lpstrWorkstation_Name))
									+ (NULL == lpWfsHwError->lpstrApp_ID ? 0 : strlen(lpWfsHwError->lpstrApp_ID))
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
									"wfsresult.lpbuffer.dwaction=%d"
									"%s"
									"wfsresult.lpbuffer.dwsize=%d"
									"%s"
									"wfsresult.lpbuffer.lpbdescription=%s",
									GetStringSplitChar(),
									(NULL == lpWfsHwError->lpstrLogical_Name ? "NULL" : lpWfsHwError->lpstrLogical_Name),
									GetStringSplitChar(),
									(NULL == lpWfsHwError->lpstrPhysical_Name ? "NULL" : lpWfsHwError->lpstrPhysical_Name),
									GetStringSplitChar(),
									(NULL == lpWfsHwError->lpstrWorkstation_Name ? "NULL" : lpWfsHwError->lpstrWorkstation_Name),
									GetStringSplitChar(),
									(NULL == lpWfsHwError->lpstrApp_ID ? "NULL" : lpWfsHwError->lpstrApp_ID),
									GetStringSplitChar(),
									lpWfsHwError->dwAction,
									GetStringSplitChar(),
									lpWfsHwError->dwSize,
									GetStringSplitChar(),
									CString((LPCSTR)lpWfsHwError->lpbDescription, lpWfsHwError->dwSize).c_str());
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
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEvent_ID);

	return strWfsResult;
}

HRESULT CDCCardReader_30::CMD_IDC_READ_RAW_DATA(long lReadData)
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_IDC_READ_RAW_DATA,
								&lReadData,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
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
		lpCardData->wData_Source = (USHORT)lDataSource;
		lpCardData->ulData_Length = strlen(strTrackData);

		// hResult = WFMAllocateMore(lpCardData->ulData_Length, lpCardData, (void**)(&lpCardData->lpbData));
		lpCardData->lpbData = new BYTE[lpCardData->ulData_Length];
		memset(lpCardData->lpbData, 0, lpCardData->ulData_Length);
		hResult = LFS_SUCCESS;

		if (hResult == LFS_SUCCESS)
		{
			memset(lpCardData->lpbData, 0, lpCardData->ulData_Length);
			memcpy(lpCardData->lpbData, (LPBYTE)strTrackData, lpCardData->ulData_Length);
			lpCardData->wWrite_Method = (USHORT)lWriteMode;

			hResult = LFSAsyncExecute(	m_DCObject.m_hService,
										LFS_CMD_IDC_WRITE_RAW_DATA,
										lppCardData,
										LFS_INDEFINITE_WAIT,
										(char *)m_strDCName.c_str(),
										&m_RequestID);
		}

		// WFMFreeBuffer(lpCardData->lpbData);
		delete[] lpCardData->lpbData;
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

	ChipIO->lpbChip_Data = new BYTE[nLenBytes];
	memset(ChipIO->lpbChip_Data, 0, nLenBytes);

	m_Utils.StrtoHex((PCHAR)strBytesHex, ChipIO->lpbChip_Data);
	ChipIO->ulChip_Data_Length = nLenBytes;
	ChipIO->wChip_Protocol = (WORD)lProtocol;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_IDC_CHIP_IO,
								ChipIO,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);
	
	delete[] ChipIO->lpbChip_Data;
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
								(char *)m_strDCName.c_str(),
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
								(char *)m_strDCName.c_str(),
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
								(char *)m_strDCName.c_str(),
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
								(char *)m_strDCName.c_str(),
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
		lpWfsRet->hResult,
		GetStringSplitChar(),
		lpWfsRet->u.dwCommand_Code);

	if (LFS_SUCCESS != lpWfsRet->hResult)
	{
		return strWfsResult;
	}

	if (LFS_INF_IDC_STATUS == lpWfsRet->u.dwCommand_Code)
	{
		LPLFSIDCSTATUS lpStatus = (LPLFSIDCSTATUS)lpWfsRet->lpvdBuffer;
		if (NULL == lpStatus)
		{
			return strWfsResult;
		}

		strWfsResult = string((NULL == lpStatus->lpstrExtra ? 0 : strlen(lpStatus->lpstrExtra)) + 1024, 0);
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
			lpStatus->wDevice,
			GetStringSplitChar(),
			lpStatus->wMedia,
			GetStringSplitChar(),
			lpStatus->wRetain_Bin,
			GetStringSplitChar(),
			lpStatus->wSecurity,
			GetStringSplitChar(),
			lpStatus->usCards,
			GetStringSplitChar(),
			lpStatus->wChip_Power,
			GetStringSplitChar(),
			(NULL == lpStatus->lpstrExtra ? "NULL" : FormatExtra(lpStatus->lpstrExtra)));
	}
	else if (LFS_INF_IDC_CAPABILITIES == lpWfsRet->u.dwCommand_Code)
	{
		LPLFSIDCCAPS lpCaps = (LPLFSIDCCAPS)lpWfsRet->lpvdBuffer;
		if (NULL == lpCaps)
		{
			return strWfsResult;
		}

		strWfsResult = string((NULL == lpCaps->lpstrExtra ? 0 : strlen(lpCaps->lpstrExtra)) + 1024, 0);
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
			lpCaps->wClass,
			GetStringSplitChar(),
			lpCaps->wType,
			GetStringSplitChar(),
			lpCaps->bCompound ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->wRead_Tracks,
			GetStringSplitChar(),
			lpCaps->wWrite_Tracks,
			GetStringSplitChar(),
			lpCaps->wChip_Protocols,
			GetStringSplitChar(),
			lpCaps->usCards,
			GetStringSplitChar(),
			lpCaps->wSec_Type,
			GetStringSplitChar(),
			lpCaps->wPower_On_Option,
			GetStringSplitChar(),
			lpCaps->wPower_Off_Option,
			GetStringSplitChar(),
			lpCaps->bFlux_Sensor_Programmable ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->bRead_Write_Access_Following_Eject ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->wWrite_Mode,
			GetStringSplitChar(),
			lpCaps->wChip_Power,
			GetStringSplitChar(),
			(NULL == lpCaps->lpstrExtra ? "NULL" : FormatExtra(lpCaps->lpstrExtra)));
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
								(char *)m_strDCName.c_str(),
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
								(char *)m_strDCName.c_str(),
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
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}