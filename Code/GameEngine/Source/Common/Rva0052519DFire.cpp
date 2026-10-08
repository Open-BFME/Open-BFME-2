// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva0052519D@Rva0052519D@@QAEHPAX0PBD1PAH@Z, retail 0x0052519D 102B unlock via AptCall plus Get.
// Free int ID via rowed Get 0x00222834 then AptCall 0x00222B19 with empty fallback.
// Evidence: callees rowed Get plus AptCall plus releaseBuffer 0x00036410; callers
// 0x005255D3 0x00526621 plus 0x005C3EA5 59B passing target plus Show; prev/next same dir.
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

int __cdecl Rva0052519DFire(void *a1, void *a2, const char *a3, const char *a4, int *a5)
{
	return ((Rva00222A8BTarget *)a1)->rva00222B19(a2, a3, a4, 1, GetStr(Rva00222834Get(*a5)), 0, 0, 0, 0);
}
