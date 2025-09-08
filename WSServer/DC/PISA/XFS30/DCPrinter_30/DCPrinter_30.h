// DCPrinter_XFS30.h: interface for the CDCPrinter_30 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DCPRINTER_30_H__INCLUDED_)
#define AFX_DCPRINTER_30_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../DC_30.h"
#include "../../../DC/DC.h"
#include "../../include/lfsptr.h"
#include "../../../../stdafx.h"

class CDCPrinter_30 : public CDC_30
{
public:
	CDCPrinter_30(LPCTSTR strDCName, LPCTSTR strTraceComponent);
	virtual ~CDCPrinter_30();

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
	HRESULT INF_PTR_STATUS();
	HRESULT INF_PTR_CAPABILITIES();
	HRESULT INF_PTR_FORM_LIST();
	HRESULT INF_PTR_MEDIA_LIST();
	HRESULT INF_PTR_QUERY_FORM(LPCTSTR strFormName);
	HRESULT INF_PTR_QUERY_MEDIA(LPCTSTR strMediaName);
	HRESULT INF_PTR_QUERY_FIELD(LPCTSTR strFormName, LPCTSTR strFieldName);

	HRESULT CMD_PTR_CONTROL_MEDIA(long lMediaControl);
	HRESULT CMD_PTR_PRINT_FORM(	LPCTSTR strFormName, 
										LPCTSTR strMediaName, 
										LPCTSTR strFields, 
										LPCTSTR strUNICODEFields,
										long lAlignment,
										long lOffsetX,
										long lOffsetY,
										long lMediaControl,
										long lResolution,
										long lPaperSource);
	HRESULT CMD_PTR_READ_FORM(LPCTSTR strFormName, LPCTSTR strFieldNames, LPCTSTR strMediaName, long lMediaControl);
	HRESULT CMD_PTR_RAW_DATA(LPCTSTR strContent);
	HRESULT CMD_PTR_MEDIA_EXTENTS(long lBase, long lUnitX, long lUnitY);
	HRESULT CMD_PTR_RESET_COUNT();
	HRESULT CMD_PTR_READ_IMAGE(	long lFrontImageType,
										long lBackImageType,
										long lFrontImageColorFormat,
										long lBackImageColorFormat,
										long lCodelineFormat,
										long lImageSource,
										LPCTSTR strFrontImageFile,
										LPCTSTR strBackImageFile);
	HRESULT CMD_PTR_RESET(long lMediaControl, long lRetractBinNumber);
	HRESULT CMD_PTR_RETRACT_MEDIA(long lBinNumber);
	HRESULT CMD_PTR_DISPENSE_PAPER(long lPaperSource);

private:
	short FormatAsciiField(char * szFieldValues);
	short FormatUnicodeField(wchar_t * wszFieldValues);
};

#endif // !defined(AFX_DCPRINTER_30_H__INCLUDED_)
