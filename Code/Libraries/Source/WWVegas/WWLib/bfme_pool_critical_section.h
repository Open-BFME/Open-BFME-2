// Pool critical section: four-byte ABI from the generated class contract.
// Lock's atomic word at +0 is independently verified at RVA 0x0006577F.
// The guard follows the existing pool-unit views: acquire once and clear the
// same word on normal or exceptional exit. Original retail type names remain
// unknown; BFMEPoolCriticalSection is the established recovery name.
#ifndef CANONICAL_BFMEPOOLCRITICALSECTION_H
#define CANONICAL_BFMEPOOLCRITICALSECTION_H

class BFMEPoolCriticalSection {
public:
    // Retail releases with a store, including the size-optimized pool users.
    volatile unsigned int m_locked;
    void Lock();

    class LockClass {
        BFMEPoolCriticalSection &m_cs;
    public:
        LockClass(BFMEPoolCriticalSection &cs) : m_cs(cs) { m_cs.Lock(); }
        ~LockClass() { m_cs.m_locked = 0; }
    private:
        LockClass &operator=(const LockClass &);
        LockClass(const LockClass &);
    };
};

#endif // CANONICAL_BFMEPOOLCRITICALSECTION_H
