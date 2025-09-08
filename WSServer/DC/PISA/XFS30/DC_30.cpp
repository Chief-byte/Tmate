// DC_30.cpp: implementation of the DC_30 class.
//
//////////////////////////////////////////////////////////////////////

#include "DC_30.h"
// #include "JavaScriptStringParam.h"
#include "JavaScriptStringParam.h"
#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>

#include <X11/Xlib.h>

//*
LPLFSSTARTUP				LFSStartUp = NULL;
LPLFSCREATEAPPHANDLE		LFSCreateAppHandle = NULL;
LPLFSOPEN 					LFSOpen = NULL;
LPLFSASYNCOPEN				LFSAsyncOpen = NULL;
LPLFSREGISTER 				LFSRegister = NULL;
LPLFSASYNCREGISTER 			LFSAsyncRegister;
LPLFSASYNCCLOSE				LFSAsyncClose = NULL;
LPLFSDEREGISTER				LFSDeregister = NULL;
LPLFSDESTROYAPPHANDLE		LFSDestroyAppHandle = NULL;
LPLFSCANCELASYNCREQUEST		LFSCancelAsyncRequest = NULL;
LPLFSISBLOCKING				LFSIsBlocking = NULL;
LPLFSFREERESULT				LFSFreeResult = NULL;
LPLFSASYNCEXECUTE			LFSAsyncExecute = NULL;
LPLFSGETINFO 				LFSGetInfo = NULL;
LPLFSASYNCGETINFO 			LFSAsyncGetInfo = NULL;

LPLFMREGCALLBACK			LPLFMRegCallBack = NULL;
//*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

unsigned long CDC_30::GetTickCount()
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

bool CDC_30::LoadXFS()
{
	printf("Version of DC.so: 20241230 PISA\n");

	m_hDll = dlopen("/usr/lib/liblfs.so", RTLD_LAZY);        // load SP so
	// m_hDll = dlopen("/usr/lib/liblfs.so.1.2", RTLD_LAZY);        // load SP so
	// m_hDll = dlopen("/data/sp/liblfs.so", RTLD_LAZY);        // load SP so
	if (m_hDll == NULL)
	{
	 	printf("LoadXFS(/usr/lib/liblfs.so) failed : %s\n", dlerror());
	//	printf("LoadXFS(/data/sp/liblfs.so) failed : %s\n", dlerror());
		return false;
	}
	printf("LoadXFS(/usr/lib/liblfs.so) success\n");
	// printf("LoadXFS(/data/sp/liblfs.so) success\n");

	m_hManagerDll = dlopen("/usr/lib/libpisaManager.so", RTLD_LAZY);        // load Manager so
	if (m_hManagerDll == NULL)
	{
		// 	printf("LoadXFS(/usr/lib/liblfs.so) failed : %s\n", dlerror());
		printf("LoadXFS(/usr/lib/libpisaManager.so) failed : %s\n", dlerror());
		return false;
	}
	printf("LoadXFS(/usr/lib/libpisaManager.so) success\n");

	LFSStartUp = (LPLFSSTARTUP)dlsym(m_hDll, "LFSStartUp");
	if (!LFSStartUp)
	{
		printf("LoadXFS Function(LFSStartUp) failed : %s\n", dlerror());
		return false;
	}

	/*
	// 20221107
	LFSCreateAppHandle = (LPLFSCREATEAPPHANDLE)dlsym(m_hDll, "LFSCreateAppHandle");
	if (!LFSCreateAppHandle)
	{
		printf("LoadXFS Function(LFSCreateAppHandle) failed : %s\n", dlerror());
		return false;
	}
	//*/

	LFSOpen = (LPLFSOPEN)dlsym(m_hDll, "LFSOpen");
	if (!LFSOpen)
	{
		printf("LoadXFS Function(LFSOpen) failed : %s\n", dlerror());
		return false;
	}
	
	LFSAsyncOpen = (LPLFSASYNCOPEN)dlsym(m_hDll, "LFSAsyncOpen");
	if (!LFSAsyncOpen)
	{
		printf("LoadXFS Function(LFSAsyncOpen) failed : %s\n", dlerror());
		return false;
	}

	LFSRegister = (LPLFSREGISTER)dlsym(m_hDll, "LFSRegister");
	if (!LFSRegister)
	{
		printf("LoadXFS Function(LFSRegister) failed : %s\n", dlerror());
		return false;
	}

	LFSAsyncRegister = (LPLFSASYNCREGISTER)dlsym(m_hDll, "LFSAsyncRegister");
	if (!LFSAsyncRegister)
	{
		printf("LoadXFS Function(LFSAsyncRegister) failed : %s\n", dlerror());
		return false;
	}

	LFSAsyncClose = (LPLFSASYNCCLOSE)dlsym(m_hDll, "LFSAsyncClose");
	if (!LFSAsyncClose)
	{
		printf("LoadXFS Function(LFSAsyncClose) failed : %s\n", dlerror());
		return false;
	}

	LFSDeregister = (LPLFSDEREGISTER)dlsym(m_hDll, "LFSDeregister");
	if (!LFSDeregister)
	{
		printf("LoadXFS Function(LFSDeregister) failed : %s\n", dlerror());
		return false;
	}

	LFSDestroyAppHandle = (LPLFSDESTROYAPPHANDLE)dlsym(m_hDll, "LFSDestroyAppHandle");
	if (!LFSDestroyAppHandle)
	{
		printf("LoadXFS Function(LFSDestroyAppHandle) failed : %s\n", dlerror());
		return false;
	}

	LFSCancelAsyncRequest = (LPLFSCANCELASYNCREQUEST)dlsym(m_hDll, "LFSCancelAsyncRequest");
	if (!LFSCancelAsyncRequest)
	{
		printf("LoadXFS Function(LFSCancelAsyncRequest) failed : %s\n", dlerror());
		return false;
	}

	LFSIsBlocking = (LPLFSISBLOCKING)dlsym(m_hDll, "LFSIsBlocking");
	if (!LFSIsBlocking)
	{
		printf("LoadXFS Function(LFSIsBlocking) failed : %s\n", dlerror());
		return false;
	}

	LFSFreeResult = (LPLFSFREERESULT)dlsym(m_hDll, "LFSFreeResult");
	if (!LFSFreeResult)
	{
		printf("LoadXFS Function(LFSFreeResult) failed : %s\n", dlerror());
		return false;
	}

	LFSAsyncExecute = (LPLFSASYNCEXECUTE)dlsym(m_hDll, "LFSAsyncExecute");
	if (!LFSAsyncExecute)
	{
		printf("LoadXFS Function(LFSAsyncExecute) failed : %s\n", dlerror());
		return false;
	}

	LFSGetInfo = (LPLFSGETINFO)dlsym(m_hDll, "LFSGetInfo");
	if (!LFSGetInfo)
	{
		printf("LoadXFS Function(LFSGetInfo) failed : %s\n", dlerror());
		return false;
	}

	LFSAsyncGetInfo = (LPLFSASYNCGETINFO)dlsym(m_hDll, "LFSAsyncGetInfo");
	if (!LFSGetInfo)
	{
		printf("LoadXFS Function(LFSAsyncGetInfo) failed : %s\n", dlerror());
		return false;
	}

	LPLFMRegCallBack = (LPLFMREGCALLBACK)dlsym(m_hDll, "LFMRegCallBack");
	if (!LPLFMRegCallBack)
	{
		printf("LoadXFS Function(LFMRegCallBack) failed : %s\n", dlerror());
		return false;
	}

	m_bLFSLoaded = true;

	return true;

};
void CDC_30::UnloadXFS()
{
	if (m_hDll)
	{
		dlclose(m_hDll);
		m_hDll = NULL;
	}
};


CDC_30::CDC_30()
{
	m_DCObject.m_bWosaXFSRun = FALSE;
	m_lpLFSCallBack = LFSCallBack;
	m_hDll = NULL;
	m_bLFSLoaded = false;
	LoadXFS();
}

CDC_30::~CDC_30()
{
	CloseDC();
	UnloadXFS();
}

HRESULT CDC_30::CallDC(LPCTSTR strMethod, LPCTSTR strParams)
{
	if (!m_bLFSLoaded)
	{
		printf("LFS not loaded\n");
		return -1;
	}

	// ��¼���ò�����ˮ
	CString strTrace(strlen(strMethod) + strlen(strParams) + 256, 0);

	// �������в���
	// 1����Կֵ
	if (0 == strcmp(strMethod, "WFS_CMD_PIN_IMPORT_KEY"))
	{
		std::string strParamsLog = strParams;
		if (-1 != strParamsLog.find("lpbdata_keyvalue="))
		{
			strParamsLog = strParamsLog.substr(0, strParamsLog.find("lpbdata_keyvalue=")) 
							+ "lpbdata_keyvalue=***;" 
							+ strParamsLog.substr(strParamsLog.find("lpsenckey="));
		}

		sprintf((char *)strTrace.c_str(), "%s(%s)",
			strMethod, strParamsLog.c_str());
	}
	else
	{
		sprintf((char *)strTrace.c_str(), "%s(%s)",
			strMethod, strParams);
	}

	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());

	CString strSingleParam;
	CStringArray strarrParams;
	if (0 == strncmp(strParams, "=", 1))
	{
		// = ��ͷ�Ĳ���Ϊ��һ�������������н���
		strSingleParam = ((LPTSTR)(LPCTSTR)strParams) + 1;
	}
	else
	{
		CJSStringParam::GetStringParams(strParams, GetStringSplitChar(), strarrParams);
	}

	// ��������
	BOOL bValid = FALSE;
	HRESULT hResult = _CallDC(strMethod, strSingleParam, strarrParams, bValid);

	// ��¼���ý����ˮ
	if (TRUE == bValid)
	{
		strTrace = CString(1024, 0);
		sprintf((char *)strTrace.c_str(), "LFSAsyncExecute(%s) m_RequestID:%d, hResult:%d(%s)",
						strMethod, m_RequestID, hResult, GetXFSErrStr(hResult).c_str());
	}
	else
	{
		strTrace = CString(1024, 0);
		sprintf((char *)strTrace.c_str(), "Invalid Method(%s), hResult:%d(%s)",
						strMethod, hResult, "DC_ERROR");
	}
	WriteTrace(m_strTraceComponent.c_str(), XFSApiRtn, strTrace.c_str());

	return hResult;
}

void repalce_all_ditinct(string& str, const string& old_value, const string& new_value)
{
	for (string::size_type pos(0); pos != string::npos; pos += strlen(new_value.c_str())) {
		if ((pos = str.find(old_value, pos)) != string::npos)
			str.replace(pos, strlen(old_value.c_str()), new_value);
		else break;
	}
}

HRESULT CDC_30::OpenDC(LPCTSTR strServiceName, long dwVersionsRequired)
{
	if (!m_bLFSLoaded)
	{
		printf("LFS not loaded\n");
		return -1;
	}

	if (m_strTraceComponent == CashAcceptor)
	{
		sleep(10);
		printf("Open CashAcceptor delay 10s\n");
	}

	printf("<DC> CDC_30::OpenDC(%s, %ld)\n", strServiceName, dwVersionsRequired);

	m_DCObject.m_strServiceName = strServiceName;
	m_DCObject.dwVersionsRequired = (DWORD)dwVersionsRequired;

	HRESULT hResult = DC_ERROR;
	m_DCObject.m_hOpenResult = DC_ERROR;

	CString strTrace;
	if (FALSE == m_DCObject.m_bWosaXFSRun)
	{
		printf("<DC> CDC_30::OpenDC FALSE == m_DCObject.m_bWosaXFSRun\n");

		// ע��ӹ������Ļص�����
		printf("<DC> CDC_30::OpenDC LFMRegCallBack >>>\n");
		LPLFMRegCallBack((LPSTR)m_strDCName.c_str(), (CallBack *)&m_lpLFSCallBack);
		printf("<DC> CDC_30::OpenDC LFMRegCallBack <<<\n");

		// DWORD dwWosaThreadID = 0;
		// CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OpenThread, this, 0, &dwWosaThreadID);
		pthread_t dwWosaThreadID = 0;
		printf("<DC> CDC_30::OpenDC pthread_create >>>\n");
		m_bIsOpenThreadEnd = false;
		pthread_create(&dwWosaThreadID, NULL, OpenThread, this);
		printf("<DC> CDC_30::OpenDC pthread_create <<<\n");

		// 20180521 ���฻ PC2050 ����180����δ����� ȡ�� ģ��򿪲���������Ϊ600�룬����
		// DWORD dwWaitOb = WaitForSingleObject(m_evtOpenThreadFinish.m_hObject, 180000);
		/*
		DWORD dwWaitOb = WaitForSingleObject(m_evtOpenThreadFinish.m_hObject, 600000);
		if ((WAIT_OBJECT_0 == dwWaitOb) && (TRUE == m_DCObject.m_bWosaXFSRun))
		*/
		int nWaitResult = 0;
		while (false == m_bIsOpenThreadEnd)
		{
			sleep(1);
		}
		printf("<DC> m_bIsOpenThreadEnd : true <<<\n");
		if ((0 == nWaitResult) && (TRUE == m_DCObject.m_bWosaXFSRun))
		{
			hResult = m_DCObject.m_hOpenResult;
		}
		else if (LFS_SUCCESS != m_DCObject.m_hOpenResult)
		{
			// �������򿪵�m_DCObject.m_hOpenResult��LFS_SUCCESS���������Ϊ�ǳɹ�
			hResult = m_DCObject.m_hOpenResult;
		}
	}
	else
	{
		hResult = LFS_SUCCESS;
	}

	CString strWfsResult(256, 0);
	sprintf((char *)strWfsResult.c_str(), "wfsresult.hresult=%d", hResult);

	strTrace = CString(strlen(strWfsResult.c_str()) + 256, 0);
	sprintf((char *)strTrace.c_str(), "messageid : %d(%s), wfsresult : %s",
		LFS_OPEN_COMPLETE, GetXFSMsgStr(LFS_OPEN_COMPLETE).c_str(), strWfsResult.c_str());
	WriteTrace(m_strTraceComponent.c_str(), OCXEVENT, strTrace.c_str());

	FireDCEvent(m_strDCName, LFS_OPEN_COMPLETE, strWfsResult);

	return hResult;
}

// UINT CDC_30::OpenThread(LPVOID lpParam)
void * CDC_30::OpenThread(LPVOID lpParam)
{
	printf("<DC> CDC_30::OpenThread >>>\n");

	CDC_30 * pDC_30 = (CDC_30 *)lpParam;

	HRESULT		hResult = DC_ERROR;
	DWORD		dwVersionsRequired = 0;
	LFSVERSION	Version = {0};
	LPSTR		lpszLogicalName = NULL;
	LPSTR		lpszAppID = NULL;
	DWORD		dwTraceLevel = 0;

	printf("<DC> CDC_30::OpenThread 1 >>>\n");
	DWORD		dwStart = pDC_30->GetTickCount();
	printf("<DC> CDC_30::OpenThread 2 >>>\n");

	LFSVERSION	SrvcVersion = {0};
	LFSVERSION	SPIVersion = {0};

	printf("<DC> CDC_30::OpenThread 3 >>>\n");
	dwVersionsRequired = pDC_30->m_DCObject.dwVersionsRequired;
	printf("<DC> CDC_30::OpenThread 4 >>>\n");

	if (NULL == LFSStartUp) printf("<DC> LFSStartUp is NULL\n"); else printf("<DC> call LFSStartUp >>>\n");
	Version.wVersion = 0x01;
	Version.wLow_Version = 0x01;
	Version.wHigh_Version = 0x01;
	hResult = LFSStartUp(dwVersionsRequired, &Version);
	printf("<DC> call LFSStartUp <<<\n");
	CString strTrace((Version.strDescription == NULL ? 0 : strlen(Version.strDescription))
					+ (Version.strSystem_Status == NULL ? 0 : strlen(Version.strSystem_Status))
					+ 2048, 0);
	sprintf((char *)strTrace.c_str(), "LFSStartUp():"
					"hResult:%d(%s),"
					"dwVersionsRequired:%d,"
					"Version.version:%d,"
					"Version.low_version:%d,"
					"Version.high_version:%d,"
					"Version.description:%s,"
					"Version.system_status:%s",
					hResult, pDC_30->GetXFSErrStr(hResult).c_str(),
					dwVersionsRequired,
					Version.wVersion,
					Version.wLow_Version,
					Version.wHigh_Version,
					((Version.strDescription ==NULL)||(strcmp(Version.strDescription,"")==0))?"NULL":Version.strDescription,
					((Version.strSystem_Status ==NULL)||(strcmp(Version.strSystem_Status,"")==0))?"NULL":Version.strSystem_Status);

	WriteTrace(pDC_30->m_strTraceComponent.c_str(), XFSApiStart, strTrace.c_str());

    if (LFS_SUCCESS == hResult || LFS_ERR_ALREADY_STARTED == hResult)
    {
		pDC_30->m_DCObject.m_hApp = NULL;
		/*
		// 20221107
		hResult = LFSCreateAppHandle(&(pDC_30->m_DCObject.m_hApp));
		printf("LFSCreateAppHandle ret %d, pDC_30->m_DCObject.m_hApp = %ld\n", hResult, pDC_30->m_DCObject.m_hApp);

		if (LFS_SUCCESS != hResult )
		{
			strTrace = CString(256, 0);
			sprintf((char *)strTrace.c_str(), "LFSCreateAppHandle Fail:hResult:%d(%s)", 
							hResult, pDC_30->GetXFSErrStr(hResult).c_str());
			WriteTrace(pDC_30->m_strTraceComponent.c_str(), XFSApiOpen, strTrace.c_str());

		    // ::SetEvent(pDC_30->m_evtOpenThreadFinish);
			pDC_30->m_bIsOpenThreadEnd = true;
			return 0;
		}
		//*/

		/*
		SrvcVersion.version		= 0x0203;
		SrvcVersion.low_version		= 0x03;
		SrvcVersion.high_version	= 0x0203;
		*/
		SrvcVersion.wVersion = 0x01;
		SrvcVersion.wLow_Version = 0x01;
		SrvcVersion.wHigh_Version = 0x01;
		lpszLogicalName				= (char *)pDC_30->m_DCObject.m_strServiceName.c_str();
        lpszAppID					= "SSA XFS DC";
        dwTraceLevel				= LFS_TRACE_API;
        dwVersionsRequired			= pDC_30->m_DCObject.dwVersionsRequired;

		hResult = LFS_ERR_OP_IN_PROGRESS;
		
		/*
		pDC_30->m_DCObject.m_hOpenResult = hResult = 
				LFSOpen(	lpszLogicalName, 
							// pDC_30->m_DCObject.m_hApp,
							0, // LFS_DEFAULT_HAPP
							lpszAppID,
							dwTraceLevel,
							LFS_INDEFINITE_WAIT,
							dwVersionsRequired,
							&SrvcVersion,
							&SPIVersion,
							&(pDC_30->m_DCObject.m_hService));
		*/
			
		pDC_30->m_bIsOenCompleted = FALSE;  // ������Ҫ�ȴ�SP��ģ�������¼�

		ULONG requestid = 0;
		printf("LFSAsyncOpen >>>\n");
		pDC_30->m_DCObject.m_hOpenResult = hResult =
			LFSAsyncOpen(lpszLogicalName,
				pDC_30->m_DCObject.m_hApp,
				// 0, // LFS_DEFAULT_HAPP
				lpszAppID,
				dwTraceLevel,
				LFS_INDEFINITE_WAIT,
				&(pDC_30->m_DCObject.m_hService),
				(char *)pDC_30->m_strDCName.c_str(),
				dwVersionsRequired,
				&SrvcVersion,
				&SPIVersion, 
				&requestid);

		printf("LFSAsyncOpen <<<\n");

		strTrace = CString((lpszLogicalName == NULL ? 0 : strlen(lpszLogicalName))
							+ (lpszAppID == NULL ? 0 : strlen(lpszAppID))
							+ (Version.strDescription == NULL ? 0 : strlen(Version.strDescription))
							+ (Version.strSystem_Status == NULL ? 0 : strlen(Version.strSystem_Status))
							+ 2048, 0);
		//sprintf((char *)strTrace.c_str(), "LFSAsyncOpen():"
		sprintf((char *)strTrace.c_str(), "LFSAsyncOpen():"
						"hResult:%d(%s)"
						"lpszLogicalName:%s,"
						"m_DCObject.m_hApp:%d,"
						"lpszAppID:%s,"
						"dwTraceLevel:%d,"
						"dwTimeOut:%d,"
						"dwVersionsRequired:%d,"
						"SrvcVersion.version:%d,"
						"SrvcVersion.low_version:%d,"
						"SrvcVersion.high_version:%d,"
						"SrvcVersion.description:%s,"
						"SrvcVersion.system_status:%s",
						hResult, pDC_30->GetXFSErrStr(hResult).c_str(),
						(lpszLogicalName==NULL)?"NULL":lpszLogicalName,
						pDC_30->m_DCObject.m_hApp,
						(lpszAppID==NULL)?"NULL":lpszAppID,
						dwTraceLevel,
						LFS_INDEFINITE_WAIT,
						dwVersionsRequired,
						SrvcVersion.wVersion,
						SrvcVersion.wLow_Version,
						SrvcVersion.wHigh_Version,
						((Version.strDescription ==NULL)||(strcmp(Version.strDescription,"")==0))?"NULL":Version.strDescription,
						((Version.strSystem_Status ==NULL)||(strcmp(Version.strSystem_Status,"")==0))?"NULL":Version.strSystem_Status);
		WriteTrace(pDC_30->m_strTraceComponent.c_str(), XFSApiOpen, strTrace.c_str());

		if (LFS_SUCCESS == hResult)
		{
			while (FALSE == pDC_30->m_bIsOenCompleted)
			{
				if ((pDC_30->GetTickCount() - dwStart) > (150 * 1000))
				{
					hResult = DC_ERROR;
					break;
				}

				// ::Sleep(500);
				usleep(500 * 1000);
			}
		}

		if (LFS_SUCCESS == hResult)
		{
			hResult = LFS_ERR_OP_IN_PROGRESS;
			int nRetryTimes = 0;
			dwStart = pDC_30->GetTickCount();

			ULONG requestid = 0;
			DWORD dwEventClass = SYSTEM_EVENTS | USER_EVENTS | EXECUTE_EVENTS | SERVICE_EVENTS;
			while (TRUE)
			{
				pDC_30->m_DCObject.m_hOpenResult = hResult = 
						// LFSRegister(pDC_30->m_DCObject.m_hService, 
						LFSAsyncRegister(pDC_30->m_DCObject.m_hService,
							dwEventClass, 
							(char *)pDC_30->m_strDCName.c_str(),
							(char *)pDC_30->m_strDCName.c_str(),
							&requestid);
				printf("LFSAsyncRegister ret %d\n", hResult);
				if (LFS_SUCCESS == hResult)
				{
					break;
				}

				if ((pDC_30->GetTickCount() - dwStart) > (10 * 1000) || (++ nRetryTimes) >= 10)
				{
					break;
				}

				// ::Sleep(1 * 1000);
				sleep(1);
			}
		}
		
		if (LFS_SUCCESS == hResult)
        {
			pDC_30->m_DCObject.m_bWosaXFSRun = TRUE;
        }
		else
		{
			pDC_30->m_DCObject.m_bWosaXFSRun = FALSE ;
		}
    }
    else
    {
		strTrace = CString(256, 0);
		sprintf((char *)strTrace.c_str(), "LFSStartUp Fail:hResult:%d(%s)", 
						hResult, pDC_30->GetXFSErrStr(hResult).c_str());
		WriteTrace(pDC_30->m_strTraceComponent.c_str(), XFSApiStart, strTrace.c_str());
    }

	// ::SetEvent(pDC_30->m_evtOpenThreadFinish);
	pDC_30->m_bIsOpenThreadEnd = true;
	return 0;
}

HRESULT CDC_30::CloseDC() 
{
	if (!m_bLFSLoaded)
	{
		printf("LFS not loaded\n");
		return -1;
	}

	HRESULT hResult = DC_ERROR;

	if (TRUE == m_DCObject.m_bWosaXFSRun)
	{
		hResult = LFSAsyncClose(	m_DCObject.m_hService,
									(char *)m_strDCName.c_str(),
									&m_RequestID);
		if (LFS_SUCCESS == hResult)
		{
			m_DCObject.m_bWosaXFSRun = FALSE;
			DWORD dwEventClass = SYSTEM_EVENTS | USER_EVENTS | EXECUTE_EVENTS | SERVICE_EVENTS;
			LFSDeregister(m_DCObject.m_hService,
				dwEventClass,
				(char *)m_strDCName.c_str());

			LFSDestroyAppHandle(m_DCObject.m_hApp);
		}
	}

	CString strTrace(256, 0);
	sprintf((char *)strTrace.c_str(), "LFSAsyncClose() hResult = %d(%s)", 
					hResult, GetXFSErrStr(hResult).c_str());
	WriteTrace(m_strTraceComponent.c_str(), OCXCALL, strTrace.c_str());

	return hResult;
}

HRESULT CDC_30::CancelAsyncRequest()
{
	if (!m_bLFSLoaded)
	{
		printf("LFS not loaded\n");
		return -1;
	}

	HRESULT hResult = LFSCancelAsyncRequest(m_DCObject.m_hService, NULL);

	CString strTrace = CString(256, 0);
	sprintf((char *)strTrace.c_str(), "LFSCancelAsyncRequest() hResult:%d(%s)",
					hResult, GetXFSErrStr(hResult).c_str());
	WriteTrace(m_strTraceComponent.c_str(), XFSApiRtn, strTrace.c_str());
	
	return hResult;
}

BOOL CDC_30::IsBlocking()
{
	if (!m_bLFSLoaded)
	{
		printf("LFS not loaded\n");
		return -1;
	}

	return LFSIsBlocking();
}

CString	CDC_30::GetXFSCmdStr(DWORD dwCmdCode)
{
	return "DC_INVALID_CMD";
}

CString	CDC_30::GetXFSMsgStr(DWORD dwEventID)
{
	struct XFSMSG {
		char strMsg[128];
		DWORD iMsg;
	}XFSMsg[]={
		{"WFS_OPEN_COMPLETE"					,(WM_USER + 1)},
		{"WFS_CLOSE_COMPLETE"					,(WM_USER + 2)},
		{"WFS_LOCK_COMPLETE"					,(WM_USER + 3)},
		{"WFS_UNLOCK_COMPLETE"					,(WM_USER + 4)},
		{"WFS_REGISTER_COMPLETE"				,(WM_USER + 5)},
		{"WFS_DEREGISTER_COMPLETE"				,(WM_USER + 6)},
		{"WFS_GETINFO_COMPLETE"					,(WM_USER + 7)},
		{"WFS_EXECUTE_COMPLETE"					,(WM_USER + 8)},

		{"WFS_EXECUTE_EVENT"					,(WM_USER + 20)},
		{"WFS_SERVICE_EVENT"					,(WM_USER + 21)},
		{"WFS_USER_EVENT"						,(WM_USER + 22)},
		{"WFS_SYSTEM_EVENT"						,(WM_USER + 23)},

		{"WFS_TIMER_EVENT"						,(WM_USER + 100)}
	};
	CString strRes="DC_INVALID_MSG";
	for (int i = 0; i < sizeof(XFSMsg) / sizeof(XFSMSG); i ++)
	{
		if( XFSMsg[i].iMsg==dwEventID )
		{
			strRes=XFSMsg[i].strMsg;
			break;
		}
	}
	return strRes;
}

CString	CDC_30::GetXFSSysEvtStr(DWORD dwEventID)
{
	struct XFSSYSEVT {
		char strSysEvt[128];
		DWORD iSysEvt;
	}XFSSysEvt[]={
		{"WFS_SYSE_UNDELIVERABLE_MSG"              ,1},
		{"WFS_SYSE_HARDWARE_ERROR"                 ,2},
		{"WFS_SYSE_VERSION_ERROR"                  ,3},
		{"WFS_SYSE_DEVICE_STATUS"                  ,4},
		{"WFS_SYSE_APP_DISCONNECT"                 ,5},
		{"WFS_SYSE_SOFTWARE_ERROR"                 ,6},
		{"WFS_SYSE_USER_ERROR"                     ,7},
		{"WFS_SYSE_LOCK_REQUESTED"                 ,8}
	};
	CString strRes="UNKNOWN MSG";
	for (int i = 0; i < sizeof(XFSSysEvt) / sizeof(XFSSYSEVT); i ++)
	{
		if( XFSSysEvt[i].iSysEvt==dwEventID )
		{
			strRes=XFSSysEvt[i].strSysEvt;
			break;
		}
	}
	return strRes;
}

CString	CDC_30::GetXFSErrStr(HRESULT hResult)
{
	if (hResult >= DC_ERROR && hResult < LFS_ERR_UNSUPP_DATA)
	{
		return "DC_ERROR";
	}

	struct XFSERR {
		char strErr[128];
		LONG iErr;
	}XFSErr[]={
		{"WFS_SUCCESS"						,0},
		{"WFS_ERR_ALREADY_STARTED"			,-1},
		{"WFS_ERR_API_VER_TOO_HIGH"			,-2},
		{"WFS_ERR_API_VER_TOO_LOW"			,-3},
		{"WFS_ERR_CANCELED"					,-4},
		{"WFS_ERR_CFG_INVALID_HKEY"			,-5},
		{"WFS_ERR_CFG_INVALID_NAME"			,-6},
		{"WFS_ERR_CFG_INVALID_SUBKEY"		,-7},
		{"WFS_ERR_CFG_INVALID_VALUE"		,-8},
		{"WFS_ERR_CFG_KEY_NOT_EMPTY"		,-9},
		{"WFS_ERR_CFG_NAME_TOO_LONG"		,-10},
		{"WFS_ERR_CFG_NO_MORE_ITEMS"		,-11},
		{"WFS_ERR_CFG_VALUE_TOO_LONG"		,-12},
		{"WFS_ERR_DEV_NOT_READY"			,-13},
		{"WFS_ERR_HARDWARE_ERROR"			,-14},
		{"WFS_ERR_INTERNAL_ERROR"			,-15},
		{"WFS_ERR_INVALID_ADDRESS"			,-16},
		{"WFS_ERR_INVALID_APP_HANDLE"		,-17},
		{"WFS_ERR_INVALID_BUFFER"			,-18},
		{"WFS_ERR_INVALID_CATEGORY"			,-19},
		{"WFS_ERR_INVALID_COMMAND"			,-20},
		{"WFS_ERR_INVALID_EVENT_CLASS"		,-21},
		{"WFS_ERR_INVALID_HSERVICE"			,-22},
		{"WFS_ERR_INVALID_HPROVIDER"		,-23},
		{"WFS_ERR_INVALID_HWND"				,-24},
		{"WFS_ERR_INVALID_HWNDREG"			,-25},
		{"WFS_ERR_INVALID_POINTER"			,-26},
		{"WFS_ERR_INVALID_REQ_ID"			,-27},
		{"WFS_ERR_INVALID_RESULT"			,-28},
		{"WFS_ERR_INVALID_SERVPROV"			,-29},
		{"WFS_ERR_INVALID_TIMER"			,-30},
		{"WFS_ERR_INVALID_TRACELEVEL"		,-31},
		{"WFS_ERR_LOCKED"					,-32},
		{"WFS_ERR_NO_BLOCKING_CALL"			,-33},
		{"WFS_ERR_NO_SERVPROV"				,-34},
		{"WFS_ERR_NO_SUCH_THREAD"			,-35},
		{"WFS_ERR_NO_TIMER"					,-36},
		{"WFS_ERR_NOT_LOCKED"				,-37},
		{"WFS_ERR_NOT_OK_TO_UNLOAD"			,-38},
		{"WFS_ERR_NOT_STARTED"				,-39},
		{"WFS_ERR_NOT_REGISTERED"			,-40},
		{"WFS_ERR_OP_IN_PROGRESS"			,-41},
		{"WFS_ERR_OUT_OF_MEMORY"			,-42},
		{"WFS_ERR_SERVICE_NOT_FOUND"		,-43},
		{"WFS_ERR_SPI_VER_TOO_HIGH"			,-44},
		{"WFS_ERR_SPI_VER_TOO_LOW"			,-45},
		{"WFS_ERR_SRVC_VER_TOO_HIGH"		,-46},
		{"WFS_ERR_SRVC_VER_TOO_LOW"			,-47},
		{"WFS_ERR_TIMEOUT"					,-48},
		{"WFS_ERR_UNSUPP_CATEGORY"			,-49},
		{"WFS_ERR_UNSUPP_COMMAND"			,-50},
		{"WFS_ERR_VERSION_ERROR_IN_SRVC"	,-51},
		{"WFS_ERR_INVALID_DATA"				,-52},
		{"WFS_ERR_SOFTWARE_ERROR"			,-53},
		{"WFS_ERR_CONNECTION_LOST"			,-54},
		{"WFS_ERR_USER_ERROR"				,-55},
		{"WFS_ERR_UNSUPP_DATA"				,-56}
	};

	CString strRes="UNKNOWN ERROR";

	for (int i = 0; i < sizeof(XFSErr) / sizeof(XFSERR); i ++)
	{
		if ( XFSErr[i].iErr==hResult )
		{
			strRes=XFSErr[i].strErr;
			break;
		}
	}
	return strRes;
}

LPTSTR CDC_30::FormatExtra(LPTSTR lpszExtra)
{
	// ��ʽ����չ�ֶ�����
	// �󲿷�����£���չ�ֶ���\0����
	// ��������£���չ�ֶ�����������\0�������м�ĵ���\0ֻ���ڷָ���չ�ֶ��еĶ�����ݣ����SP���������������������������ָ��Խ���쳣����
	// ��������������ݣ���������ļ� /SSA/WSServer/extra2null.flag ʱ������������\0��������
	struct stat s_buf = { 0 };

	if (0 == stat("/SSA/WSServer/extra2null.flag", &s_buf))
	{
		for (int nLoop = 0; ; nLoop++)
		{
			if ((NULL == lpszExtra[nLoop] && NULL == lpszExtra[nLoop + 1])
				|| lpszExtra[nLoop] > 128)
			{
				// ������������NULLʱ�����������ǿɼ�Ӣ���ַ�ʱ����(��ֹ��������)
				break;
			}
			else if (NULL == lpszExtra[nLoop] || '\r' == lpszExtra[nLoop] || '\n' == lpszExtra[nLoop])  // ���з��ᵼ��js����������
			{
				lpszExtra[nLoop] = ' ';
			}
		}
	}
	else
	{
		for (int nLoop = 0; ; nLoop++)
		{
			if (NULL == lpszExtra[nLoop]
				|| lpszExtra[nLoop] > 128)
			{
				// ����NULLʱ�����������ǿɼ�Ӣ���ַ�ʱ����(��ֹ��������)
				lpszExtra[nLoop] = '\0';
				break;
			}
			else if ('\r' == lpszExtra[nLoop] || '\n' == lpszExtra[nLoop])  // ���з��ᵼ��js����������
			{
				lpszExtra[nLoop] = ' ';
			}
		}
	}

	return lpszExtra;
}

VOID LFSCallBack(LPSTR lpstrObject_Name, DWORD dwEventID, UINT wParam, LONG lParam)
{
	printf("onManagerMessage(%s, %ld, %ld, %ld)\n", lpstrObject_Name, dwEventID, wParam, lParam);
	UINT uMsg = dwEventID;
	string strDCName = lpstrObject_Name;

	// ��map���ң�����ֱ�� m_mapPtrIDeviceController.find(strDCName);����Ϊ strDCName �Ǵ�DBUS·���н�ȡ�����ģ����� "_30"��"_31"֮��ĺ�׺����m_mapPtrIDeviceController�е�key�Ǵ���׺��
	PDCRUNNINGTIME pDCRunningTime = NULL;
	map<CString, PDCRUNNINGTIME>::iterator iter = m_mapPtrIDeviceController.begin();
	while (iter != m_mapPtrIDeviceController.end())
	{
		if (string::npos != iter->first.find(strDCName))
		{
			pDCRunningTime = iter->second;
		}

		iter++;
	}

	if (NULL == pDCRunningTime)
	{
		printf("<DC> OnXFSManagerMessage NULL == pDCRunningTime >>>\n");
		return ;
	}

	if (uMsg > WM_USER)
	{
		if (pDCRunningTime->pIDeviceController)
		{
			pDCRunningTime->pIDeviceController->OnDCMessage(uMsg, 0, lParam);
		}

		return;
	}

	return ;
}