// cl: /EHsc /DNDEBUG /DWIN32 /MD
// ?rva006C3660@Rva006C1F60@@QAEXPAX@Z @ 0x006C3660 (370B), thiscall, ret 4.
// The debug allocator's release of a user pointer, in the lock-guarded
// Rva006C1F60 family (same +0x4E4 lock guard and SEH handler 0x00BA7D58 as
// the setter 0x006C3840 in Rva006C3840Cluster.cpp). Reached only through a
// vtable (no direct call or code reference in retail).
//
// Target facts: a null pointer does nothing. Under the lock, a pointer the
// rowed 0x006C1DC0 accepts first has the rowed 0x006C33D0 run with the
// +0x540/+0x544 pair, then its 8-byte-headed block's guard fill checked
// (rowed VerifyGuardFill 0x006C3020). With +0x540 zero, or a usable size
// (rowed 0x006C1D10) under 8, the block goes to 0x006C26F0 and the pointer
// to 0x00033150 (both pinned). Otherwise the bytes past the first 8 are
// filled with the +0x509 fill byte, mode 3 stamps the first word with the
// rowed 0x006C1790, the block is linked at the tail of the +0x548 list
// (next +8, previous +0xC), the +0x558 count rises and the +0x55C byte
// total grows by the block size (0x00032A20). Both paths end in the pinned
// 0x006C1D60 (pointer, true).
// Structural inference: the free semantics and field roles; the class and
// member names are address-derived.
#include <string.h>

struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

class Rva00030DD0Guard
{
public:
	Rva00030DD0Guard(Rva00030DD0Lock *lock) : m_lock(lock)
	{
		if (m_lock != 0)
			Rva00030DD0AddRef(m_lock);
	}
	~Rva00030DD0Guard()
	{
		if (m_lock != 0)
			Rva00030DF0Release(m_lock);
	}

private:
	Rva00030DD0Lock *m_lock;
};

namespace EA { namespace Allocator {
class GeneralAllocator
{
public:
	// memory_pool.cpp owns the native 0x00033150 free engine under this ABI.
	void rva00033150(const void *block);

	unsigned int rva006C1D10(const void *p);					// 0x006C1D10
	unsigned int rva00032A20(const void *p);					// 0x00032A20
};
} }

class GeneralAllocatorDebug
{
public:
	bool VerifyGuardFill(void *block, int a, unsigned char b);	// 0x006C3020
	void rva006C26F0(void *block, bool allocation);						// 0x006C26F0
};


class Rva006C1D60
{
public:
	bool rva006C1D60(unsigned int p, bool a);					// 0x006C1D60
};

unsigned int Rva006C1790();									// 0x006C1790

struct Rva006C3660Block
{
	unsigned char m_header[8];
	Rva006C3660Block *m_next;									// +0x08
	Rva006C3660Block *m_prev;									// +0x0C
};

class Rva006C1F60
{
public:
	void rva006C3660(void *p);
	int rva006C1DC0(unsigned int p);							// 0x006C1DC0
	void rva006C33D0(int a, int b);							// 0x006C33D0

private:
	unsigned char m_pad0[0x4E4];
	Rva00030DD0Lock *m_lock;									// +0x4E4
	unsigned char m_pad4E8[0x509 - 0x4E8];
	unsigned char m_fillByte;									// +0x509
	unsigned char m_pad50A[0x540 - 0x50A];
	int m_540;													// +0x540
	int m_544;													// +0x544
	Rva006C3660Block m_list;									// +0x548
	int m_count;												// +0x558
	unsigned int m_bytes;										// +0x55C
};

void Rva006C1F60::rva006C3660(void *p)
{
	if (p)
	{
		Rva00030DD0Guard guard(m_lock);
		if ((char)rva006C1DC0((unsigned int)p))
		{
			rva006C33D0(m_540, m_544);
			Rva006C3660Block *block = (Rva006C3660Block *)((char *)p - 8);
			((GeneralAllocatorDebug *)this)->VerifyGuardFill(block, 0, 0);
			if (m_540 == 0)
			{
				((GeneralAllocatorDebug *)this)->rva006C26F0(block, false);
				reinterpret_cast<EA::Allocator::GeneralAllocator *>(this)->rva00033150(p);
			}
			else
			{
				unsigned int size = ((EA::Allocator::GeneralAllocator *)this)->rva006C1D10(p);
				if (size < 8)
				{
					((GeneralAllocatorDebug *)this)->rva006C26F0(block, false);
					reinterpret_cast<EA::Allocator::GeneralAllocator *>(this)->rva00033150(p);
				}
				else
				{
					memset((char *)p + 8, m_fillByte, size - 8);
					if (m_540 == 3)
						*(unsigned int *)p = Rva006C1790();
					Rva006C3660Block *tail = m_list.m_prev;
					Rva006C3660Block *head = &m_list;
					block->m_next = head;
					block->m_prev = tail;
					head->m_prev = block;
					tail->m_next = block;
					++m_count;
					m_bytes += ((EA::Allocator::GeneralAllocator *)this)->rva00032A20(p);
				}
			}
			((Rva006C1D60 *)this)->rva006C1D60((unsigned int)p, true);
		}
	}
}
