
#include <wtypes.h>

#ifdef _WIN32

#pragma once

// ��Unicode����ת����ANSI����
char* UnicodeConvert2ANSI(LPCWCH strEncodeData);

// ��utf-8����ת����Unicode����
WCHAR* UTF8Convert2Unicode(const char* strUtf8);

#endif