// ?bfmeEraseVMU@BfmeListVMU@@QAEXPAPAVBfmeNodeVMU@@@Z, retail 0x006D1C90.
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv1474.cpp
// (BFME1 0x00896A80). BFME2 repairs: the node is {payload next} (see the
// landed tracker drop in BfmeRva008C4310Release.cpp) and frees go through
// the sized pool deallocator (allocator object at 0x00E176E8 args
// (block 8)) instead of the BFME1 cdecl free. The per-node teardown and
// the pool free resolve via the rowed Rva006CD530 detach and the pinned
// Rva006DB270 freeBlock (ModuleInfoNuggetChainDrain precedent); the
// allocator global is a TU-local extern (DIR32 auto-patches).
// No // cl: line: the defaults (-O2 -EHsc-) match this EH-free body
// (the lea-ecx alignment nop is plain /O2 loop alignment).
class BfmeNodeVMU
{
public:
	void *m_bfmePayload;
	BfmeNodeVMU *m_bfmeNext;
};

class Rva006CD530
{
public:
	void detach();
};

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pVmuBlockAllocator; // 0x00E176E8

class BfmeListVMU
{
public:
	void bfmeEraseVMU(BfmeNodeVMU **it);
	BfmeNodeVMU *m_bfmeHead;
};

// ?bfmeEraseVMU@BfmeListVMU@@QAEXPAPAVBfmeNodeVMU@@@Z
void BfmeListVMU::bfmeEraseVMU(BfmeNodeVMU **it)
{
	BfmeNodeVMU *target = *it;
	BfmeNodeVMU *head = m_bfmeHead;

	if (target == head)
	{
		if (head != 0)
		{
			BfmeNodeVMU *next = head->m_bfmeNext;
			((Rva006CD530 *)head)->detach();
			g_pVmuBlockAllocator->freeBlock(head, 8);
			m_bfmeHead = next;
		}
		return;
	}
	BfmeNodeVMU *prev = m_bfmeHead;
	while (prev != 0)
	{
		if (prev->m_bfmeNext == target)
			break;
		prev = prev->m_bfmeNext;
	}
	BfmeNodeVMU *node = prev->m_bfmeNext;
	if (node != 0)
	{
		prev->m_bfmeNext = node->m_bfmeNext;
		((Rva006CD530 *)node)->detach();
		g_pVmuBlockAllocator->freeBlock(node, 8);
	}
}
