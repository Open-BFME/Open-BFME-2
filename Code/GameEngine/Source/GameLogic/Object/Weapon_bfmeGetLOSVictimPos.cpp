// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object

class Object;
class WeaponTemplate;

struct Coord3D
{
	__forceinline Coord3D(WeaponTemplate *weaponTemplate, const Object *source,
		const Object *victim, int weaponSlot);

	float x, y, z;
};

struct TargetCoord;
#include "../../../Include/GameLogic/WeaponTemplate.h"

Coord3D::Coord3D(WeaponTemplate *weaponTemplate, const Object *source,
	const Object *victim, int weaponSlot)
{
	typedef Coord3D *(WeaponTemplate::*AimPositionCall)(Coord3D *, const Object *, const Object *, int);
	(weaponTemplate->*reinterpret_cast<AimPositionCall>(&WeaponTemplate::adjustTargetPositionOnVictim))(this, source, victim, weaponSlot);
}

class Weapon
{
public:
	Coord3D bfmeGetLOSVictimPos(const Object *source, const Object *victim,
		int weaponSlot) const;

private:
	void *m_vtable;
	WeaponTemplate *m_template;
};

Coord3D Weapon::bfmeGetLOSVictimPos(const Object *source, const Object *victim,
	int weaponSlot) const
{
	return Coord3D(m_template, source, victim, weaponSlot);
}
