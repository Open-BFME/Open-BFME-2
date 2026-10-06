// cl: /DNDEBUG /MD
// ?rva00263077@AIUpdateInterface@@QAE_NPAVObject@@@Z @0x00263077 126B
// Evidence: chain lane calls rowed isWithinAttackRange 0x002CB933; neighbours rva0026304D and rva002630F5 prove AIUpdateInterface with m_object at +0x08.

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

class Weapon
{
public:
	Bool isWithinAttackRange(const Object *source, const Object *target, float extra, int flag) const;
	char m_pad00[4];
	Rva002C9400ByteField *m_field4; // +0x04
};

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
	char m_pad00[8];
	Object *m_object; // +0x08
	char m_pad0C[0x3C1 - 0x0C];
	unsigned char m_3C1; // +0x3C1
public:
	Bool rva00263077(Object *target);
};

Bool AIUpdateInterface::rva00263077(Object *target)
{
	const Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon != 0)
	{
		if (!weapon->isWithinAttackRange(m_object, target, 0.0f, 1))
		{
			if (!((Rva002C9400ByteField *)weapon->m_field4)->get())
			{
				if (!((Rva002C9407ByteField *)weapon->m_field4)->get())
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
