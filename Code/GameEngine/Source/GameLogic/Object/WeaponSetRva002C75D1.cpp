// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002C75D1@WeaponSet@@QBE_NHH@Z @0x002C75D1, 41B.
// WeaponSet slot auto-choose check. Returns true when the per-slot byte at
// +0x36 is set, otherwise tests the template auto-choose mask at +0x2C for
// bit (1 << cmdSource). Retail reads byte [this+0x36+slot] then
// [[this+4]+slot*4+0x2C] & (1 << cmdSource).
// Evidence: caller 0x002C7E25 passes slot in 0..5 and CommandSource;
// [this+4] is WeaponTemplateSet whose +0x2C array stride 4 matches
// m_autoChooseMask[6] (+0x2C..+0x43, next array at +0x44proven by 0x002C7501
// KindOf callers). Neighbour WeaponSetRvaSlotSearch.cpp proves six slots.

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class WeaponTemplate;
class ThingTemplate;
class INI;
enum WeaponSlotType { PRIMARY_WEAPON = 0, WEAPONSLOT_COUNT = 6 };
// Native masks shared with the parser and weapon selection views.
template<int N> class BitFlags;
template<> class BitFlags<218> { public: bool any() const; private: unsigned m_bits[7]; };
class ModelConditionFlags { public: bool rva000B3EB3() const; private: unsigned m_bits[19]; };
enum WeaponChoiceCriteria
{
 PREFER_MOST_DAMAGE=0, PREFER_LONGEST_RANGE=1, PREFER_SPECIAL=2,
 PREFER_SMALLEST_RANGE_ERROR=3, PREFER_RANDOM=4, PREFER_TEMPLATE_DEFAULT=5
};
class WeaponTemplateSet
{
private:
	static void parseWeapon(INI *ini, void *instance, void *store, const void *userData);
	static void parseAutoChoose(INI *ini, void *instance, void *store, const void *userData);
	static void parsePreferredAgainst(INI *ini, void *instance, void *store, const void *userData);
public:
	static void rva002C8C47(INI *ini, void *instance, void *store, const void *userData);
	static void rva002C883E(INI *ini, void *instance, void *store, const void *userData);
private:
	unsigned char m_unreconstructed_00[0x14]; // +0x00
public:
	const WeaponTemplate *m_weapons[WEAPONSLOT_COUNT]; // +0x14 +0x14
	unsigned int m_autoChooseMask[WEAPONSLOT_COUNT]; // +0x2C +0x2C
	BitFlags<218> m_preferredAgainst[WEAPONSLOT_COUNT]; // +0x44 +0x44
	BitFlags<218> m_onlyAgainst[WEAPONSLOT_COUNT]; // +0xEC +0xEC
	ModelConditionFlags m_onlyInCondition[WEAPONSLOT_COUNT]; // +0x194 +0x194
	bool m_sharedReload; // +0x35C
	bool m_sharedLock; // +0x35D
	char m_pad35E[0x2];
	WeaponChoiceCriteria m_defaultCriteria; // +0x360
	bool m_364; // +0x364
	char m_pad365[0x3];
};

enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
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
class Weapon;
struct EmitVtableTag;
struct Coord3D;
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

bool WeaponSet::rva002C75D1(int slot, int cmdSource) const
{
	if (m_slotFlags[slot])
		return true;
	if ((m_set->m_autoChooseMask[slot] & (1 << cmdSource)) != 0)
		return true;
	return false;
}
