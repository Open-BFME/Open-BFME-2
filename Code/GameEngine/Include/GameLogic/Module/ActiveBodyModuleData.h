// Target facts (code addresses are RVAs, table addresses are VAs): constructor 0x004BF59F installs 0x00C5AFB8 at +0 (0x004BF5B8); factory 0x002513E8 allocates 0x64 bytes at 0x002513F4 and calls it at 0x00251409. The registered ModuleData base occupies +0..+7; derived fields begin at +8. The 31-slot live table ends at the zero word 0x00C5B034: slot 0 is deleting destructor 0x004BF9B5, which calls destructor 0x00256CB0 at 0x004BF9B8; slot 7 returns true through 0x0050B5C6. Other slots equal ModuleData's table 0x00C4ED70: 1/2/3 are 0x000B3FD0/0x00065212/0x0047A69C, 4..6/8..13/15 return false through 0x0047A699, 14 is the AsciiString-returning 0x000B69A1, 16..29 return null through 0x000D43D0, and 30 returns true through 0x0050B5C6. No slots are added.
// Target facts: destructor 0x00256CB0 frees +0x58 through 0x00030830, destroys AsciiStrings +0x34/+0x30/+0x2C through 0x00036410, then stores 0x00BBB554 at 0x00256CFD. Snapshot constructor 0x000053A6 and destructor 0x0049B47C install that same four-slot teardown table; it is not ActiveBodyModuleData's live table. Constructor stores 0x004BF5C1..0x004BF68D prove float fields +08/+0C/+10/+14/+18/+3C/+40/+44/+4C, dwords +1C/+20/+24/+38/+48/+54 and byte flags +28/+50/+51. Its call at 0x004BF5E6 constructs the 12-byte vector storage at +0x58 through 0x00211E58; the element type and original vector member name remain unresolved. Reader 0x004BE67E copies the +0x2C string through 0x000365F0.
// Target facts: buildFieldParse 0x004BFDF6 registers the 21-entry table 0x00C5B228, ending at 0x00C5B378. It identifies MaxHealth +08, InitialHealth +0C, MaxHealthDamaged +10, MaxHealthReallyDamaged +14, DodgePercent +18, EnteringDamagedTransitionTime +1C, EnteringReallyDamagedTransitionTime +20, RecoveryTime +24, UseDefaultDamageSettings +28, GrabObject +2C, DamagedAttributeModifier +30, ReallyDamagedAttributeModifier +34, GrabFX +38, GrabDamage +3C, GrabOffset +40, HealingBuffFx +48, CheerRadius +4C, RemoveUpgradesOnDeath +50, BurningDeathBehavior +51 and BurningDeathFX +54; DamageCreationList calls 0x004BFD83 with the complete object. Parsers 0x0002EFC0/0x0002F1BA, 0x00338B30, 0x0002E850, 0x0002F11E and 0x00338A09 prove float, unsigned frame count, bool, AsciiString and FXList* respectively. Zero Hour GeneralsMD ActiveBody.h proves only the member names m_maxHealth/m_initialHealth here; other fields and slot 7 retain neutral names. The constructor, virtual destructor, buildFieldParse and friend_newModuleData have ledger rows and remain out of line.
#pragma once

#ifndef BFME2_ACTIVEBODYMODULEDATA_H
#define BFME2_ACTIVEBODYMODULEDATA_H

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../Common/ModuleData.h"

class FXList;
class INI;

class ActiveBodyModuleData : public ModuleData
{
public:
    ActiveBodyModuleData();
    virtual ~ActiveBodyModuleData();

    virtual bool slot07() const { return true; }

    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    float m_maxHealth;
    float m_initialHealth;
    float field10;
    float field14;
    float field18;
    unsigned int field1C;
    unsigned int field20;
    unsigned int field24;
    bool field28;
    unsigned char pad29[3];
    AsciiString field2C;
    AsciiString field30;
    AsciiString field34;
    const FXList *field38;
    float field3C;
    float field40;
    float field44;
    const FXList *field48;
    float field4C;
    bool field50;
    bool field51;
    unsigned char pad52[2];
    const FXList *field54;
    void *field58;
    void *field5C;
    void *field60;
};

typedef char ActiveBodyModuleDataSizeCheck[sizeof(ActiveBodyModuleData) == 0x64 ? 1 : -1];

#endif
