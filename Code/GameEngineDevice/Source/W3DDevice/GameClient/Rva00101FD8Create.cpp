// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ?Rva00101FD8Create@@YG... @0x00101FD8 78B: unlock factory comparing the input
// StringBase to global g_00DEC3B8 via rowed compare 0x000069D6; on equality
// new(12) + ctor LookupTablePostEffect 0x00111B84 else return 0.
// Evidence: packet disassembly; callers 0x001022F5 (pushes its arg) and
// 0x00102351 (pushes the same global); unblocks those two.

#include "ascii_string.h"

extern const StringBase<char> g_00DEC3B8;

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
    if (name.compare(g_00DEC3B8) == 0)
        result = new LookupTablePostEffect;
    return result;
}
