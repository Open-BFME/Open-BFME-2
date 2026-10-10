// ?rva00031D00@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.6174358638171409 date=2026-10-10
template<class T> static __forceinline T p4Operand(const T &v) { return *(const volatile T*)&v; }
// ?rva00031D00@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.7 date=2026-10-06
// ?rva00031D00@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.7 date=2026-10-06
// Banked candidate for GeneralAllocator depth-guarded block score @0x00031D00 (351B).
// Home: Code/GameEngine/Source/Common/System/memory_pool.cpp (members m_440/m_470/m_4D4
// already located there; declarations added in failed attempt, reverted).
// Full retail decode in re_attempts.log; semantics settled. WALL = ebx/esi/edi rotation:
// retail homes this=edi lock=ebx score=esi masked=ebp; every source shape tried homes
// this=ebx (or ebp) lock=esi score=edi. 12 scratch variants tested (V2-V20): temp
// elimination (masked/end/blockEnd/mask/base inlined), size-liveness kill (fresh-load bit
// term), decl-order swap (depth before score), signed/unsigned size/masked/depth, upfront
// decls. Closest V4 (no end local): 235/351 diffs. Same-TU 0x31680 visibility ruled out
// (callee touches volatiles only). Next: sculpt post-call temps to retail spill pattern
// (base loaded twice not homed; end computed once reused twice + recomputed for -0x10 term),
// then re-probe rotation; or permute.py from this stash. t=70 model=muse-spark
#include <string.h>

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
	struct ListNode
	{
		unsigned int m_unk0;
		unsigned int m_size;
		unsigned char m_pad[16];
		ListNode *m_next;
		ListNode *m_prev;
	};
	struct Lock
	{
		unsigned char m_pad[0x18];
		int volatile m_count;
	};
	void *rva00031680(const void *block);
	int rva00031D00(const void *block);

	unsigned char m_pad0[0x440];
	void *m_440;
	unsigned char m_pad444[0x448 - 0x444];
	ListNode m_sentinel;
	unsigned char m_padAfterSentinel[0x470 - (0x448 + sizeof(ListNode))];
	unsigned int m_470;
	unsigned char m_pad474[0x4D4 - 0x474];
	unsigned int m_4D4;
	unsigned char m_pad4D8[0x4E4 - 0x4D8];
	Lock *m_4E4;
};

int GeneralAllocator::rva00031D00(const void *block)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	int score = 0;
	int depth = m_470;
	if (depth <= 1)
	{
		unsigned int next = depth + 1;
		m_470 = next;
		unsigned int size = *(const unsigned int *)((const char *)block + 4);
		score = ((size & 0x7FFFFFF8) >= 0x40000000);
		if ((size & 2) != 0)
		{
			score += (rva00031680(block) != 0);
			score += ((((unsigned int)block - *(const unsigned int *)block) & (m_4D4 - 1)) != 0);
			score += ((((unsigned int)block + (size & 0x7FFFFFF8) + 0x10) & (m_4D4 - 1)) != 0);
			score += ((((unsigned int)block) & 7) != 0);
		}
		else
		{
			void *node = rva00031680(block);
			score += (node == 0);

			score += ((unsigned int)block < *(const unsigned int *)node);
			score += ((unsigned int)block >= *(const unsigned int *)node + *(const unsigned int *)((const char *)node + 4));
			unsigned int blockEnd = (unsigned int)block + (size & 0x7FFFFFF8);
			score += (blockEnd >= *(const unsigned int *)node + *(const unsigned int *)((const char *)node + 4));
			if (block == m_440)
			{
				score += (*(const void *const *)((const char *)block + 8) != block
					|| *(const void *const *)((const char *)block + 0xC) != block);
				score += (((size & 0x7FFFFFF8)) < 0x10);
				score += (((*(const unsigned int *)((const char *)block + 4)) & 1) == 0);
			}
			else if (m_sentinel.m_prev == m_sentinel.m_next)
			{
				score += ((unsigned int)block < *(const unsigned int *)node);
				score += (*(const unsigned int *)node + *(const unsigned int *)((const char *)node + 4) - 0x10 < (this?p4Operand(blockEnd):p4Operand(blockEnd)));
			}
		}
		m_470 = next - 1;
	}
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return score;
}

}}
