// Target facts (game.dat 1.06): ctor RVA 0x002C72D5 stores VA 0x00C0089C at +0, clears the template pointer +4, six Weapon pointers +8..+0x1C, words +0x20/+0x24/+0x28/+0x2C/+0x30, flags +0x34/+0x35, six bytes +0x36..+0x3B and owner ID +0x3C; Object passes +0x330 to this ctor and places its next flags at +0x370 (0x00290963), bounding sizeof to 0x40. Dtor 0x002C7311 installs the same table at 0x002C7324, destroys six weapons, then restores Snapshot VA 0x00BBB554 at 0x002C7351; unwind 0x00776F70 calls Snapshot dtor 0x0049B47C, proving Snapshot at +0.
// Target facts: VA 0x00C0089C has exactly four slots before the "WeaponSet" literal at VA 0x00C008AC: scalar deleting dtor RVA 0x002C75B5, empty loadPostProcess 0x000B3FD0, name getter 0x002C74FB returning that literal, and xfer 0x002C8872. Snapshot's registered name-slot profile gives this order. Rowed methods retain their ledger signatures: updateWeaponSet 0x002C8C97, reloadAllAmmo 0x002C739E, isOutOfAmmo 0x002C73CE, findAmmoPipShowingWeapon 0x002C73F7, findWaypointFollowingCapableWeapon 0x002C741C, isAnyWithinTargetPitch 0x002C7362, chooseBestWeaponForTarget 0x002C7D03, getAbleToUseWeaponAgainstTarget 0x002C7907 and getAbleToAttackSpecificObject 0x002C83FC. getWeaponInWeaponSlot is pinned to 0x002C7469, whose indexed +8 load and Object call at 0x00290C74 prove the accessor. xfer transfers the tail ID; setWeaponLock 0x002C8AAE and releaseWeaponLock 0x002C8B9B resolve +0x3C through GameLogic::findObjectByID. rva002C75D1 at 0x002C75D1 tests the unnamed byte array at +0x36.
// Donor facts: Zero Hour GeneralsMD GameLogic/WeaponSet.h names the common fields and inline accessors; BFME2's ctor and rowed members establish their offsets and six-slot extent. The damage mask is a native word (ctor 0x002C72EF and xfer 0x002C8872), rather than Zero Hour's BitFlags member. Fields are public to permit mechanical adoption of retail accesses. Special members and rowed methods remain out of line.

#pragma once
#ifndef BFME2_WEAPONSETCLASS_H
#define BFME2_WEAPONSETCLASS_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;

class Object;
class Weapon;
class WeaponTemplateSet;
struct Coord3D;
enum AbleToAttackType;
enum CanAttackResult;
enum CommandSourceType;
enum WeaponChoiceCriteria;
enum WeaponLockType;
enum WeaponSlotType;

class WeaponSet : public Snapshot
{
public:
    WeaponSet();
    virtual ~WeaponSet();

    void updateWeaponSet(const Object *obj);
    void reloadAllAmmo(const Object *obj, bool now);
    bool isOutOfAmmo() const;
    const Weapon *findAmmoPipShowingWeapon() const;
    Weapon *findWaypointFollowingCapableWeapon();
    bool rva002C75D1(int slot, int cmdSource) const;
    bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
    void releaseWeaponLock(WeaponLockType lockType);
    bool chooseBestWeaponForTarget(const Object *obj, const Object *victim, WeaponChoiceCriteria criteria, CommandSourceType commandSource);
    CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType attackType, const Object *obj, const Object *victim, const Coord3D *pos, CommandSourceType commandSource) const;
    CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType, const Object *obj, const Object *victim, CommandSourceType commandSource) const;
    Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const;

    bool hasAnyWeapon() const { return m_filledWeaponSlotMask != 0; }
    bool hasAnyDamageWeapon() const { return m_hasDamageWeapon; }
    bool isCurWeaponLocked() const { return m_curWeaponLockedStatus != 0; }
    Weapon *getCurWeapon() { return m_weapons[m_curWeapon]; }
    const Weapon *getCurWeapon() const { return m_weapons[m_curWeapon]; }
    WeaponSlotType getCurWeaponSlot() const { return (WeaponSlotType)m_curWeapon; }

    const WeaponTemplateSet *m_curWeaponTemplateSet; // +0x04
    Weapon *m_weapons[6]; // +0x08
    int m_curWeapon; // +0x20
    int m_curWeaponLockedStatus; // +0x24
    unsigned int m_filledWeaponSlotMask; // +0x28
    int m_totalAntiMask; // +0x2C
    unsigned int m_totalDamageTypeMask; // +0x30
    bool m_hasPitchLimit; // +0x34
    bool m_hasDamageWeapon; // +0x35
    unsigned char m_field36[6]; // +0x36
    int m_ownerID; // +0x3C

protected:
    virtual void loadPostProcess() {}
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

private:
    bool isAnyWithinTargetPitch(const Object *obj, const Object *victim) const;
};

#endif
