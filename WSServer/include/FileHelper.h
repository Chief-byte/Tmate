// FileHelper.h: interface for the CFileHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEHELPER_H__2AFFF4AF_1DDC_47CF_94FB_1CD5996034B4__INCLUDED_)
#define AFX_FILEHELPER_H__2AFFF4AF_1DDC_47CF_94FB_1CD5996034B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

//##ModelId=48C7876C00EA
class CFileHelper
{
public:
	//##ModelId=48C7876C00EB
	static bool Base64Str2File(const char * strFilePath, const char * strBase64);
	//##ModelId=48C7876C00EF
	static std::string File2Base64Str(const char * strFilePath);
	static std::string File2Base64StrWithSkip(const char * strFilePath, long nSkipLength);
	//##ModelId=48C7876C00F2
	static bool WriteFile_Cover(const char * strFilePath, const char * strData);
	//##ModelId=48C7876C00FC
	static bool WriteFile_Append(const char * strFilePath, const char * strData);

	static std::string File2String(const char * strFilePath);
	static std::string File2StringMaxLen(const char * strFilePath, int nMaxLen);
	static bool String2File(const char * strFilePath, const char * strString, bool bAppend);
	static bool MakeDirectory(const char * strFileFullPath);
	//##ModelId=48C7876C0104
	CFileHelper();
	//##ModelId=48C7876C0105
	virtual ~CFileHelper();
};

#endif // !defined(AFX_FILEHELPER_H__2AFFF4AF_1DDC_47CF_94FB_1CD5996034B4__INCLUDED_)
