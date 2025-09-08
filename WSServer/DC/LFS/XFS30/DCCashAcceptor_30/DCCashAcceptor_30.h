// DCCashAcceptor_XFS30.h: interface for the CDCCashAcceptor_30 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCCASHACCEPTOR_30_H__INCLUDED_)
#define AFX_DCCASHACCEPTOR_30_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DC_30.h"
#include "DC.h"
#include "lfscim.h"

class CDCCashAcceptor_30 : public CDC_30
{
public:
	CDCCashAcceptor_30(LPCTSTR strDCName, LPCTSTR strTraceComponent);
	virtual ~CDCCashAcceptor_30();

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
	HRESULT INF_CIM_STATUS();
	HRESULT INF_CIM_CAPABILITIES();
	HRESULT INF_CIM_CASH_UNIT_INFO();
	HRESULT INF_CIM_TELLER_INFO();  // ��δʵ��
	HRESULT INF_CIM_CURRENCY_EXP();
	HRESULT INF_CIM_BANKNOTE_TYPES();
	HRESULT INF_CIM_CASH_IN_STATUS();
	HRESULT INF_CIM_GET_P6_INFO();  // ��δʵ��
	HRESULT INF_CIM_GET_P6_SIGNATURE();  // ��δʵ��

	HRESULT CMD_CIM_CASH_IN_START(long lInputPosition, long lOutputPosition, long lUseRecycleUnits);
	HRESULT CMD_CIM_CASH_IN();
	HRESULT CMD_CIM_CASH_IN_END();
	HRESULT CMD_CIM_CASH_IN_ROLLBACK();
	HRESULT CMD_CIM_RETRACT(long lRetractArea, long lRetractIndex, long lRetractPosition);
	HRESULT CMD_CIM_OPEN_SHUTTER(long lPosition);
	HRESULT CMD_CIM_CLOSE_SHUTTER(long lPosition);
	HRESULT CMD_CIM_SET_TELLER_INFO(LPCTSTR strTellerUpdate);
	HRESULT CMD_CIM_SET_CASH_UNIT_INFO(LPCTSTR strCUInfo);
	HRESULT CMD_CIM_START_EXCHANGE(LPCTSTR strStartEx);
	HRESULT CMD_CIM_END_EXCHANGE(LPCTSTR strCUInfo);
	HRESULT CMD_CIM_OPEN_SAFE_DOOR();
	HRESULT CMD_CIM_RESET(long lNumber, long lResetPosition, long lRetractArea, long lRetractIndex, long lRetractPosition);
	HRESULT CMD_CIM_CONFIGURE_CASH_IN_UNITS(LPCTSTR strCashInType);
	HRESULT CMD_CIM_CONFIGURE_NOTETYPES(LPCTSTR strNoteIDs);
	HRESULT CMD_CIM_CREATE_P6_SIGNATURE();

private:
	CString GetCashInResultString(LPLFSCIMCASHIN lpCashIn);
	CString GetCashInfoResultString(LPLFSCIMCASHINFO lpCashInfo);

private:
	BOOL m_bCashUnitInfo4EndExchange;
	LPLFSRESULT m_lpResult4EndExchange;
};

#endif // !defined(AFX_DCCASHACCEPTOR_30_H__INCLUDED_)
