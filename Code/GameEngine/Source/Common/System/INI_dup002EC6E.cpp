// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
// platformsdk
//
// ?dup_002EC6E@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002EC6E, 64 bytes.
// Dedicated TU (same INI verb family as INI_parseBitString8.cpp, framed).
//
// Opaque row: byte-sized index-list parser (getNextToken(0) + member
// scanIndexList against the caller-provided table from userData + signed
// 0..255 range check + byte store). Failure is a bare `throw 1` through the
// int throwinfo at 0x8FE2C8 (the parseBitString8-twin TU proves the idiom;
// replicated here as tmp-set plus direct _CxxThrowException call since the
// family builds /GX-). Identity open (the 0x2EC6E byte-check verb); address
// token kept per the dup_ convention for real bodies with unproven names.
// Retail-measured: userData is pushed first so it feeds scanIndexList as the
// name table (no global table); the shared fail tail at 0x2EC99 is exclusive
// to this body (the next verb stores without throwing), so the 64B extent
// covers success (43B) plus the direct-throw block.

#include <windows.h>

typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

#include "../../../Include/Common/INI/INI.h"

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

// The throw site pushes the address of retail's int ThrowInfo at 0x8FE2C8, the
// compiler's own __TI1H, which the units that `throw` an int emit as a COMDAT.
// Name it rather than a zero stand-in, so a throw finds the catchable type.
extern "C" const struct _s__ThrowInfo __identifier("_TI1H");

// ?dup_002EC6E@INI@@SAXPAV1@PAX1PBX@Z
void INI::dup_002EC6E(INI *ini, void * /*instance*/, void *store, const void *userData)
{
	int value = ini->scanIndexList(ini->getNextToken(NULL), (ConstCharPtrArray)userData);
	if (value < 0 || value > 255) {
		// Dead-slot reuse: userData is dead after the scanIndexList call, so
		// the thrown int homes to its stack slot ([ebp+0x14]) instead of a
		// fresh reserve (retail has no push-ecx).
		userData = (const void *)1;
		_CxxThrowException((void *)&userData, &__identifier("_TI1H")); __assume(0);
	}
	*(unsigned char *)store = (unsigned char)value;
}
