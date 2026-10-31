// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Two WeaponSet slot-search leaves (retail 0x002C73F7/37 + 0x002C741C/43).
// Both scan the six slots at +0x8 for the first entry whose state link at
// +0x4 carries the wanted flag byte (+0x133 forward, +0x132 reverse) and
// return the slot or null. /O1 selects the retail size idioms: xor-before-add
// init order, push-5/pop-reg small immediates, and the indexed reload on the
// reverse find's return (the check itself walks a lea cursor).

struct RvaWeaponSlotState
{
	char m_pad[0x132];				// +0x000..+0x132 unknown
	bool m_flag132;					// +0x132
	bool m_flag133;					// +0x133
};

struct RvaWeaponSlot
{
	char m_pad[4];					// +0x000..+0x004 unknown
	RvaWeaponSlotState *m_state;	// +0x004
};

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Weapon;

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
class Object;
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

// ?findAmmoPipShowingWeapon@WeaponSet@@QBEPBVWeapon@@XZ (ZH WeaponSet::findAmmoPipShowingWeapon)
const Weapon *WeaponSet::findAmmoPipShowingWeapon() const
{
	int i = 0;
	RvaWeaponSlot **pp = (RvaWeaponSlot **)((char *)this + 8);
	for (; i < 6; i++, pp++)
	{
		RvaWeaponSlot *slot = *pp;
		if (slot != 0 && slot->m_state->m_flag133)
			return (const Weapon *)slot;
	}
	return 0;
}

// ?findWaypointFollowingCapableWeapon@WeaponSet@@QAEPAVWeapon@@XZ (ZH WeaponSet::findWaypointFollowingCapableWeapon)
Weapon *WeaponSet::findWaypointFollowingCapableWeapon()
{
	int i = 5;
	RvaWeaponSlot **pp = (RvaWeaponSlot **)((char *)this + 0x1C);
	for (; i >= 0; i--, pp--)
	{
		RvaWeaponSlot *slot = *pp;
		if (slot != 0 && slot->m_state->m_flag132)
			return (Weapon *)m_weapons[i];
	}
	return 0;
}
