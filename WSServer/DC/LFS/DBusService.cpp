#include "DBusService.h"
// DBus 消息处理  开始
// cd /usr/include/dbus-1.0
// sudo cp -r ./dbus ../
// sudo cp /usr/lib/x86_64-linux-gnu/dbus-1.0/include/dbus/* /usr/include/dbus
// 如果出现 undefined reference to symbol 'g_main_context_push_thread_default' 编译错误：
// sudo apt-get install libglib2.0-dev
#include <dbus/dbus-glib-lowlevel.h> /* for glib main loop */
#include <iostream>
#include "../DC/DC.h"

const char *version = "1.0";

const char *server_introspection_xml =
DBUS_INTROSPECT_1_0_XML_DOCTYPE_DECL_NODE
"<node>\n"
"  <interface name='org.freedesktop.DBus.Introspectable'>\n"
"    <method name='Introspect'>\n"
"      <arg name='data' type='s' direction='out' />\n"
"    </method>\n"
"  </interface>\n"

"  <interface name='org.freedesktop.DBus.Properties'>\n"
"    <method name='Get'>\n"
"      <arg name='interface' type='s' direction='in' />\n"
"      <arg name='property'  type='s' direction='in' />\n"
"      <arg name='value'     type='s' direction='out' />\n"
"    </method>\n"
"    <method name='GetAll'>\n"
"      <arg name='interface'  type='s'     direction='in'/>\n"
"      <arg name='properties' type='a{sv}' direction='out'/>\n"
"    </method>\n"
"  </interface>\n"

"  <interface name='org.lfs.windows_compatible_intf'>\n"
// "    <property name='Version' type='s' access='read' />\n"
"    <method name='event_callback' >\n"
"      <arg name='msg_id' direction='in' type='x'/>\n"
"      <arg name='pointer' direction='in' type='x'/>\n"
"    </method>\n"
"    <signal name='cmdComplete'>\n"
"      <arg type='x'/>\n"
"      <arg type='x'/>\n"
"    </signal>"
"    <signal name='eventArrived'>\n"
"      <arg type='x'/>\n"
"      <arg type='x'/>\n"
"    </signal>"
"    <signal name='executed'>\n"
"      <arg type='x'/>\n"
"    </signal>"
"    <signal name='infoGot'>\n"
"      <arg type='x'/>\n"
"    </signal>"
"  </interface>\n"

"</node>\n";

extern long OnXFSManagerMessage(char * strDCName, long nMessageID, long nPtrWfsRet);

DBusHandlerResult server_get_properties_handler(const char *property, DBusConnection *conn, DBusMessage *reply)
{
	if (!strcmp(property, "Version")) {
		dbus_message_append_args(reply,
			DBUS_TYPE_STRING, &version,
			DBUS_TYPE_INVALID);
	}
	else
		// Unknown property
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

	if (!dbus_connection_send(conn, reply, NULL))
		return DBUS_HANDLER_RESULT_NEED_MEMORY;
	return DBUS_HANDLER_RESULT_HANDLED;
}

DBusHandlerResult server_get_all_properties_handler(DBusConnection *conn, DBusMessage *reply)
{
	DBusHandlerResult result;
	DBusMessageIter array, dict, iter, variant;
	const char *property = "Version";

	result = DBUS_HANDLER_RESULT_NEED_MEMORY;

	dbus_message_iter_init_append(reply, &iter);
	dbus_message_iter_open_container(&iter, DBUS_TYPE_ARRAY, "{sv}", &array);

	// Append all properties name/value pairs
	property = "Version";
	dbus_message_iter_open_container(&array, DBUS_TYPE_DICT_ENTRY, NULL, &dict);
	dbus_message_iter_append_basic(&dict, DBUS_TYPE_STRING, &property);
	dbus_message_iter_open_container(&dict, DBUS_TYPE_VARIANT, "s", &variant);
	dbus_message_iter_append_basic(&variant, DBUS_TYPE_STRING, &version);
	dbus_message_iter_close_container(&dict, &variant);
	dbus_message_iter_close_container(&array, &dict);

	dbus_message_iter_close_container(&iter, &array);

	if (dbus_connection_send(conn, reply, NULL))
		result = DBUS_HANDLER_RESULT_HANDLED;
	return result;
}

DBusHandlerResult server_message_handler(DBusConnection *conn, DBusMessage *message, void *data)
{
	DBusHandlerResult result;
	DBusMessage *reply = NULL;
	DBusError err;
	bool quit = false;

	fprintf(stderr, "Got D-Bus request: %s.%s on %s\n",
		dbus_message_get_interface(message),
		dbus_message_get_member(message),
		dbus_message_get_path(message));

	dbus_error_init(&err);

	if (dbus_message_is_method_call(message, DBUS_INTERFACE_INTROSPECTABLE, "Introspect")) {

		if (!(reply = dbus_message_new_method_return(message)))
			goto fail;

		dbus_message_append_args(reply,
			DBUS_TYPE_STRING, &server_introspection_xml,
			DBUS_TYPE_INVALID);

	}
	else if (dbus_message_is_method_call(message, DBUS_INTERFACE_PROPERTIES, "Get")) {
		const char *interface, *property;

		if (!dbus_message_get_args(message, &err,
			DBUS_TYPE_STRING, &interface,
			DBUS_TYPE_STRING, &property,
			DBUS_TYPE_INVALID))
			goto fail;

		if (!(reply = dbus_message_new_method_return(message)))
			goto fail;

		result = server_get_properties_handler(property, conn, reply);
		dbus_message_unref(reply);
		return result;

	}
	else if (dbus_message_is_method_call(message, DBUS_INTERFACE_PROPERTIES, "GetAll")) {

		if (!(reply = dbus_message_new_method_return(message)))
			goto fail;

		result = server_get_all_properties_handler(conn, reply);
		dbus_message_unref(reply);
		return result;

	}
	else if (dbus_message_is_method_call(message, "org.lfs.windows_compatible_intf", "event_callback")) {
		DBusError err;
		dbus_error_init(&err);

		const char * path = NULL;
		// 获取路径，判断是哪个模块的事件
		if (NULL == (path = dbus_message_get_path(message)))
		{
			printf("*** get path failed when event_callback is called\n");
		}

		// 从path（例如 /lfs/dcidcardreader/listener）中截出DCName
		std::string strDCName = "";

		std::string strPath = path;
		strPath.replace(strPath.find("/lfs"), 1, "");
		char * pDCName = strstr((char *)path, "/DC");
		if (NULL != pDCName)
		{
			char * pDCNameEnd = strstr(pDCName + 2, "/");
			if (NULL != pDCNameEnd)
			{
				strDCName = std::string(pDCName + 1, pDCNameEnd - (pDCName + 1));
				printf("server_message_handler strDCName = %s\n", strDCName.c_str());
			}
		}

		int64_t nMessageID = 0;
		int64_t nPtrWfsRet = 0;
		printf("*** event_callback is called\n");
		if (true == dbus_message_get_args(message, &err, DBUS_TYPE_INT64, &nMessageID, DBUS_TYPE_INT64, &nPtrWfsRet, DBUS_TYPE_INVALID))
		{
			printf("*** event_callback is called (%ld, %ld)\n", nMessageID, nPtrWfsRet);

			OnXFSManagerMessage((char *)strDCName.c_str(), nMessageID, nPtrWfsRet);
		}
		else
		{
			printf("*** dbus_message_get_args failed\n");
			if (dbus_error_is_set(&err))
			{
				printf("*** dbus_message_get_args failed : %s\n", err.message);
			}
		}

		if (!(reply = dbus_message_new_method_return(message)))
			goto fail;
	}
	else
		return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

fail:
	if (dbus_error_is_set(&err)) {
		if (reply)
			dbus_message_unref(reply);
		reply = dbus_message_new_error(message, err.name, err.message);
		dbus_error_free(&err);
	}
	if (!reply)
		return DBUS_HANDLER_RESULT_NEED_MEMORY;

	// Send the reply which might be an error one too.
	result = DBUS_HANDLER_RESULT_HANDLED;
	if (!dbus_connection_send(conn, reply, NULL))
		result = DBUS_HANDLER_RESULT_NEED_MEMORY;
	dbus_message_unref(reply);

	if (quit) {
		fprintf(stderr, "Server exiting...\n");
	}
	return result;
}

DBusObjectPathVTable server_vtable;

DBusConnection * StartupDBus(char * szPathName)
{
	server_vtable.message_function = server_message_handler;

	DBusConnection *conn = NULL;
	DBusError err;
	int rv;

	dbus_error_init(&err);

	// connect to the daemon bus
	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
	if (!conn) {
		fprintf(stderr, "Failed to get a session DBus connection: %s\n", err.message);
		dbus_error_free(&err);
	}

	char szDBusName[128] = { 0 };
	sprintf(szDBusName, "org.lfs.manager.p%d", getpid());

	// rv = dbus_bus_request_name(conn, "org.example.TestServer", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
	rv = dbus_bus_request_name(conn, szDBusName, DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
	if (rv != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
		fprintf(stderr, "Failed to request name on bus: %s\n", err.message);
		dbus_error_free(&err);
	}

	// 增加DBus访问路径
	char szarrPath[][64] =
	{
		"/lfs/DCCardReader/listener",  // 接触读卡器
		"/lfs/DCChipCardReader/listener",  // IC读卡器
		"/lfs/DCRFChipCardReader/listener",  // 非接IC读卡器
		"/lfs/DCIDCardReader/listener",  // 身份证
		"/lfs/DCUKeyReader/listener",  // UKey条码阅读器
		"/lfs/DCPinPad/listener",  // 密码键盘
		"/lfs/DCJournalPrinter/listener",  // 流水打印机
		"/lfs/DCReceiptPrinter/listener",  // 凭条打印机
		"/lfs/DCPassBookPrinter/listener",  // 存折打印机
		"/lfs/DCStatementPrinter/listener",  // 对账单打印机
		"/lfs/DCInvoicePrinter/listener",  // 发票打印机
		"/lfs/DCDocumentPrinter/listener",  // 文档打印机
		"/lfs/DCDocumentRetractPrinter/listener",  // 文档回收
		"/lfs/DCFingerPrinter/listener",  // 指纹仪：基于打印机的指纹仪
		"/lfs/DCCashAcceptor/listener",  // 存款模块
		"/lfs/DCCashDispenser/listener",  // 取款模块
		"/lfs/DCOperatorPanel/listener",  // 操作员面板
		"/lfs/DCSensorsAndIndicators/listener",  // 传感器/指示灯
		"/lfs/DCVendorMode/listener",  // 厂商模式
		"/lfs/DCScanner/listener",  // 扫描仪
		"/lfs/DCBarcode/listener",  // 二维码
		"/lfs/DCCardDispenser/listener",  // 发卡
		"/lfs/DCCamera/listener"   // 摄像头
	};

	// if (!dbus_connection_register_object_path(conn, "/org/example/TestObject", &server_vtable, NULL)) {
	for (int nLoop = 0; nLoop < (int)sizeof(szarrPath) / 64; nLoop++)
	{
		if (!dbus_connection_register_object_path(conn, szarrPath[nLoop], &server_vtable, NULL)) {
			fprintf(stderr, "Failed to register a object path for %s\n", szarrPath[nLoop]);
			dbus_error_free(&err);

			break;
		}
	}

	printf("Starting dbus tiny server v%s\n", version);

	return conn;
}
// DBus 消息处理  结束

void * DBusService::Init(LPVOID lpParam)
{
	DBusConnection * dbusconn = NULL;
	// llx 启动dbus
	dbusconn = StartupDBus((char *)std::string("").c_str());

	GMainContext* main_context_ = g_main_context_new();
	g_main_context_push_thread_default(main_context_);

	GMainLoop* main_loop_ = g_main_loop_new(main_context_, TRUE);

	// llx 关联DBus消息处理到主消息循环
	if (NULL != dbusconn)
	{
		dbus_connection_setup_with_g_main(dbusconn, main_context_);
	}

	g_main_loop_run(main_loop_);

	// Release GLib resources.
	g_main_loop_unref(main_loop_);
	main_loop_ = nullptr;

	g_main_context_pop_thread_default(main_context_);
	g_main_context_unref(main_context_);
	main_context_ = nullptr;

	printf("DBusService::Init end\n");
}
