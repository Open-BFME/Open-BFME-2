// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
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

#define NULL 0

class INI
{
public:
	static void parseBitString32(INI *ini, void *instance, void *store, const void *userData);
	static void parseBitString16(INI *ini, void *instance, void *store, const void *userData);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

// Address anchor only: the throw site pushes this object's address as an
// immediate (DIR32, copied from retail's int throwinfo at 0x8FE2C8). Content
// is never compared; the real chain lives in the retail image.
struct ParseBitString16ThrowInfoAnchor { int a; int b; int c; int d; };
static const ParseBitString16ThrowInfoAnchor parseBitString16ThrowInfoAnchor = { 0, 0, 0, 0 };

// ?parseBitString16@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseBitString16(INI *ini, void * /*instance*/, void *store, const void *userData)
{
	unsigned int tmp;
	INI::parseBitString32(ini, NULL, &tmp, userData);
	if (tmp & 0xffff0000) {
		tmp = 1;
		_CxxThrowException(&tmp, (const _s__ThrowInfo *)&parseBitString16ThrowInfoAnchor); __assume(0);
	}
	*(unsigned short *)store = (unsigned short)tmp;
}
