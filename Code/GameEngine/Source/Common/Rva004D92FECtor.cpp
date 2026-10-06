// cl: /MD
//
// ??0Rva004D92FE@@QAE@XZ @0x004D92FE 61B
// Frameless 0x24-byte holder ctor: byte false at +0, four int zeros at
// +4/+8/+0xC/+0x10, Coord3D at +0x14 from the global default, int zero at
// +0x20. No vptr, so plain class with an honest Rva name. Evidence: 22 free
// callers wait on it including 0x0026B403 which inits a stack slot at
// ebp-0x3c via lea ecx and passes it to 0x004DAAFD; that callee compares
// +0x14 via rowed Coord3D::equals 0x00003702 against the global at
// 0x00DCFC18 at 0x004DA74B and 0x004DB95B. Data 0x009CFC18 holds
// FLT_MAX,-FLT_MAX,FLT_MAX. The three movss loads are DIR32-masked; literals
// would hoist and CSE, while the extern global keeps retail order.

#include <float.h>

struct Coord3DBase
{
    float x;
    float y;
    float z;
};

// g_bfmeCoordDefault: VA 0x00DCFC18 (.data); retail bytes encode FLT_MAX,
// -FLT_MAX, FLT_MAX in the Coord3DBase layout.
Coord3DBase g_bfmeCoordDefault = { FLT_MAX, -FLT_MAX, FLT_MAX };

class Rva004D92FE
{
public:
    Rva004D92FE();

private:
    bool m_00;
    int m_04;
    int m_08;
    int m_0c;
    int m_10;
    Coord3DBase m_14;
    int m_20;
};

Rva004D92FE::Rva004D92FE()
{
    m_00 = false;
    m_04 = 0;
    m_08 = 0;
    m_0c = 0;
    m_10 = 0;
    m_14.x = g_bfmeCoordDefault.x;
    m_14.y = g_bfmeCoordDefault.y;
    m_14.z = g_bfmeCoordDefault.z;
    m_20 = 0;
}
