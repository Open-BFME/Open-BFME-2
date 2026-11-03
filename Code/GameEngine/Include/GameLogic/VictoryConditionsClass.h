// Target facts (code addresses are RVAs; tables are VAs):
// Constructor 0x0042017F calls 0x0041FDF8 at +0, then stores 0x00C3BA28 at 0x0042019C. Destructor 0x004201FA stores that table at 0x0042020B, calls 0x00420110, restores the base table 0x00C3B988 at 0x00420220, and calls ~SubsystemInterface 0x001B4E74. Base constructor 0x0041FDF8 calls SubsystemInterface 0x001B4E63, clears +0x0C, and installs 0x00C3B988; base destructor 0x0041FE0E restores it. These are distinct derived and base lifetimes, not competing class tables. Factory 0x00420353 pushes 0x94 at 0x0042035E and calls the constructor at 0x00420377: sizeof 0x94, base extent 0x10, one primary vptr, no secondary or virtual base.
// Table 0x00C3B988 has 31 slots, ending before the string at 0x00C3BA04; 1, 9, 10 and 14-30 are __purecall 0x0003B810. Table 0x00C3BA28 has 32 slots, ending before the string at 0x00C3BAA8. Slots 0-13 retain SubsystemInterface's layout, overriding 0 (0x00420238), 1 (0x000D20D6, dispatch to slot 9), 9 (0x0041FE86) and 10 (0x00420388). Slots 14-19 are the named rows at 0x0041FEEB, 0x0041FF6E, 0x0042090C, 0x0041FFAD, 0x0042008F and 0x004200CB. Slots 20-22 are 0x004200FD, 0x004201CE and 0x0036750C; their names and field meanings follow Zero Hour's VictoryConditions declarations. Slots 23-31 are 0x00420254, 0x00420110, 0x004201D5, 0x00420017, 0x004201E0, 0x004201ED, 0x00094ADC, 0x00094AE3 and 0x0041FE63. Slots 23/24 have separately declared nonvirtual ledger spellings; the unnamed virtual interfaces keep neutral names. Slot 26 and 31 names come from their virtual ledger rows. The nonvirtual testDefeat row is 0x004207D4.
// Constructor stores prove byte +0x10, dword +0x14/+0x8C and bytes +0x90/+0x91. Reset 0x0041FE86 writes twenty dwords at +0x18 and twenty bytes at +0x70, -1 at +0x68, dwords +0x0C/+0x6C/+0x88/+0x8C and bytes +0x84/+0x85/+0x86/+0x90/+0x91. Cache helper 0x00420017 stores Player pointers at +0x18, counts them at +0x8C and sets the local index +0x68. Slots 20-22 read +0x84/+0x86, +0x86 and +0x6C; 25 reads byte +0x70[index], 27/28 write +0x90/+0x91, and 29/30 read them. The timeout body 0x0041FE63 reads +0x10/+0x14 and dispatches slot 24; 0x00420110 clears +0x10, while 0x00420254 sets it and records timeGetTime at +0x14. Zero Hour's interface and implementation supply m_victoryConditions, m_players, m_localSlotNum, m_endFrame, m_isDefeated, m_localPlayerDefeated, m_singleAllianceRemaining and m_isObserver names; other fields keep offset names. No Snapshot base or Snapshot name slot is present.

#pragma once
#ifndef BFME2_VICTORYCONDITIONSCLASS_H
#define BFME2_VICTORYCONDITIONSCLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Player;

class Rva0041FE0E : public SubsystemInterface
{
public:
    Rva0041FE0E();
    virtual ~Rva0041FE0E();

    virtual bool hasAchievedVictory(Player *player) = 0;
    virtual bool hasBeenDefeated(Player *player) = 0;
    virtual bool hasSinglePlayerBeenDefeated(Player *player) = 0;
    virtual void cachePlayerPtrs() = 0;
    virtual bool isLocalAlliedVictory() = 0;
    virtual bool isLocalAlliedDefeat() = 0;
    virtual bool isLocalDefeat() = 0;
    virtual bool amIObserver() = 0;
    virtual unsigned int getEndFrame() = 0;
    virtual void slot23(const AsciiString &, bool, const AsciiString &, const AsciiString &) = 0;
    virtual void slot24() = 0;
    virtual unsigned char slot25(int) const = 0;
    virtual bool rva00420017(Player *player) = 0;
    virtual void slot27(unsigned char) = 0;
    virtual void slot28(unsigned char) = 0;
    virtual unsigned char slot29() const = 0;
    virtual unsigned char slot30() const = 0;

    int m_victoryConditions;
};

class VictoryConditions : public Rva0041FE0E
{
public:
    VictoryConditions();
    virtual ~VictoryConditions();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual bool hasAchievedVictory(Player *player);
    virtual bool hasBeenDefeated(Player *player);
    virtual bool hasSinglePlayerBeenDefeated(Player *player);
    virtual void cachePlayerPtrs();
    virtual bool isLocalAlliedVictory();
    virtual bool isLocalAlliedDefeat();
    virtual bool isLocalDefeat();
    virtual bool amIObserver();
    virtual unsigned int getEndFrame();
    virtual void slot23(const AsciiString &, bool, const AsciiString &, const AsciiString &);
    virtual void slot24();
    virtual unsigned char slot25(int) const;
    virtual bool rva00420017(Player *player);
    virtual void slot27(unsigned char);
    virtual void slot28(unsigned char);
    virtual unsigned char slot29() const;
    virtual unsigned char slot30() const;
    virtual void rva0041FE63();

    void rva00420110();
    void rva00420254(const AsciiString &, bool, const AsciiString &, const AsciiString &);
    bool testDefeat(Player *player);

    bool m_10;
    unsigned int m_14;
    Player *m_players[20];
    int m_localSlotNum;
    unsigned int m_endFrame;
    bool m_isDefeated[20];
    bool m_localPlayerDefeated;
    bool m_singleAllianceRemaining;
    bool m_isObserver;
    int m_field88;
    int m_8C;
    bool m_90;
    bool m_91;
};

typedef char VictoryConditionsBaseSize[(sizeof(Rva0041FE0E) == 0x10) ? 1 : -1];
typedef char VictoryConditionsSize[(sizeof(VictoryConditions) == 0x94) ? 1 : -1];

#endif
