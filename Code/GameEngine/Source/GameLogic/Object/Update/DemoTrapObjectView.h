#ifndef BFME2_DEMO_TRAP_OBJECT_VIEW_H
#define BFME2_DEMO_TRAP_OBJECT_VIEW_H

// Local call/storage views shared by the rowed update and detonation helper.
// Both retail bodies use Object position +0x38 (the canonical Thing's
// m_cachedPos); the helper reads its module
// data at +4, Object at +8 and stores the detonation byte at +0x24.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum DamageType
{
	DAMAGE_8 = 8
};
enum DeathType
{
	DEATH_0 = 0
};
enum ObjectStatusTypes
{
	STATUS_UNDER_CONSTRUCTION = 2,
	STATUS_SOLD = 0x13
};
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};
enum Relationship
{
	RELATIONSHIP_ENEMIES = 0
};
template <int N>
class BitFlags
{
public:
	unsigned int m_bits[7];
};
class Weapon
{
public:
	unsigned char m_pad00[0x0c];
	WeaponSlotType m_slot;
};
#include "../../../Common/Thing/thing.h"
enum WeaponSetType;
enum WeaponLockType;

class Object : public Thing
{
public:
	void setWeaponSetFlag(WeaponSetType flag);
	bool setWeaponLock(WeaponSlotType slot, WeaponLockType lock);
	bool testStatus(ObjectStatusTypes s) const;
	void kill(DamageType d, DeathType t);
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Relationship getRelationship(const Object *other) const;
	// The canonical Thing ends at +0x60 (position +0x38 is its m_cachedPos).
	unsigned char m_pad60[0x438 - 0x60];
	unsigned char m_dead438;
};
struct Rva00495A2B_H04;
class Rva00495A2B
{
public:
	void rva00495A2B();
private:
	unsigned char m_pad00[4];
	Rva00495A2B_H04 *m_p04; // +0x04
	Object *m_obj08; // +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
	unsigned char m_b24; // +0x24
};

#endif
