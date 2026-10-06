// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
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

#define NULL 0

typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

class INI
{
public:
	const char *getNextToken(const char *seps);
	int scanIndexList(const char *token, ConstCharPtrArray flagList);
	static void dup_002EC6E(INI *ini, void *instance, void *store, const void *userData);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

// Address anchor only: the throw site pushes this object's address as an
// immediate (DIR32, copied from retail's int throwinfo at 0x8FE2C8). Content
// is never compared; the real chain lives in the retail image.
struct Dup002EC6EThrowInfoAnchor { int a; int b; int c; int d; };
static const Dup002EC6EThrowInfoAnchor dup002EC6EThrowInfoAnchor = { 0, 0, 0, 0 };

// ?dup_002EC6E@INI@@SAXPAV1@PAX1PBX@Z
void INI::dup_002EC6E(INI *ini, void * /*instance*/, void *store, const void *userData)
{
	int value = ini->scanIndexList(ini->getNextToken(NULL), (ConstCharPtrArray)userData);
	if (value < 0 || value > 255) {
		// Dead-slot reuse: userData is dead after the scanIndexList call, so
		// the thrown int homes to its stack slot ([ebp+0x14]) instead of a
		// fresh reserve (retail has no push-ecx).
		userData = (const void *)1;
		_CxxThrowException((void *)&userData, (const _s__ThrowInfo *)&dup002EC6EThrowInfoAnchor); __assume(0);
	}
	*(unsigned char *)store = (unsigned char)value;
}
