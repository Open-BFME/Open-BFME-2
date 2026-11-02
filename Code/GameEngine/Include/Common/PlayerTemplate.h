// Target facts: game.dat 1.06, addresses below are RVAs unless marked VA.
// Constructor 0x001FEB8B stores VA 0x00BE1BE8 at +0 (0x001FEBAC), after
// initializing Overridable's +4/+8/+0xC (0x001FEB9C..0x001FEBA9).
// Destructor 0x001FE06A restores the same table at 0x001FE07B and calls
// ~Overridable 0x001E3624 at 0x001FE2EE; that body installs VA 0x00BDDC48.
// VA 0x00BE1BE8 has one slot, deleting destructor 0x001FE772, followed by
// string data at VA 0x00BE1BEC. PlayerTemplate has no other virtual slots.
// The +0x2C table VA 0x00BE1AA0 (store 0x001FEBCA) belongs to the Money
// member, whose destructor restores Snapshot's VA 0x00BBB554 at 0x001FE2CC.
// It has four slots (0x004A10FD, 0x000B3FD0, 0x001FD2AE, 0x003B0E38);
// 0x001FD2AE returns "Money". It is not a PlayerTemplate base or table.
// Parser 0x001FEFEC allocates 0x1DC at 0x001FF03A..0x001FF053 and calls
// 0x001FEB8B. Store lookup 0x001FD3C6 independently uses stride 0x1DC.
// Parser helper 0x001FE70F passes VA 0x00BE2070 at 0x001FE728: its
// 16-byte entries through VA 0x00BE2430 prove the names and offsets below.
// Entries VA 0x00BE20D0..0x00BE2200 prove ten starting strings at +0x48
// and ten 12-byte coordinate records at +0x70. Constructor 0x001FEBC5
// initializes the 16-byte +0x1C record through 0x003B0E83; +0x154 is a
// 16-byte record constructed by 0x003B0E5D, with an AsciiString at +0.
// Getters 0x0023E95E/0x00449B8F prove key +0x10/display name +0x14;
// The four bytes at +0x14 are opaque storage here; UnicodeString is only
// needed by the declared out-of-line return type.
// 0x001FD1FB/0x001FD221/0x001FD23F use strings +0x170/+0x174/+0x1D8;
// 0x001FD234 passes +0x18 to 0x0033A3F4. All are out-of-line ledger rows.
// Copy 0x001FE352 and assignment 0x001FE78E are out of line, currently
// rowed as BfmeObject476; this header does not define replacement copies.
// Donor names: Zero Hour GeneralsMD Common/PlayerTemplate.h supplies the
// accessor names. Retail's INI entries, not the donor's layout, place data.

#pragma once

#ifndef BFME2_COMMON_PLAYERTEMPLATE_H
#define BFME2_COMMON_PLAYERTEMPLATE_H

#include "Overridable.h"

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
class UnicodeString;
class INI;
class Image;
enum NameKeyType;

class PlayerTemplate : public Overridable
{
public:
    PlayerTemplate();
    PlayerTemplate(const PlayerTemplate &other);
    PlayerTemplate &operator=(const PlayerTemplate &other);
    virtual ~PlayerTemplate();

    AsciiString getName() const;
    UnicodeString getDisplayName() const;
    const Image *getFlagWaterMarkImage() const;
    const Image *getEnabledImage() const;
    int rva001FD234() const;
    const Image *rva001FD23F() const;

    NameKeyType getNameKey() const { return m_nameKey; }
    void setNameKey(NameKeyType key) { m_nameKey = key; }
    const AsciiString &getSide() const { return m_side; }
    bool isObserver() const { return m_observer; }
    bool isPlayableSide() const { return m_playableSide; }
    const AsciiString &getSpecialPowerShortcutCommandSet() const { return m_specialPowerShortcutCommandSet; }
    const AsciiString &getSpecialPowerShortcutWinName() const { return m_specialPowerShortcutWinName; }
    int getSpecialPowerShortcutButtonCount() const { return m_specialPowerShortcutButtonCount; }
    const AsciiString &getBeaconTemplate() const { return m_beaconTemplate; }
    const AsciiString &getDefaultAIType() const { return m_defaultAIType; }

    static void parseStartMoney(INI *, void *, void *, const void *);

protected:
    static void parseProductionCostChange(INI *, void *, void *, const void *);
    static void parseProductionTimeChange(INI *, void *, void *, const void *);
    static void parseProductionVeterancyLevel(INI *, void *, void *, const void *);

public:
    NameKeyType m_nameKey;                          // +0x010
    unsigned int m_unknown14;                       // +0x014
    AsciiString m_side;                              // +0x018
    unsigned char m_unknown1C[0x10];                 // +0x01C
    unsigned char m_startMoney[0x0C];                // +0x02C
    float m_preferredColor[3];                       // +0x038
    AsciiString m_startingBuilding;                  // +0x044
    AsciiString m_startingUnits[10];                 // +0x048
    float m_startingUnitOffsets[10][3];              // +0x070
    unsigned char m_startingUnitTacticalWOTR[0x0C];   // +0x0E8
    unsigned char m_productionCostChanges[0x0C];     // +0x0F4
    unsigned char m_productionTimeChanges[0x14];     // +0x100
    unsigned char m_productionVeterancyLevels[0x0C]; // +0x114
    unsigned char m_intrinsicSciences[0x0C];         // +0x120
    unsigned char m_intrinsicSciencesMP[0x0C];       // +0x12C
    AsciiString m_purchaseScienceCommandSet;         // +0x138
    AsciiString m_purchaseScienceCommandSetMP;       // +0x13C
    AsciiString m_specialPowerShortcutCommandSet;    // +0x140
    AsciiString m_specialPowerShortcutWinName;       // +0x144
    int m_specialPowerShortcutButtonCount;          // +0x148
    AsciiString m_loadScreenMusic;                   // +0x14C
    bool m_observer;                                // +0x150
    bool m_playableSide;                            // +0x151
    unsigned char m_pad152[2];
    unsigned char m_unknown154[0x10];               // +0x154
    AsciiString m_scoreScreenImage;                  // +0x164
    AsciiString m_loadScreenImage;                   // +0x168
    AsciiString m_headWaterMark;                     // +0x16C
    AsciiString m_flagWaterMark;                     // +0x170
    AsciiString m_enabledImage;                      // +0x174
    AsciiString m_sideIconImage;                     // +0x178
    AsciiString m_beaconTemplate;                    // +0x17C
    unsigned char m_initialUpgrades[0x0C];           // +0x180
    AsciiString *m_buildableHeroesMPStart;           // +0x18C
    AsciiString *m_buildableHeroesMPFinish;          // +0x190
    AsciiString *m_buildableHeroesMPEnd;             // +0x194
    unsigned char m_buildableRingHeroesMP[0x0C];     // +0x198
    void *m_lightPointsUpSound;                      // +0x1A4
    void *m_objectiveAddedSound;                     // +0x1A8
    void *m_objectiveCompletedSound;                 // +0x1AC
    AsciiString m_defaultAIType;                     // +0x1B0
    AsciiString m_spellBook;                         // +0x1B4
    AsciiString m_spellBookMP;                       // +0x1B8
    bool m_isEvil;                                  // +0x1BC
    unsigned char m_pad1BD[3];
    AsciiString m_spellStoreCurrentPowerLabel;       // +0x1C0
    AsciiString m_spellStoreMaximumPowerLabel;       // +0x1C4
    void *m_resourceModifierObjectFilter;            // +0x1C8
    unsigned char m_resourceModifierValues[0x0C];    // +0x1CC
    AsciiString m_multiSelectionPortrait;            // +0x1D8
};

#endif
