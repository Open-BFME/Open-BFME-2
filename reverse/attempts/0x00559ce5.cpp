// ?Rva00559CE5@@YA?AVUnicodeString@@HH@Z
// partial score=0.95 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /G7 /arch:SSE /EHsc /DNDEBUG /MD
#include "unicode_string.h"

// ?Rva00559CE5@@YA?AVUnicodeString@@HH@Z @0x00559CE5 39B.
// Target evidence: Ghidra gives this exact boundary. Its two retail callers
// pass a result slot and two integers, then use that slot as a UnicodeString.
// The body validates the first integer through the matched 0x00559B4B helper
// and forwards its byte result with the second integer to 0x00559C3D. The
// wrapper's original method and class identity remain unknown.

extern unsigned char __cdecl Rva00559B4BCheck(int value);
UnicodeString __cdecl Rva00559C3D(unsigned char valid, int value);

UnicodeString __cdecl Rva00559CE5(int type, int value)
{
	return Rva00559C3D(Rva00559B4BCheck(type), value);
}
