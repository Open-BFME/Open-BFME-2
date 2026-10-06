// cl: /MD /EHsc
#include "../../../../GameEngine/Include/Common/Rva00041004Lock.h"
// ?Rva00035C90Get@@YAPAVRva00041004@@XZ @0x00035C90 93B
// ?Rva00035DF0Get@@YAPAVRva00041004@@XZ @0x00035DF0 93B
// Narrow/wide StringBase lock singletons: each returns the address of its
// function-local Rva00041004 guard lock after one-time init (ctor arg 1,
// atexit cleanup). Evidence: twin 93B bodies with manual EH frames
// (push -1 / push handler / mov fs:0), guard bytes at 0x009E084C (narrow,
// object 0x009E0828) and 0x009E0874 (wide, object 0x009E0850), ctor calls to
// rowed ??0Rva00041004@@QAE@H@Z at 0x000411C1, atexit cleanups at 0x007B6A90
// (narrow, mov ecx 0x9E0828) and 0x007B6A80 (wide, mov ecx 0x9E0850) both
// jumping to the real ??1Rva00041004@@UAE@XZ cleanup at 0x00040FE5, callers are the narrow StringBase
// methods (releaseBuffer/ctor/set at 0x0003642C 0x000365F4 0x0003670C) and
// the wide ones (0x00036E8C 0x00037054 0x0003716C), vtable 0x007C16DC shared
// with the rowed ctor TU Code/GameEngine/Source/Common/Rva00041004Lock.cpp.
// Flags /O2 /MD /EHsc probe-proven: /O1 emits __EH_prolog instead of the
// manual frame. Honest address-derived names: identity unproven beyond the
// lock layout and call sites.

Rva00041004 *Rva00035C90Get()
{
    static Rva00041004 obj(1);
    return &obj;
}

Rva00041004 *Rva00035DF0Get()
{
    static Rva00041004 obj(1);
    return &obj;
}
