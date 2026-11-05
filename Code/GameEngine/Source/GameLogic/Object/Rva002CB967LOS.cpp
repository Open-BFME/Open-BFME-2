// cl: /O1 /DNDEBUG /MD
//
// ?rva002CB967@Weapon@@QAEXPBVObject@@0@Z @0x002CB967 86B: Weapon LOS pair
// (thiscall, 2 args, void). Copies 12B from arg0+0x38 into a Coord3D,
// refines it through landed Weapon::getFiringLineOfSightOrigin, assigns a
// second Coord3D from landed Weapon::bfmeGetLOSVictimPos(arg0, arg1, 0),
// then calls TheTerrainLogic virtual slot 15 with (&origin, &victim).
// Calls use the canonical Weapon, Coord3D and TerrainLogic headers.
// The enclosing function identity remains unproven and address-derived.
class Object;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

#include "../../../Include/GameLogic/Weapon.h"

// ?rva002CB967@Weapon@@QAEXPBVObject@@0@Z
void Weapon::rva002CB967(const Object *object, const Object *b)
{
	Coord3D origin;
	origin = *(const Coord3D *)((const char *)object + 0x38);
	getFiringLineOfSightOrigin(object, origin);
	Coord3D victim;
	victim = bfmeGetLOSVictimPos(object, b, 0);
	TheTerrainLogic->isClearLineOfSight(origin, victim);
}
