// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?isOutOfAmmo@WeaponSet@@QBE_NXZ @0x002C73CE, 41B.
// WeaponSet::isOutOfAmmo. Returns true when every present weapon reports
// OUT_OF_AMMO (1), skipping null slots. Retail scans the six slots at +0x8.
// Evidence: neighbour WeaponSetRvaSlotSearch.cpp proves six slots at +0x8;
// caller 0x0028ADD5 does add ecx 0x330 then jmp here (Object WeaponSet
// forwarder); callee ?getStatus@Weapon@@QBE?AW4WeaponStatus@@XZ is rowed.
// Donor: ZH WeaponSet::isOutOfAmmo verbatim except WEAPONSLOT_COUNT 6.
//
// ?isAnyWithinTargetPitch@WeaponSet@@ABE_NPBVObject@@0@Z @0x002C7362, 60B.
// WeaponSet::isAnyWithinTargetPitch (private). Returns true when no pitch
// limit or any of the six slots at +0x8 reports isWithinTargetPitch.
// Evidence: [ecx+0x34] early-out plus six-slot loop calling rowed
// ?isWithinTargetPitch@Weapon@@QBE_NPBVObject@@0@Z; caller 0x002C7BC3.
// Donor: ZH WeaponSet::isAnyWithinTargetPitch verbatim except 6 slots.

enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO,
	BETWEEN_FIRING_SHOTS,
	RELOADING_CLIP,
	PRE_ATTACK
};

class Object;

#include "../../../Include/GameLogic/Weapon.h"

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0, WEAPONSLOT_COUNT = 6
};
enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
};
enum WeaponChoiceCriteria
{
 PREFER_MOST_DAMAGE=0, PREFER_LONGEST_RANGE=1, PREFER_SPECIAL=2,
 PREFER_SMALLEST_RANGE_ERROR=3, PREFER_RANDOM=4, PREFER_TEMPLATE_DEFAULT=5
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2
};
enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};
enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0,
	ATTACK_TUNNEL_NETWORK_GUARD = 4
};
class Xfer;
struct EmitVtableTag;
struct Coord3D;
class WeaponTemplateSet;
class WeaponSet : public Snapshot
{
public:
	WeaponSet();
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);
public:
	bool isOutOfAmmo() const;
	void reloadAllAmmo(const Object *obj, bool now);
private:
	bool isAnyWithinTargetPitch(const Object *obj, const Object *victim) const;
public:
	const Weapon *findAmmoPipShowingWeapon() const;
	Weapon *findWaypointFollowingCapableWeapon();
	WeaponSet(EmitVtableTag *);
	bool rva002C75D1(int slot, int cmdSource) const;
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
	void updateWeaponSet(const Object *);
	void releaseWeaponLock(WeaponLockType);
	bool chooseBestWeaponForTarget(const Object *, const Object *, WeaponChoiceCriteria, CommandSourceType);
	CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType, const Object *, const Object *, const Coord3D *, CommandSourceType) const;
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType, const Object *, const Object *, CommandSourceType) const;
	virtual ~WeaponSet();
private:
	const WeaponTemplateSet *m_set; // +0x04
	Weapon *m_weapons[6]; // +0x08
	int m_curWeapon; // +0x20
	int m_curWeaponLockedStatus; // +0x24
	int m_filled; // +0x28
	int m_anti; // +0x2C
	int m_damage; // +0x30
	unsigned char m_pitch; // +0x34
	unsigned char m_hasDamage; // +0x35
	unsigned char m_slotFlags[6]; // +0x36
	int m_ownerID; // +0x3C
};

bool WeaponSet::isOutOfAmmo() const
{
	for (int i = 0; i < 6; ++i) {
		const Weapon *weapon = m_weapons[i];
		if (weapon == 0)
			continue;
		if (weapon->getStatus() != OUT_OF_AMMO)
			return false;
	}
	return true;
}

bool WeaponSet::isAnyWithinTargetPitch(const Object *obj, const Object *victim) const
{
	if (!m_pitch)
		return true;
	for (int i = 0; i < 6; ++i) {
		const Weapon *weapon = m_weapons[i];
		if (weapon && weapon->isWithinTargetPitch(obj, victim))
			return true;
	}
	return false;
}

void WeaponSet::reloadAllAmmo(const Object *obj, bool now)
{
	for (int i = 0; i < 6; ++i) {
		Weapon *weapon = m_weapons[i];
		if (weapon != 0) {
			if (now)
				weapon->loadAmmoNow(obj);
			else
				weapon->reloadAmmo(obj);
		}
	}
}
