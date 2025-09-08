// DCCashDispenser_XFS30.h: interface for the CDCCashDispenser_30 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCCASHDISPENSER_30_H__INCLUDED_)
#define AFX_DCCASHDISPENSER_30_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DC_30.h"
#include "../../../DC/DC.h"
#include "../../include/lfscdm.h"
#include "../../../../stdafx.h"

class CDCCashDispenser_30 : public CDC_30
{
public:
	CDCCashDispenser_30(LPCTSTR strDCName, LPCTSTR strTraceComponent);
	virtual ~CDCCashDispenser_30();

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
	HRESULT INF_CDM_CAPABILITIES();
	HRESULT INF_CDM_CASH_UNIT_INFO();
	HRESULT INF_CDM_CURRENCY_EXP();
	HRESULT INF_CDM_MIX_TABLE();
	HRESULT INF_CDM_MIX_TYPES();
	HRESULT INF_CDM_STATUS();
	HRESULT INF_CDM_PRESENT_STATUS(long lPosition);

	HRESULT CMD_CDM_CLOSE_SHUTTER(long lPosition);
	HRESULT CMD_CDM_COUNT(LPCTSTR strPhysicalLocation, long lPosition);
	HRESULT CMD_CDM_DENOMINATE(long lAmount, LPCTSTR strCurrency, long lMixAlgorithm);
	HRESULT CMD_CDM_DISPENSE(long lAmount, LPCTSTR strCurrency, long lMixAlgorithm, long lPosition, BOOL bPresent);
	HRESULT CMD_CDM_END_EXCHANGE(LPCTSTR strExchangeCounts);
	HRESULT CMD_CDM_OPEN_SHUTTER(long lPosition);
	HRESULT CMD_CDM_PRESENT(long lPosition);
	HRESULT CMD_CDM_REJECT();
	HRESULT CMD_CDM_RESET(long lResetInNumber, long lRetractArea, long lRetractIndex, long lPosition);
	HRESULT CMD_CDM_RETRACT(long lRetractArea, long lRetractIndex, long lPosition);
	HRESULT CMD_CDM_START_EXCHANGE(LPCTSTR strStartEx);
	HRESULT CMD_CDM_TEST_CASH_UNITS(long lNumber, long lRetractArea, long lRetractIndex, long lPosition);

private:
	BOOL m_bCashUnitInfo4EndExchange;
	LPLFSRESULT m_lpResult4EndExchange;
};

#endif // !defined(AFX_DCCASHDISPENSER_30_H__INCLUDED_)
