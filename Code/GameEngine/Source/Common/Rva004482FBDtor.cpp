// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ??1Rva004482FB@@QAE@XZ retail 0x004482FB 87B
// Dtor: release UnicodeString at +0xF64 via rowed 0x00036E70 then destroy 8x0x1D0 array at +0xDC via rowed Rva00447B0E 0x00447B0E then base Rva00382FA7 pin 0x00400A7F. Evidence: unlock lane; caller 0x004482DF deleting dtor; prev Rva004482B7Finish array shape 8x0x1D0; wide release same as sibling 0x00448280.
#include "unicode_string.h"

class Rva00382FA7
{
public:
    virtual ~Rva00382FA7();
    char m_pad[0xDC - 4];
};

class GameSlot
{
public:
    void setMapAvailability(bool v);
};

struct Rva00447B0E
{
    ~Rva00447B0E();
    struct Rva00447B0E &rva00447B58(const struct Rva00447B0E &o);
    char m_pad[0x1D0];
};

class Rva004482FB
{
public:
    ~Rva004482FB();
    void rva00448352(int index, struct Rva00447B0E v);
    int rva004483BC(UnicodeString name);
private:
    Rva00382FA7 m_base;
    struct Rva00447B0E m_items[8];
    char m_gap[8];
    UnicodeString m_wide;
};

Rva004482FB::~Rva004482FB()
{
}

// ?rva00448352@Rva004482FB@@QAEXHURva00447B0E@@@Z @0x00448352 106B: assign m_items[index] from by-value Rva00447B0E plus index0 GameSlot setMapAvailability. Evidence: prev owns 8x0x1D0 at +0xDC; imul 0x1D0 and ret 0x1D4 prove by-value 0x1D0; callers 4 free; callees rowed.
void Rva004482FB::rva00448352(int index, struct Rva00447B0E v)
{
    if (index < 0 || index >= 8)
        return;
    m_items[index].rva00447B58(v);
    if (index != 0)
        return;
    m_items[0].m_pad[8] = 1;
    ((GameSlot *)&m_items[0])->setMapAvailability(true);
}

// ?rva004483BC@Rva004482FB@@QAEHVUnicodeString@@@Z @0x004483BC (103B):
// LANGameInfo-style getSlotNum by Unicode name: inGame gate at +0x10,
// per-slot getConstLANSlot scan over 8x0x1D0 at +0xDC via rowed 0x447773,
// isPlayer via rowed Rva004481A7 0x4481A7, by-value UnicodeString with
// explicit copy-ctor temp (rowed 0x37050) and tail releaseBuffer (rowed
// 0x36E70), ret 4. Evidence: chain from 0x4481A7; callers 0x24A1C1 0x582202;
// layout matches Rva004482FB/LANGameInfoSlots precedent.
class Rva00447773
{
public:
    void *rva00447773(int index);
};

class Rva004481A7
{
public:
    bool isPlayer(UnicodeString userName) const;
};

// ?rva004483BC@Rva004482FB@@QAEHVUnicodeString@@@Z
int Rva004482FB::rva004483BC(UnicodeString name)
{
    if (!*(bool *)((char *)this + 0x10))
        return -1;
    for (int i = 0; i < 8; ++i)
    {
        void *slot = ((Rva00447773 *)this)->rva00447773(i);
        if (((Rva004481A7 *)slot)->isPlayer(name))
            return i;
    }
    return -1;
}
