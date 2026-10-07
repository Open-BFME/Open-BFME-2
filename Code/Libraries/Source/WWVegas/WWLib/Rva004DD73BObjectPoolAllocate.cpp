// cl: /DNDEBUG /MD /EHsc
//
// ?rva004DD73B@Rva004DD73B@@QAEPAXXZ @ 0x004DD73B (137B).
// Pool allocate: 16-byte nodes x1024 per block (0x4004 bytes via the rowed
// byte allocator at 0x000307F0). Layout matches the rowed precedent
// Rva00065964ObjectPool::rva002635C2 at 0x002635C2 (137B, same shape:
// head +0 block +4 free +8 total +0xC lock +0x10 via
// BFMEPoolCriticalSection::Lock at 0x0006577F). Callers at 0x004DDA52 and
// 0x004DD88B (both unclaimed). Prev/next dtors both /O1.

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

class Rva004DD73B
{
public:
	void *rva004DD73B();

private:
	PoolNode16 *m_freeListHead;
	uint32 *m_blockListHead;
	int m_freeObjectCount;
	int m_totalObjectCount;
	BFMEPoolCriticalSection m_lock10;
};

void *Rva004DD73B::rva004DD73B()
{
	BFMEPoolCriticalSection::LockClass lock(m_lock10);

	if (m_freeListHead == 0) {
		uint32 *tmp_block_head = m_blockListHead;
		m_blockListHead = (uint32 *)_STL::allocator<char>::allocate(sizeof(PoolNode16) * 1024 + sizeof(uint32 *));
		*(void **)m_blockListHead = tmp_block_head;

		m_freeListHead = (PoolNode16 *)(m_blockListHead + 1);
		for (int i = 0; i < 1024; ++i) {
			*(void **)(&m_freeListHead[i]) = &m_freeListHead[i + 1];
		}
		*(void **)(&m_freeListHead[1023]) = 0;

		m_freeObjectCount += 1024;
		m_totalObjectCount += 1024;
	}

	void *obj = m_freeListHead;
	m_freeListHead = *(PoolNode16 **)m_freeListHead;
	m_freeObjectCount--;

	return obj;
}
