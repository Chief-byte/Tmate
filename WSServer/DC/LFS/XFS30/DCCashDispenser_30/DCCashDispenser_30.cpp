// DCCashDispenser_30.cpp: implementation of the CDCCashDispenser_30 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCCashDispenser_30.h"
#include "JavaScriptStringParam.h"
#include <unistd.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDCCashDispenser_30::CDCCashDispenser_30(LPCTSTR strDCName, LPCTSTR strTraceComponent)
{
	m_strDCName = strDCName;
	m_strTraceComponent = CString(strTraceComponent);
	m_DCObject.m_bWosaXFSRun = FALSE;

	m_bCashUnitInfo4EndExchange = FALSE;
	m_lpResult4EndExchange = NULL;
}

CDCCashDispenser_30::~CDCCashDispenser_30()
{

}

HRESULT CDCCashDispenser_30::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// ��������
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_CDM_DENOMINATE"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_DENOMINATE(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "ulamount").c_str()), 
										CJSStringParam::GetStringParam(strarrParams, "ccurrencyid").c_str(),
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "usmixnumber").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_DISPENSE"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_DISPENSE(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "ulamount").c_str()), 
									CJSStringParam::GetStringParam(strarrParams, "ccurrencyid").c_str(),
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "usmixnumber").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwposition").c_str()), 
									(BOOL)atol(CJSStringParam::GetStringParam(strarrParams, "bpresent").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_COUNT"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_COUNT(	CJSStringParam::GetStringParam(strarrParams, "lpphysicalpositionname").c_str(),
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwposition").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_PRESENT"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_PRESENT((short)atol(CJSStringParam::GetStringParam(strarrParams, "lpfwposition").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_REJECT"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_REJECT();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_RETRACT"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_RETRACT(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "usretractarea").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "usindex").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwoutputposition").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_OPEN_SHUTTER"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_OPEN_SHUTTER((short)atol(CJSStringParam::GetStringParam(strarrParams, "lpfwposition").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_CLOSE_SHUTTER"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_CLOSE_SHUTTER((short)atol(CJSStringParam::GetStringParam(strarrParams, "lPosition").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_SET_TELLER_INFO"))
	{
		// ��ʹ�ô˷���
		// bValid = TRUE;
		// hResult = CMD_CDM_SET_TELLER_INFO();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_SET_CASH_UNIT_INFO"))
	{
		// ��ʹ�ô˷���
		// bValid = TRUE;
		// hResult = CMD_CDM_SET_CASH_UNIT_INFO();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_START_EXCHANGE"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_START_EXCHANGE(strSingleParam.c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_END_EXCHANGE"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_END_EXCHANGE(strSingleParam.c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_OPEN_SAFE_DOOR"))
	{
		// ��ʹ�ô˷���
		// bValid = TRUE;
		// hResult = CMD_CDM_OPEN_SAFE_DOOR();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_CALIBRATE_CASH_UNIT"))
	{
		// ��ʹ�ô˷���
		// bValid = TRUE;
		// hResult = CMD_CDM_CALIBRATE_CASH_UNIT();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_SET_MIX_TABLE"))
	{
		// ��ʹ�ô˷���
		// bValid = TRUE;
		// hResult = CMD_CDM_SET_MIX_TABLE();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_RESET"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_RESET(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "usnumber").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "usretractarea").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "usindex").c_str()), 
									(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwoutputposition").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CDM_TEST_CASH_UNITS"))
	{
		bValid = TRUE;
		hResult = CMD_CDM_TEST_CASH_UNITS(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "usnumber").c_str()), 
											(short)atol(CJSStringParam::GetStringParam(strarrParams, "usretractarea").c_str()), 
											(short)atol(CJSStringParam::GetStringParam(strarrParams, "usindex").c_str()), 
											(short)atol(CJSStringParam::GetStringParam(strarrParams, "fwoutputposition").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CDM_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_CDM_CAPABILITIES();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CDM_CASH_UNIT_INFO"))
	{
		bValid = TRUE;
		hResult = INF_CDM_CASH_UNIT_INFO();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CDM_CURRENCY_EXP"))
	{
		bValid = TRUE;
		hResult = INF_CDM_CURRENCY_EXP();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CDM_MIX_TABLE"))
	{
		bValid = TRUE;
		hResult = INF_CDM_MIX_TABLE();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CDM_MIX_TYPES"))
	{
		bValid = TRUE;
		hResult = INF_CDM_MIX_TYPES();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CDM_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_CDM_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CDM_PRESENT_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_CDM_PRESENT_STATUS((short)atol(CJSStringParam::GetStringParam(strarrParams, "lpfwposition").c_str()));
	}

	return hResult;
}

CString CDCCashDispenser_30::HandleEXEEvtResult(LPLFSRESULT lpWfsRet)
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
		case LFS_EXEE_CDM_DELAYEDDISPENSE:
			break;
		case LFS_EXEE_CDM_STARTDISPENSE:
			break;
		case LFS_EXEE_CDM_CASHUNITERROR:
			{
				LPLFSCDMCUERROR lpCashUnitError = (LPLFSCDMCUERROR)lpWfsRet->buffer;
				if (NULL == lpCashUnitError)
				{
					break ;
				}

				LPLFSCDMCASHUNIT lpWfsCdmCashUnit = (LPLFSCDMCASHUNIT)lpCashUnitError->cash_unit;
				if (NULL == lpWfsCdmCashUnit)
				{
					break ;
				}

				strEvtResult = CString(256, 0);
				sprintf((char *)strEvtResult.c_str(), "wfsresult.lpbuffer.wfailure=%d"
									"%s"
									"wfsresult.lpbuffer.lpcashunit.usnumber=%d"
									"%s"
									"wfsresult.u.dweventid=%d",
									lpCashUnitError->failure,
									GetStringSplitChar(),
									lpWfsCdmCashUnit->number,
									GetStringSplitChar(),
									lpWfsRet->u.event_id);

				break;
			}
		case LFS_EXEE_CDM_PARTIALDISPENSE:
			break;
		case LFS_EXEE_CDM_SUBDISPENSEOK:
			break;
		case LFS_EXEE_CDM_INCOMPLETEDISPENSE:
			break;
		case LFS_EXEE_CDM_NOTEERROR:
			break;
		default:
			break;
	}

	strWfsResult = string(strWfsResult.c_str()) + strEvtResult;

	return strWfsResult;
}

CString CDCCashDispenser_30::HandleUSEREvtResult(LPLFSRESULT lpWfsRet)
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

	return strWfsResult;
}

CString CDCCashDispenser_30::HandleSRVEvtResult(LPLFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	// �����Ҫʹ��LFS_SRVE_CDM_MEDIADETECTED�¼�����Ҫע��WOSA�ĵ��е�LFS_SRVE_CDM_MEDIADETECTED�¼��Ĳ���
	// �������"LPLFSCDMITEMPOSITION * lpItemPosition"
	// ��������壬����LP??? * ����ı�����Ӧ��lpp��ͷ�������lp��ͷ����Ӧ����ֻ��LP???
	// CIM�ĵ������û�����⣬û��"*"
	// ����ȡ����Ӧ��Ϊ"LPLFSCDMITEMPOSITION lpItemPosition"��û��"*"�����˴�����Ҫָ�����飬����Ҫ��ָ������ҲӦ����CIM����ʹ��

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d"
						"%s"
						"wfsresult.u.dweventid=%d",
						lpWfsRet->result,
						GetStringSplitChar(),
						lpWfsRet->u.event_id);

	return strWfsResult;
}

CString CDCCashDispenser_30::HandleSysEvtResult(LPLFSRESULT lpWfsRet)
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

CString	CDCCashDispenser_30::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[17]={
		{"WFS_CMD_CDM_DENOMINATE"              ,CDM_SERVICE_OFFSET + 1},
		{"WFS_CMD_CDM_DISPENSE"                ,CDM_SERVICE_OFFSET + 2},
		{"WFS_CMD_CDM_PRESENT"                 ,CDM_SERVICE_OFFSET + 3},
		{"WFS_CMD_CDM_REJECT"                  ,CDM_SERVICE_OFFSET + 4},
		{"WFS_CMD_CDM_RETRACT"                 ,CDM_SERVICE_OFFSET + 5},
		{"WFS_CMD_CDM_OPEN_SHUTTER"            ,CDM_SERVICE_OFFSET + 7},
		{"WFS_CMD_CDM_CLOSE_SHUTTER"           ,CDM_SERVICE_OFFSET + 8},
		{"WFS_CMD_CDM_SET_TELLER_INFO"         ,CDM_SERVICE_OFFSET + 9},
		{"WFS_CMD_CDM_SET_CASH_UNIT_INFO"      ,CDM_SERVICE_OFFSET + 10},
		{"WFS_CMD_CDM_START_EXCHANGE"          ,CDM_SERVICE_OFFSET + 11},
		{"WFS_CMD_CDM_END_EXCHANGE"            ,CDM_SERVICE_OFFSET + 12},
		{"WFS_CMD_CDM_OPEN_SAFE_DOOR"          ,CDM_SERVICE_OFFSET + 13},
		{"WFS_CMD_CDM_CALIBRATE_CASH_UNIT"     ,CDM_SERVICE_OFFSET + 15},
		{"WFS_CMD_CDM_SET_MIX_TABLE"           ,CDM_SERVICE_OFFSET + 20},
		{"WFS_CMD_CDM_RESET"                   ,CDM_SERVICE_OFFSET + 21},
		{"WFS_CMD_CDM_TEST_CASH_UNITS"         ,CDM_SERVICE_OFFSET + 22},
		{"WFS_CMD_CDM_COUNT"                   ,CDM_SERVICE_OFFSET + 23}
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

CString	CDCCashDispenser_30::GetXFSMsgStr(DWORD dwEventID)
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

		{"WFS_SRVE_CDM_SAFEDOOROPEN"           ,(CDM_SERVICE_OFFSET + 1)},
		{"WFS_SRVE_CDM_SAFEDOORCLOSED"         ,(CDM_SERVICE_OFFSET + 2)},
		{"WFS_USRE_CDM_CASHUNITTHRESHOLD"      ,(CDM_SERVICE_OFFSET + 3)},
		{"WFS_SRVE_CDM_CASHUNITINFOCHANGED"    ,(CDM_SERVICE_OFFSET + 4)},
		{"WFS_SRVE_CDM_TELLERINFOCHANGED"      ,(CDM_SERVICE_OFFSET + 5)},
		{"WFS_EXEE_CDM_DELAYEDDISPENSE"        ,(CDM_SERVICE_OFFSET + 6)},
		{"WFS_EXEE_CDM_STARTDISPENSE"          ,(CDM_SERVICE_OFFSET + 7)},
		{"WFS_EXEE_CDM_CASHUNITERROR"          ,(CDM_SERVICE_OFFSET + 8)},
		{"WFS_SRVE_CDM_ITEMSTAKEN"             ,(CDM_SERVICE_OFFSET + 9)},
		{"WFS_EXEE_CDM_PARTIALDISPENSE"        ,(CDM_SERVICE_OFFSET + 10)},
		{"WFS_EXEE_CDM_SUBDISPENSEOK"          ,(CDM_SERVICE_OFFSET + 11)},
		{"WFS_SRVE_CDM_ITEMSPRESENTED"         ,(CDM_SERVICE_OFFSET + 13)},
		{"WFS_SRVE_CDM_COUNTS_CHANGED"        ,(CDM_SERVICE_OFFSET + 14)},
		{"WFS_EXEE_CDM_INCOMPLETEDISPENSE"     ,(CDM_SERVICE_OFFSET + 15)},
		{"WFS_EXEE_CDM_NOTEERROR"              ,(CDM_SERVICE_OFFSET + 16)},
		{"WFS_EXEE_CDM_MEDIADETECTED"          ,(CDM_SERVICE_OFFSET + 17)},
		{"WFS_SRVE_CDM_MEDIADETECTED"          ,(CDM_SERVICE_OFFSET + 17)}
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

CString	CDCCashDispenser_30::GetXFSSysEvtStr(DWORD dwEventID)
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

CString	CDCCashDispenser_30::GetXFSErrStr(HRESULT hResult)
{
	if (hResult >= DC_ERROR && hResult < LFS_ERR_UNSUPP_DATA)
	{
		return "DC_ERROR";
	}

	struct XFSERR {
		char strErr[128];
		LONG iErr;
	}XFSErr[87]={
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
		{"WFS_ERR_CDM_INVALIDCURRENCY"         ,-(CDM_SERVICE_OFFSET + 0)},
		{"WFS_ERR_CDM_INVALIDTELLERID"         ,-(CDM_SERVICE_OFFSET + 1)},
		{"WFS_ERR_CDM_CASHUNITERROR"           ,-(CDM_SERVICE_OFFSET + 2)},
		{"WFS_ERR_CDM_INVALIDDENOMINATION"     ,-(CDM_SERVICE_OFFSET + 3)},
		{"WFS_ERR_CDM_INVALIDMIXNUMBER"        ,-(CDM_SERVICE_OFFSET + 4)},
		{"WFS_ERR_CDM_NOCURRENCYMIX"           ,-(CDM_SERVICE_OFFSET + 5)},
		{"WFS_ERR_CDM_NOTDISPENSABLE"          ,-(CDM_SERVICE_OFFSET + 6)},
		{"WFS_ERR_CDM_TOOMANYITEMS"            ,-(CDM_SERVICE_OFFSET + 7)},
		{"WFS_ERR_CDM_UNSUPPOSITION"           ,-(CDM_SERVICE_OFFSET + 8)},
		{"WFS_ERR_CDM_SAFEDOOROPEN"            ,-(CDM_SERVICE_OFFSET + 10)},
		{"WFS_ERR_CDM_SHUTTERNOTOPEN"          ,-(CDM_SERVICE_OFFSET + 12)},
		{"WFS_ERR_CDM_SHUTTEROPEN"             ,-(CDM_SERVICE_OFFSET + 13)},
		{"WFS_ERR_CDM_SHUTTERCLOSED"           ,-(CDM_SERVICE_OFFSET + 14)},
		{"WFS_ERR_CDM_INVALIDCASHUNIT"         ,-(CDM_SERVICE_OFFSET + 15)},
		{"WFS_ERR_CDM_NOITEMS"                 ,-(CDM_SERVICE_OFFSET + 16)},
		{"WFS_ERR_CDM_EXCHANGEACTIVE"          ,-(CDM_SERVICE_OFFSET + 17)},
		{"WFS_ERR_CDM_NOEXCHANGEACTIVE"        ,-(CDM_SERVICE_OFFSET + 18)},
		{"WFS_ERR_CDM_SHUTTERNOTCLOSED"        ,-(CDM_SERVICE_OFFSET + 19)},
		{"WFS_ERR_CDM_PRERRORNOITEMS"          ,-(CDM_SERVICE_OFFSET + 20)},
		{"WFS_ERR_CDM_PRERRORITEMS"            ,-(CDM_SERVICE_OFFSET + 21)},
		{"WFS_ERR_CDM_PRERRORUNKNOWN"          ,-(CDM_SERVICE_OFFSET + 22)},
		{"WFS_ERR_CDM_ITEMSTAKEN"              ,-(CDM_SERVICE_OFFSET + 23)},
		{"WFS_ERR_CDM_INVALIDMIXTABLE"         ,-(CDM_SERVICE_OFFSET + 27)},
		{"WFS_ERR_CDM_OUTPUTPOS_NOT_EMPTY"     ,-(CDM_SERVICE_OFFSET + 28)},
		{"WFS_ERR_CDM_INVALIDRETRACTPOSITION"  ,-(CDM_SERVICE_OFFSET + 29)},
		{"WFS_ERR_CDM_NOTRETRACTAREA"          ,-(CDM_SERVICE_OFFSET + 30)},
		{"WFS_ERR_CDM_NOCASHBOXPRESENT"        ,-(CDM_SERVICE_OFFSET + 33)},
		{"WFS_ERR_CDM_AMOUNTNOTINMIXTABLE"     ,-(CDM_SERVICE_OFFSET + 34)},
		{"WFS_ERR_CDM_ITEMSNOTTAKEN"           ,-(CDM_SERVICE_OFFSET + 35)},
		{"WFS_ERR_CDM_ITEMSLEFT"               ,-(CDM_SERVICE_OFFSET + 36)}
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

CString CDCCashDispenser_30::HandleCmdErr(LPLFSRESULT lpWfsRet)
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

CString CDCCashDispenser_30::HandleCmdResult(LPLFSRESULT lpWfsRet)
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
		case LFS_CMD_CDM_DENOMINATE:
		{
			// ��break ;�������LFS_CMD_CDM_DISPENSE��֧��LFS_CMD_CDM_DENOMINATE��֧������LFSCDMDENOMINATION�ṹ
			// break ;
		}
		case LFS_CMD_CDM_DISPENSE:
		{
			// ע�⣺�����LFS_CMD_CDM_DENOMINATE��֧����������û��break ;���ʻ����ô˷�֧�Ĵ���

			LPLFSCDMDENOMINATION lpDenomination = (LPLFSCDMDENOMINATION)lpWfsRet->buffer;
			if (NULL == lpDenomination)
			{
				break ;
			}

			strCmdResult = CString(256, 0);
			sprintf((char *)strCmdResult.c_str(), "%s"
								"wfsresult.lpbuffer.count=%d",
								GetStringSplitChar(),
								lpDenomination->count);

			if (NULL != lpDenomination->values)
			{
				for (int nLoop = 0; nLoop < lpDenomination->count; nLoop ++) 
				{
					CString strDenomination(256, 0);
					sprintf((char *)strDenomination.c_str(), "%s"
											"wfsresult.lpbuffer.lpulValues[%d]=%d", 
											GetStringSplitChar(),
											nLoop, lpDenomination->values[nLoop]);

					strCmdResult = string(strCmdResult.c_str()) + strDenomination;
				}
			}

			break ;
		}
		case LFS_CMD_CDM_PRESENT:
			break ;
		case LFS_CMD_CDM_REJECT:
		case LFS_CMD_CDM_RETRACT:
		case LFS_CMD_CDM_OPEN_SHUTTER:
		case LFS_CMD_CDM_CLOSE_SHUTTER:
		case LFS_CMD_CDM_SET_TELLER_INFO:
		case LFS_CMD_CDM_SET_CASH_UNIT_INFO:
		case LFS_CMD_CDM_START_EXCHANGE:
		case LFS_CMD_CDM_END_EXCHANGE:
		case LFS_CMD_CDM_OPEN_SAFE_DOOR:
		case LFS_CMD_CDM_CALIBRATE_CASH_UNIT:
		case LFS_CMD_CDM_SET_MIX_TABLE:
		case LFS_CMD_CDM_RESET:
			break ;
		case LFS_CMD_CDM_TEST_CASH_UNITS:
			break ;
		case LFS_CMD_CDM_COUNT:
		{
			LPLFSCDMCOUNT lpCount = (LPLFSCDMCOUNT)lpWfsRet->buffer;
			if (NULL == lpCount)
			{
				break ;
			}

			LPLFSCDMCOUNTEDPHYSCU * lppCountedPhysCUs = lpCount->counted_phys_cus;
			if (NULL == lppCountedPhysCUs)
			{
				break ;
			}

			strCmdResult = CString(256, 0);
			sprintf((char *)strCmdResult.c_str(), "%s"
								"wfsresult.lpbuffer.usnumphysicalcus=%d",
								GetStringSplitChar(),
								lpCount->num_physical_cus);

			for (int nLoop = 0; nLoop < lpCount->num_physical_cus; nLoop ++)
			{
				if (NULL != lppCountedPhysCUs[nLoop])
				{
					CString strCdmCountedPhysCu((NULL == lppCountedPhysCUs[nLoop]->physical_position_name ? 0 : strlen(lppCountedPhysCUs[nLoop]->physical_position_name))
												+ sizeof(lppCountedPhysCUs[nLoop]->unit_id)
												+ 1024, 0);
					sprintf((char *)strCdmCountedPhysCu.c_str(), "%s"
												"wfsresult.lpbuffer.lppcountedphyscus[%d].lpphysicalpositionname=%s"
												"%s"
												"wfsresult.lpbuffer.lppcountedphyscus[%d].cunitid=%s"
												"%s"
												"wfsresult.lpbuffer.lppcountedphyscus[%d].uldispensed=%d"
												"%s"
												"wfsresult.lpbuffer.lppcountedphyscus[%d].ulcounted=%d"
												"%s"
												"wfsresult.lpbuffer.lppcountedphyscus[%d].uspstatus=%d",
												GetStringSplitChar(),
												nLoop, (NULL == lppCountedPhysCUs[nLoop]->physical_position_name ? "NULL" : lppCountedPhysCUs[nLoop]->physical_position_name),
												GetStringSplitChar(),
												nLoop, CString(lppCountedPhysCUs[nLoop]->unit_id, sizeof(lppCountedPhysCUs[nLoop]->unit_id)).c_str(),
												GetStringSplitChar(),
												nLoop, lppCountedPhysCUs[nLoop]->dispensed,
												GetStringSplitChar(),
												nLoop, lppCountedPhysCUs[nLoop]->counted,
												GetStringSplitChar(),
												nLoop, lppCountedPhysCUs[nLoop]->p_status);

					strCmdResult = string(strCmdResult.c_str()) + strCdmCountedPhysCu;
				}
			}
			break ;
		}
		default :
			break ;
	}

	strWfsResult = string(strWfsResult.c_str()) + strCmdResult;

	return strWfsResult;
}

int CDCCashDispenser_30::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			printf("LFS_OPEN_COMPLETE CDCCashDispenser_30\n");
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

			if (FALSE == m_bCashUnitInfo4EndExchange)  // LFS_CMD_CDM_END_EXCHANGE������Ҫʹ�ô�״̬��Ϣ�еĳ���ṹ��EndExchangeʹ����Ϻ����ͷ�
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

HRESULT CDCCashDispenser_30::INF_CDM_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CDM_STATUS,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

CString CDCCashDispenser_30::HandleInfResult(LPLFSRESULT lpWfsRet)
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

	CString strCmdResult = "";

	if (LFS_INF_CDM_STATUS == lpWfsRet->u.command_code)
	{
		LPLFSCDMSTATUS lpStatus = (LPLFSCDMSTATUS)lpWfsRet->buffer;
		if (NULL == lpStatus)
		{
			return strWfsResult;
		}

		LPLFSCDMOUTPOS * lppPositions = (LPLFSCDMOUTPOS *)lpStatus->positions;

		CString strPositions = "";
		CString strPosition = "";

		if (NULL != lppPositions)
		{
			for (int nLoop = 0; NULL != lppPositions[nLoop]; nLoop ++)
			{
				strPosition = CString(1024, 0);
				sprintf((char *)strPosition.c_str(), "wfsresult.lpbuffer.lpppositions[%d].fwposition=%d"
									"%s"
									"wfsresult.lpbuffer.lpppositions[%d].fwshutter=%d"
									"%s"
									"wfsresult.lpbuffer.lpppositions[%d].fwpositionstatus=%d"
									"%s"
									"wfsresult.lpbuffer.lpppositions[%d].fwtransport=%d"
									"%s"
									"wfsresult.lpbuffer.lpppositions[%d].fwtransportstatus=%d"
									"%s",
									nLoop, lppPositions[nLoop]->position,
									GetStringSplitChar(),
									nLoop, lppPositions[nLoop]->shutter,
									GetStringSplitChar(),
									nLoop, lppPositions[nLoop]->position_status,
									GetStringSplitChar(),
									nLoop, lppPositions[nLoop]->transport, 
									GetStringSplitChar(),
									nLoop, lppPositions[nLoop]->transport_status, 
									GetStringSplitChar());

				strPositions = string(strPositions.c_str()) + strPosition;
			}
		}

		strWfsResult = CString(strPositions.length() + (NULL == lpStatus->extra ? 0 : strlen(lpStatus->extra)) + 1024, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
							"%s"
							"wfsresult.lpbuffer.fwdevice=%d"
							"%s"
							"wfsresult.lpbuffer.fwsafedoor=%d"
							"%s"
							"wfsresult.lpbuffer.fwdispenser=%d"
							"%s"
							"wfsresult.lpbuffer.fwintermediatestacker=%d"
							"%s"
							"%s"  // "wfsresult.lpbuffer.lpppositions=%d"
							"wfsresult.lpbuffer.lpszextra=%s",
							LFS_INF_CDM_STATUS,
							GetStringSplitChar(),
							lpStatus->device,
							GetStringSplitChar(),
							lpStatus->safe_door,
							GetStringSplitChar(),
							lpStatus->dispenser,
							GetStringSplitChar(),
							lpStatus->intermediate_stacker,
							GetStringSplitChar(),
							strPositions.c_str(),
							(NULL == lpStatus->extra ? "NULL" : lpStatus->extra));
	}
	else if (LFS_INF_CDM_CAPABILITIES == lpWfsRet->u.command_code)
	{
		LPLFSCDMCAPS lpCaps = (LPLFSCDMCAPS)lpWfsRet->buffer;
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
			"wfsresult.lpbuffer.wmaxdispenseitems=%d"
			"%s"
			"wfsresult.lpbuffer.bcompound=%s"
			"%s"
			"wfsresult.lpbuffer.bshutter=%s"
			"%s"
			"wfsresult.lpbuffer.bshuttercontrol=%s"
			"%s"
			"wfsresult.lpbuffer.fwretractareas=%d"
			"%s"
			"wfsresult.lpbuffer.fwretracttransportactions=%d"
			"%s"
			"wfsresult.lpbuffer.fwretractstackeractions=%d"
			"%s"
			"wfsresult.lpbuffer.bsafedoor=%s"
			"%s"
			"wfsresult.lpbuffer.bcashbox=%s"
			"%s"
			"wfsresult.lpbuffer.bintermediatestacker=%s"
			"%s"
			"wfsresult.lpbuffer.bitemstakensensor=%s"
			"%s"
			"wfsresult.lpbuffer.fwpositions=%d"
			"%s"
			"wfsresult.lpbuffer.fwmoveitems=%d"
			"%s"
			"wfsresult.lpbuffer.fwexchangetype=%d"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_CDM_CAPABILITIES,
			GetStringSplitChar(),
			lpCaps->dev_class,
			GetStringSplitChar(),
			lpCaps->dev_type,
			GetStringSplitChar(),
			lpCaps->max_dispense_items,
			GetStringSplitChar(),
			lpCaps->compound ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->shutter ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->shutter_control ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->retract_areas,
			GetStringSplitChar(),
			lpCaps->retract_transport_actions,
			GetStringSplitChar(),
			lpCaps->retract_stacker_actions,
			GetStringSplitChar(),
			lpCaps->safe_door ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->cash_box ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->intermediate_stacker ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->items_taken_sensor ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->positions,
			GetStringSplitChar(),
			lpCaps->move_items,
			GetStringSplitChar(),
			lpCaps->exchange_type,
			GetStringSplitChar(),
			(NULL == lpCaps->extra ? "NULL" : lpCaps->extra));
	}
	else if (LFS_INF_CDM_CASH_UNIT_INFO == lpWfsRet->u.command_code)
	{
		LPLFSCDMCUINFO lpCashUnitInfo = (LPLFSCDMCUINFO)lpWfsRet->buffer;
		if (NULL == lpCashUnitInfo)
		{
			return strWfsResult;
		}

		strWfsResult = CString(256, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.ustellerid=%d"
			"%s"
			"wfsresult.lpbuffer.uscount=%d",
			LFS_INF_CDM_CASH_UNIT_INFO,
			GetStringSplitChar(),
			lpCashUnitInfo->teller_id,
			GetStringSplitChar(),
			lpCashUnitInfo->count);

		CString strCashUnitInfo;
		CString strCdmCashUnit;
		CString strCdmPhCu;
		LPLFSCDMCASHUNIT lpList = NULL;
		for (int nLoop = 0; nLoop < lpCashUnitInfo->count; nLoop++)
		{
			lpList = lpCashUnitInfo->list[nLoop];
			if (NULL == lpList)
			{
				continue;
			}

			strCdmCashUnit = CString((NULL == lpList->cash_unit_name ? 0 : strlen(lpList->cash_unit_name))
				+ sizeof(lpList->unit_id)
				+ sizeof(lpList->currency_id) + 2048, 0);
			sprintf((char *)strCdmCashUnit.c_str(), "%s"
				"wfsresult.lpbuffer.lpplist[%d].usnumber=%d"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].ustype=%d"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].lpszcashunitname=%s"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].cunitid=%s"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].ccurrencyid=%s"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].ulvalues=%d"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].ulinitialcount=%d"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].ulcount=%d"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].ulrejectcount=%d"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].ulminimum=%d"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].ulmaximum=%d"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].bapplock=%s"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].usstatus=%d"
				"%s"
				"wfsresult.lpbuffer.lpplist[%d].usnumphysicalcus=%d",
				GetStringSplitChar(),
				nLoop, lpList->number,
				GetStringSplitChar(),
				nLoop, lpList->type,
				GetStringSplitChar(),
				nLoop, (NULL == lpList->cash_unit_name ? "NULL" : lpList->cash_unit_name),
				GetStringSplitChar(),
				nLoop, CString(lpList->unit_id, sizeof(lpList->unit_id)).c_str(),
				GetStringSplitChar(),
				nLoop, CString(lpList->currency_id, sizeof(lpList->currency_id)).c_str(),
				GetStringSplitChar(),
				nLoop, lpList->values,
				GetStringSplitChar(),
				nLoop, lpList->initial_count,
				GetStringSplitChar(),
				nLoop, lpList->count,
				GetStringSplitChar(),
				nLoop, lpList->reject_count,
				GetStringSplitChar(),
				nLoop, lpList->minimum,
				GetStringSplitChar(),
				nLoop, lpList->maximum,
				GetStringSplitChar(),
				nLoop, (TRUE == lpList->app_lock ? "TRUE" : "false"),
				GetStringSplitChar(),
				nLoop, lpList->status,
				GetStringSplitChar(),
				nLoop, lpList->num_physical_cus);

			LPLFSCDMPHCU lpPhysical = NULL;
			for (int jLoop = 0; jLoop < lpList->num_physical_cus; jLoop++)
			{
				lpPhysical = lpList->physical[jLoop];
				if (NULL == lpPhysical)
				{
					continue;
				}

				strCdmPhCu = CString((NULL == lpPhysical->physical_position_name ? 0 : strlen(lpPhysical->physical_position_name))
					+ sizeof(lpPhysical->unit_id) + 2048, 0);
				sprintf((char *)strCdmPhCu.c_str(), "%s"
					"wfsresult.lpbuffer.lpplist[%d].lppphysical[%d].lpphysicalpositionname=%s"
					"%s"
					"wfsresult.lpbuffer.lpplist[%d].lppphysical[%d].cunitid=%s"
					"%s"
					"wfsresult.lpbuffer.lpplist[%d].lppphysical[%d].ulinitialcount=%d"
					"%s"
					"wfsresult.lpbuffer.lpplist[%d].lppphysical[%d].ulcount=%d"
					"%s"
					"wfsresult.lpbuffer.lpplist[%d].lppphysical[%d].ulrejectcount=%d"
					"%s"
					"wfsresult.lpbuffer.lpplist[%d].lppphysical[%d].ulmaximum=%d"
					"%s"
					"wfsresult.lpbuffer.lpplist[%d].lppphysical[%d].uspstatus=%d"
					"%s"
					"wfsresult.lpbuffer.lpplist[%d].lppphysical[%d].bhardwaresensor=%s",
					GetStringSplitChar(),
					nLoop, jLoop, (NULL == lpPhysical->physical_position_name ? "NULL" : lpPhysical->physical_position_name),
					GetStringSplitChar(),
					nLoop, jLoop, CString(lpPhysical->unit_id, sizeof(lpPhysical->unit_id)).c_str(),
					GetStringSplitChar(),
					nLoop, jLoop, lpPhysical->initial_count,
					GetStringSplitChar(),
					nLoop, jLoop, lpPhysical->count,
					GetStringSplitChar(),
					nLoop, jLoop, lpPhysical->reject_count,
					GetStringSplitChar(),
					nLoop, jLoop, lpPhysical->maximum,
					GetStringSplitChar(),
					nLoop, jLoop, lpPhysical->p_status,
					GetStringSplitChar(),
					nLoop, jLoop, (TRUE == lpPhysical->hardware_sensor ? "TRUE" : "false"),
					GetStringSplitChar());

				strCdmCashUnit = string(strCdmCashUnit.c_str()) + strCdmPhCu;
			}

			strWfsResult = string(strWfsResult.c_str()) + strCdmCashUnit;
		}

		// EXE_LFS_CMD_CDM_END_EXCHANGE��������ô�GET_LFS_INF_CDM_CASH_UNIT_INFO���������ڻ�ȡ���ݵ�SP�ļӳ��Ľṹ
		if (TRUE == m_bCashUnitInfo4EndExchange)
		{
			// �����Ҳ��ͷ�LFS���
			m_lpResult4EndExchange = lpWfsRet;
		}
	}
	else if (LFS_INF_CDM_CURRENCY_EXP == lpWfsRet->u.command_code)
	{
		LPLFSCDMCURRENCYEXP * lppCurrencyExp = (LPLFSCDMCURRENCYEXP *)lpWfsRet->buffer;

		CString strCurrencyExps = "";
		CString strCurrencyExp = "";

		if (NULL != lppCurrencyExp)
		{
			for (int nLoop = 0; NULL != lppCurrencyExp[nLoop]; nLoop++)
			{
				strCurrencyExp = CString(sizeof(lppCurrencyExp[nLoop]->currency_id) + 1024, 0);
				sprintf((char *)strCurrencyExp.c_str(), "wfsresult.lpbuffer[%d].ccurrencyid=%d"
					"%s"
					"wfsresult.lpbuffer[%d].sexponent=%d"
					"%s",
					nLoop, CString(lppCurrencyExp[nLoop]->currency_id, sizeof(lppCurrencyExp[nLoop]->currency_id)).c_str(),
					GetStringSplitChar(),
					nLoop, lppCurrencyExp[nLoop]->exponent,
					GetStringSplitChar());

				strCurrencyExps = string(strCurrencyExps.c_str()) + strCurrencyExp;
			}
			strWfsResult = string(strWfsResult.c_str()) + strCurrencyExps;
		}
	}
	else if (LFS_INF_CDM_CURRENCY_EXP == lpWfsRet->u.command_code)
	{
		LPLFSCDMMIXTABLE * lppMixTable = (LPLFSCDMMIXTABLE *)lpWfsRet->buffer;

		CString strMixTables;
		CString strMixTable;

		if (NULL != lppMixTable)
		{
			for (int nLoop = 0; NULL != lppMixTable[nLoop]; nLoop++)
			{
				CString strMixHeaders;

				if (NULL != lppMixTable[nLoop]->mix_header)
				{
					for (int jLoop = 0; jLoop < lppMixTable[nLoop]->cols; jLoop++)
					{
						CString strMixHeader(256, 0);
						sprintf((char *)strMixHeader.c_str(), "%s"
							"wfsresult.lpbuffer[%d].lpulMixHeader[%d]=%d",
							GetStringSplitChar(),
							nLoop, jLoop, lppMixTable[nLoop]->mix_header[jLoop]);

						strMixHeaders = string(strMixHeaders.c_str()) + strMixHeader;
					}
				}

				CString strMixRows;

				LPLFSCDMMIXROW * lppMixRows = (LPLFSCDMMIXROW *)lppMixTable[nLoop]->rows;
				if (NULL != lppMixRows)
				{
					for (int jLoop = 0; NULL != lppMixRows[jLoop]; jLoop++)
					{
						CString strMixtures;

						if (NULL != lppMixRows[jLoop]->mixture)
						{
							for (int kLoop = 0; kLoop < lppMixTable[nLoop]->cols; kLoop++)
							{
								CString strMixture(256, 0);
								sprintf((char *)strMixture.c_str(), "%s"
									"wfsresult.lpbuffer[%d].lppMixRows[%d].lpusMixture[%d]=%d",
									GetStringSplitChar(),
									nLoop, jLoop, kLoop, lppMixRows[jLoop]->mixture[kLoop]);

								strMixtures = string(strMixtures.c_str()) + strMixture;
							}
						}

						CString strMixRow(strMixtures.length() + 1024, 0);
						sprintf((char *)strMixRow.c_str(), "wfsresult.lpbuffer[%d].lppMixRows[%d].ulAmount=%d"
							"%s"
							"%s",
							nLoop, jLoop, lppMixRows[jLoop]->amount,
							strMixtures.c_str(),
							GetStringSplitChar());

						strMixRows = string(strMixRows.c_str()) + strMixRow;
					}
				}

				strMixTable = CString((NULL == lppMixTable[nLoop]->name ? 0 : strlen(lppMixTable[nLoop]->name))
					+ strMixHeaders.length() + strMixRows.length() + 1024, 0);
				sprintf((char *)strMixTable.c_str(), "wfsresult.lpbuffer[%d].usMixNumber=%d"
					"%s"
					"wfsresult.lpbuffer[%d].lpszName=%d"
					"%s"
					"wfsresult.lpbuffer[%d].usRows=%d"
					"%s"
					"wfsresult.lpbuffer[%d].usCols=%d"
					"%s"
					"%s",
					nLoop, lppMixTable[nLoop]->mix_number,
					GetStringSplitChar(),
					nLoop, (NULL == lppMixTable[nLoop]->name ? "NULL" : lppMixTable[nLoop]->name),
					GetStringSplitChar(),
					nLoop, lppMixTable[nLoop]->rows,
					GetStringSplitChar(),
					nLoop, lppMixTable[nLoop]->cols,
					strMixHeaders.c_str(),
					strMixRows.c_str());

				strMixTables = string(strMixTables.c_str()) + strMixTable;
			}
			strWfsResult = string(strWfsResult.c_str()) + strMixTables;
		}
	}
	else if (LFS_INF_CDM_PRESENT_STATUS == lpWfsRet->u.command_code)
	{
		LPLFSCDMPRESENTSTATUS lpPresentStatus = (LPLFSCDMPRESENTSTATUS)lpWfsRet->buffer;
		if (NULL == lpPresentStatus)
		{
			return strWfsResult;
		}

		LPLFSCDMDENOMINATION lpDenomination = lpPresentStatus->denomination;
		CString strDenomination = "";
		if (NULL != lpDenomination)
		{
			CString strValues;
			if (NULL != lpDenomination->values)
			{
				for (int nLoop = 0; nLoop < lpDenomination->count; nLoop++)
				{
					CString strValue(256, 0);
					sprintf((char *)strValue.c_str(), "%s"
						"wfsresult.lpbuffer.lpdenomination.lpulvalues[%d]=%d",
						GetStringSplitChar(),
						nLoop, lpDenomination->values[nLoop]);

					strValues = string(strValues.c_str()) + strValue;
				}
			}

			strDenomination = CString(strValues.length() + 1024, 0);
			sprintf((char *)strDenomination.c_str(), "wfsresult.lpbuffer.lpdenomination.ccurrencyid=%s"
				"%s"
				"wfsresult.lpbuffer.lpdenomination.ulamount=%d"
				"%s"
				"wfsresult.lpbuffer.lpdenomination.uscount=%d"
				"%s"
				"%s"
				"wfsresult.lpbuffer.lpdenomination.ulcashbox=%d",
				CString(lpDenomination->currency_id, sizeof(lpDenomination->currency_id)).c_str(),
				GetStringSplitChar(),
				lpDenomination->amount,
				GetStringSplitChar(),
				lpDenomination->count,
				strValues.c_str(),
				GetStringSplitChar(),
				lpDenomination->cash_box);
		}

		strWfsResult = string(strDenomination.length() + (NULL == lpPresentStatus->extra ? 0 : strlen(lpPresentStatus->extra)) + 2048, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"%s"
			"%s"
			"wfsresult.lpbuffer.wpresentstate=%d"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_CDM_PRESENT_STATUS,
			GetStringSplitChar(),
			strDenomination.c_str(),
			("" != strDenomination ? GetStringSplitChar() : ""),
			lpPresentStatus->present_state,
			GetStringSplitChar(),
			(NULL == lpPresentStatus->extra ? "NULL" : lpPresentStatus->extra));
	}

	return strWfsResult;
}

HRESULT CDCCashDispenser_30::INF_CDM_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CDM_CAPABILITIES,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::INF_CDM_PRESENT_STATUS(long lPosition)
{
	HRESULT hResult = DC_ERROR;

	WORD fwPosition = (WORD)lPosition;
	LPLFSRESULT lpResult = NULL;
	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CDM_PRESENT_STATUS,
		&fwPosition,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::INF_CDM_CASH_UNIT_INFO()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CDM_CASH_UNIT_INFO,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::INF_CDM_CURRENCY_EXP()
{
	// ����Ӧ�ö��ԣ��������û���ô������Ҵ�����Ҫ�����£�����ʧ��
	// ��ͬ���У�GET_LFS_INF_CDM_MIX_TYPES��GET_LFS_INF_CDM_MIX_TABLE��GET_LFS_INF_CDM_CURRENCY_EXP
	return (short)DC_ERROR;

	HRESULT hResult = DC_ERROR;

	CString strWfsResult = "";

	LPLFSRESULT lpWfsRet = NULL;
	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CDM_CURRENCY_EXP,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::INF_CDM_MIX_TYPES()
{
	// ����Ӧ�ö��ԣ��������û���ô������Ҵ�����Ҫ�����£�����ʧ��
	// ��ͬ���У�GET_LFS_INF_CDM_MIX_TYPES��GET_LFS_INF_CDM_MIX_TABLE��GET_LFS_INF_CDM_CURRENCY_EXP
	return (short)DC_ERROR;
}

HRESULT CDCCashDispenser_30::INF_CDM_MIX_TABLE()
{
	// ����Ӧ�ö��ԣ��������û���ô������Ҵ�����Ҫ�����£�����ʧ��
	// ��ͬ���У�GET_LFS_INF_CDM_MIX_TYPES��GET_LFS_INF_CDM_MIX_TABLE��GET_LFS_INF_CDM_CURRENCY_EXP
	return (short)DC_ERROR;

	// ע�⣬����Ĵ���û�о������ԣ���ſ������Ȳ���

	HRESULT hResult = DC_ERROR;

	CString strWfsResult = "";

	LPLFSRESULT lpWfsRet = NULL;
	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_CDM_MIX_TABLE,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_CLOSE_SHUTTER(long lPosition) 
{
	HRESULT hResult = DC_ERROR;

	WORD fwPosition = (WORD)lPosition;
	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CDM_CLOSE_SHUTTER,
								&fwPosition,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_COUNT(LPCTSTR strPhysicalLocation, long lPosition) 
{
	HRESULT hResult = DC_ERROR;

	LFSCDMPHYSICALCU PhysicalCU = {0};
	if (0 == stricmp(strPhysicalLocation, "_ALL_"))  // �Զ���ؼ��֣����� _ALL_ ʱ�����������г�Ʊ��ղ�����
	{
		PhysicalCU.empty_all = TRUE;
	}
	else
	{
		PhysicalCU.empty_all = FALSE;
	}
	PhysicalCU.position = (WORD)lPosition;
	PhysicalCU.physical_position_name = (LPTSTR)strPhysicalLocation;
	
	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CDM_COUNT,
								&PhysicalCU,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_DENOMINATE(long lAmount, LPCTSTR strCurrency, long lMixAlgorithm) 
{
	HRESULT hResult = DC_ERROR;

	if (0 == lAmount || NULL == strCurrency)
	{
		return (short)DC_ERROR;
	}

	LFSCDMDENOMINATE Denominate = {0};
	Denominate.mix_number = (USHORT)lMixAlgorithm;
	LFSCDMDENOMINATION Denomination = {0};
	if (strlen(strCurrency) > sizeof(Denomination.currency_id))
	{
		memcpy(Denomination.currency_id, strCurrency, sizeof(Denomination.currency_id));
	}
	else
	{
		memcpy(Denomination.currency_id, strCurrency, strlen(strCurrency));
	}
	Denomination.amount = lAmount;
	Denomination.count = 0;
	Denomination.cash_box = 0;
	Denomination.values = NULL;
	Denominate.denomination = &Denomination;
	
	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CDM_DENOMINATE,
								&Denominate,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_DISPENSE(long lAmount, LPCTSTR strCurrency, long lMixAlgorithm, long lPosition, BOOL bPresent)
{
	HRESULT hResult = DC_ERROR;

	if (lAmount <= 0 || NULL == strCurrency || lMixAlgorithm <= 0)
	{
		return (short)DC_ERROR;
	}

	LFSCDMDISPENSE Dispense = {0};
	Dispense.mix_number = (USHORT)lMixAlgorithm;
	Dispense.position = (WORD)lPosition;
	Dispense.present = bPresent;

	LFSCDMDENOMINATION Denomination = {0};
	if (strlen(strCurrency) > sizeof(Denomination.currency_id))
	{
		memcpy(Denomination.currency_id, strCurrency, sizeof(Denomination.currency_id));
	}
	else
	{
		memcpy(Denomination.currency_id, strCurrency, strlen(strCurrency));
	}
	Denomination.amount = lAmount;
	Denomination.count = 0;
	Denomination.cash_box = 0;
	Denomination.values = NULL;

	Dispense.denomination = &Denomination;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CDM_DISPENSE,
								&Dispense,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_END_EXCHANGE(LPCTSTR strCUInfo) 
{
	if (NULL == strCUInfo)
	{
		return (short)DC_ERROR;
	}

	HRESULT hResult = DC_ERROR;

	// ����GET_LFS_INF_CDM_CASH_UNIT_INFO��ȡ����ṹ
	if (NULL != m_lpResult4EndExchange)  // ��ֹ�в����ڴ�û���ͷ�
	{
		LFSFreeResult(m_lpResult4EndExchange);
		m_lpResult4EndExchange = NULL;
	}

	m_bCashUnitInfo4EndExchange = TRUE;
	hResult = INF_CDM_CASH_UNIT_INFO();
	if (LFS_SUCCESS != hResult)
	{
		m_bCashUnitInfo4EndExchange = FALSE;

		printf(" (LFS_SUCCESS != hResult)\n");
		return hResult;
	}

	// ���ȴ�INF_CIM_CASH_UNIT_INFO 30��ȡ״̬��ɣ���ȡ����ṹ�Խ����������
	int nCount = 0;
	while (NULL == m_lpResult4EndExchange && (++ nCount) < 300)
	{
		usleep(100 * 1000);
	}

	if (NULL == m_lpResult4EndExchange)
	{
		m_bCashUnitInfo4EndExchange = FALSE;

		printf("INF_CDM_CASH_UNIT_INFO not return in 30 seconds\n");
		return (short)DC_ERROR;
	}

	LPLFSCDMCUINFO lpCashUnitInfo = (LPLFSCDMCUINFO)m_lpResult4EndExchange->buffer;
	if (NULL == lpCashUnitInfo || NULL == lpCashUnitInfo->list)
	{
		m_bCashUnitInfo4EndExchange = FALSE;

		LFSFreeResult(m_lpResult4EndExchange);
		m_lpResult4EndExchange = NULL;

		printf("if (NULL == lpCashUnitInfo || NULL == lpCashUnitInfo->list)\n");
		return (short)DC_ERROR;
	}

	BOOL bEndWithNoChange = FALSE;
	if (0 == strlen(strCUInfo) || NULL != strstr(strCUInfo, "ccurrencyid"))
	{
		// ���ı䳮�������ļӳ�������ȡ��ģ�鸴λ��������Ȳ����еĸ�����������������ó��������ֵ�Ĳ���
		bEndWithNoChange = TRUE;
	}

	CStringArray strarrParams;
	CString strParamKey;
	CString strParamValue;
	if (FALSE == bEndWithNoChange || NULL != strstr(strCUInfo, "ccurrencyid"))
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
	LPLFSCDMCASHUNIT lpList = NULL;
 	for (int nLoop = 0; nLoop < lpCashUnitInfo->count; nLoop ++)
	{
		lpList = lpCashUnitInfo->list[nLoop];
		if (NULL != lpList)
		{
			if (FALSE == bEndWithNoChange)
			{
				strParamKey = CString(256, 0);
				sprintf((char *)strParamKey.c_str(), "wfsresult.lpbuffer.lpplist[%d].ulcount", nLoop);
				if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
				{
					m_bCashUnitInfo4EndExchange = FALSE;

					LFSFreeResult(m_lpResult4EndExchange);
					m_lpResult4EndExchange = NULL;

					printf("if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))\n");
					return (short)DC_ERROR;
				}

				lpList->count = atoi(strParamValue.c_str());
				lpList->initial_count = lpList->count;
				lpList->reject_count = 0;
			}
			else
			{
				// ����������ı�

				// ���ı���
				strParamKey = CString(256, 0);
				sprintf((char *)strParamKey.c_str(), "wfsresult.lpbuffer.lpplist[%d].ccurrencyid", nLoop);
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

					memset(lpList->currency_id, 0, sizeof(lpList->currency_id));
					memcpy(	lpList->currency_id, 
							strParamValue.c_str(),
							strParamValue.length());
				}

				// ������ֵ
				strParamKey = CString(256, 0);
				sprintf((char *)strParamKey.c_str(), "wfsresult.lpbuffer.lpplist[%d].ulvalues", nLoop);
				if (TRUE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
				{
					lpList->values = atoi((LPCTSTR)strParamValue.c_str());
				}
			}
			
			LPLFSCDMPHCU lpPhysical = NULL;

			for (int jLoop = 0; jLoop < lpList->num_physical_cus; jLoop ++)
			{
				lpPhysical = lpList->physical[jLoop];
				if (NULL != lpPhysical)
				{
					if (FALSE == bEndWithNoChange)
					{
						strParamKey = CString(256, 0);
						sprintf((char *)strParamKey.c_str(), "wfsresult.lpbuffer.lpplist[%d].lppphysical[%d].ulcount", nLoop, jLoop);
						if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
						{
							m_bCashUnitInfo4EndExchange = FALSE;

							LFSFreeResult(m_lpResult4EndExchange);
							m_lpResult4EndExchange = NULL;

							printf("if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))\n");
							return (short)DC_ERROR;
						}

						lpPhysical->count = atoi(strParamValue.c_str());
						lpPhysical->initial_count = lpPhysical->count;
						lpPhysical->reject_count = 0;
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
								LFS_CMD_CDM_END_EXCHANGE,
								lpCashUnitInfo,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	m_bCashUnitInfo4EndExchange = FALSE;

	LFSFreeResult(m_lpResult4EndExchange);
	m_lpResult4EndExchange = NULL;

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_OPEN_SHUTTER(long lPosition) 
{
	HRESULT hResult = DC_ERROR;

	WORD fwPosition = (WORD)lPosition;
	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CDM_OPEN_SHUTTER,
								&fwPosition,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_PRESENT(long lPosition) 
{
	HRESULT hResult = DC_ERROR;

	WORD fwPosition = (WORD)lPosition;
	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CDM_PRESENT,
								&fwPosition,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_REJECT() 
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CDM_REJECT,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_RESET(long lNumber, long lRetractArea, long lRetractIndex, long lPosition) 
{
	HRESULT hResult = DC_ERROR;

	LPLFSCDMITEMPOSITION lpResetIn = NULL;

	LFSCDMRETRACT Retract = {0};
	LFSCDMITEMPOSITION ResetIn = {0};
	if (lNumber >= 0)
	{
		Retract.output_position = (WORD)lPosition;
		Retract.retract_area = (USHORT)lRetractArea;
		Retract.index = (USHORT)lRetractIndex;

		ResetIn.output_position = Retract.output_position;
		ResetIn.number = (USHORT)lNumber;
		ResetIn.retract_area = &Retract;

		lpResetIn = &ResetIn;
	}

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CDM_RESET,
								lpResetIn,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_RETRACT(long lRetractArea, long lRetractIndex, long lPosition) 
{
	HRESULT hResult = DC_ERROR;

	LFSCDMRETRACT Retract = {0};
	Retract.output_position = (WORD)lPosition;
	Retract.retract_area = (USHORT)lRetractArea;
	Retract.index = (USHORT)lRetractIndex;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CDM_RETRACT,
								&Retract,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_START_EXCHANGE(LPCTSTR strStartEx) 
{
	if (NULL == strStartEx)
	{
		return (short)DC_ERROR;
	}

	HRESULT hResult = DC_ERROR;

	LFSCDMSTARTEX StartEx = {0};

	CStringArray strarrParams;
	CString strParamKey;
	CString strParamValue;
	if (FALSE == CJSStringParam::GetStringParams(strStartEx, GetStringSplitChar(), strarrParams) || TRUE == strarrParams.empty())
	{
		return (short)DC_ERROR;
	}

	strParamKey = CString(256, 0);
	sprintf((char *)strParamKey.c_str(), "wfscdmstartex.fwexchangetype");
	if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
	{
		return (short)DC_ERROR;
	}
	StartEx.exchange_type = atoi(strParamValue.c_str());

	strParamKey = CString(256, 0);
	sprintf((char *)strParamKey.c_str(), "wfscdmstartex.ustellerid");
	if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
	{
		return (short)DC_ERROR;
	}
	StartEx.teller_id = atoi(strParamValue.c_str());
	
	strParamKey = CString(256, 0);
	sprintf((char *)strParamKey.c_str(), "wfscdmstartex.uscount");
	if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
	{
		return (short)DC_ERROR;
	}
	StartEx.count = atoi(strParamValue.c_str());

	USHORT usCUNumList[64] = {0};
	for (int nLoop = 0; nLoop < StartEx.count; nLoop ++)
	{
		strParamKey = CString(256, 0);
		sprintf((char *)strParamKey.c_str(), "wfscdmstartex.lpuscunumlist[%d]", nLoop);
		if (FALSE == CJSStringParam::GetStringParam(strarrParams, strParamKey.c_str(), strParamValue))
		{
			return (short)DC_ERROR;
		}
		usCUNumList[nLoop] = atoi(strParamValue.c_str());
	}
	StartEx.cu_num_list = usCUNumList;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CDM_START_EXCHANGE,
								&StartEx,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCCashDispenser_30::CMD_CDM_TEST_CASH_UNITS(long lNumber, long lRetractArea, long lRetractIndex, long lPosition) 
{
	HRESULT hResult = DC_ERROR;

	LFSCDMRETRACT Retract = {0};
	Retract.output_position = (WORD)lPosition;
	Retract.retract_area = (USHORT)lRetractArea;
	Retract.index = (USHORT)lRetractIndex;

	LFSCDMITEMPOSITION Position = {0};
	Position.output_position = Retract.output_position;
	Position.number = (USHORT)lNumber;
	Position.retract_area = &Retract;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_CDM_TEST_CASH_UNITS,
								&Position,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}
