// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX-
//
// ?isWithinAttackRange@Weapon@@QBE_NPBVObject@@0MH@Z @0x002CB933 52B
// Evidence: pinned name; BFME1 donor game/GameEngine/Source/GameLogic/Object/Weapon_isWithinAttackRange.cpp
// (isWithinAttackRange overloads forwarding source/target plus positions at +0x38 into inner);
// retail outer takes (source target float int) and forwards both plus derived positions.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	char m_pad[0x38];
	Coord3D m_position;
};

#include "../../../Include/GameLogic/Weapon.h"

// The six-slot worker 0x002CB35C (WeaponRva002CB2D1Range.cpp) is called
// through a member-pointer cast that keeps retail's untyped argument shape.
typedef bool (Weapon::*Rva002CB35CWorker)(Object *, const Coord3D *, Object *, const Coord3D *, float, bool);
typedef bool (Weapon::*Rva002CB35CShape)(int, void *, void *, void *, float, int);
#define RVA002CB35C_CALL(self) (((Weapon *)(self))->*reinterpret_cast<Rva002CB35CShape>(static_cast<Rva002CB35CWorker>(&Weapon::isWithinAttackRange)))

bool Weapon::isWithinAttackRange(const Object *source, const Object *target, float extra, int flag) const
{
	if (source && target)
		return RVA002CB35C_CALL(this)((int)source, (void *)&source->m_position, (void *)target, (void *)&target->m_position, extra, flag);
	return false;
}

// ?isWithinAttackRange@Weapon@@QBEDPAVObject@@PAXMH@Z @0x002CB902 49B
// Evidence: pin address-named; BFME1 donor Weapon_isWithinAttackRange.cpp Coord3D overload
// forwards (source sourcePos 0 pos extra flag) into 0x002CB35C; neighbour 0x002CB933 same inner.
char Weapon::isWithinAttackRange(Object *source, void *pos, float extra, int flag) const
{
	if (source && pos)
		return RVA002CB35C_CALL(this)((int)source, (void *)&source->m_position, 0, pos, extra, flag);
	return 0;
}
