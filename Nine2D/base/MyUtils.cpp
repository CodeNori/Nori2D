#include "pch.h"
#include "MyUtils.h"



void OutputDebugString2(const char* format, ...)
{
    char str[256];

    va_list args;
    va_start(args, format);

    vsprintf_s(str,256, format, args);

    va_end(args);

    OutputDebugStringA(str);
}






