// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ?Rva00101FD8Create@@YG... @0x00101FD8 78B: unlock factory comparing the input
// StringBase to global g_00DEC3B8 via rowed compare 0x000069D6; on equality
// new(12) + ctor LookupTablePostEffect 0x00111B84 else return 0.
// Evidence: packet disassembly; callers 0x001022F5 (pushes its arg) and
// 0x00102351 (pushes the same global); unblocks those two.

#include "ascii_string.h"

// VA 0x00DEC3B8 (.data, four bytes, retail holds zeros there): the lookup-table
// key the factory and the two PostFX paths compare against. Nothing can define it
// as its own StringBase<char> spelling -- that class's default constructor is
// private in the shim (onlyfriendclass AsciiString opens it) -- but its public
// derived spelling is AsciiString, whose base subobject sits at offset 0, so the
// four readers keep passing the same address to the same rowed compare at RVA
// 0x000069D6. Retail's storage is zero-filled and is filled at static-init
// time, exactly like the zero slots defined elsewhere in .data.
const AsciiString g_00DEC3B8;

class LookupTablePostEffect
{
public:
    LookupTablePostEffect();
private:
    char m_pad[12];
};

void *__cdecl operator new(unsigned int size);

LookupTablePostEffect *__stdcall Rva00101FD8Create(const StringBase<char> &name)
{
    LookupTablePostEffect *result = 0;
    // AsciiString is a layout twin of StringBase<char> (both one pointer) but not a
    // base of it, so the key is passed through the twin cast, which is a no-op.
    if (name.compare(*(const StringBase<char> *)&g_00DEC3B8) == 0)
        result = new LookupTablePostEffect;
    return result;
}
