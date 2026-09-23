// cl: /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O1 /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// StreakLine's matched constructor initializes the float widths member at +0xF0.
// Its derived/base tables BD41B8/BD41AC point to these deleting destructors.
// /O1 preserves the target's separate base and derived cleanup calls.
#include "always.h"
void __cdecl operator delete[](void *) throw();
#include "simplevec.h"

template class SimpleDynVecClass<float>;
