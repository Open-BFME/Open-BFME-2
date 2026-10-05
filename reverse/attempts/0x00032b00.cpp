// ?rva00032B00@GeneralAllocator@Allocator@EA@@QAEPAXI@Z
// partial score=0.85 date=2026-10-05
// ?rva00032B00@GeneralAllocator@Allocator@EA@@QAEPAXI@Z
// partial score=0.85 date=2026-10-05
// @0x00032B00 343B segment reserve-grow leaf trial-3 (meta9, owner scale-20261005-meta-9)
// Stash: trial block lived in Code/GameEngine/Source/Common/Rva00034C90Finish.cpp
// home TU (wrapper + funclet intact, 2/2 green), TU fully reverted after explain.
// Trial-1 (0.50, 360B): frame spills, sar kindbit, ternary neg/sbb, seg-homed esi.
// Trial-2 (unscored stepping stone, 349B): unsigned kind, +8-first stores,
//   data-before-kind, bool sentinel, fresh gran reads, if/else type, no seg local.
// Trial-3 (THIS BODY, 0.85, 343/343 SIZE-EXACT): trial-2 + (a) base reassigned
//   from commit-call result (base stays eax through init, kind gets register,
//   frame gone) + (b) type assign-then-override (kills neg/sbb, matches retail
//   mov-eax-before-je). Target-native reconstruction; donor-negative family.
// Offsets +0x448/+0x460/+0x464/+0x498/+0x4D4/+0x4D8/+0x4DC agree with the rowed
// memory_pool.cpp GeneralAllocator view; labels descriptive-only.
// IAT 0xBBA1A4 call shape (0,size,0x2000/0x1000/0x3000,4) = VirtualAlloc.
// EXACT in trial-3: 4-push prolog shape, mov ebx,1 placement, 3x call arg
// sequences, reserve round64k + commit clamp, type mov-before-je pair,
// kind=3/reserve reassign, +8/+4/data/kindbit stores, shr+and-dl kindbit.
// RESIDUE (trial-4 recipe): (1) head reg-role swap (mask edx not ecx, min ecx
// not edx; min-clamp recompute dec/not not CSE-reuse); (2) arg prefetch before
// pushes not after; (3) sentinel prev spilled to dead arg slot + E=1 hoisted
// above link store (wants load-prev,lea,store-link,reg-cmp,setne-dl order with
// no spill); (4) splice via edi not sentinel-ecx; (5) header-0 store sank late
// + tagged/bodySize eax-edx role swap; (6) footer [edx+ecx] not [eax+ecx]
// (needs bodySize-eax + data-ecx); (7) fail path fall-through not far-je +
// xor-eax block. See scale-pass meta-9-explain3.txt (titan_nv3 normal-restart)
// for the full side-by-side diff.
extern "C" __declspec(dllimport) void *__stdcall TrialVirtualAlloc(void *address, unsigned size, unsigned type, unsigned protect);

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	void *rva00032B00(unsigned size);
private:
	struct ListNode
	{
		unsigned int m_unk0;
		unsigned int m_size4;
		unsigned char m_pad8[16];
		ListNode *m_next18;
		ListNode *m_prev1C;
	};
	struct Segment
	{
		void *m_data0;
		unsigned int m_size4;
		unsigned int m_size8;
		unsigned char m_kindC;
		unsigned char m_nonemptyD;
		unsigned char m_flagE;
		unsigned char m_nonemptyF;
		unsigned int m_zero10;
		unsigned int m_zero14;
		ListNode *m_next18;
		ListNode *m_link1C;
	};
	unsigned char m_pad0[0x448];
	ListNode m_sentinel448;
	unsigned char m_pad468[0x498 - 0x468];
	unsigned char m_flag498;
	unsigned char m_pad499[0x4D4 - 0x499];
	unsigned int m_gran4D4;
	unsigned int m_min4D8;
	unsigned int m_commit4DC;
};

void *GeneralAllocator::rva00032B00(unsigned size)
{
	unsigned int kind = 1;
	unsigned int aligned = (m_gran4D4 + size - 1) & ~(m_gran4D4 - 1);
	if (aligned < m_min4D8)
		aligned = (m_min4D8 + m_gran4D4 - 1) & ~(m_gran4D4 - 1);
	unsigned int reserve = (aligned + 0xFFFF) & 0xFFFF0000;
	unsigned char *base = (unsigned char *)TrialVirtualAlloc(0, reserve, 0x2000, 4);
	if (base != 0)
	{
		aligned = 0x100000;
		if (m_commit4DC > 0x100000)
			aligned = (m_commit4DC + m_gran4D4 - 1) & ~(m_gran4D4 - 1);
		if (aligned > reserve)
			aligned = reserve;
		base = (unsigned char *)TrialVirtualAlloc(base, aligned, 0x1000, 4);
		if (base != 0)
			goto init;
	}
	unsigned int type = 0x3000;
	if (m_flag498)
		type = 0x103000;
	base = (unsigned char *)TrialVirtualAlloc(0, aligned, type, 4);
	if (base == 0)
		return 0;
	kind = 3;
	reserve = aligned;
init:
	((Segment *)base)->m_size8 = aligned;
	((Segment *)base)->m_size4 = aligned;
	unsigned char *data = (unsigned char *)(((unsigned int)base + 0x27) & 0xFFFFFFF8);
	((Segment *)base)->m_data0 = data;
	((Segment *)base)->m_kindC = (unsigned char)((kind >> 1) & 1);
	ListNode *prev = m_sentinel448.m_prev1C;
	((Segment *)base)->m_link1C = &m_sentinel448;
	bool nonempty = (prev != &m_sentinel448);
	((Segment *)base)->m_nonemptyD = nonempty;
	((Segment *)base)->m_nonemptyF = nonempty;
	((Segment *)base)->m_flagE = 1;
	((Segment *)base)->m_zero10 = 0;
	((Segment *)base)->m_zero14 = 0;
	ListNode *head = m_sentinel448.m_next18;
	((Segment *)base)->m_next18 = head;
	m_sentinel448.m_next18 = (ListNode *)base;
	head->m_prev1C = (ListNode *)base;
	((Segment *)base)->m_size8 = reserve;
	unsigned int span = aligned - (unsigned int)(data - base);
	*(unsigned int *)data = 0;
	unsigned int tagged = span | kind;
	unsigned int bodySize = ((tagged & 0x7FFFFFF8) - 9) & 0xFFFFFFF8;
	*(unsigned int *)(data + 4) = (tagged & 0x80000007) | bodySize;
	*(unsigned int *)(bodySize + data) = bodySize;
	*(unsigned int *)(bodySize + data + 4) = 8;
	*(unsigned int *)(bodySize + data + 8) = 8;
	*(unsigned int *)(bodySize + data + 12) = 9;
	return data;
}

}
}
