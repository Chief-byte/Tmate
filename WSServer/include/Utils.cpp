/* 
 * ���ļ����ͨ�ù��ߺ���
 * ������CUtils��װ���еĴ�����
 */

#include "Utils.h"
#include <time.h>
#include <sys/time.h>

CUtils::CUtils()
{
}

CUtils::~CUtils()
{
}

/* 
 *  �õ�ϵͳʱ��,��ʽΪ
 *  YYYYMMDDhhmmss
 */
void CUtils::GetSysTime(PCHAR pchDate,PCHAR pchTime)
{
	time_t t;
	t = time(NULL);
	struct tm *n = localtime(&t);
	char strDate[60] = {0};
	sprintf(strDate, "%04d%02d%02d%02d%02d%02d", n->tm_year + 1900, n->tm_mon + 1, n->tm_mday, n->tm_hour, n->tm_min, n->tm_sec);

	memcpy(pchDate, strDate, 8);
	pchDate[8] = 0;
	memcpy(pchTime, strDate + 8, 6);
	pchTime[6] = 0;
}


/*
 * ����ϵͳ��ʱ��
 */
void CUtils::SetSysTime(PCHAR pchDate,PCHAR pchTime)
{
    SYSTEMTIME SysTm;
	int nYear,nMonth,nDay,nHour,nMin,nSec;
	char tmp[5];

	memcpy(tmp,pchDate ,4);
	tmp[4]=0;
	nYear = atoi(tmp);
	memcpy(tmp,pchDate+4 ,2);
	tmp[2]=0;
	nMonth = atoi(tmp);

	memcpy(tmp,pchDate+6 ,2);
	tmp[2]=0;
	nDay = atoi(tmp);
	
	memcpy(tmp,pchTime ,2);
	tmp[2]=0;
	nHour = atoi(tmp);

	memcpy(tmp,pchTime+2 ,2);
	tmp[2]=0;
	nMin = atoi(tmp);

	memcpy(tmp,pchTime+4 ,2);
	tmp[2]=0;
	nSec = atoi(tmp);

	struct tm *p = new struct tm();
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);//��ȡʱ������tz��
	p->tm_year = nYear - 1900;
	p->tm_mon = nMonth - 1;
	p->tm_mday = nDay;
	p->tm_hour = nHour;
	p->tm_min = nMin;
	p->tm_sec = nSec;
	time_t utc_t = mktime(p);
	delete(p);
	tv.tv_sec = utc_t;
	tv.tv_usec = 0;
	if (settimeofday(&tv, &tz) < 0)
	{
		return;
	}
}

BYTE CUtils::HextoBcd(BYTE Hex)
{
	BYTE H,L,bBcd;
	
	H=Hex/10;
	L=Hex%10;

	bBcd=(H<<4) | L;

	return bBcd;
}

VOID CUtils::HextoBcd(SHORT Hex,PBYTE pBcd)
{
	BYTE H,L;
	
	H=Hex/1000;
	L=(Hex%1000)/100;
	pBcd[0]=(H<<4) | L;

	H=(Hex%100)/10;
	L=Hex%10;
	pBcd[1]=(H<<4) | L;
}

/*---------------------------------------------------------------------------------
	�� �� ��:	StrtoBcd
	��������:	�����ַ���ת��ΪBCD��
	��    ��:	pch:       �����ַ���
	��    ��:	pBcd:������BCD��
	��	  ��:	��
	ȫ�ֱ���:	��
	ע    ��:   ���������ַ���"1234"ת��ΪBCD: 0x12 0x34
				    �����ַ���"123"ת��ΪBCD:  0x12 0x30
---------------------------------------------------------------------------------*/
VOID CUtils::StrtoBcd(PCHAR pch,PBYTE pBcd)
{
	SHORT n;
	BYTE  H,L;

	n=0;
	while (*pch)
	{
		H=*pch-'0';
		pch++;
		if (*pch) L=*pch-'0';
		else L=0x00;
		pch++;
		pBcd[n]=(H<<4) | L;
		n++;
	}
}

/*---------------------------------------------------------------------------------
	�� �� ��:	BcdtoStr
	��������:	BCD��ת��Ϊ�����ַ���
	��    ��:	pBcd:������BCD��
	��    ��:	pch:       �����ַ���
	��	  ��:	��
	ȫ�ֱ���:	��
	ע    ��:   ����BCD: 0x12 0x34ת��Ϊ�����ַ���"1234"
---------------------------------------------------------------------------------*/
VOID CUtils::BcdtoStr(PBYTE pBcd,SHORT sLen,PCHAR pch)
{
	SHORT i;
	BYTE  H,L;

	for (i=0;i<sLen;i++) 
	{
		H=pBcd[i]>>4;
		L=pBcd[i]&0x0f;
		*pch=H+'0';
		pch++;
		*pch=L+'0';
		pch++;
	}

	*pch=0;
}

SHORT CUtils::BcdtoShort(BYTE bBcd)
{
	BYTE  H,L;

	H=bBcd>>4;
	L=bBcd&0x0f;

	return(H*10+L);
}

/*---------------------------------------------------------------------------------
	�� �� ��:	StrtoHex
	��������:	�ַ���ת��ΪHEX��
	��    ��:	pch:       �����ַ���
	��    ��:	pbHex:���� HEX��
	��	  ��:	��
	ȫ�ֱ���:	��
	ע    ��:   �����ַ���"AB37"ת��ΪHEX: 0xAB 0x37
---------------------------------------------------------------------------------*/
void CUtils::StrtoHex(PCHAR pch,PBYTE pbHex)
{
	BYTE  H,L;
	CHAR  ch1,ch2;
	int   i,j=0;

	int sLen = strlen(pch);
	for (i=0;i<sLen;i+=2)
	{
		ch1=toupper(pch[i]);
		ch2=toupper(pch[i+1]);
		
		if (ch1>'F')
			H = 0;
		else if (ch1>='A')
			H = ch1-'A'+10;
		else if (ch1>='0')
			H = ch1-'0';
		else
			H =0;

		if (ch2>'F')
			L = 0;
		else if (ch2>='A')
			L = ch2-'A'+10;
		else if (ch2>='0')
			L = ch2-'0';
		else 
			L = 0;

		pbHex[j++] = H*16+L;
	}
}

/*---------------------------------------------------------------------------------
	�� �� ��:	HextoStr
	��������:	�ַ���ת��ΪHEX��
	��    ��:	pbHex:���� HEX��
	��    ��:	pch:       �����ַ���
	��	  ��:	��
	ȫ�ֱ���:	��
	ע    ��:   �����ַ���HEX: 0xAB 0x37ת��Ϊ"AB37"
---------------------------------------------------------------------------------*/
void CUtils::HextoStr(PBYTE pbHex,int sLen,PCHAR pch)
{
	BYTE  H,L;
	CHAR  ch1,ch2;
	int   i;

	for (i=0;i<sLen;i++)
	{
		H = pbHex[i] >> 4;
		L = pbHex[i] & 0x0F;

		if (H>15) ch1 = 'F';
		else if (H>=10) ch1 = 'A'+H-10;
		else ch1 = H+'0';
		
		if (L>15) ch2 = 'F';
		else if (L>=10) ch2 = 'A'+L-10;
		else ch2 = L+'0';

		pch[i*2] = ch1;
		pch[i*2+1] = ch2;
	}

	pch[sLen*2] = 0;
}

int CUtils::SplitString(CStringArray & strarr, LPSTR str, LPCSTR sep)
{
	// strarr.RemoveAll();
	strarr.clear();

	int iSepLen = strlen(sep);
	PCHAR pch1 = str;
	PCHAR pch2 = strstr(pch1, sep);

	int nIndex = 0;
	while (NULL != pch2)
	{
		strarr.push_back(CString(pch1, pch2 - pch1)), nIndex ++;

		pch1 = pch2 + iSepLen;
		pch2 = strstr(pch1, sep);
	}

	// if (strlen(pch1) > 0)  // ���һ�����ַ���ʱҲ����һ����������ⲿ�жϲ�������
	{
		strarr.push_back(pch1), nIndex ++;
	}

	return nIndex;
}