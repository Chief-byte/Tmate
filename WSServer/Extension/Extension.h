#pragma once

#include <list>
#include <string>
using namespace std;

class Extension
{
public:
	static int CallExtension(string strSessionName, list<string> params, string & strRet);
};
