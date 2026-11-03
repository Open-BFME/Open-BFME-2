// Target facts (code addresses are RVAs, tables are VAs): constructor 0x0045E386 stores 0x00C42108 at 0x0045E3A0; destructor 0x0045E4A5 restores that table at 0x0045E4B6, destroys the four vector arrays, then restores Snapshot's 0x00BBB554 at 0x0045E523. The four-slot Snapshot table is base teardown. The live table has 31 slots, ending before the string at 0x00C42184; slot 0 is deleting destructor 0x0045E88D, which calls 0x0045E4A5. Slots 1..30 equal registered ModuleData's table 0x00C4ED70: 1=0x000B3FD0, 2=0x00065212 (shared "ModuleData" literal 0x00BC5AFC), 3=0x0047A69C, 4..13/15=0x0047A699, 14=0x000B69A1, 16..29=0x000D43D0, 30=0x0050B5C6. ModuleData supplies the eight-byte prefix and the shared virtual interface; an intermediate base name is not established by these bytes.
// Target facts: factory 0x0024B29C allocates 0x190 at 0x0024B2A8 and calls the constructor at 0x0024B2C0; derived constructors 0x00461F7F and 0x00483E25 begin their members at +0x190. Constructor calls establish DieMuxData/+8 (0x0045E3A6), four 12-byte vector headers each at +0x58/+0x88/+0xB8/+0xE8 (0x0045E3BD/0x0045E3DB/0x0045E3F9/0x0045E417), a 0x4C-byte value/+0x128 (0x0045E422) and a 16-byte mask/+0x174 (0x0045E42D). Stores 0x0045E438..0x0045E48E prove four-byte scalars at +0x38..+0x54, +0x118..+0x124, +0x184/+0x188, and bytes +0x18C/+0x18D. The vector and mask storage remains opaque until shared member types are established.
// Target facts and names: FieldParse 0x00C42290..0x00C423C0 proves the scalar names/offsets and maps FX/OCL/Weapon/Sound/DeathFlags to rowed parsers 0x0045E533/0x0045E5A4/0x0045E618/0x0045E8A9/0x0045E293. The first four parsers OR bits 1/2/4/8 into +0x18C. buildFieldParse 0x0045E93F adds this table and DieMuxData's table at +8; the factory passes that row out of line at 0x0024B2D6. Zero Hour GeneralsMD SlowDeathBehavior.h supplies matching scalar spellings and hasNonLodEffects (mask 6), not BFME2 offsets, phase count or inheritance. The constructor and virtual destructor remain declared out of line.
#pragma once

#ifndef BFME2_SLOWDEATHBEHAVIORMODULEDATA_H
#define BFME2_SLOWDEATHBEHAVIORMODULEDATA_H

#include "../../Common/ModuleData.h"
#include "DieMuxData.h"

class INI;
class MultiIniFieldParse;

class SlowDeathBehaviorModuleData : public ModuleData
{
public:
    SlowDeathBehaviorModuleData();
    virtual ~SlowDeathBehaviorModuleData();

    static ModuleData *friend_newModuleData(INI *ini);
    static void buildFieldParse(MultiIniFieldParse &parse);
    static void parseFX(INI *ini, void *instance, void *store, const void *userData);
    static void parseOCL(INI *ini, void *instance, void *store, const void *userData);
    static void parseWeapon(INI *ini, void *instance, void *store, const void *userData);
    static void rva0045E8A9(INI *ini, void *instance, void *store, const void *userData);
    static void parseDeathFlags(INI *ini, void *instance, void *store, const void *userData);

    enum
    {
        HAS_FX = 1,
        HAS_OCL = 2,
        HAS_WEAPON = 4,
        HAS_SOUND = 8,
        HAS_NON_LOD_EFFECTS = HAS_OCL | HAS_WEAPON
    };

    bool hasNonLodEffects() const { return (m_maskOfLoadedEffects & HAS_NON_LOD_EFFECTS) != 0; }

    DieMuxData m_dieMuxData;
    float m_sinkRate;
    int m_probabilityModifier;
    float m_modifierBonusPerOverkillPercent;
    unsigned int m_sinkDelay;
    unsigned int m_sinkDelayVariance;
    unsigned int m_destructionDelay;
    unsigned int m_destructionDelayVariance;
    unsigned int m_decayBeginTime;
    unsigned char field058[0x30];
    unsigned char field088[0x30];
    unsigned char field0B8[0x30];
    unsigned char field0E8[0x30];
    float m_flingForce;
    float m_flingForceVariance;
    float m_flingPitch;
    float m_flingPitchVariance;
    unsigned char field128[0x4C];
    unsigned long field174[4];
    unsigned int m_fadeTime;
    unsigned int m_fadeDelay;
    unsigned char m_maskOfLoadedEffects;
    bool m_shadowWhenDead;
};

typedef char SlowDeathBehaviorModuleDataSizeCheck[sizeof(SlowDeathBehaviorModuleData) == 0x190 ? 1 : -1];

#endif
