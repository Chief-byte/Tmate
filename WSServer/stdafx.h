#if !defined(AFX_STDAFX_H__ACBDB5E2_29C5_4AB8_8DF0_B9CE3CB845C1__INCLUDED_)
#define AFX_STDAFX_H__ACBDB5E2_29C5_4AB8_8DF0_B9CE3CB845C1__INCLUDED_

#define PROTOCOL_PISA 1
// #define PROTOCOL_LFS 1

#include <list>
#include <string>
using namespace std;
#include <string.h>

#include <regex>

#define __float128	float
// #define LPCTSTR (char *)
// #define LPCSTR	const char *
// #define LPTSTR	(char *)
typedef char * LPTSTR;
// #define LPSTR	char *
typedef unsigned char BYTE;
typedef BYTE * PBYTE;
typedef char * PCHAR;
typedef char CHAR;
typedef short SHORT;

// #define HWND	long
// #define HRESULT	long
#define LRESULT	long
// #define HANDLE	void *

// #define UINT	unsigned int
// #define WPARAM	unsigned int
// #define LPARAM	long

// #define BOOL	bool
#define CString	string

#define HMODULE	long

// #define LPVOID	void *
#define WINAPI
// #define WORD	unsigned short
// #define DWORD	unsigned long
// #define LONG	long
// #define LPWORD	WORD *
// #define LPDWORD	DWORD *
// #define VOID	void
// #define SYSTEMTIME	time_t

typedef unsigned char       BYTE;
typedef BYTE *	LPBYTE;
// typedef time_t *	LPSYSTEMTIME;
// typedef SYSTEMTIME *	LPSYSTEMTIME;
// typedef unsigned short WCHAR;
typedef wchar_t WCHAR;
typedef WCHAR *LPWSTR, *PWSTR;

#define strnicmp	strncmp
#define stricmp		strcmp

#define WM_USER		0x0400
typedef list<string>	CStringArray;

// typedef LONG HRESULT;
// typedef HRESULT * LPHRESULT;


// ���������Ч�غ��ֽ���
#define MAX_PAYLOAD_SIZE  10 * 1024 * 1024

#include "libwebsockets.h"
/**
 * �Ự�����Ķ��󣬽ṹ������Ҫ�Զ���
 */
struct session_data {
	unsigned char buf[LWS_PRE + MAX_PAYLOAD_SIZE];
	int len;
};

// ���ӿ�
/*
websockets
pthread
dl
X11
xml2
nettle
dbus - 1
dbus - glib - 1
glib - 2.0
gtk - x11 - 2.0
gdk - x11 - 2.0
gmodule - 2.0
gthread - 2.0
gobject - 2.0
//*/
// ����Ϊ
/*
websockets
pthread
dl
X11
xml2
nettle
gmodule - 2.0
gthread - 2.0
gobject - 2.0
//*/

// VC++ Ŀ¼������Ŀ������ϵĴ����Ŀ¼�����磺
// /home/cfes/projects/WSServer

#endif // !defined(AFX_STDAFX_H__ACBDB5E2_29C5_4AB8_8DF0_B9CE3CB845C1__INCLUDED_)
