// cl: /DNDEBUG /MD
//
// ?Rva004F6B7BInit@@YAXPAVRva00468520@@PBV1@@Z, retail 0x004F6B7B, 18 bytes.
// Null-checked wrapper around rowed set 0x004F62FE for Rva00468520 (ptr at
// +0 with refcount at +4 plus int at +4). Same shape as _Construct for
// Rva004F6352 at 0x004F6A76. Callers at 0x00153433 0x0015345E 0x0015391C
// 0x00153A39 and 0x004F7130 in FUN_008f711c which allocates 0x10 and inits
// at +8.

#include "../../Include/Common/Rva00468520Obj.h"

#include "../../Include/Common/Rva00468520.h"

void __cdecl Rva004F6B7BInit(Rva00468520 *dst, const Rva00468520 *src)
{
	if (dst)
		dst->set(src);
}
