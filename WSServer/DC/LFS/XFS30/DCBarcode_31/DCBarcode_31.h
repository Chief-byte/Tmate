// DCBarcode_XFS31.h: interface for the CDCBarcode_31 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCBARCODE_31_H__INCLUDED_)
#define AFX_DCBARCODE_31_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DC_30.h"
#include "../../DC/DC.h"
#include "../../XFS320/Include/XFSBCR.H"

class CDCBarcode_31 : public CDC_30
{
public:
	CDCBarcode_31(LPCTSTR strDCName);
	virtual ~CDCBarcode_31();

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
	HRESULT INF_BCR_STATUS();
	HRESULT INF_BCR_CAPABILITIES();

	// √¸¡Ó÷¥––
	HRESULT CMD_BCR_READ(LPCTSTR lpszSymbologies);
	HRESULT CMD_BCR_SET_GUIDANCE_LIGHT(long lGuidLight, long lCommand);
	HRESULT CMD_BCR_RESET();
	HRESULT CMD_BCR_POWER_SAVE_CONTROL(long lMaxPowerSaveRecoveryTime);
};

#endif // !defined(AFX_DCBARCODE_31_H__INCLUDED_)
