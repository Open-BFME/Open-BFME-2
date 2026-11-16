// cl: /GX-

// Native 0x00222B19 ignores ECX and pops nine stack arguments.
// Address its rowed stdcall provider while preserving retail callers' ECX setup.
int __stdcall Rva00222B19AptCall(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
// ?Rva0050E9FEAptCall@@YAHPAVRva00222A8BTarget@@PAXPBD2PAPBD@Z @0x0050E9FE 36B: chain via 0x00222B19 thiscall. Evidence: 5 stack args, ECX=arg1 plus 9 pushes (4x0 plus *arg5 plus 1 plus arg4/3/2) to rowed AptCall thiscall.
#include "../../Include/Common/Rva00222A8BTarget.h"
int Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr)
{
    const char *a0 = *a0ptr;
    union {
        int (__stdcall *provider)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
        int (Rva00222A8BTarget::*member)(void *, const char *, const char *, int, const char *, void *, void *, void *, void *);
    } nativeCall;
    typedef char NativeCallPointerMustBeOneWord[(sizeof(nativeCall.provider) == sizeof(nativeCall.member)) ? 1 : -1];
    nativeCall.provider = &Rva00222B19AptCall;
    return (target->*nativeCall.member)(level, prefix, function, 1, a0, 0, 0, 0, 0);
}
