// Base64.cpp: implementation of the CKeyou class.
//
//////////////////////////////////////////////////////////////////////
#include "Keyou.h"

#include<stdio.h>      /*��׼�����������*/    
#include<stdlib.h>     /*��׼�����ⶨ��*/    
#include<unistd.h>     /*Unix ��׼��������*/    
#include<sys/types.h>     
#include<sys/stat.h>       
#include<fcntl.h>      /*�ļ����ƶ���*/    
#include<termios.h>    /*PPSIX �ն˿��ƶ���*/    
#include<errno.h>      /*����Ŷ���*/    

#include "Utils.h"
#include "KDMexp.h"
#include "MessageHandle.h"
#include <unistd.h>
#include <pthread.h>
#include <dlfcn.h>
#include <mutex>

extern struct session_data session_data4send;
extern std::mutex mtx_session_data4send;  // WebSocket�ĻỰuser_session���շ�ʱ���ܳ�ͻ�����͵���ʹ�÷��ͽṹ����ʹ�û���������
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

	m_hKeyouDll = dlopen("/SSA/DC/KdmExp.so", RTLD_LAZY);        // load ���� so
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

	/*  tcgetattr(fd,&options)�õ���fdָ��������ز������������Ǳ�����options,�ú��������Բ��������Ƿ���ȷ��
		�ô����Ƿ���õȡ������óɹ�����������ֵΪ0��������ʧ�ܣ���������ֵΪ1.  */
	if (tcgetattr(fd, &options) != 0)
	{
		printf("UART0_Set failed: %s\n", strCom);
		perror("tcgetattr failed 1");
		return-1;
	}

	//���ô������벨���ʺ����������    
	for (i = 0; i < (int)(sizeof(speed_arr) / sizeof(int)); i++)
	{
		if (speed == name_arr[i])
		{
			cfsetispeed(&options, speed_arr[i]);
			cfsetospeed(&options, speed_arr[i]);
		}
	}

	//�޸Ŀ���ģʽ����֤���򲻻�ռ�ô���    
	options.c_cflag |= CLOCAL;
	//�޸Ŀ���ģʽ��ʹ���ܹ��Ӵ����ж�ȡ��������    
	options.c_cflag |= CREAD;

	//��������������    
	switch (flow_ctrl)
	{

	case 0://��ʹ��������    
		options.c_cflag &= ~CRTSCTS;
		break;

	case 1://ʹ��Ӳ��������    
		options.c_cflag |= CRTSCTS;
		break;
	case 2://ʹ������������    
		options.c_cflag |= IXON | IXOFF | IXANY;
		break;
	}
	//��������λ    
	//����������־λ    
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
	//����У��λ    
	switch (parity)
	{
	case 'n':
	case 'N': //����żУ��λ��    
		options.c_cflag &= ~PARENB;
		options.c_iflag &= ~INPCK;
		break;
	case 'o':
	case 'O'://����Ϊ��У��        
		options.c_cflag |= (PARODD | PARENB);
		options.c_iflag |= INPCK;
		break;
	case 'e':
	case 'E'://����ΪżУ��      
		options.c_cflag |= PARENB;
		options.c_cflag &= ~PARODD;
		options.c_iflag |= INPCK;
		break;
	case 's':
	case 'S': //����Ϊ�ո�     
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		break;
	default:
		printf("unsupport parity:%c, %s\n", parity, strCom);
		return -1;
	}
	// ����ֹͣλ     
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

	//�޸����ģʽ��ԭʼ�������    
	options.c_oflag &= ~OPOST;

	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	//options.c_lflag &= ~(ISIG | ICANON);    

	//���õȴ�ʱ�����С�����ַ�    
	options.c_cc[VTIME] = 1; /* ��ȡһ���ַ��ȴ�1*(1/10)s */
	options.c_cc[VMIN] = 1; /* ��ȡ�ַ������ٸ���Ϊ1 */

	//�����������������������ݣ����ǲ��ٶ�ȡ ˢ���յ������ݵ��ǲ���    
	tcflush(fd, TCIFLUSH);

	//�������� (���޸ĺ��termios�������õ������У�    
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

	// ����������ӵ���Կ�ַ����Ķ˿ں�
	m_bEnd = false;
	memset(m_strCom, 0, sizeof(m_strCom));

	// ����豸
	int hCom = -1;
	char strCom[64] = { 0 };

	for (int nLoop = 11; nLoop <= nMaxPortNum; nLoop++)
	{
		memset(strCom, 0, sizeof(strCom));
		sprintf(strCom, "/dev/ttyS%d", nLoop);

		hCom = open(strCom, O_RDWR | O_NOCTTY | O_NDELAY);
		if (hCom < 0) //9000			
		{
			// �򿪴���ʧ��
			printf("open com failed: %s\n", strCom);

			continue;
		}
		
		//���ô�������֡��ʽ    
		if (UART0_Set(hCom, KEYOU_PORT_BAUD, 0, 8, 1, 'N', strCom) == -1)
		{
			continue;
		}

		// ������ȡ�߳�
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
	while (false == pParam->pThis->m_bEnd && ++nRetries < 120)  // ��ȴ�120��
	{
		int len = read(pParam->hCom, buff + nReceivedLen, sizeof(buff) - nReceivedLen);
		if (len > 0)
		{
			printf("GetSM4KeyThread(%s) data received, len: %d\n", pParam->strCom, len);
			nReceivedLen += len;

			// ��֪�������Ƿ��Ѿ����������Խ���������ܽ����ɹ���ֱ�ӽ���
			if (NULL != pParam->pThis->m_DispatchData)
			{
				if (1 == pParam->pThis->m_DispatchData(nReceivedLen, buff, szDeviceid, szDecryptedTMK))
				{
					// �����ɹ��������������ݶ�ȡ
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
			if ((strlen(szDeviceid) != 0 && strlen(szDeviceid) != 0)  // ǰ���Ѿ���������
				|| 1 == pParam->pThis->m_DispatchData(nReceivedLen, buff, szDeviceid, szDecryptedTMK))
			{
				// �����ɹ�
				pParam->pThis->m_bEnd = true;  // ���д����߳��˳�

				printf("find keyou com: %s\n", pParam->strCom);
				printf("DeviceID: %s\n", szDeviceid);
				// printf("Key value: %s\n", szDecryptedTMK);
				printf("Key value: len : %d\n", (int)strlen(szDecryptedTMK));

				// �ȶ��ն˺ţ��ն˺Ų�ƥ��ʱ�������������Ϊ�ɹ���������Կ�ַ������ܻ�ɾ������Կ��
				if (0 != strcmp(szDeviceid, pParam->strTermNum))
				{
					printf("DeviceID not match, local: %s, keyou: %s\n", pParam->strTermNum, szDeviceid);
				}

				// ���洮�ںţ����ں���������ɺ����������Ϣ
				memset(pParam->pThis->m_strCom, 0, sizeof(pParam->pThis->m_strCom));
				strcpy(pParam->pThis->m_strCom, pParam->strCom);

				// �ص�ҳ����ɷ���
				// ����JS����
				char strCallbackJs[1024] = { 0 };
				sprintf(strCallbackJs, "onGetSM4KeyComplete('%s', '%s')", szDeviceid, szDecryptedTMK);
				int nRetLen = strlen(strCallbackJs);

				// m_pRootWindow->GetBrowser()->GetMainFrame()->ExecuteJavaScript(strCallbackJs, m_pRootWindow->GetBrowser()->GetMainFrame()->GetURL(), 0);
				printf("mtx_session_data4send.lock ->\n");
				mtx_session_data4send.lock();  //���ķ��ͺ�����
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
				// ������Կ�ַ���������
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
	strcpy(format_time_string, time_string + 2);  // ȥ�����ǰ��λ

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

	// ���´򿪴��ڶ˿�
	int hCom = open(m_strCom, O_RDWR | O_NOCTTY | O_NDELAY);
	if (hCom < 0) //9000
	{
		// �򿪴���ʧ��
		printf("open com failed(CompleteKey): %s\n", m_strCom);

		return -1;
	}

	//���ô�������֡��ʽ    
	if (UART0_Set(hCom, KEYOU_PORT_BAUD, 0, 8, 1, 'N', m_strCom) == -1)
	{
		close(hCom);
		return -1;
	}

	// ������Կ�ַ�����Ӧ����
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
