// TraceSM.h: interface for the CTraceSMServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACESM_H__61F3C906_17F7_42D3_A2AF_B7B425BC338B__INCLUDED_)
#define AFX_TRACESM_H__61F3C906_17F7_42D3_A2AF_B7B425BC338B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

#ifdef PROTOCOL_PISA
#include "lfsapi.h"
#else
#include "lfsapi.h"
#endif

/*
 * 系统内的自定义错，和XFS返回的错误区别，可用范围-99(LFS_ERR_PTR_FORMNOTFOUND : -100) ~ -57(LFS_ERR_UNSUPP_DATA : -56)
 */
#define	DC_ERROR				(-99)

#define	CardReader				("读卡器\0")
#define	CardDispenser			("发卡器\0")
#define UKeyDispenser			("发UKey器\0")
#define ChipCardReader			("接触IC\0")
#define RFChipCardReader		("非接IC\0")
#define	IDCardReader			("身份证\0")
#define UKeyReader				("UKey条码阅读\0")
#define	CashAcceptor			("存款\0")
#define	CashDispenser			("取款\0")
#define	JournalPrinter			("流水")
#define	ReceiptPrinter			("凭条")
#define	StatementPrinter		("对账单")
#define	InvoicePrinter			("发票")
#define	PassBookPrinter			("存折")
#define	DocumentPrinter			("文档打印")
#define	DocumentRetractPrinter	("文档回收")
#define	Printer		            ("打印机")
#define	OperatorPanel			("面板")
#define	Encryptor				("键盘")
#define	SensorsAndIndicators	("灯传感器")
#define	GuideLights				("服务灯")
#define	VendorMode				("厂商模式")
#define UPS                     ("UPS")
#define Camera                  ("摄像头")
#define NFC						("近场通讯")
#define CheckReader				("票据")
#define Stamp					("盖章机")
#define TwoDimCode				("二维码")
#define CardRetainerBin			("退卡器")
#define Barcode					("条形码")
#define KeyLoader				("密钥分发器")
#define Scanner					("扫描仪")
#define FingerPrinter			("指纹仪")

#define	XFSApiRtn				("异步调用\0")
#define	XFSCmdMsg				("命令消息\0")
#define	XFSEvtMsg				("事件消息\0")
#define	XFSApiOpen				("打开模块\0")
#define	XFSApiStart				("环境启动\0")
#define	OCXGetInfo				("取状态\0")
#define	OCXCALL					("方法调用\0")
#define	OCXEVENT				("中间件事件\0")
#define	OCXRtn					("中间件返回\0")
#define	OCXGetProp				("取属性\0")
#define	OCXLoadLib				("加载动态库\0")


/*
// 直接在项目中实现
typedef int (* PFWRITETRACE)(LPCTSTR lpszComponent, LPCTSTR lpszOperation, LPCTSTR lpszTrace);
int WriteTrace(LPCTSTR lpszComponent, LPCTSTR lpszOperation, LPCTSTR lpszTrace);

typedef int (* PFFLUSHTRACE)();
int FlushTrace();
*/

#endif // !defined(AFX_TRACESM_H__61F3C906_17F7_42D3_A2AF_B7B425BC338B__INCLUDED_)
