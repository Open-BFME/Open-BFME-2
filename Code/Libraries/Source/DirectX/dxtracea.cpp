// Microsoft DXUT 2c3ad3ceaf99a7aaff5278dabc2cc952c727d8c1 Core/dxerr.cpp:
// Copyright (c) Microsoft Corporation. Licensed under the MIT License.
// See license.dxut.txt. Adapted from DXTraceW's readable control flow; 2005 ABI, sizes, strings,
// worker calls and API identities are independently read from retail.
// compiler: vc71-ddk-4035
// cl:  /O1 /G7 /MT /DNDEBUG /hotpatch /Oy- /GS
#include <stdio.h>
#define _vsnwprintf vswprintf
#define STRSAFE_NO_DEPRECATE
#include "../../../../reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include/strsafe.h"
#undef _vsnwprintf
typedef unsigned long DWORD;
typedef int BOOL;
struct HWND__;
typedef HWND__ *HWND;
extern "C" {
__declspec(dllimport) void __stdcall OutputDebugStringA(const char *);
__declspec(dllimport) void __stdcall OutputDebugStringW(const wchar_t *);
__declspec(dllimport) HWND __stdcall GetForegroundWindow();
__declspec(dllimport) int __stdcall MessageBoxA(HWND,const char *,const char *,unsigned int);
__declspec(dllimport) int __stdcall MessageBoxW(HWND,const wchar_t *,const wchar_t *,unsigned int);
__declspec(dllimport) void __stdcall DebugBreak();
const char *__stdcall DXGetErrorString9A(HRESULT);
const wchar_t *__stdcall DXGetErrorString9W(HRESULT);
}

extern "C" HRESULT __stdcall DXTraceA(const char *strFile, DWORD dwLine,
                                       HRESULT hr, const char *strMsg, BOOL bPopMsgBox)
{
    char strBufferLine[128];
    char strBufferError[256];
    char strBuffer[3000];

    StringCchPrintfA(strBufferLine, 128, "%ld", dwLine);
    if (strFile)
    {
        StringCchPrintfA(strBuffer, 3000, "%s(%s): ", strFile, strBufferLine);
        OutputDebugStringA(strBuffer);
    }
    size_t nMsgLen = 0;
    if (strMsg)
        StringCchLengthA(strMsg, 1024, &nMsgLen);
    if (nMsgLen > 0)
    {
        OutputDebugStringA(strMsg);
        OutputDebugStringA(" ");
    }
    StringCchPrintfA(strBufferError, 256, "%s (0x%0.8x)", DXGetErrorString9A(hr), hr);
    StringCchPrintfA(strBuffer, 3000, "hr=%s", strBufferError);
    OutputDebugStringA(strBuffer);
    OutputDebugStringA("\n");
    if (bPopMsgBox)
    {
        char strBufferFile[260];
        StringCchCopyA(strBufferFile, 260, "");
        if (strFile)
            StringCchCopyA(strBufferFile, 260, strFile);
        char strBufferMsg[1024];
        StringCchCopyA(strBufferMsg, 1024, "");
        if (nMsgLen > 0)
            StringCchPrintfA(strBufferMsg, 1024, "Calling: %s\n", strMsg);
        StringCchPrintfA(strBuffer, 3000,
            "File: %S\nLine: %s\nError Code: %s\n%sDo you want to debug the application?",
            strBufferFile, strBufferLine, strBufferError, strBufferMsg);
        int nResult = MessageBoxA(GetForegroundWindow(), strBuffer,
                                  "Unexpected error encountered", 0x14);
        if (nResult == 6)
            DebugBreak();
    }
    return hr;
}

