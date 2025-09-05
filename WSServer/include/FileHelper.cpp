// FileHelper.cpp: implementation of the CFileHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "FileHelper.h"
#include "Base64.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define		MAX_FILESIZE_ALLOWED		1024*1024*16
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//##ModelId=48C7876C0104
CFileHelper::CFileHelper()
{

}

//##ModelId=48C7876C0105
CFileHelper::~CFileHelper()
{

}

//##ModelId=48C7876C00FC
bool CFileHelper::WriteFile_Append(const char * strFilePath, const char * strData)
{
	FILE * fp = NULL;
	if ((fp = fopen(strFilePath, "a+") ) != NULL)
	{
		fprintf(fp, strData);
		fflush(fp);
		fclose(fp);
		return true;
	}
	return false;
}

//##ModelId=48C7876C00F2
bool CFileHelper::WriteFile_Cover(const char * strFilePath, const char * strData)
{
	FILE * fp = NULL;
	if ((fp = fopen(strFilePath, "w") ) != NULL)
	{
		fprintf(fp, strData);
		fflush(fp);
		fclose(fp);
		return true;
	}
	return false;
}

//##ModelId=48C7876C00EF
std::string CFileHelper::File2Base64Str(const char * strFilePath)
{
	std::string strRet;
	FILE * fp = NULL;
	if ((fp = fopen(strFilePath, "a+")) != NULL)
	{
		struct stat statbuf;
		stat(strFilePath, &statbuf);

		long dwLength = statbuf.st_size;
		if (dwLength <= MAX_FILESIZE_ALLOWED)
		{
			unsigned char* bufsrc = new unsigned char[dwLength];
			long iRead = fread(bufsrc, 1, dwLength, fp);
			if (iRead > 0 && iRead <= dwLength)
			{
				char* bufdest = new char[iRead*4/3+6];
				memset(bufdest, 0, iRead*4/3+6);
				int len = CBase64::EncodeBase64(bufsrc, bufdest, iRead);
				strRet = std::string(bufdest, len);
				delete []bufdest;
			}
			delete []bufsrc;
		}

		fclose(fp);
		fp = NULL;
	}
	return strRet;
}

//##ModelId=48C7876C00EF
std::string CFileHelper::File2Base64StrWithSkip(const char * strFilePath, long nSkipLength)
{
	std::string strRet;
	if (nSkipLength < 0)
	{
		return strRet;
	}


	FILE * fp = NULL;
	if ((fp = fopen(strFilePath, "a+")) != NULL)
	{
		struct stat statbuf;
		stat(strFilePath, &statbuf);

		long dwLength = statbuf.st_size;
		dwLength -= nSkipLength;
		if (dwLength <= MAX_FILESIZE_ALLOWED)
		{
			unsigned char* bufsrc = new unsigned char[dwLength];
			fseek(fp, nSkipLength, SEEK_SET);
			long iRead = fread(bufsrc, 1, dwLength, fp);
			if (iRead > 0 && iRead <= dwLength)
			{
				char* bufdest = new char[iRead * 4 / 3 + 6];
				memset(bufdest, 0, iRead * 4 / 3 + 6);
				int len = CBase64::EncodeBase64(bufsrc, bufdest, iRead);
				strRet = std::string(bufdest, len);
				delete[]bufdest;
			}
			delete[]bufsrc;
		}

		fclose(fp);
		fp = NULL;
	}
	return strRet;
}

//##ModelId=48C7876C00EB
bool CFileHelper::Base64Str2File(const char * strFilePath, const char * strBase64)
{
	MakeDirectory(strFilePath);

	bool bRet = false;
	size_t srclen = strlen(strBase64);
	if (srclen > 0 && srclen <= MAX_FILESIZE_ALLOWED)
	{
		unsigned char* bufdest = new unsigned char[srclen/4*3+6];
		memset(bufdest, 0, srclen/4*3+6);
		int destlen = CBase64::DecodeBase64(strBase64, bufdest, srclen);
		if (destlen > 0)
		{
			FILE * fp = NULL;
			if ((fp = fopen(strFilePath, "wb")) != NULL)
			{
				fwrite(bufdest, 1, destlen, fp);
				fclose(fp);
				bRet = true;
			}
		}
		delete []bufdest;
	}
	return bRet;
}

std::string CFileHelper::File2String(const char * strFilePath)
{
	std::string strRet;

	if (NULL == strFilePath)
	{
		return strRet;
	}
	
	FILE * fp = NULL;
	if ((fp = fopen(strFilePath, "a+")) != NULL)
	{
		struct stat statbuf;
		stat(strFilePath, &statbuf);

		long dwLength = statbuf.st_size;
		if (dwLength > 0)
		{
			unsigned char * bufsrc = new unsigned char[dwLength + 2];
			memset(bufsrc, 0, (dwLength + 2) * sizeof(unsigned char));
			
			long nRead = fread(bufsrc, 1, dwLength, fp);
			if (nRead > 0 && nRead <= dwLength)
			{
				strRet = std::string((char *)bufsrc, nRead);
			}
			
			delete []bufsrc;
		}

		fclose(fp);
		fp = NULL;
	}

	return strRet;
}

std::string CFileHelper::File2StringMaxLen(const char * strFilePath, int nMaxLen)
{
	std::string strRet;

	if (NULL == strFilePath)
	{
		return strRet;
	}

	FILE * fp = NULL;
	if ((fp = fopen(strFilePath, "a+")) != NULL)
	{
		struct stat statbuf;
		stat(strFilePath, &statbuf);
		
		long dwLength = statbuf.st_size;
		if ((int)dwLength > nMaxLen)
		{
			dwLength = nMaxLen;
		}

		if (dwLength > 0)
		{
			unsigned char * bufsrc = new unsigned char[dwLength + 2];
			memset(bufsrc, 0, (dwLength + 2) * sizeof(unsigned char));
			
			long nRead = fread(bufsrc, 1, dwLength, fp);
			if (nRead > 0 && nRead <= dwLength)
			{
				strRet = std::string((char *)bufsrc, nRead);
			}
			
			delete []bufsrc;
		}

		fclose(fp);
		fp = NULL;
	}

	return strRet;
}

bool CFileHelper::String2File(const char * strFilePath, const char * strString, bool bAppend)
{
	MakeDirectory(strFilePath);

	bool bRet = false;
	size_t srclen = strlen(strString);

	FILE * fp = NULL;
	if ((fp = fopen(strFilePath, (true == bAppend ? "a+" : "w"))) != NULL)
	{
		if (true == bAppend)
		{
			fseek(fp, 0, SEEK_END);
		}
		else
		{
			int nRet = truncate(strFilePath, 0);
			if (nRet < 0)
			{
				printf("String2File : truncate failed\n");
				return false;
			}
		}

		fwrite(strString, 1, srclen, fp);
		fclose(fp);
		fp = NULL;

		bRet = true;
	}

	return bRet;
}

bool CFileHelper::MakeDirectory(const char * strFileFullPath)
{
	char DirName[256];
	strcpy(DirName, strFileFullPath);
	int i = 0, len = 0;
	len = strlen(DirName);
	for (i = 1; i < len; i++)
	{
		if (DirName[i] == '/')
		{
			DirName[i] = 0;
			int a = access(DirName, F_OK);
			if (a == -1)
			{
				mkdir(DirName, 0755);
			}
			DirName[i] = '/';
		}
	}
	return 0;
}