// cl: /EHs
#include "../../../../GameEngine/Include/Common/Rva00041004Lock.h"
// ??1Rva000358B0@@QAE@XZ @0x000358B0 35B
// String lock guard destructor: if the +4 locked flag is set, leaves the
// Rva00041004 critical section at +8 unless its +0x20 bypass flag is set,
// then clears the locked flag. Evidence: 7 unwind-funclet jmp callers
// (Unwind@00b5cce0 00b6487b 00b6592d 00b6593f 00b665f8 00b6660a 00ba7ffe),
// IAT LeaveCriticalSection at 0x00BBA204, lock layout with vtable at +0 and
// bypass byte at +0x20 from rowed ctor 0x000411C1. Honest address-derived
// name: identity unproven beyond the guard shape and unwind role.

extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *section);

class Rva000358B0
{
public:
    ~Rva000358B0();
private:
    Rva00041004 *m_lock;
    bool m_locked;
};

Rva000358B0::~Rva000358B0()
{
    if (m_locked) {
        if (!m_lock->m_flag)
            LeaveCriticalSection(&m_lock->m_cs);
        m_locked = false;
    }
}
