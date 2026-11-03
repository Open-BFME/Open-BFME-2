// Target facts: TeamTemplateInfo ctor RVA 0x003A26E6 constructs seven records at +4 using ctor RVA 0x0039EA9C, dtor RVA 0x0039EAB7 and stride 0x18 (0x003A26F9..0x003A2716); its dtor repeats count 7 and stride 0x18 at 0x0039EBB0..0x0039EBC1. sizeof this record is 0x18.
// Record ctor RVA 0x0039EA9C stores dwords +0/+4/+0xC/+0x10 = 0, +8 = 1 and +0x14 = -1; dtor RVA 0x0039EAB7 releases strings at +0x10/+0xC through RVA 0x00036410. This record has no base, vptr or virtual functions; VA 0x00C1AE70 in the enclosing ctor and VA 0x00BBB554 in its dtor belong to TeamTemplateInfo and Snapshot at enclosing +0, outside the record.
// Loader RVA 0x0039FEBB uses keys at VA 0x00DBDA1C/24/2C/34/14 (strings VA 0x00C08A98/8AAC/8AC0/8ADC/8A88: teamUnitMinCount1, teamUnitMaxCount1, teamUnitExperienceLevel1, teamUnitUpgradeList1, teamUnitType1); stores at RVA 0x003A000F/001C/002C and string assignments at 0x003A0041/0057 prove minUnits +0, maxUnits +4, experience +8, upgrades +0xC and unitThingName +0x10. Fields +8/+0xC/+0x14 keep neutral names; no ledger method is named TCreateUnitsInfo.
#pragma once

#ifndef BFME2_TCREATEUNITSINFO_H
#define BFME2_TCREATEUNITSINFO_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct TCreateUnitsInfo
{
    int minUnits;
    int maxUnits;
    int m_08;
    AsciiString m_0C;
    AsciiString unitThingName;
    int m_14;
};

typedef char TCreateUnitsInfoSizeCheck[sizeof(TCreateUnitsInfo) == 0x18 ? 1 : -1];

#endif
