// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0031BEF1@Rva0031BEF1@@QAEPAXABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@Z @0x0031BEF1 37B
// Hashtable node create: allocate 12B via rowed allocator 0x000307F0, null
// next, construct pair at +4 via rowed dup 0x0031BDC1 (true _Construct
// pair<const AsciiString,NoCaseTreeValue4> at 0x000A7849). Caller 0x0031C7D6.
// Evidence: push 0/push 0xc/allocate/push arg/construct shape; unlocks 0x0031C7D6.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

#include "ascii_string.h"

struct NoCaseTreeValue4
{
public:
	NoCaseTreeValue4() { *(unsigned int *)m_data = 0; }
	unsigned char m_data[4]; // +0x00
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> Bef1Pair;

void __cdecl Rva0031BDC1Construct(void *dest, const void *source);

struct Bef1Node
{
    Bef1Node *m_next;
    Bef1Pair m_pair;
};

struct Rva0031BEF1
{
    void *rva0031BEF1(Bef1Pair const &src);
};

void *Rva0031BEF1::rva0031BEF1(Bef1Pair const &src)
{
    Bef1Node *bef1Node = (Bef1Node *)_STL::allocator<char>::allocate(12, 0);
    bef1Node->m_next = 0;
    Rva0031BDC1Construct(&bef1Node->m_pair, &src);
    return bef1Node;
}
