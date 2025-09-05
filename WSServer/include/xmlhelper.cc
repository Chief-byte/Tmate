#include <stdio.h>
#include <stdlib.h>

#include "xmlhelper.h"

xmlXPathObjectPtr GetNodeset(xmlDocPtr pdoc, const xmlChar *xpath)
{
	xmlXPathContextPtr context = NULL;//XPath上下文指针
	xmlXPathObjectPtr result = NULL; //XPath结果指针
	context = xmlXPathNewContext(pdoc);

	if (pdoc == NULL) {
		printf("pdoc is NULL\n");
		return NULL;
	}

	if (xpath) {
		if (context == NULL) {
			printf("context is NULL\n");
			return NULL;
		}

		result = xmlXPathEvalExpression(xpath, context);
		xmlXPathFreeContext(context); //释放上下文指针
		if (result == NULL) {
			printf("xmlXPathEvalExpression return NULL\n");
			return NULL;
		}

		if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
			xmlXPathFreeObject(result);
			printf("nodeset is empty\n");
			return NULL;
		}
	}

	return result;
}

int CreateXmlPath(xmlDocPtr pdoc, std::string strParentXPath, std::string strNewNodeName) {
	xmlChar *xpath = BAD_CAST(strParentXPath.c_str()); //xpath语句
	xmlXPathObjectPtr result = GetNodeset(pdoc, xpath); //查询XPath表达式，得到一个查询结果

	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //获取查询到的节点指针集合
		if (nodeset->nodeNr > 0)
		{
			xmlNodePtr cur = nodeset->nodeTab[0];
			if (NULL != cur)
			{
				xmlNodePtr node = xmlNewNode(NULL, BAD_CAST(strNewNodeName.c_str()));
				xmlAddChild(cur, node);
			}
		}

		xmlXPathFreeObject(result);//释放结果指针
	}

	return 0;
}

int SetXmlParam(std::string strFileName, std::string strXPath, std::string strValue) {
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL;

	/*****************打开xml文档********************/
	xmlKeepBlanksDefault(0);//必须加上，防止程序把元素前后的空白文本符号当作一个node
	pdoc = xmlReadFile(strFileName.c_str(), "UTF-8", XML_PARSE_RECOVER);//libxml只能解析UTF-8格式数据
	if (pdoc == NULL)
	{
		printf("error:can't open file!\n");
		return -1;
	}
	/*****************获取xml文档对象的根节对象********************/
	proot = xmlDocGetRootElement(pdoc);
	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		return -1;
	}
	int nRet = -1;

	// 创建路径
	char szXPath[256] = { 0 };
	strcpy(szXPath, strXPath.c_str());  // /A/B/C/D/E

	char * pstrstr = strstr(szXPath + 1, "/");  // 根节点不能创建，+1 跳过根节点  /A/
	
	char * pParent = szXPath;
	char * pNewNodeName = NULL;
	while (NULL != pstrstr)
	{
		*pstrstr = '\0';  // pParent = /A
		pNewNodeName = pstrstr + 1;

		char * pnewstrstr = strstr(pNewNodeName, "/"); // /A/B/
		if (NULL != pnewstrstr)
		{
			*pnewstrstr = '\0';  // pNewNodeName = B
		}
		string strxpath = string(pParent) + "/" + string(pNewNodeName);
		xmlChar *xpath = BAD_CAST(strxpath.c_str()); //xpath语句
		xmlXPathObjectPtr result = GetNodeset(pdoc, xpath); //查询XPath表达式，得到一个查询结果
		if (!result)
		{
			// 路径不存在，创建该路径
			printf("CreateXmlPath(pdoc, %s, %s)\n", pParent, pNewNodeName);
			CreateXmlPath(pdoc, pParent, pNewNodeName);
		}

		if (NULL != pnewstrstr)
		{
			*pnewstrstr = '/';  // pNewNodeName = B/...
		}

		*pstrstr = '/';  // pParent = szXPath
		pstrstr = strstr(pstrstr + 1, "/");
	}

	xmlChar *xpath = BAD_CAST(strXPath.c_str()); //xpath语句
	xmlXPathObjectPtr result = GetNodeset(pdoc, xpath); //查询XPath表达式，得到一个查询结果
	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //获取查询到的节点指针集合
		if (nodeset->nodeNr > 0)
		{
			xmlNodePtr cur = nodeset->nodeTab[0];
			if (NULL != cur)
			{
				xmlNodeSetContent(cur, BAD_CAST(strValue.c_str()));
				nRet = xmlSaveFormatFile(strFileName.c_str(), pdoc, 1);
			}
		}

		xmlXPathFreeObject(result);//释放结果指针
	}

	/*****************释放资源********************/
	xmlFreeDoc(pdoc);
	xmlCleanupParser();
	xmlMemoryDump();

	return nRet;
}

std::string GetXmlParam(std::string strFileName, std::string strXPath) {
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL;

	/*****************打开xml文档********************/
	xmlKeepBlanksDefault(0);//必须加上，防止程序把元素前后的空白文本符号当作一个node
	pdoc = xmlReadFile(strFileName.c_str(), "UTF-8", XML_PARSE_RECOVER);//libxml只能解析UTF-8格式数据

	if (pdoc == NULL)
	{
		printf("error:can't open file!\n");
		return "";
	}

	/*****************获取xml文档对象的根节对象********************/
	proot = xmlDocGetRootElement(pdoc);

	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		return "";
	}

	xmlChar *xpath = BAD_CAST(strXPath.c_str()); //xpath语句
	xmlXPathObjectPtr result = GetNodeset(pdoc, xpath); //查询XPath表达式，得到一个查询结果
	if (result == NULL)
	{
		printf("result is NULL\n");
		return "";
	}

	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //获取查询到的节点指针集合
		if (nodeset->nodeNr > 0)
		{
			xmlNodePtr cur = nodeset->nodeTab[0];
			if (NULL != cur)
			{
				return std::string((char *)XML_GET_CONTENT(cur->xmlChildrenNode));
			}
		}

		xmlXPathFreeObject(result);//释放结果指针
	}

	/*****************释放资源********************/
	xmlFreeDoc(pdoc);
	xmlCleanupParser();
	xmlMemoryDump();

	return "";
}