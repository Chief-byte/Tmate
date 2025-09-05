#ifndef CUTILS_H
#define CUTILS_H

#include "../stdafx.h"

#ifdef PROTOCOL_PISA
#include "../DC/PISA/include/lfsapi.h"
#else
#include "../DC/LFS/include/lfsapi.h"
#endif

class CUtils
{
public:
	CUtils();
	~CUtils();

public:
/*  *  得到系统时间,格式为 *  YYYYMMDDhhmmss */
	void  GetSysTime(PCHAR,PCHAR);
/* * 设置系统的时间 */
	void  SetSysTime(PCHAR,PCHAR);
	
	BYTE  HextoBcd(BYTE Hex);
	VOID  HextoBcd(SHORT Hex, PBYTE pBcd);
	VOID  StrtoBcd(PCHAR pch, PBYTE pBcd);
	VOID  BcdtoStr(PBYTE pBcd, SHORT sLen, PCHAR pch);
	SHORT BcdtoShort(BYTE bBcd);
	void  StrtoHex(PCHAR pch, PBYTE pbHex);
	void  HextoStr(PBYTE pbHex, int sLen, PCHAR pch);

	/*
	 * 分解字符串到字符串数组
	 */
	static int SplitString(CStringArray & strarr, LPSTR str, LPCSTR sep);
};
#endif