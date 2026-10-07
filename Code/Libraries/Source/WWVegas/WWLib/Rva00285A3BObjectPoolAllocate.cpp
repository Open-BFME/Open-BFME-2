// cl: /DNDEBUG /MD /EHsc
//
// ?rva00285A3B@Rva00065964ObjectPool@@QAEPAXXZ @0x00285A3B (137B).
// Object pool allocate sibling of rva002635C2 @0x002635C2 (137B): 16-byte
// nodes x512 per block (0x2004 bytes via the rowed byte allocator at
// 0x000307F0). Layout matches the rowed FreeObject at 0x00065964 (head +0
// block +4 free +8 total +0xC lock +0x10 via BFMEPoolCriticalSection::Lock
// at 0x0006577F). Callers at 0x00286DAB and 0x00286111.
typedef unsigned int uint32;

namespace _STL {
template <class _Tp> class allocator;
template <> class allocator<char> {
public:
	static char *allocate(unsigned int n, const void *hint = 0);
};
}

#include "bfme_pool_critical_section.h"

struct PoolNode16
{
	void *m_next;
	char m_pad[12];
};

class Rva00065964ObjectPool
{
public:
	void *rva00285A3B();

private:
	PoolNode16 *m_freeListHead;
	uint32 *m_blockListHead;
	int m_freeObjectCount;
	int m_totalObjectCount;
	BFMEPoolCriticalSection m_lock10;
};

void *Rva00065964ObjectPool::rva00285A3B()
{
	BFMEPoolCriticalSection::LockClass lock(m_lock10);

	if (m_freeListHead == 0) {
		uint32 *tmp_block_head = m_blockListHead;
		m_blockListHead = (uint32 *)_STL::allocator<char>::allocate(sizeof(PoolNode16) * 512 + sizeof(uint32 *));
		*(void **)m_blockListHead = tmp_block_head;

		m_freeListHead = (PoolNode16 *)(m_blockListHead + 1);
		for (int i = 0; i < 0x2000; i += 0x10) {
			*(void **)((char *)m_freeListHead + i) = (char *)m_freeListHead + i + 0x10;
		}
		*(void **)((char *)m_freeListHead + 0x1FF0) = 0;

		m_freeObjectCount += 0x200;
		m_totalObjectCount += 0x200;
	}

	void *obj = m_freeListHead;
	m_freeListHead = *(PoolNode16 **)m_freeListHead;
	m_freeObjectCount--;

	return obj;
}
