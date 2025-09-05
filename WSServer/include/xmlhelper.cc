#include <stdio.h>
#include <stdlib.h>

#include "xmlhelper.h"

xmlXPathObjectPtr GetNodeset(xmlDocPtr pdoc, const xmlChar *xpath)
{
	xmlXPathContextPtr context = NULL;//XPath������ָ��
	xmlXPathObjectPtr result = NULL; //XPath���ָ��
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
		xmlXPathFreeContext(context); //�ͷ�������ָ��
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
	xmlChar *xpath = BAD_CAST(strParentXPath.c_str()); //xpath���
	xmlXPathObjectPtr result = GetNodeset(pdoc, xpath); //��ѯXPath���ʽ���õ�һ����ѯ���

	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //��ȡ��ѯ���Ľڵ�ָ�뼯��
		if (nodeset->nodeNr > 0)
		{
			xmlNodePtr cur = nodeset->nodeTab[0];
			if (NULL != cur)
			{
				xmlNodePtr node = xmlNewNode(NULL, BAD_CAST(strNewNodeName.c_str()));
				xmlAddChild(cur, node);
			}
		}

		xmlXPathFreeObject(result);//�ͷŽ��ָ��
	}

	return 0;
}

int SetXmlParam(std::string strFileName, std::string strXPath, std::string strValue) {
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL;

	/*****************��xml�ĵ�********************/
	xmlKeepBlanksDefault(0);//������ϣ���ֹ�����Ԫ��ǰ��Ŀհ��ı����ŵ���һ��node
	pdoc = xmlReadFile(strFileName.c_str(), "UTF-8", XML_PARSE_RECOVER);//libxmlֻ�ܽ���UTF-8��ʽ����
	if (pdoc == NULL)
	{
		printf("error:can't open file!\n");
		return -1;
	}
	/*****************��ȡxml�ĵ�����ĸ��ڶ���********************/
	proot = xmlDocGetRootElement(pdoc);
	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		return -1;
	}
	int nRet = -1;

	// ����·��
	char szXPath[256] = { 0 };
	strcpy(szXPath, strXPath.c_str());  // /A/B/C/D/E

	char * pstrstr = strstr(szXPath + 1, "/");  // ���ڵ㲻�ܴ�����+1 �������ڵ�  /A/
	
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
		xmlChar *xpath = BAD_CAST(strxpath.c_str()); //xpath���
		xmlXPathObjectPtr result = GetNodeset(pdoc, xpath); //��ѯXPath���ʽ���õ�һ����ѯ���
		if (!result)
		{
			// ·�������ڣ�������·��
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

	xmlChar *xpath = BAD_CAST(strXPath.c_str()); //xpath���
	xmlXPathObjectPtr result = GetNodeset(pdoc, xpath); //��ѯXPath���ʽ���õ�һ����ѯ���
	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //��ȡ��ѯ���Ľڵ�ָ�뼯��
		if (nodeset->nodeNr > 0)
		{
			xmlNodePtr cur = nodeset->nodeTab[0];
			if (NULL != cur)
			{
				xmlNodeSetContent(cur, BAD_CAST(strValue.c_str()));
				nRet = xmlSaveFormatFile(strFileName.c_str(), pdoc, 1);
			}
		}

		xmlXPathFreeObject(result);//�ͷŽ��ָ��
	}

	/*****************�ͷ���Դ********************/
	xmlFreeDoc(pdoc);
	xmlCleanupParser();
	xmlMemoryDump();

	return nRet;
}

std::string GetXmlParam(std::string strFileName, std::string strXPath) {
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL;

	/*****************��xml�ĵ�********************/
	xmlKeepBlanksDefault(0);//������ϣ���ֹ�����Ԫ��ǰ��Ŀհ��ı����ŵ���һ��node
	pdoc = xmlReadFile(strFileName.c_str(), "UTF-8", XML_PARSE_RECOVER);//libxmlֻ�ܽ���UTF-8��ʽ����

	if (pdoc == NULL)
	{
		printf("error:can't open file!\n");
		return "";
	}

	/*****************��ȡxml�ĵ�����ĸ��ڶ���********************/
	proot = xmlDocGetRootElement(pdoc);

	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		return "";
	}

	xmlChar *xpath = BAD_CAST(strXPath.c_str()); //xpath���
	xmlXPathObjectPtr result = GetNodeset(pdoc, xpath); //��ѯXPath���ʽ���õ�һ����ѯ���
	if (result == NULL)
	{
		printf("result is NULL\n");
		return "";
	}

	if (result)
	{
		xmlNodeSetPtr nodeset = result->nodesetval; //��ȡ��ѯ���Ľڵ�ָ�뼯��
		if (nodeset->nodeNr > 0)
		{
			xmlNodePtr cur = nodeset->nodeTab[0];
			if (NULL != cur)
			{
				return std::string((char *)XML_GET_CONTENT(cur->xmlChildrenNode));
			}
		}

		xmlXPathFreeObject(result);//�ͷŽ��ָ��
	}

	/*****************�ͷ���Դ********************/
	xmlFreeDoc(pdoc);
	xmlCleanupParser();
	xmlMemoryDump();

	return "";
}