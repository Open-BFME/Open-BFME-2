// cl: /DNDEBUG /MD /EHsc
// ??1Rva006D6D20@@UAE@XZ @0x006D6D20 82B. Dtor of Apt string-value class (vtable 0x008EA358).
// Evidence: stores vtable 0x008EA358; destroys EAStringC at +8 via rowed ??1EAStringC@@QAE@XZ (0x006D3010)
// then base via rowed ??1Rva006DE350@@UAE@XZ (0x006DE350); ctor twin 0x006D6CC0 same vtable same EH handler
// 0x007A8838 constructs base type 1 plus clear plus +0xC=0; deleting dtor 0x006D7320 frees 0x10; size 0x10.
#include "../../../GameEngine/Include/Common/Rva006DB270.h"
extern Rva006DB270 *g_pChainBlockAllocator;
#include "EAStringC.h"
#include "../../../GameEngine/Include/Common/Rva006DE350.h"
struct Rva006D6D20 : public Rva006DE350
{
    char m_pad[4];
    EAStringC m_str;
    int m_0C;
    virtual ~Rva006D6D20();
    static void operator delete(void*p,unsigned int size){g_pChainBlockAllocator->freeBlock(p,size);}

};
Rva006D6D20::~Rva006D6D20()
{
}
