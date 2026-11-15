// NodeAllocMutex: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin.
// Target facts (BFME2 1.06): _STLP_mutex_base::_M_initialize at RVA 0x00013260
// writes a dword at this+0. A call site at RVA 0x00024842 names the false-thread
// lock (VA 0x00DDF570, RVA 0x009DF570), but is skipped by a constant-false guard.
// The call at RVA 0x00024867 names the true-thread lock
// (VA 0x00DDF574, RVA 0x009DF574). Both data-ledger entries specify 4 bytes.
// The former empty class allocated only 1 byte; reserve the full lock word.
#ifndef CANONICAL_NODEALLOCMUTEX_H
#define CANONICAL_NODEALLOCMUTEX_H

class NodeAllocMutex
{
public:
	void _M_acquire_lock();
	void _M_release_lock();
	volatile long _M_lock; // +0x0, STLport's _STLP_mutex_base lock word
};

typedef char NodeAllocMutexSize[sizeof(NodeAllocMutex) == 4 ? 1 : -1];

#endif // CANONICAL_NODEALLOCMUTEX_H
