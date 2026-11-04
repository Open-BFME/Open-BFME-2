// cl: /DNDEBUG /MD
// Retail RVA 0x00850600 is the 103-byte INIException(int, const char *, ...)
// constructor. The formatter writes the retail global at VA 0x0130C650 and
// imports _vsnprintf through IAT VA 0x01359360.
#include <stdarg.h>
// Retail copies through the _mbscpy import thunk at 0x00629176.
#define _CRTIMP
#include <mbstring.h>
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#include <stdio.h>
#include <new>

// .bss VA 0x00DDF9D0; the next datum starts 0x800 bytes later.
char g_bfmeFormatBuffer[2048];

#include "../../../Include/Common/INI/FieldParse.h"

INIException::INIException(int argCount, const char *format, ...)
{
    field04 = argCount;
    mFailureMessage = 0;
    if (format != 0) {
        va_list args;
        va_start(args, format);
        int length = _vsnprintf(g_bfmeFormatBuffer, 2047, format, args);
        mFailureMessage = new char[length + 1];
        memcpy(mFailureMessage, g_bfmeFormatBuffer, length);
        mFailureMessage[length] = 0;
        va_end(args);
    }
}

// ??1INIException@@QAE@XZ, retail 0x0002BD30, 9 bytes. Gap between
// _rva002bcab_scanIndex and ?scanIndexList@INI@@QAEHPBDPBQBD@Z in
// INI_scanIndexList.cpp. ZH donor
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
// proves public non-virtual dtor deleting mFailureMessage at +0 with
// ??_V@YAXPAX@Z at 0x0002FD80. No vtable so QAE.
INIException::~INIException()
{
    delete[] mFailureMessage;
}

// ??0INIException@@QAE@ABV0@@Z and ??4INIException@@QAEAAV0@ABV0@@Z: retail's
// throw information for INIException (VA 0x00CFE2FC) names the copy
// constructor at 0x000588C5, the body XferException's shares; it nulls the
// message and assigns through operator= at 0x0002F6D6.
INIException::INIException(const INIException &that)
{
    mFailureMessage = 0;
    *this = that;
}

INIException &INIException::operator=(const INIException &that)
{
    if (this != &that)
    {
        delete[] mFailureMessage;
        if (that.mFailureMessage != 0)
        {
            mFailureMessage = new char[strlen(that.mFailureMessage) + 1];
            _mbscpy(reinterpret_cast<unsigned char *>(mFailureMessage), reinterpret_cast<const unsigned char *>(that.mFailureMessage));
        }
        else
            mFailureMessage = 0;
        field04 = that.field04;
    }
    return *this;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:_rva002f681_fill=??0INIException@@QAA@HPBDZZ")
