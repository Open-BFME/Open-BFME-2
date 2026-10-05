// ?rva0010F49A@Rva0010F49A@@QAEXXZ
// cl: /O1 /arch:SSE /MD
#include "../../Include/Common/Rva00041004Lock.h"
// Guarded AIL_set_stream_volume_pan(stream, +0x0C, 0.5), retail 0x0010F49A (96B).
// Same guard derivation as the matched 0x0010F38A (+0x38 of the inner's +0x0C
// outer, lock via rowed 0x0010F24F, unlock via rowed 0x0010F26E). Slot 1 of
// the one-slot vftable at 0x00BCFA94; IAT AIL_set_stream_volume_pan at
// 0x00BBAACC, 0.5f literal at 0x00BC26F0. Honest address names.
extern "C" __declspec(dllimport) void __stdcall AIL_set_stream_volume_pan(void *stream, float volume, float pan);

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

struct Rva0010F49AMid
{
    char pad[0x38];
    Rva00041004 lock; // +0x38
};

struct Rva0010F49AInner
{
    char pad0[8]; // +0..+7
    void *m_stream; // +8
    Rva0010F49AMid *m_outer; // +0x0C
};

struct Rva0010F49AGuard
{
    Rva00041004 *m_target; // +0
    unsigned char m_locked; // +4
};

class Rva0010F49A
{
public:
    void rva0010F49A();
private:
    char m_pad0[8]; // +0..+7
    Rva0010F49AInner *m_inner; // +8
    float m_volume0C; // +0x0C
};

// The unlock call is duplicated into both arms of the stream test rather than
// emitted once after it. That keeps MSVC from hoisting the `pop esi` above the
// guard test at /O1; retail schedules the pop after the unlock call, so the
// call has to sit in the same block as the pop's epilogue. Proven on the
// matched siblings 0x0010F4FA and 0x0010F557 in Rva0010F557Finish.cpp.
void Rva0010F49A::rva0010F49A()
{
    Rva00041004 *p;
    Rva0010F49AInner *inner = m_inner;
    if (inner != 0) {
        Rva0010F49AMid *o = inner->m_outer;
        if (o == 0)
            p = 0;
        else
            p = (Rva00041004 *)((char *)o + 0x38);
    } else
        p = 0;
    Rva0010F49AGuard g;
    g.m_target = p;
    g.m_locked = 0;
    ((Rva0010F24F *)&g)->rva0010F24F();
    if (m_inner->m_stream != 0) {
        AIL_set_stream_volume_pan(m_inner->m_stream, m_volume0C, 0.5f);
        if (g.m_locked != 0)
            ((Rva0010F26E *)&g)->rva0010F26E();
    } else if (g.m_locked != 0)
        ((Rva0010F26E *)&g)->rva0010F26E();
}