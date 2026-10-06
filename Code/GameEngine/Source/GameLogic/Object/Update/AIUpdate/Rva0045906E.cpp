// cl: /DNDEBUG /MD
//
// ?rva0045906E@Rva0045906E@@QAEX_N@Z, retail 0x0045906E 87B. Unlocks 3 callers.
// Bool selects setStatus 0x36 true/false plus set/clearWeaponSetFlag 0x16 plus
// AIUpdate slot142 8/0 via Object+0x258 with shared tail. Prev EnragedXfer.

enum ObjectStatusTypes
{
	Status_36 = 0x36
};

enum WeaponSetType
{
	Weapon_16 = 0x16
};

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<142>
{
public:
	virtual void slot142(int);
};

class Object
{
public:
	void setStatus(ObjectStatusTypes t, bool b);
	void setWeaponSetFlag(WeaponSetType t);
	void clearWeaponSetFlag(WeaponSetType t);
	unsigned char m_pad00[0x258];
	AIUpdateInterface *m_258;
};

class Rva0045906E
{
public:
	void rva0045906E(bool b);
private:
	unsigned char m_pad00[8];
	Object *m_08;
};

void Rva0045906E::rva0045906E(bool b)
{
	Object *obj = m_08;
	if (b)
	{
		obj->setStatus(Status_36, true);
		obj->setWeaponSetFlag(Weapon_16);
		AIUpdateInterface *p = obj->m_258;
		if (p == 0)
			return;
		p->slot142(8);
	}
	else
	{
		obj->setStatus(Status_36, false);
		obj->clearWeaponSetFlag(Weapon_16);
		AIUpdateInterface *p = obj->m_258;
		if (p == 0)
			return;
		p->slot142(0);
	}
}
