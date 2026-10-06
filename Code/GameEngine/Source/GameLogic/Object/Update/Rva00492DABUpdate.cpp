// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00492DAB@Rva00492C59@@UAEXXZ at retail 0x00492DAB (101B). Slot 22 (offset
// 0x58) override of SpecialAbilityUpdate slot 22 (0x004508B7, pinned) for the
// class of Rva00492C59 ctor (vtable 0x0084E1A8). Evidence: calls rowed
// WeaponStore::findWeaponTemplate 0x002CB8BF plus rowed
// WeaponStore::createAndFireTempWeapon 0x002CE904 plus pinned
// SpecialAbilityUpdate::rva004508B7 0x004508B7 plus rowed
// Object::rva002900E0 0x002900E0; TheWeaponStore plus TheGameLogic externs;
// ModuleData weapon AsciiString at +0xD0 plus int at +0xC8; Object pos at +0x38.
#include "ascii_string.h"

struct Coord3D { float x, y, z; };

class Thing;
class ModuleData;
class WeaponTemplate;

class Object
{
public:
	void rva002900E0(int frame);

	char m_pad00[0x38];
	Coord3D m_position;
};

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, const Coord3D *pos);
};
extern WeaponStore *TheWeaponStore;

class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

class SpecialAbilityUpdate
{
public:
	virtual void rva004508B7();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x88 - 0x0C];
};

class Rva00492C59ModuleData
{
public:
	unsigned char m_pad[0xC8];
	int m_C8;
	unsigned char m_padCC[4];
	AsciiString m_D0;
};

class Rva00492C59 : public SpecialAbilityUpdate
{
public:
	virtual void rva00492DAB();
};

void Rva00492C59::rva00492DAB()
{
	Object *object = m_object;
	const Rva00492C59ModuleData *data = (const Rva00492C59ModuleData *)m_moduleData;
	if (data->m_D0.getLength() > 0)
	{
		const WeaponTemplate *wt = TheWeaponStore->findWeaponTemplate(data->m_D0);
		if (wt != 0)
			TheWeaponStore->createAndFireTempWeapon(wt, object, &object->m_position);
	}
	SpecialAbilityUpdate::rva004508B7();
	object->rva002900E0(TheGameLogic->m_frame + data->m_C8);
}
