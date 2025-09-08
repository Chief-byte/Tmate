// DCCashAcceptor_30.cpp: implementation of the CDCCashAcceptor_30 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCCashAcceptor_30.h"
#include "JavaScriptStringParam.h"
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
	// ��������
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
		// ��ʹ�ô˷���
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
		// ��ʹ�ô˷���
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
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.event_id);

	CString strEvtResult;
	switch (lpWfsRet->u.event_id)
	{
		case LFS_EXEE_CIM_CASHUNITERROR:
		{
			LPLFSCIMCUERROR lpCashUnitError = (LPLFSCIMCUERROR)lpWfsRet->buffer;
			if (NULL != lpCashUnitError && NULL != lpCashUnitError->cash_unit)
			{
				CString strCashUnit = GetCashInResultString(lpCashUnitError->cash_unit);
				if ("" != strCashUnit)
				{
					// GetCashInResultString�������ص��ַ���ǰ׺��wfscimcashin��
					// �˴�ǰ׺Ӧ����Ϊ��wfscimcuerror.lpcashunit
					char szPrefix[128] = { 0 };
					sprintf(szPrefix, "wfscimcuerror.lpcashunit");

					// strCashUnit.Replace("wfscimcashin", strPrefix);
					strCashUnit = replace_all_distinct(strCashUnit, "wfscimcashin", string(szPrefix));

					strEvtResult = CString(strCashUnit.length() + 128, 0);
					sprintf((char *)strEvtResult.c_str(), 	"%s"
											"wfscimcuerror.wfailure=%d"
											"%s"
											"%s",
											GetStringSplitChar(),
											lpCashUnitError->failure,
											GetStringSplitChar(), 
											strCashUnit.c_str());
				}
			}

			break;
		}
		case LFS_EXEE_CIM_INPUTREFUSE:
		{
			LPUSHORT lpusReason = (LPUSHORT)lpWfsRet->buffer;
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
			LPUSHORT lpusReason = (LPUSHORT)lpWfsRet->buffer;
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
			// һ�δ��ֲ��֣����������Ӧ���в����ڣ�������
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
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.event_id);

	CString strEvtResult;

	switch(lpWfsRet->u.event_id)
	{
		case LFS_USRE_CIM_CASHUNITTHRESHOLD:
		{
			LPLFSCIMCASHIN lpCashUnit = (LPLFSCIMCASHIN)lpWfsRet->buffer;
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
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.event_id);

	CString strEvtResult;

	switch (lpWfsRet->u.event_id)
	{
		case LFS_SRVE_CIM_SAFEDOOROPEN:
			break;
		case LFS_SRVE_CIM_SAFEDOORCLOSED:
			break;
		case LFS_SRVE_CIM_CASHUNITINFOCHANGED:
		{
			LPLFSCIMCASHIN lpCashIn = (LPLFSCIMCASHIN)lpWfsRet->buffer;
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
			LPLFSCIMCOUNTSCHANGED lpCountsChanged = (LPLFSCIMCOUNTSCHANGED)lpWfsRet->buffer;
			if (NULL == lpCountsChanged)
			{
				break ;
			}

			CString strCountsChanged(128, 0);
			sprintf((char *)strCountsChanged.c_str(), "%s"
									"wfsresult.lpbuffer.uscount=%d",
									GetStringSplitChar(),
									lpCountsChanged->count);

			if (NULL != lpCountsChanged->cu_num_list)
			{
				CString strCUNumList(128, 0);
				for (int nLoop = 0; nLoop < lpCountsChanged->count; nLoop ++)
				{
					sprintf((char *)strCUNumList.c_str(), "%s"
										"wfsresult.lpbuffer.lpuscunumlist[%d]=%d",
										GetStringSplitChar(),
										nLoop, lpCountsChanged->cu_num_list[nLoop]);
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

CString	CDCCashAcceptor_30::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[16]={
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
		{"WFS_CMD_CIM_CREATE_P6_SIGNATURE"     ,(CIM_SERVICE_OFFSET + 16)}
	};
	CString strRes="UNKNOWN CMD";
	for( int i=0;i<16;i++)
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
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.command_code);
	return strWfsResult;
}

CString CDCCashAcceptor_30::HandleCmdResult(LPLFSRESULT lpWfsRet)
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
		case LFS_CMD_CIM_CASH_IN_START:
			break;
		case LFS_CMD_CIM_CASH_IN:
		{
			LPLFSCIMNOTENUMBERLIST lpNoteNumberList = (LPLFSCIMNOTENUMBERLIST)lpWfsRet->buffer;
			if (NULL == lpNoteNumberList)
			{
				break ;
			}

			LPLFSCIMNOTENUMBER lpNoteNumber = NULL;

			CString strNoteNumberList(256, 0);
			sprintf((char *)strNoteNumberList.c_str(), "%s"
										"wfsresult.lpbuffer.usnumofnotenumbers=%d",
										GetStringSplitChar(),
										lpNoteNumberList->num_of_note_numbers);

			if (NULL != lpNoteNumberList->note_number)
			{
				for (int nLoop = 0; nLoop < lpNoteNumberList->num_of_note_numbers; nLoop ++)
				{
					lpNoteNumber = lpNoteNumberList->note_number[nLoop];
					if (NULL != lpNoteNumber)
					{
						CString strNoteNumber(256, 0);
						sprintf((char *)strNoteNumber.c_str(), "%s"
												"wfsresult.lpbuffer.lppnotetypes[%d].usnoteid=%d"
												"%s"
												"wfsresult.lpbuffer.lppnotetypes[%d].ulcount=%d",
												GetStringSplitChar(),
												nLoop, lpNoteNumber->note_id,
												GetStringSplitChar(),
												nLoop, lpNoteNumber->count);

						strNoteNumberList = string(strNoteNumberList.c_str()) + strNoteNumber;
					}
				}
				strCmdResult = strNoteNumberList;
			}

			break;
		}
		case LFS_CMD_CIM_CASH_IN_END:
		{
			LPLFSCIMCASHINFO lpCashInfo = (LPLFSCIMCASHINFO)lpWfsRet->buffer;
			if (NULL != lpCashInfo)
			{
				strCmdResult = GetCashInfoResultString(lpCashInfo);
				if (strCmdResult.length() > 0)
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
				// ��������·��ؿգ�����Level 2��Level 3��Ʊ������û�н����೮Ʊ�˻����û�ʱ�ŷ��طǿ�
				LPLFSCIMCASHINFO lpCashInfo = (LPLFSCIMCASHINFO)lpWfsRet->buffer;
				if (NULL != lpCashInfo)
				{
					strCmdResult = GetCashInfoResultString(lpCashInfo);
					if (strCmdResult.length() > 0)
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
			// �з��ؽṹ�������ò��ţ�������
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

			if (FALSE == m_bCashUnitInfo4EndExchange)  // LFS_CMD_CIM_END_EXCHANGE������Ҫʹ�ô�״̬��Ϣ�еĳ���ṹ��EndExchangeʹ����Ϻ����ͷ�
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
		CString strTrace(strWfsResult.length() + 256, 0);
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

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CIM_TELLER_INFO,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_CURRENCY_EXP()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CIM_CURRENCY_EXP,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_SET_CASH_UNIT_INFO(LPCTSTR strCashInType) 
{
	// ����������Ӳ������ʹ�����й��߽��У�Ӧ�ò�֧��
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_SET_TELLER_INFO(LPCTSTR strCUInfo) 
{
	// ��ʹ�ô˷���
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_START_EXCHANGE(LPCTSTR strStartEx) 
{
	if (NULL == strStartEx)
	{
		return (short)DC_ERROR;
	}

	CString strTrace(strlen(strStartEx) + 128, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_START_EXCHANGE(strStartEx : %s)", 
					strStartEx);
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
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
	StartEx.exchange_type = atoi(strParamValue.c_str());

	strParamKey = CString(128, 0);
	sprintf((char *)strParamKey.c_str(), "wfscimstartex.ustellerid");
	if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
	{
		return hResult;
	}
	StartEx.teller_id = atoi(strParamValue.c_str());
	
	strParamKey = CString(128, 0);
	sprintf((char *)strParamKey.c_str(), "wfscimstartex.uscount");
	if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
	{
		return hResult;
	}
	StartEx.count = atoi(strParamValue.c_str());

	USHORT usCUNumList[64] = {0};
	for (int nLoop = 0; nLoop < StartEx.count; nLoop ++)
	{
		strParamKey = CString(128, 0);
		sprintf((char *)strParamKey.c_str(), "wfscimstartex.lpuscunumlist[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			return hResult;
		}
		usCUNumList[nLoop] = atoi(strParamValue.c_str());
	}
	StartEx.cu_num_list = usCUNumList;

	LFSCIMOUTPUT WfsCimOutput = {0};
	StartEx.output = &WfsCimOutput;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_START_EXCHANGE,
								&StartEx,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_BANKNOTE_TYPES()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CIM_BANKNOTE_TYPES,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CIM_CAPABILITIES,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_CASH_IN_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CIM_CASH_IN_STATUS,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
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
	LPLFSCIMNOTENUMBERLIST lpNoteNumberList = (LPLFSCIMNOTENUMBERLIST)lpCashIn->note_number_list;
	if (NULL != lpNoteNumberList)
	{
		sprintf((char *)strNoteNumberList.c_str(), "%s"
									"wfscimcashin.lpnotenumberlist.usnumofnotenumbers=%d",
									GetStringSplitChar(),
									lpNoteNumberList->num_of_note_numbers);

		if (NULL != lpNoteNumberList->note_number)
		{
			LPLFSCIMNOTENUMBER lpNoteNumber = NULL;
			for (int nLoop = 0; nLoop < lpNoteNumberList->num_of_note_numbers; nLoop ++)
			{
				lpNoteNumber = lpNoteNumberList->note_number[nLoop];
				if (NULL != lpNoteNumber)
				{
					CString strNoteNumber(256, 0);
					sprintf((char *)strNoteNumber.c_str(), "%s"
											"wfscimcashin.lpnotenumberlist.lppnotenumber[%d].usnoteid=%d"
											"%s"
											"wfscimcashin.lpnotenumberlist.lppnotenumber[%d].ulcount=%d",
											GetStringSplitChar(),
											nLoop, lpNoteNumber->note_id,
											GetStringSplitChar(),
											nLoop, lpNoteNumber->count);

					strNoteNumberList = string(strNoteNumberList.c_str()) + strNoteNumber;
				}
			}
		}
	}

	CString strCimPhCus = "";
	CString strCimPhCu;
	LPLFSCIMPHCU lpPhysical = NULL;
	for (int nLoop = 0; nLoop < lpCashIn->num_physical_cus; nLoop ++)
	{
		lpPhysical = lpCashIn->physical[nLoop];
		if (NULL == lpPhysical)
		{
			continue ;
		}

		strCimPhCu = CString((NULL == lpPhysical->physical_position_name ? 0 : strlen(lpPhysical->physical_position_name))
							+ sizeof(lpPhysical->unit_id)
							+ (NULL == lpPhysical->extra ? 0 : strlen(lpPhysical->extra))
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
							nLoop, (NULL == lpPhysical->physical_position_name ? "NULL" : lpPhysical->physical_position_name),
							GetStringSplitChar(),
							nLoop, CString(lpPhysical->unit_id, sizeof(lpPhysical->unit_id)).c_str(),
							GetStringSplitChar(),
							nLoop, lpPhysical->cash_in_count,
							GetStringSplitChar(),
							nLoop, lpPhysical->count,
							GetStringSplitChar(),
							nLoop, lpPhysical->maximum,
							GetStringSplitChar(),
							nLoop, lpPhysical->p_status,
							GetStringSplitChar(),
							nLoop, (TRUE == lpPhysical->hardware_sensors ? "TRUE" : "false"),
							GetStringSplitChar(), 
							nLoop, (NULL == lpPhysical->extra ? "NULL" : lpPhysical->extra));

		strCimPhCus = string(strCimPhCus.c_str()) + strCimPhCu;
	}

	CString strCashIn(strNoteNumberList.length() + strCimPhCus.length() 
					 + (NULL == lpCashIn->extra ? 0 : strlen(lpCashIn->extra)) + 1024, 0);
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
						lpCashIn->number,
						GetStringSplitChar(),
						lpCashIn->type,
						GetStringSplitChar(),
						lpCashIn->item_type,
						GetStringSplitChar(),
						CString(lpCashIn->unit_id, sizeof(lpCashIn->unit_id)).c_str(),
						GetStringSplitChar(),
						CString(lpCashIn->currency_id, sizeof(lpCashIn->currency_id)).c_str(),
						GetStringSplitChar(),
						lpCashIn->values,
						GetStringSplitChar(),
						lpCashIn->cash_in_count,
						GetStringSplitChar(),
						lpCashIn->count,
						GetStringSplitChar(),
						lpCashIn->maximum,
						GetStringSplitChar(),
						lpCashIn->status,
						GetStringSplitChar(),
						(TRUE == lpCashIn->app_lock ? "TRUE" : "false"),
						strNoteNumberList.c_str(),
						GetStringSplitChar(),
						lpCashIn->num_physical_cus,
						strCimPhCus.c_str(),
						GetStringSplitChar(),
						(NULL == lpCashIn->extra ? "NULL" : lpCashIn->extra));

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
						lpCashInfo->cashin_count);

	if (NULL != lpCashInfo->cash_in)
	{
		CString strCashIn = "";
		LPLFSCIMCASHIN lpCashIn = NULL;

		for (int nLoop = 0; nLoop < lpCashInfo->cashin_count; nLoop ++)
		{
			lpCashIn = lpCashInfo->cash_in[nLoop];
			if (NULL != lpCashIn)
			{
				strCashIn = GetCashInResultString(lpCashIn);

				// GetCashInResultString�������ص��ַ���ǰ׺��wfscimcashin��
				// �˴�ǰ׺Ӧ����Ϊ��wfsresult.lpbuffer.lppcashin[%d]
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

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CIM_CASH_UNIT_INFO,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CIM_STATUS,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
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
		lpWfsRet->result,
		GetStringSplitChar(),
		lpWfsRet->u.command_code,
		GetStringSplitChar());

	if (LFS_SUCCESS != lpWfsRet->result)
	{
		return strWfsResult;
	}

	if (LFS_INF_CIM_STATUS == lpWfsRet->u.command_code)
	{
		LPLFSCIMSTATUS lpStatus = (LPLFSCIMSTATUS)lpWfsRet->buffer;
		if (NULL == lpStatus)
		{
			return strWfsResult;
		}

		LPLFSCIMINPOS * lppPositions = (LPLFSCIMINPOS *)lpStatus->positions;
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
								lpWfsCimInPos1->position,
								GetStringSplitChar(),
								lpWfsCimInPos1->shutter,
								GetStringSplitChar(),
								lpWfsCimInPos1->position_status,
								GetStringSplitChar(),
								lpWfsCimInPos1->transport, 
								GetStringSplitChar(),
								lpWfsCimInPos1->transport_status, 
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
								lpWfsCimInPos2->position,
								GetStringSplitChar(),
								lpWfsCimInPos2->shutter,
								GetStringSplitChar(),
								lpWfsCimInPos2->position_status,
								GetStringSplitChar(),
								lpWfsCimInPos2->transport, 
								GetStringSplitChar(),
								lpWfsCimInPos2->transport_status, 
								GetStringSplitChar());

			strPositions = string(strPositions.c_str()) + strPosition;
		}

		strWfsResult = CString(strPositions.length() + (NULL == lpStatus->extra ? 0 : strlen(lpStatus->extra)) + 1024, 0);
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
							lpStatus->device,
							GetStringSplitChar(),
							lpStatus->safe_door,
							GetStringSplitChar(),
							lpStatus->acceptor,
							GetStringSplitChar(),
							lpStatus->intermediate_stacker,
							GetStringSplitChar(),
							lpStatus->stacker_items,
							GetStringSplitChar(),
							lpStatus->banknote_reader,
							GetStringSplitChar(),
							(TRUE == lpStatus->drop_box ? "TRUE" : "FALSE"),
							GetStringSplitChar(),
							strPositions.c_str(),
							(NULL == lpStatus->extra ? "NULL" : lpStatus->extra));
	 }
	else if (LFS_INF_CIM_BANKNOTE_TYPES == lpWfsRet->u.command_code)
	{
		LPLFSCIMNOTETYPELIST lpNoteTypeList = (LPLFSCIMNOTETYPELIST)lpWfsRet->buffer;
		if (NULL == lpNoteTypeList)
		{
			return strWfsResult;
		}

		LPLFSCIMNOTETYPE lpNoteType = NULL;

		CString strNoteTypeList = "";
		if (NULL != lpNoteTypeList->note_types)
		{
			for (int nLoop = 0; nLoop < lpNoteTypeList->num_of_note_types; nLoop++)
			{
				lpNoteType = lpNoteTypeList->note_types[nLoop];
				if (NULL != lpNoteType)
				{
					CString strNoteType(sizeof(lpNoteType->currency_id) + 2048, 0);
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
						nLoop, lpNoteType->note_id,
						GetStringSplitChar(),
						nLoop, CString(lpNoteType->currency_id, sizeof(lpNoteType->currency_id)).c_str(),
						GetStringSplitChar(),
						nLoop, lpNoteType->values,
						GetStringSplitChar(),
						nLoop, lpNoteType->release,
						GetStringSplitChar(),
						nLoop, (TRUE == lpNoteType->configured ? "TRUE" : "false"));

					strNoteTypeList = string(strNoteTypeList.c_str()) + strNoteType;
				}
			}
		}

		strWfsResult = string(strNoteTypeList.length() + 128, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.usnumofnotetypes=%d"
			"%s",
			LFS_INF_CIM_BANKNOTE_TYPES,
			GetStringSplitChar(),
			lpNoteTypeList->num_of_note_types,
			strNoteTypeList.c_str());
	}
	else if (LFS_INF_CIM_CAPABILITIES == lpWfsRet->u.command_code)
	{
		LPLFSCIMCAPS lpCaps = (LPLFSCIMCAPS)lpWfsRet->buffer;
		if (NULL == lpCaps)
		{
			return strWfsResult;
		}

		strWfsResult = string((NULL == lpCaps->extra ? 0 : strlen(lpCaps->extra)) + 2048, 0);
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
			lpCaps->dev_class,
			GetStringSplitChar(),
			lpCaps->dev_type,
			GetStringSplitChar(),
			lpCaps->max_cashin_items,
			GetStringSplitChar(),
			lpCaps->compound ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->shutter ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->shutter_control ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->safe_door ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->cash_box ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->refill ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->intermediate_stacker,
			GetStringSplitChar(),
			lpCaps->items_taken_sensor ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->items_inserted_sensor ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->positions,
			GetStringSplitChar(),
			lpCaps->exchange_type,
			GetStringSplitChar(),
			lpCaps->retract_areas,
			GetStringSplitChar(),
			lpCaps->retract_transport_actions,
			GetStringSplitChar(),
			lpCaps->retract_stacker_actions,
			GetStringSplitChar(),
			(NULL == lpCaps->extra ? "NULL" : lpCaps->extra));
	}
	else if (LFS_INF_CIM_CASH_IN_STATUS == lpWfsRet->u.command_code)
	{
		LPLFSCIMCASHINSTATUS lpCashInStatus = (LPLFSCIMCASHINSTATUS)lpWfsRet->buffer;
		if (NULL == lpCashInStatus)
		{
			return strWfsResult;
		}

		CString strNoteNumberList(256, 0);
		LPLFSCIMNOTENUMBERLIST lpNoteNumberList = (LPLFSCIMNOTENUMBERLIST)lpCashInStatus->note_number_list;
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
				lpNoteNumberList->num_of_note_numbers);
			if (NULL != lpNoteNumberList->note_number)
			{
				LPLFSCIMNOTENUMBER lpNoteNumber = NULL;

				for (int nLoop = 0; nLoop < lpNoteNumberList->num_of_note_numbers; nLoop++)
				{
					lpNoteNumber = lpNoteNumberList->note_number[nLoop];
					if (NULL != lpNoteNumber)
					{
						CString strNoteNumber(256, 0);
						sprintf((char *)strNoteNumber.c_str(), "%s"
							"wfsresult.lpbuffer.lpnotenumberlist.lppnotenumber[%d].usnoteid=%d"
							"%s"
							"wfsresult.lpbuffer.lpnotenumberlist.lppnotenumber[%d].ulcount=%d",
							GetStringSplitChar(),
							nLoop, lpNoteNumber->note_id,
							GetStringSplitChar(),
							nLoop, lpNoteNumber->count);

						strNoteNumberList = string(strNoteNumberList.c_str()) + strNoteNumber;
					}
				}
			}
		}

		strWfsResult = string((NULL == lpCashInStatus->extra ? 0 : strlen(lpCashInStatus->extra)) + strNoteNumberList.length() + 2048, 0);
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
			lpCashInStatus->status,
			GetStringSplitChar(),
			lpCashInStatus->num_of_refused,
			strNoteNumberList.c_str(),
			GetStringSplitChar(),
			(NULL == lpCashInStatus->extra ? "NULL" : lpCashInStatus->extra));
	}
	else if (LFS_INF_CIM_CASH_UNIT_INFO == lpWfsRet->u.command_code)
	{
		LPLFSCIMCASHINFO lpCashInfo = (LPLFSCIMCASHINFO)lpWfsRet->buffer;
		if (NULL == lpCashInfo)
		{
			return strWfsResult;
		}

		CString strCashIn = GetCashInfoResultString(lpCashInfo);
		strWfsResult = string(strWfsResult.c_str()) + strCashIn;

		// EXE_LFS_CMD_CIM_END_EXCHANGE��������ô�GET_LFS_INF_CIM_CASH_UNIT_INFO���������ڻ�ȡ���ݵ�SP�ļӳ��Ľṹ
		if (TRUE == m_bCashUnitInfo4EndExchange)
		{
			// �����Ҳ��ͷ�LFS���
			m_lpResult4EndExchange = lpWfsRet;
		}
	}
	else if (LFS_INF_CIM_CURRENCY_EXP == lpWfsRet->u.command_code)
	{
		LPLFSCIMCURRENCYEXP * lppCurrencyExp = (LPLFSCIMCURRENCYEXP *)lpWfsRet->buffer;
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
				CString strCurrencyExp(sizeof(lppCurrencyExp[nLoop]->currency_id) + 128, 0);
				sprintf((char *)strCurrencyExp.c_str(), "wfsresult.lpbuffer[%d].ccurrencyid=%s"
					"%s"
					"wfsresult.lpbuffer[%d].sexponent=%d",
					nLoop, CString(lppCurrencyExp[nLoop]->currency_id, sizeof(lppCurrencyExp[nLoop]->currency_id)).c_str(),
					GetStringSplitChar(),
					nLoop, lppCurrencyExp[nLoop]->exponent);
				if ("" != strWfsResult)
				{
					strWfsResult = string(strWfsResult.c_str()) + GetStringSplitChar();
				}

				strWfsResult = string(strWfsResult.c_str()) + strCurrencyExp;
			}
		}
	}
	else if (LFS_INF_CIM_TELLER_INFO == lpWfsRet->u.command_code)
	{
		LPLFSCIMTELLERINFO lpTellerInfo = (LPLFSCIMTELLERINFO)lpWfsRet->buffer;
		if (NULL == lpTellerInfo)
		{
			return strWfsResult;
		}

		strWfsResult = string(sizeof(lpTellerInfo->currency_id) + 1024, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.ustellerid=%d"
			"%s"
			"wfsresult.lpbuffer.ccurrencyid=%s",
			LFS_INF_CIM_TELLER_INFO,
			GetStringSplitChar(),
			lpTellerInfo->teller_id,
			GetStringSplitChar(),
			CString(lpTellerInfo->currency_id, sizeof(lpTellerInfo->currency_id)).c_str());
	}

	return strWfsResult;
}

HRESULT CDCCashAcceptor_30::INF_CIM_GET_P6_INFO()
{
	// ����Ӧ�ö��ԣ��������û���ô������Ҵ�����Ҫ�����£�����ʧ��
	// ��ͬ���У�GET_LFS_INF_CDM_MIX_TYPES��GET_LFS_INF_CDM_MIX_TABLE��GET_LFS_INF_CDM_CURRENCY_EXP
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::INF_CIM_GET_P6_SIGNATURE()
{
	// ����Ӧ�ö��ԣ��������û���ô������Ҵ�����Ҫ�����£�����ʧ��
	// ��ͬ���У�GET_LFS_INF_CDM_MIX_TYPES��GET_LFS_INF_CDM_MIX_TABLE��GET_LFS_INF_CDM_CURRENCY_EXP
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CASH_IN()
{
	CString strTrace(128, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_CASH_IN()");
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CASH_IN,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);
	
	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CASH_IN_END()
{
	CString strTrace(128, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_CASH_IN_END()");
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CASH_IN_END,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);
	
	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CASH_IN_ROLLBACK()
{
	CString strTrace(128, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_CASH_IN_ROLLBACK()");
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CASH_IN_ROLLBACK,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CASH_IN_START(long lInputPosition, long lOutputPosition, long lUseRecycleUnits)
{
	CString strTrace(128, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_CASH_IN_START()");
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
	HRESULT hResult = DC_ERROR;

	LFSCIMCASHINSTART CashInStart = {0};
	CashInStart.teller_id = 0;
	CashInStart.use_recycle_units = (0 == lUseRecycleUnits ? FALSE : TRUE);
	CashInStart.input_position = (WORD)lInputPosition;
	CashInStart.output_position = (WORD)lOutputPosition;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CASH_IN_START,
								&CashInStart,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CLOSE_SHUTTER(long lPosition) 
{
	CString strTrace(128, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_CLOSE_SHUTTER(lPosition : %d)", lPosition);
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
	HRESULT hResult = DC_ERROR;

	WORD fwPosition = (WORD)lPosition;
	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_CLOSE_SHUTTER,
								&fwPosition,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CONFIGURE_CASH_IN_UNITS(LPCTSTR strCashInType) 
{
	// ����������Ӳ������ʹʹ�����й��߽��У�Ӧ�ò�֧��
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CONFIGURE_NOTETYPES(LPCTSTR strNoteIDs) 
{
	CString strTrace(strlen(strNoteIDs) + 128, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_CONFIGURE_NOTETYPES(strNoteIDs : %s)", strNoteIDs);
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
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
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_CREATE_P6_SIGNATURE()
{
	// ����Ӧ�ö��ԣ��������û���ô�����δʵ��
	return (short)DC_ERROR;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_END_EXCHANGE(LPCTSTR strCUInfo) 
{
	CString strTrace(strlen(strCUInfo) + 128, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_END_EXCHANGE(strCUInfo : %s)",
					strCUInfo);
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
	HRESULT hResult = DC_ERROR;

	// ����GET_LFS_INF_CIM_CASH_UNIT_INFO��ȡ����ṹ
	if (NULL != m_lpResult4EndExchange)  // ��ֹ�в����ڴ�û���ͷ�
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

	// ���ȴ�INF_CIM_CASH_UNIT_INFO 30��ȡ״̬��ɣ���ȡ����ṹ�Խ����������
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

	LPLFSCIMCASHINFO lpCashInfo = (LPLFSCIMCASHINFO)m_lpResult4EndExchange->buffer;
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
 	for (int nLoop = 0; nLoop < lpCashInfo->cashin_count; nLoop ++)
	{
		lpCashIn = lpCashInfo->cash_in[nLoop];
		if (NULL != lpCashIn)
		{
			if(TRUE == bEndWithClean)
			{
				lpCashIn->count = 0;
				lpCashIn->cash_in_count = 0;
				lpCashIn->note_number_list = NULL;
				lpCashIn->status = LFS_CIM_STATCUEMPTY;
			}
			else
			{
				// ����������ı�
				// ���ı���
				strParamKey = CString(128, 0);
				sprintf((char *)strParamKey.c_str(), "wfsresult.lpbuffer.lppcashin[%d].ccurrencyid", nLoop);
				if (TRUE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
				{
					if (strParamValue.length() > 3)
					{
						m_bCashUnitInfo4EndExchange = FALSE;

						LFSFreeResult(m_lpResult4EndExchange);
						m_lpResult4EndExchange = NULL;

						printf("if (strParamValue.length() > 3)\n");
						return (short)DC_ERROR;
					}
					
					memset(lpCashIn->currency_id, 0, sizeof(lpCashIn->currency_id));
					memcpy(	lpCashIn->currency_id, 
							strParamValue.c_str(),
							strParamValue.length());
				}

				// ������ֵ
				strParamKey = CString(128, 0);
				sprintf((char *)strParamKey.c_str(), "wfsresult.lpbuffer.lppcashin[%d].ulvalues", nLoop);
				if (TRUE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
				{
					lpCashIn->values = atoi(strParamValue.c_str());
				}
			}

			LPLFSCIMPHCU lpPhysical = NULL;
			
			for (int jLoop = 0; jLoop < lpCashIn->num_physical_cus; jLoop ++)
			{
				lpPhysical = lpCashIn->physical[jLoop];
				if (NULL != lpPhysical)
				{
					if(TRUE == bEndWithClean)
					{
						lpPhysical->count = 0;
						lpPhysical->cash_in_count = 0;
						lpPhysical->p_status = LFS_CIM_STATCUEMPTY;
					}
					else
					{
						// ����������ı䣬���߸��ı��ֺ���ֵʱ����Ҫ�Ķ���������
					}
				}
			}
		}
	}

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_END_EXCHANGE,
								lpCashInfo,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);
	
	m_bCashUnitInfo4EndExchange = FALSE;

	LFSFreeResult(m_lpResult4EndExchange);
	m_lpResult4EndExchange = NULL;

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_OPEN_SAFE_DOOR() 
{
	CString strTrace(128, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_OPEN_SAFE_DOOR()");
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_OPEN_SAFE_DOOR,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_OPEN_SHUTTER(long lPosition) 
{
	CString strTrace(128, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_OPEN_SHUTTER(lPosition : %d)", lPosition);
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
	HRESULT hResult = DC_ERROR;

	WORD fwPosition = (WORD)lPosition;
	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_OPEN_SHUTTER,
								&fwPosition,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);
	
	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_RESET(long lNumber, long lResetPosition, long lRetractArea, long lRetractIndex, long lRetractPosition) 
{
	CString strTrace(256, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_RESET(lNumber : %d, lResetPosition : %d, lRetractArea : %d, lRetractIndex : %d, lRetractPosition : %d)", 
					lNumber, lResetPosition, lRetractArea, lRetractIndex, lRetractPosition);
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
	HRESULT hResult = DC_ERROR;

	LFSCIMRETRACT Retract = {0};
	Retract.output_position = (WORD)lRetractPosition;
	Retract.retract_area = (USHORT)lRetractArea;
	Retract.index = (USHORT)lRetractIndex;

	LFSCIMITEMPOSITION ResetIn = {0};
	ResetIn.output_position = (WORD)lResetPosition;
	ResetIn.output_position = (USHORT)lNumber;
	ResetIn.retract_area = &Retract;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_RESET,
								&ResetIn,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashAcceptor_30::CMD_CIM_RETRACT(long lRetractArea, long lRetractIndex, long lRetractPosition) 
{
	CString strTrace(256, 0);
	sprintf((char *)strTrace.c_str(), "EXE_LFS_CMD_CIM_RETRACT(lRetractArea : %d, lRetractIndex : %d, lRetractPosition : %d)", 
					lRetractArea, lRetractIndex, lRetractPosition);
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());
	
	HRESULT hResult = DC_ERROR;

	LFSCIMRETRACT Retract = {0};
	Retract.output_position = (WORD)lRetractPosition;
	Retract.retract_area = (USHORT)lRetractArea;
	Retract.index = (USHORT)lRetractIndex;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CIM_RETRACT,
								&Retract,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}
