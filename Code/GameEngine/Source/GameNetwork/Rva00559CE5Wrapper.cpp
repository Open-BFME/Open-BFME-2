// cl: /Ireference/shims/bfme2_ascii /G7 /arch:SSE /EHsc /DNDEBUG /MD /O1 /Oy- /Gy
#include "unicode_string.h"
// ?Rva00559CE5@@YA?AVUnicodeString@@HH@Z, retail 0x00559CE5, 39 bytes.
// Target evidence: Ghidra gives this exact boundary. Its two retail callers pass a result slot
// and two integers, then use that slot as a UnicodeString. The body validates the first integer
// through the matched 0x00559B4B helper and forwards its byte result with the second integer to
// 0x00559C3D (WB 0x013F9DD0 RankPointValue::RankString). The WB wrapper (0x013F9F20) keeps a
// returned-temporary flag local (retail's `and [ebp-4],0`). The method and class identity
// of the wrapper remain unknown.
// Codegen: retail keeps `add esp,4` after the checker call and the ebp frame only when the
// checker's body is visible in the unit (its register effects are known); the visible copy is
// the 0x00559B4B row itself, so both live in this unit (one definition). Its own body has no
// frame pointer in retail, unlike the wrapper's (/Oy-).
// ?Rva00559B4BCheck@@YAEH@Z, retail 0x00559B4B, 25 bytes: 1 for 3/4/5 else 0, as a byte;
// caller 0x00559CF3 pushes one argument then add esp,4 (__cdecl).
#pragma optimize("y", on)
__declspec(noinline) unsigned char __cdecl Rva00559B4BCheck(int v)
{
	return v == 3 || v == 4 || v == 5;
}
UnicodeString __cdecl Rva00559C3D(unsigned char valid, int value);
UnicodeString __cdecl Rva00559CE5(int type, int value)
{
	return Rva00559C3D(Rva00559B4BCheck(type), value);
}
