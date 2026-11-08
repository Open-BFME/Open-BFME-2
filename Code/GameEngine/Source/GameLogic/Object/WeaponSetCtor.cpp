// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??0WeaponSet@@QAE@XZ @0x002C72D5, 60B.
// WeaponSet::WeaponSet. Zero-initializing ctor: vtable 0x0080089C plus null
// template set at +0x4, six slots at +0x8, ints at +0x20..+0x30, flags at
// +0x34/+0x35, per-slot bytes at +0x36[6] and tail at +0x3C.
// Evidence: neighbour WeaponSetIsOutOfAmmo.cpp proves six slots at +0x8 and
// hasPitchLimit at +0x34; WeaponSetRva002C75D1.cpp proves template set at
// +0x4 and byte array at +0x36[6]; next row 0x002C7362 is WeaponSet method;
// ZH donor WeaponSet::WeaponSet zeroes the same fields.
// ?isAnyWithinTargetPitch@WeaponSet@@ABE_NPBVObject@@0@Z is rowed.

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

// The destructor and scalar deleter use the same Snapshot base. Retail's
// first store installs WeaponSet's table; it is the compiler-owned vfptr,
// not a second data member occupying the base at +0.
class Weapon;
class WeaponTemplateSet;

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
class Object;
struct EmitVtableTag;
struct Coord3D;
class WeaponSet : public Snapshot
{
public:
	WeaponSet();
protected:
	virtual const char *GetSnapshotName() const;
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

WeaponSet::WeaponSet()
{
	m_curWeapon = 0;
	m_curWeaponLockedStatus = 0;
	m_set = 0;
	m_filled = 0;
	m_anti = 0;
	m_damage = 0;
	m_pitch = 0;
	m_hasDamage = 0;
	for (int i = 0; i < 6; ++i) {
		m_weapons[i] = 0;
		m_slotFlags[i] = 0;
	}
	m_ownerID = 0;
}
