// cl: /DNDEBUG /MD /EHs-c-
// Donor provenance: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Weapon_privateFireWeaponWrappers.cpp
// Target callers establish Weapon receivers; Object fields are position +0x38
// and ID +0x74. Address-based method names and control arguments remain neutral.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Object { public: char m_pad[0x38]; Coord3D m_position; char m_pad44[0x30]; int m_id; };

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern GameLogic *TheGameLogic;
#include "../../../Include/GameLogic/Weapon.h"
bool Weapon::fireWeapon(const Object *source, const Coord3D *pos, int *projectileID)
{
	return privateFireWeapon(source, &source->m_position, 0, 0, pos, 0, 0, 0, projectileID);
}

bool Weapon::rva002CE6C5(const Object *source, int targetID, const Object *target, int *projectileID)
{
	return privateFireWeapon(source, &source->m_position, target, targetID, 0, 0, 0, 0, projectileID);
}

Object *Weapon::forceFireWeapon(const Object *source, const Coord3D *pos)
{
	int id = 0;
	privateFireWeapon(source, &source->m_position, 0, 0, pos, 1, 0, 0, &id);
	return TheGameLogic->findObjectByID((ObjectID)id);
}

bool Weapon::fireProjectileDetonationWeapon(const Object *object, const Coord3D *a2, const Coord3D *a3, int a4)
{
	return privateFireWeapon(object, a2, 0, 0, a3, 1, 0, a4, 0);
}

// 0x002CE7A4 56B: object-target sibling of forceFireWeapon above: id=0,
// privateFireWeapon(source, &source->m_position, target, target->m_id, 0, 1,
// 0, 0, &id) via pinned 0x002CE30A, then findObjectByID(id). Entry ecx
// passes through as the Weapon this for privateFireWeapon; ret 8 with two
// stack args. Callers in 0x004911AE prove (source target) order.
Object *Weapon::forceFireWeapon(const Object *source, const Object *target)
{
	int id = 0;
	privateFireWeapon(source, &source->m_position, target, target->m_id, 0, 1, 0, 0, &id);
	return TheGameLogic->findObjectByID((ObjectID)id);
}
