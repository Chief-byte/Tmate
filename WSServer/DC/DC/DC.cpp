// DCCtl.cpp : Implementation of the CDCCtrl ActiveX Control class.

#include "DC.h"

#ifdef PROTOCOL_PISA
#include "../PISA/XFS30/DCCardReader_30/DCCardReader_30.h"
#include "../PISA/XFS30/DCPinPad_30/DCPinPad_30.h"
#include "../PISA/XFS30/DCPrinter_30/DCPrinter_30.h"
#include "../PISA/XFS30/DCCashAcceptor_30/DCCashAcceptor_30.h"
#include "../PISA/XFS30/DCCashDispenser_30/DCCashDispenser_30.h"
#include "../PISA/XFS30/DCSensorsAndIndicators_30/DCSensorsAndIndicators_30.h"
// #include "../PISA/XFS30/DCVendorMode_30/DCVendorMode_30.h"
// #include "../PISA/XFS30/DCScanner_30/DCScanner_30.h"
// #include "../PISA/XFS30/DCBarcode_31/DCBarcode_31.h"
// #include "../PISA/XFS30/DCCardDispenser_31/DCCardDispenser_31.h"
#include "../PISA/XFS30/DCCamera_31/DCCamera_31.h"
#else
#include "../LFS/XFS30/DCCardReader_30/DCCardReader_30.h"
#include "../LFS/XFS30/DCPinPad_30/DCPinPad_30.h"
#include "../LFS/XFS30/DCPrinter_30/DCPrinter_30.h"
#include "../LFS/XFS30/DCCashAcceptor_30/DCCashAcceptor_30.h"
#include "../LFS/XFS30/DCCashDispenser_30/DCCashDispenser_30.h"
#include "../LFS/XFS30/DCSensorsAndIndicators_30/DCSensorsAndIndicators_30.h"
#include "../LFS/XFS30/DCVendorMode_30/DCVendorMode_30.h"
// #include "../LFS/XFS30/DCScanner_30/DCScanner_30.h"
// #include "../LFS/XFS30/DCBarcode_31/DCBarcode_31.h"
// #include "../LFS/XFS30/DCCardDispenser_31/DCCardDispenser_31.h"
#include "../LFS/XFS30/DCCamera_31/DCCamera_31.h"
#endif

#include<stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

// 控制输出文件大小，没有其他作用
char __szUnuseful[10 * 1024] = {0};

IDC * m_pIDeviceController = nullptr;
HMODULE m_hDCTraceMod = NULL;
CString m_strStringSplitChar = "";
PFDCCALLBACKFUNC m_lpDCCallbackFunc = NULL;
std::map<CString, PDCRUNNINGTIME> m_mapPtrIDeviceController;

/////////////////////////////////////////////////////////////////////////////
// CDCCtrl message handlers

HRESULT CallDC(char * strDCName, LPCTSTR strMethod, LPCTSTR strParams)
{
	printf("<DC> CallDC(%s, %s) %s\n", strMethod, strParams, strDCName);

	map<CString, PDCRUNNINGTIME>::iterator iter;
	iter = m_mapPtrIDeviceController.find(strDCName);

	PDCRUNNINGTIME pDCRunningTime = NULL;
	// if (NULL == m_pIDeviceController)
	if (m_mapPtrIDeviceController.end() == iter)
	{
		printf("<DC> CallDC NULL == pIDeviceController >>>\n");
		return -1;
	}
	else
	{
		pDCRunningTime = iter->second;
	}

	HRESULT hResult = -1;
	if (NULL != pDCRunningTime->pIDeviceController)
	{
		hResult = pDCRunningTime->pIDeviceController->CallDC(strMethod, strParams);
	}

	return hResult;
}

long CancelAsyncRequest(char * strDCName)
{
	printf("<DC> CancelAsyncRequest %s\n", strDCName);

	map<CString, PDCRUNNINGTIME>::iterator iter;
	iter = m_mapPtrIDeviceController.find(strDCName);

	PDCRUNNINGTIME pDCRunningTime = NULL;
	// if (NULL == m_pIDeviceController)
	if (m_mapPtrIDeviceController.end() == iter)
	{
		printf("<DC> CancelAsyncRequest NULL == pIDeviceController >>>\n");
		return -1;
	}
	else
	{
		pDCRunningTime = iter->second;
	}

	if (NULL != pDCRunningTime->pIDeviceController)
	{
		return pDCRunningTime->pIDeviceController->CancelAsyncRequest();
	}

	return -1;
}

BOOL IsBlocking(char * strDCName)
{
	printf("<DC> IsBlocking %s\n", strDCName);

	map<CString, PDCRUNNINGTIME>::iterator iter;
	iter = m_mapPtrIDeviceController.find(strDCName);

	PDCRUNNINGTIME pDCRunningTime = NULL;
	// if (NULL == m_pIDeviceController)
	if (m_mapPtrIDeviceController.end() == iter)
	{
		printf("<DC> IsBlocking NULL == pIDeviceController >>>\n");
		return -1;
	}
	else
	{
		pDCRunningTime = iter->second;
	}

	if (NULL != pDCRunningTime->pIDeviceController)
	{
		return pDCRunningTime->pIDeviceController->IsBlocking();
	}

	return -1;
}

int WriteTrace(LPCTSTR strTraceComponent, LPCTSTR lpszOperation, LPCTSTR lpszTrace)
{
	printf("DC WriteTrace\n");

	struct timeval tv;
	gettimeofday(&tv, NULL);

	time_t t;
	t = time(NULL);
	struct tm *n = localtime(&t);

	char * szLogBuff = new char[strlen(lpszTrace) + 256];
	memset(szLogBuff, 0, strlen(lpszTrace) + 256);
	sprintf(szLogBuff,
		"%-8s "
		"%04d-%02d-%02d "
		"%02d:%02d:%02d.%03d "
		"%-12s "
		"%s\r\n\r\n",
		strTraceComponent,
		n->tm_year + 1900, n->tm_mon + 1, n->tm_mday,
		n->tm_hour, n->tm_min, n->tm_sec, tv.tv_usec,
		lpszOperation,
		lpszTrace
	);

	char szTracePath[256] = { 0 };
	strcpy(szTracePath, "/SSA/Trace");
	if (access(szTracePath, 0) != 0)
	{
		mkdir(szTracePath, 0777);
	}

	sprintf(szTracePath, "%s/%04d%02d%02d",
		szTracePath, n->tm_year + 1900, n->tm_mon + 1, n->tm_mday);
	if (access(szTracePath, 0) != 0)
	{
		mkdir(szTracePath, 0777);
	}

	sprintf(szTracePath, "%s/DeviceController.jrn",
		szTracePath);

	printf("DC WriteTrace szTracePath : %s, strLog2Write : %s\n", szTracePath, szLogBuff);

	FILE *fp;
	if ((fp = fopen(szTracePath, "a+")) != NULL);
	{
		fseek(fp, 0, SEEK_END);
		fwrite(szLogBuff, strlen(szLogBuff), 1, fp);
		fflush(fp);
		fclose(fp);

		printf("DC WriteTrace end\n");
	}

	delete szLogBuff;
	szLogBuff = NULL;

	return 0;
}

PDCRUNNINGTIME CreateDC(LPCTSTR strDCName, LPCTSTR strServiceName, LPCTSTR strVersion)
{
	printf("<DC> CreateDC(%s, %s, %s)\n", strDCName, strServiceName, strVersion);

	IDC * pIDeviceController = NULL;
	PDCRUNNINGTIME pDCRunningTime = NULL;

	char * pTraceComponent = NULL;

	// 读卡器
	if (0 == strnicmp(strDCName, "DCCardReader", strlen("DCCardReader")))
	{
		printf("<DC> m_lpszTraceComponent = %s\n", CardReader);

		pTraceComponent = CardReader;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			printf("<DC> new CDCCardReader_30 >>>\n");
			pIDeviceController = new CDCCardReader_30(strDCName, pTraceComponent);
			printf("<DC> new CDCCardReader_30 <<<\n");
		}
	}
	// IC读卡器
	else if (0 == strnicmp(strDCName, "DCChipCardReader", strlen("DCChipCardReader")))
	{
		pTraceComponent = ChipCardReader;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCCardReader_30(strDCName, pTraceComponent);
		}
	}
	// 非接IC读卡器
	else if (0 == strnicmp(strDCName, "DCRFChipCardReader", strlen("DCRFChipCardReader")))
	{
		pTraceComponent = RFChipCardReader;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCCardReader_30(strDCName, pTraceComponent);
		}
	}
	// 身份证
	else if (0 == strnicmp(strDCName, "DCIDCardReader", strlen("DCIDCardReader")))
	{
		pTraceComponent = IDCardReader;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCCardReader_30(strDCName, pTraceComponent);
		}
	}
	// UKey条码阅读器
	else if (0 == strnicmp(strDCName, "DCUKeyReader", strlen("DCUKeyReader")))
	{
		pTraceComponent = UKeyReader;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCCardReader_30(strDCName, pTraceComponent);
		}
	}
	// 密码键盘
	else if (0 == strnicmp(strDCName, "DCPinPad", strlen("DCPinPad")))
	{
		pTraceComponent = Encryptor;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			// 硬加密
			pIDeviceController = new CDCPinPad_30(strDCName, pTraceComponent);
		}
		/*  // Linux下暂时不支持EDS
		else if (-1 != CString(strVersion).find("EDS30"))
		{
			// 软加密
			m_pIDeviceController = new CDCPinPad_30_EDS();
		}
		*/
	}
	// 流水打印机
	if (0 == strnicmp(strDCName, "DCJournalPrinter", strlen("DCJournalPrinter")))
	{
		pTraceComponent = JournalPrinter;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCPrinter_30(strDCName, pTraceComponent);
		}
	}
	// 凭条打印机
	else if (0 == strnicmp(strDCName, "DCReceiptPrinter", strlen("DCReceiptPrinter")))
	{
		pTraceComponent = ReceiptPrinter;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCPrinter_30(strDCName, pTraceComponent);
		}
	}
	// 存折打印机
	else if (0 == strnicmp(strDCName, "DCPassBookPrinter", strlen("DCPassBookPrinter")))
	{
		pTraceComponent = PassBookPrinter;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCPrinter_30(strDCName, pTraceComponent);
		}
	}
	// 对账单打印机
	else if (0 == strnicmp(strDCName, "DCStatementPrinter", strlen("DCStatementPrinter")))
	{
		pTraceComponent = StatementPrinter;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCPrinter_30(strDCName, pTraceComponent);
		}
	}
	// 发票打印机
	else if (0 == strnicmp(strDCName, "DCInvoicePrinter", strlen("DCInvoicePrinter")))
	{
		pTraceComponent = InvoicePrinter;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCPrinter_30(strDCName, pTraceComponent);
		}
	}
	// 文档打印机
	else if (0 == strnicmp(strDCName, "DCDocumentPrinter", strlen("DCDocumentPrinter")))
	{
		pTraceComponent = DocumentPrinter;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCPrinter_30(strDCName, pTraceComponent);
		}
	}
	// 文档回收
	else if (0 == strnicmp(strDCName, "DCDocumentRetractPrinter", strlen("DCDocumentRetractPrinter")))
	{
		pTraceComponent = DocumentRetractPrinter;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCPrinter_30(strDCName, pTraceComponent);
		}
	}
	// 指纹仪：基于打印机的指纹仪
	else if (0 == strnicmp(strDCName, "DCFingerPrinter", strlen("DCFingerPrinter")))
	{
		pTraceComponent = FingerPrinter;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCPrinter_30(strDCName, pTraceComponent);
		}
	}
	// 存款模块
	else if (0 == strnicmp(strDCName, "DCCashAcceptor", strlen("DCCashAcceptor")))
	{
		pTraceComponent = CashAcceptor;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCCashAcceptor_30(strDCName, pTraceComponent);
		}
	}
	// 取款模块
	else if (0 == strnicmp(strDCName, "DCCashDispenser", strlen("DCCashDispenser")))
	{
		pTraceComponent = CashDispenser;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCCashDispenser_30(strDCName, pTraceComponent);
		}
	}
	// 操作员面板
	else if (0 == strnicmp(strDCName, "DCOperatorPanel", strlen("DCOperatorPanel")))
	{
		pTraceComponent = OperatorPanel;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCPinPad_30(strDCName, pTraceComponent);
		}
	}
	// 传感器/指示灯
	else if (0 == strnicmp(strDCName, "DCSensorsAndIndicators", strlen("DCSensorsAndIndicators")))
	{
		pTraceComponent = SensorsAndIndicators;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCSensorsAndIndicators_30(strDCName, pTraceComponent);
		}
	}
	// 厂商模式
	/*  // Linux下暂时不支持厂商模式
	else if (0 == strnicmp(strDCName, "DCVendorMode", strlen("DCVendorMode")))
	{
		pTraceComponent = VendorMode;
		if (-1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCVendorMode_30(strDCName, pTraceComponent);
		}
	}
	//*/
	// 扫描仪
	/*  // Linux下暂时不支持扫描仪
	else if (0 == strnicmp(strDCName, "DCScanner", strlen("DCScanner")))
	{
		pTraceComponent = Scanner;
		if (-1 != CString(strVersion).find("XFS31"))
		{
			pIDeviceController = new CDCScanner_30(strDCName, pTraceComponent);
		}
	}
	//*/
	// 二维码
	/*  // Linux下暂时不支持二维码
	else if (0 == strnicmp(strDCName, "DCBarcode", strlen("DCBarcode")))
	{
		pTraceComponent = Barcode;
		if (-1 != CString(strVersion).find("XFS31"))
		{
			pIDeviceController = new CDCBarcode_31(strDCName, pTraceComponent);
		}
	}
	//*/
	// 发卡
	/*  // Linux下暂时不支持发卡
	else if (0 == strnicmp(strDCName, "DCCardDispenser", strlen("DCCardDispenser")))
	{
		pTraceComponent = CardDispenser;
		if (-1 != CString(strVersion).find("XFS31"))
		{
			pIDeviceController = new CDCCardDispenser_31(strDCName, pTraceComponent);
		}
	}
	//*/
	// 摄像头
	else if (0 == strnicmp(strDCName, "DCCamera", strlen("DCCamera")))
	{
		pTraceComponent = Camera;
		if (-1 != CString(strVersion).find("XFS31") || -1 != CString(strVersion).find("XFS30"))
		{
			pIDeviceController = new CDCCamera_31(strDCName, pTraceComponent);
		}
	}

	printf("<DC> new DC Object end\n");

	if (NULL == pIDeviceController)
	{
		printf("<DC> new DC Object failed\n");

		CString strTrace(strlen(strDCName) + 256, 0);
		sprintf((char *)strTrace.c_str(), "Invalid DCName(%s)", strDCName);
		WriteTrace("公共", XFSApiRtn, strTrace.c_str());
	}
	else
	{
		printf("<DC> new DC Object success\n");

		pDCRunningTime = new DCRUNNINGTIME();
		pDCRunningTime->pIDeviceController = pIDeviceController;
		pDCRunningTime->strTraceComponent = pTraceComponent;
	}
	return pDCRunningTime;
}

long OpenDC(LPCTSTR strDCName, LPCTSTR strServiceName, LPCTSTR strVersion, long dwVersionsRequired) 
{
	printf("<DC> OpenDC(%s, %s, %s, %ld)\n", strDCName, strServiceName, strVersion, dwVersionsRequired);

	map<CString, PDCRUNNINGTIME>::iterator iter;
	iter = m_mapPtrIDeviceController.find(strDCName);

	PDCRUNNINGTIME pDCRunningTime = NULL;
	// if (NULL == m_pIDeviceController)
	if (m_mapPtrIDeviceController.end() == iter)
	{
		printf("<DC> OpenDC NULL == m_pIDeviceController -> CreateDC >>>\n");
		pDCRunningTime = CreateDC(strDCName, strServiceName, strVersion);
		if (NULL == pDCRunningTime)
		{
			printf("<DC> OpenDC ret -999\n");
			return -999;
		}
		m_mapPtrIDeviceController.insert(std::pair<CString, PDCRUNNINGTIME>(strDCName, pDCRunningTime));
		printf("<DC> OpenDC NULL == m_pIDeviceController -> CreateDC <<<\n");
	}
	else
	{
		pDCRunningTime = iter->second;
	}

	if (NULL != pDCRunningTime->pIDeviceController)
	{
		printf("<DC> OpenDC execute\n");
		return pDCRunningTime->pIDeviceController->OpenDC(strServiceName, dwVersionsRequired);
	}

	printf("<DC> OpenDC ret -1\n");
	return -1;
}

long CloseDC(char * strDCName)
{
	printf("<DC> CloseDC\n");

	map<CString, PDCRUNNINGTIME>::iterator iter;
	iter = m_mapPtrIDeviceController.find(strDCName);

	PDCRUNNINGTIME pDCRunningTime = NULL;
	// if (NULL == m_pIDeviceController)
	if (m_mapPtrIDeviceController.end() == iter)
	{
		printf("<DC> IsBlocking NULL == pIDeviceController >>>\n");
		return -1;
	}
	else
	{
		pDCRunningTime = iter->second;
	}

	if (NULL != pDCRunningTime->pIDeviceController)
	{
		return pDCRunningTime->pIDeviceController->CloseDC();
	}

	return -1;
}

LPCTSTR GetStringSplitChar()
{
	if ("" == m_strStringSplitChar)
	{
		m_strStringSplitChar = ";";
	}

	return m_strStringSplitChar.c_str();
}

/*
LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message>WM_USER)
	{
		if (m_pIDeviceController)
		{
			m_pIDeviceController->OnDCMessage(message, wParam, lParam);
		}

		return 0;
	}
	else
	{
		return COleControl::WindowProc(message, wParam, lParam);
	}
}
//*/

void SetDCCallbackFunc(PFDCCALLBACKFUNC lpFunc)
{
	m_lpDCCallbackFunc = lpFunc;
}

void FireDCEvent(CString m_strDCName, long messageid, CString wfsresult)
{
	if (NULL != m_lpDCCallbackFunc)
	{
		m_lpDCCallbackFunc(m_strDCName, messageid, wfsresult);
	}
}

long OnXFSManagerMessage(char * strDCName, long nMessageID, long nPtrWfsRet)
{
	printf("onManagerMessage(%s, %ld, %ld)\n", strDCName, nMessageID, nPtrWfsRet);

	// 从map中找，不能直接 m_mapPtrIDeviceController.find(strDCName);，因为 strDCName 是从DBUS路径中截取出来的，不带 "_30"、"_31"之类的后缀，但m_mapPtrIDeviceController中的key是带后缀的
	PDCRUNNINGTIME pDCRunningTime = NULL;
	map<CString, PDCRUNNINGTIME>::iterator iter = m_mapPtrIDeviceController.begin();
	while (iter != m_mapPtrIDeviceController.end())
	{
		if (string::npos != iter->first.find(strDCName))
		{
			pDCRunningTime = iter->second;
		}

		iter ++;
	}
	
	if (NULL == pDCRunningTime)
	{
		printf("<DC> OnXFSManagerMessage NULL == pDCRunningTime >>>\n");
		return -1;
	}

	if (nMessageID > WM_USER)
	{
		printf("onManagerMessage 1\n");
		if (pDCRunningTime->pIDeviceController)
		{
			printf("onManagerMessage 2\n");
			pDCRunningTime->pIDeviceController->OnDCMessage(nMessageID, 0, nPtrWfsRet);
			printf("onManagerMessage 3\n");
		}

		return 0;
	}

	printf("onManagerMessage 4\n");
	return -1;
}