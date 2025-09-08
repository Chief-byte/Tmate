// Base64.h: interface for the CKeyou class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYOU_H__91E9E5DD_6C15_41B8_9B59_4BADE7523EBF__INCLUDED_)
#define AFX_KEYOU_H__91E9E5DD_6C15_41B8_9B59_4BADE7523EBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "KDMexp.h"

class CKeyou
{
public:
	CKeyou();
	virtual ~CKeyou();

	static CKeyou * GetInstance()
	{
		if (nullptr == m_pInstance)
		{
			m_pInstance = new CKeyou();
		}

		return m_pInstance;
	}

public:
	short GetSM4Key(string strSessionName, int nMaxPortNum, char * strTermNum);
	short CancelGetKey();
	short CompleteKey(int nResult); // = 0ʧ�ܣ� = 1�ɹ�

private:
	// ��ȡ��Կ�ַ���������Կ�߳�
	static void * GetSM4KeyThread(void * lpParam);

	static CKeyou * m_pInstance;

public:
	void * m_hKeyouDll;

	char m_strCom[64];
	bool m_bEnd;

public:
	PFDISPATCHDATA m_DispatchData;
	PFASSEMBLEMSG m_AssembleMsg;
};
#endif // !defined(AFX_KEYOU_H__91E9E5DD_6C15_41B8_9B59_4BADE7523EBF__INCLUDED_)
