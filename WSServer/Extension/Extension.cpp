#include "Extension.h"

#include <map>
#include <string.h>  
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <linux/input.h>  
#include <linux/uinput.h>  
#include <sys/time.h>  
#include <unistd.h>  
#include <errno.h>
#include "libwebsockets.h"
#include <nettle/md5.h>

#include "FileHelper.h"
#include "Utils.h"
#include "xmlhelper.h"
#include "Keyou.h"
#include "SSMKeyou.h"
#include "MessageHandle.h"

#include <unistd.h>
#include <sys/reboot.h>
#include <linux/reboot.h>
#include <mutex>

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>

extern struct session_data session_data4send;
extern std::mutex mtx_session_data4send;  // WebSocket�ĻỰuser_session���շ�ʱ���ܳ�ͻ�����͵���ʹ�÷��ͽṹ����ʹ�û���������
extern MessageHandle messagehandle;

// �������û���ã�gtk_window_list_toplevelsֱ�ӷ���ʧ�ܣ��������õ�browser����uosbrowser
/*
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
GtkWindow* find_gtk_window_by_xid(Window _xid) {
	GList* windows = gtk_window_list_toplevels();
	int n = 0;
	for (GList* list = windows; list != nullptr; list = list->next) {
		GtkWindow *window = GTK_WINDOW(list->data);
        GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(window));
        if (gdk_window) {
            Window xid = GDK_WINDOW_XID(gdk_window);
            if (xid == _xid) {
				g_list_free(windows);
				return window;
            }
        }
	}
	g_list_free(windows);
	return nullptr;
}
//*/

int uinput_fd = -1;
struct uinput_user_dev uinput;
struct input_event event;

int kbdms_init_dev(char *dev) {
	int i = 0;
	if (dev == nullptr) {
		printf("The device is null\n");
		return -1;
	}
	uinput_fd = open(dev, O_WRONLY | O_NDELAY);
	if (uinput_fd < 0) {
		perror("open uinput device failure:");
		return -1;
	}
	memset(&uinput, 0, sizeof(uinput));
	strncpy(uinput.name, "xiangpeng's virtual device", UINPUT_MAX_NAME_SIZE);
	uinput.id.version = 4;
	uinput.id.bustype = BUS_USB;
	ioctl(uinput_fd, UI_SET_EVBIT, EV_KEY);

	for (i = 0; i < 256; i++) {
		ioctl(uinput_fd, UI_SET_KEYBIT, i);
	}
	/* Create input device into input sub-system */
	size_t n = write(uinput_fd, &uinput, sizeof(uinput));
	if (n > 0 && ioctl(uinput_fd, UI_DEV_CREATE)) {
		perror("create uinput device");
		return -1;
	}

	printf("call kbdms_init_dev ok\n");
	return 0;                     /* success */

}
void kbdms_close_dev(void) {
	if (uinput_fd > 0) {
		ioctl(uinput_fd, UI_DEV_DESTROY);
		close(uinput_fd);
	}
}

void kbdms_open_dev()
{
	if (uinput_fd > 0) {
		return;
	}

	int ret = -1;
	ret = kbdms_init_dev((char*)"/dev/uinput");
	if (ret < 0) {
		ret = kbdms_init_dev((char*)"/dev/input/uinput");
		if (ret < 0) {
			printf("call kbdms_open_dev failure\n");
			return;
		}
	}
	printf("call kbdms_open_dev ok\n");
}

void kbdms_send_button_event(unsigned short key_code) {

	if (uinput_fd <= 0)
	{
		printf("kbdms_send_button_event uinput_fd < 0\n");
		return;
	}

	printf("kbdms_send_button_event keycode : %d\n", key_code);

	struct input_event ev;
	memset(&ev, 0, sizeof(ev));
	// ģ�ⰴ��
	ev.type = EV_KEY;
	ev.code = key_code;
	ev.value = 1;
	if (write(uinput_fd, &ev, sizeof(ev)) < 0)
	{
		printf("kbdms_send_button_event faile\n");
	}

	// ͬ���¼�
	memset(&ev, 0, sizeof(ev));
	ev.type = EV_SYN;
	ev.code = SYN_REPORT;
	ev.value = 0;
	if (write(uinput_fd, &ev, sizeof(ev)) < 0)
	{
		printf("kbdms_send_button_event faile\n");
	}

	// ģ���ɿ�
	ev.type = EV_KEY;
	ev.code = key_code;
	ev.value = 0;
	if (write(uinput_fd, &ev, sizeof(ev)) < 0)
	{
		printf("kbdms_send_button_event faile\n");
	}

	// ͬ���¼�
	memset(&ev, 0, sizeof(ev));
	ev.type = EV_SYN;
	ev.code = SYN_REPORT;
	ev.value = 0;
	if (write(uinput_fd, &ev, sizeof(ev)) < 0)
	{
		printf("kbdms_send_button_event faile\n");
	}
}

void ShutdownLinux(int shutdown)
{
	if (1 == shutdown)
	{
		// reboot(LINUX_REBOOT_CMD_POWER_OFF);
		int nResult = reboot(LINUX_REBOOT_CMD_HALT);
		printf("reboot ret %d\n", nResult);
	}
	else if (0 == shutdown)
	{
		int nResult = reboot(LINUX_REBOOT_CMD_RESTART);
		printf("reboot ret %d\n", nResult);
	}
}

std::string GetAppHome()
{
	char path[1024] = { 0 };
	int cnt = readlink("/proc/self/exe", path, 1024);
	if (cnt < 0 || cnt >= 1024)
	{
		return "";
	}
	//���һ��'/' �����ǿ�ִ�г�������ȥ����ִ�г�������֣�ֻ����·��
	for (int i = cnt; i >= 0; --i)
	{
		if (path[i] == '/')
		{
			path[i + 1] = '\0';
			break;
		}
	}
	std::string s_path(path);
	return s_path;
}

std::string GetAppName()
{
	char path[1024] = { 0 };
	int cnt = readlink("/proc/self/exe", path, 1024);
	if (cnt < 0 || cnt >= 1024)
	{
		return "";
	}
	//���һ��'/' �����ǿ�ִ�г�������ȥ����ִ�г�������֣�ֻ����·��
	int i = 0;
	for (i = cnt; i >= 0; --i)
	{
		if (path[i] == '/')
		{
			break;
		}
	}
	std::string s_appname(path + i + 1);
	return s_appname;
}

#include <sys/socket.h>
#include <netinet/in.h>
struct socketthread_data
{
	string strSessionName;
	struct sockaddr_in client_addr;
	int sock_fd;
	std::string strSocketCallbackFunction = "";
};

// socket�����е�GBK��UTF-8֮���ת��
#include <iconv.h>
int code_convert(char *from_charset, char *to_charset, char *inbuf, int inlen, char *outbuf, int outlen)
{
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;

	size_t stinlen = inlen;
	size_t stoutlen = outlen;

	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
		return -1;
	memset(outbuf, 0, outlen);
	if ((int)iconv(cd, pin, &stinlen, pout, &stoutlen) == -1)
		return -1;
	iconv_close(cd);
	return 0;
}

int u2g(char *inbuf, int inlen, char *outbuf, int outlen)
{
	return code_convert((char*)"utf-8", (char*)"gb2312", inbuf, inlen, outbuf, outlen);
}

int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return code_convert((char*)"gb2312", (char*)"utf-8", inbuf, (int)inlen, outbuf, (int)outlen);
}

std::string & replace_all_distinct(std::string & str, const std::string & old_value, const std::string & new_value)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += strlen(new_value.c_str())) {
		if ((pos = str.find(old_value, pos)) != std::string::npos)
		{
			str.replace(pos, strlen(old_value.c_str()), new_value);
		}
		else
		{
			break;
		}
	}
	return str;
}

std::map<int, std::string> m_JSResultMap;
void * SocketThread(void *arg)
{
	struct socketthread_data * spdata = (struct socketthread_data *)arg;
	int client_fd = spdata->sock_fd;

	char * recvbuf = nullptr;
	char * newrecvbuf = nullptr;

	int nTotalLength = 0;

	char oncerecvbuf[100 * 1024] = { 0 };

	// �޸Ļ�������С
	int nSendRecvBuf = 80 * 1024;
	setsockopt(client_fd, SOL_SOCKET, SO_RCVBUF, (const char*)&nSendRecvBuf, sizeof(int));
	setsockopt(client_fd, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendRecvBuf, sizeof(int));

	bool bEnd = false;
	while (false == bEnd)
	{
		memset(oncerecvbuf, 0, sizeof(oncerecvbuf));
		int nLength = recv(client_fd, oncerecvbuf, sizeof(oncerecvbuf), 0);
		if (nLength > 0)
		{
			// ѭ����ȡ���ģ�ֱ�� \n ������Ϊֹ
			if (nullptr != strstr(oncerecvbuf, "\n"))
			{
				bEnd = true;
			}

			nTotalLength += nLength;

			newrecvbuf = new char[nTotalLength + 4];
			memset(newrecvbuf, 0, nTotalLength + 4);

			if (nullptr != recvbuf)
			{
				memcpy(newrecvbuf, recvbuf, nTotalLength - nLength);
			}
			memcpy(newrecvbuf + nTotalLength - nLength, oncerecvbuf, nLength);
			newrecvbuf[nTotalLength] = '\0';

			if (nullptr != recvbuf)
			{
				delete recvbuf;
			}
			recvbuf = newrecvbuf;
		}
		else if (nLength < 0)
		{
			break;
		}
	}

	if (nullptr != recvbuf)
	{
		printf("SocketThread message received : %s\n", recvbuf);
		int nulen = 2 * strlen(recvbuf) + 1024;
		char * pszRecvBuf = new char[nulen];
		memset(pszRecvBuf, 0, nulen);
		g2u(recvbuf, strlen(recvbuf), pszRecvBuf, nulen - 2);
		printf("g2u : %s\n", pszRecvBuf);

		// std::string strMessage = recvbuf;
		std::string strMessage = pszRecvBuf;
		delete recvbuf;

		strMessage = replace_all_distinct(strMessage, "\r", "");
		strMessage = replace_all_distinct(strMessage, "\n", "");
		strMessage = replace_all_distinct(strMessage, "'", "\\'");
		strMessage = replace_all_distinct(strMessage, "\\", "/");

		int nBuffLen = strMessage.size() + 256;
		char * strCallbackJs = new char[nBuffLen];
		memset(strCallbackJs, 0, nBuffLen);
		sprintf(strCallbackJs, "%s('%s', %d)",  // �ڶ�������ΪSocket����ţ�����JS�ص�������Ϣ
			spdata->strSocketCallbackFunction.c_str(), strMessage.c_str(), client_fd);
		int nRetLen = strlen(strCallbackJs);

		printf("SocketThread strCallbackJs : %s\n", strCallbackJs);

		printf("mtx_session_data4send.lock ->\n");
		mtx_session_data4send.lock();  //���ķ��ͺ�����
		printf("mtx_session_data4send.lock <-\n");
		memset(session_data4send.buf, 0, sizeof(session_data4send.buf));
		memcpy(&session_data4send.buf[LWS_PRE], strCallbackJs, nRetLen);
		session_data4send.len = nRetLen;

		struct lws * wsi_session = messagehandle.GetSession(spdata->strSessionName);
		if (nullptr != wsi_session)
		{
			lws_write(wsi_session, &session_data4send.buf[LWS_PRE], session_data4send.len, LWS_WRITE_TEXT);
		}
		else
		{
			printf("GetSession failed, strSessionName : %s\n", spdata->strSessionName.c_str());
		}
		mtx_session_data4send.unlock();

		delete strCallbackJs;
		strCallbackJs = nullptr;

		// �ȴ�JS�������
		int nTimeoutCount = 0;
		while (true && nTimeoutCount++ < 15 * 60)  // ����ס15����
		{
			std::map<int, std::string>::iterator iter = m_JSResultMap.find(client_fd);
			if (iter != m_JSResultMap.end())
			{
				// ����ת��
				// printf("socket message 2 send : %s, length : %d\n", iter->second.c_str(), (int)iter->second.size());
				
				string strMessage2Send = iter->second;
				printf("socket message 2 send : %d, length : %d\n", client_fd, (int)strMessage2Send.size());

				int nglen = strMessage2Send.size() + 1024;
				char * pszSndBuf = new char[nglen];
				memset(pszSndBuf, 0, nglen);
				u2g((char *)strMessage2Send.c_str(), strMessage2Send.size(), pszSndBuf, nglen - 2);
				printf("u2g : %s\n", pszSndBuf);

				int nSendLength = strlen(pszSndBuf);
				if (nSendLength > 0)
				{
					const char * pszResultStringBuffer = pszSndBuf;

					// ���͸���Ϊѭ������
					// send(client_fd, pszCodesetBuffer_send, strlen(pszCodesetBuffer_send), 0);
					int nSentTotal = nSendLength;  // ʣ��δ����
					int nSentCount = 0;  // �Ѿ�����
					int nSentOnce = 0;  // ���η���
					while (true)
					{
						nSentOnce = send(client_fd, pszResultStringBuffer + nSentCount, (nSentTotal > nSendRecvBuf ? nSendRecvBuf : nSentTotal), 0);
						if (nSentOnce < 0)
						{
							break;
						}

						nSentCount += nSentOnce;
						nSentTotal -= nSentOnce;

						if (nSentTotal <= 0)
						{
							break;
						}
					}
				}

				delete pszSndBuf;
				pszSndBuf = nullptr;

				m_JSResultMap.erase(iter);

				break;
			}

			sleep(1);
		}
	}

	close(client_fd);
	client_fd = 0;

	delete spdata;
	spdata = nullptr;

	pthread_exit(0);
}

struct acceptthread_data
{
	string strSessionName;
	std::string strSocketCallbackFunction = "";
	long nSocketListenPort = 0;
};
void * AcceptThread(void *arg)
{
	struct acceptthread_data * apdata = (struct acceptthread_data *)arg;

	int sock_fd = 0;
	struct sockaddr_in listensock = { 0 };

	socklen_t sin_size = sizeof(struct sockaddr_in);
	struct sockaddr_in client_addr = { 0 };

	//��ʼ��socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	//�༭��ַ��Ϣ
	memset(&listensock, 0, sizeof(listensock));
	listensock.sin_family = AF_INET;
	listensock.sin_port = htons(apdata->nSocketListenPort);
	listensock.sin_addr.s_addr = INADDR_ANY;

	//�󶨵�ַ��Ȼ�����
	bind(sock_fd, (struct sockaddr *)&listensock, sizeof(struct sockaddr));
	if (0 != listen(sock_fd, 10))
	{
		printf("listen error.\n");
	}

	printf("listening...\n");
	while (true)
	{
		// accpet
		int client_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
		if (-1 != client_fd)
		{
			struct socketthread_data * spdata = new struct socketthread_data();
			spdata->strSessionName = apdata->strSessionName;
			spdata->client_addr = client_addr;
			spdata->sock_fd = client_fd;
			spdata->strSocketCallbackFunction = apdata->strSocketCallbackFunction;

			pthread_t pt = 0;
			pthread_create(&pt, nullptr, SocketThread, (void *)spdata);
		}
	}

	close(sock_fd);

	delete apdata;
	pthread_exit(0);
}

int StartSocketService(string strSessionName, long nPort, std::string strCallbackFunction)
{
	if (nPort < 0)
	{
		return -1;
	}

	struct acceptthread_data * apdata = new struct acceptthread_data();
	apdata->strSessionName = strSessionName;
	apdata->strSocketCallbackFunction = strCallbackFunction;
	apdata->nSocketListenPort = nPort;

	pthread_t pt = 0;
	pthread_create(&pt, nullptr, AcceptThread, (void *)apdata);

	return 0;
}

#include <arpa/inet.h>
struct socketmessagethread_data
{
	string netaddr;
	int port;
	string message;
};
void * SendSocketMessageThread(void *arg)
{
	socketmessagethread_data * smpdata = (socketmessagethread_data *)arg;
	string netaddr = smpdata->netaddr;
	int port = smpdata->port;
	string message = smpdata->message;

	delete smpdata;
	smpdata = nullptr;

	int sockfd = 0;
	struct sockaddr_in servaddr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("SendSocketMessageThread create socket failed\n");
		return nullptr;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	if (inet_pton(AF_INET, netaddr.c_str(), &servaddr.sin_addr) <= 0)
	{
		printf("SendSocketMessageThread inet_pton failed\n");
		close(sockfd);
		return nullptr;
	}

	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("SendSocketMessageThread connect failed\n");
		close(sockfd);
		return nullptr;
	}

	if (send(sockfd, message.c_str(), strlen(message.c_str()), 0) < 0)
	{
		printf("SendSocketMessageThread connect failed\n");
		close(sockfd);
		return nullptr;
	}

	close(sockfd);
	return nullptr;
}

struct checkfilethread_data
{
	string strSessionName;
	std::string strFileName = "";
	std::string strCheckFileCallbackFunction = "";
};
void * CheckFileStatusChangeThread(void *arg)
{
	checkfilethread_data * cfpdata = (checkfilethread_data *)arg;

	while (true)  // ÿ���ļ������һ�������̣߳�һֱѭ����飬���������
	{
		bool bFileExists = false;
		__time_t mtim = 0;

		// �ļ���ʼ״̬�Ƿ����
		struct stat s_buf = {0};
		if (0 == stat(cfpdata->strFileName.c_str(), &s_buf))
		{
			bFileExists = true;
			mtim = s_buf.st_mtim.tv_sec;
		}

		while (true)
		{
			if (0 == stat(cfpdata->strFileName.c_str(), &s_buf))
			{
				if (false == bFileExists || mtim != s_buf.st_mtim.tv_sec)
				{
					// �ļ����޵��У������ļ��޸�ʱ��仯
					bFileExists = true;
					break;
				}
			}
			else
			{
				if (true == bFileExists)
				{
					// �ļ����е���
					bFileExists = false;
					break;
				}
			}

			sleep(3);  // 3����һ��
		}

		// ����JS����
		int nBuffLen = cfpdata->strFileName.size() + 256;
		char * strCallbackJs = new char[nBuffLen];
		memset(strCallbackJs, 0, nBuffLen);
		sprintf(strCallbackJs, "%s('%s', %s)",  // ��һ������Ϊ�ļ������ڶ�������Ϊ�ļ��Ƿ���ڣ�true / false
			cfpdata->strCheckFileCallbackFunction.c_str(), cfpdata->strFileName.c_str(), (true == bFileExists ? "true" : "false"));
		int nRetLen = strlen(strCallbackJs);

		printf("mtx_session_data4send.lock ->\n");
		mtx_session_data4send.lock();  //���ķ��ͺ�����
		printf("mtx_session_data4send.lock <-\n");
		memset(session_data4send.buf, 0, sizeof(session_data4send.buf));
		memcpy(&session_data4send.buf[LWS_PRE], strCallbackJs, nRetLen);
		session_data4send.len = nRetLen;

		struct lws * wsi_session = messagehandle.GetSession(cfpdata->strSessionName);
		if (nullptr != wsi_session)
		{
			lws_write(wsi_session, &session_data4send.buf[LWS_PRE], session_data4send.len, LWS_WRITE_TEXT);
		}
		else
		{
			printf("GetSession failed, strSessionName : %s\n", cfpdata->strSessionName.c_str());
		}
		mtx_session_data4send.unlock();

		delete strCallbackJs;
		strCallbackJs = nullptr;
	}

	delete cfpdata;
	pthread_exit(0);  // ��⵽һ�α仯���˳������������Ҫ�ٴμ�⣬��ҪJS���ٴε���
}

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <cstring>
#include <stdio.h>
void _FindWindow(Display* display, Window window, char* windowName, Window* result)
{
	Window root, parent, *children;
	unsigned int nChildren;

	//����ʹ��_NET_WM_NAME��ʽ��ȡ���ڵ�����
	XTextProperty tp;
	XGetTextProperty(display, window, &tp, XInternAtom(display, "WM_NAME", False));
	if (tp.nitems > 0)
	{
		int count = 0, i, ret;
		char **list = nullptr;
		ret = XmbTextPropertyToTextList(display, &tp, &list, &count);
		if ((ret == Success || ret > 0) && list != nullptr)
		{
			for (i = 0; i < count; i++)
			{
				if (windowName && strstr(list[i], windowName) != nullptr)
				{
					printf("windowName : %s, list[%d] : %s\n", windowName, i, list[i]);

					*result = window;
					return;
				}
			}
			XFreeStringList(list);
		}
	}

	if (XQueryTree(display, window, &root, &parent, &children, &nChildren) != 0)
	{
		for (int i = 0; i < nChildren; i++)
		{
			_FindWindow(display, children[i], windowName, result);
			if (None != *result)
			{
				break;
			}
		}
		XFree(children);
	}
}

unsigned long FindWindow(char* windowName)
{
	Window result = None;
	Display* display = XOpenDisplay(nullptr);
	if (nullptr == display)
	{
		printf("nullptr == display\n");
		return result;
	}

	Window root = DefaultRootWindow(display);
	_FindWindow(display, root, windowName, &result);

	XCloseDisplay(display);

	printf("Found window with ID %lu\n", result);
	return result;
}

#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
std::string get_local_ip()
{
	std::string strIP = "";
	int fd, intrface = 0;
	struct ifreq buf[INET_ADDRSTRLEN];
	struct ifconf ifc;
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)
	{
		ifc.ifc_len = sizeof(buf);
		// caddr_t,linux�ں�Դ���ﶨ��ģ�typedef void *caddr_t��
		ifc.ifc_buf = (caddr_t)buf;
		if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))
		{
			intrface = ifc.ifc_len / sizeof(struct ifreq);
			while (intrface-- > 0)
			{
				if (!(ioctl(fd, SIOCGIFADDR, (char *)&buf[intrface])))
				{
					if (strlen(strIP.c_str()) > 0)
					{
						strIP += ",";
					}

					strIP += (inet_ntoa(((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr));
				}
			}
		}

		close(fd);
	}

	return strIP;
}

#include <ifaddrs.h>
#include <netpacket/packet.h>
std::string get_local_mac()
{
	struct ifaddrs *ifaddr = NULL, *ifa = NULL;

	if (getifaddrs(&ifaddr) == -1)
	{
		perror("getifaddrs");
		return "";
	}

	string strMac = "";
	char mac[64] = { 0 };
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family != AF_PACKET)
		{
			continue;
		}

		struct sockaddr_ll *s = (struct sockaddr_ll*)ifa->ifa_addr;
		sprintf(mac, "%s(%02x:%02x:%02x:%02x:%02x:%02x)",
			ifa->ifa_name,
			s->sll_addr[0], s->sll_addr[1], s->sll_addr[2],
			s->sll_addr[3], s->sll_addr[4], s->sll_addr[5]);
		if (strlen(strMac.c_str()) > 0)
		{
			strMac += ",";
		}
		strMac += mac;
	}

	freeifaddrs(ifaddr);
	return strMac;
}

int Extension::CallExtension(string strSessionName, list<string> params, string & strRet)
{
	int nRet = -1;  // ����ֵ
	strRet = "";

	if (params.size() < 1)  // ��һ���Ƿ�������
	{
		printf("ssa.callExtension ArgumentList is empty\n");
		return -1;
	}

	list<string>::iterator iter = params.begin();
	
	string strMethod = (* iter++);  // ��������
	printf("strMethod : %s\n", strMethod.c_str());

	if ("SetSocketResult" == strMethod)  // ����Socket����JS������ĵ��ý��
	{
		strRet = "false";
		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		int userdataid = atol((*iter++).c_str());  // �û�����id����Ϊsocket���ĵ���ʱ��Ϊsocket�����
		std::string resultstring = (*iter++);  // ����ַ���
		printf("userdataid : %d, resultstring : %s\n", userdataid, resultstring.c_str());

		m_JSResultMap.insert(std::pair<int, std::string>(userdataid, resultstring));

		strRet = "true";
		nRet = 0;
	}
	else if ("RestartWindows" == strMethod || "RestartLinux" == strMethod)  // ����
	{
		strRet = "false";
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		int delayseconds = atol((*iter++).c_str());  // ��Ҫ�ӳٵ����������ڵ��÷�������������

		if (delayseconds > 0)
		{
			sleep(delayseconds);
		}

		// ShutdownLinux(0);  // �ػ���������1�ػ���0����������Reboot��������Ȩ�����ⷵ��-1ʧ�ܣ���Ϊֱ�ӵ���ϵͳ����

		int nResult = system("/usr/sbin/reboot");
		printf("ShutdownLinux(0) ret %d\n", nResult);

		strRet = "true";
		nRet = 0;
	}
	else if ("SendKeyInput" == strMethod)  // ���ͼ����¼�
	{
		strRet = "false";
		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		int keycode = atol((*iter++).c_str());  // ����
		long microseconds = atol((*iter++).c_str());  // �ӳ�ʱ�䣬��Ϊ��ʱ�����SetActiveScreenʹ�ã�JS�ص��������ֵ���SendKeyInput����û��Ч������Ҫ�ӳ��£�C++��window.setTimeout�ô���
		printf("keycode : %d, microseconds %ld\n", keycode, microseconds);
		if (microseconds > 1000)
		{
			usleep(microseconds);
		}

		kbdms_send_button_event(keycode);

		strRet = "true";
		nRet = 0;
	}
	else if ("EnablePointer" == strMethod)  // ����/����ָ���豸
	{
		strRet = "false";
		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string pointername = (*iter++);  // ָ���豸���ƣ�ͨ���豸�������� xinput list��һ������������ Mouse���������� TouchScreen
		int enable = atol((*iter++).c_str());  // 1 ������0 ����
		printf("EnablePointer pointername : %s, enable : %d\n", pointername.c_str(), enable);
		
		char szCommandLine[256] = { 0 };
		sprintf(szCommandLine, "xinput list | grep '%s' | head -n 1 | cut -d'=' -f2 | awk '{print $1}' | xargs xinput --%s", pointername.c_str(), (0 == enable ? "disable" : "enable"));
		int nResult = system(szCommandLine);
		printf("EnablePointer ret %d\n", nResult);

		strRet = "true";
		nRet = 0;
	}
	else if ("ShutdownWindows" == strMethod || "ShutdownLinux" == strMethod)  // �ػ�
	{
		strRet = "false";
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		int delayseconds = atol((*iter++).c_str());  // ��Ҫ�ӳٵ����������ڵ��÷�������������

		if (delayseconds > 0)
		{
			sleep(delayseconds);
		}

		// ShutdownLinux(1);  // �ػ���������1�ػ���0����������Reboot��������Ȩ�����ⷵ��-1ʧ�ܣ���Ϊֱ�ӵ���ϵͳ����
		int nResult = system("/usr/sbin/shutdown -h now");
		printf("ShutdownLinux(1) ret %d\n", nResult);

		strRet = "true";
		nRet = 0;
	}
	else if ("ShowCursor" == strMethod)  // ��ʾ���
	{
		strRet = "false";

		char outbuf[1024] = { 0 };
		g2u("Linux�´����֧��", strlen("Linux�´����֧��"), outbuf, sizeof(outbuf));
		strRet = outbuf;  // strRet = "Linux�´����֧��"; strRet = u8"Linux�´����֧��"; ֮�����ʾ���룬����websocketת��ʧ�ܶ���

		nRet = 0;
	}
	else if ("SetSystemTime" == strMethod)  // ����ϵͳʱ��
	{
		strRet = "false";
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string timestring = (*iter++);  // ϵͳʱ���ַ�������ʽ YYYY-MM-DD hh:mm:ss
		printf("timestring : %s\n", timestring.c_str());
		// ����ϵͳʱ�䣺����settimeofday��������Ȩ�����ⷵ��-1ʧ�ܣ���Ϊֱ�ӵ���ϵͳ�����Ҫ�� chmod 4755 /usr/bin/date
		timestring = replace_all_distinct(timestring, "/", "-");

		// date ��������޸ı���ʱ��͸�������ʱ��
		char szCommandLine[256] = { 0 };
		sprintf(szCommandLine, "/usr/bin/date -s \"%s\"", timestring.c_str());
		int nResult = system(szCommandLine);

		// �����ͨSPʹ�õ�����RTCʱ�䣬��Ҫ����
		// ͬ������ʱ�䵽Ӳ��ʱ�䣨BIOSʱ�䣩����Ҫ�� chmod 4755 /usr/sbin/hwclock
		memset(szCommandLine, 0, sizeof(szCommandLine));
		sprintf(szCommandLine, "/usr/sbin/hwclock -w");
		nResult = system(szCommandLine);

		printf("%s ret %d\n", szCommandLine, nResult);

		strRet = "true";
		nRet = 0;
	}
	else if ("GetAppHome" == strMethod)  // ��ȡӦ�ó�������·��
	{
		strRet = GetAppHome();
		printf("apphome : %s\n", strRet.c_str());

		nRet = 0;
	}
	else if ("GetAppName" == strMethod)  // ��ȡӦ�ó�������
	{
		strRet = GetAppName();
		printf("appname : %s\n", strRet.c_str());

		nRet = 0;
	}
	else if ("MoveScreen" == strMethod)  // �ƶ�����
	{
		strRet = "false";
		if (params.size() < 6) { printf("params miss, need 5 param\n"); return nRet; }

		std::string windowname = (*iter++);  // ��������
		int left = atoi((*iter++).c_str());
		int top = atoi((*iter++).c_str());
		int width = atoi((*iter++).c_str());
		int height = atoi((*iter++).c_str());

		unsigned long windowid = FindWindow((char *)windowname.c_str());

		printf("windowname : %s, windowid : %lu, left : %d, top : %d, width : %d, heigth : %d\n", 
			windowname.c_str(), windowid, left, top, width, height);

		strRet = "false";
		if (0 == windowid)
		{
			printf("window not found\n");
		}
		else
		{
			/*
			// �򵥻���ֱ���������й��߲���
			Display *display = nullptr;
			XWindowAttributes attributes1 = { 0 }, attributes2 = { 0 };

			display = XOpenDisplay(nullptr);
			if (display != nullptr)
			{
				if (0 != XGetWindowAttributes(display, windowid, &attributes1))
				{
					XMoveWindow(display, windowid, left, top);
					XResizeWindow(display, windowid, width, height);
					XFlush(display);

					strRet = "true";
				}
				XCloseDisplay(display);
			}
			//*/

			// ��Ϊʹ�������й���ʵ��
			char szCommand[256] = { 0 };
			sprintf(szCommand, "xdotool windowmove --sync %ld %d %d; xdotool windowsize --sync %ld %d %d", windowid, left, top, windowid, width, height);
			printf("xdotool control window : %s\n", szCommand);

			int nSystemResult = system(szCommand);
			printf("MoveScreen ret %d\n", nSystemResult);

			strRet = "true";
		}

		nRet = 0;
	}
	else if ("SetWindowDesktop" == strMethod)  // ���ô�����ʾ���ĸ����棬û��Ч��
	{
		strRet = "false";
		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string windowname = (*iter++);  // ��������
		int desktop = atoi((*iter++).c_str());  // Ŀ�깤������ţ��� 0 ��ʼ��

		unsigned long windowid = FindWindow((char *)windowname.c_str());

		printf("windowname : %s, windowid : %ul, desktop : %d\n", 
			windowname.c_str(), windowid, desktop);

		strRet = "false";
		if (0 == windowid)
		{
			printf("window not found\n");
		}
		else
		{
			Display *display = nullptr;
			XWindowAttributes attributes1 = { 0 }, attributes2 = { 0 };

			display = XOpenDisplay(nullptr);
			if (display != nullptr)
			{
				Atom desktopAtom = XInternAtom(display, "_NET_WM_DESKTOP", False);
				nRet = XChangeProperty(display, windowid, desktopAtom, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)&desktop, 1);
				printf("XChangeProperty : %d\n", nRet);
				XFlush(display);

				strRet = "true";

				XCloseDisplay(display);
			}
		}
		
		nRet = 0;
	}
	else if ("SetScreenSize" == strMethod)  // ���ô��ڴ�С
	{
		strRet = "false";

		char outbuf[1024] = { 0 };
		g2u("Linux�´����֧��", strlen("Linux�´����֧��"), outbuf, sizeof(outbuf));
		strRet = outbuf;  // strRet = "Linux�´����֧��"; strRet = u8"Linux�´����֧��"; ֮�����ʾ���룬����websocketת��ʧ�ܶ���

		nRet = 0;
	}
	else if ("ShowScreenTitle" == strMethod)  // ��ʾ���ڱ���
	{
		strRet = "false";

		char outbuf[1024] = { 0 };
		g2u("Linux�´����֧��", strlen("Linux�´����֧��"), outbuf, sizeof(outbuf));
		strRet = outbuf;  // strRet = "Linux�´����֧��"; strRet = u8"Linux�´����֧��"; ֮�����ʾ���룬����websocketת��ʧ�ܶ���

		nRet = 0;
	}
	else if ("SetForeground" == strMethod)  // ������ǰ��ʾ
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string screenname = (*iter++);  // ��������
		printf("screenname : %s\n", screenname.c_str());

		strRet = "false";
		unsigned long windowid = FindWindow((char *)screenname.c_str());
		if (0 == windowid)
		{
			printf("screen not found\n");
		}
		else
		{
			Display *display = nullptr;
			display = XOpenDisplay(nullptr);
			if (display)
			{
				XRaiseWindow(display, windowid);
				XFlush(display);

				strRet = "true";
				XCloseDisplay(display);
			}
		}

		nRet = 0;
	}
	else if ("SetActiveScreen" == strMethod)  // ���û����
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string windowname = (*iter++);  // ��������
		unsigned long windowid = FindWindow((char *)windowname.c_str());

		printf("windowname : %s, windowid : %lu\n",
			windowname.c_str(), windowid);

		strRet = "false";
		if (0 == windowid)
		{
			printf("window not found\n");
		}
		else
		{
			Display* display = XOpenDisplay(nullptr);
			if (display == nullptr)
			{
				printf("XOpenDisplay failed\n");
			}
			else
			{
				// ʹ�� XRaiseWindow �� XSetInputFocus �����û����
				XRaiseWindow(display, windowid);
				XSetInputFocus(display, windowid, RevertToPointerRoot, CurrentTime);

				strRet = "true";

				XCloseDisplay(display);
			}
		}

		nRet = 0;
	}
	else if ("SetScreenInfo" == strMethod)  // ���ô���λ�ô�С��Ϣ
	{
		strRet = "false";

		char outbuf[1024] = { 0 };
		g2u("Linux�´����֧��", strlen("Linux�´����֧��"), outbuf, sizeof(outbuf));
		strRet = outbuf;  // strRet = "Linux�´����֧��"; strRet = u8"Linux�´����֧��"; ֮�����ʾ���룬����websocketת��ʧ�ܶ���

		nRet = 0;
	}
	else if ("OpenScreen" == strMethod)  // ���´���
	{
		strRet = "false";

		char outbuf[1024] = { 0 };
		g2u("Linux�´����֧��", strlen("Linux�´����֧��"), outbuf, sizeof(outbuf));
		strRet = outbuf;  // strRet = "Linux�´����֧��"; strRet = u8"Linux�´����֧��"; ֮�����ʾ���룬����websocketת��ʧ�ܶ���

		nRet = 0;
	}
	else if ("FindScreen" == strMethod)  // ���Ҵ���
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string screenname = (*iter++);  // ��������
		unsigned long windowid = FindWindow((char *)screenname.c_str());
		printf("screenname : %s, windowid : %ul\n", screenname.c_str(), windowid);
		
		if (0 == windowid)
		{
			printf("screen not found\n");
		}
		else
		{
			strRet = "true";
		}

		nRet = 0;
	}
	else if ("SwitchScreen" == strMethod)  // �л�����λ��
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string windowname1 = (*iter++);  // ��������1
		std::string windowname2 = (*iter++);  // ��������2

		unsigned long windowid1 = FindWindow((char *)windowname1.c_str());
		unsigned long windowid2 = FindWindow((char *)windowname2.c_str());
		printf("windowname1 : %s, windowid1 : %lu\n", windowname1.c_str(), windowid1);
		printf("windowname2 : %s, windowid2 : %lu\n", windowname2.c_str(), windowid2);

		if (0 == windowid1 || 0 == windowid2)
		{
			printf("window not found\n");
		}
		else
		{
			Display *display = nullptr;
			XWindowAttributes attributes1 = { 0 }, attributes2 = {0};

			display = XOpenDisplay(nullptr);
			if (display == nullptr)
			{
				printf("XOpenDisplay failed\n");
			}
			else
			{
				int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
				Window root_window = DefaultRootWindow(display);
				Window child = 0;

				XTranslateCoordinates(display, windowid1, root_window, 0, 0, &x1, &y1, &child);
				XTranslateCoordinates(display, windowid2, root_window, 0, 0, &x2, &y2, &child);

				if (0 != XGetWindowAttributes(display, windowid1, &attributes1)
					&& 0 != XGetWindowAttributes(display, windowid2, &attributes2))
				{
					printf("x1 : %d, y1 : %d, attributes1.width : %d, attributes1.height : %d\n", x1, y1, attributes1.width, attributes1.height);
					printf("x2 : %d, y2 : %d, attributes1.width : %d, attributes1.height : %d\n", x2, y2, attributes2.width, attributes2.height);
					
					XMoveWindow(display, windowid1, x2, y2);
					XMoveWindow(display, windowid2, x1, y1);

					XResizeWindow(display, windowid1, attributes2.width, attributes2.height);
					XResizeWindow(display, windowid2, attributes1.width, attributes1.height);

					XFlush(display);

					strRet = "true";
				}
				XCloseDisplay(display);
			}
		}

		nRet = 0;
	}
	else if ("SwitchFullBrowserScreen" == strMethod)  // �л������ȫ������
	{
		strRet = "false";

		if (params.size() < 12) { printf("params miss, need 11 param\n"); return nRet; }

		std::string windowname1 = (*iter++);  // ��������1
		int left1 = atoi((*iter++).c_str());
		int top1 = atoi((*iter++).c_str());
		int width1 = atoi((*iter++).c_str());
		int height1 = atoi((*iter++).c_str());
		std::string windowname2 = (*iter++);  // ��������2
		int left2 = atoi((*iter++).c_str());
		int top2 = atoi((*iter++).c_str());
		int width2 = atoi((*iter++).c_str());
		int height2 = atoi((*iter++).c_str());
		int millisecond = atoi((*iter++).c_str());  // ÿ�β�������ĺ�������ʱ�����������ϵͳ���ܷ�Ӧ����������������ʱ���ֲ������ܲ���Ч��
		
		unsigned long windowid1 = FindWindow((char *)windowname1.c_str());
		unsigned long windowid2 = FindWindow((char *)windowname2.c_str());
		printf("windowname1 : %s, windowid1 : %lu, left1 : %d, top1 : %d, width1 : %d, height1 : %d\n", 
			windowname1.c_str(), windowid1, left1, top1, width1, height1);
		printf("windowname2 : %s, windowid2 : %lu, left2 : %d, top2 : %d, width2 : %d, height2 : %d\n", 
			windowname2.c_str(), windowid2, left2, top2, width2, height2);
		printf("millisecond : %d\n", millisecond);
		if (millisecond < 100)
		{
			millisecond = 100;
		}

		if (0 == windowid1 || 0 == windowid2)
		{
			printf("window not found\n");
		}
		else
		{
			Display *display = nullptr;
			
			display = XOpenDisplay(nullptr);
			if (display == nullptr)
			{
				printf("XOpenDisplay failed\n");
			}
			else
			{
				// �������������ڣ��������̲��ɼ������������в������ش��ڣ���Ȼ��Ϊ�������أ�X11�������³����쳣��ֱ���˳�����F11�������ܷ��͵������
				// XUnmapWindow(display, windowid1); // ���ش���
				// XUnmapWindow(display, windowid2); // ���ش���

				// ��ȡ��������Ļ��ȫ��״̬������F11
				// ��һ������
				XRaiseWindow(display, windowid1);
				XSetInputFocus(display, windowid1, RevertToPointerRoot, CurrentTime);
				XFlush(display);

				usleep(millisecond * 1000);
				kbdms_send_button_event(KEY_F11);

				usleep(millisecond * 1000);
				XMoveWindow(display, windowid1, left2, top2);
				XFlush(display);

				usleep(millisecond * 1000);
				XResizeWindow(display, windowid1, width2, height2);
				XFlush(display);

				usleep(millisecond * 1000);
				kbdms_send_button_event(KEY_F11);

				usleep(millisecond * 1000);

				// �ڶ�������
				XRaiseWindow(display, windowid2);
				XSetInputFocus(display, windowid2, RevertToPointerRoot, CurrentTime);
				XFlush(display);

				usleep(millisecond * 1000);
				kbdms_send_button_event(KEY_F11);

				usleep(millisecond * 1000);
				XMoveWindow(display, windowid2, left1, top1);
				XFlush(display);

				usleep(millisecond * 1000);
				XResizeWindow(display, windowid2, width1, height1);
				XFlush(display);

				usleep(millisecond * 1000);
				kbdms_send_button_event(KEY_F11);

				// �ָ���ʾ��������
				// XMapWindow(display, windowid1); // ��ʾ����
				// XMapWindow(display, windowid2); // ��ʾ����

				XFlush(display);

				XCloseDisplay(display);

				strRet = "true";
			}
		}

		nRet = 0;
	}
	else if ("FullBrowserScreen" == strMethod)  // ���������ȫ��
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string windowname = (*iter++);  // ��������
		int millisecond = atoi((*iter++).c_str());  // ÿ�β�������ĺ�������ʱ�����������ϵͳ���ܷ�Ӧ����������������ʱ���ֲ������ܲ���Ч��
		
		unsigned long windowid = FindWindow((char *)windowname.c_str());
		printf("windowname : %s, windowid : %lu\n", 
			windowname.c_str(), windowid);
		printf("millisecond : %d\n", millisecond);
		if (millisecond < 100)
		{
			millisecond = 100;
		}

		if (0 == windowid)
		{
			printf("window not found\n");
		}
		else
		{
			Display *display = nullptr;
			
			display = XOpenDisplay(nullptr);
			if (display == nullptr)
			{
				printf("XOpenDisplay failed\n");
			}
			else
			{
				/*
				// ����_NET_WM_STATE_FULLSCREEN�¼�ֻ�ܰ������������󻯣����������˵�������ַ���Ȼ��ڣ���Ҫ���� F11 ������ʽ���ܰ����������ȫ��
				Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
				Atom wm_fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

				XEvent event;
				memset(&event, 0, sizeof(event));

				event.type = ClientMessage;
				event.xclient.window = windowid;
				event.xclient.message_type = wm_state;
				event.xclient.format = 32;
				event.xclient.data.l[0] = 1; // _NET_WM_STATE_ADD
				event.xclient.data.l[1] = wm_fullscreen;
				event.xclient.data.l[2] = 0; // �޵ڶ�������

				// �����¼��������ڣ�����EWMH�淶��
				XSendEvent(display, DefaultRootWindow(display), False,
					SubstructureRedirectMask | SubstructureNotifyMask,
					&event);
				XFlush(display);
				XCloseDisplay(display);
				*/


				//*  20250212����ʹ��F11����
				// ���������й����ô��ڽ���
				char szCommand[256] = { 0 };
				sprintf(szCommand, "xdotool windowactivate --sync %ld", windowid);
				printf("xdotool control window : %s\n", szCommand);

				int nSystemResult = system(szCommand);
				printf("windowactivate ret %d\n", nSystemResult);

				XRaiseWindow(display, windowid);
				XSetInputFocus(display, windowid, RevertToPointerRoot, CurrentTime);
				XFlush(display);

				usleep(millisecond * 1000);
				kbdms_send_button_event(KEY_F11);

				XFlush(display);

				XCloseDisplay(display);

				strRet = "true";
				//*/
			}
		}

		nRet = 0;
	}
	else if ("GetScreenPosition" == strMethod)  // ��ȡ����λ��
	{
		strRet = "{}";  // ����һ��json�ַ�����Ĭ��Ϊ�ն���

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string windowname = (*iter++);  // ��������1

		unsigned long windowid = FindWindow((char *)windowname.c_str());
		printf("windowname : %s, windowid : %lu\n", windowname.c_str(), windowid);

		if (0 == windowid)
		{
			printf("window not found\n");
		}
		else
		{
			Display *display = nullptr;
			XWindowAttributes attributes = { 0 };

			display = XOpenDisplay(nullptr);
			if (display == nullptr)
			{
				printf("XOpenDisplay failed\n");
			}
			else
			{
				int x = 0, y = 0;
				Window root_window = DefaultRootWindow(display);
				Window child = 0;

				XTranslateCoordinates(display, windowid, root_window, 0, 0, &x, &y, &child);

				if (0 != XGetWindowAttributes(display, windowid, &attributes))
				{
					char szBuf[1024] = { 0 };
					sprintf(szBuf, "{left : %d, top : %d, width : %d, height : %d}", x, y, attributes.width, attributes.height);
					
					strRet = szBuf;
				}
				XCloseDisplay(display);
			}
		}

		nRet = 0;
	}
	else if ("ShowWindow" == strMethod)  // ��ʾ����
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string windowname = (*iter++);  // �������ƣ�ͬscreenname����
		int show = atoi((*iter++).c_str());  // ��ʾ��ʽ(ͬWindows����ֵ)��0��SW_HIDE����2(SW_SHOWMINIMIZED ��С��)��3(SW_SHOWMAXIMIZED ���)��5��SW_SHOW��
		printf("windowname : %s, show : %d\n", windowname.c_str(), show);

		unsigned long windowid = FindWindow((char *)windowname.c_str());

		if (0 == windowid)
		{
			printf("window not found\n");
		}
		else
		{
			Display *display = nullptr;
			display = XOpenDisplay(nullptr);
			if (display == nullptr)
			{
				printf("XOpenDisplay failed\n");
			}
			else
			{
				// ֻ֧����ʾ�����ش��ڣ�����
				if (0 == show)  // SW_HIDE
				{
					XUnmapWindow(display, windowid); // ���ش���
					strRet = "true";
				}
				else if (2 == show)  // SW_SHOWMINIMIZED
				{
					// ����_NET_WM_STATE_MINIMIZED����_NET_WM_STATE_HIDDEN�¼���������
					/*
					Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
					// Atom wm_min = XInternAtom(display, "_NET_WM_STATE_MINIMIZED", False);
					Atom wm_min = XInternAtom(display, "_NET_WM_STATE_HIDDEN", False);

					XEvent event;
					memset(&event, 0, sizeof(event));

					event.type = ClientMessage;
					event.xclient.window = windowid;
					event.xclient.message_type = wm_state;
					event.xclient.format = 32;
					event.xclient.data.l[0] = 1; // _NET_WM_STATE_ADD
					event.xclient.data.l[1] = wm_min;
					event.xclient.data.l[2] = 0; // �޵ڶ�������

					// �����¼��������ڣ�����EWMH�淶��
					XSendEvent(display, DefaultRootWindow(display), False,
						SubstructureRedirectMask | SubstructureNotifyMask,
						&event);
					XFlush(display);
					*/

					// ��Ϊʹ�������й���ʵ��
					char szCommand[256] = { 0 };
					sprintf(szCommand, "xdotool windowminimize --sync %ld", windowid);
					printf("xdotool control window : %s\n", szCommand);

					int nSystemResult = system(szCommand);
					printf("ShowWindow ret %d\n", nSystemResult);

					strRet = "true";
				}
				else if (3 == show)  // SW_SHOWMAXIMIZED
				{
					// ֱ����_NET_WM_STATE_MAXIMIZED_VERT��_NET_WM_STATE_MAXIMIZED_HORZ�¼�������󻯺��������
					Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
					Atom wm_vmax = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
					Atom wm_hmax = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);

					XEvent event;
					memset(&event, 0, sizeof(event));

					event.type = ClientMessage;
					event.xclient.window = windowid;
					event.xclient.message_type = wm_state;
					event.xclient.format = 32;
					event.xclient.data.l[0] = 1; // _NET_WM_STATE_ADD
					event.xclient.data.l[1] = wm_vmax;
					event.xclient.data.l[2] = wm_hmax;
					event.xclient.data.l[3] = 0; // �޵���������

					// �����¼��������ڣ�����EWMH�淶��
					XSendEvent(display, DefaultRootWindow(display), False,
						SubstructureRedirectMask | SubstructureNotifyMask,
						&event);
					XFlush(display);
				}
				else if (5 == show)  // SW_SHOW
				{
					XMapWindow(display, windowid); // ��ʾ����
					strRet = "true";
				}

				XCloseDisplay(display);
			}
		}
		nRet = 0;
	}
	else if ("CaptureScreenAsJPG" == strMethod)  // ץȡ��Ļ
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string filename = (*iter++);  // �ļ���
		printf("capture screen to filename : %s\n", filename.c_str());

		if (std::string::npos != filename.find("*") || std::string::npos != filename.find("?"))
		{
			printf("filename invalid : %s\n", filename.c_str());
		}
		else
		{
			// ֱ�ӻ���������ʵ��
			int nSystemResult = system((char*)("rm -f " + filename).c_str());
			printf("CaptureScreenAsJPG rm ret %d\n", nSystemResult);

			char szCommand[256] = { 0 };
			sprintf(szCommand, "for i in `xrandr | grep -P 'current[^,]*' -o | grep -P '(\\d)*' -o | tr '\\n' '*' | grep -P '(\\d)+\\*(\\d)+' -o`; do ffmpeg -f x11grab -s $i -i :0.0 %s; done;", filename.c_str());
			printf("CaptureScreenAsJPG : %s\n", szCommand);

			nSystemResult = system(szCommand);
			printf("CaptureScreenAsJPG ret %d\n", nSystemResult);

			strRet = "true";
		}

		nRet = 0;
	}
	else if ("SystemCmdWithResult" == strMethod)  // ִ������������
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string commandline = (*iter++);  // ������
		nRet = system(commandline.c_str());

		if (0 == nRet)
		{
			strRet = "true";
		}
		else
		{
			printf("szCommand failed: %s\n", commandline.c_str());
		}

		nRet = 0;
	}
	else if ("GetFileVersion" == strMethod)  // ��ȡ�ļ��汾��Ϣ����֧�֣�ֻ��Windows����Ч
	{
		strRet = "false";

		char outbuf[1024] = { 0 };
		g2u("Linux�´����֧��", strlen("Linux�´����֧��"), outbuf, sizeof(outbuf));
		strRet = outbuf;  // strRet = "Linux�´����֧��"; strRet = u8"Linux�´����֧��"; ֮�����ʾ���룬����websocketת��ʧ�ܶ���

		nRet = 0;
	}
	else if ("GetRemovableDrivers" == strMethod)  // ��ȡ���ƶ��洢������֧�֣�ֻ��Windows����Ч
	{
		strRet = "false";

		char outbuf[1024] = { 0 };
		g2u("Linux�´����֧��", strlen("Linux�´����֧��"), outbuf, sizeof(outbuf));
		strRet = outbuf;  // strRet = "Linux�´����֧��"; strRet = u8"Linux�´����֧��"; ֮�����ʾ���룬����websocketת��ʧ�ܶ���

		nRet = 0;
	}
	else if ("ZipFile" == strMethod)  // ѹ���ļ�
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string filename = (*iter++);  // ��ѹ�����ļ���
		std::string zipfilename = (*iter++);  // ѹ������ļ���

		// ʹ������������
		char szCommand[256] = { 0 };
		sprintf(szCommand, "rm -r %s; zip -qj %s %s", zipfilename.c_str(), zipfilename.c_str(), filename.c_str());

		nRet = system(szCommand);
		if (0 == nRet)
		{
			// ������ļ��Ƿ����
			struct stat s_buf = {0};
			if (0 == stat(zipfilename.c_str(), &s_buf))
			{
				strRet = "true";
			}
		}
		else
		{
			printf("szCommand failed: %s\n", szCommand);
		}

		nRet = 0;
	}
	else if ("ZipPath" == strMethod)  // ѹ��·��
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string filepath = (*iter++);  // ��ѹ�����ļ�·��
		std::string zipfilename = (*iter++);  // ѹ������ļ���

		// ʹ������������
		char szCommand[256] = { 0 };
		sprintf(szCommand, "rm -f %s", zipfilename.c_str());
		system(szCommand);  // ɾ���ļ���Ŀ¼����ʧ�ܣ���ִ�У�������ɾ���Ľ��

		sprintf(szCommand, "cd %s; zip -rq %s ./", filepath.c_str(), zipfilename.c_str());
		nRet = system(szCommand);
		if (0 == nRet)
		{
			// ������ļ��Ƿ����
			struct stat s_buf = {0};
			if (0 == stat(zipfilename.c_str(), &s_buf))
			{
				strRet = "true";
			}
		}
		else
		{
			printf("szCommand failed: %s\n", szCommand);
		}

		nRet = 0;
	}
	else if ("GetDirectoryFileInfo" == strMethod)  // ��ȡĿ¼��Ϣ
	{
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string filepath = (*iter++);  // �ļ�·��

		std::string strDirectoryFileInfo = "";

		struct dirent *direntp;

		int nchdir = chdir(filepath.c_str());
		if (0 == nchdir)
		{
			DIR *dirp = opendir(filepath.c_str());

			struct stat s_buf = {0};
			int nLoop = 0;

			if (dirp != nullptr)
			{
				while ((direntp = readdir(dirp)) != nullptr)
				{
					if (0 != stat(direntp->d_name, &s_buf))
					{
						continue;
					}

					char ctim[20] = { 0 };
					strftime(ctim, sizeof(ctim), "%Y-%m-%d %T", localtime(&s_buf.st_ctim.tv_sec));
					char mtim[20] = { 0 };
					strftime(mtim, sizeof(mtim), "%Y-%m-%d %T", localtime(&s_buf.st_mtim.tv_sec));

					char szBuffer[1024] = { 0 };
					sprintf(szBuffer, "fileinfo.file[%d].file.filename=%s"
						"%s"
						"fileinfo.file[%d].file.type=%s"
						"%s"
						"fileinfo.file[%d].file.length=%ld"
						"%s"
						"fileinfo.file[%d].file.createtime=%s"
						"%s"
						"fileinfo.file[%d].file.modifytime=%s",
						nLoop,
						direntp->d_name,
						";",
						nLoop,
						((S_ISDIR(s_buf.st_mode)) ? "directory" : "file"),
						";",
						nLoop,
						(long)s_buf.st_size,
						";",
						nLoop,
						"", // ctim = s_buf.st_ctim���Ǵ���ʱ�䣬����״̬�޸�ʱ�䣬Ϊ���ֺ�Windowsһ�£����ṩ��ֵ
						";",
						nLoop,
						mtim);

					if ("" != strDirectoryFileInfo)
					{
						strDirectoryFileInfo += ";";
					}

					strDirectoryFileInfo += szBuffer;

					nLoop++;
				}
			}
			closedir(dirp);
		}

		printf("strDirectoryFileInfo : %s\n", strDirectoryFileInfo.c_str());

		strRet = strDirectoryFileInfo;
		nRet = 0;
	}
	else if ("CheckFileStatus" == strMethod  || "AddFileStatus2Check" == strMethod)  // �����ļ����
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string filename = (*iter++);  // �ļ�·��
		std::string callbackfunction = (*iter++);  // �ص�����
		printf("filename : %s, callbackfunction : %s\n", filename.c_str(), callbackfunction.c_str());

		struct checkfilethread_data * cfpdata = new struct checkfilethread_data();
		cfpdata->strFileName = filename;
		cfpdata->strCheckFileCallbackFunction = callbackfunction;
		cfpdata->strSessionName = strSessionName;

		pthread_t pt = 0;
		pthread_create(&pt, nullptr, CheckFileStatusChangeThread, (void *)cfpdata);

		strRet = "true";
		nRet = 0;
	}
	else if ("GetFileSize" == strMethod)  // ��ȡ�ļ���С
	{
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string filename = (*iter++);  // �ļ�·��
		printf("filename : %s\n", filename.c_str());

		// û�к���֧�֣�ֱ��ʹ������������
		struct stat s_buf = {0};
		if (0 == stat(filename.c_str(), &s_buf))
		{
			char szFileSize[64] = { 0 };
			sprintf(szFileSize, "%ld", s_buf.st_size);
			strRet = szFileSize;
		}

		nRet = 0;
	}
	else if ("FindProcess" == strMethod)  // ����ָ�����ƵĽ��̣���Ҫ����������ps -ef������Ϣ�а�����ָ���ַ����Ľ��̶��ᱻɱ��������ֻ��·���������������в����Ȱ����˸�����
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string processname = (*iter++);  // ��������
		printf("processname : %s\n", processname.c_str());

		// ֱ��ʹ�������������
		// ɾ����ʱ�ļ�
		system("rm -f /SSA/findprocess.txt");

		char szCommand[256] = { 0 };
		sprintf(szCommand, "ps -ef | grep %s | grep -v grep > /SSA/findprocess.txt", processname.c_str());

		nRet = system(szCommand);
		if (0 == nRet)
		{
			// /SSA/findprocess.txt�ļ�����ʱ��ʾ�ҵ�����
			struct stat s_buf = {0};
			if (0 == stat("/SSA/findprocess.txt", &s_buf) && s_buf.st_size > 0)
			{
				strRet = "true";
			}
		}
		else
		{
			printf("szCommand failed: %s\n", szCommand);
		}

		nRet = 0;
	}
	else if ("KillProcess" == strMethod)  // ����ָ�����ƵĽ���
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string processname = (*iter++);  // ��������
		printf("processname : %s\n", processname.c_str());

		// ֱ��ʹ�������������
		char szCommand[256] = { 0 };
		sprintf(szCommand, "for i in `ps -ef|grep %s |awk '{print $2}' `; do kill -9 $i ; done;", processname.c_str());

		nRet = system(szCommand);
		printf("%s ret : %d\n", szCommand, nRet);

		strRet = "true";
		nRet = 0;
	}
	else if ("GetLocalIpAddress" == strMethod)  // ��ȡ����IP��ַ
	{
		strRet = get_local_ip();

		nRet = 0;
	}
	else if ("GetLocalMacAddress" == strMethod)  // ��ȡ����Mac��ַ����������(MAC��ַ),��������(MAC��ַ), ...
	{
		strRet = get_local_mac();

		nRet = 0;
	}
	else if ("ShellExecute" == strMethod)  // ִ��ָ������
	{
		strRet = "false";

		if (params.size() < 4) { printf("params miss, need 3 param\n"); return nRet; }

		std::string filepath = (*iter++);  // �ļ���
		std::string parameters = (*iter++);  // ����
		std::string directory = (*iter++);  // ·��
		printf("filepath : %s, parameters : %s, directory : %s\n", filepath.c_str(), parameters.c_str(), directory.c_str());

		char szCommand[256] = { 0 };
		sprintf(szCommand, "%s%s", directory.c_str(), filepath.c_str());

		nRet = system(szCommand);
		printf("%s ret : %d\n", szCommand, nRet);

		strRet = "true";
		nRet = 0;
	}
	else if ("SendSocketMessage" == strMethod)  // ����socket��Ϣ
	{
		strRet = "false";

		if (params.size() < 4) { printf("params miss, need 3 param\n"); return nRet; }

		std::string netaddr = (*iter++);  // ��������ַ
		int port = atoi((*iter++).c_str());  // �˿ں�
		std::string message = (*iter++);  // ����
		printf("netaddr : %s, port : %d, message : %s\n", netaddr.c_str(), port, message.c_str());

		// ʹ���̷߳��ͣ���ֹ��ַ���ɷ��ʻ�����ṩ�����⣬��������̿�ס
		struct socketmessagethread_data * smdata = new struct socketmessagethread_data();
		smdata->netaddr = netaddr;
		smdata->port = port;
		smdata->message = message;

		pthread_t pt = 0;
		pthread_create(&pt, nullptr, SendSocketMessageThread, (void *)smdata);

		strRet = "true";
		nRet = 0;
	}
	else if ("GetScreenSetting" == strMethod)  // ��ȡ��Ļ�ֱ���
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		int screenindex = atoi((*iter++).c_str());  // ��Ļ�±�
		printf("screenindex : %d\n", screenindex);

		char outbuf[1024] = { 0 };
		g2u("Linux�´����֧��", strlen("Linux�´����֧��"), outbuf, sizeof(outbuf));
		strRet = outbuf;  // strRet = "Linux�´����֧��"; strRet = u8"Linux�´����֧��"; ֮�����ʾ���룬����websocketת��ʧ�ܶ���

		nRet = 0;
	}
	else if ("SetScreenSetting" == strMethod)  // ������Ļ�ֱ���
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		int screenindex = atoi((*iter++).c_str());  // ��Ļ�±�
		std::string setting = (*iter++);  // ������Ϣ������GetScreenSetting�Ľ����д
		printf("screenindex : %d, setting : %s\n", screenindex, setting.c_str());

		char outbuf[1024] = { 0 };
		g2u("Linux�´����֧��", strlen("Linux�´����֧��"), outbuf, sizeof(outbuf));
		strRet = outbuf;  // strRet = "Linux�´����֧��"; strRet = u8"Linux�´����֧��"; ֮�����ʾ���룬����websocketת��ʧ�ܶ���

		nRet = 0;
	}
	else if ("GetFileBase64String" == strMethod)  // ȡ�ļ����ݵ�Base64����
	{
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string filename = (*iter++);  // �ļ���
		printf("filename 111 : %s\n", filename.c_str());

		std::string strBase64 = CFileHelper().File2Base64Str(filename.c_str());

		strRet = strBase64;
		nRet = 0;
	}
	else if ("GetFileBase64StringWithSkip" == strMethod)  // ȡ�ļ����ݵ�Base64����
	{
		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string filename = (*iter++);  // �ļ���
		int skiplength = atoi((*iter++).c_str());  // ����ָ������
		printf("filename : %s, skiplength : %d\n", filename.c_str(), skiplength);

		std::string strBase64 = CFileHelper().File2Base64StrWithSkip(filename.c_str(), skiplength);

		strRet = strBase64;
		nRet = 0;
	}
	else if ("Base64String2File" == strMethod)  // ���ļ����ݵ�Base64����д���ļ�
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string base64string = (*iter++);  // Base64��������
		std::string filename = (*iter++);  // �ļ���
		printf("base64string : %s, filename : %s\n", base64string.c_str(), filename.c_str());

		CFileHelper().Base64Str2File(filename.c_str(), base64string.c_str());

		strRet = "true";
		nRet = 0;
	}
	else if ("CopyFileOrDirectory" == strMethod)  // �����ļ���Ŀ¼
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string srcfilepath = (*iter++);  // Դ�ļ�·��
		std::string destfilepath = (*iter++);  // Ŀ���ļ�·��
		printf("srcfilepath : %s, destfilepath : %s\n", srcfilepath.c_str(), destfilepath.c_str());

		// û�к���֧�֣�ֱ��ʹ������������
		struct stat s_buf = {0};
		if (0 != stat(srcfilepath.c_str(), &s_buf))
		{
			printf("srcfilepath not exists\n");
		}
		else
		{
			std::string command;
			if (S_ISDIR(s_buf.st_mode))
			{
				command = "cp -rf ";
			}
			else
			{
				command = "cp ";
			}

			command += srcfilepath;
			command += " ";
			command += destfilepath;
			if (0 == system((char*)command.c_str()))
			{
				strRet = "true";
			}
		}

		nRet = 0;
	}
	else if ("DeleteFile" == strMethod)  // ɾ���ļ�
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string filename = (*iter++);  // �ļ�·��
		printf("filename : %s\n", filename.c_str());

		// ������ʹ��ͨ���
		if (nullptr != strstr(filename.c_str(), "*") || nullptr != strstr(filename.c_str(), "?"))
		{
			printf("invalid filename : * and ? not support\n", filename.c_str());
		}
		else
		{
			struct stat s_buf = {0};
			if (0 != stat(filename.c_str(), &s_buf))
			{
				printf("file not exists\n");
			}
			else
			{
				std::string command;
				if (S_ISREG(s_buf.st_mode))
				{
					command = "rm -f ";
					command += filename;
					if (0 == system((char*)command.c_str()))
					{
						strRet = "true";
					}
				}
			}
		}

		nRet = 0;
	}
	else if ("DeletePath" == strMethod)  // ɾ��Ŀ¼
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string filepath = (*iter++);  // Ŀ¼·��
		printf("filename : %s\n", filepath.c_str());

		// ������ʹ��ͨ���
		if (nullptr != strstr(filepath.c_str(), "*") || nullptr != strstr(filepath.c_str(), "?"))
		{
			printf("invalid filename : * and ? not support\n", filepath.c_str());
		}
		else
		{
			struct stat s_buf = {0};
			if (0 != stat(filepath.c_str(), &s_buf))
			{
				printf("path not exists\n");
			}
			else
			{
				std::string command;
				if (S_ISDIR(s_buf.st_mode))
				{
					command = "rm -rf ";

					command += filepath;
					command += "/*";  // ֻɾ��Ŀ¼���ݣ���ɾ��Ŀ¼����
					printf("command : %s\n", command.c_str());
					if (0 == system((char*)command.c_str()))
					{
						strRet = "true";
					}
				}
			}
		}
		
		nRet = 0;
	}
	else if ("RenameFile" == strMethod)  // �������ļ�
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string srcfilepath = (*iter++);  // Դ�ļ�·��
		std::string destfilepath = (*iter++);  // Ŀ���ļ�·��
		printf("srcfilepath : %s, destfilepath : %s\n", srcfilepath.c_str(), destfilepath.c_str());

		// ������ʹ��ͨ���
		if (nullptr != strstr(srcfilepath.c_str(), "*") || nullptr != strstr(srcfilepath.c_str(), "?")
			|| nullptr != strstr(destfilepath.c_str(), "*") || nullptr != strstr(destfilepath.c_str(), "?"))
		{
			printf("invalid filename : * and ? not support\n", srcfilepath.c_str(), destfilepath.c_str());
		}
		else
		{
			// û�к���֧�֣�ֱ��ʹ������������
			struct stat s_buf = {0};
			if (0 == stat(srcfilepath.c_str(), &s_buf))
			{
				if (!S_ISREG(s_buf.st_mode))
				{
					printf("srcfilepath is not file\n");
				}
				else
				{
					std::string command = "mv ";

					command += srcfilepath;
					command += " ";
					command += destfilepath;
					nRet = system((char*)command.c_str());
					printf("%s ret : %d\n", command.c_str(), nRet);

					strRet = "true";
				}
			}
		}
		
		nRet = 0;
	}
	else if ("IsFileExists" == strMethod)  // �ļ��Ƿ����
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string filename = (*iter++);  // �ļ�·��
		printf("filename : %s\n", filename.c_str());

		struct stat s_buf = {0};
		nRet = stat(filename.c_str(), &s_buf);
		if (0 == nRet)
		{
			strRet = "true";
		}
		printf("filename %s %s\n", filename.c_str(), (0 == nRet ? "exist" : "not exist"));

		nRet = 0;
	}
	else if ("File2String" == strMethod)  // �ļ���ȡΪ�ַ���
	{
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string filename = (*iter++);  // �ļ�·��
		printf("filename : %s\n", filename.c_str());

		struct stat s_buf = {0};
		if (0 == stat(filename.c_str(), &s_buf))
		{
			if (S_ISREG(s_buf.st_mode))
			{
				std::string strFileContent = CFileHelper().File2String(filename.c_str());
				printf("strFileContent : %s\n", strFileContent.c_str());

				strRet = strFileContent;
			}
			else
			{
				printf("%s is not file\n", filename.c_str());
			}
		}
		
		nRet = 0;
	}
	else if ("String2File" == strMethod)  // �ַ������浽�ļ�
	{
		strRet = "false";

		if (params.size() < 4) { printf("params miss, need 3 param\n"); return nRet; }

		std::string filename = (*iter++);  // �ļ�·��
		std::string filecontent = (*iter++);  // �ļ�����
		int bappend = atoi((*iter++).c_str());  // �ļ��Ƿ�׷�ӣ�1׷�ӣ�0����
		printf("filename : %s, filecontent : %s, bappend : %d\n", filename.c_str(), filecontent.c_str(), bappend);

		struct stat s_buf = {0};
		if (0 == stat(filename.c_str(), &s_buf) && S_ISDIR(s_buf.st_mode))  // ���ܴ���ͬ��Ŀ¼
		{
			printf("%s is directory\n", filename.c_str());
		}
		else
		{
			CFileHelper().String2File(filename.c_str(), filecontent.c_str(), bappend);
			strRet = "true";
		}

		nRet = 0;
	}
	else if ("CalculateMd5Digest" == strMethod)  // ����MD5
	{
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string datahexstring = (*iter++);  // �ֽ�16�����ַ���
		printf("datahexstring : %s\n", datahexstring.c_str());

		CUtils utils;

		int nDataLen = strlen(datahexstring.c_str()) / 2;
		unsigned char * pszData = new unsigned char[nDataLen + 2];
		memset(pszData, 0, nDataLen + 2);
		utils.StrtoHex((char *)datahexstring.c_str(), pszData);

		md5_ctx Md5Ctx;
		char digest[32] = { 0 };
		char digesthexstring[64 + 2] = { 0 };

		md5_init(&Md5Ctx);  // ��ʼ��
		md5_update(&Md5Ctx, nDataLen, pszData);  // md5����
		md5_digest(&Md5Ctx, 16, (unsigned char *)digest);  // ���ܺ������
		utils.HextoStr((unsigned char *)digest, 16, digesthexstring);
		printf("CalculateMd5Digest result : %s\n", digesthexstring);

		strRet = digesthexstring;
		nRet = 0;
	}
	else if ("CallJScriptWithOutput" == strMethod)  // ִ�д���JS����
	{
		strRet = "false";

		if (params.size() < 6) { printf("params miss, need 5 param\n"); return nRet; }

		std::string srcsessionname = (*iter++);  // Դsession���ƣ����ڽ������Ӧ���͸�˭��JS�������ʱ����ص�
		std::string callbackfuncname = (*iter++);  // �����Ӧ�ص�����
		std::string destsessionname = (*iter++);  // Ŀ��session���ƣ�������˭�������
		std::string functionname = (*iter++);  // ��������
		std::string param = (*iter++);  // ����
		printf("srcsessionname : %s, callbackfuncname : %s, destsessionname : %s, functionname : %s, param : %s\n", 
			srcsessionname.c_str(), callbackfuncname.c_str(), destsessionname.c_str(), functionname.c_str(), param.c_str());

		int nBuffLen = 1024 + strlen(srcsessionname.c_str()) + strlen(functionname.c_str()) + strlen(param.c_str());
		char * strCallbackJs = new char[nBuffLen];
		memset(strCallbackJs, 0, nBuffLen);
		sprintf(strCallbackJs, "%s('%s', '%s', '%s')", functionname.c_str(), param.c_str(), srcsessionname.c_str(), callbackfuncname.c_str());  // functionname(param, srcsessionname, callbackfuncname)
		int nRetLen = strlen(strCallbackJs);

		printf("mtx_session_data4send.lock ->\n");
		mtx_session_data4send.lock();  //���ķ��ͺ�����
		printf("mtx_session_data4send.lock <-\n");
		memset(session_data4send.buf, 0, sizeof(session_data4send.buf));
		memcpy(&session_data4send.buf[LWS_PRE], strCallbackJs, nRetLen);
		session_data4send.len = nRetLen;

		struct lws * wsi_session = messagehandle.GetSession(destsessionname);
		if (nullptr != wsi_session)
		{
			lws_write(wsi_session, &session_data4send.buf[LWS_PRE], session_data4send.len, LWS_WRITE_TEXT);
		}
		else
		{
			printf("GetSession failed, strSessionName : %s\n", destsessionname.c_str());
		}
		mtx_session_data4send.unlock();

		delete strCallbackJs;
		strCallbackJs = nullptr;

		strRet = "true";
		nRet = 0;
	}
	else if ("StartSocketService" == strMethod)  // ����Socket����
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		int port = atoi((*iter++).c_str());  // �����˿ں�
		std::string callbackfunction = (*iter++);  // �ص���������
		printf("port : %d, callbackfunction : %s\n", port, callbackfunction.c_str());

		StartSocketService(strSessionName, port, callbackfunction);

		strRet = "true";
		nRet = 0;
	}
	else if ("GetXmlParam" == strMethod)  // ��ȡXMLֵ
	{
		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string strFileName = (*iter++);  // xml�ļ���
		std::string strXPath = (*iter++);  // xml�ڵ�·��

		printf("strFileName : %s, strXPath : %s\n", strFileName.c_str(), strXPath.c_str());

		strRet = GetXmlParam(strFileName, strXPath);
		nRet = 0;
	}
	else if ("SetXmlParam" == strMethod)  // ����XMLֵ
	{
		strRet = "false";

		if (params.size() < 4) { printf("params miss, need 3 param\n"); return nRet; }

		std::string strFileName = (*iter++);  // xml�ļ���
		std::string strXPath = (*iter++);  // xml�ڵ�·��
		std::string strValue = (*iter++);  // xml�ڵ�ֵ

		printf("strFileName : %s, strXPath : %s, strValue : %s\n", strFileName.c_str(), strXPath.c_str(), strValue.c_str());

		nRet = SetXmlParam(strFileName, strXPath, strValue);
		if (-1 != nRet)
		{
			strRet = "true";
		}
		printf("SetXmlParam ret %d\n", nRet);

		nRet = 0;
	}
	else if ("GetSM4Key" == strMethod)  // ��ȡ��Կ�ַ���������Կ
	{
		strRet = "false";

		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		int nMaxPortNum = atoi((*iter++).c_str());  // �����˿ڣ�ͬʱ�������ٸ��̼߳�⴮�ڶ˿��Ƿ�����Ϣ
		std::string strTermNum = (*iter++);  // ����ȡ��Կ���ն˱�ţ���Կ�ַ����������˲��������ڱȶԴ���Կ�ַ������õ���Կ�Ƿ�����Ҫ���ն˱�ŵ���Կ

		printf("nMaxPortNum : %d, strTermNum : %s\n", nMaxPortNum, strTermNum.c_str());

		nRet = CKeyou::GetInstance()->GetSM4Key(strSessionName, nMaxPortNum, (char *)strTermNum.c_str());
		if (-1 != nRet)
		{
			strRet = "true";
		}
		printf("GetSM4Key ret %d\n", nRet);

		nRet = 0;
	}
	else if ("CancelGetKey" == strMethod)  // ȡ����ȡ��Կ�ַ���������Կ�������ȴ����ڶ˿���Ϣ�߳�
	{
		strRet = "false";

		nRet = CKeyou::GetInstance()->CancelGetKey();
		if (-1 != nRet)
		{
			strRet = "true";
		}
		printf("CancelGetKey ret %d\n", nRet);

		nRet = 0;
	}
	else if ("CompleteKey" == strMethod)  // ������Կ�ַ�����Կ�������
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		int nResult = atoi((*iter++).c_str());  // = 0ʧ�ܣ� = 1�ɹ�
		printf("nResult : %d(0 failed, 1 success)\n", nResult);

		nRet = CKeyou::GetInstance()->CompleteKey(nResult);
		if (-1 != nRet)
		{
			strRet = "true";
		}
		printf("CompleteKey ret %d\n", nRet);

		nRet = 0;
	}
	else if ("ReloadMainUrl" == strMethod)  // ҳ�����ʧ��ʱ�����¼�����ҳ��
	{
		strRet = "false";

		char outbuf[1024] = { 0 };
		g2u("Linux�´����֧��", strlen("Linux�´����֧��"), outbuf, sizeof(outbuf));
		strRet = outbuf;  // strRet = "Linux�´����֧��"; strRet = u8"Linux�´����֧��"; ֮�����ʾ���룬����websocketת��ʧ�ܶ���

		nRet = 0;
	}
	else if ("LoadSSMDServer" == strMethod)  // ����ȫ���ļ��ܣ�����SSMD����
	{
		strRet = "false";

		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string strFileFullPath = (*iter++);  // ssmd �������ȫ·��
		nRet = CSSMKeyou::GetInstance()->LoadSSMDServer(strFileFullPath.c_str());
		if (-1 != nRet)
		{
			strRet = "true";
		}
		printf("LoadSSMDServer ret %d\n", nRet);

		nRet = 0;
	}
	else if ("CreateSM2Key" == strMethod)  // ����ȫ���ļ��ܣ�����SM2Key
	{
		strRet = "false";

		strRet = CSSMKeyou::GetInstance()->CreateSM2Key();

		nRet = 0;
	}
	else if ("SetServerSM2PublicKey" == strMethod)  // ����ȫ���ļ��ܣ����ñ��ط���SM2��Կ
	{
		strRet = "false";
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string strServerSM2PublicKeyHex = (*iter++);  // ssmd ����SM2��Կ
		strRet = CSSMKeyou::GetInstance()->SetServerSM2PublicKey(strServerSM2PublicKeyHex.c_str());

		nRet = 0;
	}
	else if ("GetEnvelopeHmac" == strMethod)  // ����ȫ���ļ��ܣ���ȡ����mac
	{
		strRet = "false";
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string strSourceData = (*iter++);  // Դ����
		strRet = CSSMKeyou::GetInstance()->GetEnvelopeHmac(strSourceData.c_str());

		nRet = 0;
	}
	else if ("VerifySSMEnvelopeHmac" == strMethod)  // ����ȫ���ļ��ܣ���֤����mac
	{
		strRet = "false";
		if (params.size() < 4) { printf("params miss, need 3 param\n"); return nRet; }

		std::string strSourceData = (*iter++);  // ssmd �������ȫ·��
		std::string strHmacHex = (*iter++);  // ssmd �������ȫ·��
		std::string strHmacKeyByPkHex = (*iter++);  // ssmd �������ȫ·��
		strRet = CSSMKeyou::GetInstance()->VerifySSMEnvelopeHmac(strSourceData.c_str(), strHmacHex.c_str(), strHmacKeyByPkHex.c_str());

		nRet = 0;
	}
	else if ("ECBEncryptSSMEnvelope" == strMethod)  // ����ȫ���ļ��ܣ������ŷ�
	{
		strRet = "false";
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string strPlain = (*iter++);  // ��������
		strRet = CSSMKeyou::GetInstance()->ECBEncryptSSMEnvelope(strPlain.c_str());

		nRet = 0;
	}
	else if ("ECBDecryptSSMEnvelope" == strMethod)  // ����ȫ���ļ��ܣ������ŷ�
	{
		strRet = "false";
		if (params.size() < 3) { printf("params miss, need 2 param\n"); return nRet; }

		std::string strCipherHex = (*iter++);  // ��������
		std::string strKeyByClientPkHex = (*iter++);  // ��������
		strRet = CSSMKeyou::GetInstance()->ECBDecryptSSMEnvelope(strCipherHex.c_str(), strKeyByClientPkHex.c_str());

		nRet = 0;
	}
	else if ("String2HexString" == strMethod)
	{
		strRet = "false";
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string str = (*iter++);  // �ַ�������

		int nLen = strlen(str.c_str());
		char * hexstring = new char[nLen * 2 + 2];
		memset(hexstring, 0, nLen * 2 + 2);

		CUtils utils;
		utils.HextoStr((unsigned char *)str.c_str(), nLen, hexstring);
		strRet = hexstring;

		delete hexstring;

		nRet = 0;
	}
	else if ("HexString2String" == strMethod) 
	{

		strRet = "false";
		if (params.size() < 2) { printf("params miss, need 1 param\n"); return nRet; }

		std::string strhex = (*iter++);  // 16�����ַ�������

		int nLen = strlen(strhex.c_str());
		char * str = new char[nLen + 2];
		memset(str, 0, nLen + 2);

		CUtils utils;
		utils.StrtoHex((char *)strhex.c_str(), (unsigned char *)str);
		strRet = str;

		delete str;

		nRet = 0;
	}


	return nRet;
}
