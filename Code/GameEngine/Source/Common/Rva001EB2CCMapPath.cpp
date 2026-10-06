// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva001EB2CCGetMapPath@@YA?AVAsciiString@@PBD@Z, retail 0x001EB2CC, 93 bytes.
// Free function returning AsciiString by value (hidden pointer at +8, caller cleans 8B, returns +8 in eax):
// formats "maps\%s\%s.map" with same name twice, copy-constructs return value from local tmp via rowed
// StringBase copy 0x365F0, destroys tmp via rowed releaseBuffer 0x36410. Evidence: __cdecl ret, 4-push
// format (this+fmt+2x[ebp+0xC]) with add esp 0x10 to rowed format 0x38150, EH_prolog state 1, caller
// 0x001EB4E3 pushes string then local and cleans 8B then set+release.
#include "ascii_string.h"

AsciiString __cdecl Rva001EB2CCGetMapPath(const char *name)
{
	AsciiString tmp;
	tmp.format("maps\\%s\\%s.map", name, name);
	return tmp;
}
