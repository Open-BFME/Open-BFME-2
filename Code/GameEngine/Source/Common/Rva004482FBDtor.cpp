// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// Native EH action 0x789325 destroys the eight LANGameSlot objects at +0xDC with stride0x1D0; the complete parent EH graph proves this 27B lifetime.
// ??1LANGameInfo@@UAE@XZ retail 0x004482FB 87B: Zero Hour's LANGameInfo
// declares no destructor (GameNetwork/LANGameInfo.h), so this is the implicit
// virtual one, called by the scalar deleting destructor 0x004482DF in slot 0
// of the LANGameInfo vtable 0x00C3E518. It releases m_gameName at +0xF64
// (rowed 0x00036E70), destroys the eight 0x1D0-byte slots at +0xDC with
// ~LANGameSlot 0x00447B0E, then runs the GameInfo base destructor 0x00400A7F
// without re-storing the vtable (MSVC 7.1's implicit shape). The base is
// rowed as ??1GameInfo (formerly the address name Rva00382FA7).
#include "unicode_string.h"

class GameInfo
{
public:
    virtual ~GameInfo();
    char m_pad[0xDC - 4];
};

class GameSlot
{
public:
    virtual ~GameSlot();
    void setAccept() { m_isAccepted = true; }
    void setMapAvailability(bool hasMap);
private:
    int m_state;                        // +0x04
    bool m_isAccepted;                  // +0x08
    char m_rest[0x1AC - 9];
};

class LANGameSlot : public GameSlot
{
public:
    virtual ~LANGameSlot();
private:
    char m_rest[0x1D0 - 0x1AC];
};

// LANGameSlot's copy assignment, rowed under its address name (0x00447B58).
struct Rva00447B0E
{
    struct Rva00447B0E &rva00447B58(const struct Rva00447B0E &o);
};

enum
{
    MAX_SLOTS = 8
};

class LANGameInfo : public GameInfo
{
public:
    void setSlot(int slotNum, LANGameSlot slotInfo);
private:
    LANGameSlot m_LANSlot[MAX_SLOTS];   // +0xDC
    LANGameInfo *m_next;                // +0xF5C
    unsigned int m_lastHeard;           // +0xF60
    UnicodeString m_gameName;           // +0xF64
    bool m_isDirectConnect;             // +0xF68
};

// Makes this unit emit the implicit destructor; not retail code.
// ?<LANGameInfo::~LANGameInfo anchor> absent-from-retail
void bfmeAnchorLANGameInfoDtor(LANGameInfo *game)
{
    game->LANGameInfo::~LANGameInfo();
}

// ?getSlotNum@Rva004482FB@@QAEHVUnicodeString@@@Z @0x004483BC (103B):
// LANGameInfo-style getSlotNum by Unicode name: inGame gate at +0x10,
// per-slot getConstLANSlot scan over 8x0x1D0 at +0xDC via rowed 0x447773,
// isPlayer via rowed Rva004481A7 0x4481A7, by-value UnicodeString with
// explicit copy-ctor temp (rowed 0x37050) and tail releaseBuffer (rowed
// 0x36E70), ret 4. Evidence: chain from 0x4481A7; callers 0x24A1C1 0x582202;
// layout matches Rva004482FB/LANGameInfoSlots precedent.
class Rva00447773
{
public:
    void *getLANSlot(int index);
};

class Rva004482FB
{
public:
    int getSlotNum(UnicodeString name);
};

class Rva004481A7
{
public:
    bool isPlayer(UnicodeString userName) const;
};

// ?getSlotNum@Rva004482FB@@QAEHVUnicodeString@@@Z
int Rva004482FB::getSlotNum(UnicodeString name)
{
    if (!*(bool *)((char *)this + 0x10))
        return -1;
    for (int i = 0; i < 8; ++i)
    {
        void *slot = ((Rva00447773 *)this)->getLANSlot(i);
        if (((Rva004481A7 *)slot)->isPlayer(name))
            return i;
    }
    return -1;
}
