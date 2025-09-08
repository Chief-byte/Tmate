#ifndef CUTILS_H
#define CUTILS_H

#include "stdafx.h"

#ifdef PROTOCOL_PISA
#include "lfsapi.h"
#else
#include "lfsapi.h"
#endif

class CUtils
{
public:
	CUtils();
	~CUtils();

public:
/*  *  �õ�ϵͳʱ��,��ʽΪ *  YYYYMMDDhhmmss */
	void  GetSysTime(PCHAR,PCHAR);
/* * ����ϵͳ��ʱ�� */
	void  SetSysTime(PCHAR,PCHAR);
	
	BYTE  HextoBcd(BYTE Hex);
	VOID  HextoBcd(SHORT Hex, PBYTE pBcd);
	VOID  StrtoBcd(PCHAR pch, PBYTE pBcd);
	VOID  BcdtoStr(PBYTE pBcd, SHORT sLen, PCHAR pch);
	SHORT BcdtoShort(BYTE bBcd);
	void  StrtoHex(PCHAR pch, PBYTE pbHex);
	void  HextoStr(PBYTE pbHex, int sLen, PCHAR pch);

	/*
	 * �ֽ��ַ������ַ�������
	 */
	static int SplitString(CStringArray & strarr, LPSTR str, LPCSTR sep);
};
#endif