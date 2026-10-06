// cl: /Ireference/shims/bfme2_ascii /GX-
// ?rva0038028B@Rva00380200@@QAEXXZ @0x0038028B 84B. Unlock init plus rank bonus plus tail to rva0038020D
// evidence: prev 0x0038020D same class Rva00380200 same TU family; members +0x4 +0xC(float) +0x14 +0x18 +0x1C +0x28
// match shim; callees TheRankInfoStore plus pinned get 0x002000D7 plus rowed tail 0x0038020D; unblocks 2.
#include "ascii_string.h"
struct Rva002000D7Config
{
    int m_pad[0x34 / 4];
    int m_34;
};
class Rva002000D7Store
{
public:
    Rva002000D7Config *get(int v);
};
class RankInfoStore;
extern RankInfoStore *TheRankInfoStore;
class Rva00380200
{
public:
    void rva0038028B();
    void rva0038020D();
    void rva0038027B(int v);
private:
    int m_00;
    void *m_04;
    unsigned char m_pad08[0x0C - 0x08];
    float m_0C;
    int m_10;
    int m_14;
    int m_18;
    int m_1C;
    unsigned char m_pad20[0x28 - 0x20];
    int m_28;
};
void Rva00380200::rva0038027B(int v)
{
    m_1C += v;
    if (m_1C < 0)
        m_1C = 0;
}
void Rva00380200::rva0038028B()
{
    m_28 = 0;
    m_14 = 1;
    m_18 = 1;
    m_0C = 0.0f;
    if (!m_04)
        m_1C &= (int)m_04;
    else
        m_1C = *(int *)((char *)m_04 + 4);
    Rva002000D7Config *cfg = TheRankInfoStore ? ((Rva002000D7Store *)TheRankInfoStore)->get(1) : 0;
    int add = cfg ? cfg->m_34 : 0;
    m_1C += add;
    rva0038020D();
}
