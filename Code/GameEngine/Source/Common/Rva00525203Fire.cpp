// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /Oy-

// Native 0x00222B19 ignores ECX and pops nine stack arguments.
// Address its rowed stdcall provider while preserving retail callers' ECX setup.
int __stdcall Rva00222B19AptCall(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
// ?Rva00525203Fire@@YAHPAX0PBD1PBVAsciiString@@@Z, retail 0x00525203 50B unlock via AptCall plus direct GetStr.
// Direct AsciiString pointer GetStr then AptCall 0x00222B19 argc 1 with empty fallback.
// Evidence: callee rowed AptCall 0x00222B19; callers 0x00525606 0x00578157; prev 0x0052519D same pattern.
#include "ascii_string.h"


#include "../../Include/Common/Rva00222A8BTarget.h"

static __forceinline const char *GetStr(const AsciiString &asciiString)
{
	char *stringData = *(char **)(void *)&asciiString;
	return stringData ? stringData + 8 : "";
}

int __cdecl Rva00525203Fire(void *a1, void *level, const char *prefix, const char *function, const AsciiString *asciiString)
{
	union {
	    int (__stdcall *provider)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	    int (Rva00222A8BTarget::*member)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	} nativeCall;
	typedef char NativeCallPointerMustBeOneWord[(sizeof(nativeCall.provider) == sizeof(nativeCall.member)) ? 1 : -1];
	nativeCall.provider = &Rva00222B19AptCall;
	return (((Rva00222A8BTarget *)a1)->*nativeCall.member)(level, prefix, function, 1, GetStr(*asciiString), 0, 0, 0, 0);
}
