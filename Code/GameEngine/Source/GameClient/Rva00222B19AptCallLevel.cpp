// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva00222B19AptCall@@YGHPAXPBD1H10000@Z, retail 0x00222B19 180B free stdcall ret 0x24.
// Level-gated APT call: below 14 build "/_level%d" plus "." plus prefix, at 14 use
// prefix alone, above 14 return empty static buffer. Evidence: callers pass level
// plus prefix plus APT args, callees rowed format 0x00038150 concat 0x00005629
// releaseBuffer 0x00036410 plus pinned AptCall 0x006CCB80, statics g_00DFE5D8
// g_00BBD3EC plus empty fallback g_Rva0107301CEmptyString, neighbours
// Rva00222A8BAptCallLevel.cpp and Rva00222BCDInvoke.cpp same page.
//
#include "ascii_string.h"

extern const char g_00BBD3EC[];
// g_00DFE5D8: matched references place it at VA 0xdfe5d8; zero-filled at retail, sized to the
// 0x10c-byte gap before the next known global there.
char g_00DFE5D8[268];

int __cdecl Rva006CCB80AptCall(const char *function, char *result, const char *path,
	int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);

int __stdcall Rva00222B19AptCall(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4)
{
	g_00DFE5D8[0] = 0;
	AsciiString path;
	if ((unsigned int)level == 14) {
		((StringBase<char> *)&path)->concat(prefix);
	} else if ((unsigned int)level >= 14) {
		return (int)g_00DFE5D8;
	} else {
		path.format("/_level%d", level);
		((StringBase<char> *)&path)->concat(g_00BBD3EC);
		((StringBase<char> *)&path)->concat(prefix);
	}
	const char *s = path.str();
	Rva006CCB80AptCall(function, g_00DFE5D8, s, argc, a0, a1, a2, a3, a4);
	return (int)g_00DFE5D8;
}

// The UI firers call this body as a method of the APT call target (thiscall, ECX unused, the same nine arguments popped by the callee, ret 0x24), pinned to the same 0x00222B19; bind that spelling here.
#pragma comment(linker, "/alternatename:?rva00222B19@Rva00222A8BTarget@@QAEHPAXPBD1H10000@Z=?Rva00222B19AptCall@@YGHPAXPBD1H10000@Z")
