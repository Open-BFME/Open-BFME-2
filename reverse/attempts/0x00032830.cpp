// ?rva00032830@GeneralAllocator@Allocator@EA@@QAE_NPBXH@Z
// partial score=0.96 date=2026-10-05
// ?rva00032830@GeneralAllocator@Allocator@EA@@QAE_NPBXH@Z
// partial score=0.96 date=2026-10-05
// cl: /O2 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// ?rva00032830@GeneralAllocator@Allocator@EA@@QAE_NPBXH@Z @0x00032830 (227B):
// bank score=0.96 date=2026-10-05 (228B emitted, exact through 0x32853). Residue: (1) sentinel lea-ecx-vs-add-esi rotation from 0x32853 (fleet cl emits lea whenever valid-carry range arms keep bl reserved; direct-return shape un-rotates to add-esi but blows the range +28B -- rotation driver is the range-arm bool liveness, not the sentinel spelling; 6 sentinel spellings exhausted); (2) addressType test mov-dl/test-dl (6B, volatile-byte view of int slot) vs retail cmp-byte-[esp+0x14],0 (5B) = the +1B -- volatile forces a true stack read but still load+test, never 80-form cmp; plain-int mov-edx/test-edx, bool-type mov-dl/test-dl all 6B (BV strong form FALSIFIED). Resolved vs prior 0.94 bank: flag mov-bl/test-mem-bl form (pair present, mov hoisted 2B before the sz-and under this allocation), compute-then-release with sete-bl eq arm, xor-bl range-fail, three release blocks, sz re-read, nop padding all match modulo reg names.
// ValidateAddress-like: lock at +0x4E4 with count at +0x18, outer intrusive
// search via sentinel at +0x448 (head at +0x460, size at +4, next at +0x18)
// then inner chunk walk via sizes at +4 masked with 0x7FFFFFF8 and footer
// flag at [size+start+4] bit0, addressType!=0 returns (block==start+8) else
// (start+8<=block<end). Callers MemoryPool::_IsValidBlock at 0x000305E0
// (block,1) and Rva006C1F60::rva006C1E20 at 0x006C1E20 (block,0).
//
// Split out of memory_pool.cpp, which already rows 20 allocator bodies and
// cannot absorb another edit without re-risking all of them. The class layout
// here is the subset this body needs; it agrees with memory_pool.cpp's
// GeneralAllocator at every offset both spell (+0x448 sentinel, +0x4E4 lock).
//
// Shape notes (retail-observed, seat49 r9-r11 + retail disassembly):
// - Genuine ABI per pin 4565 + memory_pool.cpp:81: (const void*, int)->bool.
// - Lock first (this->esi, lock->edi); sentinel from this so the address
//   folds to add esi,0x448; block used straight from its stack slot (no b
//   local) so it reloads per iteration into edx; one bool carries flag-1
//   (mov bl,1 + test mem,bl) into the range result and is overwritten by
//   sete bl on the equality arm; low byte of addressType tested directly
//   (sibling Rva006C1E20 tag spelling) for the cmp-byte-on-stack-slot form.
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	bool rva00032830(const void *block, int addressType);	// ValidateAddress-like

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
	unsigned char m_pad468[0x4E4 - (0x448 + sizeof(ListNode))];
	Lock *m_4E4;
};

// ?rva00032830@GeneralAllocator@Allocator@EA@@QAE_NPBXH@Z present-unmatched
bool GeneralAllocator::rva00032830(const void *block, int addressType)
{
	GeneralAllocator *self = this;
	Lock *lock = self->m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	ListNode *cur = self->m_sentinel.m_next;
	self = (GeneralAllocator *)((char *)self + 0x448);
	ListNode *sent = (ListNode *)self;
	while (cur != sent)
	{
		if ((unsigned int)block >= (unsigned int)cur)
		{
			unsigned int end = (unsigned int)cur + cur->m_size;
			if ((unsigned int)block < end)
				goto found;
		}
		cur = cur->m_next;
	}
	goto fail;
found:
	{
		unsigned int start = cur->m_unk0;
		unsigned int end = (*(const unsigned int *)(start + 4) & 0x7FFFFFF8) + start;
		if (end < (unsigned int)block)
		{
			do
			{
				if (end == start)
					break;
				unsigned int nextSize = *(const unsigned int *)(end + 4) & 0x7FFFFFF8;
				start = end;
				end += nextSize;
			} while (end < (unsigned int)block);
		}
		unsigned int sz = *(const unsigned int *)(start + 4) & 0x7FFFFFF8;
		bool valid = true;
		if ((*(const unsigned char *)(sz + start + 4) & valid) == 0)
			goto fail;
		start += 8;
		if (*(volatile unsigned char *)&addressType != 0)
		{
			bool eq = ((unsigned int)block == start);
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return eq;
		}
		else
		{
			if ((unsigned int)block < start || (unsigned int)block >= end)
				valid = false;
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return valid;
		}
	}
fail:
	if (lock != 0)
	{
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return false;
}

}
}
