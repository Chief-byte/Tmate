// DCCardDispenser_XFS31.h: interface for the CDCCardDispenser_31 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCCARDDISPENSER_31_H__INCLUDED_)
#define AFX_DCCARDDISPENSER_31_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DC_30.h"
#include "../../DC/DC.h"
#include "../../XFS320/Include/XFSCRD.H"

class CDCCardDispenser_31 : public CDC_30
{
public:
	CDCCardDispenser_31(LPCTSTR strDCName);
	virtual ~CDCCardDispenser_31();

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
	HRESULT INF_CRD_STATUS();
	HRESULT INF_CRD_CAPABILITIES();
	HRESULT INF_CRD_CARD_UNIT_INFO(LPVOID * lppResult = NULL);
	
	// √¸¡Ó÷¥––
	HRESULT CMD_CRD_EJECT_CARD();
	HRESULT CMD_CRD_RETAIN_CARD(long lNumber);
	HRESULT CMD_CRD_RESET(long lResetIn);
	HRESULT CMD_CRD_DISPENSE_CARD(long lNumber, BOOL bPresent);
	HRESULT CMD_CRD_SET_CARD_UNIT_INFO(LPCTSTR strCUInfo);
};

#endif // !defined(AFX_DCCARDDISPENSER_31_H__INCLUDED_)
