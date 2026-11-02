// Target facts (RVAs): ctor 0x002CC20E calls SubsystemInterface's ctor
// 0x001B4E63, then stores VA 0x00C02114 at +0 (0x002CC221).
// GameEngine::init pushes 0x24 at 0x0022EB61 and calls that ctor at
// 0x0022EB76: sizeof is 0x24, with the 0x0C-byte base at +0.
// The base ctor stores VA 0x00BD77A0, clears byte +4 and dword +8;
// its dtor 0x001B4E74 restores that base table and destroys AsciiString +8.
// Dtor 0x002CCD56 (rowed as Rva002CCD56) restores VA 0x00C02114 at
// 0x002CCD69, destroys both vectors, then calls the base dtor at 0x002CCE23.
// Slot 0 at table RVA 0x00802114 is 0x002CD5E0, which calls 0x002CCD56.
// Thus the constructor/destructor table is WeaponStore's, and 0x007D77A0
// is the base's table. The destructor stays declared out of line.
// The table has fourteen slots, ending before Weapon's table 0x0080214C:
// 0=002CD5E0, 1=000B3FD0, 2=001B5384, 3=002CADFA, 4=002CAE34,
// 5=002CAE6C, 6=000D43D0, 7=002C941C, 8=000B3FD0, 9=002C9A34,
// 10=000B3FD0, 11=005CB9FF, 12=000B3FD0, 13=0047A69C.
// Slots 2, 3 and 9 have ledger names; init/update follow Zero Hour's
// declaration and the base's slot order. Other slots keep neutral names.
// 0x002CC227/0x002CC233 construct vector bases at +0x0C/+0x18;
// dtor 0x002CCD6F..0x002CCE16 traverses four-byte pointers and frees both
// buffers. 0x002CADBE searches the +0x0C vector by template key +0x0C;
// 0x002CDB0E erases an active template and appends it to +0x18. The two
// twelve-byte vector representations remain opaque storage here.
// Method declarations use ledger spellings and signatures: allocateNewWeapon
// 0x0028AA81, findWeaponTemplate 0x002CB8BF, findWeaponTemplatePrivate
// 0x002CADBE, newWeaponTemplate 0x002CD5FC, newOverride 0x002CE063,
// rva002CDB0E 0x002CDB0E, parseWeaponTemplateDefinition 0x002CE102,
// resetWeaponTemplates 0x002C9A18, createAndFireTempWeapon 0x002CE904,
// handleProjectileDetonation 0x002CE8AA and rva002CE964/rva002CE9C8.
// The existing Rva002C724E thunk at 0x002C724E jumps directly to the
// protected lookup 0x002CADBE; its source view retains access through friendship.
#pragma once

#ifndef BFME2_WEAPONSTORE_H
#define BFME2_WEAPONSTORE_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class AsciiString;
class INI;
class Object;
class Rva002C724E;
class Weapon;
class WeaponSet;
class WeaponTemplate;
struct Coord3D;
enum NameKeyType;
enum WeaponSlotType;

class WeaponStore : public SubsystemInterface
{
    friend class WeaponTemplate;
    friend class WeaponSet;
    friend class Rva002C724E;

public:
    WeaponStore();
    virtual ~WeaponStore();

    virtual void init();
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
    virtual void reset();
    virtual void update();
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);

    const WeaponTemplate *findWeaponTemplate(const AsciiString &) const;
    Weapon *allocateNewWeapon(const WeaponTemplate *, WeaponSlotType) const;
    WeaponTemplate *newOverride(WeaponTemplate *);
    void rva002CDB0E(const WeaponTemplate *);
    void createAndFireTempWeapon(const WeaponTemplate *, const Object *, const Coord3D *);
    void handleProjectileDetonation(const WeaponTemplate *, const Coord3D *, const Object *, const Coord3D *, int);
    void rva002CE964(const WeaponTemplate *, const Object *, const Object *);
    void rva002CE9C8(const WeaponTemplate *, const Object *, const Object *);
    static void parseWeaponTemplateDefinition(INI *);

protected:
    WeaponTemplate *findWeaponTemplatePrivate(NameKeyType) const;
    WeaponTemplate *newWeaponTemplate(const AsciiString &);
    void resetWeaponTemplates();

private:
    unsigned char m_field0C[0x0C];
    unsigned char m_field18[0x0C];
};

#endif
