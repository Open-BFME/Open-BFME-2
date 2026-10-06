// cl: /MD
#include "../../Include/Common/Rva00041004Lock.h"
// ?rva0010F33C@Rva0010F33C@@QAEXXZ @0x0010F33C 78B.
// Guarded AIL_start_stream on the +0x08 inner stream: derives the guard
// target as +0x38 of the +0x0C outer (null-checked pair), locks via rowed
// 0x0010F24F, starts the stream when non-null, unlocks via rowed 0x0010F26E
// when the guard flag is set. Evidence: rowed lock/unlock callees, IAT
// AIL_start_stream at 0x00BBABC4, target layout Rva00041004 with cs at +8
// and bypass at +0x20 from rowed ctor 0x000411C1. Honest address name.

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *section);
extern "C" __declspec(dllimport) void __stdcall AIL_start_stream(void *stream);

class Rva0010F24F
{
public:
    void rva0010F24F();
};

class Rva0010F26E
{
public:
    void rva0010F26E();
};

struct Rva0010F33CMid
{
    char pad[0x38];
    Rva00041004 lock; // +0x38
};

struct Rva0010F33CInner
{
    char pad0[8]; // +0..+7
    void *m_stream; // +8
    Rva0010F33CMid *m_outer; // +0x0C
};

class Rva0010F33C
{
public:
    void rva0010F33C();
private:
    char m_pad0[8]; // +0..+7
    Rva0010F33CInner *m_inner; // +8
};

struct Rva0010F33CGuard
{
    Rva00041004 *m_target; // +0
    unsigned char m_locked; // +4
};

void Rva0010F33C::rva0010F33C()
{
    Rva00041004 *p;
    Rva0010F33CInner *inner = m_inner;
    if (inner != 0) {
        Rva0010F33CMid *o = inner->m_outer;
        if (o == 0)
            p = 0;
        else
            p = (Rva00041004 *)((char *)o + 0x38);
    } else
        p = 0;
    Rva0010F33CGuard g;
    g.m_target = p;
    g.m_locked = 0;
    ((Rva0010F24F *)&g)->rva0010F24F();
    void *s = m_inner->m_stream;
    if (s != 0)
        AIL_start_stream(s);
    if (g.m_locked != 0)
        ((Rva0010F26E *)&g)->rva0010F26E();
}
