// cl: /DNDEBUG /MD /EHsc
//
// ?rva002635C2@Rva00065964ObjectPool@@QAEPAXXZ @0x002635C2 (137B).
// Path-node pool allocate: 36-byte nodes (PathNode) x128 per block
// (0x1204 bytes via the rowed byte allocator at 0x000307F0). Layout matches
// the rowed FreeObject at 0x00065964 (head +0 block +4 free +8 total +0xC
// lock +0x10 via BFMEPoolCriticalSection::Lock at 0x0006577F). Callers at
// 0x0026559F 0x0026561A 0x003649E9 and 0x003663DE load the path pool global
// at 0x00E01E94 into ecx then construct PathNode (0x0026212A) on the return.

typedef unsigned int uint32;

namespace _STL {
template <class _Tp> class allocator;
template <> class allocator<char> {
public:
	static char *allocate(unsigned int n, const void *hint = 0);
};
}

#include "bfme_pool_critical_section.h"

struct PoolNode36
{
	void *m_next;
	char m_pad[32];
};

class Rva00065964ObjectPool
{
public:
	void *rva002635C2();

private:
	PoolNode36 *m_freeListHead;
	uint32 *m_blockListHead;
	int m_freeObjectCount;
	int m_totalObjectCount;
	BFMEPoolCriticalSection m_lock10;
};

void *Rva00065964ObjectPool::rva002635C2()
{
	BFMEPoolCriticalSection::LockClass lock(m_lock10);

	if (m_freeListHead == 0) {
		uint32 *tmp_block_head = m_blockListHead;
		m_blockListHead = (uint32 *)_STL::allocator<char>::allocate(sizeof(PoolNode36) * 128 + sizeof(uint32 *));
		*(void **)m_blockListHead = tmp_block_head;

		m_freeListHead = (PoolNode36 *)(m_blockListHead + 1);
		for (int i = 0; i < 128; ++i) {
			*(void **)(&m_freeListHead[i]) = &m_freeListHead[i + 1];
		}
		*(void **)(&m_freeListHead[127]) = 0;

		m_freeObjectCount += 128;
		m_totalObjectCount += 128;
	}

	void *obj = m_freeListHead;
	m_freeListHead = *(PoolNode36 **)m_freeListHead;
	m_freeObjectCount--;

	return obj;
}
