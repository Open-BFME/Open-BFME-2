// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva00525235Fire@@YAHPAX0PBD1PAH2@Z, retail 0x00525235 152B unlock via AptCall plus double Get.
// Two rowed Get 0x00222834 temps then AptCall 0x00222B19 argc 2 with empty fallback.
// Evidence: callees rowed Get plus AptCall plus releaseBuffer 0x00036410; callers 0x00526706 plus 9 more; prev 0x0052519D same pattern.
#include "ascii_string.h"

AsciiString __cdecl Rva00222834Get(int val);

class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

__forceinline const char *GetStr(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : "";
}

int __cdecl Rva00525235Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, int *a6)
{
	return ((Rva00222A8BTarget *)a1)->rva00222B19(a2, a3, a4, 2, GetStr(Rva00222834Get(*a5)), (void *)GetStr(Rva00222834Get(*a6)), 0, 0, 0);
}
