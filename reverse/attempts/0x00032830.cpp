// ?rva00032830@GeneralAllocator@Allocator@EA@@QAE_NPBX_N@Z
// partial score=0.94 date=2026-10-05
// cl: /O2 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// ?rva00032830@GeneralAllocator@Allocator@EA@@QAE_NPBX_N@Z @0x00032830 (227B):
// ValidateAddress-like: lock at +0x4E4 with count at +0x18, outer
// intrusive search via sentinel at +0x448 (head at +0x460, size at +4
// next at +0x18) then inner chunk walk via sizes at +4 masked with
// 0x7FFFFFF8 and footer flag at [size+start+4] bit0, type!=0 returns
// (block==start+8) else (start+8<=block<end). Callers _IsValidBlock at
// 0x000305F6 and 0x006C1E79.
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	bool rva00032830(const void *block, bool type);	// ValidateAddress-like

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

// ?rva00032830@GeneralAllocator@Allocator@EA@@QAE_NPBX_N@Z present-unmatched
bool GeneralAllocator::rva00032830(const void *block, bool type)
{
	Lock *lock = m_4E4;
	if (lock != 0)
	{
		EnterCriticalSection(lock);
		++lock->m_count;
	}
	ListNode *cur = m_sentinel.m_next;
	ListNode *const sent = &m_sentinel;
	unsigned int b = (unsigned int)block;
	while (cur != (ListNode *)sent)
	{
		if (b >= (unsigned int)cur)
		{
			unsigned int end = (unsigned int)cur + cur->m_size;
			if (b < end)
				goto found;
		}
		cur = cur->m_next;
	}
	goto fail;
found:
	{
		unsigned int start = cur->m_unk0;
		unsigned int end = (*(const unsigned int *)(start + 4) & 0x7FFFFFF8) + start;
		if (end < b)
		{
			do
			{
				if (end == start)
					break;
				unsigned int nextSize = *(const unsigned int *)(end + 4) & 0x7FFFFFF8;
				start = end;
				end += nextSize;
			} while (end < b);
		}
		unsigned int sz = *(const unsigned int *)(start + 4) & 0x7FFFFFF8;
		bool ok = true;
		if ((*(const unsigned char *)(sz + start + 4) & ok) == 0)
			goto fail;
		start += 8;
		if (type)
		{
			bool eq = (b == start);
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return eq;
		}
		else
		{
			bool inRange = true;
			if (b < start || b >= end)
				inRange = false;
			if (lock != 0)
			{
				--lock->m_count;
				LeaveCriticalSection(lock);
			}
			return inRange;
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