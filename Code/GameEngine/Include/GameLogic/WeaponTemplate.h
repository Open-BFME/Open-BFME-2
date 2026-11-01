// Target facts (RVAs): 0x002CD169 stores vftable 0x00802170 at +0
// (store 0x002CD180); 0x002CD4A6 restores the same table at 0x002CD4B7.
// The sole slot is the deleting destructor 0x002CE047, which calls
// 0x002CD4A6. These bodies are rowed as Rva002CD4A6, not WeaponTemplate.
// Allocation sites 0x002CD61B and 0x002CE088 push 0x180 before calling
// operator new and then 0x002CD169. There is one vptr and no secondary table.
// Zero Hour declares MemoryPoolObject as the parent; its registered header
// has the same one-destructor-slot ABI. No additional virtuals are present.
// 0x002CD67C is the out-of-line assignment; ctor/dtor and assignment remain
// declarations so consumers cannot emit substitute ownership operations.
// The ctor's writes and assignment's reads/stores establish the scalar widths;
// the INI table 0x00800B48..0x00801308 supplies named offsets and types.
// Strings +08/+90/+178, vector triples +40/+4C, refs +C8/+D4/+DC,
// pooled handle +120 and list head +17C are opaque storage, not donor layouts.
// +94/+A4/+B8 are four-pointer arrays (ctor loop 0x002CD2CD..0x002CD2D9).
// +141 is byte-sized in ctor/assignment despite the INI integer parser.
// The methods below carry ledger spellings; getName is the by-value call
// at 0x0028F95C to the folded body 0x0028F940. Scalar getter names follow
// Zero Hour; +78/+16F accessors follow Object::fireCurrentWeapon 0x00291873.
// Method rows: getProjectileExhaust 0x000D1AB3, getMinimumAttackRange
// 0x002C92FA, getClipReloadTime 0x002C937C, isContactWeapon 0x0047A699,
// adjustTargetPositionOnVictim 0x002CAB3A, bfmeCalcScatterTargetPos
// 0x002CB679, rva002CBA59 0x002CBA59, shouldProjectileCollideWith
// 0x002CBA7C and fireWeaponTemplate 0x002CBBF5; neutral delay getters
// 0x002C9322/0x002C93DF/0x002C93F7, parsers 0x002C9055/0x002C9136/
// 0x002CE813. The ledger supplies each signature, including constness.
#pragma once

#ifndef BFME2_WEAPONTEMPLATE_H
#define BFME2_WEAPONTEMPLATE_H

#include "../Common/MemoryPoolObject.h"

class AsciiString;
class INI;
class Matrix3D;
class Object;
class Weapon;
class WeaponBonus;
class Xfer;
struct Coord3D;
class FXList;
class ParticleSystemTemplate;
class WeaponBonusSet;
struct TargetCoord;
enum ObjectID;
enum VeterancyLevel;
enum WeaponPrefireType;

class WeaponTemplate : public MemoryPoolObject
{
public:
    WeaponTemplate();
    virtual ~WeaponTemplate();
    WeaponTemplate &operator=(const WeaponTemplate &);

    AsciiString getName() const;
    const ParticleSystemTemplate *getProjectileExhaust(VeterancyLevel) const;
    int getClipReloadTime(const WeaponBonus &) const;
    float getMinimumAttackRange() const;
    bool isContactWeapon() const;
    void rva002CBA59(void *);
    Coord3D bfmeCalcScatterTargetPos(const Object *, const Object *, Coord3D);
    int rva002C9322(const WeaponBonus &, float) const;
    int rva002C93DF(const WeaponBonus &) const;
    int rva002C93F7(const WeaponBonus &) const;
    bool shouldProjectileCollideWith(const Object *, const Object *, const Object *, ObjectID) const;
    void fireWeaponTemplate(Object *, int, int, int, Object *, int, const Coord3D *, const WeaponBonus &, bool, Weapon *, int);
    TargetCoord adjustTargetPositionOnVictim(Object *, Object *, bool);
    static void parseShotDelay(INI *, void *, void *, const void *);
    static void parseClipReloadTime(INI *, void *, void *, const void *);

    float getAimDelta() const { return m_aimDelta; }
    float getWeaponSpeed() const { return m_weaponSpeed; }
    float getMinWeaponSpeed() const { return m_minWeaponSpeed; }
    bool isScaleWeaponSpeed() const { return m_isScaleWeaponSpeed; }
    float getMinTargetPitch() const { return m_minTargetPitch; }
    float getMaxTargetPitch() const { return m_maxTargetPitch; }
    int getClipSize() const { return m_clipSize; }
    int getShotsPerBarrel() const { return m_shotsPerBarrel; }
    unsigned int getSuspendFXDelay() const { return m_suspendFXDelay; }
    int getAntiMask() const { return m_antiMask; }
    float getContinueAttackRange() const { return m_continueAttackRange; }
    int getProjectileCollideMask() const { return m_collideMask; }
    bool getLocksSlotWhenFiring() const { return m_lockWhenUsing; }
    int getValue78() const { return m_idleAfterFiringDelay; }

    WeaponTemplate * m_nextTemplate; // +0x04
    void * m_field08; // +0x08
    int m_nameKey; // +0x0C
    int m_field10; // +0x10
    float m_attackRange; // +0x14
    float m_minimumAttackRange; // +0x18
    float m_field1C; // +0x1C
    float m_field20; // +0x20
    float m_field24; // +0x24
    float m_requestAssistRange; // +0x28
    float m_aimDelta; // +0x2C
    float m_field30; // +0x30
    float m_scatterRadius; // +0x34
    float m_scatterTargetScalar; // +0x38
    bool m_field3C; // +0x3C
    bool m_field3D; // +0x3D
    unsigned char m_pad3E[0x2];
    void * m_field40[3]; // +0x40
    void * m_field4C[3]; // +0x4C
    int m_damageType; // +0x58
    int m_deathType; // +0x5C
    int m_field60; // +0x60
    int m_field64; // +0x64
    float m_weaponSpeed; // +0x68
    float m_minWeaponSpeed; // +0x6C
    float m_field70; // +0x70
    bool m_isScaleWeaponSpeed; // +0x74
    bool m_field75; // +0x75
    unsigned char m_pad76[0x2];
    int m_idleAfterFiringDelay; // +0x78
    int m_field7C; // +0x7C
    bool m_field80; // +0x80
    bool m_field81; // +0x81
    bool m_field82; // +0x82
    bool m_field83; // +0x83
    float m_weaponRecoil; // +0x84
    float m_minTargetPitch; // +0x88
    float m_maxTargetPitch; // +0x8C
    void * m_field90; // +0x90
    const ParticleSystemTemplate * m_projectileExhausts[4]; // +0x94
    const FXList * m_fireFXs[4]; // +0xA4
    const FXList * m_fieldB4; // +0xB4
    const FXList * m_fieldB8[4]; // +0xB8
    void * m_fieldC8; // +0xC8
    unsigned int m_fireSoundLoopTime; // +0xCC
    unsigned int m_fieldD0[2]; // +0xD0
    unsigned int m_fieldD8[2]; // +0xD8
    WeaponBonusSet * m_extraBonus; // +0xE0
    int m_clipSize; // +0xE4
    int m_minClipReloadTime; // +0xE8
    int m_maxClipReloadTime; // +0xEC
    int m_minDelayBetweenShots; // +0xF0
    int m_maxDelayBetweenShots; // +0xF4
    int m_continuousFireOneShotsNeeded; // +0xF8
    int m_continuousFireTwoShotsNeeded; // +0xFC
    unsigned int m_continuousFireCoastFrames; // +0x100
    unsigned int m_autoReloadWhenIdleFrames; // +0x104
    int m_shotsPerBarrel; // +0x108
    int m_antiMask; // +0x10C
    int m_affectsMask; // +0x110
    bool m_field114; // +0x114
    unsigned char m_pad115[0x3];
    int m_collideMask; // +0x118
    bool m_damageDealtAtSelfPosition; // +0x11C
    unsigned char m_pad11D[0x3];
    void * m_field120; // +0x120
    bool m_field124; // +0x124
    bool m_field125; // +0x125
    bool m_field126; // +0x126
    unsigned char m_pad127[0x1];
    int m_field128; // +0x128
    WeaponPrefireType m_prefireType; // +0x12C
    bool m_leechRangeWeapon; // +0x130
    bool m_field131; // +0x131
    bool m_capableOfFollowingWaypoint; // +0x132
    bool m_isShowsAmmoPips; // +0x133
    bool m_allowAttackGarrisonedBldgs; // +0x134
    bool m_playFXWhenStealthed; // +0x135
    unsigned char m_pad136[0x2];
    int m_preAttackDelay; // +0x138
    int m_field13C; // +0x13C
    bool m_field140; // +0x140
    unsigned char m_field141; // +0x141
    unsigned char m_pad142[0x2];
    int m_field144; // +0x144
    float m_continueAttackRange; // +0x148
    float m_infantryInaccuracyDist; // +0x14C
    unsigned int m_suspendFXDelay; // +0x150
    bool m_field154; // +0x154
    bool m_field155; // +0x155
    bool m_field156; // +0x156
    bool m_field157; // +0x157
    float m_field158; // +0x158
    float m_field15C; // +0x15C
    bool m_field160; // +0x160
    bool m_field161; // +0x161
    unsigned char m_pad162[0x2];
    float m_field164; // +0x164
    bool m_field168; // +0x168
    bool m_field169; // +0x169
    bool m_field16A; // +0x16A
    bool m_field16B; // +0x16B
    bool m_field16C; // +0x16C
    bool m_field16D; // +0x16D
    bool m_field16E; // +0x16E
    bool m_lockWhenUsing; // +0x16F
    bool m_field170; // +0x170
    bool m_field171; // +0x171
    unsigned char m_pad172[0x2];
    int m_field174; // +0x174
    void * m_field178; // +0x178
    void * m_field17C; // +0x17C

private:
    static void parseScatterTarget(INI *, void *, void *, const void *);
};

#endif // BFME2_WEAPONTEMPLATE_H
