// Target facts (code addresses are RVAs, tables are VAs): constructor 0x002575C2 stores 0x00BF4128 at 0x002575E4; factory 0x0025769F requests 0x174 bytes at 0x002576AB and calls it at 0x002576C3. The 31-slot table ends at the zero word 0x00BF41A4. Slot 0 is deleting destructor 0x00257653, which calls destructor 0x0025766F at 0x00257656. That destructor destroys vector<AsciiString> at +0x20 through 0x0002CC70, then restores Snapshot's four-slot 0x00BBB554 at 0x0025768F. This is base teardown; the live class is polymorphic and both lifetime methods remain out of line.
// Target facts: slots 1..30 match ModuleData's registered interface (table 0x00C549F8): 1 is 0x000B3FD0, 2 is 0x00065212 returning the shared ModuleData name at 0x00BC5AFC, 3 is 0x0047A69C, 4..13 and 15 are false at 0x0047A699, 14 is the AsciiString returner 0x000B69A1, 16..29 are null at 0x000D43D0, and 30 is true at 0x0050B5C6. ModuleFactory writes the tag at +4 at 0x00257237; first derived data starts at +8. ModuleData inheritance represents this eight-byte prefix and shared interface; the original intermediate base name is not established by these bytes.
// Target facts: FieldParse table 0x00BF0200 names SpawnNumber/+8, SpawnReplaceDelay/+0xC, InitialBurst/+0x10, OneShot/+0x14, CanReclaimOrphans/+0x15, AggregateHealth/+0x16, ExitByBudding/+0x17, SpawnedRequireSpawner/+0x18, RespectCommandLimit/+0x19, PropagateDamageTypesToSlavesWhenExisting/+0x1C, SpawnTemplateName/+0x20, FadeInTime/+0x16C, KillSpawnsBasedOnModelConditionState/+0x170, ShareUpgrades/+0x171 and SpawnInsideBuilding/+0x172. Constructor calls at 0x002575EA/0x002575F6/0x002575FE initialize the 12-byte vector/+0x20, DieMuxData/+0x2C and 0x110-byte Rva0025342CMember/+0x5C. Rowed parser 0x00253542 adds these member tables at +0x5C/+0x2C and the Spawn table; factory 0x002576DF passes that parser to INI. Zero Hour SpawnBehavior.h supplies the matching member spellings, not BFME2 offsets.
#pragma once

#ifndef BFME2_SPAWNBEHAVIORMODULEDATA_H
#define BFME2_SPAWNBEHAVIORMODULEDATA_H

#include "../../Common/ModuleData.h"
#include "DieMuxData.h"
#include "Rva0025342CMember.h"

class INI;
class MultiIniFieldParse;

class SpawnBehaviorModuleData : public ModuleData
{
public:
    SpawnBehaviorModuleData();
    virtual ~SpawnBehaviorModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    int m_spawnNumberData;
    int m_spawnReplaceDelayData;
    int m_initialBurst;
    bool m_isOneShotData;
    bool m_canReclaimOrphans;
    bool m_aggregateHealth;
    bool m_exitByBudding;
    bool m_spawnedRequireSpawner;
    bool m_respectCommandLimit;
    unsigned int m_damageTypesToPropagateToSlaves;
    unsigned char m_storage20[0x0C];
    DieMuxData m_dieMuxData;
    Rva0025342CMember m_slot5C;
    unsigned int m_fadeInTime;
    bool m_killSpawnsBasedOnModelConditionState;
    bool m_shareUpgrades;
    bool m_spawnInsideBuilding;
};

#endif
