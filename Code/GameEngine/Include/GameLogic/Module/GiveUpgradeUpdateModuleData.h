// Target facts (code addresses are RVAs; table addresses are VAs): constructor 0x0049C4D2 calls SpecialAbilityUpdateModuleData's 0x0044EB54 at 0x0049C4D6, then stores 0x00C51280 at 0x0049C4E6. Factory 0x0024E800 pushes sizeof 0xE4 at 0x0024E80C and calls that constructor at 0x0024E824. ModuleFactory registration 0x00259B45..0x00259B6A binds the literal GiveUpgradeUpdate (0x00BF51B0) to this factory. The parent factory 0x0024A882 allocates 0xC8; derived fields start at +0xC8.
// Table 0x00C51280 has 31 slots and ends at 0x00C512FC; slots 1..30 equal the parent's 0x00C3F2A8 and ModuleData's 0x00C4ED70. Slot 0 is deleting destructor 0x0049C624, which calls destructor 0x0049C640 at 0x0049C627. The latter frees +0xC8 at 0x0049C660 and calls parent destructor 0x0044ECCE at 0x0049C66C without storing a vptr. The parent restores 0x00C3F2A8 at 0x0044ECDF and Snapshot's 0x00BBB554 at 0x0044ED85 during teardown. No new virtual slots are introduced; the destructor overrides inherited slot 0. Inherited GetSnapshotName 0x00065212 returns ModuleData, a shared base name.
// Constructor 0x0049C4E0..0x0049C4EC constructs a 12-byte vector header at +0xC8 through folded helper 0x00211E58 and allocator proxy 0x0014F3C4, proving three pointer words but no element type; fieldC8/fieldCC/fieldD0 retain its storage. Stores 0x0049C4FB/0x0049C501/0x0049C507/0x0049C50D initialize +0xD4/+0xD8/+0xE0/+0xDC, the float from 0x00C5127C (0.025f). buildFieldParse 0x0049C391 calls parent parser 0x0044ED95 and passes 0x00C511A0: GiveUpgradeEffect and SpawnOutFX use INI::parseFXList (0x00338A09) at +0xD4/+0xD8; FadeOutSpeed uses parseReal (0x0002EFC0) at +0xDC; DeliverUpgrade uses parseBool (0x0002E850) at +0xE0. These tokens prove the member names. Rowed constructor, destructor and static methods remain out of line.
#pragma once

#ifndef BFME2_GIVEUPGRADEUPDATEMODULEDATA_H
#define BFME2_GIVEUPGRADEUPDATEMODULEDATA_H

#include "SpecialAbilityUpdateModuleData.h"

class FXList;

class GiveUpgradeUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
    GiveUpgradeUpdateModuleData();
    virtual ~GiveUpgradeUpdateModuleData();
    static void buildFieldParse(MultiIniFieldParse &);
    static ModuleData *friend_newModuleData(INI *);

    void *fieldC8;                          // +0xC8
    void *fieldCC;                          // +0xCC
    void *fieldD0;                          // +0xD0
    const FXList *m_giveUpgradeEffect;       // +0xD4
    const FXList *m_spawnOutFX;              // +0xD8
    float m_fadeOutSpeed;                   // +0xDC
    bool m_deliverUpgrade;                  // +0xE0
};

#endif
