// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// Retail RVA 0x00216517, 153 bytes.
// ?Rva00216517Fire@@YAHPAVRva00222A8BTarget@@PAXPBDPBIPBM@Z int-return firer: formats int and float via rowed gets, empty fallback, returns invoke result.
// Free __cdecl UI firer with (int float) as strings: formats via rowed Rva002228E8Get(float) and
// Rva0022288EGet(uint), substitutes rowed empty string when a buffer is null, invokes with argc 2, returns result.
// Evidence: callees Rva002228E8Get 0x002228E8 and Rva0022288EGet 0x0022288E plus invoke row 0x00222A8B QAEH
// and releaseBuffer row 0x00036410; caller 0x00216670 pushes (target owner SetBannerXOffset int* float*); retail leaves invoke result in EAX at ret so outer returns int not void.
#include "ascii_string.h"

AsciiString Rva002228E8Get(float val);
AsciiString Rva0022288EGet(unsigned int val);

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};


__forceinline const char *GetStr00216517(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : "";
}

int __cdecl Rva00216517Fire(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int *pInt, const float *pFloat)
{
	return target->invoke(owner, name, 2, GetStr00216517(Rva0022288EGet(*pInt)), (void *)GetStr00216517(Rva002228E8Get(*pFloat)), 0, 0, 0);
}
