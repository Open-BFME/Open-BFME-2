// cl: /Ireference/shims/bfme2_ascii /MD /EHsc

// Native 0x00222B19 ignores ECX and pops nine stack arguments.
// Address its rowed stdcall provider while preserving retail callers' ECX setup.
int __stdcall Rva00222B19AptCall(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
//
// ?Rva005E30E8AptCall@@YAHPAV1PAXPBD1PAVRva005E2D74@@@Z, retail 0x005E30E8 99B free cdecl.
// Level-gated AptCall via Rva005E2D74::rva005E306D string plus rowed 0x00222B19.
// Evidence: rowed rva005E306D 0x005E306D plus rowed AptCall 0x00222B19 plus
// empty fallback g_Rva0107301CEmptyString plus caller 0x005E314B, neighbours
// Rva005E2D74.cpp and Rva005D2F96Build.cpp same page.
//
#include "ascii_string.h"

#include "../../Include/Common/Rva00222A8BTarget.h"
class Rva005E2D74
{
public:
	AsciiString rva005E306D();
};

int __cdecl Rva005E30E8AptCall(Rva00222A8BTarget *target, void *level, const char *mid, const char *function, Rva005E2D74 *obj)
{
	AsciiString tmp = obj->rva005E306D();
	const char *s = tmp.str();
	union {
	    int (__stdcall *provider)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	    int (Rva00222A8BTarget::*member)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	} nativeCall;
	typedef char NativeCallPointerMustBeOneWord[(sizeof(nativeCall.provider) == sizeof(nativeCall.member)) ? 1 : -1];
	nativeCall.provider = &Rva00222B19AptCall;
	return (target->*nativeCall.member)(level, mid, function, 1, s, 0, 0, 0, 0);
}
