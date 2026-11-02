// Target facts (code addresses are RVAs, table addresses are VAs):
// Constructor 0x004930A0 stores 0x00C4E318 at +0 (0x004930BC); factory 0x0024DC8C allocates 0x7C bytes (0x0024DC98), calls that constructor and returns ModuleData*. ModuleData's registered eight-byte base supplies the Snapshot vptr at +0 and module tag at +4; the first derived field is +8. No separate BehaviorModuleData header or additional base storage is required.
// The live table 0x00C4E318 has 31 slots and ends at non-code 0x00C4E394: slot 0 is deleting destructor 0x00493333, which calls destructor 0x0049334F; slots 1/2/3 are 0x000B3FD0/0x00065212/0x0047A69C, slots 4..13 and 15 are false (0x0047A699), slot 14 is the AsciiString-returning 0x000B69A1, slots 16..29 return null (0x000D43D0), and slot 30 returns true (0x0050B5C6). These are ModuleData's inherited slots; this class adds none.
// Destructor 0x0049334F releases strings +0x6C/+0x18 through 0x00036410, filters +0x3C/+0x38/+0x24 through 0x00360D26, and the +0x14 reference through 0x00050ED3, then stores Snapshot's 0x00BBB554 at 0x004933B2. That four-slot teardown table is not this class's live table. The constructor and virtual destructor remain out of line.
// buildFieldParse 0x00493207 passes table 0x00C4E628 to MultiIniFieldParse::add. Its 0x10-byte entries through 0x00C4E858 prove offsets: SpecialPowerTemplate +08, UpdateModuleStartsAttack +0C, StartsPaused +0D, InitiateSound +10, AttributeModifier +18, AttributeModifierRange +1C, AttributeModifierAffectsSelf +20, AttributeModifierAffects +24, AttributeModifierFX +28, AttributeModifierWeatherBased +2C, WeatherDuration +30, AntiCategory +34, RequirementsFilterMPSkirmish +38, RequirementsFilterStrategic +3C, TargetEnemy +40, TargetAllSides +41, ReEnableAntiCategory +42, InitiateFX +44, TriggerFX +48, AntiFX +4C, SetModelCondition +50, SetModelConditionTime +54, GiveLevels +58, DisableDuringAnimDuration +5C, IdleWhenStartingPower +5D, AffectGood +5E, AffectEvil +5F, AffectAllies +60, AvailableAtStart +61, ChangeWeather +64, AdjustVictim +68, OnTriggerRechargeSpecialPower +6C, BurnDecayModifier +70, UseDistanceFromCommandCenter +74, DistanceFromCommandCenter +78.
// The table's rowed parsers prove bool (0x0002E850), int (0x0002EF56), unsigned int (0x0002EF72/0x00338B30), float (0x0002EFC0), AsciiString (0x0002F11E), SpecialPowerTemplate* (0x00339918) and FXList* (0x00338A09). Constructor stores 0x004930C2..0x0049318E independently prove scalar widths and the end at +0x7C. InitiateSound occupies +0x10..+0x17; filters and AntiCategory occupy four bytes each. Their unrecovered member types retain neutral storage.
// Zero Hour GameLogic/Module/SpecialPowerModule.h proves the names m_specialPowerTemplate, m_updateModuleStartsAttack and m_startsPaused. Its AudioEventRTS extent does not match the target's eight-byte member. Other C++ member names remain neutral; the retail INI token names above identify their roles. Ledger rows prove buildFieldParse and friend_newModuleData (0x0024DC8C).
#pragma once

#ifndef BFME2_SPECIALPOWERMODULEDATA_H
#define BFME2_SPECIALPOWERMODULEDATA_H

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../Common/ModuleData.h"
#include "../../Common/SpecialPower.h"

class FXList;
class INI;

class SpecialPowerModuleData : public ModuleData
{
public:
    SpecialPowerModuleData();
    virtual ~SpecialPowerModuleData();

    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    const SpecialPowerTemplate *m_specialPowerTemplate;
    bool m_updateModuleStartsAttack;
    bool m_startsPaused;
    unsigned char pad0E[2];
    unsigned char field10[8];
    AsciiString field18;
    float field1C;
    bool field20;
    unsigned char pad21[3];
    unsigned int field24;
    const FXList *field28;
    bool field2C;
    unsigned char pad2D[3];
    unsigned int field30;
    unsigned int field34;
    unsigned int field38;
    unsigned int field3C;
    bool field40;
    bool field41;
    bool field42;
    unsigned char pad43;
    const FXList *field44;
    const FXList *field48;
    const FXList *field4C;
    int field50;
    float field54;
    int field58;
    bool field5C;
    bool field5D;
    bool field5E;
    bool field5F;
    bool field60;
    bool field61;
    unsigned char pad62[2];
    int field64;
    bool field68;
    unsigned char pad69[3];
    AsciiString field6C;
    unsigned int field70;
    bool field74;
    unsigned char pad75[3];
    float field78;
};

#endif
