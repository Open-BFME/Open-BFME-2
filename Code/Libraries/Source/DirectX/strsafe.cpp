// Microsoft Platform SDK strsafe.h supplied with Visual Studio .NET 2003.
// Copyright (c) Microsoft Corp. All rights reserved; definitions remain in
// the pristine SDK header pinned by Open-BFME-1 revision
// 64d369b90170b7e9ec917d646f020b11f13eb0d5.
// compiler: vc71-sp1
// cl:  /O1 /G7 /MT /DNDEBUG /hotpatch /Oy-
// Identity: the August 2005 DXErr archive names these exact COMDATs and its
// relocations bind the A/W wrappers to their respective workers in retail.
#include <stdio.h>
// Retail's PE import at IAT BBA5AC names this bounded C++ CRT export.
// Select that existing stdio.h overload without editing SDK definitions.
#define _vsnwprintf vswprintf
#define STRSAFE_NO_DEPRECATE
#include "../../../../reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include/strsafe.h"
#undef _vsnwprintf
#undef StringCopyWorkerA
#undef StringCopyWorkerW
#undef StringVPrintfWorkerA
#undef StringVPrintfWorkerW
#undef StringLengthWorkerA
#undef StringLengthWorkerW

typedef void (__cdecl *StrSafeEmissionTarget)();
// Synthetic emission helper; this function has no retail identity or row.
// ?strSafeEmissionTarget absent-from-retail
StrSafeEmissionTarget strSafeEmissionTarget(unsigned index)
{
    static StrSafeEmissionTarget const targets[] = {
        reinterpret_cast<StrSafeEmissionTarget>(&StringCopyWorkerA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCopyWorkerW),
        reinterpret_cast<StrSafeEmissionTarget>(&StringVPrintfWorkerA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringVPrintfWorkerW),
        reinterpret_cast<StrSafeEmissionTarget>(&StringLengthWorkerA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringLengthWorkerW),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchCopyA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchCopyW),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchPrintfA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchPrintfW),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchLengthA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchLengthW)
    };
    return index < sizeof(targets) / sizeof(targets[0]) ? targets[index] : 0;
}
