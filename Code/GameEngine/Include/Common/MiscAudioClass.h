// Target facts (addresses are RVAs): MiscAudio has no virtual functions or bases. MilesAudioManager's constructor pushes sizeof 0xF4 at 0x0005D3B2, calls constructor 0x001ED70C at 0x0005D3D1 and stores the result at +0x14 (0x0005D3E0). Its table VA 0x00BC55B0 slots 78 and 79 both call 0x0057E556, which returns that pointer. INI::parseMiscAudio (0x001ED6EE) calls slot 79 and applies the table at 0x007DF2D0 to it.
// Target facts: constructor 0x001ED70C zeroes 42 owning handles at +0x00..+0xA4, constructs five four-byte handles at +0xA8 (0x001ED7BE..0x001ED7D7, callbacks 0x00326BE6 and 0x0010F149), then zeroes 14 handles at +0xBC..+0xF0. Destructor 0x001ED840 releases these members through 0x00050ED3 and the same array destructor callback; neither body installs a vtable. The non-virtual deleting destructor 0x000510EB calls 0x001ED840. Those lifetime rows are named Rva001ED70C in the ledger.
// Target facts: FieldParse entries 0x007DF2D0..0x007DF690 cover every four-byte offset +0x00..+0xF0, with parser 0x00339900 and a null terminator at 0x007DF6A0. Zero Hour Common/MiscAudio.h supplies the named members below; the retail tokens at table offsets +0x00..+0x40 and +0x80..+0x1A0 establish their BFME2 placement. BFME2-only members and the five-element volume sample array retain neutral offset names. No method row is named MiscAudio.
#pragma once

#ifndef BFME2_MISCAUDIOCLASS_H
#define BFME2_MISCAUDIOCLASS_H

#include "OpaqueRefElement4.h"

struct FieldParse;

struct MiscAudio
{
    static const FieldParse m_fieldParseTable[];

    OpaqueRefElement4 m_radarHarvesterUnderAttackSound;
    OpaqueRefElement4 m_radarStructureUnderAttackSound;
    OpaqueRefElement4 m_radarInfiltrationSound;
    OpaqueRefElement4 m_radarOnlineSound;
    OpaqueRefElement4 m_radarOfflineSound;
    OpaqueRefElement4 m_14;
    OpaqueRefElement4 m_18;
    OpaqueRefElement4 m_1C;
    OpaqueRefElement4 m_defectorTimerTickSound;
    OpaqueRefElement4 m_defectorTimerDingSound;
    OpaqueRefElement4 m_allCheerSound;
    OpaqueRefElement4 m_noCanDoSound;
    OpaqueRefElement4 m_stealthDiscoveredSound;
    OpaqueRefElement4 m_stealthNeutralizedSound;
    OpaqueRefElement4 m_moneyDepositSound;
    OpaqueRefElement4 m_moneyWithdrawSound;
    OpaqueRefElement4 m_buildingDisabled;
    OpaqueRefElement4 m_buildingReenabled;
    OpaqueRefElement4 m_vehicleDisabled;
    OpaqueRefElement4 m_vehicleReenabled;
    OpaqueRefElement4 m_splatterVehiclePilotsBrain;
    OpaqueRefElement4 m_crateHeal;
    OpaqueRefElement4 m_crateShroud;
    OpaqueRefElement4 m_crateFreeUnit;
    OpaqueRefElement4 m_crateMoney;
    OpaqueRefElement4 m_unitPromoted;
    OpaqueRefElement4 m_repairSparks;
    OpaqueRefElement4 m_6C;
    OpaqueRefElement4 m_70;
    OpaqueRefElement4 m_74;
    OpaqueRefElement4 m_78;
    OpaqueRefElement4 m_7C;
    OpaqueRefElement4 m_80;
    OpaqueRefElement4 m_84;
    OpaqueRefElement4 m_88;
    OpaqueRefElement4 m_8C;
    OpaqueRefElement4 m_90;
    OpaqueRefElement4 m_94;
    OpaqueRefElement4 m_98;
    OpaqueRefElement4 m_9C;
    OpaqueRefElement4 m_A0;
    OpaqueRefElement4 m_A4;
    OpaqueRefElement4 m_A8[5];
    OpaqueRefElement4 m_BC;
    OpaqueRefElement4 m_C0;
    OpaqueRefElement4 m_C4;
    OpaqueRefElement4 m_C8;
    OpaqueRefElement4 m_CC;
    OpaqueRefElement4 m_D0;
    OpaqueRefElement4 m_D4;
    OpaqueRefElement4 m_D8;
    OpaqueRefElement4 m_DC;
    OpaqueRefElement4 m_E0;
    OpaqueRefElement4 m_E4;
    OpaqueRefElement4 m_E8;
    OpaqueRefElement4 m_EC;
    OpaqueRefElement4 m_F0;
};

typedef char MiscAudioSizeCheck[sizeof(MiscAudio) == 0xF4 ? 1 : -1];

#endif
