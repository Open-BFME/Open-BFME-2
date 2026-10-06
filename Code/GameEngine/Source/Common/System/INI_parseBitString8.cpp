// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
//
// ?parseBitString8@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002F1DC, 56 bytes.
// Dedicated TU (same INI verb family as INI_parseBitString32.cpp, framed).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/INI_stl.cpp,
// INI::parseBitString8, plus the converted
// reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/INI_parseBitString16.cpp
// for the 16-bit twin): parse through parseBitString32, range-check the
// result, narrow into the store. BFME2 deltas (all retail-measured): the
// DEBUG_CRASH/throw-ERROR_BUG pair is a bare `throw 1` (the 16-bit twin's TU
// proves the idiom; replicated here as the equivalent tmp-set plus direct
// _CxxThrowException call since the family builds /GX-), thrown through the
// int throwinfo at 0x8FE2C8.

#define NULL 0

class INI
{
public:
	static void parseBitString32(INI *ini, void *instance, void *store, const void *userData);
	static void parseBitString8(INI *ini, void *instance, void *store, const void *userData);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

// Address anchor only: the throw site pushes this object's address as an
// immediate (DIR32, copied from retail's int throwinfo at 0x8FE2C8). Content
// is never compared; the real chain lives in the retail image.
struct ParseBitString8ThrowInfoAnchor { int a; int b; int c; int d; };
static const ParseBitString8ThrowInfoAnchor parseBitString8ThrowInfoAnchor = { 0, 0, 0, 0 };

// ?parseBitString8@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseBitString8(INI *ini, void * /*instance*/, void *store, const void *userData)
{
	unsigned int tmp;
	INI::parseBitString32(ini, NULL, &tmp, userData);
	if (tmp & 0xffffff00) {
		tmp = 1;
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&parseBitString8ThrowInfoAnchor); __assume(0);
	}
	*(unsigned char *)store = (unsigned char)tmp;
}
