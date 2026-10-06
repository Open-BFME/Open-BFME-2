// cl: /MD
#include "../../Include/Common/Rva00041004Lock.h"
// ?rva0010F38A@Rva0010F38A@@QAEXXZ @0x0010F38A 80B.
// ?rva0010F3DA@Rva0010F3DA@@QAEXXZ @0x0010F3DA 80B.
// Guarded AIL_pause_stream pair (resume/pause): same guard derivation as
// 0x0010F33C (+0x38 of the +0x0C outer), lock via rowed 0x0010F24F, pause
// the +0x08 inner stream with flag 1 (0x0010F38A) or 0 (0x0010F3DA),
// unlock via rowed 0x0010F26E. Evidence: rowed lock pair, IAT
// AIL_pause_stream at 0x00BBABC8, Rva00041004 layout from rowed ctor
// 0x000411C1. Honest address names.

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION *section);
extern "C" __declspec(dllimport) void __stdcall AIL_pause_stream(void *stream, int flag);

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

struct Rva0010F38AMid
{
    char pad[0x38];
    Rva00041004 lock; // +0x38
};

struct Rva0010F38AInner
{
    char pad0[8]; // +0..+7
    void *m_stream; // +8
    Rva0010F38AMid *m_outer; // +0x0C
};

struct Rva0010F38AGuard
{
    Rva00041004 *m_target; // +0
    unsigned char m_locked; // +4
};

class Rva0010F38A
{
public:
    void rva0010F38A();
private:
    char m_pad0[8]; // +0..+7
    Rva0010F38AInner *m_inner; // +8
};

class Rva0010F3DA
{
public:
    void rva0010F3DA();
private:
    char m_pad0[8]; // +0..+7
    Rva0010F38AInner *m_inner; // +8
};

void Rva0010F38A::rva0010F38A()
{
    Rva00041004 *p;
    Rva0010F38AInner *inner = m_inner;
    if (inner != 0) {
        Rva0010F38AMid *o = inner->m_outer;
        if (o == 0)
            p = 0;
        else
            p = (Rva00041004 *)((char *)o + 0x38);
    } else
        p = 0;
    Rva0010F38AGuard g;
    g.m_target = p;
    g.m_locked = 0;
    ((Rva0010F24F *)&g)->rva0010F24F();
    void *s = m_inner->m_stream;
    if (s != 0)
        AIL_pause_stream(s, 1);
    if (g.m_locked != 0)
        ((Rva0010F26E *)&g)->rva0010F26E();
}

void Rva0010F3DA::rva0010F3DA()
{
    Rva00041004 *p;
    Rva0010F38AInner *inner = m_inner;
    if (inner != 0) {
        Rva0010F38AMid *o = inner->m_outer;
        if (o == 0)
            p = 0;
        else
            p = (Rva00041004 *)((char *)o + 0x38);
    } else
        p = 0;
    Rva0010F38AGuard g;
    g.m_target = p;
    g.m_locked = 0;
    ((Rva0010F24F *)&g)->rva0010F24F();
    void *s = m_inner->m_stream;
    if (s != 0)
        AIL_pause_stream(s, 0);
    if (g.m_locked != 0)
        ((Rva0010F26E *)&g)->rva0010F26E();
}
