// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x0044EB54 stores 0x00C3F2A8 at 0x0044EB68. Destructor 0x0044ECCE stores the same table at 0x0044ECDF, then Snapshot's 0x00BBB554 at 0x0044ED85. Slot 0 is the deleting destructor 0x0044EF42, which calls 0x0044ECCE. The live table has 31 slots, ending at 0x00C3F324; slots 1..30 equal ModuleData's 0x00C4ED70 table: loadPostProcess, GetSnapshotName, xfer, false at 4..13/15, an AsciiString result at 14, null at 16..29, true at 30. Snapshot's four-slot table is base teardown, not the live interface. ModuleData supplies the eight-byte prefix. Donor fact: Zero Hour's UpdateModuleData and BehaviorModuleData introduce no fields or virtuals. Structural inference: direct ModuleData inheritance represents that empty chain.
// Factory 0x0024A882 allocates 0xC8 at 0x0024A88E and calls 0x0044EB54 at 0x0024A8A6; derived constructor 0x004923E2 starts its fields at +0xC8. Parser 0x0044ED95 passes 0x00C3F7F8, whose 58 entries prove the field offsets below. Constructor 0x0044EB71..0x0044ECBB proves dwords +08..+A4, bytes +A8..+B8/+C4..+C6, and strings +40/+44/+48/+BC/+C0; destructor 0x0044ECED..0x0044ED7D releases those strings and refcounted pointers +08/+0C/+10/+14/+34. +18..+2C are two three-dword animation records (parser 0x0044E6CD); their internal names are unknown. Zero Hour SpecialAbilityUpdate.h supplies the shared member names. BFME2-only members retain offset placeholders. Constructor, destructor, buildFieldParse (0x0044ED95), and friend_newModuleData (0x0024A882) are declared out of line; their shared native lifetime representation is below.
#pragma once

#ifndef BFME2_SPECIALABILITYUPDATEMODULEDATA_H
#define BFME2_SPECIALABILITYUPDATEMODULEDATA_H

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
#include "../../Common/ModuleData.h"

class INI;
class OpaqueRefCounted;
class ParticleSystemTemplate;
class SpecialPowerTemplate;

// Both native lifetime owners construct these five nullable four-byte handles
// and release them after the string members. Preserve the existing helper's
// name: its whole 12-byte destructor is rowed at 0x0010F149. The original
// application type and copy semantics are not established by that lifetime.
class OpaqueRefPtr
{
public:
    ~OpaqueRefPtr() { if (m_p) m_p->Release_Ref(); }
    OpaqueRefPtr() : m_p(0) {}
private:
    OpaqueRefCounted *m_p;
};

// This existing layout-only group preserves the constructor's store order:
// zero +1C/+20, then set +18/+24 to -1. It proves no original aggregate name.
class Rva0044EB54Fields18
{
public:
    __forceinline Rva0044EB54Fields18()
    {
        m_customAnimTime = 0;
        m_20 = 0;
        m_customAnimState = -1;
        m_grabPassengerAnimState = -1;
    }
private:
    int m_customAnimState;
    int m_customAnimTime;
    int m_20;
    int m_grabPassengerAnimState;
};

class SpecialAbilityUpdateModuleData : public ModuleData
{
public:
    SpecialAbilityUpdateModuleData();
    virtual ~SpecialAbilityUpdateModuleData();
    static void buildFieldParse(MultiIniFieldParse &);
    static ModuleData *friend_newModuleData(INI *);

    OpaqueRefPtr m_packSound;                             // +0x08
    OpaqueRefPtr m_unpackSound;                           // +0x0C
    OpaqueRefPtr m_prepSoundLoop;                         // +0x10
    OpaqueRefPtr m_triggerSound;                          // +0x14
    Rva0044EB54Fields18 m_fields18;                       // +0x18
    unsigned int field28;                                // +0x28
    unsigned int field2C;                                // +0x2C
    float field30;                                       // +0x30
    OpaqueRefPtr field34;                                // +0x34
    const SpecialPowerTemplate *m_specialPowerTemplate;   // +0x38
    const ParticleSystemTemplate *m_disableFXParticleSystem; // +0x3C
    AsciiString m_specialObjectName;                     // +0x40
    AsciiString m_specialObjectAttachToBoneName;           // +0x44
    AsciiString field48;                                 // +0x48
    float m_startAbilityRange;                           // +0x4C
    float m_abilityAbortRange;                           // +0x50
    float m_packUnpackVariationFactor;                    // +0x54
    float m_fleeRangeAfterCompletion;                     // +0x58
    int m_effectValue;                                   // +0x5C
    float field60;                                       // +0x60
    int m_awardXPForTriggering;                           // +0x64
    int m_skillPointsForTriggering;                       // +0x68
    int field6C;                                         // +0x6C
    int field70;                                         // +0x70
    unsigned int m_preparationFrames;                     // +0x74
    unsigned int m_persistentPrepFrames;                  // +0x78
    unsigned int m_effectDuration;                       // +0x7C
    unsigned int m_maxSpecialObjects;                     // +0x80
    unsigned int m_packTime;                              // +0x84
    unsigned int m_unpackTime;                            // +0x88
    unsigned int m_preTriggerUnstealthFrames;             // +0x8C
    unsigned int field90;                                // +0x90
    unsigned int field94;                                // +0x94
    unsigned int field98;                                // +0x98
    unsigned int field9C;                                // +0x9C
    unsigned int fieldA0;                                // +0xA0
    unsigned int fieldA4;                                // +0xA4
    bool m_skipPackingWithNoTarget;                       // +0xA8
    bool m_specialObjectsPersistent;                     // +0xA9
    bool m_uniqueSpecialObjectTargets;                    // +0xAA
    bool m_specialObjectsPersistWhenOwnerDies;            // +0xAB
    bool m_flipObjectAfterPacking;                       // +0xAC
    bool m_flipObjectAfterUnpacking;                      // +0xAD
    bool m_alwaysValidateSpecialObjects;                  // +0xAE
    bool m_doCaptureFX;                                  // +0xAF
    bool m_loseStealthOnTrigger;                          // +0xB0
    bool m_approachRequiresLOS;                           // +0xB1
    bool fieldB2;                                        // +0xB2
    bool fieldB3;                                        // +0xB3
    bool fieldB4;                                        // +0xB4
    bool fieldB5;                                        // +0xB5
    bool fieldB6;                                        // +0xB6
    bool fieldB7;                                        // +0xB7
    bool fieldB8;                                        // +0xB8
    AsciiString fieldBC;                                 // +0xBC
    AsciiString fieldC0;                                 // +0xC0
    bool fieldC4;                                        // +0xC4
    bool fieldC5;                                        // +0xC5
    bool fieldC6;                                        // +0xC6
};

#endif
