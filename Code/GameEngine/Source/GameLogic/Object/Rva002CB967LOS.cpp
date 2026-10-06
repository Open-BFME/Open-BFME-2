// cl: /O1 /DNDEBUG /MD
//
// ?rva002CB967@Weapon@@QAEXPBVObject@@0@Z @0x002CB967 86B: Weapon LOS pair
// (thiscall, 2 args, void). Copies 12B from arg0+0x38 into a Coord3D,
// refines it through landed Weapon::getFiringLineOfSightOrigin, assigns a
// second Coord3D from landed Weapon::bfmeGetLOSVictimPos(arg0, arg1, 0),
// then calls TheTerrainLogic virtual slot 15 with (&origin, &victim).
// Weapon/Coord3D/TerrainLogic are minimal TU-local views for call
// resolution (numbered-slot idiom for TerrainLogic); exact function
// identity unproven, honest address-derived method name.
class Object;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15(void *a, void *b);
};
extern TerrainLogic *TheTerrainLogic;

class Weapon
{
public:
	void rva002CB967(const Object *a, const Object *b);

protected:
	void getFiringLineOfSightOrigin(const Object *obj, Coord3D &origin) const;

public:
	Coord3D bfmeGetLOSVictimPos(const Object *source, const Object *victim, int weaponSlot) const;

private:
	void *m_vtable;
};

// ?rva002CB967@Weapon@@QAEXPBVObject@@0@Z
void Weapon::rva002CB967(const Object *a, const Object *b)
{
	Coord3D origin;
	origin = *(const Coord3D *)((const char *)a + 0x38);
	getFiringLineOfSightOrigin(a, origin);
	Coord3D victim;
	victim = bfmeGetLOSVictimPos(a, b, 0);
	TheTerrainLogic->slot15(&origin, &victim);
}
