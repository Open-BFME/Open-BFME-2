// NodeAllocMutex: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_NODEALLOCMUTEX_H
#define CANONICAL_NODEALLOCMUTEX_H

class NodeAllocMutex
{
public:
	void _M_acquire_lock();
	void _M_release_lock();
};

#endif // CANONICAL_NODEALLOCMUTEX_H
