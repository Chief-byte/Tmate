// IDC.h: interface for the IDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDC_H__6A276BA6_D3B5_42A0_8F25_2BE07C362D6C__INCLUDED_)
#define AFX_IDC_H__6A276BA6_D3B5_42A0_8F25_2BE07C362D6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../stdafx.h"

#ifdef PROTOCOL_PISA
#include "../PISA/include/lfsapi.h"
#else
#include "../LFS/include/lfsapi.h"
#endif

// DC½Ó¿ÚÀà

class IDC
{
public:
	IDC(){};
	virtual ~IDC(){};

public:
	virtual HRESULT OpenDC(LPCTSTR strServiceName, long dwVersionsRequired) { return 0; };
	virtual HRESULT CloseDC() { return 0; };
	virtual BOOL IsBlocking() { return FALSE; };
	virtual	HRESULT CancelAsyncRequest() { return 0; };
	virtual int OnDCMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return 0; };

	virtual HRESULT CallDC(LPCTSTR strMethod, LPCTSTR strParams) { return 0; };
};

#endif // !defined(AFX_IDC_H__6A276BA6_D3B5_42A0_8F25_2BE07C362D6C__INCLUDED_)
