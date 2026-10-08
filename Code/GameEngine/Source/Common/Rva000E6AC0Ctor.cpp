// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Fix over the banked attempt, from the retail unwind map (ten states): state 0
// is a polymorphic base with an out-of-line virtual dtor (folded 7-byte
// 0x0049B47C); states 1-4 the four vectors; state 5 the Rva00087A93 at +0x34
// (rowed dtor 0x0007B724); states 6-7 the RefCountPtr<TextureClass> pair at
// +0x38/+0x3C; states 8-9 the two Rva00171024 members, whose destructor is
// out of line (0x00170E82). The ??_H iterator builds 100 Coord3D (12-byte,
// rowed empty ctor 0x0047A6A9) at +0x90, not 12 larger records. The 1.0
// fallback is a compiler literal (retail pool 0x007BB8D8).
// stlport
// ??0Rva000E6AC0@@QAE@XZ retail 0x000E6AC0 211B chain lane ctor with EH.
// Calls rowed vector_base 0x00211E58 x4 plus landed Rva00171024 ctor 0x00171024
// x2 plus rowed Region3D ctor 0x0047A6A9 x12 via ??_H plus rowed __EH_prolog.
// Evidence: vtable 0x007CEAB4 at +0; DXT5/DXT1 FourCCs; float from 0x009FE710.

#include <map>

class LadderPref
{
    char m_pad[16];
};

typedef _STL::map<long, LadderPref> LadderPrefMap;

class Rva00171024
{
public:
    Rva00171024(int a, int b);
    ~Rva00171024();

private:
    int m_00;
    int m_04;
    LadderPrefMap m_map;
    LadderPrefMap::iterator m_current;
    int m_18;
    bool m_1c;
    bool m_1d;
};

#include <vector>
class Rva00087A93
{
public:
    Rva00087A93() : m_data(0) {}
    ~Rva00087A93();
private:
    void *m_data;
};
class TextureClass;
template <class T> class RefCountPtr
{
public:
    RefCountPtr() : m_ptr(0) {}
    ~RefCountPtr();
private:
    T *m_ptr;
};

struct BfmeE16 { float x, y, z, w; };

struct Coord3D
{
    float x;
    float y;
    float z;
    Coord3D();
};
class Rva000E6AC0Base
{
public:
    Rva000E6AC0Base() {}
    virtual ~Rva000E6AC0Base();
};

struct Global9FE710
{
    char m_pad[0x38];
    int m_38;
};

extern Global9FE710 *g_Va009FE710;

class Rva000E6AC0 : public Rva000E6AC0Base
{
public:
    Rva000E6AC0();
    virtual ~Rva000E6AC0();

private:
    _STL::vector<BfmeE16> m_vec0;
    _STL::vector<BfmeE16> m_vec1;
    _STL::vector<BfmeE16> m_vec2;
    _STL::vector<BfmeE16> m_vec3;
    Rva00087A93 m_34;
    RefCountPtr<TextureClass> m_38;
    RefCountPtr<TextureClass> m_3c;
    Rva00171024 m_r40;
    int m_60;
    int m_64;
    Rva00171024 m_r68;
    int m_88;
    int m_8c;
    Coord3D m_90[100];
    int m_540;
    char m_pad544[0x5BC - 0x544];
    float m_5bc;
};

// ??0Rva000E6AC0@@QAE@XZ @0x000E6AC0
Rva000E6AC0::Rva000E6AC0()
    : m_vec0(), m_vec1(), m_vec2(), m_vec3()
    , m_r40(0x800, 0x35545844)
    , m_r68(0x400, 0x31545844)
{
    float f = (g_Va009FE710 != 0) ? (float)g_Va009FE710->m_38 : 1.0f;
    m_540 = -1;
    m_5bc = f;
}

// ?g_Va009FE710@@3PAUGlobal9FE710@@A: the global at this VA is ?TheGameEngine@@3PAVGameEngine@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va009FE710@@3PAUGlobal9FE710@@A=?TheGameEngine@@3PAVGameEngine@@A")
// ?g_Va009FE710@@3PAUGlobal9FE710@@A: the global at VA 0xdfe710 is ?TheGameEngine@@3PAVGameEngine@@A.
#pragma comment(linker, "/alternatename:?g_Va009FE710@@3PAUGlobal9FE710@@A=?TheGameEngine@@3PAVGameEngine@@A")
