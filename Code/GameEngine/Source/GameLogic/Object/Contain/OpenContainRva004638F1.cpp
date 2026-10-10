// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva004638F1@OpenContain@@UAEXPAVObject@@@Z @0x004638F1 42B
// OpenContain slot-40 add-rider: push rider as int into +0x34 list<int>,
// bump +0x38, and bump +0x48 when rider template kind bit1 set.
// Evidence: vslot 78 of 0x00848AA0 SlaughterHordeContain; pin OpenContain;
// callers 0x0047C155 and HordeSiege override 0x0047D17E; neighbours
// Rva004DD206TwoTreeConstructor and HordeTransportContainRva00463A4D.
#include <list>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class ThingTemplate
{
public:
	char m_pad[0x10C];
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	void *m_vtable;
	ThingTemplate *m_template;
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos;		// +0x38
};

class OpenContain
{
public:
	virtual void rva004638F1(Object *rider);
	virtual Object *rva004632E0(const Coord3D *pos);
private:
	char m_pad[0x30];
	_STL::list<int> m_list;
	int m_38;
	char m_pad2[0x48 - 0x3C];
	int m_48;
};

void OpenContain::rva004638F1(Object *rider)
{
	m_list.push_back((const int &)rider);
	++m_38;
	if (*(unsigned char *)((char *)rider->m_template + 0x10C) & 2)
		++m_48;
}

// ?rva004632E0@OpenContain@@UAEPAVObject@@PBUCoord3D@@@Z @0x004632E0 91B (RET 4):
// the shared contain-interface slot every OpenContain-derived table holds
// (e.g. 0x008434A4, 0x00843B64): the contained object nearest, in the ground
// plane, to the given position, or null when nothing is inside.
Object *OpenContain::rva004632E0(const Coord3D *pos)
{
	Object *closest = 0;
	float closestDistSqr = 3.402823466e+38f;
	for (_STL::list<int>::iterator it = m_list.begin(); it != m_list.end(); ++it)
	{
		Object *obj = (Object *)*it;
		if (obj)
		{
			float dx = pos->x - obj->getPosition()->x;
			float dy = pos->y - obj->getPosition()->y;
			float distSqr = dx * dx + dy * dy;
			if (closest == 0 || distSqr < closestDistSqr)
			{
				closest = obj;
				closestDistSqr = distSqr;
			}
		}
	}
	return closest;
}
