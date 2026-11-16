// cl: /Ireference/shims/bfme2_ascii /MD /EHsc

// Native 0x00222B19 ignores ECX and pops nine stack arguments.
// Address its rowed stdcall provider while preserving retail callers' ECX setup.
int __stdcall Rva00222B19AptCall(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
// ?Rva00527925Fire@@YAHPAX0PBD1PBM@Z @ 0x00527925 (106B): free float Apt firer via rowed Get 0x002228E8 plus rowed AptCall 0x00222B19 and empty fallback g_Rva0107301CEmptyString. Evidence: callers pass level prefix function plus float; callees rowed; neighbours Rva00527890Move and Rva0052798FConcat.
#include "ascii_string.h"

AsciiString Rva002228E8Get(float val);

#include "../../Include/Common/Rva00222A8BTarget.h"

__forceinline const char *GetStr00527925(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

int Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val)
{
	union {
	    int (__stdcall *provider)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	    int (Rva00222A8BTarget::*member)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	} nativeCall;
	typedef char NativeCallPointerMustBeOneWord[(sizeof(nativeCall.provider) == sizeof(nativeCall.member)) ? 1 : -1];
	nativeCall.provider = &Rva00222B19AptCall;
	return (((Rva00222A8BTarget *)target)->*nativeCall.member)(level, prefix, function, 1, GetStr00527925(Rva002228E8Get(*val)), 0, 0, 0, 0);
}
