// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva0057A9B7Fire@@YAHPAX0PBD1PAH0@Z, retail 0x0057A9B7 104B unlock via AptCall plus Get.
// Free int ID via rowed Get 0x00222834 then AptCall 0x00222B19 argc 2 with empty fallback.
// Evidence: callees rowed Get 0x00222834 plus AptCall 0x00222B19 plus releaseBuffer 0x00036410 plus empty g_Rva0107301CEmptyString; callers 0x0057AB16 0x005ED7CC 0x005FE122; prev 0x0057A961 same page.
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

int __cdecl Rva0057A9B7Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, void *a6)
{
	return ((Rva00222A8BTarget *)a1)->rva00222B19(a2, a3, a4, 2, GetStr(Rva00222834Get(*a5)), a6, 0, 0, 0);
}
