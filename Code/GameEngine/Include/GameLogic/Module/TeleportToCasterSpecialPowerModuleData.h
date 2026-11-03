// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x004CD34E calls SpecialAbilityUpdateModuleData's 0x0044EB54 at 0x004CD351 with the same this, then stores 0x00C5F778 at +0 (0x004CD367). Factory 0x00253092 allocates 0xDC at 0x0025309E and calls 0x004CD34E at 0x002530B6. The registered parent occupies 0xC8 bytes (its factory 0x0024A882 allocates 0xC8 at 0x0024A88E); the first derived field is +0xC8.
// The live table 0x00C5F778 has 31 slots and ends at non-code 0x00C5F7F4. Slot 0 is deleting destructor 0x004AD538, which calls 0x004C6CC1; that body jumps to parent destructor 0x0044ECCE. Slots 1..30 equal the parent's 0x00C3F2A8 table: 1/2/3 are 0x000B3FD0/0x00065212/0x0047A69C, 4..13 and 15 return false (0x0047A699), 14 returns AsciiString (0x000B69A1), 16..29 return null (0x000D43D0), and 30 returns true (0x0050B5C6). This class adds no virtual slots.
// Parent destructor 0x0044ECCE restores 0x00C3F2A8 at 0x0044ECDF and Snapshot's four-slot 0x00BBB554 at 0x0044ED85. These teardown tables describe the base subobjects; neither replaces the derived live table. The constructor and virtual destructor are declared out of line.
// buildFieldParse 0x004CD389 calls the parent's parser 0x0044ED95 and passes 0x00C5FAE0 to MultiIniFieldParse::add. Its five 0x10-byte entries prove Radius +0xC8, MinDestinationRadius +0xCC, MaxDestinationRadius +0xD0 (parseReal 0x0002EFC0), TriggerFX +0xD4 and TargetFX +0xD8 (parseFXList 0x00338A09, storing const FXList*). Constructor stores at 0x004CD359/0x004CD360 clear the two pointers; 0x004CD36D/0x004CD375/0x004CD37D zero the three floats. The INI tokens identify roles, not original C++ member spellings, so members retain offset names.
// Ledger rows prove the constructor, buildFieldParse, and friend_newModuleData (0x00253092); the factory passes buildFieldParse at 0x002530CC. The parent's constructor, parser, table and extent establish SpecialAbilityUpdateModuleData inheritance independently of private declarations.
#pragma once

#ifndef BFME2_TELEPORTTOCASTERSPECIALPOWERMODULEDATA_H
#define BFME2_TELEPORTTOCASTERSPECIALPOWERMODULEDATA_H

#include "SpecialAbilityUpdateModuleData.h"

class FXList;
class INI;

class TeleportToCasterSpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
    TeleportToCasterSpecialPowerModuleData();
    virtual ~TeleportToCasterSpecialPowerModuleData();

    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    float fieldC8;
    float fieldCC;
    float fieldD0;
    const FXList *fieldD4;
    const FXList *fieldD8;
};

#endif
