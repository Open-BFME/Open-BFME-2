// ?rva00032B00@@YAPAXI@Z
// partial score=0.8 date=2026-10-10
// cl: /O2 /G6 /MD
// NEAR draft for ?rva00032B00@GeneralAllocator@Allocator@EA@@QAEPAXI@Z @0x00032B00 343B
// (PPMalloc VirtualAlloc core extension: reserve round64k + commit clamp or
// reserve|commit fallback; CoreBlock init + list insert after the head at
// +0x448; first chunk + inlined AddDoubleFencepost). 342/343B; head through
// the +0x14 zero stores exact. Levers found: reassigning the size parameter
// (fixes arg load order and the uncse'd dec/not mask); if/else type select;
// the +0xE store through a bool pointer (alias barrier keeps it after +0xD/+0xF
// as retail). Residue: retail keeps the zero in edx (live to chunk[0]) with
// the old next in edi and the chunk in ecx; cl gives zero edi so the chunk
// lands in edx and the tagged/fencepost registers rotate (1 byte shorter).
extern "C" __declspec(dllimport) void *__stdcall VirtualAlloc(void *address, unsigned long size, unsigned long type, unsigned long protect);

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	void *rva00032B00(unsigned int size);
private:
	struct CoreBlock
	{
		void *m_core0;
		unsigned int m_size4;
		unsigned int m_reserved8;
		bool m_mapped;
		bool m_shouldFree;
		bool m_flagE;
		bool m_shouldTrim;
		void *m_free10;
		void *m_context14;
		CoreBlock *m_next18;
		CoreBlock *m_prev1C;
	};
	static unsigned int AlignUp(unsigned int x, unsigned int a)
	{
		return (x + a - 1) & ~(a - 1);
	}
	static void AddDoubleFencepost(void *chunk, unsigned int flags)
	{
		unsigned int *const header = static_cast<unsigned int *>(chunk);
		unsigned int size = header[1];
		unsigned int fencepostOffset = (size & 0x7FFFFFF8) - 9;
		fencepostOffset &= 0xFFFFFFF8;
		header[1] = (size & 0x80000007) | fencepostOffset;
		unsigned int *const fencepost = reinterpret_cast<unsigned int *>(
			reinterpret_cast<char *>(chunk) + fencepostOffset);
		fencepost[0] = fencepostOffset;
		fencepost[1] = flags | 8;
		fencepost[2] = 8;
		fencepost[3] = 9;
	}
	unsigned char m_pad0[0x448];
	CoreBlock m_head448;
	unsigned char m_pad468[0x498 - 0x468];
	bool m_topDown498;
	unsigned char m_pad499[0x4D4 - 0x499];
	unsigned int m_page4D4;
	unsigned int m_min4D8;
	unsigned int m_commit4DC;
};

void *GeneralAllocator::rva00032B00(unsigned int size)
{
	unsigned int kind = 1;
	size = AlignUp(size, m_page4D4);
	if (size < m_min4D8)
		size = AlignUp(m_min4D8, m_page4D4);
	unsigned int reserve = (size + 0xFFFF) & 0xFFFF0000;
	char *core = (char *)VirtualAlloc(0, reserve, 0x2000, 4);
	if (core)
	{
		size = 0x100000;
		if (m_commit4DC > 0x100000)
			size = AlignUp(m_commit4DC, m_page4D4);
		if (size > reserve)
			size = reserve;
		core = (char *)VirtualAlloc(core, size, 0x1000, 4);
	}
	if (!core)
	{
		unsigned int type = 0x3000;
		if (m_topDown498)
			type = 0x103000;
		core = (char *)VirtualAlloc(0, size, type, 4);
		if (core)
		{
			kind = 3;
			reserve = size;
		}
	}
	if (core)
	{
		CoreBlock *block = (CoreBlock *)core;
		block->m_reserved8 = size;
		block->m_size4 = size;
		block->m_core0 = (void *)((unsigned int)(core + 0x27) & 0xFFFFFFF8);
		block->m_mapped = (kind >> 1) & 1;
		CoreBlock *last = m_head448.m_prev1C;
		CoreBlock *head = &m_head448;
		block->m_prev1C = head;
		bool sf = last != head;
		block->m_shouldFree = sf;
		block->m_shouldTrim = sf;
		bool *pe = &block->m_flagE;
		*pe = true;
		block->m_free10 = 0;
		block->m_context14 = 0;
		block->m_next18 = head->m_next18;
		head->m_next18 = block;
		block->m_next18->m_prev1C = block;
		unsigned int *chunk = (unsigned int *)block->m_core0;
		block->m_reserved8 = reserve;
		chunk[0] = 0;
		chunk[1] = (unsigned int)(core + size - (char *)chunk) | kind;
		AddDoubleFencepost(chunk, 0);
		return chunk;
	}
	return 0;
}

}
}
