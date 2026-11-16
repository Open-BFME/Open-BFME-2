// cl: /Oy- /MD

// Native 0x00222B19 ignores ECX and pops nine stack arguments.
// Address its rowed stdcall provider while preserving retail callers' ECX setup.
int __stdcall Rva00222B19AptCall(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
// ?Rva005FB5E6AptCall@@YAHPAVRva00222A8BTarget@@PAXPBD22@Z @0x005FB5E6 33B: free AptCall wrapper via thiscall twin rva00222B19 same 9 stack args. Evidence: thiscall twin pin at 0x00222B19 via call-site mov ecx at 0x005E30E8 precedent Rva005E30E8AptCall plus 40+ callers pushing TheRva00222A8BTarget plus level plus prefix plus function plus _show/_hide plus add esp 0x14.
#include "../../Include/Common/Rva00222A8BTarget.h"
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0)
{
	union {
	    int (__stdcall *provider)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	    int (Rva00222A8BTarget::*member)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	} nativeCall;
	typedef char NativeCallPointerMustBeOneWord[(sizeof(nativeCall.provider) == sizeof(nativeCall.member)) ? 1 : -1];
	nativeCall.provider = &Rva00222B19AptCall;
	return (target->*nativeCall.member)(level, prefix, function, 1, a0, 0, 0, 0, 0);
}
