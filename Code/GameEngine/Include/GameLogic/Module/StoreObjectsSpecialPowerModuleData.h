// Target facts (code addresses are RVAs; table addresses are VAs): constructor 0x004CD8FB calls SpecialAbilityUpdateModuleData's 0x0044EB54 at 0x004CD8FE, installs 0x00C5F778 at +0 (0x004CD906), and stores float zero at +0xC8 (0x004CD90C). Factory 0x00253121 allocates 0xCC bytes at 0x0025312D and calls this constructor at 0x00253145. The registered parent's extent is 0xC8; this class adds one four-byte field and no virtual slots.
// Live table 0x00C5F778 has 31 slots and ends at non-code 0x00C5F7F4. Slot 0 is deleting destructor 0x004AD538, which calls 0x004C6CC1; that body jumps to parent destructor 0x0044ECCE, which restores 0x00C3F2A8 at 0x0044ECDF and Snapshot's 0x00BBB554 at 0x0044ED85. These are parent teardown tables. Slots 1..30 equal the parent's 0x00C3F2A8 table: 0x000B3FD0, 0x00065212, 0x0047A69C, false at 4..13/15 (0x0047A699), AsciiString at 14 (0x000B69A1), null at 16..29 (0x000D43D0), and true at 30 (0x0050B5C6). Constructor and virtual destructor remain out of line.
// buildFieldParse 0x004CD918 calls the parent's 0x0044ED95 at 0x004CD91C, then adds 0x00C5FB9C: its sole entry is Radius, INI::parseReal (0x0002EFC0), offset +0xC8, followed by a zero sentinel. The parser's 0x0002EFD9 stores a four-byte float. The field's original C++ name is unknown. Ledger rows establish buildFieldParse and friend_newModuleData; factory 0x0025315B passes the former to INI initialization. ModuleFactory::init loads the StoreObjectsSpecialPower literal at VA 0x00BF4B50 (0x0025ACAB), pushes this data factory at 0x0025ACBD, and registers it at 0x0025ACD0.
#pragma once

#ifndef BFME2_STOREOBJECTSSPECIALPOWERMODULEDATA_H
#define BFME2_STOREOBJECTSSPECIALPOWERMODULEDATA_H

#include "SpecialAbilityUpdateModuleData.h"

class StoreObjectsSpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
    StoreObjectsSpecialPowerModuleData();
    virtual ~StoreObjectsSpecialPowerModuleData();

    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    float fieldC8;
};

#endif
