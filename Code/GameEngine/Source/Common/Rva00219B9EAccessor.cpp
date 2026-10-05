// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00219B9E@Rva00219B9E@@QAEPAXI@Z @0x00219B9E 44B
// Bounds-checked accessor for the 216-byte (0xD8) element vector at +0x14/+0x18.
// Returns null when index >= (finish-start)/216 via signed idiv (cdq), else
// start+index*216. Proven by 12 direct callers needing this exact shape:
// 0x00219BE1/0x00219C1F return dword counts from the element's +0x3c/+0x30
// vectors, 0x00219C00/0x00219C3E forward two indices into those inner vectors,
// 0x00219C5D adds 0x68 to the returned element. Outer chain 0x00219E74/
// 0x00219E9F/0x00219F00 indexes a 32-byte outer vector at +0x14C/+0x150 then
// calls here; top callers at 0x00406E53/0x00406E65/0x00406E8F read the global
// at 0x009FE344. Landing unblocks 24 functions (14 fully ready). No donor;
// recipe follows ObjectFilter signed-idiv precedent with /O1 keeping idiv.
// Honest-address name: owner unknown so Rva00219B9E class, void* return.
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")
extern int g_00DFE368;
extern int g_00DFE364;
extern int g_00DFE3E4;
extern int g_00DFE3E0;
struct IntVec { int *m_start; int *m_finish; int *m_end; };
struct Elem216 {
    char m_00[0x0C];
    AsciiString m_0C;
    int m_10;
    int m_14;
    int m_18;
    int m_1C;
    AsciiString m_20;
    char m_24[0x30 - 0x24];
    IntVec m_30;
    IntVec m_3C;
    char m_48[0x64 - 0x48];
    int m_64;
    char m_68[0xD8 - 0x68];
};
struct Vec216 {
    Elem216 *m_start;
    Elem216 *m_finish;
    Elem216 *m_end;
};
struct OuterElem32 { char m_00[32]; };
struct Vec32 {
    OuterElem32 *m_start;
    OuterElem32 *m_finish;
    OuterElem32 *m_end;
};
struct Elem16 { char m_data[16]; };
struct Vec16 {
    Elem16 *m_start;
    Elem16 *m_finish;
    Elem16 *m_end;
};
static __forceinline unsigned VecSize(const Vec216 *v) { return v->m_finish - v->m_start; }
static __forceinline Elem216 &VecAt(Vec216 *v, unsigned i) { return v->m_start[i]; }
static __forceinline unsigned Vec32Size(const Vec32 *v) { return v->m_finish - v->m_start; }
static __forceinline OuterElem32 &Vec32At(Vec32 *v, unsigned i) { return v->m_start[i]; }
struct IdxPair {
    char m_00[0x0C];
    unsigned m_o;
    unsigned m_i;
};
class Rva00219B62 {
    char m_pad[0x30];
    IntVec m_vec;
public:
    int rva00219B62(unsigned int index);
};
class Rva00219B80 {
    char m_pad[0x3C];
    IntVec m_vec;
public:
    int rva00219B80(unsigned int index);
};
class Rva00219B9E {
    char m_pad[0x14];
    Vec216 m_vec;
    char m_pad2[0x14C - 0x20];
    Vec32 m_outer;
    char m_pad3[0x15C - 0x158];
    Vec16 m_15c;
public:
    void *rva00219B9E(unsigned int index);
    int rva00219CDF(unsigned int index);
    int rva00219CF6(unsigned int index);
    int rva00219D0D(unsigned int index);
    int rva00219D24(unsigned int index);
    int rva00219C93(unsigned int index);
    void *rva00219CAB(unsigned int index);
    void *rva00219CC5(unsigned int index);
    int rva00219BE1(unsigned int index);
    int rva00219C1F(unsigned int index);
    void *rva0021ADF8(unsigned int index);
    void *rva0021AE56(unsigned int index);
    void *rva0021AEB9(unsigned int index);
    void *rva0021AF7E(unsigned int index);
    void *rva0021AFEA(unsigned int index);
    void *rva0021B13A(unsigned int o, unsigned int i);
    void *rva0021B1B4(unsigned int o, unsigned int i);
    void *rva0021B2A2(unsigned int o, unsigned int i);
    void *rva0021A134(unsigned int index);
    int rva0021A016(unsigned int o, unsigned int i);
    int rva00219E74(unsigned int o, unsigned int i);
    int rva00219ED5(unsigned int o, unsigned int i);
    int rva00219D52(unsigned int o);
    int rva0021A041(unsigned int o, unsigned int i);
    int rva0021A06C(unsigned int o, unsigned int i);
    int rva0021A097(unsigned int o, unsigned int i);
    void *rva0021A1B6(unsigned int o, unsigned int i);
    void *rva0021A15D(unsigned int o, unsigned int i);
    void *rva0021B05A(unsigned int index);
    void *rva0021B0CA(unsigned int index);
    void *rva0021B22E(unsigned int o, unsigned int i);
    void *rva0021B670(const IdxPair *p);
    void *rva00219C5D(unsigned int index);
    void *rva00219F8E(unsigned int o, unsigned int i);
    int rva00219C3E(unsigned int o, unsigned int i);
    int rva00219F00(unsigned int o, unsigned int o2, unsigned int i);
    int rva00219C00(unsigned int o, unsigned int i);
    int rva00219E9F(unsigned int o, unsigned int o2, unsigned int i);
    void *rva00219D85(unsigned int index);
    int rva00219FE3(unsigned int o, unsigned int i);
    int rva0021BE42(unsigned int o, unsigned int i);
    int rva0021BF42(unsigned int o, unsigned int outer, unsigned int i);
};
void *Rva00219B9E::rva00219B9E(unsigned int index)
{
    void *result = 0;
    unsigned int count = VecSize(&m_vec);
    if (index < count)
        result = &VecAt(&m_vec, index);
    return result;
}
// ?rva00219CDF@Rva00219B9E@@QAEHI@Z @0x00219CDF 23B: returns element+0x10 or 0.
// Chain of 0x00219B9E; caller 0x0021A016 (outer 32B vector at +0x14C) needs it.
int Rva00219B9E::rva00219CDF(unsigned int index)
{
    void *p = rva00219B9E(index);
    if (p)
        return ((Elem216 *)p)->m_10;
    return 0;
}
// ?rva00219CF6@Rva00219B9E@@QAEHI@Z @0x00219CF6 23B: returns element+0x14 or 0.
// Chain of 0x00219B9E; caller 0x0021A041 needs it.
int Rva00219B9E::rva00219CF6(unsigned int index)
{
    void *p = rva00219B9E(index);
    if (p)
        return ((Elem216 *)p)->m_14;
    return 0;
}
// ?rva00219D0D@Rva00219B9E@@QAEHI@Z @0x00219D0D 23B: returns element+0x18 or 0.
// Chain of 0x00219B9E; caller 0x0021A06C needs it.
int Rva00219B9E::rva00219D0D(unsigned int index)
{
    void *p = rva00219B9E(index);
    if (p)
        return ((Elem216 *)p)->m_18;
    return 0;
}
// ?rva00219D24@Rva00219B9E@@QAEHI@Z @0x00219D24 23B: returns element+0x1C or 0.
// Chain of 0x00219B9E; caller 0x0021A097 needs it.
int Rva00219B9E::rva00219D24(unsigned int index)
{
    void *p = rva00219B9E(index);
    if (p)
        return ((Elem216 *)p)->m_1C;
    return 0;
}
// ?rva00219C93@Rva00219B9E@@QAEHI@Z @0x00219C93 24B: returns element+0x64 or -1.
// Chain of 0x00219B9E; caller 0x00219FE3 needs it. Null path uses or eax,-1.
int Rva00219B9E::rva00219C93(unsigned int index)
{
    void *p = rva00219B9E(index);
    if (!p)
        return -1;
    return ((Elem216 *)p)->m_64;
}
// ?rva00219CAB@Rva00219B9E@@QAEPAXI@Z @0x00219CAB 26B: returns element+0x0C or empty.
// Chain of 0x00219B9E; caller 0x0021B22E needs it. Fallback is TheEmptyString.
void *Rva00219B9E::rva00219CAB(unsigned int index)
{
    void *p = rva00219B9E(index);
    if (p)
        return &((Elem216 *)p)->m_0C;
    return (void *)&AsciiString::TheEmptyString;
}
// ?rva00219CC5@Rva00219B9E@@QAEPAXI@Z @0x00219CC5 26B: returns element+0x20 or empty.
// Chain of 0x00219B9E; caller 0x0021A15D needs it. Fallback is TheEmptyString.
void *Rva00219B9E::rva00219CC5(unsigned int index)
{
    void *p = rva00219B9E(index);
    if (p)
        return &((Elem216 *)p)->m_20;
    return (void *)&AsciiString::TheEmptyString;
}
// ?rva00219BE1@Rva00219B9E@@QAEHI@Z @0x00219BE1 31B: inner int-vector count at +0x3C.
// Chain of 0x00219B9E; caller 0x00219E74 needs it. Pointer diff gives sar 2.
int Rva00219B9E::rva00219BE1(unsigned int index)
{
    void *p = rva00219B9E(index);
    if (p)
        return ((Elem216 *)p)->m_3C.m_finish - ((Elem216 *)p)->m_3C.m_start;
    return 0;
}
// ?rva00219C1F@Rva00219B9E@@QAEHI@Z @0x00219C1F 31B: inner int-vector count at +0x30.
// Chain of 0x00219B9E; callers 0x00219EF4/0x0022027F need it via 0x00219ED5.
int Rva00219B9E::rva00219C1F(unsigned int index)
{
    void *p = rva00219B9E(index);
    if (p)
        return ((Elem216 *)p)->m_30.m_finish - ((Elem216 *)p)->m_30.m_start;
    return 0;
}
// ?rva0021AE56@Rva00219B9E@@QAEPAXI@Z @0x0021AE56 99B
// Subclass-name accessor with function-static fallback "ERROR: Invalid SubCalssIndex".
// Chain of 0x00219B9E; static constructed via rowed StringBase<char> PBD 0x00037BA0
// with atexit cleanup; null path returns the static, else element+8.
// Caller 0x0021B215.
// ?rva0021ADF8@Rva00219B9E@@QAEPAXI@Z @0x0021ADF8 94B
// The element itself (no member offset), with its own static fallback.
void *Rva00219B9E::rva0021ADF8(unsigned int index)
{
    static AsciiString err("ERROR: Invalid SubCalssIndex");
    void *p = rva00219B9E(index);
    if (p)
        return p;
    return &err;
}
void *Rva00219B9E::rva0021AE56(unsigned int index)
{
    static AsciiString err("ERROR: Invalid SubCalssIndex");
    void *p = rva00219B9E(index);
    if (p)
        return (char *)p + 8;
    return &err;
}
// ?rva0021AEB9@Rva00219B9E@@QAEPAXI@Z @0x0021AEB9 99B
// Twin of 0x0021AE56 above with element+4: same static fallback literal,
// same rowed callees; caller 0x0021B303.
void *Rva00219B9E::rva0021AEB9(unsigned int index)
{
    static AsciiString err("ERROR: Invalid SubCalssIndex");
    void *p = rva00219B9E(index);
    if (p)
        return (char *)p + 4;
    return &err;
}
// ?rva0021AF7E@Rva00219B9E@@QAEPAXI@Z @0x0021AF7E 108B
// Outer 32-byte vector accessor at +0x14C with static "ERROR: Invalid CalssIndex"
// fallback; callers 0x0021CB79 0x005B20FB.
void *Rva00219B9E::rva0021AF7E(unsigned int index)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = Vec32Size(&m_outer);
    if (index < count)
        return &Vec32At(&m_outer, index);
    return &err;
}
// ?rva0021AFEA@Rva00219B9E@@QAEPAXI@Z @0x0021AFEA 112B
// Twin of 0x0021AF7E returning outer element+4; same literal and callees;
// callers 0x0021CB51 0x005B55B4.
void *Rva00219B9E::rva0021AFEA(unsigned int index)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = Vec32Size(&m_outer);
    if (index < count)
        return (char *)&Vec32At(&m_outer, index) + 4;
    return &err;
}
// ?rva0021B05A@Rva00219B9E@@QAEPAXI@Z @0x0021B05A 112B
// Twin of 0x0021AF7E/0x0021AFEA returning outer element+8; same literal
// and callees; caller 0x0021CBA1.
void *Rva00219B9E::rva0021B05A(unsigned int index)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = Vec32Size(&m_outer);
    if (index < count)
        return (char *)&Vec32At(&m_outer, index) + 8;
    return &err;
}
// ?rva0021B0CA@Rva00219B9E@@QAEPAXI@Z @0x0021B0CA 112B
// Twin returning outer element+0xC; same literal and callees;
// caller 0x005B56FC.
void *Rva00219B9E::rva0021B0CA(unsigned int index)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = Vec32Size(&m_outer);
    if (index < count)
        return (char *)&Vec32At(&m_outer, index) + 0xC;
    return &err;
}
// ?rva0021B22E@Rva00219B9E@@QAEPAXII@Z @0x0021B22E 116B
// Two-level string lookup: outer 32B vector at +0x14C selects the element,
// then the rowed 0x00219CAB accessor resolves the inner index to element+0x0C;
// either level falls back to its own static error string. Same pattern as
// 0x0021B1B4/0x0021B2A2. Callers 0x0021B685/0x005B554E.
void *Rva00219B9E::rva0021B22E(unsigned int o, unsigned int i)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva00219CAB(i);
    }
    return &err;
}
// ?rva0021B670@Rva00219B9E@@QAEPAXPBUIdxPair@@@Z @0x0021B670 29B
// Null-guarded forward into rowed 0x0021B22E: null yields TheEmptyString,
// else the +0xC/+0x10 pair selects outer and inner indices on the same this.
// Callers 0x002E1C02/0x0037ED4B/0x004AF339/0x004E24AD/0x004E257E/0x005F0447.
void *Rva00219B9E::rva0021B670(const IdxPair *p)
{
    if (!p)
        return (void *)&AsciiString::TheEmptyString;
    return rva0021B22E(p->m_o, p->m_i);
}
// ?rva0021B13A@Rva00219B9E@@QAEPAXII@Z @0x0021B13A 122B
// Twin of 0x0021B1B4 below resolving through 0x0021ADF8; callers 0x0021CBE1,
// 0x0043F98C (MpGameSetup), 0x005B2167, 0x005B6885.
void *Rva00219B9E::rva0021B13A(unsigned int o, unsigned int i)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva0021ADF8(i);
    }
    return &err;
}
// ?rva0021B1B4@Rva00219B9E@@QAEPAXII@Z @0x0021B1B4 122B
// Two-level lookup: outer 32B vector at +0x14C selects the element, then the
// rowed 0x0021AE56 accessor resolves the inner index; either level falls back
// to its own static error string. Outer elements share the +0x14 Vec216
// prefix the callee reads, hence the layout-compatible reinterpret cast.
void *Rva00219B9E::rva0021B1B4(unsigned int o, unsigned int i)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva0021AE56(i);
    }
    return &err;
}
// ?rva0021B2A2@Rva00219B9E@@QAEPAXII@Z @0x0021B2A2 122B
// Twin of 0x0021B1B4 resolving through the +4 accessor 0x0021AEB9;
// callers 0x0021CC0C 0x005B561A.
void *Rva00219B9E::rva0021B2A2(unsigned int o, unsigned int i)
{
    static AsciiString err("ERROR: Invalid CalssIndex");
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva0021AEB9(i);
    }
    return &err;
}
// ?rva0021A134@Rva00219B9E@@QAEPAXI@Z @0x0021A134 41B
// Outer 32-byte vector accessor at +0x14C returning element+0x10 or TheEmptyString.
// Same outer vector as 0x0021AF7E/0x0021AFEA; +0x10 holds an AsciiString.
// Proven by callers 0x004085A1/0x00409490 forwarding the result to StringBase copy 0x000365F0.
void *Rva00219B9E::rva0021A134(unsigned int index)
{
    unsigned int count = Vec32Size(&m_outer);
    if (index < count)
        return (char *)&Vec32At(&m_outer, index) + 0x10;
    return (void *)&AsciiString::TheEmptyString;
}
// ?rva0021A016@Rva00219B9E@@QAEHII@Z @0x0021A016 43B
// Two-level int lookup: outer 32B vector at +0x14C selects the element, then the
// rowed 0x00219CDF accessor resolves the inner index; out-of-range returns 0.
// Same reinterpret-cast pattern as 0x0021B1B4/0x0021B2A2. Caller 0x00407037.
int Rva00219B9E::rva0021A016(unsigned int o, unsigned int i)
{
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva00219CDF(i);
    }
    return 0;
}
// ?rva0021A041@Rva00219B9E@@QAEHII@Z @0x0021A041 43B
// Twin of 0x0021A016 resolving through the +0x14 accessor 0x00219CF6;
// caller 0x00407050.
int Rva00219B9E::rva0021A041(unsigned int o, unsigned int i)
{
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva00219CF6(i);
    }
    return 0;
}
// ?rva0021A06C@Rva00219B9E@@QAEHII@Z @0x0021A06C 43B
// Twin resolving through the +0x18 accessor 0x00219D0D; caller 0x00407069.
int Rva00219B9E::rva0021A06C(unsigned int o, unsigned int i)
{
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva00219D0D(i);
    }
    return 0;
}
// ?rva0021A097@Rva00219B9E@@QAEHII@Z @0x0021A097 43B
// Twin resolving through the +0x1C accessor 0x00219D24; caller 0x005B1B81.
int Rva00219B9E::rva0021A097(unsigned int o, unsigned int i)
{
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva00219D24(i);
    }
    return 0;
}
// ?rva0021A1B6@Rva00219B9E@@QAEPAXII@Z @0x0021A1B6 43B
// Twin returning the inner element itself via rowed 0x00219B9E; null on miss.
// Callers 0x0021D58E/0x00409A93.
void *Rva00219B9E::rva0021A1B6(unsigned int o, unsigned int i)
{
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva00219B9E(i);
    }
    return 0;
}
// ?rva0021A15D@Rva00219B9E@@QAEPAXII@Z @0x0021A15D 46B
// Two-level string lookup: outer 32B vector at +0x14C selects the element,
// then the rowed 0x00219CC5 accessor resolves the inner index to element+0x20;
// out-of-range returns TheEmptyString. Same reinterpret-cast pattern as
// 0x0021A016/0x0021A1B6. Caller 0x004085D7.
void *Rva00219B9E::rva0021A15D(unsigned int o, unsigned int i)
{
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva00219CC5(i);
    }
    return (void *)&AsciiString::TheEmptyString;
}

// Two more outer-index forwards of rva0021A016's shape, to the sibling inner
// accessors rva00219BE1 and rva00219C1F; only the forwarded call differs.

// ?rva00219E74@Rva00219B9E@@QAEHII@Z @0x00219E74 43B -> rva00219BE1
int Rva00219B9E::rva00219E74(unsigned int o, unsigned int i)
{
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva00219BE1(i);
    }
    return 0;
}

// ?rva00219ED5@Rva00219B9E@@QAEHII@Z @0x00219ED5 43B -> rva00219C1F
int Rva00219B9E::rva00219ED5(unsigned int o, unsigned int i)
{
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        return ((Rva00219B9E *)&base[o])->rva00219C1F(i);
    }
    return 0;
}

// ?rva00219D52@Rva00219B9E@@QAEHI@Z @0x00219D52 51B
// Outer 32B vector at +0x14C selects element o, then returns the count of its
// inner 216B vector at +0x14 via signed idiv. Same reinterpret-cast pattern as
// 0x00219E74/0x0021A016: outer elements share the +0x14 Vec216 prefix.
// Evidence: retail lea eax,[ecx+0x14C] plus sar 5 for outer, then
// lea ecx,[ecx+eax+0x14] plus mov ecx,0xD8/cdq/idiv for inner.
int Rva00219B9E::rva00219D52(unsigned int o)
{
    unsigned int count = Vec32Size(&m_outer);
    if (o < count) {
        OuterElem32 *base = m_outer.m_start;
        Rva00219B9E *inner = (Rva00219B9E *)&base[o];
        return (int)VecSize(&inner->m_vec);
    }
    return 0;
}

// ?rva00219C5D@Rva00219B9E@@QAEPAXI@Z @0x00219C5D 54B
// One-time memset of g_00DFE364 guarded by g_00DFE368, then forwards index
// through rowed rva00219B9E and returns element+0x68 unconditionally.
// Evidence: retail test byte/or dword guard plus push 4/0/addr call to the
// rowed memset thunk 0x006291AE, then push index call rva00219B9E plus
// add eax,0x68; caller 0x00219F8E; same class/outer layout as siblings.
void *Rva00219B9E::rva00219C5D(unsigned int index)
{
    if (!(*(unsigned char *)&g_00DFE368 & 1)) {
        g_00DFE368 |= 1;
        ji_006291ae(&g_00DFE364, 0, 4);
    }
    void *p = rva00219B9E(index);
    return (char *)p + 0x68;
}
// ?rva00219F8E@Rva00219B9E@@QAEPAXII@Z @0x00219F8E 85B
// One-time memset of g_00DFE3E0 guarded by g_00DFE3E4, then outer 32B vector
// at +0x14C selects element o and forwards i through rowed 0x00219C5D;
// out-of-range returns &g_00DFE3E0. Same guard idiom as 0x00219C5D and same
// outer reinterpret-cast pattern as 0x00219E74/0x0021A016.
// Evidence: retail test byte/or dword guard plus push 4/0/addr call to rowed
// memset thunk 0x006291AE, lea eax,[edi+0x14C] plus sar 5 outer count,
// shl 5 plus call 0x00219C5D; callers 0x002446DE/0x0044089E/0x00441549/0x0052BC1D.
void *Rva00219B9E::rva00219F8E(unsigned int o, unsigned int i)
{
    void *fallback = &g_00DFE3E0;
    if (!(*(unsigned char *)&g_00DFE3E4 & 1)) {
        g_00DFE3E4 |= 1;
        ji_006291ae(fallback, 0, 4);
    }
    unsigned int count = Vec32Size(&m_outer);
    if (o >= count)
        return fallback;
    OuterElem32 *base = m_outer.m_start;
    return ((Rva00219B9E *)&base[o])->rva00219C5D(i);
}
// ?rva00219B62@Rva00219B62@@QAEHI@Z @0x00219B62 30B
// Inner int-vector element at +0x30/+0x34 (Elem216::m_30): bounds-checked load
// returning start[index] or 0. Same sar-2 count idiom as 0x00219BE1/0x00219C1F.
// Evidence: retail mov edx,[ecx+0x34] sub [ecx+0x30] sar 2 cmp jae xor,
// else mov ecx,[ecx+0x30] mov eax,[ecx+eax*4]; caller 0x00219C51 in 0x00219C3E
// which forwards element from rowed 0x00219B9E; unblocks 0x00219C3E.
int Rva00219B62::rva00219B62(unsigned int index)
{
    unsigned int count = (unsigned int)(((char *)m_vec.m_finish - (char *)m_vec.m_start) >> 2);
    if (index < count) {
        _ReadWriteBarrier();
        return m_vec.m_start[index];
    }
    return 0;
}
// ?rva00219C3E@Rva00219B9E@@QAEHII@Z @0x00219C3E 31B
// Two-level int lookup: rowed 0x00219B9E selects the 216B element via o,
// then rowed 0x00219B62 selects the inner int at +0x30 via i; null yields 0.
// Evidence: retail push [esp+4] call 0x219B9E test je xor else push [esp+8]
// mov ecx,eax call 0x219B62; same this passthrough proves Rva00219B9E owner;
// caller 0x00219F2A in 0x00219F00; unblocks 0x00219F00.
int Rva00219B9E::rva00219C3E(unsigned int o, unsigned int i)
{
    void *p = rva00219B9E(o);
    if (p)
        return ((Rva00219B62 *)p)->rva00219B62(i);
    return 0;
}
// ?rva00219F00@Rva00219B9E@@QAEHIII@Z @0x00219F00 54B
// Three-level int lookup: outer 32B vector at +0x14C selects element o,
// then rowed 0x00219C3E resolves (o2 i) on the same this prefix.
// Evidence: retail mov eax ecx mov edx [eax+0x150] sub [eax+0x14C] sar 5
// cmp jae xor else shl 5 add ecx [eax+0x14C] call 0x219C3E; caller 0x00406E9F
// in 0x00406E8F; unblocks 0x00406E8F.
int Rva00219B9E::rva00219F00(unsigned int o, unsigned int o2, unsigned int i)
{
    unsigned int count = (unsigned int)(((char *)m_outer.m_finish - (char *)m_outer.m_start) >> 5);
    if (o < count) {
        _ReadWriteBarrier();
        return ((Rva00219B9E *)((char *)m_outer.m_start + (o << 5)))->rva00219C3E(o2, i);
    }
    return 0;
}
// ?rva00219B80@Rva00219B80@@QAEHI@Z @0x00219B80 30B
// Twin of 0x00219B62 at +0x3C/+0x40 (Elem216::m_3C): same sar-2 barrier reload.
// Evidence: retail mov edx [ecx+0x40] sub [ecx+0x3C] sar 2 cmp jae xor else
// mov ecx [ecx+0x3C] mov eax [ecx+eax*4]; caller 0x00219C13 in 0x00219C00;
// unblocks 0x00219C00.
int Rva00219B80::rva00219B80(unsigned int index)
{
    unsigned int count = (unsigned int)(((char *)m_vec.m_finish - (char *)m_vec.m_start) >> 2);
    if (index < count) {
        _ReadWriteBarrier();
        return m_vec.m_start[index];
    }
    return 0;
}
// ?rva00219C00@Rva00219B9E@@QAEHII@Z @0x00219C00 31B
// Two-level int lookup: rowed 0x00219B9E selects the 216B element via o,
// then rowed 0x00219B80 selects the inner int at +0x3C via i; null yields 0.
// Evidence: retail push [esp+4] call 0x219B9E test je xor else push [esp+8]
// mov ecx,eax call 0x219B80; twin of 0x00219C3E via +0x30; same this
// passthrough proves Rva00219B9E owner; caller 0x00219EC9 in 0x00219E9F.
int Rva00219B9E::rva00219C00(unsigned int o, unsigned int i)
{
    void *p = rva00219B9E(o);
    if (p)
        return ((Rva00219B80 *)p)->rva00219B80(i);
    return 0;
}
// ?rva00219E9F@Rva00219B9E@@QAEHIII@Z @0x00219E9F 54B
// Three-level int lookup: outer 32B vector at +0x14C selects element o,
// then rowed 0x00219C00 resolves (o2 i) on the same this prefix.
// Evidence: retail mov eax ecx mov edx [eax+0x150] sub [eax+0x14C] sar 5
// cmp jae xor else shl 5 add ecx [eax+0x14C] call 0x219C00; twin of 0x00219F00
// via 0x00219C3E; caller 0x00406E75 in 0x00406E65.
int Rva00219B9E::rva00219E9F(unsigned int o, unsigned int o2, unsigned int i)
{
    unsigned int count = (unsigned int)(((char *)m_outer.m_finish - (char *)m_outer.m_start) >> 5);
    if (o < count) {
        _ReadWriteBarrier();
        return ((Rva00219B9E *)((char *)m_outer.m_start + (o << 5)))->rva00219C00(o2, i);
    }
    return 0;
}
// ?rva00219D85@Rva00219B9E@@QAEPAXI@Z @0x00219D85 37B
// Bounds-checked 16-byte element accessor at +0x15C/+0x160.
// Returns null when index >= (finish-start)/16 via sar 4, else start+index*16.
// Evidence: retail mov edx [ecx+0x160] mov eax [esp+4] add ecx 0x15c sub sar 4
// cmp jae xor else shl 4 add; callers 0x00219DD7/0x00219E17/0x00219E5C and
// 0x0021AD93/0x0021ADB3/0x0021BCE1/0x0021BD76; same class as neighbours
// (m_outer at +0x14C, this vector at +0x15C).
void *Rva00219B9E::rva00219D85(unsigned int index)
{
    Vec16 *v = &m_15c;
    char *finish = (char *)v->m_finish;
    unsigned int count = (unsigned int)((finish - (char *)v->m_start) >> 4);
    if (index < count) {
        _ReadWriteBarrier();
        return &v->m_start[index];
    }
    return 0;
}
// ?rva00219FE3@Rva00219B9E@@QAEHII@Z @0x00219FE3 51B
// Two-level int forward to rowed 0x00219C93 (element+0x64 or -1).
// Same outer 32B shape as 0x00219F00/0x00219E9F but miss returns -1 via
// or eax,-1; retail mov eax ecx mov edx [eax+0x150] sub [eax+0x14C] sar 5
// cmp jb plus shl 5 add ecx [eax+0x14C] call 0x219C93; caller 0x0021A709.
int Rva00219B9E::rva00219FE3(unsigned int o, unsigned int i)
{
    unsigned int count = (unsigned int)(((char *)m_outer.m_finish - (char *)m_outer.m_start) >> 5);
    if (o >= count)
        return -1;
    _ReadWriteBarrier();
    return ((Rva00219B9E *)((char *)m_outer.m_start + (o << 5)))->rva00219C93(i);
}
// ?rva0021BF42@Rva00219B9E@@QAEHIII@Z @0x0021BF42 50B: outer 32B at +0x14C selects via middle index then rowed 0x0021BE42. Evidence: same outer shape as 0x00219FE3 51B but miss returns -1 and forwards first and third args; callee rowed 0x0021BE42; caller 0x005B1D0A.
int Rva00219B9E::rva0021BF42(unsigned int o, unsigned int outer, unsigned int i)
{
    Vec32 *v = &m_outer;
    unsigned int count = Vec32Size(v);
    if (outer < count) {
        _ReadWriteBarrier();
        OuterElem32 *base = v->m_start;
        return ((Rva00219B9E *)&base[outer])->rva0021BE42(o, i);
    }
    return -1;
}
