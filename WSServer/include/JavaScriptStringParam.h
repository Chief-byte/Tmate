// JavaScriptStringParam.h: interface for the CJSStringParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JAVASCRIPTSTRINGPARAM_H__1B273555_96F9_45DE_B717_4187269C0BB9__INCLUDED_)
#define AFX_JAVASCRIPTSTRINGPARAM_H__1B273555_96F9_45DE_B717_4187269C0BB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../stdafx.h"

#ifdef PROTOCOL_PISA
#include "../DC/PISA/include/lfsapi.h"
#else
#include "../DC/LFS/include/lfsapi.h"
#endif


class CJSStringParam  
{
public:
	CJSStringParam();
	virtual ~CJSStringParam();

public:
	/*
	 * 获取应用传递的字符串参数值，格式为Key=Value;Key=Value;Key=Value ...
	 *
	 */
	static BOOL GetStringParams(LPCTSTR strParams, LPCTSTR strSplitString, CStringArray & strarrParams);

	/*
	 * 获取应用传递的字符串参数值，格式为Key=Value;Key=Value;Key=Value ...
	 *
	 */
	static BOOL GetStringParam(CStringArray & strarrParams, LPCTSTR strKey, CString & strValue);

	/*
	 * 获取应用传递的字符串参数值，格式为Key=Value;Key=Value;Key=Value ...
	 *
	 */
	static CString GetStringParam(CStringArray & strarrParams, LPCTSTR strKey);
};

#endif // !defined(AFX_JAVASCRIPTSTRINGPARAM_H__1B273555_96F9_45DE_B717_4187269C0BB9__INCLUDED_)
