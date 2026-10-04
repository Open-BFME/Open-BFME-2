// cl: /O2 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// ?rva00032920@GeneralAllocator@Allocator@EA@@QAE_NPBX@Z @0x00032920 (190B):
// owns-address test. Header at block-4: bit1 selects the small-list scan, else
// the intrusive search. Lock at +0x4E4 with the use count at +0x18 of the
// wrapper.
//
// Split out of memory_pool.cpp, which already rows 20 allocator bodies and
// cannot absorb another edit without re-risking all of them. The class layout
// here is the subset this body needs; it agrees with memory_pool.cpp's
// GeneralAllocator at every offset both spell (+0x448 sentinel, +0x49C small
// list, +0x4A8 next, +0x4E4 lock).
//
// The return shape is what makes this body exact, and it took three earlier
// passes to read it correctly. Both prior banks recorded the residue as the
// block-selection decision or the scan's compare form; the real constraint is
// the NUMBER OF LOCK-RELEASE BLOCKS.
//
// Retail emits exactly two release blocks: the scan's not-found return at
// 0x00032981 and the shared true return at 0x000329C3. The intrusive branch
// does not own a third -- its `test eax,eax / je 0x00032981` falls into the
// scan's not-found return. With three blocks (one per branch plus the scan's)
// MSVC picks a different copy of the identical release for the
// `test BYTE PTR [esp+0x14],2 / je` at +0x31, which is the single byte the
// 0.96 bank missed: the je landed at 0x0003299C rather than 0x000329B7.
//
// So the source gives the small-list scan BOTH of its returns -- true inside
// the loop, false by falling off the end -- and expresses the intrusive
// branch as an `else if` that returns true on a hit and otherwise falls
// through to that same single false return. That is two returns total, and
// the je reaches the intrusive block.
//
// Verified wrong and reverted: folding the result onto one `owns` flag with a
// single shared release drops the body to 143B, because the shared release
// makes the scan's loop-invariant compare hoist out of the loop. Inverting the
// test so the intrusive path is the fall-through gives jne +0x42 instead of
// je +0x64. A goto-based convergence of the two false paths is the same
// shape but 192B, two over. A flag variant of the scan's empty-list early
// return (the previous pass's best) is byte-identical to the bank.
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	bool rva00032920(const void *block);	// owns-address test
	void *rva00031680(const void *block);	// intrusive circular-list search

private:
	// Intrusive list node proven by 0x00031680 (size at +4, next at +0x18) and
	// by retail's scan here (node base at +0, next at +0xC).
	struct ListNode
	{
		unsigned int m_unk0;
		unsigned int m_size;
		unsigned char m_pad[16];
		ListNode *m_next;
		ListNode *m_prev;
	};
	unsigned char m_pad0[0x448];
	ListNode m_sentinel;
	// Lock wrapper proven by 0x00032A20: Enter/Leave on the pointer at
	// +0x4E4 with the use count at +0x18 of the wrapper.
	struct Lock
	{
		unsigned char m_pad[0x18];
		int volatile m_count;
	};
	// Small-block list proven by 0x00032920: sentinel at +0x49C with its next
	// at +0x4A8 (+0xC), nodes with their stored base at +0 and next at +0xC.
	struct SmallNode
	{
		unsigned int m_0;
		unsigned char m_pad[8];
		SmallNode *m_next;
	};
	unsigned char m_pad468a[0x49C - (0x448 + sizeof(ListNode))];
	SmallNode m_49C;
	unsigned char m_pad4AC[0x4E4 - (0x49C + sizeof(SmallNode))];
	Lock *m_4E4;
};

// ?rva00031680@GeneralAllocator@Allocator@EA@@QAEPAXPBX@Z @ 0x00031680 (47B):
// intrusive circular-list search returning the node containing the address, or
// null. Same body as the row memory_pool.cpp already carries for its own call
// sites; this copy is the callee of this body's non-small-list path, and its
// relative call is what fixes rva00032920's register allocation.
//
// ?rva00031680@GeneralAllocator@Allocator@EA@@QAEPAXPBX@Z present-unmatched
void *GeneralAllocator::rva00031680(const void *block)
{
	ListNode *cur = m_sentinel.m_next;
	ListNode *sentinel = &m_sentinel;
	while (cur != sentinel)
	{
		if ((unsigned int)block >= (unsigned int)cur)
		{
			unsigned int end = (unsigned int)cur + cur->m_size;
			if ((unsigned int)block < end)
				return cur;
		}
		cur = cur->m_next;
	}
	return 0;
}

// ?rva00032920@GeneralAllocator@Allocator@EA@@QAE_NPBX@Z @0x00032920 (190B):
// owns-address test. Header bit1 at block-4 selects the small-list scan at
// +0x49C: each node stores the block base it owns, and the test compares
// (p8 - p8's stored base) against (node - node's stored base) for equality, so
// a node matches when both are the same distance from their base -- the
// tie-break retail uses to pick between equal-distance fencepost candidates.
// Otherwise the intrusive search at 0x00031680 decides. Callers _Free at
// 0x000305B8 and _GetBlockHeap at 0x00030658.
//
// Two returns only: the scan returns true from inside its loop and false by
// falling off the end, and the intrusive branch returns true on a hit and
// otherwise falls through to that same false return. See the note above on why
// the count of release blocks is what makes this exact.
//
bool GeneralAllocator::rva00032920(const void *block)
{
	Lock *lock = m_4E4;
	const char *const blk = (const char *)block;
	const char *const p8 = blk - 8;
	unsigned int header = *(const unsigned int *)(p8 + 4);
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	if ((header & 2) != 0)
	{
		SmallNode *sent = &m_49C;
		SmallNode *cur = m_49C.m_next;
		if (cur != sent)
		{
			unsigned int v = *(const unsigned int *)p8;
			unsigned int off = (unsigned int)p8 - v;
			do
			{
				unsigned int nv = cur->m_0;
				if ((unsigned int)cur - nv == off)
				{
					if (lock != 0)
					{
						--lock->m_count;
						LeaveCriticalSection(lock);
					}
					return true;
				}
				cur = cur->m_next;
			} while (cur != sent);
		}
	}
	else if (rva00031680(block) != 0)
	{
		if (lock != 0)
		{
			--lock->m_count;
			LeaveCriticalSection(lock);
		}
		return true;
	}
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return false;
}

}
}