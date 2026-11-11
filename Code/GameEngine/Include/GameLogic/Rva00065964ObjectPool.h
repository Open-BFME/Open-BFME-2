// Rva00065964ObjectPool: canonical declarations for the members 13 units call through private views of it;
// each call resolves to the unit's ledger row or pin.
// Retail's pools are 0x14 bytes (the contract's size; 0x009FEC94, 0x009FECA8, 0x00A01E94): the allocators read
// the free list at +0, the block list at +4, the counts at +8 and +0xC, and lock +0x10. No constructor: retail's
// storage is zero-filled and only the atexit destructor thunks touch it outside the users. The layout is here
// for the units that define a pool's storage.
#ifndef CANONICAL_RVA00065964OBJECTPOOL_H
#define CANONICAL_RVA00065964OBJECTPOOL_H

#include "../../../Libraries/Source/WWVegas/WWLib/bfme_pool_critical_section.h"

class Rva00065964ObjectPool
{
public:
	void FreeObject(void *obj);
	void *rva000658DB();
	void *rva00285A3B();
	void *rva00285AC4();

	void *m_freeListHead;
	void *m_blockListHead;
	int m_freeObjectCount;
	int m_totalObjectCount;
	BFMEPoolCriticalSection m_lock10;
};
typedef char Rva00065964ObjectPoolSize20[(sizeof(Rva00065964ObjectPool) == 0x14) ? 1 : -1];

#endif // CANONICAL_RVA00065964OBJECTPOOL_H
