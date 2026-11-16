// cl: /Ireference/shims/bfme2_ascii /MD

// Native 0x00222B19 ignores ECX and pops nine stack arguments.
// Address its rowed stdcall provider while preserving retail callers' ECX setup.
int __stdcall Rva00222B19AptCall(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
//
// ?Rva005C3240AptCall@@YAHPAVRva00222A8BTarget@@PAXPBD2ABVAsciiString@@3@Z @0x005C3240 63B: Apt forward with 2 strings.
// Builds no temporaries: takes two AsciiStrings by reference, passes their text
// or g_Rva0107301CEmptyString as 2 args to thiscall twin rva00222B19
// 0x00222B19 with argc 2. Evidence: rowed AptCallLevel 0x00222B19 plus empty
// 0x007BAC1C plus caller 0x005C3351 in 0x005C329B, neighbours Rva005C31FB
// in AsciiStringFoldDeleters.cpp same page, precedent Rva00577AE9AptCall.
#include "ascii_string.h"

#include "../../Include/Common/Rva00222A8BTarget.h"


static __forceinline const char *GetStr(const AsciiString &asciiString)
{
	char *t = *(char **)(void *)&asciiString;
	return t ? t + 8 : "";
}

int __cdecl Rva005C3240AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const AsciiString &asciiString, const AsciiString &a1)
{
	union {
	    int (__stdcall *provider)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	    int (Rva00222A8BTarget::*member)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	} nativeCall;
	typedef char NativeCallPointerMustBeOneWord[(sizeof(nativeCall.provider) == sizeof(nativeCall.member)) ? 1 : -1];
	nativeCall.provider = &Rva00222B19AptCall;
	return (target->*nativeCall.member)(level, prefix, function, 2, GetStr(asciiString), (void *)GetStr(a1), 0, 0, 0);
}
