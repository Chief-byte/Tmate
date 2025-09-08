// DCPrinter_30.cpp: implementation of the CDCPrinter_30 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCPrinter_30.h"
#include "../../../include/JavaScriptStringParam.h"
#include <codecvt>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDCPrinter_30::CDCPrinter_30(LPCTSTR strDCName, LPCTSTR strTraceComponent)
{
	m_strDCName = strDCName;
	m_strTraceComponent = CString(strTraceComponent);
	m_DCObject.m_bWosaXFSRun = FALSE;
}

CDCPrinter_30::~CDCPrinter_30()
{
}

HRESULT CDCPrinter_30::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// 调用命令
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_PTR_CONTROL_MEDIA"))
	{
		bValid = TRUE;
		hResult = CMD_PTR_CONTROL_MEDIA(atol(CJSStringParam::GetStringParam(strarrParams, "lpdwmediacontrol").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PTR_PRINT_FORM"))
	{
		bValid = TRUE;

		hResult = CMD_PTR_PRINT_FORM(	CJSStringParam::GetStringParam(strarrParams, "lpszformname").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpszmedianame").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpszfields").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpszunicodefields").c_str(),
										atol(CJSStringParam::GetStringParam(strarrParams, "walignment").c_str()), 
										atol(CJSStringParam::GetStringParam(strarrParams, "woffsetx").c_str()), 
										atol(CJSStringParam::GetStringParam(strarrParams, "woffsety").c_str()), 
										atol(CJSStringParam::GetStringParam(strarrParams, "dwmediacontrol").c_str()), 
										atol(CJSStringParam::GetStringParam(strarrParams, "wresolution").c_str()), 
										atol(CJSStringParam::GetStringParam(strarrParams, "wpapersource").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PTR_READ_FORM"))
	{
		bValid = TRUE;
		hResult = CMD_PTR_READ_FORM(	CJSStringParam::GetStringParam(strarrParams, "lpszformname").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpszfieldnames").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpszmedianame").c_str(),
										atol(CJSStringParam::GetStringParam(strarrParams, "dwmediacontrol").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PTR_RAW_DATA"))
	{
		bValid = TRUE;
		hResult = CMD_PTR_RAW_DATA(CJSStringParam::GetStringParam(strarrParams, "lpbdata").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PTR_MEDIA_EXTENTS"))
	{
		bValid = TRUE;
		hResult = CMD_PTR_MEDIA_EXTENTS((short)atol(CJSStringParam::GetStringParam(strarrParams, "wbase").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "wunitx").c_str()), 
										(short)atol(CJSStringParam::GetStringParam(strarrParams, "wunity").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PTR_RESET_COUNT"))
	{
		bValid = TRUE;
		hResult = CMD_PTR_RESET_COUNT();
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PTR_READ_IMAGE"))
	{
		bValid = TRUE;
		hResult = CMD_PTR_READ_IMAGE(	atol(CJSStringParam::GetStringParam(strarrParams, "wfrontimagetype").c_str()), 
										atol(CJSStringParam::GetStringParam(strarrParams, "wbackimagetype").c_str()), 
										atol(CJSStringParam::GetStringParam(strarrParams, "wfrontimagecolorformat").c_str()), 
										atol(CJSStringParam::GetStringParam(strarrParams, "wbackimagecolorformat").c_str()), 
										atol(CJSStringParam::GetStringParam(strarrParams, "wcodelineformat").c_str()), 
										atol(CJSStringParam::GetStringParam(strarrParams, "fwimagesource").c_str()),  
										CJSStringParam::GetStringParam(strarrParams, "lpszfrontimagefile").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpszbackimagefile").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PTR_RESET"))
	{
		bValid = TRUE;
		hResult = CMD_PTR_RESET(	atol(CJSStringParam::GetStringParam(strarrParams, "dwmediacontrol").c_str()), 
									atol(CJSStringParam::GetStringParam(strarrParams, "usretractbinnumber").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PTR_RETRACT_MEDIA"))
	{
		bValid = TRUE;
		hResult = CMD_PTR_RETRACT_MEDIA(atol(CJSStringParam::GetStringParam(strarrParams, "lpusbinnumber").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_PTR_DISPENSE_PAPER"))
	{
		bValid = TRUE;
		hResult = CMD_PTR_DISPENSE_PAPER((short)atol(CJSStringParam::GetStringParam(strarrParams, "wpapersource").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_INF_PTR_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_PTR_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_PTR_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_PTR_CAPABILITIES();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_PTR_FORM_LIST"))
	{
		bValid = TRUE;
		hResult = INF_PTR_FORM_LIST();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_PTR_MEDIA_LIST"))
	{
		bValid = TRUE;
		hResult = INF_PTR_MEDIA_LIST();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_PTR_QUERY_FORM"))
	{
		bValid = TRUE;
		hResult = INF_PTR_QUERY_FORM(CJSStringParam::GetStringParam(strarrParams, "lpszformname").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_INF_PTR_QUERY_MEDIA"))
	{
		bValid = TRUE;
		hResult = INF_PTR_QUERY_MEDIA(CJSStringParam::GetStringParam(strarrParams, "lpszmedianame").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_INF_PTR_QUERY_FIELD"))
	{
		bValid = TRUE;
		hResult = INF_PTR_QUERY_FIELD(	CJSStringParam::GetStringParam(strarrParams, "lpszformname").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "lpszfieldname").c_str());
	}

	return hResult;
}

CString CDCPrinter_30::HandleCmdErr(LPLFSRESULT lpWfsRet)
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

CString CDCPrinter_30::HandleCmdResult(LPLFSRESULT lpWfsRet)
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
		case LFS_CMD_PTR_CONTROL_MEDIA:
			break ;
		case LFS_CMD_PTR_PRINT_FORM:
			break ;
		case LFS_CMD_PTR_READ_FORM:
		{
			CString strReadFormOutData;
			LPLFSPTRREADFORMOUT lpReadFormOut = NULL;
			lpReadFormOut = (LPLFSPTRREADFORMOUT)lpWfsRet->buffer;
			if (NULL != lpReadFormOut)
			{
				if (NULL != lpReadFormOut->fields)
				{
					for (int nLoop = 0; ; nLoop ++)
					{
						if (NULL == lpReadFormOut->fields[nLoop])
						{
							if (NULL == lpReadFormOut->fields[nLoop + 1])
							{
								break ;
							}
							else
							{
								lpReadFormOut->fields[nLoop] = ',';
							}
						}
					}
				}

				if (NULL != lpReadFormOut->unicode_fields)
				{
					for (int nLoop = 0; ; nLoop ++)
					{
						if (NULL == lpReadFormOut->unicode_fields[nLoop])
						{
							if (NULL == lpReadFormOut->unicode_fields[nLoop + 1])
							{
								break ;
							}
							else
							{
								lpReadFormOut->unicode_fields[nLoop] = ',';
							}
						}
					}
				}

				// widechar 转 ascii
				char * unicode_fields = NULL;
				if (NULL != lpReadFormOut->unicode_fields)
				{
					size_t sSize = wcslen(lpReadFormOut->unicode_fields);
					int dSize = wcstombs(unicode_fields, lpReadFormOut->unicode_fields, 0) + 1;
					unicode_fields = new char[dSize];
					memset(unicode_fields, 0, dSize);
					wcstombs(unicode_fields, lpReadFormOut->unicode_fields, dSize);
				}

				strReadFormOutData = CString((NULL == lpReadFormOut->fields ? 0 : strlen(lpReadFormOut->fields))
											+ (NULL == lpReadFormOut->unicode_fields ? 0 : strlen(unicode_fields))
											+ 256, 0);
				sprintf((char *)strReadFormOutData.c_str(), "%s"
									"wfsresult.lpbuffer.lpszfields=%s"
									"%s"
									"wfsresult.lpbuffer.lpszunicodefields=%s",
									GetStringSplitChar(),
									(NULL == lpReadFormOut->fields ? "" : lpReadFormOut->fields),
									GetStringSplitChar(),
									(NULL == lpReadFormOut->unicode_fields ? "" : unicode_fields));
				strCmdResult = string(strCmdResult.c_str()) + strReadFormOutData;

				if (NULL != unicode_fields)
				{
					delete[] unicode_fields;
				}
			}
		}
		case LFS_CMD_PTR_RAW_DATA:
			break ;
		case LFS_CMD_PTR_MEDIA_EXTENTS:
			break ;
		case LFS_CMD_PTR_RESET_COUNT:
			break ;
		case LFS_CMD_PTR_READ_IMAGE:
		{
			CString strReadImageOutData;
			LPLFSPTRIMAGE * lppImage = NULL;
			lppImage = (LPLFSPTRIMAGE *)lpWfsRet->buffer;
			if (NULL != lppImage)
			{
				int nIndex = 0;
				while (* lppImage != NULL)
				{
					CHAR * pszData = NULL;
					if (NULL != (* lppImage)->data)
					{
						if ((* lppImage)->data_length > 0)
						{
							pszData = new CHAR[(* lppImage)->data_length * 2 + 2];
							CUtils().HextoStr((* lppImage)->data, (SHORT)(* lppImage)->data_length, pszData);
						}
					}
					
					strReadImageOutData = CString((NULL == (*lppImage)->data || NULL == pszData ? 0 : strlen(pszData)) + 2048, 0);
					sprintf((char *)strReadImageOutData.c_str(), "%s"
										"wfsresult.lpbuffer[%d].wimagesource=%d"
										"%s"
										"wfsresult.lpbuffer[%d].wstatus=%d"
										"%s"
										"wfsresult.lpbuffer[%d].uldatalength=%d"
										"%s"
										"wfsresult.lpbuffer[%d].lpbdata=%s",
										GetStringSplitChar(),
										nIndex, 
										(* lppImage)->image_source,
										GetStringSplitChar(),
										nIndex, 
										(* lppImage)->status,
										GetStringSplitChar(),
										nIndex, 
										(* lppImage)->data_length,
										GetStringSplitChar(),
										nIndex, 
										(NULL == (* lppImage)->data || NULL == pszData ? "" : pszData));

					if (NULL != pszData)
					{
						delete[] pszData;
						pszData = NULL;
					}

					nIndex ++;
					lppImage ++;

					strCmdResult = string(strCmdResult.c_str()) + strReadImageOutData;
				}
			}
		}
		case LFS_CMD_PTR_RESET:
			break ;
		case LFS_CMD_PTR_RETRACT_MEDIA:
			break ;
		case LFS_CMD_PTR_DISPENSE_PAPER:
			break ;
		default:
			break ;
	}

	strWfsResult = string(strWfsResult.c_str()) + strCmdResult;

	return strWfsResult;
}

CString CDCPrinter_30::HandleEXEEvtResult(LPLFSRESULT lpWfsRet)
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
		case LFS_EXEE_PTR_NOMEDIA:
			break;
		case LFS_EXEE_PTR_MEDIAINSERTED:
			break;
		case LFS_EXEE_PTR_FIELDERROR:
			{
				LPLFSPTRFIELDFAIL lpFieldFail = (LPLFSPTRFIELDFAIL)lpWfsRet->buffer;
				if(NULL != lpFieldFail)
				{
					strEvtResult = CString(strlen(lpFieldFail->form_name) + strlen(lpFieldFail->field_name) + 1024, 0);
					sprintf((char *)strEvtResult.c_str(), "%s"
						"wfsresult.lpbuffer.lpszformname=%s"
						"%s"
						"wfsresult.lpbuffer.lpszfieldname=%s"
						"%s"
						"wfsresult.lpbuffer.wfailure=%d",
						GetStringSplitChar(),
						lpFieldFail->form_name,
						GetStringSplitChar(),
						lpFieldFail->field_name,
						GetStringSplitChar(),
						lpFieldFail->failure);
					
				}
				
				break;
			}
		case LFS_EXEE_PTR_FIELDWARNING:
			break;
		/*
		// linux 中暂不支持
		case LFS_EXEE_PTR_MEDIAPRESENTED:
			{
				LPLFSPTRMEDIAPRESENTED lpMediaPresented = (LPLFSPTRMEDIAPRESENTED)lpWfsRet->buffer;
				if(NULL != lpMediaPresented)
				{
					strEvtResult = CString(256, 0);
					sprintf((char *)strEvtResult.c_str(), "%s"
						"wfsresult.lpbuffer.uswadindex=%d"
						"%s"
						"wfsresult.lpbuffer.ustotalwads=%d",
						GetStringSplitChar(),
						lpMediaPresented->usWadIndex,
						GetStringSplitChar(),
						lpMediaPresented->usTotalWads);
				}
				
				break;
			}
		*/
		default:
			break;
	}
	
	strWfsResult = string(strWfsResult.c_str()) + strEvtResult;

	return strWfsResult;
}

CString CDCPrinter_30::HandleUSEREvtResult(LPLFSRESULT lpWfsRet)
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
		case LFS_USRE_PTR_RETRACTBINTHRESHOLD:
		case LFS_USRE_PTR_PAPERTHRESHOLD:
		case LFS_USRE_PTR_TONERTHRESHOLD:
		case LFS_USRE_PTR_LAMPTHRESHOLD:
		case LFS_USRE_PTR_INKTHRESHOLD:
		default:
			break;
	}

	strWfsResult = string(strWfsResult.c_str()) + strEvtResult;

	return strWfsResult;
}

CString CDCPrinter_30::HandleSRVEvtResult(LPLFSRESULT lpWfsRet)
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
		case LFS_SRVE_PTR_MEDIATAKEN:
		case LFS_SRVE_PTR_MEDIAINSERTED:
		case LFS_SRVE_PTR_MEDIADETECTED:
		default:
			break;
	}

	strWfsResult = string(strWfsResult.c_str()) + strEvtResult;

	return strWfsResult;
}

CString CDCPrinter_30::HandleSysEvtResult(LPLFSRESULT lpWfsRet)
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

CString	CDCPrinter_30::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[]={
		{"WFS_CMD_PTR_CONTROL_MEDIA"        ,(PTR_SERVICE_OFFSET + 1)},
		{"WFS_CMD_PTR_PRINT_FORM"           ,(PTR_SERVICE_OFFSET + 2)},
		{"WFS_CMD_PTR_READ_FORM"            ,(PTR_SERVICE_OFFSET + 3)},
		{"WFS_CMD_PTR_RAW_DATA"             ,(PTR_SERVICE_OFFSET + 4)},
		{"WFS_CMD_PTR_MEDIA_EXTENTS"        ,(PTR_SERVICE_OFFSET + 5)},
		{"WFS_CMD_PTR_RESET_COUNT"          ,(PTR_SERVICE_OFFSET + 6)},
		{"WFS_CMD_PTR_READ_IMAGE"           ,(PTR_SERVICE_OFFSET + 7)},
		{"WFS_CMD_PTR_RESET"                ,(PTR_SERVICE_OFFSET + 8)},
		{"WFS_CMD_PTR_RETRACT_MEDIA"        ,(PTR_SERVICE_OFFSET + 9)},
		{"WFS_CMD_PTR_DISPENSE_PAPER"       ,(PTR_SERVICE_OFFSET + 10)}
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

CString	CDCPrinter_30::GetXFSMsgStr(DWORD dwEventID)
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

		{"WFS_EXEE_PTR_NOMEDIA"             ,(PTR_SERVICE_OFFSET + 1)},
		{"WFS_EXEE_PTR_MEDIAINSERTED"       ,(PTR_SERVICE_OFFSET + 2)},
		{"WFS_EXEE_PTR_FIELDERROR"          ,(PTR_SERVICE_OFFSET + 3)},
		{"WFS_EXEE_PTR_FIELDWARNING"        ,(PTR_SERVICE_OFFSET + 4)},
		{"WFS_USRE_PTR_RETRACTBINTHRESHOLD" ,(PTR_SERVICE_OFFSET + 5)},
		{"WFS_SRVE_PTR_MEDIATAKEN"          ,(PTR_SERVICE_OFFSET + 6)},
		{"WFS_USRE_PTR_PAPERTHRESHOLD"      ,(PTR_SERVICE_OFFSET + 7)},
		{"WFS_USRE_PTR_TONERTHRESHOLD"      ,(PTR_SERVICE_OFFSET + 8)},
		{"WFS_SRVE_PTR_MEDIAINSERTED"       ,(PTR_SERVICE_OFFSET + 9)},
		{"WFS_USRE_PTR_LAMPTHRESHOLD"       ,(PTR_SERVICE_OFFSET + 10)},
		{"WFS_USRE_PTR_INKTHRESHOLD"        ,(PTR_SERVICE_OFFSET + 11)},
		{"WFS_SRVE_PTR_MEDIADETECTED"       ,(PTR_SERVICE_OFFSET + 12)}
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

CString	CDCPrinter_30::GetXFSSysEvtStr(DWORD dwEventID)
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

CString	CDCPrinter_30::GetXFSErrStr(HRESULT hResult)
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
		{"WFS_ERR_PTR_FORMNOTFOUND"         ,(-(PTR_SERVICE_OFFSET + 0))},
		{"WFS_ERR_PTR_FIELDNOTFOUND"        ,(-(PTR_SERVICE_OFFSET + 1))},
		{"WFS_ERR_PTR_NOMEDIAPRESENT"       ,(-(PTR_SERVICE_OFFSET + 2))},
		{"WFS_ERR_PTR_READNOTSUPPORTED"     ,(-(PTR_SERVICE_OFFSET + 3))},
		{"WFS_ERR_PTR_FLUSHFAIL"            ,(-(PTR_SERVICE_OFFSET + 4))},
		{"WFS_ERR_PTR_MEDIAOVERFLOW"        ,(-(PTR_SERVICE_OFFSET + 5))},
		{"WFS_ERR_PTR_FIELDSPECFAILURE"     ,(-(PTR_SERVICE_OFFSET + 6))},
		{"WFS_ERR_PTR_FIELDERROR"           ,(-(PTR_SERVICE_OFFSET + 7))},
		{"WFS_ERR_PTR_MEDIANOTFOUND"        ,(-(PTR_SERVICE_OFFSET + 8))},
		{"WFS_ERR_PTR_EXTENTNOTSUPPORTED"   ,(-(PTR_SERVICE_OFFSET + 9))},
		{"WFS_ERR_PTR_MEDIAINVALID"         ,(-(PTR_SERVICE_OFFSET + 10))},
		{"WFS_ERR_PTR_FORMINVALID"          ,(-(PTR_SERVICE_OFFSET + 11))},
		{"WFS_ERR_PTR_FIELDINVALID"         ,(-(PTR_SERVICE_OFFSET + 12))},
		{"WFS_ERR_PTR_MEDIASKEWED"          ,(-(PTR_SERVICE_OFFSET + 13))},
		{"WFS_ERR_PTR_RETRACTBINFULL"       ,(-(PTR_SERVICE_OFFSET + 14))},
		{"WFS_ERR_PTR_STACKERFULL"          ,(-(PTR_SERVICE_OFFSET + 15))},
		{"WFS_ERR_PTR_PAGETURNFAIL"         ,(-(PTR_SERVICE_OFFSET + 16))},
		{"WFS_ERR_PTR_MEDIATURNFAIL"        ,(-(PTR_SERVICE_OFFSET + 17))},
		{"WFS_ERR_PTR_SHUTTERFAIL"          ,(-(PTR_SERVICE_OFFSET + 18))},
		{"WFS_ERR_PTR_MEDIAJAMMED"          ,(-(PTR_SERVICE_OFFSET + 19))},
		{"WFS_ERR_PTR_FILE_IO_ERROR"        ,(-(PTR_SERVICE_OFFSET + 20))},
		{"WFS_ERR_PTR_CHARSETDATA"          ,(-(PTR_SERVICE_OFFSET + 21))},
		{"WFS_ERR_PTR_PAPERJAMMED"          ,(-(PTR_SERVICE_OFFSET + 22))},
		{"WFS_ERR_PTR_PAPEROUT"             ,(-(PTR_SERVICE_OFFSET + 23))},
		{"WFS_ERR_PTR_INKOUT"               ,(-(PTR_SERVICE_OFFSET + 24))},
		{"WFS_ERR_PTR_TONEROUT"             ,(-(PTR_SERVICE_OFFSET + 25))},
		{"WFS_ERR_PTR_LAMPINOP"             ,(-(PTR_SERVICE_OFFSET + 26))},
		{"WFS_ERR_PTR_SOURCEINVALID"        ,(-(PTR_SERVICE_OFFSET + 27))},
		{"WFS_ERR_PTR_SEQUENCEINVALID"      ,(-(PTR_SERVICE_OFFSET + 28))},
		{"WFS_ERR_PTR_MEDIASIZE"            ,(-(PTR_SERVICE_OFFSET + 29))}
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

HRESULT CDCPrinter_30::INF_PTR_STATUS()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_PTR_STATUS,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

CString CDCPrinter_30::HandleInfResult(LPLFSRESULT lpWfsRet)
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
	printf("CDCPrinter_30:HandleInfResult %s\n", strWfsResult.c_str());


	if (LFS_SUCCESS != lpWfsRet->result)
	{
		return strWfsResult;
	}

	if (LFS_INF_PTR_STATUS == lpWfsRet->u.command_code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_STATUS 1\n");

		LPLFSPTRSTATUS lpStatus = (LPLFSPTRSTATUS)lpWfsRet->buffer;
		if (NULL == lpStatus)
		{
			return strWfsResult;
		}

		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_STATUS 2\n");
		LPLFSPTRRETRACTBINS * lppRetractBins = lpStatus->retract_bins;
		CString strRetractBins;
		if (NULL != lppRetractBins)
		{
			for (int nLoop = 0; NULL != lppRetractBins[nLoop]; nLoop ++)
			{
				CString strRetractBin(256, 0);
				sprintf((char *)strRetractBin.c_str(), "%s"
										"wfsresult.lpbuffer.lppretractbins[%d].wretractbin=%d"
										"%s"
										"wfsresult.lpbuffer.lppretractbins[%d].usretractcount=%d",
										GetStringSplitChar(),
										nLoop, lppRetractBins[nLoop]->retract_bin,
										GetStringSplitChar(),
										nLoop, lppRetractBins[nLoop]->retract_count);
				strRetractBins = string(strRetractBins.c_str()) + strRetractBin;
			}
		}

		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_STATUS 3\n");
		CString strPapers;
		for (int nLoop = 0; nLoop < LFS_PTR_SUPPLYSIZE; nLoop ++)
		{
			CString strPaper(256, 0);
			sprintf((char *)strPaper.c_str(), "%s"
								"wfsresult.lpbuffer.fwpaper[%d]=%d",
								GetStringSplitChar(),
								nLoop, lpStatus->paper[nLoop]);
			strPapers = string(strPapers.c_str()) + strPaper;
		}

		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_STATUS 4\n");
		strWfsResult = CString(strPapers.length() + strRetractBins.length() + 2048, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
							"%s"
							"wfsresult.lpbuffer.fwdevice=%d"
							"%s"
							"wfsresult.lpbuffer.fwmedia=%d"
							"%s"
							"%s"
							"wfsresult.lpbuffer.fwtoner=%d"
							"%s"
							"wfsresult.lpbuffer.fwink=%d"
							"%s"
							"wfsresult.lpbuffer.fwlamp=%d"
							"%s"
							"%s"
							"wfsresult.lpbuffer.usmediaonstacker=%d"
							"%s"
							"wfsresult.lpbuffer.lpszextra=%s",
							LFS_INF_PTR_STATUS,
							GetStringSplitChar(),
							lpStatus->device,
							GetStringSplitChar(),
							lpStatus->media,
							strPapers.c_str(),
							GetStringSplitChar(),
							lpStatus->toner,
							GetStringSplitChar(),
							lpStatus->ink,
							GetStringSplitChar(),
							lpStatus->lamp,
							strRetractBins.c_str(),
							GetStringSplitChar(),
							lpStatus->media_on_stacker,
							GetStringSplitChar(),
							(NULL == lpStatus->extra ? "NULL" : lpStatus->extra));

		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_STATUS 5\n");
	}
	else if (LFS_INF_PTR_CAPABILITIES == lpWfsRet->u.command_code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_CAPABILITIES 1\n");
		LPLFSPTRCAPS lpCaps = (LPLFSPTRCAPS)lpWfsRet->buffer;
		if (NULL == lpCaps)
		{
			return strWfsResult;
		}
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_CAPABILITIES 2\n");

		CString strRetractBins;
		if (NULL != lpCaps->max_retract)
		{
			for (int nLoop = 0; nLoop < lpCaps->retract_bins; nLoop++)
			{
				CString strRetractBin(256, 0);
				sprintf((char *)strRetractBin.c_str(), "%s"
					"wfsresult.lpbuffer.lpusmaxretract[%d]=%d",
					GetStringSplitChar(),
					nLoop, lpCaps->max_retract[nLoop]);

				strRetractBins = string(strRetractBins.c_str()) + strRetractBin;
			}
		}
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_CAPABILITIES 3\n");

		strWfsResult = string((NULL == lpCaps->extra ? 0 : strlen(lpCaps->extra)) + 4096, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.wclass=%d"
			"%s"
			"wfsresult.lpbuffer.fwtype=%d"
			"%s"
			"wfsresult.lpbuffer.bcompound=%s"
			"%s"
			"wfsresult.lpbuffer.wresolution=%d"
			"%s"
			"wfsresult.lpbuffer.fwreadform=%d"
			"%s"
			"wfsresult.lpbuffer.fwwriteform=%d"
			"%s"
			"wfsresult.lpbuffer.fwextents=%d"
			"%s"
			"wfsresult.lpbuffer.fwcontrol=%d"
			"%s"
			"wfsresult.lpbuffer.usmaxmediaonstacker=%d"
			"%s"
			"wfsresult.lpbuffer.bacceptmedia=%s"
			"%s"
			"wfsresult.lpbuffer.bmultipage=%s"
			"%s"
			"wfsresult.lpbuffer.fwpapersources=%d"
			"%s"
			"wfsresult.lpbuffer.bmediataken=%s"
			"%s"
			"wfsresult.lpbuffer.usretractbins=%d"
			"%s"
			"%s"
			"wfsresult.lpbuffer.fwimagetype=%d"
			"%s"
			"wfsresult.lpbuffer.fwfrontimagecolorformat=%d"
			"%s"
			"wfsresult.lpbuffer.fwbackimagecolorformat=%d"
			"%s"
			"wfsresult.lpbuffer.fwcodelineformat=%d"
			"%s"
			"wfsresult.lpbuffer.fwimagesource=%d"
			"%s"
			"wfsresult.lpbuffer.fwcharsupport=%d"
			"%s"
			"wfsresult.lpbuffer.bdispensepaper=%s"
			"%s"
			"wfsresult.lpbuffer.lpszextra=%s",
			LFS_INF_PTR_CAPABILITIES,
			GetStringSplitChar(),
			lpCaps->dev_class,
			GetStringSplitChar(),
			lpCaps->dev_type,
			GetStringSplitChar(),
			(lpCaps->compound ? "TRUE" : "false"),
			GetStringSplitChar(),
			lpCaps->resolution,
			GetStringSplitChar(),
			lpCaps->read_form,
			GetStringSplitChar(),
			lpCaps->write_form,
			GetStringSplitChar(),
			lpCaps->extents,
			GetStringSplitChar(),
			lpCaps->control,
			GetStringSplitChar(),
			lpCaps->max_media_on_stacker,
			GetStringSplitChar(),
			lpCaps->accept_media ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->multi_page ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->paper_sources,
			GetStringSplitChar(),
			lpCaps->media_taken ? "TRUE" : "false",
			GetStringSplitChar(),
			lpCaps->retract_bins,
			strRetractBins.c_str(),
			GetStringSplitChar(),
			lpCaps->image_type,
			GetStringSplitChar(),
			lpCaps->front_image_color_format,
			GetStringSplitChar(),
			lpCaps->back_image_color_format,
			GetStringSplitChar(),
			lpCaps->codeline_format,
			GetStringSplitChar(),
			lpCaps->image_source,
			GetStringSplitChar(),
			lpCaps->char_support,
			GetStringSplitChar(),
			lpCaps->dispense_paper ? "TRUE" : "false",
			GetStringSplitChar(),
			(NULL == lpCaps->extra ? "NULL" : lpCaps->extra));

		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_CAPABILITIES 5\n");
	}
	else if (LFS_INF_PTR_FORM_LIST == lpWfsRet->u.command_code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_FORM_LIST 1\n");
		LPSTR lpszFormList = (LPSTR)lpWfsRet->buffer;
		if (NULL != lpszFormList)
		{
			for (int nLoop = 0; ; nLoop++)
			{
				if (NULL == lpszFormList[nLoop] && NULL == lpszFormList[nLoop + 1])
				{
					lpszFormList[nLoop] = '\0';
					break;
				}
				else if (NULL == lpszFormList[nLoop])
				{
					lpszFormList[nLoop] = ',';
				}
			}
		}
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_FORM_LIST 2\n");

		strWfsResult = string((NULL == lpszFormList ? 0 : strlen(lpszFormList)) + 1024, 0);
		// wfsresult.lpbuffer因不能区分LFS_INF_PTR_FORM_LIST、LFS_INF_PTR_MEDIA_LIST命令结果，使用变量名替代
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpszformlist=%s",
			LFS_INF_PTR_FORM_LIST,
			GetStringSplitChar(),
			(NULL == lpszFormList ? "NULL" : lpszFormList));
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_FORM_LIST 3\n");
	}
	else if (LFS_INF_PTR_MEDIA_LIST == lpWfsRet->u.command_code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_MEDIA_LIST 1\n");
		LPSTR lpszMediaList = (LPSTR)lpWfsRet->buffer;
		if (NULL != lpszMediaList)
		{
			for (int nLoop = 0; ; nLoop++)
			{
				if (NULL == lpszMediaList[nLoop] && NULL == lpszMediaList[nLoop + 1])
				{
					lpszMediaList[nLoop] = '\0';
					break;
				}
				else if (NULL == lpszMediaList[nLoop])
				{
					lpszMediaList[nLoop] = ',';
				}
			}
		}
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_MEDIA_LIST 2\n");

		strWfsResult = string((NULL == lpszMediaList ? 0 : strlen(lpszMediaList)) + 1024, 0);
		// wfsresult.lpbuffer因不能区分LFS_INF_PTR_FORM_LIST、LFS_INF_PTR_MEDIA_LIST命令结果，使用变量名替代
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpszmedialist=%s",
			LFS_INF_PTR_MEDIA_LIST,
			GetStringSplitChar(),
			(NULL == lpszMediaList ? "NULL" : lpszMediaList));

		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_MEDIA_LIST 2\n");
	}
	else if (LFS_INF_PTR_QUERY_FIELD == lpWfsRet->u.command_code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FIELD 1\n");
		LPLFSFRMFIELD * lppFields = (LPLFSFRMFIELD *)lpWfsRet->buffer;

		if (NULL != lppFields)
		{
			printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FIELD 2\n");
			for (int nLoop = 0; NULL != lppFields[nLoop]; nLoop++)
			{
				// widechar 转 ascii
				char * unicode_initial_value = NULL;
				if (NULL != lppFields[nLoop]->unicode_initial_value)
				{
					size_t sSize = wcslen(lppFields[nLoop]->unicode_initial_value);
					int dSize = wcstombs(unicode_initial_value, lppFields[nLoop]->unicode_initial_value, 0) + 1;
					unicode_initial_value = new char[dSize];
					memset(unicode_initial_value, 0, dSize);
					wcstombs(unicode_initial_value, lppFields[nLoop]->unicode_initial_value, dSize);
				}
				printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FIELD 3\n");

				char * unicode_format = NULL;
				if (NULL != lppFields[nLoop]->unicode_format)
				{
					size_t sSize = wcslen(lppFields[nLoop]->unicode_format);
					int dSize = wcstombs(unicode_format, lppFields[nLoop]->unicode_format, 0) + 1;
					unicode_format = new char[dSize];
					memset(unicode_format, 0, dSize);
					wcstombs(unicode_format, lppFields[nLoop]->unicode_format, dSize);
				}
				printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FIELD 4\n");

				CString strField = CString((NULL == lppFields[nLoop]->field_name ? 0 : strlen(lppFields[nLoop]->field_name))
					+ (NULL == lppFields[nLoop]->initial_value ? 0 : strlen(lppFields[nLoop]->initial_value))
					+ (NULL == lppFields[nLoop]->unicode_initial_value ? 0 : strlen(unicode_initial_value))
					+ (NULL == lppFields[nLoop]->format ? 0 : strlen(lppFields[nLoop]->format))
					+ (NULL == lppFields[nLoop]->unicode_format ? 0 : strlen(unicode_format)) + 4096, 0);
				sprintf((char *)strField.c_str(), "wfsresult.lpbuffer[%d].lpszfieldname=%s"
					"%s"
					"wfsresult.lpbuffer[%d].windexcount=%d"
					"%s"
					"wfsresult.lpbuffer[%d].fwtype=%d"
					"%s"
					"wfsresult.lpbuffer[%d].fwclass=%d"
					"%s"
					"wfsresult.lpbuffer[%d].fwaccess=%d"
					"%s"
					"wfsresult.lpbuffer[%d].fwoverflow=%d"
					"%s"
					"wfsresult.lpbuffer[%d].lpszinitialvalue=%s"
					"%s"
					"wfsresult.lpbuffer[%d].lpszunicodeinitialvalue=%s"
					"%s"
					"wfsresult.lpbuffer[%d].lpszformat=%s"
					"%s"
					"wfsresult.lpbuffer[%d].lpszunicodeformat=%s",
					nLoop, (NULL == lppFields[nLoop]->field_name ? "NULL" : lppFields[nLoop]->field_name),
					GetStringSplitChar(),
					nLoop, lppFields[nLoop]->index_count,
					GetStringSplitChar(),
					nLoop, lppFields[nLoop]->type,
					GetStringSplitChar(),
					nLoop, lppFields[nLoop]->field_class,
					GetStringSplitChar(),
					nLoop, lppFields[nLoop]->access,
					GetStringSplitChar(),
					nLoop, lppFields[nLoop]->overflow,
					GetStringSplitChar(),
					nLoop, (NULL == lppFields[nLoop]->initial_value ? "NULL" : lppFields[nLoop]->initial_value),
					GetStringSplitChar(),
					nLoop, (NULL == lppFields[nLoop]->unicode_initial_value ? "NULL" : unicode_initial_value),
					GetStringSplitChar(),
					nLoop, (NULL == lppFields[nLoop]->format ? "NULL" : lppFields[nLoop]->format),
					GetStringSplitChar(),
					nLoop, (NULL == lppFields[nLoop]->unicode_format ? "NULL" : unicode_format));
				printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FIELD 5\n");

				strWfsResult = string(strWfsResult.c_str()) + strField;

				if (NULL != unicode_initial_value)
				{
					delete[] unicode_initial_value;
				}
				if (NULL != unicode_format)
				{
					delete[] unicode_format;
				}
				printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FIELD 6\n");
			}
		}
	}
	else if (LFS_INF_PTR_QUERY_FORM == lpWfsRet->u.command_code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FORM 1\n");
		LPLFSFRMHEADER lpHeader = (LPLFSFRMHEADER)lpWfsRet->buffer;
		if (NULL == lpHeader)
		{
			return strWfsResult;
		}
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FORM 2\n");

		LPSTR fields = (LPSTR)lpHeader->fields;
		if (NULL != fields)
		{
			for (int nLoop = 0; ; nLoop++)
			{
				if (NULL == fields[nLoop] && NULL == fields[nLoop + 1])
				{
					fields[nLoop] = '\0';
					break;
				}
				else if (NULL == fields[nLoop])
				{
					fields[nLoop] = ',';
				}
			}
		}
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FORM 3\n");

		strWfsResult = string((NULL == lpHeader->form_name ? 0 : strlen(lpHeader->form_name))
			+ (NULL == lpHeader->user_prompt ? 0 : strlen(lpHeader->user_prompt))
			+ (NULL == lpHeader->fields ? 0 : strlen(lpHeader->fields)) + 4096, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.lpszformname=%s"
			"%s"
			"wfsresult.lpbuffer.wbase=%d"
			"%s"
			"wfsresult.lpbuffer.wunitx=%d"
			"%s"
			"wfsresult.lpbuffer.wunity=%d"
			"%s"
			"wfsresult.lpbuffer.wwidth=%d"
			"%s"
			"wfsresult.lpbuffer.wheight=%d"
			"%s"
			"wfsresult.lpbuffer.walignment=%d"
			"%s"
			"wfsresult.lpbuffer.worientation=%d"
			"%s"
			"wfsresult.lpbuffer.woffsetx=%d"
			"%s"
			"wfsresult.lpbuffer.woffsety=%d"
			"%s"
			"wfsresult.lpbuffer.wversionmajor=%d"
			"%s"
			"wfsresult.lpbuffer.wversionminor=%d"
			"%s"
			"wfsresult.lpbuffer.lpszuserprompt=%d"
			"%s"
			"wfsresult.lpbuffer.fwcharsupport=%d"
			"%s"
			"wfsresult.lpszfields=%s",
			LFS_INF_PTR_QUERY_FORM,
			GetStringSplitChar(),
			(NULL == lpHeader->form_name ? "NULL" : lpHeader->form_name),
			GetStringSplitChar(),
			lpHeader->base,
			GetStringSplitChar(),
			lpHeader->unit_x,
			GetStringSplitChar(),
			lpHeader->unit_y,
			GetStringSplitChar(),
			lpHeader->width,
			GetStringSplitChar(),
			lpHeader->height,
			GetStringSplitChar(),
			lpHeader->alignment,
			GetStringSplitChar(),
			lpHeader->orientation,
			GetStringSplitChar(),
			lpHeader->offset_x,
			GetStringSplitChar(),
			lpHeader->offset_y,
			GetStringSplitChar(),
			lpHeader->version_major,
			GetStringSplitChar(),
			lpHeader->version_minor,
			GetStringSplitChar(),
			(NULL == lpHeader->user_prompt ? "NULL" : lpHeader->user_prompt),
			GetStringSplitChar(),
			lpHeader->char_support,
			GetStringSplitChar(),
			(NULL == lpHeader->fields ? "NULL" : lpHeader->fields));
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FORM 4\n");
	}
	else if (LFS_INF_PTR_QUERY_MEDIA == lpWfsRet->u.command_code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_MEDIA 1\n");
		LPLFSFRMMEDIA lpMedia = (LPLFSFRMMEDIA)lpWfsRet->buffer;
		if (NULL == lpMedia)
		{
			return strWfsResult;
		}
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_MEDIA 2\n");

		strWfsResult = string(4096, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
			"%s"
			"wfsresult.lpbuffer.fwmediatype=%d"
			"%s"
			"wfsresult.lpbuffer.wbase=%d"
			"%s"
			"wfsresult.lpbuffer.wunitx=%d"
			"%s"
			"wfsresult.lpbuffer.wunity=%d"
			"%s"
			"wfsresult.lpbuffer.wsizewidth=%d"
			"%s"
			"wfsresult.lpbuffer.wsizeheight=%d"
			"%s"
			"wfsresult.lpbuffer.wpagecount=%d"
			"%s"
			"wfsresult.lpbuffer.wlinecount=%d"
			"%s"
			"wfsresult.lpbuffer.wprintareax=%d"
			"%s"
			"wfsresult.lpbuffer.wprintareay=%d"
			"%s"
			"wfsresult.lpbuffer.wprintareawidth=%d"
			"%s"
			"wfsresult.lpbuffer.wprintareaheight=%d"
			"%s"
			"wfsresult.lpbuffer.wrestrictedareax=%d"
			"%s"
			"wfsresult.lpbuffer.wrestrictedareay=%d"
			"%s"
			"wfsresult.lpbuffer.wrestrictedareawidth=%d"
			"%s"
			"wfsresult.lpbuffer.wrestrictedareaheight=%d"
			"%s"
			"wfsresult.lpbuffer.wstagger=%d"
			"%s"
			"wfsresult.lpbuffer.wfoldtype=%d"
			"%s"
			"wfsresult.lpbuffer.wpapersources=%d",
			LFS_INF_PTR_QUERY_MEDIA,
			GetStringSplitChar(),
			lpMedia->media_type,
			GetStringSplitChar(),
			lpMedia->base,
			GetStringSplitChar(),
			lpMedia->unit_x,
			GetStringSplitChar(),
			lpMedia->unit_y,
			GetStringSplitChar(),
			lpMedia->size_width,
			GetStringSplitChar(),
			lpMedia->size_height,
			GetStringSplitChar(),
			lpMedia->page_count,
			GetStringSplitChar(),
			lpMedia->line_count,
			GetStringSplitChar(),
			lpMedia->print_area_x,
			GetStringSplitChar(),
			lpMedia->print_area_y,
			GetStringSplitChar(),
			lpMedia->print_area_width,
			GetStringSplitChar(),
			lpMedia->print_area_height,
			GetStringSplitChar(),
			lpMedia->restricted_area_x,
			GetStringSplitChar(),
			lpMedia->restricted_area_y,
			GetStringSplitChar(),
			lpMedia->restricted_area_width,
			GetStringSplitChar(),
			lpMedia->restricted_area_height,
			GetStringSplitChar(),
			lpMedia->stagger,
			GetStringSplitChar(),
			lpMedia->fold_type,
			GetStringSplitChar(),
			lpMedia->paper_sources);
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_MEDIA 3\n");
	}
	printf("CDCPrinter_30:HandleInfResult <<<\n");

	return strWfsResult;
}

HRESULT CDCPrinter_30::INF_PTR_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_PTR_CAPABILITIES,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::INF_PTR_FORM_LIST()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_PTR_FORM_LIST,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::INF_PTR_MEDIA_LIST()
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_PTR_MEDIA_LIST,
		NULL,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::INF_PTR_QUERY_FORM(LPCTSTR strFormName)
{
	if (NULL == strFormName)
	{
		return (short)DC_ERROR;
	}

	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_PTR_QUERY_FORM,
		(LPTSTR)strFormName,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::INF_PTR_QUERY_FIELD(LPCTSTR strFormName, LPCTSTR strFieldName)
{
	if (NULL == strFormName)
	{
		return (short)DC_ERROR;
	}

	HRESULT hResult = DC_ERROR;

	LFSPTRQUERYFIELD PtrQueryField = {0};
	PtrQueryField.form_name = (LPSTR)strFormName;
	PtrQueryField.field_name = (LPSTR)strFieldName;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_PTR_QUERY_FIELD,
		&PtrQueryField,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::INF_PTR_QUERY_MEDIA(LPCTSTR strMediaName)
{
	if (NULL == strMediaName)
	{
		return (short)DC_ERROR;
	}

	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_PTR_QUERY_MEDIA,
		(LPTSTR)strMediaName,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDBusPath.c_str(),
		&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::CMD_PTR_CONTROL_MEDIA(long lMediaControl) 
{
	HRESULT hResult = DC_ERROR;

	DWORD dwMediaControl = (DWORD)lMediaControl;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_CONTROL_MEDIA,
								&dwMediaControl,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::CMD_PTR_DISPENSE_PAPER(long lPaperSource) 
{
	HRESULT hResult = DC_ERROR;

	WORD wPaperSource = (WORD)lPaperSource;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_DISPENSE_PAPER,
								&wPaperSource,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::CMD_PTR_MEDIA_EXTENTS(long lBase, long lUnitX, long lUnitY) 
{
	// 没碰到这个方法有什么用，暂不支持
	return (short)DC_ERROR;
}

HRESULT CDCPrinter_30::CMD_PTR_PRINT_FORM(	LPCTSTR strFormName, 
													LPCTSTR strMediaName, 
													LPCTSTR strFields, 
													LPCTSTR strUNICODEFields, 
													long lAlignment,
													long lOffsetX,
													long lOffsetY,
													long lMediaControl,
													long lResolution,
													long lPaperSource)
{
	HRESULT hResult = DC_ERROR;

	LFSPTRPRINTFORM PrintForm = {0};

	PrintForm.fields = NULL;
	PrintForm.unicode_fields = NULL;
	if (strlen(strFields) > 0)
	{
		if (0 != strlen(strUNICODEFields))
		{
			int nBufSize = strlen(strFields) * 2 + 4;
			PrintForm.unicode_fields = new WCHAR[nBufSize];
			memset(PrintForm.unicode_fields, 0, nBufSize * sizeof(WCHAR));

			// ascii 转 widechar
			size_t sSize = strlen(strFields);
			wchar_t * unicode_fields = NULL;
			int dSize = mbstowcs(unicode_fields, strFields, 0) + 1;
			unicode_fields = new wchar_t[dSize];
			wmemset(unicode_fields, 0, dSize);
			int nRet = mbstowcs(unicode_fields, strFields, sSize);

			wcscpy(PrintForm.unicode_fields, unicode_fields);
			FormatUnicodeField(PrintForm.unicode_fields);

			delete[] unicode_fields;
		}
		else
		{
			int nBufSize = strlen(strFields) + 4;
			PrintForm.fields = new CHAR[nBufSize];
			memset(PrintForm.fields, 0, nBufSize * sizeof(CHAR));

			strcpy(PrintForm.fields, strFields);
			FormatAsciiField(PrintForm.fields);
		}
	}

	PrintForm.form_name = (LPTSTR)strFormName;
	if (0 != strlen(strMediaName))
	{
		PrintForm.media_name = (LPTSTR)strMediaName;
	}
	else
	{
		PrintForm.media_name = NULL;
	}

	PrintForm.alignment = (WORD)lAlignment;
	PrintForm.offset_x = (WORD)lOffsetX;
	PrintForm.offset_y = (WORD)lOffsetY;
	PrintForm.media_control = (DWORD)lMediaControl;
	PrintForm.resolution = (WORD)lResolution;
	PrintForm.paper_source = (WORD)lPaperSource;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_PRINT_FORM,
								&PrintForm,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	if (NULL != PrintForm.unicode_fields)
	{
		delete[] PrintForm.unicode_fields;
		PrintForm.unicode_fields = NULL;
	}
	
	if (NULL != PrintForm.fields)
	{
		delete[] PrintForm.fields;
		PrintForm.fields = NULL;
	}

	return hResult;
}

short CDCPrinter_30::FormatAsciiField(char * szFieldValues)
{
	if (NULL == szFieldValues)
	{
		return (short)DC_ERROR;
	}

	char * szMatchStr = "|";
	char * p = strtok(szFieldValues, szMatchStr);
	while (NULL != p)
	{
		p = strtok(NULL, szMatchStr);
	}

	return LFS_SUCCESS;
}

short CDCPrinter_30::FormatUnicodeField(wchar_t * wszFieldValues)
{
	if (NULL == wszFieldValues)
	{
		return (short)DC_ERROR;
	}

	wchar_t * wszMatchStr = L"|";
	wchar_t * p = NULL;
	wcstok(wszFieldValues, wszMatchStr, &p);
	while (NULL != p)
	{
		wcstok(NULL, wszMatchStr, &p);
	}
	return LFS_SUCCESS;
}

HRESULT CDCPrinter_30::CMD_PTR_RAW_DATA(LPCTSTR strContent) 
{
	HRESULT hResult = DC_ERROR;

	LFSPTRRAWDATA PtrRawData = {0};
	PtrRawData.input_data = LFS_PTR_NOINPUTDATA;
	PtrRawData.size = strlen(strContent);
	PtrRawData.data = (PBYTE)strContent;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_RAW_DATA,
								&PtrRawData,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::CMD_PTR_READ_FORM(LPCTSTR strFormName, LPCTSTR strFieldNames, LPCTSTR strMediaName, long lMediaControl) 
{
	HRESULT hResult = DC_ERROR;

	LFSPTRREADFORM ReadForm = {0};
	ReadForm.form_name = (LPTSTR)strFormName;
	ReadForm.field_names = NULL;
	if (strlen(strFieldNames) > 0)
	{
		int nBufSize = strlen(strFieldNames) + 4;
		ReadForm.field_names = new CHAR[nBufSize];
		memset(ReadForm.field_names, 0, nBufSize * sizeof(CHAR));

		strcpy(ReadForm.field_names, strFieldNames);
		FormatAsciiField(ReadForm.field_names);
	}

	ReadForm.media_name = NULL;
	if (strlen(strMediaName) > 0)
	{
		ReadForm.media_name = (LPTSTR)strMediaName;
	}
	
	ReadForm.media_control = lMediaControl;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_READ_FORM,
								&ReadForm,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	if (NULL != ReadForm.field_names)
	{
		delete[] ReadForm.field_names;
		ReadForm.field_names = NULL;
	}

	return hResult;
}

HRESULT CDCPrinter_30::CMD_PTR_READ_IMAGE(	long lFrontImageType,
													long lBackImageType,
													long lFrontImageColorFormat,
													long lBackImageColorFormat,
													long lCodelineFormat,
													long lImageSource,
													LPCTSTR strFrontImageFile,
													LPCTSTR strBackImageFile)
{
	HRESULT hResult = DC_ERROR;

	LFSPTRIMAGEREQUEST PtrImageRequest = {0};
	PtrImageRequest.front_image_type = (USHORT)lFrontImageType;
	PtrImageRequest.back_image_type = (USHORT)lBackImageType;
	PtrImageRequest.front_image_color_format = (USHORT)lFrontImageColorFormat;
	PtrImageRequest.back_image_color_format = (USHORT)lBackImageColorFormat;
	PtrImageRequest.codeline_format = (USHORT)lCodelineFormat;
	PtrImageRequest.image_source = (USHORT)lImageSource;
	PtrImageRequest.front_image_file = NULL;
	if (strlen(strFrontImageFile) > 0)
	{
		PtrImageRequest.front_image_file = (LPTSTR)strFrontImageFile;
	}
	PtrImageRequest.back_image_file = NULL;
	if (strlen(strBackImageFile) > 0)
	{
		PtrImageRequest.back_image_file = (LPTSTR)strBackImageFile;
	}

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_READ_IMAGE,
								&PtrImageRequest,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::CMD_PTR_RESET(long lMediaControl, long lRetractBinNumber) 
{
	HRESULT hResult = DC_ERROR;

	LFSPTRRESET PtrReset = {0};
	PtrReset.media_control = lMediaControl;
	PtrReset.retract_bin_number = (LFS_PTR_CTRLEJECT == lMediaControl) ? 0 : (short)lRetractBinNumber;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_RESET,
								(0 == lMediaControl) ? NULL : &PtrReset,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::CMD_PTR_RESET_COUNT() 
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_RESET_COUNT,
								NULL,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::CMD_PTR_RETRACT_MEDIA(long lBinNumber) 
{
	HRESULT hResult = DC_ERROR;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_RETRACT_MEDIA,
								&lBinNumber,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDBusPath.c_str(),
								&m_RequestID);

	return hResult;
}

int CDCPrinter_30::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			printf("LFS_OPEN_COMPLETE CDCPrinter_30\n");
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
		CString strWfsResult2Trace = strWfsResult;
		if (-1 != strWfsResult2Trace.find("wfsresult.lpbuffer.lpszfields="))
		{
			strWfsResult2Trace = strWfsResult2Trace.substr(0, strWfsResult2Trace.find("wfsresult.lpbuffer.lpszfields=")) 
				+ "wfsresult.lpbuffer.lpszfields=***" 
				+ strWfsResult2Trace.substr(strWfsResult2Trace.find(";", strWfsResult2Trace.find("wfsresult.lpbuffer.lpszfields=")));
		}

		CString strTrace(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						uMsg, GetXFSMsgStr(uMsg).c_str(), strWfsResult2Trace.c_str());
		WriteTrace(m_strTraceComponent.c_str(), OCXEVENT, strTrace.c_str());
		
		FireDCEvent(m_strDCName, uMsg, strWfsResult);
	}

    return 0L;
}
