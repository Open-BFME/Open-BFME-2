// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
// platformsdk
//
// ?parseBitString16@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002F21A, 62 bytes.
// Dedicated TU (same INI verb family as INI_parseBitString8.cpp, framed).
//
// BFME1 reference (reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/
// INI_parseBitString16.cpp): parse through parseBitString32, range-check the
// result, narrow into the store. BFME2 is verbatim here: the DEBUG_CRASH/
// throw pair of the 8-bit twin's source is already the bare `throw 1` idiom
// in this twin (replicated as the equivalent tmp-set plus direct
// _CxxThrowException call since the family builds /GX-), thrown through the
// int throwinfo at 0x8FE2C8.

#include <windows.h>

#include "../../../Include/Common/INI/INI.h"

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

// The throw site pushes the address of retail's int ThrowInfo at 0x8FE2C8, the
// compiler's own __TI1H, which the units that `throw` an int emit as a COMDAT.
// Name it rather than a zero stand-in, so a throw finds the catchable type.
extern "C" const struct _s__ThrowInfo __identifier("_TI1H");

// ?parseBitString16@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseBitString16(INI *ini, void * /*instance*/, void *store, const void *userData)
{
	unsigned int tmp;
	INI::parseBitString32(ini, NULL, &tmp, userData);
	if (tmp & 0xffff0000) {
		tmp = 1;
		_CxxThrowException(&tmp, &__identifier("_TI1H")); __assume(0);
	}
	*(unsigned short *)store = (unsigned short)tmp;
}
