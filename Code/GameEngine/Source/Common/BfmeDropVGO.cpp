// cl: /MD
// ?bfmeDropVGO@@YAXPAX@Z 0x006D0440 32B: pool drop via teardown plus freeBlock.
// Evidence: leaf with LINK BONUS (2 files await bfmeDropVGO); 6 matched callers incl BfmeRefVGO dtor; pins teardown 0x006D0280 freeBlock 0x006DB270; pool 0x00A176E8 size 0x1C; donor bfmeDropA pattern.
void __cdecl Rva006D8680Free(void*,int);

class Rva006D0280
{
public:
	~Rva006D0280();
	__declspec(dllimport) __forceinline static void operator delete(void*p,unsigned int n){Rva006D8680Free(p,n);}
	// Retail blocks are 0x1C bytes (freeBlock(p, 0x1C) below); pad to the
	// full size so this TU's vector deleting dtor passes 28 like the link's.
	char m_pad[0x1C]; // (class is otherwise empty: 0 + 28)
};

#include "../../Include/Common/Rva006DB270.h"

extern Rva006DB270 *g_pChainBlockAllocator;

void __cdecl bfmeDropVGO(void *p)
{
	if (p != 0)
	{
		((Rva006D0280 *)p)->~Rva006D0280();
		g_pChainBlockAllocator->freeBlock(p, 0x1C);
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
