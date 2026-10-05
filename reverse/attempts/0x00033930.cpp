// ?rva00033930@Rva00034C90@@QAEXXZ
// partial score=0.85 date=2026-10-05
// ?wrapper@Rva00034C90@@QAEXXZ
// cl: /O2 /MD
// ?wrapper@Rva00034C90@@QAEXXZ @0x00034C90 104B address-derived refcount guard
// wrapper: m_pLock at +0x4E4 points at a CRITICAL_SECTION+refcount lock.
// EnterCriticalSection (IAT 0xBBA200) runs, the volatile +0x18 refcount is
// incremented, body 0x33930 runs, then the refcount is decremented and
// LeaveCriticalSection (IAT 0xBBA204) runs. Same lock layout as the rowed
// Rva00030DD0 addref at 0x00030DD0. The two IAT calls are declared
// dllimport+throw() so cl treats them as nothrow and omits the EH state reset
// retail does not carry.
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs) throw();
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs) throw();

class Rva00034C90Lock
{
public:
	void *m_obj;
	Rva00034C90Lock(void *obj) : m_obj(obj)
	{
		if (m_obj)
		{
			EnterCriticalSection(m_obj);
			++*(volatile int *)((char *)m_obj + 0x18);
		}
	}
	~Rva00034C90Lock()
	{
		if (m_obj)
		{
			--*(volatile int *)((char *)m_obj + 0x18);
			LeaveCriticalSection(m_obj);
		}
	}
};

class Rva00034C90Block
{
public:
	unsigned m_size00;
	unsigned m_head04;
	Rva00034C90Block *m_prev08;
	Rva00034C90Block *m_next0C;
};

class Rva00034C90
{
public:
	void rva00033930();
	void rva00033700(int a1, int a2, int a3, int a4, int a5, int a6);
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
	rva00033930();
}

// ?rva00033930@Rva00034C90@@QAEXXZ @0x00033930 325B true extent (ret 0x33A74)
// address-derived thiscall no-arg member of Rva00034C90 reached from wrapper
// 0x00034C90 (pin 7354, candidate not identity). Trial-2 from r10 bank 0.55:
// (1) next-test reads follow block [neighbor+nhead+4] bit0 (nhead live as
// offset; unlink/grow neighbor on clear, clear-bit+footer on set);
// (2) anchor pointer local (Block *anchor = this+0x30) so anchor.next emits
// [esi+0xC]; (3) main-first/else-tail arrangement for far-je init tail with
// this-homed [esp]; (4) next-in-ebp via folded direct splices (no p/n
// locals). Provider 0x00033700 investigated read-only: thiscall 6xint
// ret0x18 (pushes 0,0,1,0,0,0 from here), early-out on first two args zero,
// else tail-calls unrowed 0x000332D0 with this+6 args; init path sets up
// +0x04=0x40/buckets/anchor/cur/tables + IAT Enter/Leave + 0x30D90 Init.
// 33700 still unrowed/pin-less (zero symbols.csv hits); no pin added here.
// Member names descriptive-only; only offsets/sizes/masks/ABI are facts.
void Rva00034C90::rva00033930()
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
					unsigned head = block->m_head04 & 0x7ffffffbU;
					unsigned base = head & 0x7ffffff8U;
					block->m_head04 = head;
					Rva00034C90Block *neighbor = (Rva00034C90Block *)((char *)block + base);
					unsigned nhead = *(unsigned *)((char *)neighbor + 4) & 0x7ffffff8U;
					if ((head & 1) == 0)
					{
						unsigned prevSize = block->m_size00;
						base += prevSize;
						block = (Rva00034C90Block *)((char *)block - prevSize);
						block->m_head04 = base | 1;
						neighbor->m_size00 = base;
						block->m_prev08->m_next0C = block->m_next0C;
						block->m_next0C->m_prev08 = block->m_prev08;
					}
					if ((*(unsigned char *)((char *)neighbor + nhead + 4) & 1) != 0)
					{
						*(unsigned *)((char *)neighbor + 4) &= 0xfffffffeU;
						neighbor->m_size00 = base;
					}
					else
					{
						neighbor->m_prev08->m_next0C = neighbor->m_next0C;
						neighbor->m_next0C->m_prev08 = neighbor->m_prev08;
						base += nhead;
						block->m_head04 = base | 1;
						*(unsigned *)((char *)block + base) = base;
					}
					Rva00034C90Block *cur = m_cur440;
					if (block != cur && neighbor != cur)
					{
						Rva00034C90Block *tail = anchor->m_next0C;
						block->m_prev08 = anchor;
						block->m_next0C = tail;
						anchor->m_next0C = block;
						tail->m_prev08 = block;
					}
					else
					{
						m_cur440 = block;
						block->m_next0C = block;
						block->m_prev08 = block;
						block->m_head04 = base | 1;
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
		rva00033700(0, 0, 1, 0, 0, 0);
	}
}
