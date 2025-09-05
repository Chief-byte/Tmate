// DCCamera_31.h: interface for the CDCCamera_31 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCCAMERA_XFS31_H__INCLUDED_)
#define AFX_DCCAMERA_XFS31_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DC_30.h"
#include "../../../DC/DC.h"
#include "../../include/lfscam.h"

class CDCCamera_31 : public CDC_30  
{	
public:
	CDCCamera_31(LPCTSTR strDCName, LPCTSTR strTraceComponent);
	virtual ~CDCCamera_31();

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
	HRESULT INF_CAM_STATUS();
	HRESULT INF_CAM_CAPABILITIES();
	
	// √¸¡Ó÷¥––
	HRESULT CMD_CAM_TAKE_PICTURE(long lCamera, LPCTSTR lpszCamData, LPCTSTR lpszUNICODECamData, LPCTSTR lpszFilePath, long lScanSize);
	HRESULT CMD_CAM_RESET();
	HRESULT CMD_CAM_DISPLAY(long lCamera, long lAction, long lX, long lY, long lWidth, long lHeight);
};

#endif // !defined(AFX_DCCAMERA_XFS31_H__INCLUDED_)
