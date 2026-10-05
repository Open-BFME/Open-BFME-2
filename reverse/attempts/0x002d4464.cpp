// ?Rva002D4464Fire@@YAHPAVRva00222A8BTarget@@PAXPBDPAHPAM4@Z
// partial score=0.9 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva002D4464Fire@@YAHPAVRva00222A8BTarget@@PAXPBDPAHPAM4@Z retail 0x002D4464 205 bytes.
// Unlock lane: missing callee of 2 free functions; landing makes 0x002D4A69/0x002D4AEF ready.
// Free function taking target/level/function/int*/float*/float*, building three
// AsciiStrings via rowed Rva002228E8Get(float) x2 and Rva00222834Get(int), using
// EmptyString fallback g_Rva0107301CEmptyString for null buffers, then invoking
// rowed Rva00222A8BTarget::invoke with argc 3 and two zeros. Evidence: callers
// at 0x002D4ADF/0x002D4B84 pushing target/level/"MoveRadarPing"/int*/float*/float*.
#include "ascii_string.h"

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

AsciiString Rva002228E8Get(float val);
AsciiString Rva00222834Get(int val);

extern const char g_Rva0107301CEmptyString[];

// ?Rva002D4464Fire@@YAHPAVRva00222A8BTarget@@PAXPBDPAHPAM4@Z present-unmatched
int Rva002D4464Fire(Rva00222A8BTarget *target, void *level, const char *function, int *intParam, float *float1, float *float2)
{
	AsciiString s1 = Rva002228E8Get(*float2);
	AsciiString *p1 = &s1;
	AsciiString s2 = Rva002228E8Get(*float1);
	AsciiString *p2 = &s2;
	AsciiString s3 = Rva00222834Get(*intParam);
	char *a2 = *(char **)p1;
	if (a2)
		a2 += 8;
	else
		a2 = (char *)g_Rva0107301CEmptyString;
	char *a1 = *(char **)p2;
	if (a1)
		a1 += 8;
	else
		a1 = (char *)g_Rva0107301CEmptyString;
	char *a0 = *(char **)(void *)&s3;
	if (a0)
		a0 += 8;
	else
		a0 = (char *)g_Rva0107301CEmptyString;
	return target->invoke(level, function, 3, a0, a1, a2, 0, 0);
}
