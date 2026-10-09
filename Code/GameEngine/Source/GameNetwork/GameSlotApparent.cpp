// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc

// GameSlot apparent-* family plus the two slot predicates it shares a page
// with. BFME1 GameInfo.cpp donor (reference/open-bfme-1/.../GameNetwork/
// GameInfo.cpp): the four apparent accessors hide a network opponent's true
// slot behind the original values unless the slot is a local ally, and the
// display-name variant falls back to GUI:Random / GUI:Observer fetched from
// the string manager. Retail outlines the ally test into its own 92B body;
// because every caller lives in this TU, MSVC's same-TU private convention
// carries the slot in EDI with a bare call and the callers home `this` into
// EDI for their own post-call reads.

typedef int Int;
typedef bool Bool;

enum { MAX_SLOTS = 8 };

// BFME2 numbers the human slot state as 6: retail isHuman bodies compare
// m_state against 6. The earlier states are not named here.
enum { SLOT_PLAYER = 6 };

enum
{
    PLAYERTEMPLATE_RANDOM = -1,
    PLAYERTEMPLATE_OBSERVER = -2
};

typedef unsigned short WideChar;

class AsciiString;
class UnicodeString;

#include "ascii_string.h"
#include "unicode_string.h"



// Retail fetch calls use vtable offset 0x3c. The fourteen preceding
// non-destructor methods have not yet been reconstructed in this TU.
class GameTextInterface
{
public:
    virtual ~GameTextInterface() {}
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1c() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2c() = 0;
    virtual void slot30() = 0;
    virtual void slot34() = 0;
    virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class MultiplayerColorDefinition
{
public:
    Int getColor() const { return m_color; }

private:
    AsciiString m_tooltipName;
    float m_rgbValue[3];
    Int m_color;
};

class MultiplayerSettings
{
public:
    Bool showRandomPlayerTemplate() const { return m_showRandomPlayerTemplate; }
    Bool showRandomStartPos() const { return m_showRandomStartPos; }
    Bool showRandomColor() const { return m_showRandomColor; }
    MultiplayerColorDefinition *getColor(Int which);

private:
    char m_pad[0x1D];
    Bool m_showRandomPlayerTemplate;
    Bool m_showRandomStartPos;
    Bool m_showRandomColor;
};

extern MultiplayerSettings *TheMultiplayerSettings;

class PlayerTemplate
{
public:
    UnicodeString getDisplayName() const;
};

class PlayerTemplateStore
{
public:
    const PlayerTemplate *getNthPlayerTemplate(Int which) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;
// ThePlayerTemplateStore: matched references place it at VA 0xdfe0d0 (zero-filled .bss).
PlayerTemplateStore * ThePlayerTemplateStore;

class GameInfo;

struct BfmeNetAddress
{
    unsigned int m_ip;
    unsigned short m_port;
};

class GameSlot
{
public:
    virtual void reset();

    Bool isHuman() const { return m_state == SLOT_PLAYER; }
    Bool isAI() const;
    Int getColor() const { return m_color; }
    Int getTeamNumber() const { return m_teamNumber; }
    Int getOriginalPlayerTemplate() const { return m_origPlayerTemplate; }

    Int getApparentPlayerTemplate() const;
    Int getApparentColor() const;
    Int getApparentStartPos() const;
    UnicodeString getApparentPlayerTemplateDisplayName() const;
    Int rva003FF145(const BfmeNetAddress *other) const;

    void unAccept();
    void setMapAvailability(Bool hasMap);

private:
    // +0x00 vtable (virtual reset above).
    Int m_state;                    // +0x04
    Bool m_isAccepted;              // +0x08
    Bool m_hasMap;                  // +0x09
    char m_pad0A[2];                // +0x0A
    Int m_color;                    // +0x0C
    Int m_startPos;                 // +0x10
    char m_pad14[4];                // +0x14
    Int m_playerTemplate;           // +0x18
    Int m_teamNumber;               // +0x1C
    char m_pad20[4];                // +0x20
    Int m_origColor;                // +0x24
    Int m_origStartPos;             // +0x28
    Int m_origPlayerTemplate;       // +0x2C
};

class GameInfo
{
public:
    // Retail reaches getLocalSlotNum through vtable slot 13 (+0x34). The
    // twelve middle slots have not yet been reconstructed in this TU.
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1c() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void slot28() = 0;
    virtual void slot2c() = 0;
    virtual void slot30() = 0;
    virtual Int getLocalSlotNum() const = 0;
    virtual void slot38() = 0;
    virtual void slot3c() = 0;
    virtual void slot40() = 0;
    virtual void slot44() = 0;
    virtual void slot48() = 0;
    virtual Bool rva003FF3B5() = 0;

    const GameSlot *getConstSlot(Int slotNum) const;

    virtual Bool isSkirmish();
    Bool isColorTaken(Int colorIdx, Int slotToIgnore) const;
    void setSlotPointer(Int index, GameSlot *slot);

private:
    // vfptr (+0x00) then pads so the slot array lands at +0x18.
    // +0x10 is the in-game flag retail tests, +0x38 holds the local address.
    char m_pad00[0x0C];
    Bool m_inGame;                  // +0x10
    char m_pad01[0x07];
    GameSlot *m_slot[MAX_SLOTS];    // +0x18
    BfmeNetAddress m_localAddr;     // +0x38
};

extern GameInfo *TheGameInfo;

// ?getConstSlot@GameInfo@@QBEPBVGameSlot@@H@Z
const GameSlot *GameInfo::getConstSlot(Int slotNum) const
{
    if (slotNum < 0 || slotNum >= MAX_SLOTS)
        return 0;
    return m_slot[slotNum];
}

// ?setSlotPointer@GameInfo@@QAEXHPAVGameSlot@@@Z @ 0x003FF332 (24B).
// Identity: Zero Hour GameInfo.cpp donor; target range guard and m_slot store match.
void GameInfo::setSlotPointer(Int index, GameSlot *slot)
{
    if (index < 0 || index >= MAX_SLOTS)
        return;
    m_slot[index] = slot;
}

// The ally helper and the four apparent members must live in this TU
// together with getConstSlot above: same-TU visibility into getConstSlot
// (which preserves EDX) is what keeps the index loop in registers and
// picks the EDI slot convention with bare calls. Calling through the
// argless pin instead homes `this` to ESI and never matches.
static Int getSlotIndex(const GameSlot *slot)
{
    for (Int i = 0; i < MAX_SLOTS; ++i)
    {
        if (TheGameInfo->getConstSlot(i) == slot)
            return i;
    }
    return -1;
}

// ?isSlotLocalAlly@@YA_NPBVGameSlot@@@Z
static Bool isSlotLocalAlly(const GameSlot *slot)
{
    Int slotIndex = getSlotIndex(slot);
    Int localIndex = TheGameInfo->getLocalSlotNum();
    const GameSlot *localSlot = TheGameInfo->getConstSlot(localIndex);

    // if either doesn't exist, not an ally
    if (slotIndex < 0 || localIndex < 0)
        return false;

    // if slot is us, ally
    if (slotIndex == localIndex)
        return true;

    // if slot is same team as us, ally
    if (slot->getTeamNumber() == localSlot->getTeamNumber() && slot->getTeamNumber() >= 0)
        return true;

    // if we're an observer, we see all
    if (localSlot->getOriginalPlayerTemplate() == PLAYERTEMPLATE_OBSERVER)
        return true;

    // nope
    return false;
}


// ?getApparentPlayerTemplate@GameSlot@@QBEHXZ
Int GameSlot::getApparentPlayerTemplate() const
{
    if (TheMultiplayerSettings && TheMultiplayerSettings->showRandomPlayerTemplate() &&
        !isSlotLocalAlly(this))
    {
        return m_origPlayerTemplate;
    }
    return m_playerTemplate;
}

// ?getApparentColor@GameSlot@@QBEHXZ
Int GameSlot::getApparentColor() const
{
    if (TheMultiplayerSettings && m_origPlayerTemplate == PLAYERTEMPLATE_OBSERVER)
        return TheMultiplayerSettings->getColor(PLAYERTEMPLATE_OBSERVER)->getColor();

    if (TheMultiplayerSettings && TheMultiplayerSettings->showRandomColor() &&
        !isSlotLocalAlly(this))
    {
        return m_origColor;
    }
    return m_color;
}

// ?getApparentStartPos@GameSlot@@QBEHXZ
Int GameSlot::getApparentStartPos() const
{
    if (TheMultiplayerSettings && TheMultiplayerSettings->showRandomStartPos() &&
        !isSlotLocalAlly(this))
    {
        return m_origStartPos;
    }
    return m_startPos;
}

// ?getApparentPlayerTemplateDisplayName@GameSlot@@QBE?AVUnicodeString@@XZ
UnicodeString GameSlot::getApparentPlayerTemplateDisplayName() const
{
    if (TheMultiplayerSettings && TheMultiplayerSettings->showRandomPlayerTemplate() &&
        m_origPlayerTemplate == PLAYERTEMPLATE_RANDOM && !isSlotLocalAlly(this))
    {
        return TheGameText->fetch("GUI:Random");
    }
    else if (m_origPlayerTemplate == PLAYERTEMPLATE_OBSERVER)
    {
        return TheGameText->fetch("GUI:Observer");
    }
    if (m_playerTemplate < 0)
    {
        return TheGameText->fetch("GUI:Random");
    }
    return ThePlayerTemplateStore->getNthPlayerTemplate(m_playerTemplate)->getDisplayName();
}

// ?unAccept@GameSlot@@QAEXXZ
inline void GameSlot::unAccept()
{
    if (isHuman())
    {
        m_isAccepted = false;
    }
}

// ?setMapAvailability@GameSlot@@QAEX_N@Z
void GameSlot::setMapAvailability(Bool hasMap)
{
    if (isHuman())
    {
        m_hasMap = hasMap;
    }
}

// ?isSkirmish@GameInfo@@UAE_NXZ
Bool GameInfo::isSkirmish()
{
    Bool sawAI = false;

    for (Int i = 0; i < MAX_SLOTS; ++i)
    {
        if (i == getLocalSlotNum())
            continue;

        if (getConstSlot(i)->isHuman())
            return false;

        if (getConstSlot(i)->isAI())
        {
            // BFME2 diverges from the ZH donor here: an allied AI no longer
            // aborts the scan, it is simply skipped and only a non-allied AI
            // marks the game as skirmish.
            if (isSlotLocalAlly(getConstSlot(i)))
                continue;
            sawAI = true;
        }
    }
    return sawAI;
}

// ?isColorTaken@GameInfo@@QBE_NHH@Z @0x003FF34A (42B):
// GameInfo::isColorTaken. BFME1 GameInfo.cpp donor verbatim: scan 8 slots
// via getConstSlot, inline color at +0x0C, ignore one slot.
Bool GameInfo::isColorTaken(Int colorIdx, Int slotToIgnore) const
{
    for (Int i = 0; i < MAX_SLOTS; ++i)
    {
        const GameSlot *slot = getConstSlot(i);
        if (slot && slot->getColor() == colorIdx && i != slotToIgnore)
            return true;
    }
    return false;
}

// ?rva003FF3B5@GameInfo@@UAE_NXZ @0x003FF3B5 (46B):
// GameInfo slot 19 (+0x4C) of vtable 0x008193C8 (the rowed copy ctor
// ??0Rva00382FA7 stores the same vtable; its +0x18[8] block matches
// m_slot[8] at +0x18). Scans 8 slots via rowed getConstSlot, skipping the
// local slot reached through slot 13 (+0x34, getLocalSlotNum); inline
// isHuman (m_state == 6 at +0x04) decides. Retail has no null check.
Bool GameInfo::rva003FF3B5()
{
    for (Int i = 0; i < MAX_SLOTS; ++i)
    {
        if (i == getLocalSlotNum())
            continue;
        if (getConstSlot(i)->isHuman())
            return true;
    }
    return false;
}

// GameInfo slot 13 (+0x34) of vtable 0x008193C8. BFME1 GameInfo.cpp donor
// GameInfo::getLocalSlotNum verbatim shape: if not in game (+0x10) return -1,
// else scan 8 slots via rowed getConstSlot and return the first whose
// rowed GameSlot::rva003FF145 matches the local address at +0x38. Retail
// tests only AL of that Int result, so the call is narrowed to byte.
Int GameInfo::getLocalSlotNum() const
{
    if (!m_inGame)
        return -1;
    for (Int i = 0; i < MAX_SLOTS; ++i)
    {
        const GameSlot *slot = getConstSlot(i);
        if (slot == 0)
            continue;
        if ((unsigned char)slot->rva003FF145(&m_localAddr))
            return i;
    }
    return -1;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeGameSlotInlineAnchorGameSlotApparent@@YAXPAVGameSlot@@@Z absent-from-retail
void _bfmeGameSlotInlineAnchorGameSlotApparent(GameSlot *p)
{
    p->unAccept();
}
#pragma inline_depth()
