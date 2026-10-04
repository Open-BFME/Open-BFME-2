// cl: /O1 /MD /DNDEBUG /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// Retail [0x00550995..0x005509AF) clears the receiver's pointer at +0 before
// calling the independently recovered CriticalSectionClass::LockClass
// destructor at 0x00613B80 and scalar operator delete at 0x0002FD60.
// The callee establishes the lock type; the enclosing native owner's name
// and complete layout remain unknown. Reuse the donor's existing mutex.h
// view at BFME 1 revision 10af19f44a89ab7ecc23195bb9a842ceafbc02c9.
#include "mutex.h"

class Rva00550995Owner
{
public:
    void clearLock();
    void rva005509AF(CriticalSectionClass::LockClass *newLock);
private:
    CriticalSectionClass::LockClass *m_lock;
};

void Rva00550995Owner::clearLock()
{
    CriticalSectionClass::LockClass *lock = m_lock;
    m_lock = 0;
    delete lock;
}

void Rva00550995Owner::rva005509AF(CriticalSectionClass::LockClass *newLock)
{
    CriticalSectionClass::LockClass *old = m_lock;
    if (newLock == old)
        return;
    m_lock = newLock;
    if (!old)
        return;
    delete old;
}
