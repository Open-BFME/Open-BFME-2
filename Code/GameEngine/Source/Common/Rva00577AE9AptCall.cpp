// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc
// ?Rva00577AE9AptCall@@YAHPAVRva00222A8BTarget@@PAXPBD2PAHPAM444@Z @0x00577AE9 314B: Apt forward with 1 int plus 4 floats.
// Builds 5 AsciiStrings via rowed 0x00222834 and 0x002228E8, passes their text
// or g_Rva0107301CEmptyString as 5 args to thiscall twin rva00222B19
// 0x00222B19 with argc 5. Evidence: chain packet calls just-landed 0x00222B19
// plus rowed gets plus releaseBuffer 0x00036410 plus empty 0x007BAC1C.
#include "ascii_string.h"

class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

AsciiString Rva002228E8Get(float val);
AsciiString Rva00222834Get(int val);


__forceinline const char *GetStr(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : "";
}

int __cdecl Rva00577AE9AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, int *pInt, float *pF1, float *pF2, float *pF3, float *pF4)
{
	return target->rva00222B19(level, prefix, function, 5, GetStr(Rva00222834Get(*pInt)), (void *)GetStr(Rva002228E8Get(*pF1)), (void *)GetStr(Rva002228E8Get(*pF2)), (void *)GetStr(Rva002228E8Get(*pF3)), (void *)GetStr(Rva002228E8Get(*pF4)));
}

// Retail 0x00577C23 125B, the next body: the same forward with an int and a
// bool, the bool as "0"/"1" through the rowed 0x004E678B (argc 2). Caller
// 0x005F31E0 ("SetUnitIconSlotVisibility", with the slot's Apt index).
char **__cdecl Rva004E678BGet(char **out, bool flag);

static inline const char *Rva00577C23Flag(const bool &b)
{
	char *text;
	return *Rva004E678BGet(&text, b);
}

int __cdecl Rva00577C23AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, int *pInt, bool *pFlag)
{
	return target->rva00222B19(level, prefix, function, 2, GetStr(Rva00222834Get(*pInt)), (void *)Rva00577C23Flag(*pFlag), 0, 0, 0);
}
