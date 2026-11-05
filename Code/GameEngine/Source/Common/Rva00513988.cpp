// stlport
// Target evidence: Ghidra bounds 0x00513988-0x005139AF (40B); the preceding
// byte is RET and the next Ghidra function starts at 0x005139B0. Retail calls
// AptMyHero::rva005B1A6C (rowed in AptMyHero.cpp) on the embedded hero at
// this+0x27C, then invokes virtual slot 1 on five pointers at this+0x418.
// The containing class identity and member meanings are unknown.
#include "../../Include/GameClient/AptMyHero.h"

class Rva005B02B5 {
public:
    void rva005B027F();
    void rva005B0249();
    void rva005B02B5();
    void rva005B02FD();
};

class Rva00513988Part {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2(bool selected);
};

class Rva00513988 {
public:
    int rva005138E8();
    void rva00513988();
private:
    char m_pad0[0x27c];
    AptMyHero m_hero;                   // +0x27C
    char m_pad40C[0x410 - 0x40c];
    Rva00513988Part *m_selected;        // +0x410
    char m_pad414[4];
    Rva00513988Part *m_parts[5];        // +0x418
    char m_pad42C[4];
    bool m_flag430, m_flag431, m_flag432, m_flag433;
};

// ?rva005138E8@Rva00513988@@QAEHXZ @ 0x005138E8 160B (WorldBuilder twin at
// 0x01453FD0, directly before this file's 0x00513988 twin at 0x014540E0).
// Each set flag at +0x430..+0x433 drives one of the hero's four setters
// (rowed in Rva005B02B5.cpp); any of them rebuilds the hero (0x005B1019).
// Then the hero's per-frame update runs (0x005B1EE2, WB AptMyHero::FrameUpdate)
// and each of the five parts gets virtual slot 2 with whether it is the
// selected one. Returns 1. WB's indexed loop, with the part read again for
// the comparison, is what gives retail's copy before the SETE.
int Rva00513988::rva005138E8()
{
    bool changed = false;
    if (m_flag431) {
        ((Rva005B02B5 *)&m_hero)->rva005B027F();
        changed = true;
    }
    if (m_flag430) {
        ((Rva005B02B5 *)&m_hero)->rva005B0249();
        changed = true;
    }
    if (m_flag432) {
        ((Rva005B02B5 *)&m_hero)->rva005B02B5();
        changed = true;
    }
    if (m_flag433) {
        ((Rva005B02B5 *)&m_hero)->rva005B02FD();
        changed = true;
    }
    if (changed)
        m_hero.rva005B1019();
    m_hero.FrameUpdate();
    for (int i = 0; i < 5; ++i)
        m_parts[i]->slot2(m_parts[i] == m_selected);
    return 1;
}

void Rva00513988::rva00513988()
{
    ((AptMyHero *)((char *)this + 0x27C))->rva005B1A6C();

    Rva00513988Part **part = (Rva00513988Part **)((char *)this + 0x418);
    for (int count = 5; count > 0; --count) {
        (*part)->slot1();
        ++part;
    }
}
