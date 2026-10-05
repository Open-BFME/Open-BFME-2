// ?Rva005252CDAptCall@@YAHPAVRva00222A8BTarget@@PAXPBD2PAHPAPAX@Z
// partial score=0.94 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?Rva005252CDAptCall@@YAHPAVRva00222A8BTarget@@PAXPBD2PAHPAPAX@Z, retail 0x005252CD 107B finish from banked 0.93.
// Free __cdecl Apt forwarder via rowed Rva00222834Get plus thiscall twin rva00222B19 plus empty fallback.
// Evidence: rowed 0x00222834 plus rowed 0x00222B19 plus releaseBuffer 0x00036410; callers 0x0052A804 0x005FFF62; prev 0x00525235 next 0x00525338 same dir same flags.
#include "ascii_string.h"

extern const char g_Rva0107301CEmptyString[];
AsciiString __cdecl Rva00222834Get(int val);

class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

__forceinline const char *GetStr(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : g_Rva0107301CEmptyString;
}

// ?Rva005252CDAptCall@@YAHPAVRva00222A8BTarget@@PAXPBD2PAHPAPAX@Z present-unmatched
int __cdecl Rva005252CDAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, int *pInt, void **ppA1)
{
	return target->rva00222B19(level, prefix, function, 2, GetStr(Rva00222834Get(*pInt)), *ppA1, 0, 0, 0);
}
