// ?rva0010F62E@Rva0010F62E@@QAEXXZ
// cl: /MD
#include "../../Include/Common/Rva00041004Lock.h"
// Retail 0x0010F62E (192 bytes): the only slot of the one-slot vftable at
// 0x00BCFAA0, next to the guarded Miles stream operations of
// SetStreamPositionCommand_execute.cpp (same guard derivation and rowed lock pair
// 0x0010F24F / 0x0010F26E). With a stream: when the +0x0C user value is set
// and the +0x10 counter (read through InterlockedExchangeAdd(p, 0)) is
// non-zero, under the Miles mutex store the inner +0x20 value and the +0x0C
// value as stream user data 1 and 0 and register the rowed end-of-stream
// callback 0x0010EE29, backing both out again if the counter dropped to zero
// meanwhile; with no +0x0C value, unregister the callback and clear user
// data 0. Evidence: the IAT slots 0x00BBA2F8 (kernel32
// InterlockedExchangeAdd), 0x00BBAAC4 / 0x00BBAAC0 (AIL_lock_mutex /
// AIL_unlock_mutex), 0x00BBABBC (AIL_set_stream_user_data) and 0x00BBAB20
// (AIL_register_stream_callback). Honest address names.
//
// The no-stream exit unlocks on its own: written as one if around the whole
// body, cl omits the frame pointer and reallocates every register; the
// early return gives retail's ebp frame and block order.

extern "C" __declspec(dllimport) long __stdcall InterlockedExchangeAdd(long volatile *addend, long value);
extern "C" __declspec(dllimport) void __stdcall AIL_lock_mutex(void);
extern "C" __declspec(dllimport) void __stdcall AIL_unlock_mutex(void);
extern "C" __declspec(dllimport) void __stdcall AIL_set_stream_user_data(void *stream, unsigned int index, int value);
typedef void (__stdcall *Rva0010F62EStreamCallback)(void *stream);
extern "C" __declspec(dllimport) Rva0010F62EStreamCallback __stdcall AIL_register_stream_callback(void *stream, Rva0010F62EStreamCallback callback);

void __stdcall rva0010EE29(void *stream);

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
    char pad10[0x20 - 0x10];
    int m_userData20; // +0x20
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

#define RVA0010F28D_UNLOCK(g) \
    if (g.m_locked != 0) \
        ((Rva0010F26E *)&g)->rva0010F26E()

class Rva0010F62E
{
public:
    void rva0010F62E();
private:
    char m_pad0[8]; // +0..+7
    Rva0010F28DInner *m_inner; // +8
    int m_userData0C; // +0x0C
    long volatile *m_counter10; // +0x10
};

void Rva0010F62E::rva0010F62E()
{
    RVA0010F28D_LOCK(g);
    Rva0010F28DInner *in = m_inner;
    void *s = in->m_stream;
    if (s == 0) {
        RVA0010F28D_UNLOCK(g);
        return;
    }
    if (m_userData0C != 0) {
        if (InterlockedExchangeAdd(m_counter10, 0) != 0) {
            AIL_lock_mutex();
            AIL_set_stream_user_data(s, 1, in->m_userData20);
            AIL_set_stream_user_data(s, 0, m_userData0C);
            AIL_register_stream_callback(s, rva0010EE29);
            if (InterlockedExchangeAdd(m_counter10, 0) == 0) {
                AIL_register_stream_callback(s, 0);
                AIL_set_stream_user_data(s, 0, 0);
            }
            AIL_unlock_mutex();
        }
    } else {
        AIL_register_stream_callback(s, 0);
        AIL_set_stream_user_data(s, 0, 0);
    }
    RVA0010F28D_UNLOCK(g);
}
