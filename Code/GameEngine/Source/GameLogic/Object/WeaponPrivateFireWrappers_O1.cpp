// cl: /DNDEBUG /MD /EHs-c-
// Donor provenance: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Weapon_privateFireWeaponWrappers.cpp
// Target callers establish Weapon receivers; Object fields are position +0x38
// and ID +0x74. Address-based method names and control arguments remain neutral.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Common/Thing/thing.h"

#include "../../Common/GameLogicObjectLookupView.h"

class Object : public Thing
{
public:
	char m_pad060[0x74 - 0x60];
	ObjectID m_id;
};

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern GameLogic *TheGameLogic;
#include "../../../Include/GameLogic/Weapon.h"
bool Weapon::fireWeapon(const Object *source, const Coord3D *pos, int *projectileID)
{
	return privateFireWeapon(source, &source->m_cachedPos, 0, 0, pos, 0, 0, 0, projectileID);
}

bool Weapon::rva002CE6C5(const Object *source, int targetID, const Object *target, int *projectileID)
{
	return privateFireWeapon(source, &source->m_cachedPos, target, targetID, 0, 0, 0, 0, projectileID);
}

Object *Weapon::forceFireWeapon(const Object *source, const Coord3D *pos)
{
	int id = 0;
	privateFireWeapon(source, &source->m_cachedPos, 0, 0, pos, 1, 0, 0, &id);
	return TheGameLogic->findObjectByID((ObjectID)id);
}

bool Weapon::fireProjectileDetonationWeapon(const Object *object, const Coord3D *sourcePos, const Coord3D *targetPos, int extraBonusFlags)
{
	return privateFireWeapon(object, sourcePos, 0, 0, targetPos, 1, 0, extraBonusFlags, 0);
}

// 0x002CE7A4 56B: object-target sibling of forceFireWeapon above: id=0,
// privateFireWeapon(source, &source->m_cachedPos, target, target->m_id, 0, 1,
// 0, 0, &id) via pinned 0x002CE30A, then findObjectByID(id). Entry ecx
// passes through as the Weapon this for privateFireWeapon; ret 8 with two
// stack args. Callers in 0x004911AE prove (source target) order.
Object *Weapon::forceFireWeapon(const Object *source, const Object *target)
{
	int id = 0;
	privateFireWeapon(source, &source->m_cachedPos, target, target->m_id, 0, 1, 0, 0, &id);
	return TheGameLogic->findObjectByID((ObjectID)id);
}
