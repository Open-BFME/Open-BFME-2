// cl: /O1 /arch:SSE /MD
#include "../../Include/Common/Rva00041004Lock.h"
// ?rva0010F557@Rva0010F557@@QAEXXZ @0x0010F557 81B.
// ?rva0010F4FA@Rva0010F4FA@@QAEXXZ @0x0010F4FA 93B.
// Guarded Miles stream operations, each the only slot (slot 1) of its own
// one-slot vftable at 0x00BCFA4C / 54 / 74 / 7C / 84 / 8C / 94:
//
//   0x0010F2E5  87 B  AIL_service_stream(stream, +0x0C == 0)
//   0x0010F42A 112 B  AIL_stream_info data rate scaled by the +0x0C float
//                     into AIL_set_stream_playback_rate
//   0x0010F49A  96 B  AIL_set_stream_volume_pan(+0x0C, 0.5)
//   0x0010F4FA  93 B  AIL_set_stream_reverb_levels(+0x0C, +0x10)
//   0x0010F557  81 B  AIL_set_stream_loop_count(+0x0C)
//   0x0010F5A8 134 B  AIL_stream_ms_position total scaled by the +0x0C
//                     float, kept at least +0x10 ms before the end, into
//                     AIL_set_stream_ms_position
//
// Same guard derivation as the matched siblings 0x0010F33C / 0x0010F38A
// (+0x38 of the inner's +0x0C outer, lock via rowed 0x0010F24F, unlock via
// rowed 0x0010F26E when the guard flag is set). Evidence: the mss32 IAT
// slots 0x00BBAACC, 0x00BBABC0, 0x00BBAB34, 0x00BBABCC, 0x00BBAB30,
// 0x00BBAB2C, 0x00BBAB28, 0x00BBAAC8 and 0x00BBAB24, the rowed lock pair,
// and the 0.5f .rdata literal at 0x00BC26F0. Honest address names: the
// owning command classes are not recovered.
//
// The unlock call is duplicated into both arms of the stream test rather
// than emitted once after it. That keeps MSVC from hoisting the `pop esi`
// above the guard test at /O1; retail schedules the pop after the unlock
// call, so the call must be in the same block as the pop's epilogue.

extern "C" __declspec(dllimport) void __stdcall AIL_set_stream_reverb_levels(void *stream, float dryLevel, float wetLevel);
extern "C" __declspec(dllimport) void __stdcall AIL_set_stream_loop_count(void *stream, int count);

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

struct Rva0010F28DMid
{
    char pad[0x38];
    Rva00041004 lock; // +0x38
};

struct Rva0010F28DInner
{
    char pad0[8]; // +0..+7
    void *m_stream; // +8
    Rva0010F28DMid *m_outer; // +0x0C
};

struct Rva0010F28DGuard
{
    Rva00041004 *m_target; // +0
    unsigned char m_locked; // +4
};

#define RVA0010F28D_LOCK(g) \
    Rva00041004 *p; \
    Rva0010F28DInner *inner = m_inner; \
    if (inner != 0) { \
        Rva0010F28DMid *o = inner->m_outer; \
        if (o == 0) \
            p = 0; \
        else \
            p = (Rva00041004 *)((char *)o + 0x38); \
    } else \
        p = 0; \
    Rva0010F28DGuard g; \
    g.m_target = p; \
    g.m_locked = 0; \
    ((Rva0010F24F *)&g)->rva0010F24F()

class Rva0010F4FA
{
public:
    void rva0010F4FA();
private:
    char m_pad0[8]; // +0..+7
    Rva0010F28DInner *m_inner; // +8
    float m_dry0C; // +0x0C
    float m_wet10; // +0x10
};

void Rva0010F4FA::rva0010F4FA()
{
    RVA0010F28D_LOCK(g);
    if (m_inner->m_stream != 0) {
        AIL_set_stream_reverb_levels(m_inner->m_stream, m_dry0C, m_wet10);
        if (g.m_locked != 0)
            ((Rva0010F26E *)&g)->rva0010F26E();
    } else if (g.m_locked != 0)
        ((Rva0010F26E *)&g)->rva0010F26E();
}

class Rva0010F557
{
public:
    void rva0010F557();
private:
    char m_pad0[8]; // +0..+7
    Rva0010F28DInner *m_inner; // +8
    int m_count0C; // +0x0C
};

void Rva0010F557::rva0010F557()
{
    RVA0010F28D_LOCK(g);
    if (m_inner->m_stream != 0) {
        AIL_set_stream_loop_count(m_inner->m_stream, m_count0C);
        if (g.m_locked != 0)
            ((Rva0010F26E *)&g)->rva0010F26E();
    } else if (g.m_locked != 0)
        ((Rva0010F26E *)&g)->rva0010F26E();
}
