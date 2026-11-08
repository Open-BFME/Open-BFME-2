// cl: /O1 /DNDEBUG /MD
//
// ??_GWeaponSet@@UAEPAXI@Z, retail 0x002C75B5 (28 bytes): slot 0
// of vtable 0x00C0089C, whose slot-2 name getter returns "WeaponSet" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x002C7311 and then the global operator delete when bit 0 of
// the flags is set. That destructor re-stores vtable 0x00C0089C, which
// identifies it as WeaponSet::~WeaponSet (pinned in reverse/symbols.csv).
// Class shape from Zero Hour's GameLogic/WeaponSet.h (public ~WeaponSet).
// BFME 2's form frees through the global operator delete.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

// The base is the canonical Snapshot (vtable 0x00BBB554), and WeaponSet's
// three Snapshot overrides are declared as in WeaponSetDtor.cpp and
// WeaponSetXfer.cpp, so every ??_7WeaponSet copy agrees.
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

struct EmitVtableTag;

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
class Weapon;
struct Coord3D;
class WeaponTemplateSet;
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

// ?<WeaponSet::WeaponSet> absent-from-retail
WeaponSet::WeaponSet(EmitVtableTag *)
{
}
