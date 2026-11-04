// ?wrapper@Rva00034C90@@QAEXXZ
// cl: /MD /EHsc
// platformsdk
#include <windows.h>
// ?wrapper@Rva00034C90@@QAEXXZ @0x00034C90 104B address-derived refcount guard
// wrapper: m_pLock at +0x4E4 points at a CRITICAL_SECTION+refcount lock.
// EnterCriticalSection (IAT 0xBBA200) runs, the volatile +0x18 refcount is
// incremented, body 0x33930 runs, then the refcount is decremented and
// LeaveCriticalSection (IAT 0xBBA204) runs. Same lock layout as the rowed
// Rva00030DD0 addref at 0x00030DD0. The two IAT calls are declared
// by the Windows SDK. /EHsc keeps these C-linkage calls nonthrowing, so
// cl omits the EH state reset retail does not carry.

class Rva00034C90Lock
{
public:
	void *m_obj;
	Rva00034C90Lock(void *obj) : m_obj(obj)
	{
		if (m_obj)
		{
			EnterCriticalSection(static_cast<CRITICAL_SECTION *>(m_obj));
			++*(volatile int *)((char *)m_obj + 0x18);
		}
	}
	// Out of line (the EH funclet's call) this is the release at 0x000317C0:
	// one load of the lock pointer, so the count goes through ecx like retail.
	~Rva00034C90Lock()
	{
		void *held = m_obj;
		if (held)
		{
			--*(volatile int *)((char *)held + 0x18);
			LeaveCriticalSection(static_cast<CRITICAL_SECTION *>(held));
		}
	}
};

class Rva00034C90Block
{
public:
	unsigned m_prevSize;
	unsigned m_sizeAndFlags;
	Rva00034C90Block *m_prev;
	Rva00034C90Block *m_next0C;
};

class Rva00033B90Allocator
{
public:
	bool rva00033700(void *, unsigned int, bool, void *, void *, void *);
};

class Rva00034C90
{
public:
	void consolidate();
	void wrapper();
private:
	char m_pad00[4];
	unsigned m_count04;
	char m_buckets08[0x28];
	Rva00034C90Block m_anchor30;
	char m_pad40[0x400];
	Rva00034C90Block *m_cur440;
	char m_pad444[0xa0];
	void *m_pLock;
};

void Rva00034C90::wrapper()
{
	Rva00034C90Lock lock(m_pLock);
	consolidate();
}

// ?consolidate@Rva00034C90@@QAEXXZ @0x00033930 325B true extent (ret 0x33A74)
// address-derived thiscall no-arg member of Rva00034C90 reached from wrapper
// 0x00034C90; coalesce pass over buckets +0x08.. anchored list +0x30 with
// cur +0x440; far-tail inits via rowed Rva00033B90Allocator::rva00033700.
void Rva00034C90::consolidate()
{
	if (m_count04 != 0)
	{
		Rva00034C90Block **bucketEnd = (Rva00034C90Block **)((char *)this + (m_count04 >> 3) * 4);
		Rva00034C90Block **bucket = (Rva00034C90Block **)((char *)this + 8);
		Rva00034C90Block *anchor = (Rva00034C90Block *)((char *)this + 0x30);
		for (;;)
		{
			Rva00034C90Block *block = *bucket;
			if (block != 0)
			{
				*bucket = 0;
				Rva00034C90Block *next = block->m_next0C;
				do
				{
					next = block->m_next0C;
					Rva00034C90Block *neighbor;
					block->m_sizeAndFlags &= 0x7ffffffbU;
					unsigned base = block->m_sizeAndFlags & 0x7ffffff8U;
					neighbor = (Rva00034C90Block *)((char *)block + base);
					unsigned head = *(unsigned *)((char *)neighbor + 4) & 0x7ffffff8U;
					if ((block->m_sizeAndFlags & 1) == 0)
					{
						unsigned prevSize = block->m_prevSize;
						base += prevSize;
						block = (Rva00034C90Block *)((char *)block - prevSize);
						block->m_sizeAndFlags = base | 1;
						neighbor->m_prevSize = base;
						block->m_prev->m_next0C = block->m_next0C;
						block->m_next0C->m_prev = block->m_prev;
					}
					if ((*(unsigned char *)((char *)neighbor + head + 4) & 1) != 0)
					{
						*(unsigned *)((char *)neighbor + 4) &= 0xfffffffeU;
						neighbor->m_prevSize = base;
					}
					else
					{
						neighbor->m_prev->m_next0C = neighbor->m_next0C;
						neighbor->m_next0C->m_prev = neighbor->m_prev;
						base += head;
						block->m_sizeAndFlags = base | 1;
						*(unsigned *)((char *)block + base) = base;
					}
					Rva00034C90Block *cur = m_cur440;
					if (block != cur && neighbor != cur)
					{
						Rva00034C90Block *tail = anchor->m_next0C;
						block->m_prev = anchor;
						block->m_next0C = tail;
						anchor->m_next0C = block;
						tail->m_prev = block;
					}
					else
					{
						m_cur440 = block;
						block->m_next0C = block;
						block->m_prev = block;
						block->m_sizeAndFlags = base | 1;
						*(unsigned *)((char *)block + base) = base;
					}
					block = next;
				} while (next != 0);
			}
			Rva00034C90Block **prev = bucket;
			bucket = (Rva00034C90Block **)((char *)bucket + 4);
			if (prev == bucketEnd)
				break;
		}
		m_count04 &= 0xfffffffeU;
	}
	else
	{
		((Rva00033B90Allocator *)this)->rva00033700(0, 0, true, 0, 0, 0);
	}
}
