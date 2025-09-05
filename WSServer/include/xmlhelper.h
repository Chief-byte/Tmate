#ifndef CEF_TESTS_CEFCLIENT_EXTENSION_XMLHELPER_H_
#define CEF_TESTS_CEFCLIENT_EXTENSION_XMLHELPER_H_
#pragma once

// cd /usr/include/libxml2
// sudo cp -r libxml /usr/include/
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpointer.h>
#include <string>
#include <string.h>
using namespace std;

xmlXPathObjectPtr GetNodeset(xmlDocPtr pdoc, const xmlChar *xpath);

std::string GetXmlParam(std::string strFileName, std::string strXPath);
int CreateXmlPath(xmlDocPtr pdoc, std::string strParentXPath, std::string strNewNodeName);
int SetXmlParam(std::string strFileName, std::string strXPath, std::string strValue);

#endif  // CEF_TESTS_CEFCLIENT_EXTENSION_XMLHELPER_H_