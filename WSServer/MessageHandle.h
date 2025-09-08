#pragma once

#include "stdafx.h"
#include "libwebsockets.h"
#include <string.h>
#include <map>

class MessageHandle
{
public :
	void Init();
	int Process(char * recvbuf, size_t len, struct lws *wsi, void *user);

	std::map<string, struct lws *> m_mapSession;
	struct lws * GetSession(string strSessionName);
	string GetSessionName(struct lws * wsi_session);
	void SetSession(string strSessionName, struct lws * _wsi_session);
	void RemoveSession(struct lws * wsi_session);
};

