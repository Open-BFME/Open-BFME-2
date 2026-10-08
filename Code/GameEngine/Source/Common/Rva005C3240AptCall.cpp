// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?Rva005C3240AptCall@@YAHPAVRva00222A8BTarget@@PAXPBD2ABVAsciiString@@3@Z @0x005C3240 63B: Apt forward with 2 strings.
// Builds no temporaries: takes two AsciiStrings by reference, passes their text
// or g_Rva0107301CEmptyString as 2 args to thiscall twin rva00222B19
// 0x00222B19 with argc 2. Evidence: rowed AptCallLevel 0x00222B19 plus empty
// 0x007BAC1C plus caller 0x005C3351 in 0x005C329B, neighbours Rva005C31FB
// in AsciiStringFoldDeleters.cpp same page, precedent Rva00577AE9AptCall.
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

int __cdecl Rva005C3240AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const AsciiString &a0, const AsciiString &a1)
{
	return target->rva00222B19(level, prefix, function, 2, GetStr(a0), (void *)GetStr(a1), 0, 0, 0);
}
