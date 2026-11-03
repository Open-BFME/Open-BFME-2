// Target facts (code addresses are RVAs, table addresses are VAs): constructor 0x0045324E stores 0x00C40090 at 0x00453263; destructor 0x00453315 stores it at 0x00453326 before member cleanup, then restores Snapshot's 0x00BBB554 at 0x00453386 (Snapshot constructor 0x000053A6 and destructor 0x0049B47C use that table). The live table has 31 slots, ending at 0x00C4010C: slot 0 is the deleting destructor 0x004534D9, which calls 0x00453315; slots 1..30 equal ModuleData's tables 0x00C4ED70 and 0x00C549F8. There are no additional virtual slots. The inherited slot-2 getter 0x00065212 returns "ModuleData" at 0x00BC5AFC.
// Target extent and identity: factory 0x0024A9D5 allocates 0x4C at 0x0024A9E1 and calls the constructor at 0x0024A9F6; registration 0x00257D3B..0x00257D63 pairs it with "GettingBuiltBehavior" at 0x00BF5CF4. ModuleFactory stores the module tag at +4 (0x00257237), so the registered ModuleData base occupies +0..+7 and derived fields begin at +8. The constructor, virtual destructor, buildFieldParse (0x00453396) and friend_newModuleData (0x0024A9D5) are rowed out-of-line methods; buildFieldParse passes 0x00C402A0 at 0x0045339C.
// Target fields: the 17 records at 0x00C402A0..0x00C403B0 prove the configuration-derived names and offsets below. Constructor stores prove one-byte flags at +0x1C/+0x2C/+0x48, four-byte floats at +0x20/+0x24/+0x30/+0x34/+0x38/+0x3C/+0x44, and null words at +8/+0xC/+0x10/+0x14/+0x18/+0x28. Destructor calls 0x00050ED3 on the non-null +0x10/+0xC/+8 pointers, proving OpaqueRefElement4 ownership, and 0x00036410 on the strings at +0x18/+0x14. The +0x40 ObjectFilter handle is constructed through 0x003623E5 (0x00453283..0x00453292) and destroyed through 0x00360D26 (0x0045332C..0x00453336); its registered header supplies its four-byte representation. INI parsers prove AsciiString, bool, float and WeaponTemplate-pointer types; tail alignment rounds +0x49 to 0x4C. No original C++ field spelling is asserted.
#pragma once

#ifndef BFME2_GETTINGBUILTBEHAVIORMODULEDATA_H
#define BFME2_GETTINGBUILTBEHAVIORMODULEDATA_H

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../Common/ModuleData.h"
#include "../../Common/OpaqueRefElement4.h"
#include "../ObjectFilter.h"

class INI;
class MultiIniFieldParse;
class WeaponTemplate;

class GettingBuiltBehaviorModuleData : public ModuleData
{
public:
    GettingBuiltBehaviorModuleData();
    virtual ~GettingBuiltBehaviorModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    OpaqueRefElement4 m_selfBuildingLoop; // +0x08
    OpaqueRefElement4 m_selfRepairFromDamageLoop; // +0x0C
    OpaqueRefElement4 m_selfRepairFromRubbleLoop; // +0x10
    AsciiString m_workerName; // +0x14
    AsciiString m_evilWorkerName; // +0x18
    bool m_testFaction; // +0x1C
    float m_spawnTimer; // +0x20
    float m_rebuildTimeSeconds; // +0x24
    const WeaponTemplate *m_healWeapon; // +0x28
    bool m_rebuildWhenDead; // +0x2C
    float m_percentOfBuildCostToRebuildPristine; // +0x30
    float m_percentOfBuildCostToRebuildDamaged; // +0x34
    float m_percentOfBuildCostToRebuildReallyDamaged; // +0x38
    float m_percentOfBuildCostToRebuildRubble; // +0x3C
    ObjectFilter m_disallowRebuildFilter; // +0x40
    float m_disallowRebuildRange; // +0x44
    bool m_useSpawnTimerWithoutWorker; // +0x48
};

#endif
