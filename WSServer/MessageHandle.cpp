#include "MessageHandle.h"
#include "stdafx.h"
#include "include/Utils.h"
#include "Extension/Extension.h"
#include "DC/DC/DC.h"
#include <mutex>

extern struct session_data session_data4send;
extern std::mutex mtx_session_data4send;  // WebSocket的会话user_session在收发时可能冲突，发送单独使用发送结构，并使用互斥锁控制
extern MessageHandle messagehandle;

std::string trim(const std::string &s)
{
	auto wsfront = s.find_first_not_of(' ');
	auto wsback = s.find_last_not_of(' ');
	return (wsback <= wsfront ? std::string() : s.substr(wsfront, (wsback - wsfront + 1)));
}

/*
从ssa.callDC和ssa.callExtension报文字符串中，截取参数字符串列表（各参数中分割使用 "^,^"，防止参数中字符串有","）
*/
CStringArray GetParamList(char * recvbuf)
{
	printf("GetParamList recvbuf(%d) : %s\n", strlen(recvbuf), recvbuf);
	CStringArray strarr;

	PCHAR pch_start = strstr(recvbuf, "(");
	PCHAR _pch_end = strstr(pch_start + 1, ")");
	PCHAR pch_end = _pch_end;
	while (NULL != _pch_end)
	{
		pch_end = _pch_end;

		_pch_end = strstr(_pch_end + 1, ")");
	}

	if (NULL == pch_end || NULL == pch_start || pch_end < pch_start)
	{
		printf("() not found or )( format\n");
		return strarr;
	}

	pch_start = pch_start + 1;
	*pch_end = '\0';

	printf("GetParamList pch_start : %s\n", pch_start);
	CUtils::SplitString(strarr, (LPSTR)pch_start, "^,^");

	// 去除参数列表中各项的前后空格
	list<string>::iterator iter;
	for (iter = strarr.begin(); iter != strarr.end(); iter++)
	{
		// 暂时不去，JS中传入的不应该带前后空格
	}

	return strarr;
}

// 中间件事件回调方法
void DCCallBackFunc(std::string strDCName, long messageid, std::string wfsresult)
{
	printf("DCCallBackFunc start\n");

	// 回调JS方法
	/*
	std::string strCallbackJs = std::string(strDCName.size() + wfsresult.size() + 1024, 0);
	sprintf((char *)strCallbackJs.c_str(), "onDCCallBack('%s', %ld, '%s')",
		(char *)strDCName.c_str(), messageid, (char *)wfsresult.c_str());
	int nRetLen = strlen(strCallbackJs.c_str());
	*/
	int nBuffLen = strDCName.size() + wfsresult.size() + 1024;
	char * strCallbackJs = new char[nBuffLen];
	memset(strCallbackJs, 0, nBuffLen);
	sprintf(strCallbackJs, "onDCCallBack('%s', %ld, '%s')",
		(char *)strDCName.c_str(), messageid, (char *)wfsresult.c_str());
	int nRetLen = strlen(strCallbackJs);

	printf("mtx_session_data4send.lock ->\n");
	mtx_session_data4send.lock();  //报文发送后会解锁
	printf("mtx_session_data4send.lock <-\n");
	memset(session_data4send.buf, 0, sizeof(session_data4send.buf));
	memcpy(&session_data4send.buf[LWS_PRE], strCallbackJs, nRetLen);
	session_data4send.len = nRetLen;

	struct lws * wsi_session = messagehandle.GetSession("SSApp");  // 中间件固定发送到SSApp的session连接
	if (nullptr != wsi_session)
	{
		lws_write(wsi_session, &session_data4send.buf[LWS_PRE], session_data4send.len, LWS_WRITE_TEXT);
	}
	else
	{
		printf("GetSession failed, strSessionName : %s\n", "SSApp");
	}
	mtx_session_data4send.unlock();

	delete strCallbackJs;
	strCallbackJs = nullptr;

	printf("DCCallBackFunc end\n");
}

extern void kbdms_open_dev();
void MessageHandle::Init()
{
	// 打开模拟键盘设备
	kbdms_open_dev();

	// 设置中间件事件的回调函数
	SetDCCallbackFunc(DCCallBackFunc);
}

struct lws * MessageHandle::GetSession(string strSessionName)
{
	map<string, struct lws *>::iterator iter = m_mapSession.find(strSessionName);

	if (m_mapSession.end() != iter)
	{
		return iter->second;
	}

	return nullptr;
}

string MessageHandle::GetSessionName(struct lws * wsi_session)
{
	map<string, struct lws *>::iterator iter = m_mapSession.begin();
	while (iter != m_mapSession.end())
	{
		if (wsi_session == iter->second)
		{
			return iter->first;
		}

		iter++;
	}

	return "";
}

void MessageHandle::SetSession(string strSessionName, struct lws * wsi_session)
{
	map<string, struct lws *>::iterator iter = m_mapSession.find(strSessionName);

	if (m_mapSession.end() == iter)
	{
		m_mapSession.insert(std::pair<string, struct lws *>(strSessionName, wsi_session));
	}
	else
	{
		iter->second = wsi_session;
	}
}

void MessageHandle::RemoveSession(struct lws * wsi_session)
{
	map<string, struct lws *>::iterator iter = m_mapSession.begin();
	while (iter != m_mapSession.end())
	{
		if (wsi_session == iter->second)
		{
			iter = m_mapSession.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

int MessageHandle::Process(char * recvbuf, size_t len1, struct lws *wsi, void *user)
{
	int nRet = -1;
	string strRet = "";

	printf("message handle start\n");
	
	// 接入的报文类型：
	// ssa.callDC
	// ssa.callExtension
	if (0 == strncmp((char *)recvbuf, "setSessionName", strlen("setSessionName")))
	{
		CStringArray strarr = GetParamList(recvbuf);
		if (strarr.size() >= 1) // 至少要有一个参数，SessionName
		{
			std::list<string>::iterator it = strarr.begin();
			string strSessionName = (*it);
			
			printf("strSessionName : %s\n", strSessionName.c_str());

			// 每次收到报文时都重新设置一次Session变量，一个WSServer应该只有一种类型的客户端连接，如果需要多种客户端连接，需要启动多个WSServer，否则Session数据会乱：
			// 一个WSServer同时有应用页面和监控页面连接时，Socket收到的报文不知道该通知哪个页面（因为是异步方式，不好区分）
			SetSession(strSessionName, wsi);

			nRet = 0;
		}
	}
	else if (0 == strncmp((char *)recvbuf, "ssa.callDC", strlen("ssa.callDC")))
	{
		CStringArray strarr = GetParamList(recvbuf);
		if (strarr.size() >= 2) // 至少要有两个参数，第一个是strDCName，第二个是strMethod
		{
			std::list<string>::iterator it = strarr.begin();
			string strDCName = (*it);

			std::advance(it, 1);
			string strMethod = (*it);
			if ("CancelAsyncRequest" == strMethod)
			{
				nRet = CancelAsyncRequest((char *)strDCName.c_str());
			}
			else if ("IsBlocking" == strMethod)
			{
				bool bRet = IsBlocking((char *)strDCName.c_str());
				strRet = (true == bRet ? "true" : "false");
				nRet = 0;
			}
			else if ("OpenDC" == strMethod && strarr.size() >= 5)
			{
				std::advance(it, 1);
				std::string strServiceName = (*it);
				std::advance(it, 1);
				std::string strVersion = (*it);
				std::advance(it, 1);
				long dwVersionsRequired = atol((*it).c_str());

				nRet = OpenDC((char *)strDCName.c_str(),  // strDCName
								(char *)strServiceName.c_str(),  // LPCTSTR strServiceName
								(char *)strVersion.c_str(), // LPCTSTR strVersion
								dwVersionsRequired);  // long dwVersionsRequired
			}
			else if ("CloseDC" == strMethod)
			{
				nRet = CloseDC((char *)strDCName.c_str());
			}
			else if ("WriteTrace" == strMethod && strarr.size() >= 5)
			{
				std::advance(it, 1);
				std::string strTraceComponent = (*it);
				std::advance(it, 1);
				std::string lpszOperation = (*it);
				std::advance(it, 1);
				std::string lpszTrace = (*it);

				nRet = WriteTrace((char *)strTraceComponent.c_str(),
									(char *)lpszOperation.c_str(),
									(char *)lpszTrace.c_str());
			}
			else if (strarr.size() >= 3)  // XFS 方法
			{
				std::advance(it, 1);
				std::string strParams = (*it);
				nRet = CallDC((char *)strDCName.c_str(),  // strDCName
									(char *)strMethod.c_str(),  // strMethod
									(char *)strParams.c_str());  // strParams
			}
			else  // XFS 方法
			{
				nRet = CallDC((char *)strDCName.c_str(),  // strDCName
					(char *)strMethod.c_str(),  // strMethod
					(char *)std::string("").c_str());  // strParams
			}

			printf("CallDC return, nRet : %d, strRet : %s\n", nRet, strRet.c_str());
		}
		else
		{
			printf("CallDC failed : invalid format\n");
		}
	}
	else if (0 == strncmp((char *)recvbuf, "ssa.callExtension", strlen("ssa.callExtension")))
	{
		CStringArray strarr = GetParamList(recvbuf);

		unsigned long nRequestId = 0;
		if (strarr.size() > 0)
		{
			// 第一个参数是请求ID，用于标记回调JS时回调到指定ID的回调
			nRequestId = atol(strarr.front().c_str());
			strarr.erase(strarr.begin());
		}

		if (strarr.size() > 0)
		{
			string strSessionName = GetSessionName(wsi);
			nRet = Extension::CallExtension(strSessionName, strarr, strRet);

			printf("CallExtension return, nRet : %d, strRet : %s\n", nRet, strRet.c_str());
		}
		else
		{
			printf("CallExtension failed : invalid format\n");
		}

		// 不论Extension::CallExtension处理与否或者结果，都回调
		strRet = replace_all_distinct(strRet, "\r", "&CR;");  // 回车，参照&nbsp;格式
		strRet = replace_all_distinct(strRet, "\n", "&LF;");  // 换行，参照&nbsp;格式

		int nLength = 1024 + strlen(strRet.c_str());
		printf("CallExtension nLength : %d\n", nLength);

		char * strCallbackJs = new char[nLength];
		memset(strCallbackJs, 0, nLength);
		sprintf(strCallbackJs, "onSSAReturn(%d, '%s')", nRequestId, strRet.c_str());
		int nRetLen = strlen(strCallbackJs);
		printf("CallExtension strlen(strCallbackJs) : %d\n", strlen(strCallbackJs));
		printf("CallExtension strCallbackJs : %s\n", strCallbackJs);

		printf("mtx_session_data4send.lock ->\n");
		mtx_session_data4send.lock();  //报文发送后会解锁
		printf("mtx_session_data4send.lock <-\n");
		memset(session_data4send.buf, 0, sizeof(session_data4send.buf));
		memcpy(&session_data4send.buf[LWS_PRE], strCallbackJs, nRetLen);
		session_data4send.len = nRetLen;

		lws_write(wsi, &session_data4send.buf[LWS_PRE], session_data4send.len, LWS_WRITE_TEXT);
		mtx_session_data4send.unlock();

		printf("CallExtension strlen(strCallbackJs) 2 : %d\n", strlen(strCallbackJs));
		delete strCallbackJs;
		strCallbackJs = nullptr;
	}
	else
	{
		
	}

	printf("message handle end\n");
	delete recvbuf;
	return nRet;
}