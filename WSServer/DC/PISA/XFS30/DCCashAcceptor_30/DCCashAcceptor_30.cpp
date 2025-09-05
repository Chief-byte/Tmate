// DCCashAcceptor_30.cpp: implementation of the CDCCashAcceptor_30 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCCashAcceptor_30.h"
// #include "../../../include/JavaScriptStringParam.h"
#include "include/JavaScriptStringParam.h"
#include <unistd.h>

CDCCashAcceptor_30::CDCCashAcceptor_30(LPCTSTR strDCName, LPCTSTR strTraceComponent)
{
	m_strDCName = strDCName;
	m_strTraceComponent = CString(strTraceComponent);
	m_DCObject.m_bWosaXFSRun = FALSE;

	m_bCashUnitInfo4EndExchange = FALSE;
	m_lpResult4EndExchange = NULL;
}

CDCCashAcceptor_30::~CDCCashAcceptor_30()
{
}

HRESULT CDCCashAcceptor_30::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// 调用命令
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_CIM_CASH_IN_START"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_CASH_IN_START((short)atol(CJSStringParam::GetStringParam(strarrParams, "fwinputposition").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwoutputposition").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "buserecycleunits").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_CASH_IN"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_CASH_IN();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_CASH_IN_END"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_CASH_IN_END();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_CASH_IN_ROLLBACK"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_CASH_IN_ROLLBACK();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_RETRACT"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_RETRACT((short)atol(CJSStringParam::GetStringParam(strarrParams, "usretractarea").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "usindex").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwoutputposition").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_OPEN_SHUTTER"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_OPEN_SHUTTER((short)atol(CJSStringParam::GetStringParam(strarrParams, "lpfwposition").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_CLOSE_SHUTTER"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_CLOSE_SHUTTER((short)atol(CJSStringParam::GetStringParam(strarrParams, "lpfwposition").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_SET_TELLER_INFO"))
	{
		// 不使用此方法
		// bValid = TRUE;
		// hResult = CMD_CIM_SET_TELLER_INFO();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_SET_CASH_UNIT_INFO"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_SET_CASH_UNIT_INFO(CJSStringParam::GetStringParam(strarrParams, "cuinfo").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_START_EXCHANGE"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_START_EXCHANGE(strSingleParam.c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_END_EXCHANGE"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_END_EXCHANGE(strSingleParam.c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_OPEN_SAFE_DOOR"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_OPEN_SAFE_DOOR();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_RESET"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_RESET(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "usnumber").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwoutputposition").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "usretractarea").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "usindex").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwoutputposition_retract").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_CONFIGURE_CASH_IN_UNITS"))
	{
		// 不使用此方法
		// bValid = TRUE;
		// hResult = CMD_CIM_CONFIGURE_CASH_IN_UNITS(CJSStringParam::GetStringParam(strarrParams, "strCashInType").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_CONFIGURE_NOTETYPES"))
	{
		bValid = TRUE;
		// hResult = CMD_CIM_CONFIGURE_NOTETYPES(CJSStringParam::GetStringParam(strarrParams, "lpusnoteids").c_str());
		hResult = CMD_CIM_CONFIGURE_NOTETYPES(strSingleParam.c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_CREATE_P6_SIGNATURE"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_CREATE_P6_SIGNATURE();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_SET_CASH_IN_LIMIT"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_SET_CASH_IN_LIMIT(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "ultotalitemslimit").c_str()),
												CJSStringParam::GetStringParam(strarrParams, "ccurrencyid").c_str(),
												(short)atol(CJSStringParam::GetStringParam(strarrParams, "ulamount").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CIM_CASH_UNIT_COUNT"))
	{
		bValid = TRUE;
		hResult = CMD_CIM_CASH_UNIT_COUNT(CJSStringParam::GetStringParam(strarrParams, "cashunitnumbers").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CIM_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_CIM_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CIM_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_CIM_CAPABILITIES();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CIM_CASH_UNIT_INFO"))
	{
		bValid = TRUE;
		hResult = INF_CIM_CASH_UNIT_INFO();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CIM_TELLER_INFO"))
	{
		bValid = TRUE;
		hResult = INF_CIM_TELLER_INFO();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CIM_CURRENCY_EXP"))
	{
		bValid = TRUE;
		hResult = INF_CIM_CURRENCY_EXP();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CIM_BANKNOTE_TYPES"))
	{
		bValid = TRUE;
		hResult = INF_CIM_BANKNOTE_TYPES();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CIM_CASH_IN_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_CIM_CASH_IN_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CIM_GET_P6_INFO"))
	{
		bValid = TRUE;
		hResult = INF_CIM_GET_P6_INFO();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CIM_GET_P6_SIGNATURE"))
	{
		bValid = TRUE;
		hResult = INF_CIM_GET_P6_SIGNATURE();
	}

	return hResult;
}

CString CDCCashAcceptor_30::HandleEXEEvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dweventid=%d",
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEvent_ID);

	CString strEvtResult;
	switch (lpWfsRet->u.dwEvent_ID)
	{
		case LFS_EXEE_CIM_CASHUNITERROR:
		{
			LPLFSCIMCUERROR lpCashUnitError = (LPLFSCIMCUERROR)lpWfsRet->lpvdBuffer;
			if (NULL != lpCashUnitError && NULL != lpCashUnitError->lpCash_Unit)
			{
				CString strCashUnit = GetCashInResultString(lpCashUnitError->lpCash_Unit);
				if ("" != strCashUnit)
				{
					// GetCashInResultString方法返回的字符串前缀是wfscimcashin，
					// 此处前缀应更改为：wfscimcuerror.lpcashunit
					char szPrefix[128] = { 0 };
					sprintf(szPrefix, "wfscimcuerror.lpcashunit");

					// strCashUnit.Replace("wfscimcashin", strPrefix);
					strCashUnit = replace_all_distinct(strCashUnit, "wfscimcashin", string(szPrefix));

					strEvtResult = CString(strlen(strCashUnit.c_str()) + 128, 0);
					sprintf((char *)strEvtResult.c_str(), 	"%s"
											"wfscimcuerror.wfailure=%d"
											"%s"
											"%s",
											GetStringSplitChar(),
											lpCashUnitError->wFailure,
											GetStringSplitChar(), 
											strCashUnit.c_str());
				}
			}

			break;
		}
		case LFS_EXEE_CIM_INPUTREFUSE:
		{
			LPUSHORT lpusReason = (LPUSHORT)lpWfsRet->lpvdBuffer;
			if (NULL != lpusReason)
			{
				strEvtResult = CString(128, 0);
				sprintf((char *)strEvtResult.c_str(), "%s"
									"wfsresult.lpbuffer=%d",
									GetStringSplitChar(), 
									* lpusReason);
			}

			break;
		}
		case LFS_EXEE_CIM_NOTEERROR:
		{
			LPUSHORT lpusReason = (LPUSHORT)lpWfsRet->lpvdBuffer;
			if (NULL != lpusReason)
			{
				strEvtResult = CString(128, 0);
				sprintf((char *)strEvtResult.c_str(), "%s"
									"wfsresult.lpbuffer=%d",
									GetStringSplitChar(), 
									* lpusReason);
			}

			break;
		}
		/*
		case LFS_EXEE_CIM_SUBCASHIN:
			// 一次存款分部分，这种情况在应用中不存在，不处理
			break;
		case LFS_EXEE_CIM_INPUT_P6:
			break;
		*/
		default:
			break;
	}

	strWfsResult = string(strWfsResult.c_str()) + strEvtResult;

	return strWfsResult;
}

CString CDCCashAcceptor_30::HandleUSEREvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dweventid=%d",
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEvent_ID);

	CString strEvtResult;

	switch(lpWfsRet->u.dwEvent_ID)
	{
		case LFS_USRE_CIM_CASHUNITTHRESHOLD:
		{
			LPLFSCIMCASHIN lpCashUnit = (LPLFSCIMCASHIN)lpWfsRet->lpvdBuffer;
			if (NULL != lpCashUnit)
			{
				strEvtResult = GetCashInResultString(lpCashUnit);
			}

			break;
		}
		default:
		{
			break;
		}
	}

	strWfsResult = string(strWfsResult.c_str()) + strEvtResult;

	return strWfsResult;
}

CString CDCCashAcceptor_30::HandleSRVEvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dweventid=%d",
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEvent_ID);

	CString strEvtResult;

	switch (lpWfsRet->u.dwEvent_ID)
	{
		case LFS_SRVE_CIM_SAFEDOOROPEN:
			break;
		case LFS_SRVE_CIM_SAFEDOORCLOSED:
			break;
		case LFS_SRVE_CIM_CASHUNITINFOCHANGED:
		{
			LPLFSCIMCASHIN lpCashIn = (LPLFSCIMCASHIN)lpWfsRet->lpvdBuffer;
			if (NULL != lpCashIn)
			{
				strEvtResult = GetCashInResultString(lpCashIn);
			}
			break;
		}
		case LFS_SRVE_CIM_TELLERINFOCHANGED:
			break;
		case LFS_SRVE_CIM_ITEMSTAKEN:
			break;
		case LFS_SRVE_CIM_COUNTS_CHANGED:
		{
			LPLFSCIMCOUNTSCHANGED lpCountsChanged = (LPLFSCIMCOUNTSCHANGED)lpWfsRet->lpvdBuffer;
			if (NULL == lpCountsChanged)
			{
				break ;
			}

			CString strCountsChanged(128, 0);
			sprintf((char *)strCountsChanged.c_str(), "%s"
									"wfsresult.lpbuffer.uscount=%d",
									GetStringSplitChar(),
									lpCountsChanged->usCount);

			if (NULL != lpCountsChanged->lpusCU_Num_List)
			{
				CString strCUNumList(128, 0);
				for (int nLoop = 0; nLoop < lpCountsChanged->usCount; nLoop ++)
				{
					sprintf((char *)strCUNumList.c_str(), "%s"
										"wfsresult.lpbuffer.lpuscunumlist[%d]=%d",
										GetStringSplitChar(),
										nLoop, lpCountsChanged->lpusCU_Num_List[nLoop]);
					strCountsChanged = string(strCountsChanged.c_str()) + strCUNumList;
				}
			}

			strEvtResult = strCountsChanged;

			break;
		}
		case LFS_SRVE_CIM_ITEMSPRESENTED:
			break;
		case LFS_SRVE_CIM_ITEMSINSERTED:
			break;
		case LFS_SRVE_CIM_MEDIADETECTED:
			break;
		default:
			break;
	}

	strWfsResult = string(strWfsResult.c_str()) + strEvtResult;

	return strWfsResult;
}

CString CDCCashAcceptor_30::HandleSysEvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
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

CString	CDCCashAcceptor_30::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[18] = {
		{"WFS_CMD_CIM_CASH_IN_START"           ,(CIM_SERVICE_OFFSET + 1)},
		{"WFS_CMD_CIM_CASH_IN"                 ,(CIM_SERVICE_OFFSET + 2)},
		{"WFS_CMD_CIM_CASH_IN_END"             ,(CIM_SERVICE_OFFSET + 3)},
		{"WFS_CMD_CIM_CASH_IN_ROLLBACK"        ,(CIM_SERVICE_OFFSET + 4)},
		{"WFS_CMD_CIM_RETRACT"                 ,(CIM_SERVICE_OFFSET + 5)},
		{"WFS_CMD_CIM_OPEN_SHUTTER"            ,(CIM_SERVICE_OFFSET + 6)},
		{"WFS_CMD_CIM_CLOSE_SHUTTER"           ,(CIM_SERVICE_OFFSET + 7)},
		{"WFS_CMD_CIM_SET_TELLER_INFO"         ,(CIM_SERVICE_OFFSET + 8)},
		{"WFS_CMD_CIM_SET_CASH_UNIT_INFO"      ,(CIM_SERVICE_OFFSET + 9)},
		{"WFS_CMD_CIM_START_EXCHANGE"          ,(CIM_SERVICE_OFFSET + 10)},
		{"WFS_CMD_CIM_END_EXCHANGE"            ,(CIM_SERVICE_OFFSET + 11)},
		{"WFS_CMD_CIM_OPEN_SAFE_DOOR"          ,(CIM_SERVICE_OFFSET + 12)},
		{"WFS_CMD_CIM_RESET"                   ,(CIM_SERVICE_OFFSET + 13)},
		{"WFS_CMD_CIM_CONFIGURE_CASH_IN_UNITS" ,(CIM_SERVICE_OFFSET + 14)},
		{"WFS_CMD_CIM_CONFIGURE_NOTETYPES"     ,(CIM_SERVICE_OFFSET + 15)},
		{"WFS_CMD_CIM_CREATE_P6_SIGNATURE"     ,(CIM_SERVICE_OFFSET + 16)},
		{"WFS_CMD_CIM_SET_CASH_IN_LIMIT"		,(CIM_SERVICE_OFFSET + 22)},
		{"WFS_CMD_CIM_CASH_UNIT_COUNT"			,(CIM_SERVICE_OFFSET + 23)}
	};
	CString strRes="UNKNOWN CMD";
	for( int i=0;i< 18;i++)
	{
		if( XFSCmd[i].iCmd==dwCmdCode )
		{
			strRes=XFSCmd[i].strCmd;
			break;
		}
	}
	return strRes;
}

CString	CDCCashAcceptor_30::GetXFSMsgStr(DWORD dwEventID)
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

		{"WFS_SRVE_CIM_SAFEDOOROPEN"           ,(CIM_SERVICE_OFFSET + 1)},
		{"WFS_SRVE_CIM_SAFEDOORCLOSED"         ,(CIM_SERVICE_OFFSET + 2)},
		{"WFS_USRE_CIM_CASHUNITTHRESHOLD"      ,(CIM_SERVICE_OFFSET + 3)},
		{"WFS_SRVE_CIM_CASHUNITINFOCHANGED"    ,(CIM_SERVICE_OFFSET + 4)},
		{"WFS_SRVE_CIM_TELLERINFOCHANGED"      ,(CIM_SERVICE_OFFSET + 5)},
		{"WFS_EXEE_CIM_CASHUNITERROR"          ,(CIM_SERVICE_OFFSET + 6)},
		{"WFS_SRVE_CIM_ITEMSTAKEN"             ,(CIM_SERVICE_OFFSET + 7)},
		{"WFS_SRVE_CIM_COUNTS_CHANGED"         ,(CIM_SERVICE_OFFSET + 8)},
		{"WFS_EXEE_CIM_INPUTREFUSE"            ,(CIM_SERVICE_OFFSET + 9)},
		{"WFS_SRVE_CIM_ITEMSPRESENTED"         ,(CIM_SERVICE_OFFSET + 10)},
		{"WFS_SRVE_CIM_ITEMSINSERTED"          ,(CIM_SERVICE_OFFSET + 11)},
		{"WFS_EXEE_CIM_NOTEERROR"              ,(CIM_SERVICE_OFFSET + 12)},
		{"WFS_EXEE_CIM_SUBCASHIN"              ,(CIM_SERVICE_OFFSET + 13)},
		{"WFS_SRVE_CIM_MEDIADETECTED"          ,(CIM_SERVICE_OFFSET + 14)},
		{"WFS_EXEE_CIM_INPUT_P6"               ,(CIM_SERVICE_OFFSET + 15)},
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

CString	CDCCashAcceptor_30::GetXFSSysEvtStr(DWORD dwEventID)
{
	struct XFSSYSEVT {
		char strSysEvt[128];
		DWORD iSysEvt;
	}XFSSysEvt[8]={
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
	for( int i=0;i<8;i++)
	{
		if( XFSSysEvt[i].iSysEvt==dwEventID )
		{
			strRes=XFSSysEvt[i].strSysEvt;
			break;
		}
	}
	return strRes;
}

CString	CDCCashAcceptor_30::GetXFSErrStr(HRESULT hResult)
{
	if (hResult >= DC_ERROR && hResult < LFS_ERR_UNSUPP_DATA)
	{
		return "DC_ERROR";
	}

	struct XFSERR {
		char strErr[128];
		LONG iErr;
	}XFSErr[77]={
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
		{"WFS_ERR_CIM_INVALIDCURRENCY"         ,(-(CIM_SERVICE_OFFSET + 0))},
		{"WFS_ERR_CIM_INVALIDTELLERID"         ,(-(CIM_SERVICE_OFFSET + 1))},
		{"WFS_ERR_CIM_CASHUNITERROR"           ,(-(CIM_SERVICE_OFFSET + 2))},
		{"WFS_ERR_CIM_TOOMANYITEMS"            ,(-(CIM_SERVICE_OFFSET + 7))},
		{"WFS_ERR_CIM_UNSUPPOSITION"           ,(-(CIM_SERVICE_OFFSET + 8))},
		{"WFS_ERR_CIM_SAFEDOOROPEN"            ,(-(CIM_SERVICE_OFFSET + 10))},
		{"WFS_ERR_CIM_SHUTTERNOTOPEN"          ,(-(CIM_SERVICE_OFFSET + 12))},
		{"WFS_ERR_CIM_SHUTTEROPEN"             ,(-(CIM_SERVICE_OFFSET + 13))},
		{"WFS_ERR_CIM_SHUTTERCLOSED"           ,(-(CIM_SERVICE_OFFSET + 14))},
		{"WFS_ERR_CIM_INVALIDCASHUNIT"         ,(-(CIM_SERVICE_OFFSET + 15))},
		{"WFS_ERR_CIM_NOITEMS"                 ,(-(CIM_SERVICE_OFFSET + 16))},
		{"WFS_ERR_CIM_EXCHANGEACTIVE"          ,(-(CIM_SERVICE_OFFSET + 17))},
		{"WFS_ERR_CIM_NOEXCHANGEACTIVE"        ,(-(CIM_SERVICE_OFFSET + 18))},
		{"WFS_ERR_CIM_SHUTTERNOTCLOSED"        ,(-(CIM_SERVICE_OFFSET + 19))},
		{"WFS_ERR_CIM_ITEMSTAKEN"              ,(-(CIM_SERVICE_OFFSET + 23))},
		{"WFS_ERR_CIM_CASHINACTIVE"            ,(-(CIM_SERVICE_OFFSET + 25))},
		{"WFS_ERR_CIM_NOCASHINACTIVE"          ,(-(CIM_SERVICE_OFFSET + 26))},
		{"WFS_ERR_CIM_POSITION_NOT_EMPTY"      ,(-(CIM_SERVICE_OFFSET + 28))},
		{"WFS_ERR_CIM_INVALIDRETRACTPOSITION"  ,(-(CIM_SERVICE_OFFSET + 34))},
		{"WFS_ERR_CIM_NOTRETRACTAREA"          ,(-(CIM_SERVICE_OFFSET + 35))}
	};

	CString strRes="UNKNOWN ERROR";

	for(int i=0;i<77;i++)
	{
		if( XFSErr[i].iErr==hResult )
		{
			strRes=XFSErr[i].strErr;
			break;
		}
	}
	return strRes;
}

CString CDCCashAcceptor_30::HandleCmdErr(LPLFSRESULT lpWfsRet)
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
						lpWfsRet->u.dwCommand_Code);
	return strWfsResult;
}

CString CDCCashAcceptor_30::HandleCmdResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	if (LFS_SUCCESS != lpWfsRet->hResult)
	{
		return HandleCmdErr(lpWfsRet);
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dwcommandcode=%d",
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwCommand_Code);
	
	CString strCmdResult = "";

	switch (lpWfsRet->u.dwCommand_Code)
	{
		case LFS_CMD_CIM_CASH_IN_START:
			break;
		case LFS_CMD_CIM_CASH_IN:
		{
			LPLFSCIMNOTENUMBERLIST lpNoteNumberList = (LPLFSCIMNOTENUMBERLIST)lpWfsRet->lpvdBuffer;
			if (NULL == lpNoteNumberList)
			{
				break ;
			}

			LPLFSCIMNOTENUMBER lpNoteNumber = NULL;

			CString strNoteNumberList(256, 0);
			sprintf((char *)strNoteNumberList.c_str(), "%s"
										"wfsresult.lpbuffer.usnumofnotenumbers=%d",
										GetStringSplitChar(),
										lpNoteNumberList->usNum_Of_Note_Numbers);

			if (NULL != lpNoteNumberList->lppNote_Number)
			{
				for (int nLoop = 0; nLoop < lpNoteNumberList->usNum_Of_Note_Numbers; nLoop ++)
				{
					lpNoteNumber = lpNoteNumberList->lppNote_Number[nLoop];
					if (NULL != lpNoteNumber)
					{
						CString strNoteNumber(256, 0);
						sprintf((char *)strNoteNumber.c_str(), "%s"
												"wfsresult.lpbuffer.lppnotetypes[%d].usnoteid=%d"
												"%s"
												"wfsresult.lpbuffer.lppnotetypes[%d].ulcount=%d",
												GetStringSplitChar(),
												nLoop, lpNoteNumber->usNote_ID,
												GetStringSplitChar(),
												nLoop, lpNoteNumber->ulCount);

						strNoteNumberList = string(strNoteNumberList.c_str()) + strNoteNumber;
					}
				}
				strCmdResult = strNoteNumberList;
			}

			break;
		}
		case LFS_CMD_CIM_CASH_IN_END:
		{
			LPLFSCIMCASHINFO lpCashInfo = (LPLFSCIMCASHINFO)lpWfsRet->lpvdBuffer;
			if (NULL != lpCashInfo)
			{
				strCmdResult = GetCashInfoResultString(lpCashInfo);
				if (strlen(strCmdResult.c_str()) > 0)
				{
					strCmdResult = GetStringSplitChar() + strCmdResult;
				}
			}

			break;
		}
		case LFS_CMD_CIM_CASH_IN_ROLLBACK:
		{
			if (NULL != lpWfsRet)
			{
				// 正常情况下返回空，如有Level 2和Level 3钞票放入且没有将该类钞票退还给用户时才返回非空
				LPLFSCIMCASHINFO lpCashInfo = (LPLFSCIMCASHINFO)lpWfsRet->lpvdBuffer;
				if (NULL != lpCashInfo)
				{
					strCmdResult = GetCashInfoResultString(lpCashInfo);
					if (strlen(strCmdResult.c_str()) > 0)
					{
						strCmdResult = GetStringSplitChar() + strCmdResult;
					}
				}
			}

			break;
		}
		case LFS_CMD_CIM_RETRACT:
			break;
		case LFS_CMD_CIM_OPEN_SHUTTER:
			break;
		case LFS_CMD_CIM_CLOSE_SHUTTER:
			break;
		case LFS_CMD_CIM_SET_TELLER_INFO:
			break;
		case LFS_CMD_CIM_SET_CASH_UNIT_INFO:
			break;
		case LFS_CMD_CIM_START_EXCHANGE:
			break;
		case LFS_CMD_CIM_END_EXCHANGE:
			break;
		case LFS_CMD_CIM_OPEN_SAFE_DOOR:
			break;
		case LFS_CMD_CIM_RESET:
			break;
		case LFS_CMD_CIM_CONFIGURE_CASH_IN_UNITS:
			break;
		case LFS_CMD_CIM_CONFIGURE_NOTETYPES:
			break;
		/*
		case LFS_CMD_CIM_CREATE_P6_SIGNATURE:
			// 有返回结构，但是用不着，不处理
			break;
		*/
		default :
			break;
	}

	strWfsResult = string(strWfsResult.c_str()) + strCmdResult;

	return strWfsResult;
}

int CDCCashAcceptor_30::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			printf("LFS_OPEN_COMPLETE CDCCashAcceptor_30\n");
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

			if (FALSE == m_bCashUnitInfo4EndExchange)  // LFS_CMD_CIM_END_EXCHANGE后续需要使用此状态信息中的钞箱结构，EndExchange使用完毕后再释放
			{
				LFSFreeResult(lpWfsRet);
			}
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
		CString strTrace(strlen(strWfsResult.c_str()) + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						uMsg, GetXFSMsgStr(uMsg).c_str(), strWfsResult.c_str());
		WriteTrace(m_strTraceComponent.c_str(), OCXEVENT, strTrace.c_str());

		FireDCEvent(m_strDCName, uMsg, strWfsResult);
	}

    return 0L;
}

HRESULT CDCCashAcceptor_30::INF_CIM_TELLER_INFO()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(	m_DCObject.m_hService,
								LFS_INF_CIM_TELLER_INFO,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_CURRENCY_EXP()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(	m_DCObject.m_hService,
								LFS_INF_CIM_CURRENCY_EXP,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_SET_CASH_UNIT_INFO(LPCTSTR strCashInType) 
{
	// 钞箱设置由硬件工程使用自有工具进行，应用不支持
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_SET_TELLER_INFO(LPCTSTR strCUInfo) 
{
	// 不使用此方法
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_START_EXCHANGE(LPCTSTR strStartEx) 
{
	if (NULL == strStartEx)
	{
		return (short)DC_ERROR;
	}

	HRESULT hResult = DC_ERROR;

	LFSCIMSTARTEX StartEx = {0};

	CStringArray strarrParams;
	CString strParamKey;
	CString strParamValue;
	if (FALSE == CJSStringParam::GetStringParams(strStartEx, GetStringSplitChar(), strarrParams) || TRUE == strarrParams.empty())
	{
		return hResult;
	}

	strParamKey = CString(128, 0);
	sprintf((char *)strParamKey.c_str(), "wfscimstartex.fwexchangetype");
	if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
	{
		return hResult;
	}
	StartEx.wExchange_Type = atoi(strParamValue.c_str());

	strParamKey = CString(128, 0);
	sprintf((char *)strParamKey.c_str(), "wfscimstartex.ustellerid");
	if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
	{
		return hResult;
	}
	StartEx.usTeller_ID = atoi(strParamValue.c_str());
	
	strParamKey = CString(128, 0);
	sprintf((char *)strParamKey.c_str(), "wfscimstartex.uscount");
	if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
	{
		return hResult;
	}
	StartEx.usCount = atoi(strParamValue.c_str());

	USHORT usCUNumList[64] = {0};
	for (int nLoop = 0; nLoop < StartEx.usCount; nLoop ++)
	{
		strParamKey = CString(128, 0);
		sprintf((char *)strParamKey.c_str(), "wfscimstartex.lpuscunumlist[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			return hResult;
		}
		usCUNumList[nLoop] = atoi(strParamValue.c_str());
	}
	StartEx.lpusCU_Num_List = usCUNumList;

	LFSCIMOUTPUT WfsCimOutput = {0};
	StartEx.lpOutput = &WfsCimOutput;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_START_EXCHANGE,
								&StartEx,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_BANKNOTE_TYPES()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(	m_DCObject.m_hService,
								LFS_INF_CIM_BANKNOTE_TYPES,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(	m_DCObject.m_hService,
								LFS_INF_CIM_CAPABILITIES,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_CASH_IN_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(	m_DCObject.m_hService,
								LFS_INF_CIM_CASH_IN_STATUS,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

CString CDCCashAcceptor_30::GetCashInResultString(LPLFSCIMCASHIN lpCashIn)
{
	if (NULL == lpCashIn)
	{
		return "";
	}

	CString strNoteNumberList(128, 0);
	LPLFSCIMNOTENUMBERLIST lpNoteNumberList = (LPLFSCIMNOTENUMBERLIST)lpCashIn->lpNote_Number_List;
	if (NULL != lpNoteNumberList)
	{
		sprintf((char *)strNoteNumberList.c_str(), "%s"
									"wfscimcashin.lpnotenumberlist.usnumofnotenumbers=%d",
									GetStringSplitChar(),
									lpNoteNumberList->usNum_Of_Note_Numbers);

		if (NULL != lpNoteNumberList->lppNote_Number)
		{
			LPLFSCIMNOTENUMBER lpNoteNumber = NULL;
			for (int nLoop = 0; nLoop < lpNoteNumberList->usNum_Of_Note_Numbers; nLoop ++)
			{
				lpNoteNumber = lpNoteNumberList->lppNote_Number[nLoop];
				if (NULL != lpNoteNumber)
				{
					CString strNoteNumber(256, 0);
					sprintf((char *)strNoteNumber.c_str(), "%s"
											"wfscimcashin.lpnotenumberlist.lppnotenumber[%d].usnoteid=%d"
											"%s"
											"wfscimcashin.lpnotenumberlist.lppnotenumber[%d].ulcount=%d",
											GetStringSplitChar(),
											nLoop, lpNoteNumber->usNote_ID,
											GetStringSplitChar(),
											nLoop, lpNoteNumber->ulCount);

					strNoteNumberList = string(strNoteNumberList.c_str()) + strNoteNumber;
				}
			}
		}
	}

	CString strCimPhCus = "";
	CString strCimPhCu;
	LPLFSCIMPHCU lpPhysical = NULL;
	for (int nLoop = 0; nLoop < lpCashIn->usNum_Physical_CUs; nLoop ++)
	{
		lpPhysical = lpCashIn->lppPhysical[nLoop];
		if (NULL == lpPhysical)
		{
			continue ;
		}

		strCimPhCu = CString((NULL == lpPhysical->lpstrPhysical_Position_Name ? 0 : strlen(lpPhysical->lpstrPhysical_Position_Name))
							+ sizeof(lpPhysical->cUnit_ID)
							+ (NULL == lpPhysical->lpstrExtra ? 0 : strlen(lpPhysical->lpstrExtra))
							+ 1024, 0);
		sprintf((char *)strCimPhCu.c_str(), "%s"
							"wfscimcashin.lppphysical[%d].lpphysicalpositionname=%s"
							"%s"
							"wfscimcashin.lppphysical[%d].cunitid=%s"
							"%s"
							"wfscimcashin.lppphysical[%d].ulcashincount=%d"
							"%s"
							"wfscimcashin.lppphysical[%d].ulcount=%d"
							"%s"
							"wfscimcashin.lppphysical[%d].ulmaximum=%d"
							"%s"
							"wfscimcashin.lppphysical[%d].uspstatus=%d"
							"%s"
							"wfscimcashin.lppphysical[%d].bhardwaresensors=%s"
							"%s"
							"wfscimcashin.lppphysical[%d].lpszextra=%s",
							GetStringSplitChar(),
							nLoop, (NULL == lpPhysical->lpstrPhysical_Position_Name ? "NULL" : lpPhysical->lpstrPhysical_Position_Name),
							GetStringSplitChar(),
							nLoop, CString(lpPhysical->cUnit_ID, sizeof(lpPhysical->cUnit_ID)).c_str(),
							GetStringSplitChar(),
							nLoop, lpPhysical->ulCash_In_Count,
							GetStringSplitChar(),
							nLoop, lpPhysical->ulCount,
							GetStringSplitChar(),
							nLoop, lpPhysical->ulMaximum,
							GetStringSplitChar(),
							nLoop, lpPhysical->usPStatus,
							GetStringSplitChar(),
							nLoop, (TRUE == lpPhysical->bHardware_Sensors ? "true" : "false"),
							GetStringSplitChar(), 
							nLoop, (NULL == lpPhysical->lpstrExtra ? "NULL" : FormatExtra(lpPhysical->lpstrExtra)));

		strCimPhCus = string(strCimPhCus.c_str()) + strCimPhCu;
	}

	CString strCashIn(strlen(strNoteNumberList.c_str()) + strlen(strCimPhCus.c_str())
					 + (NULL == lpCashIn->lpstrExtra ? 0 : strlen(lpCashIn->lpstrExtra)) + 1024, 0);
	sprintf((char *)strCashIn.c_str(), "%s"
						"wfscimcashin.usnumber=%d"
						"%s"
						"wfscimcashin.fwtype=%d"
						"%s"
						"wfscimcashin.fwitemtype=%d"
						"%s"
						"wfscimcashin.cunitid=%s"
						"%s"
						"wfscimcashin.ccurrencyid=%s"
						"%s"
						"wfscimcashin.ulvalues=%d"
						"%s"
						"wfscimcashin.ulcashincount=%d"
						"%s"
						"wfscimcashin.ulcount=%d"
						"%s"
						"wfscimcashin.ulmaximum=%d"
						"%s"
						"wfscimcashin.usstatus=%d"
						"%s"
						"wfscimcashin.bapplock=%s"
						"%s"  // wfscimcashin.lpnotenumberlist
						"%s"
						"wfscimcashin.usnumphysicalcus=%d"
						"%s"  // wfscimcashin.lppphysical
						"%s"
						"wfscimcashin.lpszextra=%s",
						GetStringSplitChar(),
						lpCashIn->usNumber,
						GetStringSplitChar(),
						lpCashIn->dwType,
						GetStringSplitChar(),
						lpCashIn->dwItem_Type,
						GetStringSplitChar(),
						CString(lpCashIn->cUnit_ID, sizeof(lpCashIn->cUnit_ID)).c_str(),
						GetStringSplitChar(),
						CString(lpCashIn->cCurrency_ID, sizeof(lpCashIn->cCurrency_ID)).c_str(),
						GetStringSplitChar(),
						lpCashIn->ulValues,
						GetStringSplitChar(),
						lpCashIn->ulCash_In_Count,
						GetStringSplitChar(),
						lpCashIn->ulCount,
						GetStringSplitChar(),
						lpCashIn->ulMaximum,
						GetStringSplitChar(),
						lpCashIn->usStatus,
						GetStringSplitChar(),
						(TRUE == lpCashIn->bApp_Lock ? "true" : "false"),
						strNoteNumberList.c_str(),
						GetStringSplitChar(),
						lpCashIn->usNum_Physical_CUs,
						strCimPhCus.c_str(),
						GetStringSplitChar(),
						(NULL == lpCashIn->lpstrExtra ? "NULL" : FormatExtra(lpCashIn->lpstrExtra)));

	printf("1 *** strCashIn *** : %s\n", strCashIn.c_str());

	return string(strCashIn.c_str());
}

CString CDCCashAcceptor_30::GetCashInfoResultString(LPLFSCIMCASHINFO lpCashInfo)
{
	if (NULL == lpCashInfo)
	{
		return "";
	}

	CString strCashInfo(128, 0);
	sprintf((char *)strCashInfo.c_str(), "wfsresult.lpbuffer.uscount=%d",
						lpCashInfo->usCount);

	if (NULL != lpCashInfo->lppCash_In)
	{
		CString strCashIn = "";
		LPLFSCIMCASHIN lpCashIn = NULL;

		for (int nLoop = 0; nLoop < lpCashInfo->usCount; nLoop ++)
		{
			lpCashIn = lpCashInfo->lppCash_In[nLoop];
			if (NULL != lpCashIn)
			{
				strCashIn = GetCashInResultString(lpCashIn);

				// GetCashInResultString方法返回的字符串前缀是wfscimcashin，
				// 此处前缀应更改为：wfsresult.lpbuffer.lppcashin[%d]
				char szPrefix[128] = {0};
				sprintf(szPrefix, "wfsresult.lpbuffer.lppcashin[%d]", nLoop);
				// strCashIn.Replace("wfscimcashin", strPrefix);
				strCashIn = replace_all_distinct(strCashIn, "wfscimcashin", string(szPrefix));

				strCashInfo = string(strCashInfo.c_str()) + strCashIn;
			}
		}
	}

	return std::string(strCashInfo.c_str());
}

HRESULT CDCCashAcceptor_30::INF_CIM_CASH_UNIT_INFO()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(	m_DCObject.m_hService,
								LFS_INF_CIM_CASH_UNIT_INFO,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(	m_DCObject.m_hService,
								LFS_INF_CIM_STATUS,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

CString CDCCashAcceptor_30::HandleInfResult(LPLFSRESULT lpWfsRet)
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
		"wfsresult.u.dwcommandcode=%d"
		"%s",
		lpWfsRet->hResult,
		GetStringSplitChar(),
		lpWfsRet->u.dwCommand_Code,
		GetStringSplitChar());

	if (LFS_SUCCESS != lpWfsRet->hResult)
	{
		return strWfsResult;
	}

	if (LFS_INF_CIM_STATUS == lpWfsRet->u.dwCommand_Code)
	{
		LPLFSCIMSTATUS lpStatus = (LPLFSCIMSTATUS)lpWfsRet->lpvdBuffer;
		if (NULL == lpStatus)
		{
			return strWfsResult;
		}

		LPLFSCIMINPOS * lppPositions = (LPLFSCIMINPOS *)lpStatus->lppPositions;
		if (NULL == lppPositions)
		{
			return strWfsResult;
		}

		LPLFSCIMINPOS lpWfsCimInPos1 = lppPositions[0];
		LPLFSCIMINPOS lpWfsCimInPos2 = lppPositions[1];

		CString strPositions = "";
		CString strPosition = "";

		if (NULL != lpWfsCimInPos1)
		{
			strPosition = CString(1024, 0);
			sprintf((char *)strPosition.c_str(), "wfsresult.lpbuffer.lpppositions[0].fwposition=%d"
								"%s"
								"wfsresult.lpbuffer.lpppositions[0].fwshutter=%d"
								"%s"
								"wfsresult.lpbuffer.lpppositions[0].fwpositionstatus=%d"
								"%s"
								"wfsresult.lpbuffer.lpppositions[0].fwtransport=%d"
								"%s"
								"wfsresult.lpbuffer.lpppositions[0].fwtransportstatus=%d"
								"%s",
								lpWfsCimInPos1->wPosition,
								GetStringSplitChar(),
								lpWfsCimInPos1->wShutter,
								GetStringSplitChar(),
								lpWfsCimInPos1->wPosition_Status,
								GetStringSplitChar(),
								lpWfsCimInPos1->wTransport,
								GetStringSplitChar(),
								lpWfsCimInPos1->wTransport_Status,
								GetStringSplitChar());

			strPositions = string(strPositions.c_str()) + strPosition;
		}

		if (NULL != lpWfsCimInPos2)
		{
			strPosition = CString(1024, 0);
			sprintf((char *)strPosition.c_str(), "wfsresult.lpbuffer.lpppositions[1].fwposition=%d"
								"%s"
								"wfsresult.lpbuffer.lpppositions[1].fwshutter=%d"
								"%s"
								"wfsresult.lpbuffer.lpppositions[1].fwpositionstatus=%d"
								"%s"
								"wfsresult.lpbuffer.lpppositions[1].fwtransport=%d"
								"%s"
								"wfsresult.lpbuffer.lpppositions[1].fwtransportstatus=%d"
								"%s",
								lpWfsCimInPos2->wPosition,
								GetStringSplitChar(),
								lpWfsCimInPos2->wShutter,
								GetStringSplitChar(),
								lpWfsCimInPos2->wPosition_Status,
								GetStringSplitChar(),
								lpWfsCimInPos2->wTransport,
								GetStringSplitChar(),
								lpWfsCimInPos2->wTransport_Status,
								GetStringSplitChar());

			strPositions = string(strPositions.c_str()) + strPosition;
		}

		strWfsResult = CString(strlen(strPositions.c_str()) + (NULL == lpStatus->lpstrExtra ? 0 : strlen(lpStatus->lpstrExtra)) + 1024, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
							"%s"
							"wfsresult.lpbuffer.fwdevice=%d"
							"%s"
							"wfsresult.lpbuffer.fwsafedoor=%d"
							"%s"
							"wfsresult.lpbuffer.fwacceptor=%d"
							"%s"
							"wfsresult.lpbuffer.fwintermediatestacker=%d"
							"%s"
							"wfsresult.lpbuffer.fwstackeritems=%d"
							"%s"
							"wfsresult.lpbuffer.fwbanknotereader=%d"
							"%s"
							"wfsresult.lpbuffer.bdropbox=%s"
							"%s"
							"%s"  // "wfsresult.lpbuffer.lpppositions=%d"
							"wfsresult.lpbuffer.lpszextra=%s",
							LFS_INF_CIM_STATUS,
							GetStringSplitChar(),
							lpStatus->wDevice,
							GetStringSplitChar(),
							lpStatus->wSafe_Door,
							GetStringSplitChar(),
							lpStatus->wAcceptor,
							GetStringSplitChar(),
							lpStatus->wIntermediate_Stacker,
							GetStringSplitChar(),
							lpStatus->wStacker_Items,
							GetStringSplitChar(),
							lpStatus->wBank_Note_Reader,
							GetStringSplitChar(),
							(TRUE == lpStatus->bDrop_Box ? "TRUE" : "FALSE"),
							GetStringSplitChar(),
							strPositions.c_str(),
							(NULL == lpStatus->lpstrExtra ? "NULL" : FormatExtra(lpStatus->lpstrExtra)));
	 }
	else if (LFS_INF_CIM_BANKNOTE_TYPES == lpWfsRet->u.dwCommand_Code)
	{
		LPLFSCIMNOTETYPELIST lpNoteTypeList = (LPLFSCIMNOTETYPELIST)lpWfsRet->lpvdBuffer;
		if (NULL == lpNoteTypeList)
		{
			return strWfsResult;
		}

		LPLFSCIMNOTETYPE lpNoteType = NULL;

		CString strNoteTypeList = "";
		if (NULL != lpNoteTypeList->lppNote_Types)
		{
			for (int nLoop = 0; nLoop < lpNoteTypeList->usNum_Of_Note_Types; nLoop++)
			{
				lpNoteType = lpNoteTypeList->lppNote_Types[nLoop];
				if (NULL != lpNoteType)
				{
					CString strNoteType(sizeof(lpNoteType->cCurrency_ID) + 2048, 0);
					sprintf((char *)strNoteType.c_str(), "%s"
						"wfsresult.lpbuffer.lppnotetypes[%d].usnoteid=%d"
						"%s"
						"wfsresult.lpbuffer.lppnotetypes[%d].ccurrencyid=%s"
						"%s"
						"wfsresult.lpbuffer.lppnotetypes[%d].ulvalues=%d"
						"%s"
						"wfsresult.lpbuffer.lppnotetypes[%d].usrelease=%d"
						"%s"
						"wfsresult.lpbuffer.lppnotetypes[%d].bconfigured=%s",
						GetStringSplitChar(),
						nLoop, lpNoteType->usNote_ID,
						GetStringSplitChar(),
						nLoop, CString(lpNoteType->cCurrency_ID, sizeof(lpNoteType->cCurrency_ID)).c_str(),
						GetStringSplitChar(),
						nLoop, lpNoteType->ulValues,
						GetStringSplitChar(),
						nLoop, lpNoteType->usRelease,
						GetStringSplitChar(),
						nLoop, (TRUE == lpNoteType->bConfigured ? "true" : "false"));

					strNoteTypeList = string(strNoteTypeList.c_str()) + strNoteType;
				}
			}
		}

		strWfsResult = string(strlen(strNoteTypeList.c_str()) + 128, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.usnumofnotetypes=%d"
			"%s",
			LFS_INF_CIM_BANKNOTE_TYPES,
			GetStringSplitChar(),
			lpNoteTypeList->usNum_Of_Note_Types,
			strNoteTypeList.c_str());
	}
	else if (LFS_INF_CIM_CAPABILITIES == lpWfsRet->u.dwCommand_Code)
	{
		LPLFSCIMCAPS lpCaps = (LPLFSCIMCAPS)lpWfsRet->lpvdBuffer;
		if (NULL == lpCaps)
		{
			return strWfsResult;
		}

		strWfsResult = string((NULL == lpCaps->lpstrExtra ? 0 : strlen(lpCaps->lpstrExtra)) + 2048, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.wclass=%d"
			"%s"
			"wfsresult.lpbuffer.fwtype=%d"
			"%s"
			"wfsresult.lpbuffer.wmaxcashinitems=%d"
			"%s"
			"wfsresult.lpbuffer.bcompound=%s"
			"%s"
			"wfsresult.lpbuffer.bshutter=%s"
			"%s"
			"wfsresult.lpbuffer.bshuttercontrol=%s"
			"%s"
			"wfsresult.lpbuffer.bsafedoor=%s"
			"%s"
			"wfsresult.lpbuffer.bcashbox=%s"
			"%s"
			"wfsresult.lpbuffer.brefill=%s"
			"%s"
			"wfsresult.lpbuffer.fwintermediatestacker=%d"
			"%s"
			"wfsresult.lpbuffer.bitemstakensensor=%s"
			"%s"
			"wfsresult.lpbuffer.bitemsinsertedsensor=%s"
			"%s"
			"wfsresult.lpbuffer.fwpositions=%d"
			"%s"
			"wfsresult.lpbuffer.fwexchangetype=%d"
			"%s"
			"wfsresult.lpbuffer.fwretractareas=%d"
			"%s"
			"wfsresult.lpbuffer.fwretracttransportactions=%d"
			"%s"
			"wfsresult.lpbuffer.fwretractstackeractions=%d"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_CIM_CAPABILITIES,
			GetStringSplitChar(),
			lpCaps->wClass,
			GetStringSplitChar(),
			lpCaps->wType,
			GetStringSplitChar(),
			lpCaps->wMax_Cash_In_Items,
			GetStringSplitChar(),
			lpCaps->bCompound ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->bShutter ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->bShutter_Control ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->bSafe_Door ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->bCash_Box ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->bRefill ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->wIntermediate_Stacker,
			GetStringSplitChar(),
			lpCaps->bItems_Taken_Sensor ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->bItems_Inserted_Sensor ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->wPositions,
			GetStringSplitChar(),
			lpCaps->wExchange_Type,
			GetStringSplitChar(),
			lpCaps->wRetract_Areas,
			GetStringSplitChar(),
			lpCaps->wRetract_Transport_Actions,
			GetStringSplitChar(),
			lpCaps->wRetract_Stacker_Actions,
			GetStringSplitChar(),
			(NULL == lpCaps->lpstrExtra ? "NULL" : FormatExtra(lpCaps->lpstrExtra)));
	}
	else if (LFS_INF_CIM_CASH_IN_STATUS == lpWfsRet->u.dwCommand_Code)
	{
		LPLFSCIMCASHINSTATUS lpCashInStatus = (LPLFSCIMCASHINSTATUS)lpWfsRet->lpvdBuffer;
		if (NULL == lpCashInStatus)
		{
			return strWfsResult;
		}

		CString strNoteNumberList(256, 0);
		LPLFSCIMNOTENUMBERLIST lpNoteNumberList = (LPLFSCIMNOTENUMBERLIST)lpCashInStatus->lpNote_Number_List;
		if (NULL == lpNoteNumberList)
		{
			sprintf((char *)strNoteNumberList.c_str(), "%s"
				"wfsresult.lpbuffer.lpnotenumberlist.usnumofnotenumbers=%d",
				GetStringSplitChar(),
				0);
		}
		else
		{
			sprintf((char *)strNoteNumberList.c_str(), "%s"
				"wfsresult.lpbuffer.lpnotenumberlist.usnumofnotenumbers=%d",
				GetStringSplitChar(),
				lpNoteNumberList->usNum_Of_Note_Numbers);
			if (NULL != lpNoteNumberList->lppNote_Number)
			{
				LPLFSCIMNOTENUMBER lpNoteNumber = NULL;

				for (int nLoop = 0; nLoop < lpNoteNumberList->usNum_Of_Note_Numbers; nLoop++)
				{
					lpNoteNumber = lpNoteNumberList->lppNote_Number[nLoop];
					if (NULL != lpNoteNumber)
					{
						CString strNoteNumber(256, 0);
						sprintf((char *)strNoteNumber.c_str(), "%s"
							"wfsresult.lpbuffer.lpnotenumberlist.lppnotenumber[%d].usnoteid=%d"
							"%s"
							"wfsresult.lpbuffer.lpnotenumberlist.lppnotenumber[%d].ulcount=%d",
							GetStringSplitChar(),
							nLoop, lpNoteNumber->usNote_ID,
							GetStringSplitChar(),
							nLoop, lpNoteNumber->ulCount);

						strNoteNumberList = string(strNoteNumberList.c_str()) + strNoteNumber;
					}
				}
			}
		}

		strWfsResult = string((NULL == lpCashInStatus->lpstrExtra ? 0 : strlen(lpCashInStatus->lpstrExtra)) + strlen(strNoteNumberList.c_str()) + 2048, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.wstatus=%d"
			"%s"
			"wfsresult.lpbuffer.usnumofrefused=%d"
			"%s"  // wfsresult.lpbuffer.lpnotenumberlist
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_CIM_CASH_IN_STATUS,
			GetStringSplitChar(),
			lpCashInStatus->wStatus,
			GetStringSplitChar(),
			lpCashInStatus->usNum_Of_Refused,
			strNoteNumberList.c_str(),
			GetStringSplitChar(),
			(NULL == lpCashInStatus->lpstrExtra ? "NULL" : FormatExtra(lpCashInStatus->lpstrExtra)));
	}
	else if (LFS_INF_CIM_CASH_UNIT_INFO == lpWfsRet->u.dwCommand_Code)
	{
		LPLFSCIMCASHINFO lpCashInfo = (LPLFSCIMCASHINFO)lpWfsRet->lpvdBuffer;
		if (NULL == lpCashInfo)
		{
			return strWfsResult;
		}

		CString strCashIn = GetCashInfoResultString(lpCashInfo);
		strWfsResult = string(strWfsResult.c_str()) + strCashIn;

		// EXE_LFS_CMD_CIM_END_EXCHANGE方法会调用此GET_LFS_INF_CIM_CASH_UNIT_INFO方法，用于获取传递到SP的加钞的结构
		if (TRUE == m_bCashUnitInfo4EndExchange)
		{
			// 返回且不释放LFS结果
			m_lpResult4EndExchange = lpWfsRet;
		}
	}
	else if (LFS_INF_CIM_CURRENCY_EXP == lpWfsRet->u.dwCommand_Code)
	{
		LPLFSCIMCURRENCYEXP * lppCurrencyExp = (LPLFSCIMCURRENCYEXP *)lpWfsRet->lpvdBuffer;
		if (NULL == lppCurrencyExp)
		{
			return strWfsResult;
		}

		strWfsResult = string(256, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s",
			LFS_INF_CIM_CURRENCY_EXP,
			GetStringSplitChar());

		if (NULL != lppCurrencyExp)
		{
			for (int nLoop = 0; NULL != lppCurrencyExp[nLoop]; nLoop++)
			{
				CString strCurrencyExp(sizeof(lppCurrencyExp[nLoop]->cCurrency_ID) + 128, 0);
				sprintf((char *)strCurrencyExp.c_str(), "wfsresult.lpbuffer[%d].ccurrencyid=%s"
					"%s"
					"wfsresult.lpbuffer[%d].sexponent=%d",
					nLoop, CString(lppCurrencyExp[nLoop]->cCurrency_ID, sizeof(lppCurrencyExp[nLoop]->cCurrency_ID)).c_str(),
					GetStringSplitChar(),
					nLoop, lppCurrencyExp[nLoop]->sExponent);
				if ("" != strWfsResult)
				{
					strWfsResult = string(strWfsResult.c_str()) + GetStringSplitChar();
				}

				strWfsResult = string(strWfsResult.c_str()) + strCurrencyExp;
			}
		}
	}
	else if (LFS_INF_CIM_TELLER_INFO == lpWfsRet->u.dwCommand_Code)
	{
		LPLFSCIMTELLERINFO lpTellerInfo = (LPLFSCIMTELLERINFO)lpWfsRet->lpvdBuffer;
		if (NULL == lpTellerInfo)
		{
			return strWfsResult;
		}

		strWfsResult = string(sizeof(lpTellerInfo->cCurrency_ID) + 1024, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.ustellerid=%d"
			"%s"
			"wfsresult.lpbuffer.ccurrencyid=%s",
			LFS_INF_CIM_TELLER_INFO,
			GetStringSplitChar(),
			lpTellerInfo->usTeller_ID,
			GetStringSplitChar(),
			CString(lpTellerInfo->cCurrency_ID, sizeof(lpTellerInfo->cCurrency_ID)).c_str());
	}

	return strWfsResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_GET_P6_INFO()
{
	// 对于应用而言，这个命令没有用处，而且处理需要很罗嗦，返回失败
	// 相同的有：GET_LFS_INF_CDM_MIX_TYPES、GET_LFS_INF_CDM_MIX_TABLE、GET_LFS_INF_CDM_CURRENCY_EXP
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::INF_CIM_GET_P6_SIGNATURE()
{
	// 对于应用而言，这个命令没有用处，而且处理需要很罗嗦，返回失败
	// 相同的有：GET_LFS_INF_CDM_MIX_TYPES、GET_LFS_INF_CDM_MIX_TABLE、GET_LFS_INF_CDM_CURRENCY_EXP
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CASH_IN()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CASH_IN,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);
	
	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CASH_IN_END()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CASH_IN_END,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);
	
	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CASH_IN_ROLLBACK()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CASH_IN_ROLLBACK,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CASH_IN_START(long lInputPosition, long lOutputPosition, long lUseRecycleUnits)
{
	HRESULT hResult = DC_ERROR;

	LFSCIMCASHINSTART CashInStart = {0};
	CashInStart.usTeller_ID = 0;
	CashInStart.bUse_Recycle_Units = (0 == lUseRecycleUnits ? FALSE : TRUE);
	// 20250622 长沙银行中电金融要求和头文件中对应而非位置
	// CashInStart.wOutput_Position = (WORD)lInputPosition;
	// CashInStart.wInput_Position = (WORD)lOutputPosition;
	CashInStart.wInput_Position = (WORD)lInputPosition;
	CashInStart.wOutput_Position = (WORD)lOutputPosition;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CASH_IN_START,
								&CashInStart,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CLOSE_SHUTTER(long lPosition) 
{
	HRESULT hResult = DC_ERROR;

	WORD fwPosition = (WORD)lPosition;
	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CLOSE_SHUTTER,
								&fwPosition,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CONFIGURE_CASH_IN_UNITS(LPCTSTR strCashInType) 
{
	// 钞箱设置由硬件工程使使用自有工具进行，应用不支持
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CONFIGURE_NOTETYPES(LPCTSTR strNoteIDs) 
{
	HRESULT hResult = DC_ERROR;

	CStringArray strarrParams;
	CString strParamKey;
	CString strParamValue;
	if (FALSE == CJSStringParam::GetStringParams(strNoteIDs, GetStringSplitChar(), strarrParams) || TRUE == strarrParams.empty())
	{
		return hResult;
	}
	
	USHORT usNoteIDs[64] = {0};
	int nLoop = 0;
	list<string>::iterator iter;
	for (iter = strarrParams.begin(); iter != strarrParams.end(); iter++, nLoop++)
	{
		strParamKey = CString(128, 0);
		sprintf((char *)strParamKey.c_str(), "noteids[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			return hResult;
		}
		usNoteIDs[nLoop] = atoi(strParamValue.c_str());
	}

	// usNoteIDs[strarrParams.GetSize()] = NULL;
	usNoteIDs[nLoop] = NULL;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CONFIGURE_NOTETYPES,
								usNoteIDs,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CREATE_P6_SIGNATURE()
{
	// 对于应用而言，这个命令没有用处，暂未实现
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_END_EXCHANGE(LPCTSTR strCUInfo) 
{
	HRESULT hResult = DC_ERROR;

	// 调用GET_LFS_INF_CIM_CASH_UNIT_INFO获取钞箱结构
	if (NULL != m_lpResult4EndExchange)  // 防止有残留内存没有释放
	{
		LFSFreeResult(m_lpResult4EndExchange);
		m_lpResult4EndExchange = NULL;
	}

	m_bCashUnitInfo4EndExchange = TRUE;
	hResult = INF_CIM_CASH_UNIT_INFO();
	if (LFS_SUCCESS != hResult)
	{
		m_bCashUnitInfo4EndExchange = FALSE;

		printf(" (LFS_SUCCESS != hResult)\n");
		return hResult;
	}

	// 最多等待INF_CIM_CASH_UNIT_INFO 30秒取状态完成，获取钞箱结构以进行数据填充
	int nCount = 0;
	while (NULL == m_lpResult4EndExchange && (++nCount) < 300)
	{
		usleep(100 * 1000);
	}

	if (NULL == m_lpResult4EndExchange)
	{
		m_bCashUnitInfo4EndExchange = FALSE;

		printf("INF_CDM_CASH_UNIT_INFO not return in 30 seconds\n");
		return (short)DC_ERROR;
	}

	LPLFSCIMCASHINFO lpCashInfo = (LPLFSCIMCASHINFO)m_lpResult4EndExchange->lpvdBuffer;
	if (NULL == lpCashInfo)
	{
		m_bCashUnitInfo4EndExchange = FALSE;

		LFSFreeResult(m_lpResult4EndExchange);
		m_lpResult4EndExchange = NULL;

		printf("if (NULL == lpCashInfo)\n");
		return (short)DC_ERROR;
	}
	
	BOOL bEndWithClean = TRUE;
	if (strlen(strCUInfo) > 0)
	{
		bEndWithClean = FALSE;
	}
 
	CStringArray strarrParams;
	CString strParamKey;
	CString strParamValue;
	if (FALSE == bEndWithClean)
	{
		if (FALSE == CJSStringParam::GetStringParams(strCUInfo, GetStringSplitChar(), strarrParams) || TRUE == strarrParams.empty())
		{
			m_bCashUnitInfo4EndExchange = FALSE;

			LFSFreeResult(m_lpResult4EndExchange);
			m_lpResult4EndExchange = NULL;

			printf("if (FALSE == CJSStringParam::GetStringParams(strCUInfo, GetStringSplitChar(), strarrParams) || TRUE == strarrParams.empty())\n");
			return (short)DC_ERROR;
		}
	}

	int nNumOfPUCashUnits = 0;
	LPLFSCIMCASHIN lpCashIn = NULL;
 	for (int nLoop = 0; nLoop < lpCashInfo->usCount; nLoop ++)
	{
		lpCashIn = lpCashInfo->lppCash_In[nLoop];
		if (NULL != lpCashIn)
		{
			if(TRUE == bEndWithClean)
			{
				lpCashIn->ulCount = 0;
				lpCashIn->ulCash_In_Count = 0;
				lpCashIn->lpNote_Number_List = NULL;
				lpCashIn->usStatus = LFS_CIM_STATCUEMPTY;
			}
			else
			{
				// 钞箱计数不改变
				// 更改币种
				strParamKey = CString(128, 0);
				sprintf((char *)strParamKey.c_str(), "wfsresult.lpbuffer.lppcashin[%d].ccurrencyid", nLoop);
				if (TRUE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
				{
					if (strlen(strParamValue.c_str()) > 3)
					{
						m_bCashUnitInfo4EndExchange = FALSE;

						LFSFreeResult(m_lpResult4EndExchange);
						m_lpResult4EndExchange = NULL;

						printf("if (strlenstrParamValue.c_str()) > 3)\n");
						return (short)DC_ERROR;
					}
					
					memset(lpCashIn->cCurrency_ID, 0, sizeof(lpCashIn->cCurrency_ID));
					memcpy(	lpCashIn->cCurrency_ID, 
							strParamValue.c_str(),
							strlen(strParamValue.c_str()));
				}

				// 更改面值
				strParamKey = CString(128, 0);
				sprintf((char *)strParamKey.c_str(), "wfsresult.lpbuffer.lppcashin[%d].ulvalues", nLoop);
				if (TRUE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
				{
					lpCashIn->ulValues = atoi(strParamValue.c_str());
				}
			}

			LPLFSCIMPHCU lpPhysical = NULL;
			
			for (int jLoop = 0; jLoop < lpCashIn->usNum_Physical_CUs; jLoop ++)
			{
				lpPhysical = lpCashIn->lppPhysical[jLoop];
				if (NULL != lpPhysical)
				{
					if(TRUE == bEndWithClean)
					{
						lpPhysical->ulCount = 0;
						lpPhysical->ulCash_In_Count = 0;
						lpPhysical->usPStatus = LFS_CIM_STATCUEMPTY;
					}
					else
					{
						// 钞箱计数不改变，或者更改币种和面值时不需要改动物理钞箱
					}
				}
			}
		}
	}

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_END_EXCHANGE,
								lpCashInfo,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);
	
	m_bCashUnitInfo4EndExchange = FALSE;

	LFSFreeResult(m_lpResult4EndExchange);
	m_lpResult4EndExchange = NULL;

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_OPEN_SAFE_DOOR() 
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_OPEN_SAFE_DOOR,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_OPEN_SHUTTER(long lPosition) 
{
	HRESULT hResult = DC_ERROR;

	WORD fwPosition = (WORD)lPosition;
	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_OPEN_SHUTTER,
								&fwPosition,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);
	
	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_RESET(long lNumber, long lResetPosition, long lRetractArea, long lRetractIndex, long lRetractPosition) 
{
	HRESULT hResult = DC_ERROR;

	LFSCIMRETRACT Retract = {0};
	Retract.wOutput_Position = (WORD)lRetractPosition;
	Retract.usRetract_Area = (USHORT)lRetractArea;
	Retract.usIndex = (USHORT)lRetractIndex;

	LFSCIMITEMPOSITION ResetIn = {0};
	ResetIn.wOutput_Position = (WORD)lResetPosition;
	ResetIn.usNumber = (USHORT)lNumber;
	ResetIn.lpRetract_Area = &Retract;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_RESET,
								&ResetIn,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_SET_CASH_IN_LIMIT(long lTotalItemsLimit, LPCTSTR strCurrencyID, long lAmount)
{
	HRESULT hResult = DC_ERROR;

	LFSCIMCASHINLIMIT CashInLimit = { 0 };
	CashInLimit.ulTotal_Items_Limit = lTotalItemsLimit;
	CashInLimit.lpAmount_Limit = NULL;

	LFSCIMAMOUNTLIMIT AmountLimit = { 0 };
	if (NULL != strCurrencyID && lAmount > 0)
	{
		strncpy(AmountLimit.cCurrency_ID, strCurrencyID, (strlen(strCurrencyID) > sizeof(AmountLimit.cCurrency_ID) ? sizeof(AmountLimit.cCurrency_ID) : strlen(strCurrencyID)));
		AmountLimit.ulAmount = lAmount;

		CashInLimit.lpAmount_Limit = &AmountLimit;
	}

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_SET_CASH_IN_LIMIT,
								&CashInLimit,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CASH_UNIT_COUNT(LPCTSTR strCashUnitNumbers)
{
	HRESULT hResult = DC_ERROR;

	if (strlen(strCashUnitNumbers) == 0)
	{
		return DC_ERROR;
	}

	LFSCIMCOUNT Count = { 0 };
	USHORT usCUNumList[16] = { 0 };
	Count.lpusCU_Num_List = usCUNumList;

	CStringArray strarrCounts;
	CUtils::SplitString(strarrCounts, (LPSTR)strCashUnitNumbers, ",");
	if (strarrCounts.size() <= 0)
	{
		return DC_ERROR;
	}

	list<string>::iterator iter;
	int nIndex = 0;
	for (iter = strarrCounts.begin(); iter != strarrCounts.end(); iter++)
	{
		usCUNumList[nIndex ++] = atoi((*iter).c_str());
	}
	Count.usCount = nIndex;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CASH_UNIT_COUNT,
								&Count,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_RETRACT(long lRetractArea, long lRetractIndex, long lRetractPosition) 
{
	HRESULT hResult = DC_ERROR;

	LFSCIMRETRACT Retract = {0};
	Retract.wOutput_Position = (WORD)lRetractPosition;
	Retract.usRetract_Area = (USHORT)lRetractArea;
	Retract.usIndex = (USHORT)lRetractIndex;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_RETRACT,
								&Retract,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}
