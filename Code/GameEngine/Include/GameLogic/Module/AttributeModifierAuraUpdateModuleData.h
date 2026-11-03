// Target facts (code addresses are RVAs; tables and strings are VAs): factory 0x0024E65C pushes sizeof 0x154 at 0x0024E668 and calls constructor 0x0049BBD5 at 0x0024E680. The constructor installs the primary vftable 0x00C50EE8 at 0x0049BBEE. Its 31 slots end at 0x00C50F64 and agree with ModuleData's registered interface: slot 0 is deleting destructor 0x0049BF50, which calls destructor 0x0049BF6C; slots 1..30 equal the ModuleData-family tables 0x00C4ED70 and 0x00C549F8. Slot 2 is the inherited ModuleData name getter 0x00065212, returning "ModuleData" at 0x00BC5AFC. No new virtual slot or secondary vptr is present. The parent tag store at 0x00257232..0x00257237 and eight-byte allocation at 0x0024CCF4 bound ModuleData to +0..+7; derived storage starts at +8.
// Destructor 0x0049BF6C destroys the +0x24 filter through 0x00360D26 at 0x0049BF87, the +0x0C string vector through 0x0002CC70 at 0x0049BF93 and the +8 string through 0x00036410 at 0x0049BF9F, then restores Snapshot's 0x00BBB554 at 0x0049BFA7. That four-slot table belongs to base teardown. The +8 string is zeroed at 0x0049BBF7 and set through 0x000055F5 at 0x0049BC2F; its AsciiString extent is four bytes. The 12-byte vector at +0x0C is constructed through 0x00211E58 at 0x0049BC00 and remains opaque storage. The four-byte filter is constructed through 0x003623E5 at 0x0049BC0C. The +0x28 member is constructed through 0x0025342C at 0x0049BC18. It contains two 0x80-byte masks, dwords at relative +0x100, +0x104 and +0x108, and bytes at +0x10C, +0x10D and +0x10E. The next store at +0x138 bounds its extent to 0x110.
// buildFieldParse 0x0049BBB3 adds the table returned by 0x004CE29D with offset 0x28, then table 0x00C50DC8 with offset zero. That table identifies BonusName at +8, RefreshDelay at +0x18, Range at +0x1C, AllowPowerWhenAttacking at +0x20, TargetEnemy at +0x21, ObjectFilter at +0x24, StartsActive at +0x138, RequiredConditions at +0x13C, AntiCategory at +0x140, AntiFX at +0x144, AffectGood at +0x148, AffectEvil at +0x149, RunWhileDead at +0x14A, AllowSelf at +0x14B, AffectContainedOnly at +0x14C and MaxActiveRank at +0x150. Parser 0x0002F11E handles strings, 0x00338B30 unsigned durations, 0x0002EFC0 floats, 0x0002E850 bools, 0x0002EB38 32-bit masks, 0x00338A09 FX pointers and 0x0002EF56 ints. Constructor stores at 0x0049BC41..0x0049BC8F confirm their widths. AntiCategory's parser 0x0049BBA3 and constructor call 0x003B31AD operate on one four-byte mask. The constructor, virtual destructor, buildFieldParse and friend_newModuleData are rowed out-of-line methods.
#pragma once

#ifndef BFME2_ATTRIBUTEMODIFIERAURAUPDATEMODULEDATA_H
#define BFME2_ATTRIBUTEMODIFIERAURAUPDATEMODULEDATA_H

#include "../../Common/ModuleData.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "Rva003623E5Member.h"
#include "Rva0025342CMember.h"

class INI;
class MultiIniFieldParse;
class FXList;

class AttributeModifierAuraUpdateModuleData : public ModuleData
{
public:
    AttributeModifierAuraUpdateModuleData();
    virtual ~AttributeModifierAuraUpdateModuleData();

    static void buildFieldParse(MultiIniFieldParse &parse);
    static ModuleData *friend_newModuleData(INI *ini);

    AsciiString m_bonusName;
    unsigned char m_0C[12];
    unsigned int m_refreshDelay;
    float m_range;
    bool m_allowPowerWhenAttacking;
    bool m_targetEnemy;
    Rva003623E5Member m_objectFilter;
    Rva0025342CMember m_28;
    bool m_startsActive;
    unsigned int m_requiredConditions;
    unsigned int m_antiCategory;
    const FXList *m_antiFX;
    bool m_affectGood;
    bool m_affectEvil;
    bool m_runWhileDead;
    bool m_allowSelf;
    bool m_affectContainedOnly;
    int m_maxActiveRank;
};

typedef char AttributeModifierAuraUpdateModuleData_size_154[(sizeof(AttributeModifierAuraUpdateModuleData) == 0x154) ? 1 : -1];

#endif
