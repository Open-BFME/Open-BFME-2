// ?rva00031E60@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.5 date=2026-10-06
// ?rva00031E60@GeneralAllocator@Allocator@EA@@QAEHPBX@Z
// partial score=0.5 date=2026-10-06
// Banked candidate for GeneralAllocator block score @0x00031E60 (301B).
// Home: Code/GameEngine/Source/Common/System/memory_pool.cpp (same members as 0x31D00).
// Full retail decode in re_attempts.log; semantics settled (score opens with 0x31D00 call,
// fence/bit/neighbour terms, low-3-bits term added twice, gated neighbour-equality pair,
// sub-0x10 blocks score greater-than-4). WALL (expected, untested): same ebx/esi/edi
// rotation as twin 0x31D00 (retail this=ebp lock=esi here). Land 0x31D00 first (same-TU
// callee), then shape this body to retail spills (size spilled not ebp-homed). t=70 model=muse-spark
#include <string.h>

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

class ScratchAlloc
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
	int probe31D00(const void *block);
	int rva00031E60(const void *block);

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

int ScratchAlloc::rva00031E60(const void *block)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	unsigned int size = *(const unsigned int *)((const char *)block + 4) & 0x7FFFFFF8;
	unsigned int blockEnd = size + (unsigned int)block;
	int score = probe31D00(block);
	unsigned int header = *(const unsigned int *)((const char *)block + 4);
	unsigned int masked = header & 0x7FFFFFF8;
	score += (*(const unsigned char *)(masked + (unsigned int)block + 4) & 1);
	score += ((header >> 1) & 1);
	if ((unsigned int)block >= 0x10)
	{
		score += ((((unsigned int)block) & 7) != 0);
		score += ((((unsigned int)block) & 7) != 0);
		score += (*(const unsigned int *)blockEnd != (unsigned int)block);
		score += (~header & 1);
		if (block != m_440)
		{
			unsigned int fence = *(const unsigned int *)((const char *)blockEnd + 4) & 0x7FFFFFF8;
			score += ((*(const unsigned char *)(fence + blockEnd + 4) & 1) == 0);
		}
		void *next = *(void **)((const char *)block + 8);
		void *after = *(void **)((const char *)block + 0xC);
		score += (*(const unsigned int *)((const char *)after + 8) != (unsigned int)block);
		score += (*(const unsigned int *)((const char *)next + 0xC) != (unsigned int)block);
		if (block == after || block == next)
		{
			score += (next != after);
			score += (block != m_440);
		}
	}
	else
	{
		score += ((unsigned int)block > 4);
	}
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return score;
}
