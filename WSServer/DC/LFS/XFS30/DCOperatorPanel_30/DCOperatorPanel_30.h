// DCOperatorPanel_XFS30.h: interface for the CDCOperatorPanel_30 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCOPERATORPANEL_30_H__INCLUDED_)
#define AFX_DCOPERATORPANEL_30_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DC_30.h"
#include "../../DC/DC.h"
#include "lfsttu.h"

class CDCOperatorPanel_30 : public CDC_30
{
public:
	CDCOperatorPanel_30(LPCTSTR strDCName, LPCTSTR strTraceComponent);
	virtual ~CDCOperatorPanel_30();

public:
	CString HandleCmdErr(LPLFSRESULT lpWfsRet);
	CString HandleEXEEvtResult(LPLFSRESULT lpWfsRet);
	CString HandleUSEREvtResult(LPLFSRESULT lpWfsRet);
	CString HandleSRVEvtResult(LPLFSRESULT lpWfsRet);
	CString HandleSysEvtResult(LPLFSRESULT lpWfsRet);
	CString HandleCmdResult(LPLFSRESULT lpWfsRet);
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
	HRESULT INF_TTU_STATUS();
	HRESULT INF_TTU_CAPABILITIES();
	HRESULT INF_TTU_FORM_LIST();
	HRESULT INF_TTU_QUERY_FORM(LPCTSTR strFormName);
	HRESULT INF_TTU_QUERY_FIELD(LPCTSTR strFormName, LPCTSTR strFieldName);
	HRESULT INF_TTU_KEY_DETAIL();

	HRESULT CMD_TTU_BEEP(long lBeep);
	HRESULT CMD_TTU_CLEARSCREEN(long lPositionX, long lPositionY, long lWidth, long lHeight);
	HRESULT CMD_TTU_DISPLIGHT(long lMode);
	HRESULT CMD_TTU_SET_LED(long lLED, long lCommand);
	HRESULT CMD_TTU_SET_RESOLUTION(long lSizeX, long lSizeY);
	HRESULT CMD_TTU_WRITE_FORM(LPCTSTR strFormName, long lClearScreen, LPCTSTR strFields, LPCTSTR strUNICODEFields);
	HRESULT CMD_TTU_READ_FORM(LPCTSTR strFormName, LPCTSTR strFieldNames);
	HRESULT CMD_TTU_WRITE(long lMode, long lPosX, long lPosY, long lTextAttr, LPCTSTR strText, LPCTSTR strUNICODEText);
	HRESULT CMD_TTU_READ(	long lNumOfChars, 
										long lMode, 
										long lPosX, 
										long lPosY, 
										long lEchoMode, 
										long lEchoAttr, 
										long lCursor, 
										long lFlush, 
										long lAutoEnd, 
										LPCTSTR strActiveKeys, 
										LPCTSTR strActiveUNICODEKeys, 
										LPCTSTR strActiveCommandKeys, 
										LPCTSTR strTerminateCommandKeys);
	HRESULT CMD_TTU_RESET();

};

#endif // !defined(AFX_DCOPERATORPANEL_30_H__INCLUDED_)
