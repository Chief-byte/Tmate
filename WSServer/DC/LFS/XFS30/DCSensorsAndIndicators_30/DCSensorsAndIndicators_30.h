// DCSensorsAndIndicators_XFS30.h: interface for the CDCSensorsAndIndicators_30 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCSENSORSANDINDICATORS_30_H__INCLUDED_)
#define AFX_DCSENSORSANDINDICATORS_30_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DC_30.h"
#include "../../../DC/DC.h"
#include "../../include/lfssiu.h"
#include "../../../../stdafx.h"

class CDCSensorsAndIndicators_30 : public CDC_30 
{
public:
	CDCSensorsAndIndicators_30(LPCTSTR strDCName, LPCTSTR strTraceComponent);
	virtual ~CDCSensorsAndIndicators_30();

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
	HRESULT INF_SIU_CAPABILITIES();
	HRESULT INF_SIU_STATUS();

	// √¸¡Ó÷¥––
	HRESULT CMD_SIU_ENABLE_EVENTS(LPCTSTR strEnable);
	HRESULT CMD_SIU_SET_AUXILIARY(long lAuxiliary, long lCommand);
	HRESULT CMD_SIU_SET_DOOR(long lDoor, long lCommand);
	HRESULT CMD_SIU_SET_GUIDLIGHT(long lGuidLight, long lCommand);
	HRESULT CMD_SIU_SET_INDICATOR(long lIndicator, long lCommand);
	HRESULT CMD_SIU_SET_PORTS(LPCTSTR strSetPorts);
	HRESULT CMD_SIU_RESET();
};

#endif // !defined(AFX_DCSENSORSANDINDICATORS_30_H__INCLUDED_)
