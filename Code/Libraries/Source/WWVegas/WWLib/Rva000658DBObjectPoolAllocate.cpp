// cl: /DNDEBUG /MD /EHsc
// ?rva000658DB@Rva00065964ObjectPool@@QAEPAXXZ @0x000658DB 137B allocate 60B nodes x256
// Object pool allocate sibling of rva00285AC4 @0x00285AC4 and rva00285A3B @0x00285A3B (137B): 60-byte nodes x256 per block (0x3c04 bytes via rowed byte allocator at 0x000307F0). Layout matches rowed FreeObject at 0x00065964 (head +0 block +4 free +8 total +0xC lock +0x10 via BFMEPoolCriticalSection::Lock at 0x0006577F). Callers at 0x00065DD2 and 0x00065D09.
typedef unsigned int uint32;

namespace _STL {
template <class _Tp> class allocator;
template <> class allocator<char> {
public:
	static char *allocate(unsigned int n, const void *hint = 0);
};
}

#include "bfme_pool_critical_section.h"

struct PoolNode60
{
	void *m_next;
	char m_pad[56];
};

class Rva00065964ObjectPool
{
public:
	void *rva000658DB();

private:
	PoolNode60 *m_freeListHead;
	uint32 *m_blockListHead;
	int m_freeObjectCount;
	int m_totalObjectCount;
	BFMEPoolCriticalSection m_lock10;
};
void *Rva00065964ObjectPool::rva000658DB()
{
	BFMEPoolCriticalSection::LockClass lock(m_lock10);

	if (m_freeListHead == 0) {
		uint32 *tmp_block_head = m_blockListHead;
		m_blockListHead = (uint32 *)_STL::allocator<char>::allocate(sizeof(PoolNode60) * 256 + sizeof(uint32 *));
		*(void **)m_blockListHead = tmp_block_head;

		m_freeListHead = (PoolNode60 *)(m_blockListHead + 1);
		for (int i = 0; i < 0x3c00; i += 0x3c) {
			*(void **)((char *)m_freeListHead + i) = (char *)m_freeListHead + i + 0x3c;
		}
		*(void **)((char *)m_freeListHead + 0x3bc4) = 0;

		m_freeObjectCount += 0x100;
		m_totalObjectCount += 0x100;
	}

	void *obj = m_freeListHead;
	m_freeListHead = *(PoolNode60 **)m_freeListHead;
	m_freeObjectCount--;

	return obj;
}
