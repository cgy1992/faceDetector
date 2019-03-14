#include "CodeTransform.h"

/// ��Unicode����ת����ANSI����
char* UnicodeConvert2ANSI(LPCWCH strUnicode)
{
	int ncLength = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
	char *strANSI = new char[ncLength];
	ncLength = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, strANSI, ncLength, NULL, NULL);
	strANSI[ncLength - 1] = 0;
	return strANSI;
}

/// ��utf-8����ת����Unicode����
WCHAR* UTF8Convert2Unicode(const char* strUtf8)
{
	int ncLength = MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, NULL, 0);
	WCHAR *strUnicode = new WCHAR[ncLength];
	ncLength = MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, strUnicode, ncLength);
	strUnicode[ncLength - 1] = 0;
	return strUnicode;
}
