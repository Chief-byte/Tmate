#include "libwebsockets.h"
#include <signal.h>
#include <string.h>
#include <mutex>

#include "MessageHandle.h"

// ���߳��˳�ѭ����־��killʱ����
static volatile int exit_sig = 0;

void sighdl(int sig) {
	printf("SIGTERM %d received\n", sig);
	exit_sig = 1;
}

// ��Ϣ��������
MessageHandle messagehandle;
struct session_data session_data4send;
std::mutex mtx_session_data4send;  // WebSocket�ĻỰuser_session���շ�ʱ���ܳ�ͻ�����͵���ʹ�÷��ͽṹ����ʹ�û���������
static int server_callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
	switch (reason)
	{
		case LWS_CALLBACK_ESTABLISHED:       // ���������Ϳͻ���������ֺ�
		{
			printf("client connected, user label: %ld\n", (long)user);

			break;
		}
		case LWS_CALLBACK_RECEIVE:           // �����յ��ͻ��˷�����֡�Ժ�
		{
			/*
			// ���������е�user�ǻỰ�����Ĺ��ã��յ���Ϣ�ʹ�������Ϣʱ�Ǵ����ͬһ��ָ�룬����ʱ�ᵼ�´˱�����ͻ������Ϊֻ�����գ���Ҫ����ʱʹ�÷��ͽṹ���ҶԷ��ͽṹ���м�����
			struct session_data *data = (struct session_data *) user;
			// �ж��Ƿ����һ֡
			data->fin = lws_is_final_fragment(wsi);
			// �ж��Ƿ��������Ϣ
			data->bin = lws_frame_is_binary(wsi);
			// �Է������Ľ��ն˽����������ƣ�������������������Կ���֮
			// ����ĵ��ý�ֹ�ڴ������Ͻ�������
			lws_rx_flow_control(wsi, 0);
			*/
			lws_rx_flow_control(wsi, 0);

			struct session_data *data = (struct session_data *) user;

			if (len < 0)  //������յı��ĳ���С��0��ֱ�Ӷ����������� 
			{
				printf("message recvied(length : %ld): invalid data\n", len);
				memset(data->buf, 0, sizeof(data->buf));
				data->len = 0;
			}
			else
			{
				sprintf((char *)&data->buf[data->len], "%s", (char *)in);
				data->len += len;

				if (!lws_is_final_fragment(wsi))  // �������һ֡�����յ��������ĺ��ٴ���
				{
					printf("message recvied(length : %ld, strlen(in) : %ld): not final fragment, wait ...\n", len, strlen((char *)in));
				}
				else
				{
					printf("message recvied(length : %ld, strlen(data->buf) : %ld): %s\n", data->len, strlen((char *)data->buf), data->buf);

					// �ѱ��Ŀ����������������򣬺����پ��ձ��ģ��ͳ��(struct session_data *) user�е������ˣ��ص���ǰ�洦�������е�ʹ�õ�Դ���ݷ����仯
					int nBufLen = data->len;
					char * pszBuf = new char[nBufLen + 16];
					memset(pszBuf, 0, nBufLen + 16);
					memcpy(pszBuf, data->buf, nBufLen);

					// ���session�û����ݣ�ÿ����һ�Σ��ѻ��������һ��
					memset(data->buf, 0, sizeof(data->buf));
					data->len = 0;

					int nRet = messagehandle.Process(pszBuf, nBufLen, wsi, user);
					if (nRet < 0)
					{
						printf("message process failed(ret : %d)\n", nRet);
					}
				}
			}

			lws_rx_flow_control(wsi, 1);

			// ����׼��дʱ�������գ�����д���¼���ʧ�������������ˣ�����һ��д�������δ���͵����ݣ������˲�����
			lws_callback_on_writable(wsi);

			break;
		}
		case LWS_CALLBACK_SERVER_WRITEABLE:   // �������ӿ�дʱ
		{
			/*
			// lws_write(wsi, &data->buf[LWS_PRE], data->len, LWS_WRITE_TEXT);
			if (session_data4send.len > 0)
			{
				printf("response data to write(length : %ld): %s\n", session_data4send.len, &session_data4send.buf[LWS_PRE]);

				lws_write(wsi, &session_data4send.buf[LWS_PRE], session_data4send.len, LWS_WRITE_TEXT);

				memset(session_data4send.buf, 0, sizeof(session_data4send.buf));
				session_data4send.len = 0;


				// �������ͽṹ���������齨���ͽṹ���ݴ�
				printf("mtx_session_data4send.unlock ->\n");
				mtx_session_data4send.unlock();  //���ķ��ͺ�����
				printf("mtx_session_data4send.unlock <-\n");
			}
			else
			{
				printf("no response data to write\n");
			}

			// ����ĵ��������ڴ������Ͻ�������
			// lws_rx_flow_control(wsi, 1);
			*/

			break;
		}
		case LWS_CALLBACK_CLOSED:
		{	
			printf("client closed, user label: %ld\n", (long)user);

			// ɾ��strSessionName�������strSessionName�ҵ���wsi_session�Ѿ���libwebsockets���ͷţ��ٷ��ͱ��Ļᵼ�³����쳣����
			printf("LWS_CALLBACK_CLOSED.lock ->\n");
			mtx_session_data4send.lock();  // ɾ�������session���ݺ�����
			printf("LWS_CALLBACK_CLOSED.lock <-\n");
			
			messagehandle.RemoveSession(wsi);
			mtx_session_data4send.unlock();

			break;
		}
	}

	// �ص���������Ҫ����0�������޷�����������
	return 0;
}

/**
 * ֧�ֵ�WebSocket��Э������
 * ��Э�鼴JavaScript�ͻ���WebSocket(url, protocols)��2���������Ԫ��
 * ����ҪΪÿ��Э���ṩ�ص�����
 */
struct lws_protocols protocols[] = {
	{
		//Э�����ƣ�Э��ص������ջ�������С
		"ws", server_callback, sizeof(struct session_data), MAX_PAYLOAD_SIZE,
	},
	{
		nullptr, nullptr,   0 // ���һ��Ԫ�ع̶�Ϊ�˸�ʽ
	}
};

int main(int argc, char **argv)
{
	// ÿ���޸Ĵ���ʱӦ�޸Ĵ������Ա�ʶ�������еİ汾��ʹ��LFS����PISA��ʶʹ�õ�SPЭ��汾
	// printf("WebSocket Server version 2025-02-12(LFS)\n");
	printf("WebSocket Server version 2025-06-16(PISA)\n");

	// �źŴ�������
	signal(SIGTERM, sighdl);

	// �����в���Ϊ�����˿ں�
	int nPort = 3899;  // Ĭ�ϼ����˿ں� 3899��ֻ������һ��Ĭ�϶˿ڣ��ڶ��������ʧ��
	if (argc > 1)
	{
		nPort = atoi(argv[1]);
	}

	// ��ʼ��MessageHandle
	messagehandle.Init();

	struct lws_context_creation_info ctx_info = { 0 };
	ctx_info.port = nPort;
	ctx_info.iface = nullptr; // ����������ӿ��ϼ���
	ctx_info.protocols = protocols;
	ctx_info.gid = -1;
	ctx_info.uid = -1;
	ctx_info.options = LWS_SERVER_OPTION_VALIDATE_UTF8;

	// ������wssЭ��
	// ctx_info.ssl_ca_filepath = "../ca/ca-cert.pem";
	// ctx_info.ssl_cert_filepath = "./server-cert.pem";
	// ctx_info.ssl_private_key_filepath = "./server-key.pem";
	ctx_info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
	//ctx_info.options |= LWS_SERVER_OPTION_REQUIRE_VALID_OPENSSL_CLIENT_CERT;

	struct lws_context *context = lws_create_context(&ctx_info);
	while (!exit_sig)
	{
		lws_service(context, 1000);
	}

	printf("main loop end, exit\n");
	lws_context_destroy(context);

	return 0;
}
