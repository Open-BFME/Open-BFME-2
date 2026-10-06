// cl: /DNDEBUG /MD
// ?doCanMake@AIBuildable@@QAEHPAVPlayer@@@Z @0x0055AE75 97B unlock lane spend via RTS map Money virtual.
// Evidence: mov ecx g_00DFEEF8 call rowed rva002A8F24 0x002A8F24 then flag +0x21 gated rowed Money rva003B0D7C 0x003B0D7C and rva003B0CB3 0x003B0CB3 on Player+0x90 plus virtual slot 0x40; caller 0x004ECC85.
class Player;
class Rva0039B7AD;
class Rva0039B795;

class Rva003B0D7C
{
public:
    unsigned int rva003B0CB3(unsigned int amount, Rva0039B795 *arg2, bool flag);
    void rva003B0D7C(int amount, Rva0039B7AD *arg2, bool flag);
};

class PlayerFull
{
public:
    char _0[0x90];
    Rva003B0D7C m_money;
};

class Rva002A8F24
{
public:
    void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;

struct MapResInner
{
    char _0[0x14];
    int m_14;
};
struct MapRes
{
    char _0[0x0C];
    MapResInner *m_0C;
};

class AIBuildable
{
public:
    virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
    virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
    virtual void f08(); virtual void f09(); virtual void f10(); virtual void f11();
    virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
    virtual int virt16(Player *p);
    int doCanMake(Player *player);
private:
    char m_pad[0x1D];
    unsigned char m_21;
};

int AIBuildable::doCanMake(Player *player)
{
    MapRes *res = (MapRes *)g_00DFEEF8->rva002A8F24(player);
    int virtRes = 0;
    if (m_21)
    {
        int amount = res->m_0C->m_14;
        ((PlayerFull *)player)->m_money.rva003B0D7C(amount, 0, false);
    }
    virtRes = virt16(player);
    if (m_21)
    {
        int amount = res->m_0C->m_14;
        ((PlayerFull *)player)->m_money.rva003B0CB3((unsigned int)amount, 0, false);
    }
    return virtRes;
}
