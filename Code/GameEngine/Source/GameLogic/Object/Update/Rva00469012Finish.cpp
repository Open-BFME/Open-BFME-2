// cl: /DNDEBUG /MD /EHsc
//
// ?rva00469012@Rva00469012@@QAE_NPAVObject@@PBUCoord3D@@@Z, retail 0x00469012, 99 bytes.
// Behind check: dx dy from arg Coord minus Object +0x38/+0x3C, null guard on
// Thing at this+8, dot with Thing::getUnitDirectionVector2D, true when dot<0.
// Callers at 0x00474A8E 0x00476F41; honest-address method.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	float m_38_unused[14];
	float m_38;
	float m_3C;
};

class Thing
{
public:
	void getUnitDirectionVector2D(Coord3D &out) const;
};

class Rva00469012
{
public:
	bool rva00469012(Object *a, Coord3D const *b);
	char m_pad[8];
	Thing *m_thing;
};

bool Rva00469012::rva00469012(Object *a, Coord3D const *b)
{
	Coord3D delta;
	delta.x = b->x;
	delta.y = b->y;
	delta.x -= a->m_38;
	delta.y -= a->m_3C;
	if (m_thing == 0)
		return false;
	Coord3D dir;
	m_thing->getUnitDirectionVector2D(dir);
	volatile Coord3D *pd = &delta;
	if (pd->x * dir.x + pd->y * dir.y < 0.0f)
		return true;
	return false;
}
