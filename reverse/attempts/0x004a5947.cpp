// ?rva004A5947@Rva004A5B09@@QAEXPBVObject@@PBVWeaponTemplate@@MMMM@Z
// partial score=0.99 date=2026-10-07
// ?rva004A5947@Rva004A5B09@@QAEXPBVObject@@PBVWeaponTemplate@@MMMM@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD
//
// ?rva004A5947@Rva004A5B09@@QAEXPBVObject@@PBVWeaponTemplate@@MMMM@Z @0x004A5947 450B.
// This is the sibling object's weapon emission routine; its call at 0x004A5AFD
// and the neighboring 0x004A5B09 body establish the shared object layout.

#include "../../../Libraries/Include/Lib/Coord3D.h"

class Matrix3D;
class WeaponTemplate;

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary);
};

class BitSource
{
public:
	char m_pad[0x10];
	int m_index;
};

class VTable15
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual BitSource *s15();
};

class Object
{
public:
	char m_pad[0x38];
	Coord3D m_pos;
};

class HasPositionSource
{
public:
	char m_pad[0x254];
	VTable15 *m_v;
};

class Holder
{
public:
	char m_pad[0x4C];
	unsigned m_bits;
	char m_pad2[0x10];
	FXList *m_fx;
};

class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *, const Object *, const Coord3D *);
};

extern WeaponStore *TheWeaponStore;

class TerrainLogic
{
public:
	virtual void s0(); virtual void s1(); virtual void s2();
	virtual void s3(); virtual void s4(); virtual void s5();
	virtual float getPosition(float, float, int);
};

extern TerrainLogic *TheTerrainLogic;
float Sin(float);
float Cos(float);

class Rva004A5B09
{
public:
	void rva004A5947(const Object *, const WeaponTemplate *, float, float, float, float);
	void rva004A584B(int zero, Coord3D *at);

private:
	char m_pad[4];
	Holder *m_holder;
	HasPositionSource *m_obj;
};

void Rva004A5B09::rva004A5947(const Object *obj, const WeaponTemplate *weapon, float x, float y, float radius, float angle)
{
	Holder *holder = m_holder;
	BitSource *src = m_obj->m_v->s15();
	float step = -radius;
	Coord3D at;
	if (radius > step)
	{
		do
		{
			at.x = obj->m_pos.x + x + Sin(angle) * step;
			at.y = obj->m_pos.y + y + Cos(angle) * step;
			at.z = TheTerrainLogic->getPosition(at.x, at.y, 0);
			TheWeaponStore->createAndFireTempWeapon(weapon, obj, &at);
			if (src == 0 || (holder->m_bits & (1u << (src->m_index - 1))) != 0)
				FXList::doFXPos(holder->m_fx, &at, 0, 0.0f, 0);
			step += 25.0f;
		} while (radius > step);
	}
	at.x = obj->m_pos.x + x + Sin(angle) * radius;
	at.y = obj->m_pos.y + y + Cos(angle) * radius;
	at.z = TheTerrainLogic->getPosition(at.x, at.y, 0);
	TheWeaponStore->createAndFireTempWeapon(weapon, obj, &at);
	if (src == 0 || (holder->m_bits & (1u << (src->m_index - 1))) != 0)
		FXList::doFXPos(holder->m_fx, &at, 0, 0.0f, 0);
	at.x = obj->m_pos.x + x;
	at.y = obj->m_pos.y + y;
	at.z = TheTerrainLogic->getPosition(at.x, at.y, 0);
	rva004A584B(2, &at);
}
