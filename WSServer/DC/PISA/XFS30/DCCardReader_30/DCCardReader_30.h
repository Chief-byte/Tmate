// DCCardReader.h: interface for the CDCCardReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCCARDREADER_30_H__INCLUDED_)
#define AFX_DCCARDREADER_30_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DC_30.h"
#include "../../../DC/DC.h"
#include "../../include/lfsidc.h"
#include "../../../../stdafx.h"

class CDCCardReader_30 : public CDC_30
{
public:
	CDCCardReader_30(LPCTSTR strDCName, LPCTSTR strTraceComponent);
	virtual ~CDCCardReader_30();

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
	HRESULT INF_IDC_STATUS();
	HRESULT INF_IDC_CAPABILITIES();

	HRESULT CMD_IDC_EJECT_CARD();
	HRESULT CMD_IDC_RETAIN_CARD();
	HRESULT CMD_IDC_RESET_COUNT();
	HRESULT CMD_IDC_READ_RAW_DATA(long lReadData);
	HRESULT CMD_IDC_CHIP_IO(long lProtocol, LPCTSTR strBytesHex);
	HRESULT CMD_IDC_WRITE_RAW_DATA(long lDataSource, LPCTSTR strTrackData, long lWriteMode);
	HRESULT CMD_IDC_RESET(long lResetIn);
	HRESULT CMD_IDC_CHIP_POWER(long lChipPower);
};

#endif // !defined(AFX_DCCARDREADER_30_H__INCLUDED_)
