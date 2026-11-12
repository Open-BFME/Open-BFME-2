// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ?Rva00101FD8Create@@YG... @0x00101FD8 78B: unlock factory comparing the input
// StringBase to global g_00DEC3B8 via rowed compare 0x000069D6; on equality
// new(12) + ctor LookupTablePostEffect 0x00111B84 else return 0.
// Evidence: packet disassembly; callers 0x001022F5 (pushes its arg) and
// 0x00102351 (pushes the same global); unblocks those two.

#include "ascii_string.h"

// VA 0x00DEC3B8 (zero-filled .data tail): the lookup-table post effect's name, the key the
// factory and the two PostFX paths compare against. Retail builds it in this unit's
// .text$yc run (0x007ACB5D, alone before the pool-init marker 0x007ACB78) from the literal
// "LookupTablePostEffect" through the out-of-line AsciiString(const char *) 0x0000654A,
// and registers the cleanup 0x007B6F98. The readers compare through the rowed StringBase
// compare at RVA 0x000069D6; AsciiString's base subobject sits at offset 0.
// The prior `extern` declaration is what makes the definition external: without
// it MSVC gives a const namespace-scope object INTERNAL linkage and emits the
// TU-local symbol instead, so the readers' reference to
// ?g_00DEC3B8@@3VAsciiString@@B is unresolved.
extern const AsciiString g_00DEC3B8;
#pragma inline_depth( 0 )
const AsciiString g_00DEC3B8("LookupTablePostEffect");
#pragma inline_depth()

#include "../../../Include/W3DDevice/GameClient/LookupTablePostEffect.h"

#include <new>

LookupTablePostEffect *__stdcall Rva00101FD8Create(const StringBase<char> &name)
{
    LookupTablePostEffect *result = 0;
    // AsciiString is a layout twin of StringBase<char> (both one pointer) but not a
    // base of it, so the key is passed through the twin cast, which is a no-op.
    if (name.compare(*(const StringBase<char> *)&g_00DEC3B8) == 0)
        result = new LookupTablePostEffect;
    return result;
}
