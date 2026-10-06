// cl: /DNDEBUG /MD /EHsc
//
// ?allocateNewWeapon@WeaponStore@@QBEPAVWeapon@@PBVWeaponTemplate@@W4WeaponSlotType@@@Z @0x0028AA81 58B
// Donor: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/WeaponStore_allocateNewWeapon_Thunk.cpp
//   (BFME1 factory returns new Weapon with tmpl plus slot) plus ZH Weapon.h friend allocate.
// Target evidence: size 0x60 new via 0x0002FDA0; ctor 0x002CC23D pinned protected Weapon ctor;
//   vtable 0x0080214C at +0 in ctor body; 21 callers are weapon-creation sites.

class WeaponTemplate;

enum WeaponSlotType
{
	WEAPON_SLOT_PRIMARY = 0
};

// ?0Weapon@@IAE@PBVWeaponTemplate@@W4WeaponSlotType@@@Z placeholder: real class is 0x60;
// only the size and ctor matter here.
class Weapon
{
	friend class WeaponStore;

protected:
	Weapon(const WeaponTemplate *tmpl, WeaponSlotType slot);

private:
	char m_bfme_body[0x60];
};

class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const;
};

inline Weapon *WeaponStore::allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const
{
	return new Weapon(tmpl, slot);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
Weapon * (WeaponStore::*_bfmeInlineAnchor_WeaponStoreAllocateNewWeapon_0)(const WeaponTemplate *tmpl, WeaponSlotType slot) const = &WeaponStore::allocateNewWeapon;
