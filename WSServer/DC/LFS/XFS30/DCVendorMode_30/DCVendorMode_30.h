// DCVendorMode_XFS30.h: interface for the CDCVendorMode_30 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCVENDORMODE_30_H__INCLUDED_)
#define AFX_DCVENDORMODE_30_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DC_30.h"
#include "../../../DC/DC.h"
#include "../../include/lfsvdm.h"
#include "../../../../stdafx.h"

class CDCVendorMode_30 : public CDC_30
{
public:
	CDCVendorMode_30(LPCTSTR strDCName, LPCTSTR strTraceComponent);
	virtual ~CDCVendorMode_30();

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
	HRESULT INF_VDM_CAPABILITIES();
	HRESULT INF_VDM_STATUS();

	HRESULT CMD_VDM_ENTER_MODE_REQ();
	HRESULT CMD_VDM_ENTER_MODE_ACK();
	HRESULT CMD_VDM_EXIT_MODE_REQ();
	HRESULT CMD_VDM_EXIT_MODE_ACK();
};

#endif // !defined(AFX_DCVENDORMODE_30_H__INCLUDED_)
