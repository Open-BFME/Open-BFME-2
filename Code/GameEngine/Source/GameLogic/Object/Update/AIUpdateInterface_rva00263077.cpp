// cl: /DNDEBUG /MD
// ?allow@Rva00263077Filter@@UAE_NPAVObject@@@Z @0x00263077 126B
// Evidence: chain lane calls rowed isWithinAttackRange 0x002CB933. The body is
// slot 1 (allow) of partition filter vftable 0x00BF91F0, whose object is at
// +0x08 (constructor copy 0x00263061); the +0x3C1 byte is on that object's AI.

typedef bool Bool;

class Object;
class Player;
class Weapon;

class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};

class Rva002C9407ByteField
{
public:
	unsigned char get() const;
};

#include "../../../../Include/GameLogic/Weapon.h"

class Player
{
public:
	char m_pad00[0x5C];
	int m_5C; // +0x5C
};

class AIUpdateInterface;

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Player *getControllingPlayer() const;
	char m_pad00[0x249];
	unsigned char m_249; // +0x249
	char m_pad24A[0x258 - 0x24A];
	AIUpdateInterface *m_ai; // +0x258
};

class AIUpdateInterface
{
public:
	char m_pad00[0x3C1];
	unsigned char m_3C1; // +0x3C1
};

class Rva00263077Filter
{
public:
	virtual ~Rva00263077Filter();
	virtual Bool allow(Object *target);
	char m_pad04[4];
	Object *m_object; // +0x08
};

Bool Rva00263077Filter::allow(Object *target)
{
	const Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon != 0)
	{
		if (!weapon->isWithinAttackRange((const Object *)m_object, (const Object *)target, 0.0f, 1))
		{
			if (!((Rva002C9400ByteField *)weapon->m_template)->get())
			{
				if (!((Rva002C9407ByteField *)weapon->m_template)->get())
				{
					if (m_object->getControllingPlayer()->m_5C == 0)
					{
						Object *owner = m_object;
						AIUpdateInterface *ai = owner->m_ai;
						if (ai != 0)
						{
							if (ai->m_3C1 == 0)
							{
								if (owner->m_249 == 0)
									return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}
