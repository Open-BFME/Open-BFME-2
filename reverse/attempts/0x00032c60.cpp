// ?rva00032C60@GeneralAllocator@Allocator@EA@@QAEII@Z
// partial score=0.78 date=2026-10-05
// ?rva00032C60@GeneralAllocator@Allocator@EA@@QAEII@Z
// partial score=0.78 date=2026-10-05
// ?rva00032C60@GeneralAllocator@Allocator@EA@@QAEII@Z
// partial score=0.78 date=2026-10-05
// @0x00032C60 386B purge/decommit-engine trial-1 (meta-9-continue-r1, owner scale-20261005-meta-9)
// Stash: trial block lived in Code/GameEngine/Source/Common/System/Rva00031010Insert.cpp
// home TU (rowed 31010 66B intact, 1/1 green), TU fully reverted after explain.
// Trial-1 (THIS BODY, 389/386 +3B): native reconstruction from r9/seat-48-r2
// structural guide; class scope GeneralAllocator@Allocator@EA carried from
// rowed memory_pool.cpp agreement (+0x30/+0x440/+0x448/+0x4DC/+0x4E4), not donor.
// Providers: rowed AddDoubleFencepost 31120 (declare+call) + Trial IAT stand-ins
// for Enter/Leave/VirtualFree (real names for landing; Trial kept shape).
// EXACT in trial-1: sub esp,0x10 + 4-push prolog + mov ebp,ecx + lock spill pair
// + Enter/inc + head/sentinel/acc spill + je exit (0x32C60-0x32C99, 63B exact);
// growth shr/add/and + need2 sub + lea double + cmp + mov ebp + jae shape;
// VirtualFree push 0x4000/ebp/eax + call + test/je shape; acc/node add/sub shape;
// unlink 6-insn + retag + AddDoubleFencepost call + insert quad + ebp/edi restore
// + next/leave/return shapes present.
// RESIDUE (trial-2 recipe): (1) sz in eax not esi + mem-test vs al-test at
// 0x32CAE (mov eax,[ebx+4] + test byte [eax+ebx-0xC],1 vs mov esi + mov al +
// test al,1; need sz->esi steering, try unsigned-vs-int sz type or tag use-twice
// to defeat mem-test fold); (2) doubling-loop nop 6B lea ebx,[ebx] vs 2B mov
// edi,edi (follows from loop-size delta; fix 1 first); (3) acc/node update order
// + reg roles (eax/edx vs ecx/edx, this-reload position); (4) unlink/retag/insert
// reg roles (edx/eax vs ecx/edx swaps, insert extra mov eax,ecx from this-held
// ecx); (5) final Leave ecx vs edx + Trial IAT address (switch Trial imports to
// real Enter/Leave/VirtualFree for landing; import refs must be real names).
// See /mnt/titan_nv3/open-bfme2-agent-fleet/normal-restart/meta-9-continue-explain1.txt
// for the full side-by-side diff (389B, first diff +0x3F, classification
// instruction/register encoding mismatch).
extern "C" __declspec(dllimport) void __stdcall TrialEnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall TrialLeaveCriticalSection(void *section);
extern "C" __declspec(dllimport) void *__stdcall TrialVirtualFree(void *address, unsigned size, unsigned type);

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	static void AddDoubleFencepost(void *chunk, unsigned int flags);
	unsigned int rva00032C60(unsigned int size);

private:
	struct FreeChunk
	{
		unsigned int m_0;
		unsigned int m_size4;
		FreeChunk *m_next8;
		FreeChunk *m_prevC;
	};
	struct LargeNode
	{
		unsigned int m_unk0;
		unsigned int m_size4;
		unsigned char m_pad8[5];
		unsigned char m_flagD;
		unsigned char m_padE;
		unsigned char m_flagF;
		unsigned char m_pad10[8];
		LargeNode *m_next18;
		LargeNode *m_prev1C;
	};
	struct Lock
	{
		unsigned char m_pad[0x18];
		int volatile m_count;
	};
	unsigned char m_pad0[0x30];
	FreeChunk m_bin30;
	unsigned char m_pad40[0x440 - 0x40];
	FreeChunk *m_head440;
	unsigned char m_pad444[0x448 - 0x444];
	LargeNode m_sentinel448;
	unsigned char m_pad468[0x4DC - 0x468];
	unsigned int m_grow4DC;
	unsigned char m_pad4E0[0x4E4 - 0x4E0];
	Lock *m_lock4E4;
};

unsigned int GeneralAllocator::rva00032C60(unsigned int size)
{
	Lock *lock = m_lock4E4;
	if (lock != 0)
	{
		TrialEnterCriticalSection(lock);
		++lock->m_count;
	}
	unsigned int acc = 0;
	LargeNode *sent = &m_sentinel448;
	for (LargeNode *node = m_sentinel448.m_next18; node != sent; node = node->m_next18)
	{
		if (node->m_flagD == 0)
			continue;
		unsigned int sz = node->m_size4;
		unsigned char tag = *(unsigned char *)((char *)node + sz - 0x0C);
		unsigned int saved = sz;
		unsigned char *chunkB = (unsigned char *)((char *)node + sz - 0x10);
		if ((tag & 1) != 0)
			continue;
		unsigned int first = *(unsigned int *)chunkB;
		unsigned char f2 = node->m_flagF;
		unsigned char *chunk = chunkB - first;
		if (f2 == 0)
			continue;
		unsigned int usable = *(unsigned int *)(chunk + 4) & 0x7FFFFFF8;
		unsigned int need = size + 0x40;
		if (usable <= need)
			continue;
		unsigned int round = ((m_grow4DC >> 1) + 0xFFFF) & 0xFFFF0000;
		unsigned int need2 = usable - need;
		unsigned int commit = round;
		if (round + round < need2)
		{
			unsigned int limit = round + round;
			do
			{
				limit += round;
				commit += round;
			} while (limit < need2);
		}
		if (commit >= need2)
			continue;
		void *addr = (char *)node + (saved - commit);
		if (TrialVirtualFree(addr, commit, 0x4000) == 0)
			continue;
		acc += commit;
		node->m_size4 -= commit;
		FreeChunk *fc = (FreeChunk *)chunk;
		if (fc != m_head440)
		{
			fc->m_next8->m_prevC = fc->m_prevC;
			fc->m_prevC->m_next8 = fc->m_next8;
		}
		unsigned int oldTag = fc->m_size4;
		unsigned int remain = usable - commit;
		remain += 0x10;
		remain |= (oldTag & 0x80000007);
		fc->m_size4 = remain;
		AddDoubleFencepost(fc, 0);
		if (fc != m_head440)
		{
			FreeChunk *old = *(FreeChunk **)((char *)this + 0x3C);
			FreeChunk *bin = (FreeChunk *)((char *)this + 0x30);
			fc->m_next8 = bin;
			fc->m_prevC = old;
			bin->m_prevC = fc;
			old->m_next8 = fc;
		}
	}
	if (lock != 0)
	{
		--lock->m_count;
		TrialLeaveCriticalSection(lock);
	}
	return acc;
}

}
}
