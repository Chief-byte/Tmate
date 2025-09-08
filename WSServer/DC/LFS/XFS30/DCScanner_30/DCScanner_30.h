// DCScanner_XFS30.h: interface for the CDCScanner_30 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCSCANNER_30_H__INCLUDED_)
#define AFX_DCSCANNER_30_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DC_30.h"
#include "../../DC/DC.h"
#include "../../XFS320/Include/XFSCHK.H"

class CDCScanner_30 : public CDC_30
{
public:
	CDCScanner_30(LPCTSTR strDCName);
	virtual ~CDCScanner_30();

public:
	CString HandleCmdErr(LPWFSRESULT lpWfsRet);
	CString HandleEXEEvtResult(LPWFSRESULT lpWfsRet);
	CString HandleUSEREvtResult(LPWFSRESULT lpWfsRet);
	CString HandleSRVEvtResult(LPWFSRESULT lpWfsRet);
	CString HandleSysEvtResult(LPWFSRESULT lpWfsRet);
	CString HandleCmdResult(LPWFSRESULT lpWfsRet);
	CString HandleInfResult(LPLFSRESULT lpWfsRet);

private:
	virtual CString GetXFSErrStr(HRESULT hResult);
	virtual CString GetXFSMsgStr(DWORD dwEventID);
	virtual CString GetXFSSysEvtStr(DWORD dwEventID);
	virtual CString GetXFSCmdStr(DWORD dwCmdCode);

public:
	virtual int OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual HRESULT _CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid);

public:
	HRESULT INF_CHK_STATUS();
	HRESULT INF_CHK_CAPABILITIES();
	HRESULT INF_CHK_FORM_LIST();
	HRESULT INF_CHK_MEDIA_LIST();
	HRESULT INF_CHK_QUERY_FORM(LPCTSTR strFormName);
	HRESULT INF_CHK_QUERY_MEDIA(LPCTSTR strMediaName);
	HRESULT INF_CHK_QUERY_FIELD(LPCTSTR strFormName, LPCTSTR strFieldName);

	HRESULT CMD_CHK_PROCESS_FORM(	LPCTSTR strFormName, 
												LPCTSTR strMediaName,
												LPCTSTR strInputFields,
												LPCTSTR strOutputFields,
												LPCTSTR strUNICODEOutputFields,
												DWORD dwOptions);
	HRESULT CMD_CHK_RESET(long lResetIn);
	HRESULT CMD_CHK_SET_GUIDANCE_LIGHT(long lGuidLight, long lCommand);
	HRESULT CMD_CHK_POWER_SAVE_CONTROL(long lMaxPowerSaveRecoveryTime);

private:
	short FormatAsciiField(char * szFieldValues);
	short FormatUnicodeField(wchar_t * wszFieldValues);
};

#endif // !defined(AFX_DCSCANNER_30_H__INCLUDED_)
