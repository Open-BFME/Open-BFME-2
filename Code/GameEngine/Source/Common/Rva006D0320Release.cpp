// cl: /DNDEBUG /MD
// ?rva006D0320@Rva006D0280@@QAEPAV1@_N@Z @ 0x006D0320 35B
// Honest address name: __thiscall conditional pool free beside Rva008951B0Find.
// Target evidence: 35B retail, pinned teardown 0x6D0280 plus pinned freeBlock
// 0x6DB270 with pool VA 0xE176E8 and size 0x1C, ret 4 bool arg, returns this.
// Prev/next share /DNDEBUG /MD shape.
#include "../../Include/Common/Rva006DB270.h"
extern Rva006DB270 *g_pChainBlockAllocator;
void __cdecl Rva006D8680Free(void*,int);
class Rva006D0280
{
public:
    ~Rva006D0280();
    __declspec(dllimport) __forceinline static void operator delete(void*p,unsigned int n){Rva006D8680Free(p,n);}
    Rva006D0280 *rva006D0320(unsigned char doFree);
    // Retail blocks are 0x1C bytes (freeBlock(this, 0x1C) below); pad to the
    // full size so this TU's vector deleting dtor passes 28 like the link's.
    char m_pad[0x1C]; // (class is otherwise empty: 0 + 28)
};
Rva006D0280 *Rva006D0280::rva006D0320(unsigned char doFree)
{
    this->~Rva006D0280();
    if (doFree & 1)
        g_pChainBlockAllocator->freeBlock(this, 0x1C);
    return this;
}
