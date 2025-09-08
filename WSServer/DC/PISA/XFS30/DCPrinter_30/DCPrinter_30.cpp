// DCPrinter_30.cpp: implementation of the CDCPrinter_30 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCPrinter_30.h"
// #include "../../../include/JavaScriptStringParam.h"
#include "include/JavaScriptStringParam.h"
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
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwCommand_Code);

	return strWfsResult;
}

CString CDCPrinter_30::HandleCmdResult(LPLFSRESULT lpWfsRet)
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
		case LFS_CMD_PTR_CONTROL_MEDIA:
			break ;
		case LFS_CMD_PTR_PRINT_FORM:
			break ;
		case LFS_CMD_PTR_READ_FORM:
		{
			CString strReadFormOutData;
			LPLFSPTRREADFORMOUT lpReadFormOut = NULL;
			lpReadFormOut = (LPLFSPTRREADFORMOUT)lpWfsRet->lpvdBuffer;
			if (NULL != lpReadFormOut)
			{
				if (NULL != lpReadFormOut->lpstrFields)
				{
					for (int nLoop = 0; ; nLoop ++)
					{
						if (NULL == lpReadFormOut->lpstrFields[nLoop])
						{
							if (NULL == lpReadFormOut->lpstrFields[nLoop + 1])
							{
								break ;
							}
							else
							{
								lpReadFormOut->lpstrFields[nLoop] = ',';
							}
						}
					}
				}

				if (NULL != lpReadFormOut->lpwstrUnicode_Fields)
				{
					for (int nLoop = 0; ; nLoop ++)
					{
						if (NULL == lpReadFormOut->lpwstrUnicode_Fields[nLoop])
						{
							if (NULL == lpReadFormOut->lpwstrUnicode_Fields[nLoop + 1])
							{
								break ;
							}
							else
							{
								lpReadFormOut->lpwstrUnicode_Fields[nLoop] = ',';
							}
						}
					}
				}

				// widechar 转 ascii
				char * unicode_fields = NULL;
				if (NULL != lpReadFormOut->lpwstrUnicode_Fields)
				{
					size_t sSize = wcslen(lpReadFormOut->lpwstrUnicode_Fields);
					int dSize = wcstombs(unicode_fields, lpReadFormOut->lpwstrUnicode_Fields, 0) + 1;
					unicode_fields = new char[dSize];
					memset(unicode_fields, 0, dSize);
					wcstombs(unicode_fields, lpReadFormOut->lpwstrUnicode_Fields, dSize);
				}

				strReadFormOutData = CString((NULL == lpReadFormOut->lpstrFields ? 0 : strlen(lpReadFormOut->lpstrFields))
											+ (NULL == lpReadFormOut->lpwstrUnicode_Fields ? 0 : strlen(unicode_fields))
											+ 256, 0);
				sprintf((char *)strReadFormOutData.c_str(), "%s"
									"wfsresult.lpbuffer.lpszfields=%s"
									"%s"
									"wfsresult.lpbuffer.lpszunicodefields=%s",
									GetStringSplitChar(),
									(NULL == lpReadFormOut->lpstrFields ? "" : lpReadFormOut->lpstrFields),
									GetStringSplitChar(),
									(NULL == lpReadFormOut->lpwstrUnicode_Fields ? "" : unicode_fields));
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
			lppImage = (LPLFSPTRIMAGE *)lpWfsRet->lpvdBuffer;
			if (NULL != lppImage)
			{
				int nIndex = 0;
				while (* lppImage != NULL)
				{
					CHAR * pszData = NULL;
					if (NULL != (* lppImage)->lpbData)
					{
						if ((* lppImage)->ulData_Length > 0)
						{
							pszData = new CHAR[(* lppImage)->ulData_Length * 2 + 2];
							CUtils().HextoStr((* lppImage)->lpbData, (SHORT)(* lppImage)->ulData_Length, pszData);
						}
					}
					
					strReadImageOutData = CString((NULL == (*lppImage)->lpbData || NULL == pszData ? 0 : strlen(pszData)) + 2048, 0);
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
										(* lppImage)->wImage_Source,
										GetStringSplitChar(),
										nIndex, 
										(* lppImage)->wStatus,
										GetStringSplitChar(),
										nIndex, 
										(* lppImage)->ulData_Length,
										GetStringSplitChar(),
										nIndex, 
										(NULL == (* lppImage)->lpbData || NULL == pszData ? "" : pszData));

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
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEvent_ID);

	CString strEvtResult;

	switch(lpWfsRet->u.dwEvent_ID)
	{
		case LFS_EXEE_PTR_NOMEDIA:
			break;
		case LFS_EXEE_PTR_MEDIAINSERTED:
			break;
		case LFS_EXEE_PTR_FIELDERROR:
			{
				LPLFSPTRFIELDFAIL lpFieldFail = (LPLFSPTRFIELDFAIL)lpWfsRet->lpvdBuffer;
				if(NULL != lpFieldFail)
				{
					strEvtResult = CString(strlen(lpFieldFail->lpstrForm_Name) + strlen(lpFieldFail->lpstrForm_Name) + 1024, 0);
					sprintf((char *)strEvtResult.c_str(), "%s"
						"wfsresult.lpbuffer.lpszformname=%s"
						"%s"
						"wfsresult.lpbuffer.lpszfieldname=%s"
						"%s"
						"wfsresult.lpbuffer.wfailure=%d",
						GetStringSplitChar(),
						lpFieldFail->lpstrForm_Name,
						GetStringSplitChar(),
						lpFieldFail->lpstrField_Name,
						GetStringSplitChar(),
						lpFieldFail->wFailure);
					
				}
				
				break;
			}
		case LFS_EXEE_PTR_FIELDWARNING:
			break;
		/*
		// linux 中暂不支持
		case LFS_EXEE_PTR_MEDIAPRESENTED:
			{
				LPLFSPTRMEDIAPRESENTED lpMediaPresented = (LPLFSPTRMEDIAPRESENTED)lpWfsRet->lpvdBuffer;
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
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEvent_ID);

	CString strEvtResult;
	switch (lpWfsRet->u.dwEvent_ID)
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
						lpWfsRet->hResult,
						GetStringSplitChar(),
						lpWfsRet->u.dwEvent_ID);

	CString strEvtResult;
	switch (lpWfsRet->u.dwEvent_ID)
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
		(char *)m_strDCName.c_str(),
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
		lpWfsRet->hResult,
		GetStringSplitChar(),
		lpWfsRet->u.dwCommand_Code);
	printf("CDCPrinter_30:HandleInfResult %s\n", strWfsResult.c_str());


	if (LFS_SUCCESS != lpWfsRet->hResult)
	{
		return strWfsResult;
	}

	if (LFS_INF_PTR_STATUS == lpWfsRet->u.dwCommand_Code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_STATUS 1\n");

		LPLFSPTRSTATUS lpStatus = (LPLFSPTRSTATUS)lpWfsRet->lpvdBuffer;
		if (NULL == lpStatus)
		{
			return strWfsResult;
		}

		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_STATUS 2\n");
		LPLFSPTRRETRACTBINS * lppRetractBins = lpStatus->lppRetract_Bins;
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
										nLoop, lppRetractBins[nLoop]->wRetract_Bin,
										GetStringSplitChar(),
										nLoop, lppRetractBins[nLoop]->usRetract_Count);
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
								nLoop, lpStatus->wPaper[nLoop]);
			strPapers = string(strPapers.c_str()) + strPaper;
		}

		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_STATUS 4\n");
		strWfsResult = CString(strlen(strPapers.c_str()) + strlen(strRetractBins.c_str()) + 2048, 0);
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
							lpStatus->wDevice,
							GetStringSplitChar(),
							lpStatus->wMedia,
							strPapers.c_str(),
							GetStringSplitChar(),
							lpStatus->wToner,
							GetStringSplitChar(),
							lpStatus->wInk,
							GetStringSplitChar(),
							lpStatus->wLamp,
							strRetractBins.c_str(),
							GetStringSplitChar(),
							lpStatus->usMedia_On_Stacker,
							GetStringSplitChar(),
							(NULL == lpStatus->lpstrExtra ? "NULL" : FormatExtra(lpStatus->lpstrExtra)));

		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_STATUS 5\n");
	}
	else if (LFS_INF_PTR_CAPABILITIES == lpWfsRet->u.dwCommand_Code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_CAPABILITIES 1\n");
		LPLFSPTRCAPS lpCaps = (LPLFSPTRCAPS)lpWfsRet->lpvdBuffer;
		if (NULL == lpCaps)
		{
			return strWfsResult;
		}
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_CAPABILITIES 2\n");

		CString strRetractBins;
		if (NULL != lpCaps->lpusMax_Retract)
		{
			for (int nLoop = 0; nLoop < lpCaps->usRetract_Bins; nLoop++)
			{
				CString strRetractBin(256, 0);
				sprintf((char *)strRetractBin.c_str(), "%s"
					"wfsresult.lpbuffer.lpusmaxretract[%d]=%d",
					GetStringSplitChar(),
					nLoop, lpCaps->lpusMax_Retract[nLoop]);

				strRetractBins = string(strRetractBins.c_str()) + strRetractBin;
			}
		}
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_CAPABILITIES 3\n");

		strWfsResult = string((NULL == lpCaps->lpstrExtra ? 0 : strlen(lpCaps->lpstrExtra)) + 4096, 0);
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
			lpCaps->wClass,
			GetStringSplitChar(),
			lpCaps->wType,
			GetStringSplitChar(),
			(lpCaps->bCompound ? "true" : "false"),
			GetStringSplitChar(),
			lpCaps->wDev_Resolution,
			GetStringSplitChar(),
			lpCaps->wRead_form,
			GetStringSplitChar(),
			lpCaps->wWrite_form,
			GetStringSplitChar(),
			lpCaps->wDev_Extents,
			GetStringSplitChar(),
			lpCaps->wDev_Control,
			GetStringSplitChar(),
			lpCaps->usMax_Media_On_Stacker,
			GetStringSplitChar(),
			lpCaps->bAccept_Media ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->bMulti_Page ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->wPaper_Sources,
			GetStringSplitChar(),
			lpCaps->bMedia_Taken ? "true" : "false",
			GetStringSplitChar(),
			lpCaps->usRetract_Bins,
			strRetractBins.c_str(),
			GetStringSplitChar(),
			lpCaps->wImage_Type,
			GetStringSplitChar(),
			lpCaps->wFront_Image_Color_Format,
			GetStringSplitChar(),
			lpCaps->wBack_Image_Color_Format,
			GetStringSplitChar(),
			lpCaps->wCodeline_Format,
			GetStringSplitChar(),
			lpCaps->wImage_Source,
			GetStringSplitChar(),
			lpCaps->wChar_Support,
			GetStringSplitChar(),
			lpCaps->bDispense_Paper ? "true" : "false",
			GetStringSplitChar(),
			(NULL == lpCaps->lpstrExtra ? "NULL" : FormatExtra(lpCaps->lpstrExtra)));

		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_CAPABILITIES 5\n");
	}
	else if (LFS_INF_PTR_FORM_LIST == lpWfsRet->u.dwCommand_Code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_FORM_LIST 1\n");
		LPSTR lpszFormList = (LPSTR)lpWfsRet->lpvdBuffer;
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
	else if (LFS_INF_PTR_MEDIA_LIST == lpWfsRet->u.dwCommand_Code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_MEDIA_LIST 1\n");
		LPSTR lpszMediaList = (LPSTR)lpWfsRet->lpvdBuffer;
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
	else if (LFS_INF_PTR_QUERY_FIELD == lpWfsRet->u.dwCommand_Code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FIELD 1\n");
		LPLFSFRMFIELD * lppFields = (LPLFSFRMFIELD *)lpWfsRet->lpvdBuffer;

		if (NULL != lppFields)
		{
			printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FIELD 2\n");
			for (int nLoop = 0; NULL != lppFields[nLoop]; nLoop++)
			{
				// widechar 转 ascii
				char * unicode_initial_value = NULL;
				if (NULL != lppFields[nLoop]->lpwstrUnicode_Initial_Value)
				{
					size_t sSize = wcslen(lppFields[nLoop]->lpwstrUnicode_Initial_Value);
					int dSize = wcstombs(unicode_initial_value, lppFields[nLoop]->lpwstrUnicode_Initial_Value, 0) + 1;
					unicode_initial_value = new char[dSize];
					memset(unicode_initial_value, 0, dSize);
					wcstombs(unicode_initial_value, lppFields[nLoop]->lpwstrUnicode_Initial_Value, dSize);
				}
				printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FIELD 3\n");

				char * unicode_format = NULL;
				if (NULL != lppFields[nLoop]->lpwstrUnicode_Format)
				{
					size_t sSize = wcslen(lppFields[nLoop]->lpwstrUnicode_Format);
					int dSize = wcstombs(unicode_format, lppFields[nLoop]->lpwstrUnicode_Format, 0) + 1;
					unicode_format = new char[dSize];
					memset(unicode_format, 0, dSize);
					wcstombs(unicode_format, lppFields[nLoop]->lpwstrUnicode_Format, dSize);
				}
				printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FIELD 4\n");

				CString strField = CString((NULL == lppFields[nLoop]->lpstrField_Name ? 0 : strlen(lppFields[nLoop]->lpstrField_Name))
					+ (NULL == lppFields[nLoop]->lpstrInitial_Value ? 0 : strlen(lppFields[nLoop]->lpstrInitial_Value))
					+ (NULL == lppFields[nLoop]->lpwstrUnicode_Initial_Value ? 0 : strlen(unicode_initial_value))
					+ (NULL == lppFields[nLoop]->lpstrFormat ? 0 : strlen(lppFields[nLoop]->lpstrFormat))
					+ (NULL == lppFields[nLoop]->lpwstrUnicode_Format ? 0 : strlen(unicode_format)) + 4096, 0);
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
					nLoop, (NULL == lppFields[nLoop]->lpstrField_Name ? "NULL" : lppFields[nLoop]->lpstrField_Name),
					GetStringSplitChar(),
					nLoop, lppFields[nLoop]->wIndex_Count,
					GetStringSplitChar(),
					nLoop, lppFields[nLoop]->wType,
					GetStringSplitChar(),
					nLoop, lppFields[nLoop]->wField_Class,
					GetStringSplitChar(),
					nLoop, lppFields[nLoop]->wAccess,
					GetStringSplitChar(),
					nLoop, lppFields[nLoop]->wOverflow,
					GetStringSplitChar(),
					nLoop, (NULL == lppFields[nLoop]->lpstrInitial_Value ? "NULL" : lppFields[nLoop]->lpstrInitial_Value),
					GetStringSplitChar(),
					nLoop, (NULL == lppFields[nLoop]->lpwstrUnicode_Initial_Value ? "NULL" : unicode_initial_value),
					GetStringSplitChar(),
					nLoop, (NULL == lppFields[nLoop]->lpstrFormat ? "NULL" : lppFields[nLoop]->lpstrFormat),
					GetStringSplitChar(),
					nLoop, (NULL == lppFields[nLoop]->lpwstrUnicode_Format ? "NULL" : unicode_format));
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
	else if (LFS_INF_PTR_QUERY_FORM == lpWfsRet->u.dwCommand_Code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FORM 1\n");
		LPLFSFRMHEADER lpHeader = (LPLFSFRMHEADER)lpWfsRet->lpvdBuffer;
		if (NULL == lpHeader)
		{
			return strWfsResult;
		}
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FORM 2\n");

		LPSTR fields = (LPSTR)lpHeader->lpstrFields;
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

		strWfsResult = string((NULL == lpHeader->lpstrForm_Name ? 0 : strlen(lpHeader->lpstrForm_Name))
			+ (NULL == lpHeader->lpstrUser_Prompt ? 0 : strlen(lpHeader->lpstrUser_Prompt))
			+ (NULL == lpHeader->lpstrFields ? 0 : strlen(lpHeader->lpstrFields)) + 4096, 0);
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
			(NULL == lpHeader->lpstrForm_Name ? "NULL" : lpHeader->lpstrForm_Name),
			GetStringSplitChar(),
			lpHeader->wBase,
			GetStringSplitChar(),
			lpHeader->wUnit_X,
			GetStringSplitChar(),
			lpHeader->wUnit_Y,
			GetStringSplitChar(),
			lpHeader->wWidth,
			GetStringSplitChar(),
			lpHeader->wHeight,
			GetStringSplitChar(),
			lpHeader->wAlignment,
			GetStringSplitChar(),
			lpHeader->wOrientation,
			GetStringSplitChar(),
			lpHeader->wOffset_X,
			GetStringSplitChar(),
			lpHeader->wOffset_Y,
			GetStringSplitChar(),
			lpHeader->wVersion_Major,
			GetStringSplitChar(),
			lpHeader->wVersion_Minor,
			GetStringSplitChar(),
			(NULL == lpHeader->lpstrUser_Prompt ? "NULL" : lpHeader->lpstrUser_Prompt),
			GetStringSplitChar(),
			lpHeader->wChar_Support,
			GetStringSplitChar(),
			(NULL == lpHeader->lpstrFields ? "NULL" : lpHeader->lpstrFields));
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_FORM 4\n");
	}
	else if (LFS_INF_PTR_QUERY_MEDIA == lpWfsRet->u.dwCommand_Code)
	{
		printf("CDCPrinter_30:HandleInfResult LFS_INF_PTR_QUERY_MEDIA 1\n");
		LPLFSFRMMEDIA lpMedia = (LPLFSFRMMEDIA)lpWfsRet->lpvdBuffer;
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
			lpMedia->wMedia_Type,
			GetStringSplitChar(),
			lpMedia->wBase,
			GetStringSplitChar(),
			lpMedia->wUnit_X,
			GetStringSplitChar(),
			lpMedia->wUnit_Y,
			GetStringSplitChar(),
			lpMedia->wSize_Width,
			GetStringSplitChar(),
			lpMedia->wSize_Height,
			GetStringSplitChar(),
			lpMedia->wPage_Count,
			GetStringSplitChar(),
			lpMedia->wLine_Count,
			GetStringSplitChar(),
			lpMedia->wPrint_Area_X,
			GetStringSplitChar(),
			lpMedia->wPrint_Area_Y,
			GetStringSplitChar(),
			lpMedia->wPrint_Area_Width,
			GetStringSplitChar(),
			lpMedia->wPrint_Area_Height,
			GetStringSplitChar(),
			lpMedia->wRestricted_Area_X,
			GetStringSplitChar(),
			lpMedia->wRestricted_Area_Y,
			GetStringSplitChar(),
			lpMedia->wRestricted_Area_Width,
			GetStringSplitChar(),
			lpMedia->wRestricted_Area_Height,
			GetStringSplitChar(),
			lpMedia->wStagger,
			GetStringSplitChar(),
			lpMedia->wFold_Type,
			GetStringSplitChar(),
			lpMedia->wPaper_Sources);
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
		(char *)m_strDCName.c_str(),
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
		(char *)m_strDCName.c_str(),
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
		(char *)m_strDCName.c_str(),
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
		(char *)m_strDCName.c_str(),
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
	PtrQueryField.lpstrForm_Name = (LPSTR)strFormName;
	PtrQueryField.lpstrField_Name = (LPSTR)strFieldName;

	hResult = LFSAsyncGetInfo(m_DCObject.m_hService,
		LFS_INF_PTR_QUERY_FIELD,
		&PtrQueryField,
		LFS_INDEFINITE_WAIT,
		(char *)m_strDCName.c_str(),
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
		(char *)m_strDCName.c_str(),
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
								(char *)m_strDCName.c_str(),
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
								(char *)m_strDCName.c_str(),
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

	PrintForm.lpstrFields = NULL;
	PrintForm.lpwstrUnicode_Fields = NULL;
	if (strlen(strFields) > 0)
	{
		if (0 != strlen(strUNICODEFields))
		{
			int nBufSize = strlen(strFields) * 2 + 4;
			PrintForm.lpwstrUnicode_Fields = new WCHAR[nBufSize];
			memset(PrintForm.lpwstrUnicode_Fields, 0, nBufSize * sizeof(WCHAR));

			// ascii 转 widechar
			size_t sSize = strlen(strFields);
			wchar_t * unicode_fields = NULL;
			int dSize = mbstowcs(unicode_fields, strFields, 0) + 1;
			unicode_fields = new wchar_t[dSize];
			wmemset(unicode_fields, 0, dSize);
			int nRet = mbstowcs(unicode_fields, strFields, sSize);

			wcscpy(PrintForm.lpwstrUnicode_Fields, unicode_fields);
			FormatUnicodeField(PrintForm.lpwstrUnicode_Fields);

			delete[] unicode_fields;
		}
		else
		{
			int nBufSize = strlen(strFields) + 4;
			PrintForm.lpstrFields = new CHAR[nBufSize];
			memset(PrintForm.lpstrFields, 0, nBufSize * sizeof(CHAR));

			strcpy(PrintForm.lpstrFields, strFields);
			FormatAsciiField(PrintForm.lpstrFields);
		}
	}

	PrintForm.lpstrForm_Name = (LPTSTR)strFormName;
	if (0 != strlen(strMediaName))
	{
		PrintForm.lpstrMedia_Name = (LPTSTR)strMediaName;
	}
	else
	{
		PrintForm.lpstrMedia_Name = NULL;
	}

	PrintForm.wAlignment = (WORD)lAlignment;
	PrintForm.wOffset_X = (WORD)lOffsetX;
	PrintForm.wOffset_Y = (WORD)lOffsetY;
	PrintForm.dwMedia_Control = (DWORD)lMediaControl;
	PrintForm.wResolution = (WORD)lResolution;
	PrintForm.wPaper_Source = (WORD)lPaperSource;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_PRINT_FORM,
								&PrintForm,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	if (NULL != PrintForm.lpwstrUnicode_Fields)
	{
		delete[] PrintForm.lpwstrUnicode_Fields;
		PrintForm.lpwstrUnicode_Fields = NULL;
	}
	
	if (NULL != PrintForm.lpstrFields)
	{
		delete[] PrintForm.lpstrFields;
		PrintForm.lpstrFields = NULL;
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
	PtrRawData.wInput_Data = LFS_PTR_NOINPUTDATA;
	PtrRawData.ulSize = strlen(strContent);
	PtrRawData.lpbData = (PBYTE)strContent;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_RAW_DATA,
								&PtrRawData,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::CMD_PTR_READ_FORM(LPCTSTR strFormName, LPCTSTR strFieldNames, LPCTSTR strMediaName, long lMediaControl) 
{
	HRESULT hResult = DC_ERROR;

	LFSPTRREADFORM ReadForm = {0};
	ReadForm.lpstrForm_Name = (LPTSTR)strFormName;
	ReadForm.lpstrField_Names = NULL;
	if (strlen(strFieldNames) > 0)
	{
		int nBufSize = strlen(strFieldNames) + 4;
		ReadForm.lpstrField_Names = new CHAR[nBufSize];
		memset(ReadForm.lpstrField_Names, 0, nBufSize * sizeof(CHAR));

		strcpy(ReadForm.lpstrField_Names, strFieldNames);
		FormatAsciiField(ReadForm.lpstrField_Names);
	}

	ReadForm.lpstrMedia_Name = NULL;
	if (strlen(strMediaName) > 0)
	{
		ReadForm.lpstrMedia_Name = (LPTSTR)strMediaName;
	}
	
	ReadForm.dwMedia_Control = lMediaControl;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_READ_FORM,
								&ReadForm,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	if (NULL != ReadForm.lpstrField_Names)
	{
		delete[] ReadForm.lpstrField_Names;
		ReadForm.lpstrField_Names = NULL;
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
	PtrImageRequest.wFront_Image_Type = (USHORT)lFrontImageType;
	PtrImageRequest.wBack_Image_Type = (USHORT)lBackImageType;
	PtrImageRequest.wFront_Image_Color_Format = (USHORT)lFrontImageColorFormat;
	PtrImageRequest.wBack_Image_Color_Format = (USHORT)lBackImageColorFormat;
	PtrImageRequest.wCodeline_Format = (USHORT)lCodelineFormat;
	PtrImageRequest.wImage_Source = (USHORT)lImageSource;
	PtrImageRequest.lpstrFront_Image_File = NULL;
	if (strlen(strFrontImageFile) > 0)
	{
		PtrImageRequest.lpstrFront_Image_File = (LPTSTR)strFrontImageFile;
	}
	PtrImageRequest.lpstrBack_Image_File = NULL;
	if (strlen(strBackImageFile) > 0)
	{
		PtrImageRequest.lpstrBack_Image_File = (LPTSTR)strBackImageFile;
	}

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_READ_IMAGE,
								&PtrImageRequest,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
								&m_RequestID);

	return hResult;
}

HRESULT CDCPrinter_30::CMD_PTR_RESET(long lMediaControl, long lRetractBinNumber) 
{
	HRESULT hResult = DC_ERROR;

	LFSPTRRESET PtrReset = {0};
	PtrReset.dwMedia_Control = lMediaControl;
	PtrReset.usRetract_Bin_Number = (LFS_PTR_CTRLEJECT == lMediaControl) ? 0 : (short)lRetractBinNumber;

	hResult = LFSAsyncExecute(	m_DCObject.m_hService,
								LFS_CMD_PTR_RESET,
								(0 == lMediaControl) ? NULL : &PtrReset,
								LFS_INDEFINITE_WAIT,
								(char *)m_strDCName.c_str(),
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
								(char *)m_strDCName.c_str(),
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
								(char *)m_strDCName.c_str(),
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

			printf("****** printer get info no FreeResult ******\n");
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

		CString strTrace(strlen(strWfsResult.c_str()) + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						uMsg, GetXFSMsgStr(uMsg).c_str(), strWfsResult2Trace.c_str());
		WriteTrace(m_strTraceComponent.c_str(), OCXEVENT, strTrace.c_str());
		
		FireDCEvent(m_strDCName, uMsg, strWfsResult);
	}

    return 0L;
}
