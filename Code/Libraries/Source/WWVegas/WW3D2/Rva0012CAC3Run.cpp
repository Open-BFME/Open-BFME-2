// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX-
//
// ?Rva0012CAC3Run@@YA_NXZ, retail 0x0012CAC3, 82 bytes.
// OR the wide Run helper at 0x0012C907 called with NULL and with the
// configured directory converted to Unicode. Evidence: E8 calls to rowed
// 0x0012C907 twice, g_00DEE93C AsciiString length check, rowed
// UnicodeString ctor 0x006CB6D0, inline str() via TheNullChr 0x00BBB5C4,
// rowed releaseBuffer 0x00036E70; caller at 0x0012CFDB in 0x0012CFA0.

#include "ascii_string.h"
#include "unicode_string.h"

// g_00DEE93C: matched references place it at VA 0xdee93c (zero-filled; a plain-data view).
AsciiString g_00DEE93C;
bool __cdecl Rva0012C907Run(const unsigned short *currentDirectory);

bool __cdecl Rva0012CAC3Run()
{
	bool ok = Rva0012C907Run(0);
	if (!g_00DEE93C.isEmpty()) {
		ok |= Rva0012C907Run(UnicodeString(g_00DEE93C).str());
	}
	return ok;
}
