// cl: /Ireference/shims/bfme2_ascii /O1 /MD /arch:SSE
// ?rva00492D11@Rva00492C59@@UAEXXZ at retail 0x00492D11 (154B). Slot 17 (offset
// 0x44) override of SpecialAbilityUpdate for the class of Rva00492C59 ctor
// (vtable 0x0084E1A8). Evidence: calls pinned Object::rva000B4542 0x000B4542
// plus pinned Object::rva0029660C 0x0029660C plus rowed Thing::setOrientation
// 0x0030AB9D plus rowed WeaponStore::findWeaponTemplate 0x002CB8BF plus rowed
// WeaponStore::createAndFireTempWeapon 0x002CE904 plus pinned
// SpecialAbilityUpdate::rva0045108D 0x0045108D; TheWeaponStore extern;
// ModuleData AsciiString at +0xCC; Object float at +0x44; this Coord3D at +0x44.
#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Thing
{
public:
	void setOrientation(float angle);
};

class Object
{
public:
	float rva000B4542(const Coord3D *pos) const;
	void rva0029660C(const Coord3D *pos, int v);

	unsigned char m_pad00[0x44];
	float m_44;
};

class WeaponTemplate;

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *src, const Coord3D *pos);
};

extern WeaponStore *TheWeaponStore;

class Rva00492C59ModuleData
{
public:
	unsigned char m_pad[0xCC];
	AsciiString m_CC;
};

class SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();

protected:
	const Rva00492C59ModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x44 - 0x0C];
	Coord3D m_44;
	unsigned char m_pad50[0x88 - 0x50];
};

class Rva00492C59 : public SpecialAbilityUpdate
{
public:
	virtual void rva00492D11();
};

void Rva00492C59::rva00492D11()
{
	Object *object = m_object;
	const Rva00492C59ModuleData *data = m_moduleData;
	Coord3D *pos = &m_44;
	Coord3D tmp;
	tmp.x = pos->x;
	tmp.y = pos->y;
	tmp.z = pos->z;
	float extra = object->m_44;
	float ang = object->rva000B4542(&tmp) + extra;
	object->rva0029660C(&tmp, 1);
	((Thing *)object)->setOrientation(ang);
	const WeaponTemplate *wt = TheWeaponStore->findWeaponTemplate(data->m_CC);
	if (wt != 0)
		TheWeaponStore->createAndFireTempWeapon(wt, m_object, pos);
	SpecialAbilityUpdate::rva0045108D();
}
