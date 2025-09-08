// DCScanner_30.cpp: implementation of the CDCScanner_30 class.
//
//////////////////////////////////////////////////////////////////////
#include "DCScanner_30.h"
#include "JavaScriptStringParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDCScanner_30::CDCScanner_30(LPCTSTR strDCName)
{
	m_strDCName = strDCName;
	m_DCObject.m_bWosaXFSRun = FALSE;
}

CDCScanner_30::~CDCScanner_30()
{

}

HRESULT CDCScanner_30::_CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid)
{
	// ��������
	HRESULT hResult = DC_ERROR;
	if (0 == stricmp(strMethod, "WFS_CMD_CHK_PROCESS_FORM"))
	{
		bValid = TRUE;
		hResult = CMD_CHK_PROCESS_FORM(	CJSStringParam::GetStringParam(strarrParams, "strFormName").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "strMediaName").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "strInputFields").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "strOutputFields").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "strUNICODEOutputFields").c_str(),
										atol(CJSStringParam::GetStringParam(strarrParams, "dwOptions").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CHK_RESET"))
	{
		bValid = TRUE;
		hResult = CMD_CHK_RESET(atol(CJSStringParam::GetStringParam(strarrParams, "lResetIn").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CHK_SET_GUIDANCE_LIGHT"))
	{
		bValid = TRUE;
		hResult = CMD_CHK_SET_GUIDANCE_LIGHT(	(short)atol(CJSStringParam::GetStringParam(strarrParams, "lGuidLight").c_str()), 
												(short)atol(CJSStringParam::GetStringParam(strarrParams, "lCommand").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_CMD_CHK_POWER_SAVE_CONTROL"))
	{
		bValid = TRUE;
		hResult = CMD_CHK_POWER_SAVE_CONTROL(atol(CJSStringParam::GetStringParam(strarrParams, "lMaxPowerSaveRecoveryTime").c_str()));
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CHK_STATUS"))
	{
		bValid = TRUE;
		hResult = INF_CHK_STATUS();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CHK_CAPABILITIES"))
	{
		bValid = TRUE;
		hResult = INF_CHK_CAPABILITIES();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CHK_FORM_LIST"))
	{
		bValid = TRUE;
		hResult = INF_CHK_FORM_LIST();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CHK_MEDIA_LIST"))
	{
		bValid = TRUE;
		hResult = INF_CHK_MEDIA_LIST();
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CHK_QUERY_FORM"))
	{
		bValid = TRUE;
		hResult = INF_CHK_QUERY_FORM(CJSStringParam::GetStringParam(strarrParams, "strFormName").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CHK_QUERY_MEDIA"))
	{
		bValid = TRUE;
		hResult = INF_CHK_QUERY_MEDIA(CJSStringParam::GetStringParam(strarrParams, "strMediaName").c_str());
	}
	else if (0 == stricmp(strMethod, "WFS_INF_CHK_QUERY_FIELD"))
	{
		bValid = TRUE;
		hResult = INF_CHK_QUERY_FIELD(	CJSStringParam::GetStringParam(strarrParams, "strFormName").c_str(),
										CJSStringParam::GetStringParam(strarrParams, "strFieldName").c_str());
	}

	return hResult;
}

CString CDCScanner_30::HandleCmdErr(LPWFSRESULT lpWfsRet)
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

CString CDCScanner_30::HandleCmdResult(LPWFSRESULT lpWfsRet)
{
	if (NULL == lpWfsRet)
	{
		return "";
	}

	if (WFS_SUCCESS != lpWfsRet->hResult)
	{
		return HandleCmdErr(lpWfsRet);
	}

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
		case WFS_CMD_CHK_PROCESS_FORM:
		{
			CString strProcessFormOutData;
			LPWFSCHKOUTPROCESSFORM lpOutProcessForm = NULL;
			lpOutProcessForm = (LPWFSCHKOUTPROCESSFORM)lpWfsRet->lpBuffer;
			if (NULL != lpOutProcessForm)
			{
				if (NULL != lpOutProcessForm->lpszInputFields)
				{
					for (int nLoop = 0; ; nLoop ++)
					{
						if (NULL == lpOutProcessForm->lpszInputFields[nLoop])
						{
							if (NULL == lpOutProcessForm->lpszInputFields[nLoop + 1])
							{
								break ;
							}
							else
							{
								lpOutProcessForm->lpszInputFields[nLoop] = ',';
							}
						}
					}
				}

				if (NULL != lpOutProcessForm->lpszUNICODEInputFields)
				{
					for (int nLoop = 0; ; nLoop ++)
					{
						if (NULL == lpOutProcessForm->lpszUNICODEInputFields[nLoop])
						{
							if (NULL == lpOutProcessForm->lpszUNICODEInputFields[nLoop + 1])
							{
								break ;
							}
							else
							{
								lpOutProcessForm->lpszUNICODEInputFields[nLoop] = ',';
							}
						}
					}
				}

				CString strFrontImage = "";
				if (lpOutProcessForm->ulFrontImageSize > 0 && NULL != lpOutProcessForm->lpFrontImage)
				{
					char * lpszFrontImage = new char[lpOutProcessForm->ulFrontImageSize * 2 + 2];
					memset(lpszFrontImage, 0, lpOutProcessForm->ulFrontImageSize * 2 + 2);

					m_Utils.HextoStr(lpOutProcessForm->lpFrontImage, (SHORT)lpOutProcessForm->ulFrontImageSize, lpszFrontImage);
					strFrontImage = lpszFrontImage;

					delete[] lpszFrontImage;
					lpszFrontImage = NULL;
				}

				CString strBackImage = "";
				if (lpOutProcessForm->ulBackImageSize > 0 && NULL != lpOutProcessForm->lpBackImage)
				{
					char * lpszBackImage = new char[lpOutProcessForm->ulBackImageSize * 2 + 2];
					memset(lpszBackImage, 0, lpOutProcessForm->ulBackImageSize * 2 + 2);

					m_Utils.HextoStr(lpOutProcessForm->lpBackImage, (SHORT)lpOutProcessForm->ulBackImageSize, lpszBackImage);
					strBackImage = lpszBackImage;

					delete[] lpszBackImage;
					lpszBackImage = NULL;
				}

				// widechar ת ascii
				char * lpszUNICODEInputFields = NULL;
				if (NULL != lpOutProcessForm->lpszUNICODEInputFields)
				{
					size_t sSize = wcslen(lpOutProcessForm->lpszUNICODEInputFields);
					int dSize = wcstombs(lpszUNICODEInputFields, lpOutProcessForm->lpszUNICODEInputFields, 0) + 1;
					lpszUNICODEInputFields = new char[dSize];
					memset(lpszUNICODEInputFields, 0, dSize);
					wcstombs(lpszUNICODEInputFields, lpOutProcessForm->lpszUNICODEInputFields, dSize);
				}

				strProcessFormOutData = CString((NULL == lpOutProcessForm->lpszInputFields ? 0 : strlen(lpOutProcessForm->lpszInputFields))
											+ (NULL == lpOutProcessForm->lpszUNICODEInputFields ? 0 : strlen(lpszUNICODEInputFields))
											+ (NULL == lpOutProcessForm->lpFrontImage ? 0 : strFrontImage.length())
											+ (NULL == lpOutProcessForm->lpBackImage ? 0 : strBackImage.length())
											+ 2048, 0);
				sprintf((char *)strProcessFormOutData.c_str(), "%s"
									"wfsresult.lpbuffer.lpszinputfields=%s"
									"%s"
									"wfsresult.lpbuffer.lpszunicodeinputfields=%s"
									"%s"
									"wfsresult.lpbuffer.wfrontimagetype=%d"
									"%s"
									"wfsresult.lpbuffer.ulfrontimagesize=%d"
									"%s"
									"wfsresult.lpbuffer.lpfrontimage=%s"
									"%s"
									"wfsresult.lpbuffer.wbackimagetype=%d"
									"%s"
									"wfsresult.lpbuffer.ulbackimagesize=%d"
									"%s"
									"wfsresult.lpbuffer.lpbackimage=%s",
									GetStringSplitChar(),
									(NULL == lpOutProcessForm->lpszInputFields ? "" : lpOutProcessForm->lpszInputFields),
									GetStringSplitChar(),
									(NULL == lpOutProcessForm->lpszUNICODEInputFields ? "" : lpszUNICODEInputFields),
									GetStringSplitChar(),
									lpOutProcessForm->wFrontImageType,
									GetStringSplitChar(),
									lpOutProcessForm->ulFrontImageSize,
									GetStringSplitChar(),
									(NULL == lpOutProcessForm->lpFrontImage ? "" : strFrontImage),
									GetStringSplitChar(),
									lpOutProcessForm->wBackImageType,
									GetStringSplitChar(),
									lpOutProcessForm->ulBackImageSize,
									GetStringSplitChar(),
									(NULL == lpOutProcessForm->lpBackImage ? "" : strBackImage));
				strCmdResult += strProcessFormOutData;

				if (NULL != lpszUNICODEInputFields)
				{
					delete[] lpszUNICODEInputFields;
				}
			}

			break ;
		}
		case WFS_CMD_CHK_RESET:
			break ;
		case WFS_CMD_CHK_SET_GUIDANCE_LIGHT:
			break ;
		case WFS_CMD_CHK_POWER_SAVE_CONTROL:
			break ;
		default:
			break ;
	}

	strWfsResult += strCmdResult;

	return strWfsResult;
}

CString CDCScanner_30::HandleEXEEvtResult(LPWFSRESULT lpWfsRet)
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

	CString strEvtResult;

	switch(lpWfsRet->u.dwEventID)
	{
		case WFS_EXEE_CHK_NOMEDIA:
		{
			LPSTR lpszUserPrompt = (LPSTR)lpWfsRet->lpBuffer;
			if(NULL != lpszUserPrompt)
			{
				strEvtResult = CString(256, 0);
				sprintf((char *)strEvtResult.c_str(), "%s"
					"wfsresult.lpbuffer=%s",
					GetStringSplitChar(),
					* lpszUserPrompt);
			}
			
			break;
		}
		case WFS_EXEE_CHK_MEDIAINSERTED:
			break;
		case WFS_EXEE_CHK_FIELDERROR:
		case WFS_EXEE_CHK_FIELDWARNING:
		{
			LPWFSCHKFIELDFAIL lpFieldFail = (LPWFSCHKFIELDFAIL)lpWfsRet->lpBuffer;
			if(NULL != lpFieldFail)
			{
				strEvtResult = CString(1024, 0);
				sprintf((char *)strEvtResult.c_str(), "%s"
					"wfsresult.lpbuffer.lpszformname=%s"
					"%s"
					"wfsresult.lpbuffer.lpszfieldname=%s"
					"%s"
					"wfsresult.lpbuffer.wfailure=%ld",
					GetStringSplitChar(),
					lpFieldFail->lpszFormName,
					GetStringSplitChar(),
					lpFieldFail->lpszFieldName,
					GetStringSplitChar(),
					lpFieldFail->wFailure);
			}
			
			break;
		}
		default:
			break;
	}
	
	strWfsResult += strEvtResult;

	return strWfsResult;
}

CString CDCScanner_30::HandleUSEREvtResult(LPWFSRESULT lpWfsRet)
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

	CString strEvtResult;
	switch (lpWfsRet->u.dwEventID)
	{
		case WFS_USRE_CHK_INKTHRESHOLD:
		{
			LPWORD lpwInkThreshold = (LPWORD)lpWfsRet->lpBuffer;
			if(NULL != lpwInkThreshold)
			{
				strEvtResult = CString(256, 0);
				sprintf((char *)strEvtResult.c_str(), "%s"
					"wfsresult.lpbuffer=%d",
					GetStringSplitChar(),
					* lpwInkThreshold);
			}
			
			break;
		}
		default:
			break;
	}

	strWfsResult += strEvtResult;

	return strWfsResult;
}

CString CDCScanner_30::HandleSRVEvtResult(LPWFSRESULT lpWfsRet)
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

	CString strEvtResult;
	switch (lpWfsRet->u.dwEventID)
	{
		case WFS_SRVE_CHK_MEDIAINSERTED:
			break ;
		case WFS_SRVE_CHK_MEDIADETECTED:
		{
			LPWORD lpwResetOut = (LPWORD)lpWfsRet->lpBuffer;
			if(NULL != lpwResetOut)
			{
				strEvtResult = CString(256, 0);
				sprintf((char *)strEvtResult.c_str(), "%s"
					"wfsresult.lpbuffer=%d",
					GetStringSplitChar(),
					* lpwResetOut);
			}
			
			break;
		}
		case WFS_SRVE_CHK_DEVICEPOSITION:
		{
			LPWFSCHKDEVICEPOSITION lpDevicePosition = (LPWFSCHKDEVICEPOSITION)lpWfsRet->lpBuffer;
			if(NULL != lpDevicePosition)
			{
				strEvtResult = CString(256, 0);
				sprintf((char *)strEvtResult.c_str(), "%s"
					"wfsresult.lpbuffer.wposition=%d",
					GetStringSplitChar(),
					lpDevicePosition->wPosition);
			}
			
			break;
		}
		case WFS_SRVE_CHK_POWER_SAVE_CHANGE:
		{
			LPWFSCHKPOWERSAVECHANGE lpPowerSaveChange = (LPWFSCHKPOWERSAVECHANGE)lpWfsRet->lpBuffer;
			if(NULL != lpPowerSaveChange)
			{
				strEvtResult = CString(256, 0);
				sprintf((char *)strEvtResult.c_str(), "%s"
					"wfsresult.lpbuffer.uspowersaverecoverytime=%d",
					GetStringSplitChar(),
					lpPowerSaveChange->usPowerSaveRecoveryTime);
			}
			
			break;
		}
		default:
			break;
	}

	strWfsResult += strEvtResult;

	return strWfsResult;
}

CString CDCScanner_30::HandleSysEvtResult(LPWFSRESULT lpWfsRet)
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

CString	CDCScanner_30::GetXFSCmdStr(DWORD dwCmdCode)
{
	struct XFSCMD {
		char strCmd[128];
		DWORD iCmd;
	}XFSCmd[]={
		{"WFS_CMD_CHK_CONTROL_MEDIA"        ,(CHK_SERVICE_OFFSET + 1)},
		{"WFS_CMD_CHK_PRINT_FORM"           ,(CHK_SERVICE_OFFSET + 2)},
		{"WFS_CMD_CHK_READ_FORM"            ,(CHK_SERVICE_OFFSET + 3)},
		{"WFS_CMD_CHK_RAW_DATA"             ,(CHK_SERVICE_OFFSET + 4)},
		{"WFS_CMD_CHK_MEDIA_EXTENTS"        ,(CHK_SERVICE_OFFSET + 5)},
		{"WFS_CMD_CHK_RESET_COUNT"          ,(CHK_SERVICE_OFFSET + 6)},
		{"WFS_CMD_CHK_READ_IMAGE"           ,(CHK_SERVICE_OFFSET + 7)},
		{"WFS_CMD_CHK_RESET"                ,(CHK_SERVICE_OFFSET + 8)},
		{"WFS_CMD_CHK_RETRACT_MEDIA"        ,(CHK_SERVICE_OFFSET + 9)},
		{"WFS_CMD_CHK_DISPENSE_PAPER"       ,(CHK_SERVICE_OFFSET + 10)}
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

CString	CDCScanner_30::GetXFSMsgStr(DWORD dwEventID)
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

		{"WFS_EXEE_CHK_NOMEDIA"             ,(CHK_SERVICE_OFFSET + 1)},
		{"WFS_EXEE_CHK_MEDIAINSERTED"       ,(CHK_SERVICE_OFFSET + 2)},
		{"WFS_EXEE_CHK_FIELDERROR"          ,(CHK_SERVICE_OFFSET + 3)},
		{"WFS_EXEE_CHK_FIELDWARNING"        ,(CHK_SERVICE_OFFSET + 4)},
		{"WFS_USRE_CHK_RETRACTBINTHRESHOLD" ,(CHK_SERVICE_OFFSET + 5)},
		{"WFS_SRVE_CHK_MEDIATAKEN"          ,(CHK_SERVICE_OFFSET + 6)},
		{"WFS_USRE_CHK_PAPERTHRESHOLD"      ,(CHK_SERVICE_OFFSET + 7)},
		{"WFS_USRE_CHK_TONERTHRESHOLD"      ,(CHK_SERVICE_OFFSET + 8)},
		{"WFS_SRVE_CHK_MEDIAINSERTED"       ,(CHK_SERVICE_OFFSET + 9)},
		{"WFS_USRE_CHK_LAMPTHRESHOLD"       ,(CHK_SERVICE_OFFSET + 10)},
		{"WFS_USRE_CHK_INKTHRESHOLD"        ,(CHK_SERVICE_OFFSET + 11)},
		{"WFS_SRVE_CHK_MEDIADETECTED"       ,(CHK_SERVICE_OFFSET + 12)}
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

CString	CDCScanner_30::GetXFSSysEvtStr(DWORD dwEventID)
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

CString	CDCScanner_30::GetXFSErrStr(HRESULT hResult)
{
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
		{"WFS_ERR_CHK_FORMNOTFOUND"          ,(-(CHK_SERVICE_OFFSET + 0))},
		{"WFS_ERR_CHK_FORMINVALID"           ,(-(CHK_SERVICE_OFFSET + 1))},
		{"WFS_ERR_CHK_MEDIANOTFOUND"         ,(-(CHK_SERVICE_OFFSET + 2))},
		{"WFS_ERR_CHK_MEDIAINVALID"          ,(-(CHK_SERVICE_OFFSET + 3))},
		{"WFS_ERR_CHK_MEDIAOVERFLOW"         ,(-(CHK_SERVICE_OFFSET + 4))},
		{"WFS_ERR_CHK_FIELDNOTFOUND"         ,(-(CHK_SERVICE_OFFSET + 5))},
		{"WFS_ERR_CHK_FIELDINVALID"          ,(-(CHK_SERVICE_OFFSET + 6))},
		{"WFS_ERR_CHK_FIELDERROR"            ,(-(CHK_SERVICE_OFFSET + 7))},
		{"WFS_ERR_CHK_REQDFIELDMISSING"      ,(-(CHK_SERVICE_OFFSET + 8))},
		{"WFS_ERR_CHK_FIELDSPECFAILURE"      ,(-(CHK_SERVICE_OFFSET + 9))},
		{"WFS_ERR_CHK_CHARSETDATA"           ,(-(CHK_SERVICE_OFFSET + 10))},
		{"WFS_ERR_CHK_MEDIAJAM"              ,(-(CHK_SERVICE_OFFSET + 11))},
		{"WFS_ERR_CHK_SHUTTERFAIL"           ,(-(CHK_SERVICE_OFFSET + 12))},
		{"WFS_ERR_CHK_INVALID_PORT"          ,(-(CHK_SERVICE_OFFSET + 13))},
		{"WFS_ERR_CHK_POWERSAVETOOSHORT"     ,(-(CHK_SERVICE_OFFSET + 14))},
		{"WFS_ERR_CHK_POWERSAVEMEDIAPRESENT" ,(-(CHK_SERVICE_OFFSET + 15))}
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

HRESULT CDCScanner_30::INF_CHK_STATUS()
{
	HRESULT hResult = DC_ERROR;

	CString strWfsResult = "";

	LPWFSRESULT lpWfsRet = NULL;
	hResult = WFSGetInfo(	m_DCObject.m_hService, 
							WFS_INF_CHK_STATUS, 
							NULL, 
							WFS_INDEFINITE_WAIT, 
							&lpWfsRet);

	if (WFS_SUCCESS == hResult)
	{
		LPWFSCHKSTATUS lpStatus = (LPWFSCHKSTATUS)lpWfsRet->lpBuffer;
		if (NULL == lpStatus)
		{
			WFSFreeResult(lpWfsRet);
			return (short)DC_ERROR;
		}
		
		CString strGuidLights = "";
		for (int nLoop = 0; nLoop < WFS_CHK_GUIDLIGHTS_SIZE; nLoop ++)
		{
			CString strGuidLight(256, 0);
			sprintf((char *)strGuidLight.c_str(), 	"%s"
									"wfsresult.lpbuffer.dwguidlights[%d]=%d",
									GetStringSplitChar(),
									nLoop, lpStatus->dwGuidLights[nLoop]);
			strGuidLights += strGuidLight;
		}

		strWfsResult = CString((NULL == lpStatus->lpszExtra ? 0 : strlen(lpStatus->lpszExtra)) + strGuidLights.length() + 1024, 0);
		sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
							"%s"
							"wfsresult.lpbuffer.fwdevice=%d"
							"%s"
							"wfsresult.lpbuffer.fwmedia=%d"
							"%s"
							"wfsresult.lpbuffer.fwink=%d"
							"%s"
							"wfsresult.lpbuffer.lpszextra=%s"
							"%s"
							"%s"
							"wfsresult.lpbuffer.wdeviceposition=%d"
							"%s"
							"wfsresult.lpbuffer.uspowersaverecoverytime=%d",
							WFS_INF_CHK_STATUS,
							GetStringSplitChar(),
							lpStatus->fwDevice,
							GetStringSplitChar(),
							lpStatus->fwMedia,
							GetStringSplitChar(),
							lpStatus->fwInk,
							GetStringSplitChar(),
							(NULL == lpStatus->lpszExtra ? "NULL" : FormatExtra(lpStatus->lpszExtra)),
							strGuidLights,
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

HRESULT CDCScanner_30::INF_CHK_CAPABILITIES()
{
	HRESULT hResult = DC_ERROR;

	LPWFSRESULT lpResult = NULL;
	hResult = WFSGetInfo(	m_DCObject.m_hService,
							WFS_INF_CHK_CAPABILITIES,
							NULL,
							WFS_INDEFINITE_WAIT,
							&lpResult);

	if (WFS_SUCCESS != hResult)
	{
		return hResult;
	}

	LPWFSCHKCAPS lpCaps = (LPWFSCHKCAPS)lpResult->lpBuffer;
	if (NULL == lpCaps)
	{
		WFSFreeResult(lpResult);
		return (short)DC_ERROR;
	}

	CString strGuidLights = "";
	for (int nLoop = 0; nLoop < WFS_CHK_GUIDLIGHTS_SIZE; nLoop ++)
	{
		CString strGuidLight(256, 0);
		sprintf((char *)strGuidLight.c_str(), 	"%s"
								"wfsresult.lpbuffer.dwguidlights[%d]=%d",
								GetStringSplitChar(),
								nLoop, lpCaps->dwGuidLights[nLoop]);
		strGuidLights += strGuidLight;
	}

	CString strWfsResult = CString((NULL == lpCaps->lpszFontNames ? 0 : strlen(lpCaps->lpszFontNames))
								+ (NULL == lpCaps->lpszEncodeNames ? 0 : strlen(lpCaps->lpszEncodeNames))
								+ (NULL == lpCaps->lpszExtra ? 0 : strlen(lpCaps->lpszExtra))
								+ strGuidLights.length() + 1024, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
						"%s"
						"wfsresult.lpbuffer.wclass=%d"
						"%s"
						"wfsresult.lpbuffer.fwtype=%d"
						"%s"
						"wfsresult.lpbuffer.bcompound=%s"
						"%s"
						"wfsresult.lpbuffer.bmicr=%s"
						"%s"
						"wfsresult.lpbuffer.bocr=%s"
						"%s"
						"wfsresult.lpbuffer.bautofeed=%s"
						"%s"
						"wfsresult.lpbuffer.bendorser=%s"
						"%s"
						"wfsresult.lpbuffer.bencoder=%s"
						"%s"
						"wfsresult.lpbuffer.fwstamp=%d"
						"%s"
						"wfsresult.lpbuffer.wimagecapture=%d"
						"%s"
						"wfsresult.lpbuffer.lpszfontnames=%s"
						"%s"
						"wfsresult.lpbuffer.lpszencodenames=%s"
						"%s"
						"wfsresult.lpbuffer.fwcharsupport=%d"
						"%s"
						"wfsresult.lpbuffer.lpszextra=%s"
						"%s"
						"%s"
						"wfsresult.lpbuffer.bpowersavecontrol=%s",
						WFS_INF_CHK_CAPABILITIES,
						GetStringSplitChar(),
						lpCaps->wClass,
						GetStringSplitChar(),
						lpCaps->fwType,
						GetStringSplitChar(),
						(lpCaps->bCompound ? "TRUE" : "false"),
						GetStringSplitChar(),
						(lpCaps->bMICR ? "TRUE" : "false"),
						GetStringSplitChar(),
						(lpCaps->bOCR ? "TRUE" : "false"),
						GetStringSplitChar(),
						(lpCaps->bAutoFeed ? "TRUE" : "false"),
						GetStringSplitChar(),
						(lpCaps->bEndorser ? "TRUE" : "false"),
						GetStringSplitChar(),
						(lpCaps->bEncoder ? "TRUE" : "false"),
						GetStringSplitChar(),
						lpCaps->fwStamp,
						GetStringSplitChar(),
						lpCaps->wImageCapture,
						GetStringSplitChar(),
						(NULL == lpCaps->lpszFontNames ? "NULL" : lpCaps->lpszFontNames),
						GetStringSplitChar(),
						(NULL == lpCaps->lpszEncodeNames ? "NULL" : lpCaps->lpszEncodeNames),
						GetStringSplitChar(),
						lpCaps->fwCharSupport,
						GetStringSplitChar(),
						(NULL == lpCaps->lpszExtra ? "NULL" : FormatExtra(lpCaps->lpszExtra)),
						strGuidLights,
						GetStringSplitChar(),
						(lpCaps->bPowerSaveControl ? "TRUE" : "false"));

	WFSFreeResult(lpResult);

	if ("" != strWfsResult)
	{
		CString strTrace(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), strWfsResult.c_str());
		WriteTrace(OCXGetInfo, strTrace);
		
		FireDCEvent(WFS_GETINFO_COMPLETE, strWfsResult);

		return WFS_SUCCESS;
	}
	
	return hResult;
}

HRESULT CDCScanner_30::INF_CHK_FORM_LIST()
{
	HRESULT hResult = DC_ERROR;

	LPWFSRESULT lpResult = NULL;
	hResult = WFSGetInfo(	m_DCObject.m_hService,
							WFS_INF_CHK_FORM_LIST,
							NULL,
							WFS_INDEFINITE_WAIT,
							&lpResult);

	if (WFS_SUCCESS != hResult)
	{
		return hResult;
	}

	LPSTR lpszFormList = (LPSTR)lpResult->lpBuffer;
	if (NULL != lpszFormList)
	{
		for (int nLoop = 0; ; nLoop ++)
		{
			if (NULL == lpszFormList[nLoop] && NULL == lpszFormList[nLoop + 1])
			{
				lpszFormList[nLoop] = '\0';
				break ;
			}
			else if (NULL == lpszFormList[nLoop])
			{
				lpszFormList[nLoop] = ',';
			}
		}
	}

	CString strWfsResult((NULL == lpszFormList ? 0 : strlen(lpszFormList)) + 1024, 0);
	// wfsresult.lpbuffer��������WFS_INF_CHK_FORM_LIST��WFS_INF_CHK_MEDIA_LIST��������ʹ�ñ��������
	sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
						"%s"
						"wfsresult.lpszformlist=%s",
						WFS_INF_CHK_FORM_LIST,
						GetStringSplitChar(),
						(NULL == lpszFormList ? "NULL" : lpszFormList));

	WFSFreeResult(lpResult);

	if ("" != strWfsResult)
	{
		CString strTrace(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), strWfsResult.c_str());
		WriteTrace(OCXGetInfo, strTrace);
		
		FireDCEvent(WFS_GETINFO_COMPLETE, strWfsResult);

		return WFS_SUCCESS;
	}
	
	return hResult;
}

HRESULT CDCScanner_30::INF_CHK_MEDIA_LIST()
{
	HRESULT hResult = DC_ERROR;

	LPWFSRESULT lpResult = NULL;
	hResult = WFSGetInfo(	m_DCObject.m_hService,
							WFS_INF_CHK_MEDIA_LIST,
							NULL,
							WFS_INDEFINITE_WAIT,
							&lpResult);

	if (WFS_SUCCESS != hResult)
	{
		return hResult;
	}

	LPSTR lpszMediaList = (LPSTR)lpResult->lpBuffer;
	if (NULL != lpszMediaList)
	{
		for (int nLoop = 0; ; nLoop ++)
		{
			if (NULL == lpszMediaList[nLoop] && NULL == lpszMediaList[nLoop + 1])
			{
				lpszMediaList[nLoop] = '\0';
				break ;
			}
			else if (NULL == lpszMediaList[nLoop])
			{
				lpszMediaList[nLoop] = ',';
			}
		}
	}

	CString strWfsResult((NULL == lpszMediaList ? 0 : strlen(lpszMediaList)) + 1024, 0);
	// wfsresult.lpbuffer��������WFS_INF_CHK_FORM_LIST��WFS_INF_CHK_MEDIA_LIST��������ʹ�ñ��������
	sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
						"%s"
						"wfsresult.lpszmedialist=%s",
						WFS_INF_CHK_MEDIA_LIST,
						GetStringSplitChar(),
						(NULL == lpszMediaList ? "NULL" : lpszMediaList));

	WFSFreeResult(lpResult);

	if ("" != strWfsResult)
	{
		CString strTrace(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), strWfsResult.c_str());
		WriteTrace(OCXGetInfo, strTrace);
		
		FireDCEvent(WFS_GETINFO_COMPLETE, strWfsResult);

		return WFS_SUCCESS;
	}
	
	return hResult;
}

HRESULT CDCScanner_30::INF_CHK_QUERY_FORM(LPCTSTR strFormName)
{
	if (NULL == strFormName)
	{
		return (short)DC_ERROR;
	}

	HRESULT hResult = DC_ERROR;

	LPWFSRESULT lpResult = NULL;
	hResult = WFSGetInfo(	m_DCObject.m_hService,
							WFS_INF_CHK_QUERY_FORM,
							(LPTSTR)strFormName,
							WFS_INDEFINITE_WAIT,
							&lpResult);

	if (WFS_SUCCESS != hResult)
	{
		return hResult;
	}

	LPWFSCHKFRMHEADER lpFormHeader = (LPWFSCHKFRMHEADER)lpResult->lpBuffer;
	if (NULL == lpFormHeader)
	{
		return (short)DC_ERROR;
	}

	LPSTR lpszFields = (LPSTR)lpFormHeader->lpszFields;
	if (NULL != lpszFields)
	{
		for (int nLoop = 0; ; nLoop ++)
		{
			if (NULL == lpszFields[nLoop] && NULL == lpszFields[nLoop + 1])
			{
				lpszFields[nLoop] = '\0';
				break ;
			}
			else if (NULL == lpszFields[nLoop])
			{
				lpszFields[nLoop] = ',';
			}
		}
	}

	CString strWfsResult((NULL == lpFormHeader->lpszFormName ? 0 : strlen(lpFormHeader->lpszFormName))
						+ (NULL == lpFormHeader->lpszFields ? 0 : strlen(lpFormHeader->lpszFields))
						+ 2048, 0);
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
						"wfsresult.lpbuffer.woffsetx=%d"
						"%s"
						"wfsresult.lpbuffer.woffsety=%d"
						"%s"
						"wfsresult.lpbuffer.wversionmajor=%d"
						"%s"
						"wfsresult.lpbuffer.wversionminor=%d"
						"%s"
						"wfsresult.lpbuffer.fwcharsupport=%d"
						"%s"
						"wfsresult.lpszfields=%s",
						WFS_INF_CHK_QUERY_FORM,
						GetStringSplitChar(),
						(NULL == lpFormHeader->lpszFormName ? "NULL" : lpFormHeader->lpszFormName),
						GetStringSplitChar(),
						lpFormHeader->wBase,
						GetStringSplitChar(),
						lpFormHeader->wUnitX,
						GetStringSplitChar(),
						lpFormHeader->wUnitY,
						GetStringSplitChar(),
						lpFormHeader->wWidth,
						GetStringSplitChar(),
						lpFormHeader->wHeight,
						GetStringSplitChar(),
						lpFormHeader->wAlignment,
						GetStringSplitChar(),
						lpFormHeader->wOffsetX,
						GetStringSplitChar(),
						lpFormHeader->wOffsetY,
						GetStringSplitChar(),
						lpFormHeader->wVersionMajor,
						GetStringSplitChar(),
						lpFormHeader->wVersionMinor,
						GetStringSplitChar(),
						lpFormHeader->fwCharSupport,
						GetStringSplitChar(),
						(NULL == lpFormHeader->lpszFields ? "NULL" : lpFormHeader->lpszFields));

	WFSFreeResult(lpResult);

	if ("" != strWfsResult)
	{
		CString strTrace(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), strWfsResult.c_str());
		WriteTrace(OCXGetInfo, strTrace);
		
		FireDCEvent(WFS_GETINFO_COMPLETE, strWfsResult);

		return WFS_SUCCESS;
	}
	
	return hResult;
}

HRESULT CDCScanner_30::INF_CHK_QUERY_FIELD(LPCTSTR strFormName, LPCTSTR strFieldName)
{
	if (NULL == strFormName)
	{
		return (short)DC_ERROR;
	}

	HRESULT hResult = DC_ERROR;

	WFSCHKQUERYFIELD PtrQueryField = {0};
	PtrQueryField.lpszFormName = (LPSTR)strFormName;
	PtrQueryField.lpszFieldName = (LPSTR)strFieldName;

	LPWFSRESULT lpResult = NULL;
	hResult = WFSGetInfo(	m_DCObject.m_hService,
							WFS_INF_CHK_QUERY_FIELD,
							&PtrQueryField,
							WFS_INDEFINITE_WAIT,
							&lpResult);

	if (WFS_SUCCESS != hResult)
	{
		return hResult;
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.u.dwcommandcode=%d"
						"%s",
						WFS_INF_CHK_QUERY_FIELD,
						GetStringSplitChar());

	LPWFSCHKFRMFIELD * lppFields = (LPWFSCHKFRMFIELD *)lpResult->lpBuffer;

	if (NULL != lppFields)
	{
		for (int nLoop = 0; NULL != lppFields[nLoop]; nLoop ++)
		{
			// widechar ת ascii
			char * lpszUNICODEInitialValue = NULL;
			if (NULL != lppFields[nLoop]->lpszUNICODEInitialValue)
			{
				size_t sSize = wcslen(lppFields[nLoop]->lpszUNICODEInitialValue);
				int dSize = wcstombs(lpszUNICODEInitialValue, lppFields[nLoop]->lpszUNICODEInitialValue, 0) + 1;
				lpszUNICODEInitialValue = new char[dSize];
				memset(lpszUNICODEInitialValue, 0, dSize);
				wcstombs(lpszUNICODEInitialValue, lppFields[nLoop]->lpszUNICODEInitialValue, dSize);
			}

			char * lpszUNICODEFormat = NULL;
			if (NULL != lppFields[nLoop]->lpszUNICODEFormat)
			{
				size_t sSize = wcslen(lppFields[nLoop]->lpszUNICODEFormat);
				int dSize = wcstombs(lpszUNICODEFormat, lppFields[nLoop]->lpszUNICODEFormat, 0) + 1;
				lpszUNICODEFormat = new char[dSize];
				memset(lpszUNICODEFormat, 0, dSize);
				wcstombs(lpszUNICODEFormat, lppFields[nLoop]->lpszUNICODEFormat, dSize);
			}

			CString strField = CString((NULL == lppFields[nLoop]->lpszFieldName ? 0 : strlen(lppFields[nLoop]->lpszFieldName))
									+ (NULL == lppFields[nLoop]->lpszInitialValue ? 0 : strlen(lppFields[nLoop]->lpszInitialValue))
									+ (NULL == lppFields[nLoop]->lpszUNICODEInitialValue ? 0 : strlen(lpszUNICODEInitialValue))
									+ (NULL == lppFields[nLoop]->lpszFormat ? 0 : strlen(lppFields[nLoop]->lpszFormat))
									+ (NULL == lppFields[nLoop]->lpszUNICODEFormat ? 0 : strlen(lpszUNICODEFormat)) + 4096, 0);
			sprintf((char *)strField.c_str(), "wfsresult.lpbuffer[%d].lpszfieldname=%s"
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
							nLoop, (NULL == lppFields[nLoop]->lpszFieldName ? "NULL" : lppFields[nLoop]->lpszFieldName),
							GetStringSplitChar(),
							nLoop, lppFields[nLoop]->fwType,
							GetStringSplitChar(),
							nLoop, lppFields[nLoop]->fwClass,
							GetStringSplitChar(),
							nLoop, lppFields[nLoop]->fwAccess,
							GetStringSplitChar(),
							nLoop, lppFields[nLoop]->fwOverflow,
							GetStringSplitChar(),
							nLoop, (NULL == lppFields[nLoop]->lpszInitialValue ? "NULL" : lppFields[nLoop]->lpszInitialValue),
							GetStringSplitChar(),
							nLoop, (NULL == lppFields[nLoop]->lpszUNICODEInitialValue ? "NULL" : lpszUNICODEInitialValue),
							GetStringSplitChar(),
							nLoop, (NULL == lppFields[nLoop]->lpszFormat ? "NULL" : lppFields[nLoop]->lpszFormat),
							GetStringSplitChar(),
							nLoop, (NULL == lppFields[nLoop]->lpszUNICODEFormat ? "NULL" : lpszUNICODEFormat));

			strWfsResult += strField;

			if (NULL != lpszUNICODEInitialValue)
			{
				delete[] lpszUNICODEInitialValue;
			}
			if (NULL != lpszUNICODEFormat)
			{
				delete[] lpszUNICODEFormat;
			}
		}
	}

	WFSFreeResult(lpResult);

	if ("" != strWfsResult)
	{
		CString strTrace(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), strWfsResult.c_str());
		WriteTrace(OCXGetInfo, strTrace);
		
		FireDCEvent(WFS_GETINFO_COMPLETE, strWfsResult);

		return WFS_SUCCESS;
	}
	
	return hResult;
}

HRESULT CDCScanner_30::INF_CHK_QUERY_MEDIA(LPCTSTR strMediaName)
{
	if (NULL == strMediaName)
	{
		return (short)DC_ERROR;
	}

	HRESULT hResult = DC_ERROR;

	LPWFSRESULT lpResult = NULL;
	hResult = WFSGetInfo(	m_DCObject.m_hService,
							WFS_INF_CHK_QUERY_MEDIA,
							(LPTSTR)strMediaName,
							WFS_INDEFINITE_WAIT,
							&lpResult);

	if (WFS_SUCCESS != hResult)
	{
		return hResult;
	}

	LPWFSCHKFRMMEDIA lpFormMedia = (LPWFSCHKFRMMEDIA)lpResult->lpBuffer;
	if (NULL == lpFormMedia)
	{
		return (short)DC_ERROR;
	}

	CString strWfsResult(4096, 0);
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
						"wfsresult.lpbuffer.wcheckareax=%d"
						"%s"
						"wfsresult.lpbuffer.wcheckareay=%d"
						"%s"
						"wfsresult.lpbuffer.wcheckareawidth=%d"
						"%s"
						"wfsresult.lpbuffer.wcheckareaheight=%d"
						"%s"
						"wfsresult.lpbuffer.wrestrictedareax=%d"
						"%s"
						"wfsresult.lpbuffer.wrestrictedareay=%d"
						"%s"
						"wfsresult.lpbuffer.wrestrictedareawidth=%d"
						"%s"
						"wfsresult.lpbuffer.wrestrictedareaheight=%d",
						WFS_INF_CHK_QUERY_MEDIA,
						GetStringSplitChar(),
						lpFormMedia->fwMediaType,
						GetStringSplitChar(),
						lpFormMedia->wBase,
						GetStringSplitChar(),
						lpFormMedia->wUnitX,
						GetStringSplitChar(),
						lpFormMedia->wUnitY,
						GetStringSplitChar(),
						lpFormMedia->wSizeWidth,
						GetStringSplitChar(),
						lpFormMedia->wSizeHeight,
						GetStringSplitChar(),
						lpFormMedia->wCheckAreaX,
						GetStringSplitChar(),
						lpFormMedia->wCheckAreaY,
						GetStringSplitChar(),
						lpFormMedia->wCheckAreaWidth,
						GetStringSplitChar(),
						lpFormMedia->wCheckAreaHeight,
						GetStringSplitChar(),
						lpFormMedia->wRestrictedAreaX,
						GetStringSplitChar(),
						lpFormMedia->wRestrictedAreaY,
						GetStringSplitChar(),
						lpFormMedia->wRestrictedAreaWidth,
						GetStringSplitChar(),
						lpFormMedia->wRestrictedAreaHeight);

	WFSFreeResult(lpResult);

	if ("" != strWfsResult)
	{
		CString strTrace(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						WFS_GETINFO_COMPLETE, GetXFSMsgStr(WFS_GETINFO_COMPLETE).c_str(), strWfsResult.c_str());
		WriteTrace(OCXGetInfo, strTrace);
		
		FireDCEvent(WFS_GETINFO_COMPLETE, strWfsResult);

		return WFS_SUCCESS;
	}
	
	return hResult;
}

HRESULT CDCScanner_30::CMD_CHK_PROCESS_FORM(	LPCTSTR strFormName, 
														LPCTSTR strMediaName,
														LPCTSTR strInputFields,
														LPCTSTR strOutputFields,
														LPCTSTR strUNICODEOutputFields,
														DWORD dwOptions) 
{
	HRESULT hResult = DC_ERROR;

	WFSCHKINPROCESSFORM ProcessForm = {0};
	ProcessForm.lpszFormName = (LPTSTR)strFormName;
	ProcessForm.lpszMediaName = NULL;
	if (strlen(strMediaName) > 0)
	{
		ProcessForm.lpszMediaName = (LPTSTR)strMediaName;
	}

	ProcessForm.lpszInputFields = NULL;
	if (strlen(strInputFields) > 0)
	{
		int nBufSize = strlen(strInputFields) + 4;
		ProcessForm.lpszInputFields = new CHAR[nBufSize];
		memset(ProcessForm.lpszInputFields, 0, nBufSize * sizeof(CHAR));

		strcpy(ProcessForm.lpszInputFields, strInputFields);
		FormatAsciiField(ProcessForm.lpszInputFields);
	}

	ProcessForm.lpszOutputFields = NULL;
	ProcessForm.lpszUNICODEOutputFields = NULL;
	if (strlen(strOutputFields) > 0)
	{
		int nBufSize = strlen(strOutputFields) + 4;
		ProcessForm.lpszOutputFields = new CHAR[nBufSize];
		memset(ProcessForm.lpszOutputFields, 0, nBufSize * sizeof(CHAR));

		strcpy(ProcessForm.lpszOutputFields, strOutputFields);
		FormatAsciiField(ProcessForm.lpszOutputFields);
	}
	else if (strlen(strUNICODEOutputFields) > 0)
	{
		int nBufSize = strlen(strUNICODEOutputFields) * 2 + 4;
		ProcessForm.lpszUNICODEOutputFields = new WCHAR[nBufSize];
		memset(ProcessForm.lpszUNICODEOutputFields, 0, nBufSize * sizeof(WCHAR));

		// ascii ת widechar
		size_t sSize = strlen(strUNICODEOutputFields);
		wchar_t * lpszUNICODEOutputFields = NULL;
		int dSize = mbstowcs(lpszUNICODEOutputFields, strUNICODEOutputFields, 0) + 1;
		lpszUNICODEOutputFields = new wchar_t[dSize];
		wmemset(lpszUNICODEOutputFields, 0, dSize);
		int nRet = mbstowcs(lpszUNICODEOutputFields, strUNICODEOutputFields, sSize);

		wcscpy(ProcessForm.lpszUNICODEOutputFields, lpszUNICODEOutputFields);
		FormatUnicodeField(ProcessForm.lpszUNICODEOutputFields);

		delete[] lpszUNICODEOutputFields;
	}
	
	ProcessForm.dwOptions = dwOptions;

	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_CHK_PROCESS_FORM,
								&ProcessForm,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);

	if (NULL != ProcessForm.lpszInputFields)
	{
		delete[] ProcessForm.lpszInputFields;
		ProcessForm.lpszInputFields = NULL;
	}

	if (NULL != ProcessForm.lpszOutputFields)
	{
		delete[] ProcessForm.lpszOutputFields;
		ProcessForm.lpszOutputFields = NULL;
	}

	if (NULL != ProcessForm.lpszUNICODEOutputFields)
	{
		delete[] ProcessForm.lpszUNICODEOutputFields;
		ProcessForm.lpszUNICODEOutputFields = NULL;
	}

	return hResult;
}

HRESULT CDCScanner_30::CMD_CHK_RESET(long lResetIn) 
{
	HRESULT hResult = DC_ERROR;

	WORD wResetIn = (WORD)lResetIn;
	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_CHK_RESET,
								&wResetIn,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);

	return hResult;
}

HRESULT CDCScanner_30::CMD_CHK_SET_GUIDANCE_LIGHT(long lGuidLight, long lCommand) 
{
	HRESULT hResult = DC_ERROR;

	WFSCHKSETGUIDLIGHT SetGuidLight = {0};
	SetGuidLight.wGuidLight = (WORD)lGuidLight;
	SetGuidLight.dwCommand = (WORD)lCommand;

	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_CHK_SET_GUIDANCE_LIGHT,
								&SetGuidLight,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);

	return hResult;
}

short CDCScanner_30::FormatAsciiField(char * szFieldValues)
{
	if (NULL == szFieldValues)
	{
		return (short)DC_ERROR;
	}

	char * szMatchStr = ";";
	char * p = strtok(szFieldValues, szMatchStr);
	while (NULL != p)
	{
		p = strtok(NULL, szMatchStr);
	}

	return WFS_SUCCESS;
}

short CDCScanner_30::FormatUnicodeField(wchar_t * wszFieldValues)
{
	if (NULL == wszFieldValues)
	{
		return (short)DC_ERROR;
	}

	wchar_t * wszMatchStr = L",";
	wchar_t * p = NULL;
	wcstok(wszFieldValues, wszMatchStr, &p);
	while (NULL != p)
	{
		wcstok(NULL, wszMatchStr, &p);
	}
	return WFS_SUCCESS;
}

HRESULT CDCScanner_30::CMD_CHK_POWER_SAVE_CONTROL(long lMaxPowerSaveRecoveryTime) 
{
	HRESULT hResult = DC_ERROR;

	WFSCHKPOWERSAVECONTROL PowerSaveControl = {0};
	PowerSaveControl.usMaxPowerSaveRecoveryTime = (USHORT)lMaxPowerSaveRecoveryTime;

	hResult = WFSAsyncExecute(	m_DCObject.m_hService,
								WFS_CMD_CHK_POWER_SAVE_CONTROL,
								&PowerSaveControl,
								WFS_INDEFINITE_WAIT,
								NULL, // m_Ctrl.m_hWnd,
								&m_RequestID);

	return hResult;
}

int CDCScanner_30::OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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
            lpWfsRet=(LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);			
			break;
        case WFS_CLOSE_COMPLETE:
            lpWfsRet=(LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);			
			break;
        case WFS_LOCK_COMPLETE:
            lpWfsRet=(LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);			
			break;
        case WFS_UNLOCK_COMPLETE:
            lpWfsRet=(LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);			
			break;
        case WFS_REGISTER_COMPLETE:
            lpWfsRet=(LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);			
			break;
        case WFS_DEREGISTER_COMPLETE:
            lpWfsRet=(LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);			
			break;
        case WFS_GETINFO_COMPLETE:
            lpWfsRet = (LPWFSRESULT)lParam;
			WFSFreeResult(lpWfsRet);			
			break;
		case WFS_EXECUTE_COMPLETE:
			lpWfsRet = (LPWFSRESULT)lParam;
			strWfsResult = HandleCmdResult(lpWfsRet);
			WFSFreeResult(lpWfsRet);
			break;
        case WFS_EXECUTE_EVENT:
            lpWfsRet = (LPWFSRESULT)lParam;
			strWfsResult = HandleEXEEvtResult(lpWfsRet);
			WFSFreeResult(lpWfsRet);			
			break;
        case WFS_SERVICE_EVENT:
			lpWfsRet = (LPWFSRESULT)lParam;
			strWfsResult = HandleSRVEvtResult(lpWfsRet);
			WFSFreeResult(lpWfsRet);
			break ;
        case WFS_USER_EVENT:
			lpWfsRet = (LPWFSRESULT)lParam;
			strWfsResult = HandleUSEREvtResult(lpWfsRet);
			WFSFreeResult(lpWfsRet);			
			break;
		case WFS_SYSTEM_EVENT:
			lpWfsRet = (LPWFSRESULT)lParam;
			strWfsResult = HandleSysEvtResult(lpWfsRet);
			WFSFreeResult(lpWfsRet);
			break;
        case WFS_TIMER_EVENT:
			break;
         default:
            break;
    }

    if ("" != strWfsResult)
	{
		CString strTrace(strWfsResult.length() + 256, 0);
		sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s", 
						uMsg, GetXFSMsgStr(uMsg).c_str(), strWfsResult.c_str());
		WriteTrace(OCXEVENT, strTrace);
		
		FireDCEvent(uMsg, strWfsResult);
	}

    return 0L;
}
