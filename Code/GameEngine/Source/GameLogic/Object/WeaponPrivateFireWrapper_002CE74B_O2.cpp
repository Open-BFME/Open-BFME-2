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
#include "../../../Include/GameLogic/Weapon.h"
bool Weapon::rva002CE74B(const Object *source, const Object *target)
{
    return privateFireWeapon(source, &source->m_cachedPos, target, target->m_id, 0, 1, 1, 0, 0);
}
