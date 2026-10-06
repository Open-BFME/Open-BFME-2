// cl: /MD
#include "../../Include/Common/Rva00041004Lock.h"
// ?rva0010F24F@Rva0010F24F@@QAEXXZ @0x0010F24F 31B.
// ?rva0010F26E@Rva0010F26E@@QAEXXZ @0x0010F26E 31B.
// Conditional critical-section guard lock/unlock pair: if the +0x00 target
// is non-null and its +0x20 bypass flag is clear, enter/leave its +0x08
// section, then set/clear the +0x04 locked flag. Evidence: 12 callers each
// (0x0010F1D0 0x0010F28D 0x0010F2E5 0x0010F33C 0x0010F38A 0x0010F3DA
// 0x0010F42A 0x0010F49A 0x0010F4FA 0x0010F557 0x0010F5A8 0x0010F62E and the
// unlock twins); IAT EnterCriticalSection at 0x00BBA200 and
// LeaveCriticalSection at 0x00BBA204; target layout with vtable at +0 and
// bypass byte at +0x20 from rowed Rva00041004 ctor 0x000411C1; shape follows
// StringBaseLockGuardDtor. Honest address-derived names: identity unproven
// beyond the guard shape.

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *section);

class Rva0010F24F
{
public:
    void rva0010F24F();
private:
    Rva00041004 *m_target; // +0
    unsigned char m_locked; // +4
};

void Rva0010F24F::rva0010F24F()
{
    if (m_target != 0 && m_target->m_flag == 0)
        EnterCriticalSection(&m_target->m_cs);
    m_locked = 1;
}

class Rva0010F26E
{
public:
    void rva0010F26E();
private:
    Rva00041004 *m_target; // +0
    unsigned char m_locked; // +4
};

void Rva0010F26E::rva0010F26E()
{
    if (m_target != 0 && m_target->m_flag == 0)
        LeaveCriticalSection(&m_target->m_cs);
    m_locked = 0;
}
