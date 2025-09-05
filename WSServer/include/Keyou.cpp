// Base64.cpp: implementation of the CKeyou class.
//
//////////////////////////////////////////////////////////////////////
#include "Keyou.h"

#include<stdio.h>      /*标准输入输出定义*/    
#include<stdlib.h>     /*标准函数库定义*/    
#include<unistd.h>     /*Unix 标准函数定义*/    
#include<sys/types.h>     
#include<sys/stat.h>       
#include<fcntl.h>      /*文件控制定义*/    
#include<termios.h>    /*PPSIX 终端控制定义*/    
#include<errno.h>      /*错误号定义*/    

#include "Utils.h"
#include "KDMexp.h"
#include "../MessageHandle.h"
#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>
#include <mutex>

extern struct session_data session_data4send;
extern std::mutex mtx_session_data4send;  // WebSocket的会话user_session在收发时可能冲突，发送单独使用发送结构，并使用互斥锁控制
extern MessageHandle messagehandle;

CKeyou * CKeyou::m_pInstance = nullptr;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

typedef struct _GETKEYTHREADPARAM
{
	char strCom[64];
	int hCom;
	char strTermNum[64];
	CKeyou * pThis;
	string strSessionName;
} GETKEYTHREADPARAM, *PGETKEYTHREADPARAM;

//##ModelId=48C787640067
CKeyou::CKeyou()
{
	m_bEnd = true;
	memset(m_strCom, 0, sizeof(m_strCom));

	m_DispatchData = NULL;
	m_AssembleMsg = NULL;

	m_hKeyouDll = dlopen("/SSA/DC/KdmExp.so", RTLD_LAZY);        // load 科友 so
	if (m_hKeyouDll == NULL)
	{
		printf("Load Keyou(/SSA/DC/KdmExp.so) failed : %s\n", dlerror());
		return;
	}
	printf("LoadXLoad KeyouFS(/SSA/DC/KdmExp.so) success\n");

	m_DispatchData = (PFDISPATCHDATA)dlsym(m_hKeyouDll, "dispatchData");
	if (!m_DispatchData)
	{
		printf("Load Keyou Function(dispatchData) failed : %s\n", dlerror());
		return;
	}

	m_AssembleMsg = (PFASSEMBLEMSG)dlsym(m_hKeyouDll, "assembleMsg");
	if (!m_AssembleMsg)
	{
		printf("Load Keyou Function(assembleMsg) failed : %s\n", dlerror());
		return;
	}
}

//##ModelId=48C787640068
CKeyou::~CKeyou()
{
}

/////////////////////////////////////////////////////////////////////////////
// CKeyou message handlers

int UART0_Set(int fd, int speed, int flow_ctrl, int databits, int stopbits, int parity, char * strCom)
{
	int   i;
	int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300 };
	int   name_arr[] = { 115200,  19200,  9600,  4800,  2400,  1200,  300 };

	struct termios options;

	/*  tcgetattr(fd,&options)得到与fd指向对象的相关参数，并将它们保存于options,该函数还可以测试配置是否正确，
		该串口是否可用等。若调用成功，函数返回值为0，若调用失败，函数返回值为1.  */
	if (tcgetattr(fd, &options) != 0)
	{
		printf("UART0_Set failed: %s\n", strCom);
		perror("tcgetattr failed 1");
		return-1;
	}

	//设置串口输入波特率和输出波特率    
	for (i = 0; i < (int)(sizeof(speed_arr) / sizeof(int)); i++)
	{
		if (speed == name_arr[i])
		{
			cfsetispeed(&options, speed_arr[i]);
			cfsetospeed(&options, speed_arr[i]);
		}
	}

	//修改控制模式，保证程序不会占用串口    
	options.c_cflag |= CLOCAL;
	//修改控制模式，使得能够从串口中读取输入数据    
	options.c_cflag |= CREAD;

	//设置数据流控制    
	switch (flow_ctrl)
	{

	case 0://不使用流控制    
		options.c_cflag &= ~CRTSCTS;
		break;

	case 1://使用硬件流控制    
		options.c_cflag |= CRTSCTS;
		break;
	case 2://使用软件流控制    
		options.c_cflag |= IXON | IXOFF | IXANY;
		break;
	}
	//设置数据位    
	//屏蔽其他标志位    
	options.c_cflag &= ~CSIZE;
	switch (databits)
	{
	case 5:
		options.c_cflag |= CS5;
		break;
	case 6:
		options.c_cflag |= CS6;
		break;
	case 7:
		options.c_cflag |= CS7;
		break;
	case 8:
		options.c_cflag |= CS8;
		break;
	default:
		printf("unsupport databits:%d, %s\n", databits, strCom);
		return -1;
	}
	//设置校验位    
	switch (parity)
	{
	case 'n':
	case 'N': //无奇偶校验位。    
		options.c_cflag &= ~PARENB;
		options.c_iflag &= ~INPCK;
		break;
	case 'o':
	case 'O'://设置为奇校验        
		options.c_cflag |= (PARODD | PARENB);
		options.c_iflag |= INPCK;
		break;
	case 'e':
	case 'E'://设置为偶校验      
		options.c_cflag |= PARENB;
		options.c_cflag &= ~PARODD;
		options.c_iflag |= INPCK;
		break;
	case 's':
	case 'S': //设置为空格     
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		break;
	default:
		printf("unsupport parity:%c, %s\n", parity, strCom);
		return -1;
	}
	// 设置停止位     
	switch (stopbits)
	{
	case 1:
		options.c_cflag &= ~CSTOPB; break;
	case 2:
		options.c_cflag |= CSTOPB; break;
	default:
		printf("unsupport stopbits:%d, %s\n", stopbits, strCom);
		return -1;
	}

	//修改输出模式，原始数据输出    
	options.c_oflag &= ~OPOST;

	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	//options.c_lflag &= ~(ISIG | ICANON);    

	//设置等待时间和最小接收字符    
	options.c_cc[VTIME] = 1; /* 读取一个字符等待1*(1/10)s */
	options.c_cc[VMIN] = 1; /* 读取字符的最少个数为1 */

	//如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读    
	tcflush(fd, TCIFLUSH);

	//激活配置 (将修改后的termios数据设置到串口中）    
	if (tcsetattr(fd, TCSANOW, &options) != 0)
	{
		printf("UART0_Set failed: %s\n", strCom);
		perror("tcsetattr failed!");
		return -1;
	}
	return 0;
}

// int   name_arr[] = { 115200,  19200,  9600,  4800,  2400,  1200,  300 };
#define KEYOU_PORT_BAUD	(115200)
short CKeyou::GetSM4Key(string strSessionName, int nMaxPortNum, char * strTermNum)
{
	printf("GetComPort(long nMaxPortNum : %d, strTermNum : %s)\n", nMaxPortNum, strTermNum);

	// 清除保存连接到密钥分发器的端口号
	m_bEnd = false;
	memset(m_strCom, 0, sizeof(m_strCom));

	// 检测设备
	int hCom = -1;
	char strCom[64] = { 0 };

	for (int nLoop = 11; nLoop <= nMaxPortNum; nLoop++)
	{
		memset(strCom, 0, sizeof(strCom));
		sprintf(strCom, "/dev/ttyS%d", nLoop);

		hCom = open(strCom, O_RDWR | O_NOCTTY | O_NDELAY);
		if (hCom < 0) //9000			
		{
			// 打开串口失败
			printf("open com failed: %s\n", strCom);

			continue;
		}
		
		//设置串口数据帧格式    
		if (UART0_Set(hCom, KEYOU_PORT_BAUD, 0, 8, 1, 'N', strCom) == -1)
		{
			continue;
		}

		// 启动读取线程
		PGETKEYTHREADPARAM pParam = new GETKEYTHREADPARAM();
		memset(pParam, 0, sizeof(GETKEYTHREADPARAM));
		strcpy(pParam->strCom, strCom);
		pParam->hCom = hCom;
		strcpy(pParam->strTermNum, strTermNum);
		pParam->pThis = this;
		pParam->strSessionName = strSessionName;

		pthread_t dwThreadID = 0;
		pthread_create(&dwThreadID, NULL, GetSM4KeyThread, (void *)pParam);
	}

	return 0;
}

void * CKeyou::GetSM4KeyThread(void * lpParam)
{
	PGETKEYTHREADPARAM pParam = (PGETKEYTHREADPARAM)lpParam;

	printf("GetSM4KeyThread started : %s\n", pParam->strCom);

	unsigned char buff[1024] = { 0 };
	char szDeviceid[64] = { 0 };
	char szDecryptedTMK[128] = { 0 };

	int nReceivedLen = 0;
	int nRetries = 0;
	while (false == pParam->pThis->m_bEnd && ++nRetries < 120)  // 最长等待120秒
	{
		int len = read(pParam->hCom, buff + nReceivedLen, sizeof(buff) - nReceivedLen);
		if (len > 0)
		{
			printf("GetSM4KeyThread(%s) data received, len: %d\n", pParam->strCom, len);
			nReceivedLen += len;

			// 不知道数据是否已经结束，尝试解析，如果能解析成功则直接结束
			if (NULL != pParam->pThis->m_DispatchData)
			{
				if (1 == pParam->pThis->m_DispatchData(nReceivedLen, buff, szDeviceid, szDecryptedTMK))
				{
					// 处理成功，结束串口数据读取
					break ;
				}
			}
		}
		else
		{
			printf("GetSM4KeyThread read : %d, %s\n", len, pParam->strCom);
			sleep(1);
		}
	}

	printf("GetSM4KeyThread(%s) receive data end, total len: %d\n", pParam->strCom, nReceivedLen);

	if (nReceivedLen > 0)
	{
		if (NULL != pParam->pThis->m_DispatchData)
		{
			if ((strlen(szDeviceid) != 0 && strlen(szDeviceid) != 0)  // 前面已经解析过了
				|| 1 == pParam->pThis->m_DispatchData(nReceivedLen, buff, szDeviceid, szDecryptedTMK))
			{
				// 处理成功
				pParam->pThis->m_bEnd = true;  // 所有串口线程退出

				printf("find keyou com: %s\n", pParam->strCom);
				printf("DeviceID: %s\n", szDeviceid);
				// printf("Key value: %s\n", szDecryptedTMK);
				printf("Key value: len : %d\n", (int)strlen(szDecryptedTMK));

				// 比对终端号，终端号不匹配时后续不允许标记为成功导出（密钥分发器可能会删除该密钥）
				if (0 != strcmp(szDeviceid, pParam->strTermNum))
				{
					printf("DeviceID not match, local: %s, keyou: %s\n", pParam->strTermNum, szDeviceid);
				}

				// 保存串口号，用于后续处理完成后设置完成信息
				memset(pParam->pThis->m_strCom, 0, sizeof(pParam->pThis->m_strCom));
				strcpy(pParam->pThis->m_strCom, pParam->strCom);

				// 回调页面完成方法
				// 调用JS处理
				char strCallbackJs[1024] = { 0 };
				sprintf(strCallbackJs, "onGetSM4KeyComplete('%s', '%s')", szDeviceid, szDecryptedTMK);
				int nRetLen = strlen(strCallbackJs);

				// m_pRootWindow->GetBrowser()->GetMainFrame()->ExecuteJavaScript(strCallbackJs, m_pRootWindow->GetBrowser()->GetMainFrame()->GetURL(), 0);
				printf("mtx_session_data4send.lock ->\n");
				mtx_session_data4send.lock();  //报文发送后会解锁
				printf("mtx_session_data4send.lock <-\n");
				memset(session_data4send.buf, 0, sizeof(session_data4send.buf));
				memcpy(&session_data4send.buf[LWS_PRE], strCallbackJs, nRetLen);
				session_data4send.len = nRetLen;

				struct lws * wsi_session = messagehandle.GetSession(pParam->strSessionName);
				if (nullptr != wsi_session)
				{
					lws_write(wsi_session, &session_data4send.buf[LWS_PRE], session_data4send.len, LWS_WRITE_TEXT);
				}
				else
				{
					printf("GetSession failed, strSessionName : %s\n", pParam->strSessionName.c_str());
				}
				mtx_session_data4send.unlock();
			}
			else
			{
				// 不是密钥分发器的数据
				printf("not keyou com: %s\n", pParam->strCom);
			}
		}
		else
		{
			printf("NULL == DispatchData: %s\n", pParam->strCom);
		}
	}
	else
	{
		printf("no data: %s\n", pParam->strCom);
	}

	close(pParam->hCom);
	delete pParam;

	return 0;
}

short CKeyou::CancelGetKey()
{
	m_bEnd = true;

	return 0;
}

short CKeyou::CompleteKey(int nResult)
{
	if (strlen(m_strCom) <= 0)
	{
		printf("no keyou com\n");
		return -1;
	}

	struct timeval tv;
	gettimeofday(&tv, NULL);

	struct tm* ptm;
	char time_string[64] = { 0 };
	ptm = localtime(&(tv.tv_sec));

	strftime(time_string, sizeof(time_string), "%Y%m%d%H%M%S", ptm);

	char format_time_string[64] = { 0 };
	strcpy(format_time_string, time_string + 2);  // 去掉年份前两位

	unsigned char szResponse[1024] = { 0 };
	int nResponseLen = 0;
	if (NULL != m_AssembleMsg)
	{
		nResponseLen = m_AssembleMsg(nResult, strlen(format_time_string), (unsigned char *)format_time_string, szResponse);
	}

	if (nResponseLen > 0)
	{
		printf("AssembleMsg succ, len:%d, data: %s\n", nResponseLen, szResponse);
	}
	else
	{
		printf("AssembleMsg failed\n");
	}

	// 重新打开串口端口
	int hCom = open(m_strCom, O_RDWR | O_NOCTTY | O_NDELAY);
	if (hCom < 0) //9000
	{
		// 打开串口失败
		printf("open com failed(CompleteKey): %s\n", m_strCom);

		return -1;
	}

	//设置串口数据帧格式    
	if (UART0_Set(hCom, KEYOU_PORT_BAUD, 0, 8, 1, 'N', m_strCom) == -1)
	{
		close(hCom);
		return -1;
	}

	// 发送密钥分发器响应报文
	ssize_t nwritten = 0;
	if ((nwritten = write(hCom, szResponse, nResponseLen)) > 0)
	{
		printf("send keyou result succ, data len:%ld\n", nwritten);
	}
	else
	{
		printf("send keyou result failed\n");
		close(hCom);
		return -1;
	}

	close(hCom);
	return 0;
}
