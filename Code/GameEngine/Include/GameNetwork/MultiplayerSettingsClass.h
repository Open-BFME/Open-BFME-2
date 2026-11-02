/* Target facts (BFME2 game.dat; code addresses are RVAs, tables are VAs): constructor 0x003811D8 calls SubsystemInterface 0x001B4E63 at 0x003811E9 and installs 0x00C191B8 at +0 (0x003811F5). The parent initializes byte +4 and AsciiString +8, occupying 0x0C bytes. The derived table has fourteen slots: 0 deleting destructor 0x00381277; 1/3/8/9/10/12 empty 0x000B3FD0; 2 loadIniFilesFromLegend 0x001B5384; 4/11 false-ret-4 0x005CB9FF; 5 false 0x0047A699; 6 zero 0x000D43D0; 7/13 ret-4 0x0047A69C. UTF-16 text starts at 0x00C191F0, so its word 0x0065006D is not a fifteenth slot. Destructor 0x00381293 releases +0x84/+0x44, destroys the tree at +0x34 and calls ~SubsystemInterface 0x001B4E74 at 0x003812D4; the parent restores 0x00BD77A0. That table belongs to the parent, not MultiplayerSettings. Slot zero calls 0x00381293 at 0x0038127A, proving the destructor virtual even without a derived-vptr restore.
Constructor calls 0x003811FB/0x00381207/0x00381216 construct the map at +0x34 and two MultiplayerColorDefinition values at +0x44/+0x84. INI allocation 0x001EF37B pushes 0xC4 before calling this constructor at 0x001EF393, proving sizeof 0xC4. Constructor stores 0x0038121B..0x00381264 zero +0x0C/+0x14/+0x40, set +0x10 to 10000 and +0x18 to 3, set bytes +0x1C..+0x1F, and initialize five credits at +0x20..+0x30. FieldParse 0x00C18FB0 names those five credits VeryLow through VeryHigh, countdown +0x14, beacons +0x18, shroud +0x1C and random-template/start/color +0x1D/+0x1E/+0x1F. getColor 0x00381373 returns +0x84 for -1 and +0x44 for -2; 0x00381392..0x0038139B refill cached count +0x40 from map count +0x38. The map constructor 0x003811A2 and destructor cleanup 0x0077F310 establish its out-of-line lifetime. Map bytes +0x34..+0x3F and color values +0x44..+0x83/+0x84..+0xC3 use opaque storage here; their construction and destruction remain in the declared out-of-line methods, and no container or color copy semantics are asserted.
The initSubsystem<MultiplayerSettings> ledger row 0x00229E70 spells the class-key as VMultiplayerSettings. The ledger declares getColor 0x00381373, findMultiplayerColorDefinitionByName 0x00380E34 and newMultiplayerColorDefinition 0x003813B7. INI::parseMultiplayerColorDefinition 0x001EF3BF calls both name methods; INI::parseMultiplayerSettingsDefinition pushes FieldParse 0x00C18FB0 at 0x001EF3A8. These methods and the constructor/destructor remain declared out of line. Names and inline accessors follow Zero Hour GeneralsMD Common/MultiplayerSettings.h, reconciled to the target offsets above; +0x0C/+0x10 have neutral names. The registered parent's fourteen-slot form supplies the inherited virtuals. */

#pragma once
#ifndef CANONICAL_MULTIPLAYERSETTINGSCLASS_H
#define CANONICAL_MULTIPLAYERSETTINGSCLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

struct FieldParse;
class MultiplayerColorDefinition;

class MultiplayerSettings : public SubsystemInterface
{
public:
    MultiplayerSettings();
    virtual ~MultiplayerSettings();

    virtual void init() {}
    virtual void reset() {}
    virtual void update() {}

    static const FieldParse m_multiplayerSettingsFieldParseTable[];
    const FieldParse *getFieldParse() const { return m_multiplayerSettingsFieldParseTable; }
    MultiplayerColorDefinition *getColor(int which);
    MultiplayerColorDefinition *findMultiplayerColorDefinitionByName(AsciiString name);
    MultiplayerColorDefinition *newMultiplayerColorDefinition(AsciiString name);

    int getStartCountdownTimerSeconds() { return m_startCountdownTimerSeconds; }
    int getMaxBeaconsPerPlayer() { return m_maxBeaconsPerPlayer; }
    bool isShroudInMultiplayer() const { return m_isShroudInMultiplayer; }
    bool showRandomPlayerTemplate() const { return m_showRandomPlayerTemplate; }
    bool showRandomStartPos() const { return m_showRandomStartPos; }
    bool showRandomColor() const { return m_showRandomColor; }
    int getNumColors()
    {
        if (m_numColors == 0)
            m_numColors = slot38;
        return m_numColors;
    }

    int slot0C; // +0x0C
    int slot10; // +0x10
    int m_startCountdownTimerSeconds; // +0x14
    int m_maxBeaconsPerPlayer; // +0x18
    bool m_isShroudInMultiplayer; // +0x1C
    bool m_showRandomPlayerTemplate; // +0x1D
    bool m_showRandomStartPos; // +0x1E
    bool m_showRandomColor; // +0x1F
    int m_initialCredits[5]; // +0x20
    void *slot34; // +0x34, color-map storage
    int slot38; // +0x38, color-map node count
    int field3C; // +0x3C, opaque remainder of the color map
    int m_numColors; // +0x40
    unsigned char slot44[0x40]; // +0x44, observer-color storage
    unsigned char slot84[0x40]; // +0x84, random-color storage
};

extern MultiplayerSettings *TheMultiplayerSettings;

#endif
