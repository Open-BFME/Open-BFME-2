// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /Oy-
// ?Rva00525203Fire@@YAHPAX0PBD1PBVAsciiString@@@Z, retail 0x00525203 50B unlock via AptCall plus direct GetStr.
// Direct AsciiString pointer GetStr then AptCall 0x00222B19 argc 1 with empty fallback.
// Evidence: callee rowed AptCall 0x00222B19; callers 0x00525606 0x00578157; prev 0x0052519D same pattern.
#include "ascii_string.h"


class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

static __forceinline const char *GetStr(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : "";
}

int __cdecl Rva00525203Fire(void *a1, void *a2, const char *a3, const char *a4, const AsciiString *a5)
{
	return ((Rva00222A8BTarget *)a1)->rva00222B19(a2, a3, a4, 1, GetStr(*a5), 0, 0, 0, 0);
}
