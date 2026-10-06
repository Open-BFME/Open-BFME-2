// ??0Rva004E4F82@@QAE@XZ
// cl: /Ireference/shims/bfmelist /EHsc /Ow /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004E4F82@@QAE@XZ @0x004E4F82 144B
// __thiscall no-arg ctor: six floats +0..+0x14 zero, +0x18 zero,
// +0x24=g_Va00BBB8D8 +0x28=g_bfmeClearA +0x2c=g_00BC6258, +0x30=-1,
// list<int> at +0x34 via rowed List_base<int> 0x004EC36C,
// list<BfmePod8> at +0x38 via rowed List_base<BfmePod8> 0x0035C9A6.
// Caller 0x004E556E in 0x004E5559. Flags copy stlport_pod_list_bodies.cpp
// plus /arch:SSE for movss/xmm; /Ow is required to reproduce retail's early
// `or [esi+0x30],-1` scheduling (default aliasing pushes it after the stores).
#include <list>
struct BfmePod8 { int a[2]; };
inline bool operator==(const BfmePod8 &x, const BfmePod8 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod8 &x, const BfmePod8 &y) { return x.a[0] < y.a[0]; }

extern float g_Va00BBB8D8;
extern const float g_bfmeClearA;
extern float g_00BC6258;

class Rva004E4F82
{
public:
    Rva004E4F82();
    float m_00;
    float m_04;
    float m_08;
    float m_0C;
    float m_10;
    float m_14;
    float m_18;
    int m_1C;
    int m_20;
    float m_24;
    float m_28;
    float m_2C;
    int m_30;
    _STL::list<int, _STL::allocator<int> > m_34;
    _STL::list<BfmePod8, _STL::allocator<BfmePod8> > m_38;
};

Rva004E4F82::Rva004E4F82() : m_30(-1), m_18(0.0f), m_24(g_Va00BBB8D8), m_28(g_bfmeClearA), m_2C(g_00BC6258)
{
    m_00 = 0.0f;
    m_04 = 0.0f;
    m_08 = 0.0f;
    m_0C = 0.0f;
    m_10 = 0.0f;
    m_14 = 0.0f;
}