// cl: /MD
// AIWallBuilder::canBuildAnyWall (WorldBuilder name, AIWallBuilder.cpp line 186: the same +0x08 player test through 0x002A8AB1).
// was ?rva004E98DE@Rva004E98DE@@QAEEXZ, retail 0x004E98DE, 25 bytes.
// thiscall reads this+8 as owner for rowed-adjacent pin rva002A8AB1 0x002A8AB1 via g_00DFEEF8 then tests +0x16c > 0. Caller 0x004E9DB8.
struct Rva002A8AB1Record
{
    char m_pad00[0x160];
    void *m_160;
    char m_pad164[0x16c - 0x164];
    int m_16c;
};
class Rva002A8F24
{
public:
    Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;
class AIWallBuilder
{
    char m_pad00[8];
    void *m_owner;
public:
    unsigned char canBuildAnyWall();
};
unsigned char AIWallBuilder::canBuildAnyWall()
{
    return g_00DFEEF8->rva002A8AB1(m_owner)->m_16c > 0;
}
