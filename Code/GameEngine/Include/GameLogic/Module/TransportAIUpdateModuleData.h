// Target facts (code addresses are RVAs; table addresses are VAs): Constructor 0x0026E5D7 stores 0x00BFA288 at 0x0026E5F2; destructor 0x0026E1FC restores it at 0x0026E20D, then stores Snapshot's 0x00BBB554 at 0x0026E257 after member teardown. Snapshot's constructor 0x000053A6 and destructor 0x0049B47C store that four-slot base table; it is not the live Transport table. The live table ends at 0x00BFA304 and has 31 slots: 0 is deleting destructor 0x0026E67D (calling 0x0026E1FC), 1 is ret 0x000B3FD0, 2 is ModuleData::GetSnapshotName 0x00065212, 3 is ret 4 at 0x0047A69C, 4/30 return true at 0x0050B5C6, 5..13/15 return false at 0x0047A699, 14 returns an AsciiString with one int argument at 0x000B69A1, and 16..29 return null at 0x000D43D0. Slots 1..30 equal ModuleData's 0x00C4ED70 except slot 4, isAiModuleData, which an AI module data answers true.
// Target facts: Factory 0x0024BDF2 pushes 0x64 at 0x0024BDFE and calls the constructor at 0x0024BE13; Animal's constructor 0x0024BE43 calls it and begins its fields at +0x64. ModuleFactory's 0x00257237 stores the tag at +4; ModuleData supplies the eight-byte prefix. Direct ModuleData inheritance represents the data-less intermediate chain without claiming its original names. Parser 0x002638FF registers 0x00BF9378: its 19 token/offset records prove the named fields below. parseBool 0x0002E850 identifies bytes +24/+25/+3C/+54; parseReal 0x0002EFC0 identifies floats +20/+28/+4C; parseDurationUnsignedInt 0x00338B30 identifies unsigned dwords +18/+30/+34/+38/+40/+48; parseBitString32 0x0002EB38 identifies +1C; parseIndexList 0x0002EC4E identifies +50; parseAsciiString 0x0002F11E identifies +2C/+44. parseTurret 0x002623C1 allocates TurretAIData through constructor 0x004D7E6C and stores its pointer at +14. Constructor stores 0x0026E60A..0x0026E66D independently prove these scalar widths and offsets.
// Target facts: Constructor calls 0x00413727 on +8, StringBase<char> construction 0x00037BA0 on +44 and vector-base construction 0x00211E58 on +58. Destructor calls vector<AsciiString> destruction 0x0002CC70 on +58, string destruction 0x00036410 on +44/+2C, and tree destruction 0x0026E1A6 on +8 after deleting +14. Both container headers occupy twelve bytes: +14 follows the tree, and vector-base 0x00211E58 plus its allocator proxy 0x0014F3C4 initialize +0/+4/+8. The SpecialContactPoints parser 0x0002E896 appends strings to +58. The tree's original name and payload type remain unresolved; neutral storage records only the evidenced container extents, with lifetime owned by out-of-line methods. Constructor, virtual destructor, buildFieldParse (0x002638FF) and friend_newModuleData (0x0024BDF2) have ledger rows and remain declared out of line.
#pragma once

#ifndef BFME2_TRANSPORTAIUPDATEMODULEDATA_H
#define BFME2_TRANSPORTAIUPDATEMODULEDATA_H

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../Common/ModuleData.h"

class INI;
class TurretAIData;

class TransportAIUpdateModuleData : public ModuleData
{
public:
    TransportAIUpdateModuleData();
    virtual ~TransportAIUpdateModuleData();
    virtual bool isAiModuleData() const { return true; }

    static void buildFieldParse(MultiIniFieldParse &);
    static ModuleData *friend_newModuleData(INI *);

    unsigned int field08[3];                             // +0x08
    TurretAIData *m_turret;                               // +0x14
    unsigned int m_moodAttackCheckRate;                   // +0x18
    unsigned int m_autoAcquireEnemiesWhenIdle;                     // +0x1C
    float m_stopChaseDistance;                            // +0x20
    bool m_standGround;                                  // +0x24
    bool m_canAttackWhileContained;                       // +0x25
    float m_holdGroundCloseRangeDistance;                 // +0x28
    AsciiString m_aiLuaEventsList;                        // +0x2C
    unsigned int m_maxCowerTime;                          // +0x30
    unsigned int m_minCowerTime;                          // +0x34
    unsigned int m_rampageTime;                           // +0x38
    bool m_rampageRequiresAflame;                         // +0x3C
    unsigned int m_burningDeathTime;                      // +0x40
    AsciiString m_attackPriority;                        // +0x44
    unsigned int m_timeToEjectPassengersOnRampage;         // +0x48
    float m_comboLocoAttackDistance;                      // +0x4C
    int m_comboLocomotorSet;                              // +0x50
    bool m_fadeOnPortals;                                 // +0x54
    unsigned int field58[3];                             // +0x58, SpecialContactPoints
};

#endif
