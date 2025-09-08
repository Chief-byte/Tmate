// JavaScriptStringParam.cpp: implementation of the CJSStringParam class.
//
//////////////////////////////////////////////////////////////////////

#include "JavaScriptStringParam.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJSStringParam::CJSStringParam()
{

}

CJSStringParam::~CJSStringParam()
{

}

/*
 * ��ȡӦ�ô��ݵ�����������ֵ����ʽΪKey=Value;Key=Value;Key=Value ...
 *
 */
BOOL CJSStringParam::GetStringParams(LPCTSTR strParams, LPCTSTR strSplitString, CStringArray & strarrParams)
{
	// strarrParams.RemoveAll();
	strarrParams.clear();

	CUtils::SplitString(strarrParams, (LPTSTR)strParams, strSplitString);

	return TRUE;
}

/*
 * ��ȡӦ�ô��ݵ�����������ֵ����ʽΪKey=Value;Key=Value;Key=Value ...
 *
 */
BOOL CJSStringParam::GetStringParam(CStringArray & strarrParams, LPCTSTR strKey, CString & strValue)
{
	list<string>::iterator iter;
	for (iter = strarrParams.begin(); iter != strarrParams.end(); iter++)
	{
		if (0 == stricmp((*iter).substr(0, strlen(strKey) + 1).c_str(), (CString(strKey) + "=").c_str()))
		{
			strValue = (*iter).substr((strlen(strKey) + 1), strlen((*iter).c_str()) - (strlen(strKey) + 1));
			return TRUE;
		}
	}

	return FALSE;
}

/*
 * ��ȡӦ�ô��ݵ�����������ֵ����ʽΪKey=Value;Key=Value;Key=Value ...
 *
 */
CString CJSStringParam::GetStringParam(CStringArray & strarrParams, LPCTSTR strKey)
{
	CString strValue;
	if (FALSE == GetStringParam(strarrParams, strKey, strValue))
	{
		return "";
	}

	return strValue;
}

