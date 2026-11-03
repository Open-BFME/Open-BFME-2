// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x004CCD34 calls SpecialAbilityUpdateModuleData's 0x0044EB54 at 0x004CCD37, clears dwords +0xC8/+0xCC at 0x004CCD44/0x004CCD4B, stores 0x00C5F778 at +0 at 0x004CCD52, and stores a float at +0xD0 at 0x004CCD58. Factory 0x00252F74 allocates 0xD4 bytes at 0x00252F80 and calls the constructor at 0x00252F98. The registered parent occupies 0xC8 bytes; this is not the 0x7C-byte SpecialPowerModuleData.
// The live table 0x00C5F778 has 31 slots and ends at non-code 0x00C5F7F4. Slot 0 is deleting destructor 0x004AD538, which calls 0x004C6CC1; that five-byte destructor jumps to the parent's 0x0044ECCE. Slots 1..30 equal the parent's 0x00C3F2A8 table: 0x000B3FD0, 0x00065212, 0x0047A69C, false at 4..13/15 (0x0047A699), an AsciiString result at 14 (0x000B69A1), null at 16..29 (0x000D43D0), true at 30 (0x0050B5C6). No virtual slots are added.
// Parent destructor 0x0044ECCE restores 0x00C3F2A8 at 0x0044ECDF and Snapshot's four-slot 0x00BBB554 at 0x0044ED85. These are base teardown tables, not this class's live table. The constructor and virtual destructor are declared out of line.
// buildFieldParse 0x004CCD64 calls the parent's 0x0044ED95 and passes 0x00C5F810 to MultiIniFieldParse::add at 0x004CCD79. Its three 0x10-byte entries prove TriggerFX +0xC8 and CursedFX +0xCC are const FXList pointers (INI::parseFXList, 0x00338A09), and CursePercentage +0xD0 is float (INI::parsePercentToReal, 0x0002F1BA); 0x00C5F840 is the zero sentinel. Retail 0x004CCEDB passes +0xCC to FXList::doFXObj and 0x004CD002 passes +0xC8 to FXList::doFXPos. The percentage member name follows the retail CursePercentage token; the FX members retain neutral offset names.
// Ledger rows name the constructor, buildFieldParse, and friend_newModuleData (0x00252F74). The factory pushes buildFieldParse's VA at 0x00252FAE and calls INI::initFromINIMultiProc at 0x00252FB4. The shared destructor and table do not imply identical derived types: this factory's 0xD4 allocation and three parse entries identify this layout.
#pragma once

#ifndef BFME2_CURSESPECIALPOWERMODULEDATA_H
#define BFME2_CURSESPECIALPOWERMODULEDATA_H

#include "SpecialAbilityUpdateModuleData.h"

class FXList;

class CurseSpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
    CurseSpecialPowerModuleData();
    virtual ~CurseSpecialPowerModuleData();

    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    const FXList *m_C8;
    const FXList *m_CC;
    float m_cursePercentage;
};

#endif
