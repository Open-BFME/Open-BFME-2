// cl: /DNDEBUG /MD /EHsc
//
// ?rva00285AC4@Rva00065964ObjectPool@@QAEPAXXZ @0x00285AC4 (137B).
// Object pool allocate sibling of rva00285A3B @0x00285A3B (137B): 8-byte
// nodes x512 per block (0x1004 bytes via the rowed byte allocator at
// 0x000307F0). Layout matches the rowed FreeObject at 0x00065964 (head +0
// block +4 free +8 total +0xC lock +0x10 via BFMEPoolCriticalSection::Lock
// at 0x0006577F). Callers at 0x002863E6 and 0x00286131.
typedef unsigned int uint32;

namespace _STL {
template <class _Tp> class allocator;
template <> class allocator<char> {
public:
	static char *allocate(unsigned int n, const void *hint = 0);
};
}

#include "bfme_pool_critical_section.h"

struct PoolNode8
{
	void *m_next;
	char m_pad[4];
};

class Rva00065964ObjectPool
{
public:
	void *rva00285AC4();

private:
	PoolNode8 *m_freeListHead;
	uint32 *m_blockListHead;
	int m_freeObjectCount;
	int m_totalObjectCount;
	BFMEPoolCriticalSection m_lock10;
};

void *Rva00065964ObjectPool::rva00285AC4()
{
	BFMEPoolCriticalSection::LockClass lock(m_lock10);

	if (m_freeListHead == 0) {
		uint32 *tmp_block_head = m_blockListHead;
		m_blockListHead = (uint32 *)_STL::allocator<char>::allocate(sizeof(PoolNode8) * 512 + sizeof(uint32 *));
		*(void **)m_blockListHead = tmp_block_head;

		m_freeListHead = (PoolNode8 *)(m_blockListHead + 1);
		for (int i = 0; i < 0x1000; i += 8) {
			*(void **)((char *)m_freeListHead + i) = (char *)m_freeListHead + i + 8;
		}
		*(void **)((char *)m_freeListHead + 0xFF8) = 0;

		m_freeObjectCount += 0x200;
		m_totalObjectCount += 0x200;
	}

	void *obj = m_freeListHead;
	m_freeListHead = *(PoolNode8 **)m_freeListHead;
	m_freeObjectCount--;

	return obj;
}
