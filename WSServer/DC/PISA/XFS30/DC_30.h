// DCCardReader.h: interface for the CDCCardReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DC_30_H__INCLUDED_)
#define AFX_DC_30_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../include/DCTrace.h"
#include "../../../include/Utils.h"
#include "../../DC/IDC.h"
#include "../../DC/DC.h"
#include "../include/lfsapi.h"
#include "../include/lfsadmin.h"
#include "../../../stdafx.h"

// 使用信号量
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/*
typedef HRESULT(* LPLFSSTARTUP)(DWORD dwVersionsRequired, LPLFSVERSION lpLFSVersion);
typedef HRESULT(* LPLFSCREATEAPPHANDLE)(LPHAPP lphApp);
typedef HRESULT(* LPLFSOPEN)(LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, DWORD dwSrvcVersionsRequired, LPLFSVERSION lpSrvcVersion, LPLFSVERSION lpSPIVersion, LPHSERVICE lphService);
typedef HRESULT(* LPLFSASYNCOPEN)(LPSTR logical_name, HAPP app_handle, LPSTR app_id, DWORD trace_level, DWORD timeout, LPHSERVICE service, LPSTR object_name, DWORD srvc_versions_required, LPLFSVERSION srvc_version, LPLFSVERSION spi_version, LPREQUESTID request_id);
typedef HRESULT(* LPLFSREGISTER)(HSERVICE hService, DWORD dwEventClass, LPSTR hWndReg);
typedef HRESULT(* LPLFSASYNCREGISTER)(HSERVICE service, DWORD event_class, LPSTR object_reg_name, LPSTR object_name, LPREQUESTID request_id);
// typedef HRESULT(* LPLFSASYNCCLOSE)(HSERVICE hService, DWORD dwEventClass, HWND hWndReg);
typedef HRESULT(*LPLFSASYNCCLOSE)(HSERVICE hService, LPSTR object_name, LPREQUESTID request_id);
// typedef HRESULT(* LPLFSDEREGISTER)(HSERVICE hService, DWORD dwEventClass, HWND hWndReg);
typedef HRESULT(*LPLFSDEREGISTER)(HSERVICE hService, DWORD dwEventClass, LPSTR object_reg_name);
typedef HRESULT(* LPLFSDESTROYAPPHANDLE)(HAPP hApp);
typedef HRESULT(* LPLFSCANCELASYNCREQUEST)(HSERVICE hService, REQUESTID RequestID);
typedef HRESULT(* LPLFSISBLOCKING)();
typedef HRESULT(* LPLFSFREERESULT)(LPLFSRESULT lpResult);
// typedef HRESULT(* LPLFSASYNCEXECUTE)(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID);
typedef HRESULT(*LPLFSASYNCEXECUTE)(HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, LPSTR object_name, LPREQUESTID lpRequestID);
// typedef HRESULT(* LPLFSGETINFO)(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPLFSRESULT * lppResult);
typedef HRESULT(*LPLFSGETINFO)(HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPLFSRESULT * lppResult);


extern LPLFSSTARTUP					LFSStartUp;
extern LPLFSCREATEAPPHANDLE			LFSCreateAppHandle;
extern LPLFSOPEN 					LFSOpen;
extern LPLFSASYNCOPEN 				LFSAsyncOpen;
extern LPLFSREGISTER 				LFSRegister;
extern LPLFSASYNCREGISTER 			LFSAsyncRegister;
extern LPLFSASYNCCLOSE				LFSAsyncClose;
extern LPLFSDEREGISTER				LFSDeregister;
extern LPLFSDESTROYAPPHANDLE		LFSDestroyAppHandle;
extern LPLFSCANCELASYNCREQUEST		LFSCancelAsyncRequest;
extern LPLFSISBLOCKING				LFSIsBlocking;
extern LPLFSFREERESULT				LFSFreeResult;
extern LPLFSASYNCEXECUTE			LFSAsyncExecute;
extern LPLFSGETINFO 				LFSGetInfo;
*/

VOID LFSCallBack(LPSTR lpstrObject_Name, DWORD dwEventID, UINT wParam, LONG lParam);

class CDC_30 : public IDC
{
public:
	CDC_30();
	~CDC_30();
public:
	void * m_hDll;
	void * m_hManagerDll;
	bool m_bLFSLoaded;

	bool LoadXFS();
	void UnloadXFS();
public:
	struct DCOBJECT
	{
		CString		m_strServiceName;
		DWORD		dwVersionsRequired;
		BOOL		m_bWosaXFSRun;
		HRESULT		m_hOpenResult;
		HANDLE		m_hApp;
		USHORT		m_hService;
		DWORD		m_dwWosaThreadID;

		DCOBJECT()
		{
			m_strServiceName = "";
			dwVersionsRequired = 0;
			m_bWosaXFSRun = FALSE;
			m_hOpenResult = DC_ERROR;
			m_hApp = NULL;
			m_hService = NULL;
			m_dwWosaThreadID = 0;
		}
	} m_DCObject;

	CString m_strDCName;
	CString m_strTraceComponent;

public:		
	CUtils				m_Utils;
	// CEvent				m_evtOpenThreadFinish;
	ULONG				m_RequestID;

public:
	// static UINT OpenThread(LPVOID lpParam);
	bool m_bIsOenCompleted;  // 20200805 Linux设备上因打开模块时需要传入D-Bus的路径，不能使用同步打开模块方式，更改为异步打开方式：收到异步模块打开完成才能认为模块打开完成
	bool m_bIsOpenThreadEnd;
	static void * OpenThread(LPVOID lpParam);

	virtual CString GetXFSErrStr(HRESULT hResult);
	virtual CString GetXFSMsgStr(DWORD dwEventID);
	virtual CString GetXFSSysEvtStr(DWORD dwEventID);
	virtual CString GetXFSCmdStr(DWORD dwCmdCode);

	LPTSTR FormatExtra(LPTSTR lpszExtra);

public:
	virtual HRESULT OpenDC(LPCTSTR strServiceName, long dwVersionsRequired);
	virtual HRESULT CloseDC();
	virtual BOOL IsBlocking();
	virtual	HRESULT CancelAsyncRequest();
	virtual HRESULT _CallDC(LPCTSTR strMethod, CString & strSingleParam, CStringArray & strarrParams, BOOL & bValid) = 0;

public:
	HRESULT CallDC(LPCTSTR strMethod, LPCTSTR strParams);

// 信号量处理
protected:
	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *arry;
	};

	int semaphore_init();
	void semaphore_del();
	int semaphore_p(int timeoutseconds);
	int semaphore_v();

	unsigned long GetTickCount();

private:
	CallBack  m_lpLFSCallBack;
};

#endif // !defined(AFX_DC_30_H__INCLUDED_)
