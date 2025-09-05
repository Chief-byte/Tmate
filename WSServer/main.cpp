#include "stdafx.h"
#include "libwebsockets.h"
#include <signal.h>
#include <string.h>
#include <mutex>

#include "MessageHandle.h"

// 主线程退出循环标志，kill时触发
static volatile int exit_sig = 0;

void sighdl(int sig) {
	printf("SIGTERM %d received\n", sig);
	exit_sig = 1;
}

// 消息处理对象
MessageHandle messagehandle;
struct session_data session_data4send;
std::mutex mtx_session_data4send;  // WebSocket的会话user_session在收发时可能冲突，发送单独使用发送结构，并使用互斥锁控制
static int server_callback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
	switch (reason)
	{
		case LWS_CALLBACK_ESTABLISHED:       // 当服务器和客户端完成握手后
		{
			printf("client connected, user label: %ld\n", (long)user);

			break;
		}
		case LWS_CALLBACK_RECEIVE:           // 当接收到客户端发来的帧以后
		{
			/*
			// 方法参数中的user是会话上下文共用，收到消息和待发送消息时是传入的同一个指针，并发时会导致此变量冲突，更改为只用来收，需要发送时使用发送结构（且对发送结构进行加锁）
			struct session_data *data = (struct session_data *) user;
			// 判断是否最后一帧
			data->fin = lws_is_final_fragment(wsi);
			// 判断是否二进制消息
			data->bin = lws_frame_is_binary(wsi);
			// 对服务器的接收端进行流量控制，如果来不及处理，可以控制之
			// 下面的调用禁止在此连接上接收数据
			lws_rx_flow_control(wsi, 0);
			*/
			lws_rx_flow_control(wsi, 0);

			struct session_data *data = (struct session_data *) user;

			if (len < 0)  //如果接收的报文长度小于0，直接丢弃整个报文 
			{
				printf("message recvied(length : %ld): invalid data\n", len);
				memset(data->buf, 0, sizeof(data->buf));
				data->len = 0;
			}
			else
			{
				sprintf((char *)&data->buf[data->len], "%s", (char *)in);
				data->len += len;

				if (!lws_is_final_fragment(wsi))  // 不是最后一帧，待收到完整报文后再处理
				{
					printf("message recvied(length : %ld, strlen(in) : %ld): not final fragment, wait ...\n", len, strlen((char *)in));
				}
				else
				{
					printf("message recvied(length : %ld, strlen(data->buf) : %ld): %s\n", data->len, strlen((char *)data->buf), data->buf);

					// 把报文拷贝出来处理，否则，后面再就收报文，就冲掉(struct session_data *) user中的数据了，回导致前面处理过程中的使用的源数据发生变化
					int nBufLen = data->len;
					char * pszBuf = new char[nBufLen + 16];
					memset(pszBuf, 0, nBufLen + 16);
					memcpy(pszBuf, data->buf, nBufLen);

					// 清空session用户数据：每处理一次，把缓冲区清空一次
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

			// 可能准备写时触发了收，导致写的事件丢失，互斥锁锁死了，补偿一次写：如果有未发送的数据，则发送了并解锁
			lws_callback_on_writable(wsi);

			break;
		}
		case LWS_CALLBACK_SERVER_WRITEABLE:   // 当此连接可写时
		{
			/*
			// lws_write(wsi, &data->buf[LWS_PRE], data->len, LWS_WRITE_TEXT);
			if (session_data4send.len > 0)
			{
				printf("response data to write(length : %ld): %s\n", session_data4send.len, &session_data4send.buf[LWS_PRE]);

				lws_write(wsi, &session_data4send.buf[LWS_PRE], session_data4send.len, LWS_WRITE_TEXT);

				memset(session_data4send.buf, 0, sizeof(session_data4send.buf));
				session_data4send.len = 0;


				// 解锁发送结构：加锁在组建发送结构数据处
				printf("mtx_session_data4send.unlock ->\n");
				mtx_session_data4send.unlock();  //报文发送后会解锁
				printf("mtx_session_data4send.unlock <-\n");
			}
			else
			{
				printf("no response data to write\n");
			}

			// 下面的调用允许在此连接上接收数据
			// lws_rx_flow_control(wsi, 1);
			*/

			break;
		}
		case LWS_CALLBACK_CLOSED:
		{	
			printf("client closed, user label: %ld\n", (long)user);

			// 删除strSessionName，否则从strSessionName找到的wsi_session已经被libwebsockets库释放，再发送报文会导致程序异常崩溃
			printf("LWS_CALLBACK_CLOSED.lock ->\n");
			mtx_session_data4send.lock();  // 删除保存的session数据后会解锁
			printf("LWS_CALLBACK_CLOSED.lock <-\n");
			
			messagehandle.RemoveSession(wsi);
			mtx_session_data4send.unlock();

			break;
		}
	}

	// 回调函数最终要返回0，否则无法创建服务器
	return 0;
}

/**
 * 支持的WebSocket子协议数组
 * 子协议即JavaScript客户端WebSocket(url, protocols)第2参数数组的元素
 * 你需要为每种协议提供回调函数
 */
struct lws_protocols protocols[] = {
	{
		//协议名称，协议回调，接收缓冲区大小
		"ws", server_callback, sizeof(struct session_data), MAX_PAYLOAD_SIZE,
	},
	{
		nullptr, nullptr,   0 // 最后一个元素固定为此格式
	}
};

int main(int argc, char **argv)
{
	// 每次修改代码时应修改此日期以标识程序运行的版本，使用LFS或者PISA标识使用的SP协议版本
	// printf("WebSocket Server version 2025-02-12(LFS)\n");
	printf("WebSocket Server version 2025-06-16(PISA)\n");

	// 信号处理函数
	signal(SIGTERM, sighdl);

	// 命令行参数为监听端口号
	int nPort = 3899;  // 默认监听端口号 3899，只能启动一个默认端口，第二个会监听失败
	if (argc > 1)
	{
		nPort = atoi(argv[1]);
	}

	// 初始化MessageHandle
	messagehandle.Init();

	struct lws_context_creation_info ctx_info = { 0 };
	ctx_info.port = nPort;
	ctx_info.iface = nullptr; // 在所有网络接口上监听
	ctx_info.protocols = protocols;
	ctx_info.gid = -1;
	ctx_info.uid = -1;
	ctx_info.options = LWS_SERVER_OPTION_VALIDATE_UTF8;

	// 不处理wss协议
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
