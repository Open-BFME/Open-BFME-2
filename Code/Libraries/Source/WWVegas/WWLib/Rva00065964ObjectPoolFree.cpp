// cl: /O1 /DNDEBUG /MD

// ?FreeObject@Rva00065964ObjectPool@@QAEXPAX@Z, retail 0x00065964, 38 bytes.
// Pooled-object free: locks the pool's critical section, pushes the object
// onto the free list, bumps the free count and clears the lock word. Layout
// matches ObjectPoolClass (free-list head at +0, free count at +8,
// lock at +0x10) but the lock flavor is BFMEPoolCriticalSection, so the
// class keeps an address-derived name.

class BFMEPoolCriticalSection
{
public:
	void Lock();

	volatile unsigned int m_locked;
};

struct Rva00065964ObjectPool
{
	void *m_freeListHead;
	void *m_blockListHead;
	int m_freeObjectCount;
	int m_pad0C;
	BFMEPoolCriticalSection m_lock10;

	void FreeObject(void *obj);
};

// ?FreeObject@Rva00065964ObjectPool@@QAEXPAX@Z
void Rva00065964ObjectPool::FreeObject(void *obj)
{
	BFMEPoolCriticalSection *lock = &m_lock10;
	lock->Lock();
	*(void **)obj = m_freeListHead;
	m_freeObjectCount++;
	m_freeListHead = obj;
	lock->m_locked = 0;
}
