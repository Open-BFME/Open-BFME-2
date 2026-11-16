// cl: /MD

// Native 0x00222B19 ignores ECX and pops nine stack arguments.
// Address its rowed stdcall provider while preserving retail callers' ECX setup.
int __stdcall Rva00222B19AptCall(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
// ?Rva00524EF4AptCall@@YAHPAVRva00222A8BTarget@@PAXPBD2@Z @0x00524EF4 30B
// Free APT call wrapper: forwards Target as `this` plus the three caller args
// and six zeros to the thiscall AptCall twin at 0x00222B19.
// Evidence: retail 8b 4c 24 04 / 33 c0 / six 50 / three ff 74 24 28 / e8 -> 0x00222B19.
// Callers 0x00528389 and 0x0057A805 pass Target plus 3 args; the `mov ecx`
// proves the inner call is thiscall.
//
// The inner callee is the *0x00222B19* twin, not 0x00222C12. Both exist in the
// ledger with the same 9-argument thiscall signature; retail's own rel32 at
// 0x00524F0C resolves to 0x00222B19, and reverse/symbols.csv already pins
// ?rva00222B19@Rva00222A8BTarget@@QAEHPAXPBD1H10000@Z there. Naming the
// 0x00222C12 row instead compiles to the identical instruction shape but a
// wrong rel32, so the row fails byte comparison on that one field.
#include "../../Include/Common/Rva00222A8BTarget.h"

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3)
{
	union {
	    int (__stdcall *provider)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	    int (Rva00222A8BTarget::*member)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
	} nativeCall;
	typedef char NativeCallPointerMustBeOneWord[(sizeof(nativeCall.provider) == sizeof(nativeCall.member)) ? 1 : -1];
	nativeCall.provider = &Rva00222B19AptCall;
	return (t->*nativeCall.member)(a1, a2, a3, 0, 0, 0, 0, 0, 0);
}
