// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX-
//
// ?isWithinAttackRange@Weapon@@QBE_NPBVObject@@0MH@Z @0x002CB933 52B
// Evidence: pinned name; BFME1 donor game/GameEngine/Source/GameLogic/Object/Weapon_isWithinAttackRange.cpp
// (isWithinAttackRange overloads forwarding source/target plus positions at +0x38 into inner);
// retail outer takes (source target float int) and forwards both plus derived positions.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	char m_pad[0x38];
	Coord3D m_position;
};

class Rva002CB35CObj
{
public:
	bool rva002CB35C(int a, void *b, void *c, void *d, float e, int f);
};

class Weapon
{
public:
	bool isWithinAttackRange(const Object *source, const Object *target, float extra, int flag) const;
};

bool Weapon::isWithinAttackRange(const Object *source, const Object *target, float extra, int flag) const
{
	if (source && target)
		return ((Rva002CB35CObj *)this)->rva002CB35C((int)source, (void *)&source->m_position, (void *)target, (void *)&target->m_position, extra, flag);
	return false;
}
