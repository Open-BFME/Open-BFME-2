// Target facts (code addresses are RVAs; table addresses are VAs): constructor 0x004CCA24 calls SpecialAbilityUpdateModuleData's 0x0044EB54 at 0x004CCA37, then stores its own 0x00C5F6F8 at 0x004CCA4C. Factory 0x00252EE5 allocates 0xDC bytes at 0x00252EF1 and calls 0x004CCA24 at 0x00252F09. The registered parent occupies 0xC8 bytes. The live table has 31 slots, ends at zero 0x00C5F774, and equals the parent's 0x00C3F2A8 in slots 1..30; slot 0 is deleting destructor 0x004CCA9E, which calls 0x004CCABA. No new virtual slots are introduced.
// Target teardown: destructor 0x004CCABA destroys the +0xD8 handle through 0x00360D26 at 0x004CCAD5, then calls the parent's 0x0044ECCE at 0x004CCAE0. It does not store a derived table. The parent restores 0x00C3F2A8 at 0x0044ECDF and Snapshot's 0x00BBB554 at 0x0044ED85; those are base teardown tables. Constructor, virtual destructor, buildFieldParse (0x004CC96D) and friend_newModuleData (0x00252EE5) have ledger rows and remain out of line.
// Target fields: buildFieldParse calls the parent's parser 0x0044ED95 at 0x004CC971 and registers 0x00C5F638 at 0x004CC97D. Its five entries prove DominateRadius +0xC8 (float parser 0x0002EFC0), TriggerFX +0xCC and DominatedFX +0xD0 (FXList parser 0x00338A09), PermanentlyConvert +0xD4 (bool parser 0x0002E850), and AttributeModifierAffects +0xD8 (filter parser 0x00361CA5). Stores 0x004CCA52..0x004CCA66 confirm widths 4/4/4/1; 0x004CCA6C constructs the four-byte Rva003623E5Member handle through 0x003623E5. Retail 0x004CCB0E and 0x004CCBDF use those offsets. Original C++ member names are unknown, so offset placeholders identify the fields.
#pragma once

#ifndef BFME2_DOMINATEENEMYSPECIALPOWERMODULEDATA_H
#define BFME2_DOMINATEENEMYSPECIALPOWERMODULEDATA_H

#include "SpecialAbilityUpdateModuleData.h"
#include "Rva003623E5Member.h"

class FXList;
class INI;

class DominateEnemySpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
    DominateEnemySpecialPowerModuleData();
    virtual ~DominateEnemySpecialPowerModuleData();

    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    float fieldC8;
    const FXList *fieldCC;
    const FXList *fieldD0;
    bool fieldD4;
    Rva003623E5Member fieldD8;
};

#endif
