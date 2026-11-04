// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva002A4A68@InGameUI@@QAEXXZ, retail 0x002A4A68..0x002A4BFC (404 bytes, RET):
// the InGameUI per-frame update (floating-text style; purpose inferred) that
// W3DDisplay::rva0004A462 calls on
// TheInGameUI (pinned name). Shape from WorldBuilder 0xDBF4E0: a debug-only
// call on the +0x8D4 holder (retail folds it onto the empty RET 0x000B3FD0),
// then a walk of the STLport list at +0x8D0. Unless the game is paused, an
// entry whose end frame has passed, or that is flagged (bit 2) while its
// Anim2D status has 0x4 set (ZH: ANIM_2D_STATUS_COMPLETE), is deleted with
// its Anim2D and erased.
// Otherwise its position integrates its velocity, the velocity decays by the
// +0x1C factor, a fading entry (bit 0) sets the animation alpha from the
// remaining frames over the fade length 0x009FEE08, the animation size comes
// from the GlobalData random variable (+0.5f, rounded) or the entry's own
// size, and the animation is drawn at the entry position with the GlobalData
// opacity dword. An empty list resets +0x908/+0x90C to -1.
// The +0x8D4 call is spelled through a visible non-inline barrier body: retail
// keeps the receiver base in EDX across it (cross-TU knowledge that the
// callee preserves it) yet keeps the call; an empty body is elided by cl.
#include <list>
// Retail keeps one copy each of _List_iterator_base::operator!= (0x006CFE40)
// and __malloc_alloc<0>::deallocate; this unit's /O1 /G7 copies differ. An
// exact-match iterator overload and a dllimport+forceinline deallocate keep
// both inline without emitting either.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits> &a, const _List_iterator<T, RightTraits> &b)
{ return a._M_node != b._M_node; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}
#include "../Common/GameLogicObjectLookupView.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva002A1B1D
{
public:
	void rva000B3FD0();
};
__declspec(noinline) void Rva002A1B1D::rva000B3FD0()
{
	_ReadWriteBarrier();
}

class InGameUI;

extern GameLogic *TheGameLogic;

class ClientFrameSubsystem {
public:
    virtual int _v00();
    virtual int _v01();
    virtual int _v02();
    virtual int _v03();
    virtual int _v04();
    virtual int _v05();
    virtual int _v06();
    virtual int _v07();
    virtual int _v08();
    virtual int _v09();
    virtual int _v10();
    virtual int _v11();
    virtual int _v12();
    virtual int _v13();
    virtual int _v14();
    virtual int _v15();
    virtual int _v16();
    virtual int _v17();
    virtual int _v18();
    virtual int _v19();
    virtual int _v20();
    virtual int _v21();
    virtual int _v22();
    virtual int _v23();
    virtual int _v24();
    virtual int _v25();
    virtual int _v26();
    virtual int _v27();
    virtual int _v28();
    virtual int _v29();
    virtual int _v30();
    virtual int getFrame();
};
class GameClient;
extern GameClient *TheGameClient;

class GlobalData;
extern GlobalData *TheWritableGlobalData;
extern unsigned int g_00DFEE08;

#include "../../Include/GameClient/GameClientRandomVariable.h"

#include "../../Include/Common/GlobalData.h"

class Rva002D7127 {
public:
    virtual ~Rva002D7127();
    void rva002D6F80(float a, float b, int c);
    char _pad0[0x10 - 4];
    unsigned char m_flag10;
    char _pad1[0x1c - 0x10 - 1];
    float m_1c;
    char _pad2[0x2c - 0x1c - 4];
    int m_2c;
    int m_30;
};

struct Payload {
    Rva002D7127 *m_obj;
    float m_4;
    float m_8;
    int m_c;
    unsigned char m_10;
    char _p[3];
    float m_14;
    float m_18;
    float m_1c;
    int m_20;
};

#include "../../Include/GameClient/InGameUI.h"

void InGameUI::rva002A4A68()
{
    ((Rva002A1B1D *)((char *)this + 0x8d4))->rva000B3FD0();
    _STL::list<int> &lst = *(_STL::list<int> *)((char *)this + 0x8d0);
    _STL::list<int>::iterator it = lst.begin();
    while (it != lst.end()) {
        Payload *payload = (Payload *)*it;
        if (!TheGameLogic->isGamePaused()) {
            unsigned frame = ((ClientFrameSubsystem *)TheGameClient)->getFrame();
            if (frame >= (unsigned)payload->m_c || ((payload->m_10 & 2) && (payload->m_obj->m_flag10 & 4))) {
                ::delete payload->m_obj;
                delete payload;
                it = (payload ? lst.erase(it) : lst.erase(it));
                continue;
            }
        }
        payload->m_4 += payload->m_14;
        payload->m_14 *= payload->m_1c;
        payload->m_8 += payload->m_18;
        payload->m_18 *= payload->m_1c;
        if (payload->m_10 & 1) {
            unsigned remaining = payload->m_c - ((ClientFrameSubsystem *)TheGameClient)->getFrame();
            if (remaining < g_00DFEE08) {
                payload->m_obj->m_1c = (float)remaining / (float)g_00DFEE08;
            }
        }
        int v;
        if (TheWritableGlobalData->m_particleCursorPerFrameSize)
            v = (int)(TheWritableGlobalData->m_particleCursorParticleSize.getValue() + 0.5f);
        else
            v = payload->m_20;
        Rva002D7127 *o2 = payload->m_obj;
        o2->m_2c = v;
        o2->m_30 = v;
        payload->m_obj->rva002D6F80(payload->m_4, payload->m_8, TheWritableGlobalData->m_particleCursorAlpha);
        ++it;
    }
    if (lst.size() == 0) {
        *(int *)((char *)this + 0x908) = -1;
        *(int *)((char *)this + 0x90c) = -1;
    }
}
