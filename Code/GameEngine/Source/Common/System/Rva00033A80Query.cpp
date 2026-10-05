// cl: /O2 /MD
//
// ?rva00033A80@GeneralAllocator@Allocator@EA@@QAEI_N@Z @0x00033A80 269B.
// Largest-block query over the allocator bins. Counted lock-guard via the
// proven Rva00035080Lock RAII idiom (EnterCriticalSection IAT 0xBBA200 /
// LeaveCriticalSection IAT 0xBBA204 declared dllimport+throw(), SEH stub
// 0xB5CC48), same as the rowed 0x35080/0x35190/0x35210 wrappers. Returns 0
// when the +0x440 member is null; with a true argument it first calls the
// pinned (not rowed) body 0x00033930 via the existing
// ?rva00033930@Rva00034C90@@QAEXXZ pin, which this call reuses and does not
// extend. Best starts at [[+0x440]+4] masked with 0x7FFFFFF8, then takes the
// max over three bin walks: 127 eight-byte slots down from +0x428 (valid
// entries are not self-linked at +0xC), the +0x3C list against the +0x30
// sentinel (size at +4, next at +0xC), and, unless the flag is set and best
// already reaches [+0x4], up to ten dwords down from +0x2C. Address-derived
// name; member offsets are target facts, type labels descriptive.
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs) throw();
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs) throw();

class Rva00035080Lock
{
public:
	void *m_obj;
	Rva00035080Lock(void *obj) : m_obj(obj)
	{
		if (m_obj)
		{
			EnterCriticalSection(m_obj);
			++*(volatile int *)((char *)m_obj + 0x18);
		}
	}
	~Rva00035080Lock()
	{
		if (m_obj)
		{
			--*(volatile int *)((char *)m_obj + 0x18);
			LeaveCriticalSection(m_obj);
		}
	}
};

class Rva00034C90
{
public:
	void rva00033930();
};

namespace EA
{
namespace Allocator
{

class GeneralAllocator
{
public:
	struct BinNode
	{
		unsigned int m_unk0;
		unsigned int m_size;
		unsigned int m_unk8;
		BinNode *m_next;
	};

	unsigned int rva00033A80(bool full);

private:
	unsigned int m_00;
	unsigned int m_04;
	void *m_candidates[10];
	BinNode m_sentinel30;
	unsigned char m_bins40[0x428 - 0x40];
	void *m_428top;
	unsigned char m_pad42C[0x440 - 0x42C];
	void *m_440;
	unsigned char m_pad444[0x4E4 - 0x444];
	void *m_pLock;
};

unsigned int GeneralAllocator::rva00033A80(bool full)
{
	Rva00035080Lock lock(m_pLock);
	unsigned int best = 0;
	if (m_440 != 0)
	{
		if (full)
			((::Rva00034C90 *)this)->rva00033930();
		best = *(const unsigned int *)((const char *)m_440 + 4) & 0x7FFFFFF8;
		unsigned int count = 0xFE;
		void **slot = (void **)((char *)this + 0x428);
		do
		{
			void *entry = *slot;
			if (*(void **)((char *)entry + 0xC) == entry)
			{
				count -= 2;
				slot = (void **)((char *)slot - 8);
			}
			else
			{
				unsigned int size = *(const unsigned int *)((char *)entry + 4) & 0x7FFFFFF8;
				if (size > best)
					best = size;
				break;
			}
		} while (count >= 2);
		BinNode *head = m_sentinel30.m_next;
		BinNode *sentinel = &m_sentinel30;
		while (head != sentinel)
		{
			unsigned int size = head->m_size & 0x7FFFFFF8;
			if (size > best)
				best = size;
			head = head->m_next;
		}
		if (!full)
		{
			if (best < m_04)
			{
				int left = 9;
				void **cand = (void **)((char *)this + 0x2C);
				do
				{
					void *entry = *cand;
					if (entry != 0)
					{
						unsigned int size = *(const unsigned int *)((char *)entry + 4) & 0x7FFFFFF8;
						if (size > best)
							best = size;
						break;
					}
					--left;
					--cand;
				} while (left >= 0);
			}
		}
	}
	return best;
}

}
}
