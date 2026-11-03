// ?release@Rva006D0F20@@QAEXXZ, retail 0x006D0F20, 42 bytes.
//
// Sub-block release for the Nugget-chain block family: drops the use
// count at the +4 sub-block with a direct dec-mem (the value is discarded
// and only the flags are read, so no register materialization), and when
// it reaches zero tears the sub-block down through 0x006D0280 and frees
// it sized (block, 28) through the shared deallocator. Callee 0x006D0280
// resolves via pin, freeBlock via row; the allocator global is a TU-local
// extern (DIR32 auto-patches). No // cl: line (defaults match).
void __cdecl Rva006D8680Free(void*,int);
struct Rva006D0280
{
	~Rva006D0280();
	__declspec(dllimport) __forceinline static void operator delete(void*p,unsigned int n){Rva006D8680Free(p,n);}

	int m_useCount; // +0, dropped by release above
	// Retail frees 0x1C-byte blocks (freeBlock(target, 0x1C) below); the rest
	// of the layout is unobserved here. Pad to the full size so this TU's
	// vector deleting dtor passes 28 like the linked copy.
	char m_pad04[0x1C - 4];
};

#include "../../../Include/Common/Rva006DB270.h"

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class Rva006D0F20
{
public:
	void release();

private:
	int m_pad0;
	Rva006D0280 *m_subBlock; // +4
};

// ?release@Rva006D0F20@@QAEXXZ
void Rva006D0F20::release()
{
	Rva006D0280 *sub = m_subBlock;
	if (sub == 0)
		return;
	if (--sub->m_useCount != 0)
		return;
	Rva006D0280 *target = m_subBlock;
	if (target == 0)
		return;
	target->~Rva006D0280();
	g_pChainBlockAllocator->freeBlock(target, 0x1C);
}
