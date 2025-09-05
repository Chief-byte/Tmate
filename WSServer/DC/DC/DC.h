#if !defined(AFX_DCCTL_H__4D2BC854_B726_445E_AF4C_5E8E0825F819__INCLUDED_)
#define AFX_DCCTL_H__4D2BC854_B726_445E_AF4C_5E8E0825F819__INCLUDED_

#include "IDC.h"

extern IDC * m_pIDeviceController;

extern HMODULE m_hDCTraceMod;
extern CString m_strStringSplitChar;

// 保存以DCName为Key的指向模块对象的指针
typedef struct _DCRUNNINGTIME
{
	IDC * pIDeviceController;
	CString strTraceComponent;
}DCRUNNINGTIME, * PDCRUNNINGTIME;
extern std::map<CString, PDCRUNNINGTIME> m_mapPtrIDeviceController;

LPCTSTR GetStringSplitChar();

PDCRUNNINGTIME CreateDC(LPCTSTR strDCName, LPCTSTR strServiceName, LPCTSTR strVersion);

// LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
void FireDCEvent(CString m_strDCName, long messageid, CString wfsresult);

typedef void(*PFDCCALLBACKFUNC)(CString m_strDCName, long messageid, CString wfsresult);
extern PFDCCALLBACKFUNC m_lpDCCallbackFunc;

extern std::string & replace_all_distinct(std::string & str, const std::string & old_value, const std::string & new_value);

extern "C"
{
	__attribute__((visibility("default"))) HRESULT CallDC(char * strDCName, LPCTSTR strMethod, LPCTSTR strParams);
	__attribute__((visibility("default"))) long CancelAsyncRequest(char * strDCName);
	__attribute__((visibility("default"))) BOOL IsBlocking(char * strDCName);
	__attribute__((visibility("default"))) long OpenDC(LPCTSTR strDCName, LPCTSTR strServiceName, LPCTSTR strVersion, long dwVersionsRequired);
	__attribute__((visibility("default"))) long CloseDC(char * strDCName);
	__attribute__((visibility("default"))) long OnXFSManagerMessage(char * strDCName, long nMessageID, long nPtrWfsRet);
	__attribute__((visibility("default"))) void SetDCCallbackFunc(PFDCCALLBACKFUNC lpFunc);
	__attribute__((visibility("default"))) int WriteTrace(LPCTSTR strTraceComponent, LPCTSTR lpszOperation, LPCTSTR lpszTrace);
}

// 控制文件大小
extern char __szUnuseful[];

#endif // !defined(AFX_DCCTL_H__4D2BC854_B726_445E_AF4C_5E8E0825F819__INCLUDED_)
