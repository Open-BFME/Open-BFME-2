// ?rva00462BFF@OpenContain@@UAE_NPBVObject@@0@Z
// partial score=0.9 date=2026-10-11
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

// The contain-interface slots below run with `this` at the interface, module
// +0x20: module data at -0x1C, the owner at -0x18, the rider list at +0x34.
struct OpenContainModuleData
{
	char m_pad00[0x68];
	float m_exitHeightRange;	// +0x68
};
class OpenContainPrimary
{
public:
	virtual void slot0();
protected:
	const OpenContainModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
	char m_pad0C[0x20 - 0x0C];
};
class ContainModuleInterface
{
public:
	virtual void rva004638F1(Object *rider) = 0;
	virtual Object *rva004632E0(const Coord3D *pos) = 0;
	virtual bool rva00462BFF(const Object *from, const Object *toward) = 0;
};
class OpenContain : public OpenContainPrimary, public ContainModuleInterface
{
public:
	virtual void rva004638F1(Object *rider);
	virtual Object *rva004632E0(const Coord3D *pos);
	virtual bool rva00462BFF(const Object *from, const Object *toward);
private:
	char m_pad24[0x54 - 0x24];
	_STL::list<int> m_list;		// +0x54
	int m_38;			// +0x58
	char m_pad2[0x68 - 0x5C];
	int m_48;			// +0x68
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

// ?rva00462BFF@OpenContain@@UAE_NPBVObject@@0@Z @0x00462BFF 115B (RET 8): the
// shared contain-interface slot 13 entries before 0x004632E0. True when both
// objects exist, the module data's height range (+0x68) is not negative, the
// first object is not higher above the container than that range, and the
// container lies on the second object's side of the first (non-negative dot
// product of container-from and toward-from in the ground plane).
bool OpenContain::rva00462BFF(const Object *from, const Object *toward)
{
	if (!from || !toward)
		return false;
	const OpenContainModuleData *data = m_moduleData;
	if (data->m_exitHeightRange < 0.0f)
		return false;
	const Object *me = m_object;
	if (from->getPosition()->z - me->getPosition()->z > data->m_exitHeightRange)
		return false;
	Coord3D towardDir, meDir;
	towardDir.x = toward->getPosition()->x - from->getPosition()->x;
	towardDir.y = toward->getPosition()->y - from->getPosition()->y;
	meDir.x = me->getPosition()->x - from->getPosition()->x;
	meDir.y = me->getPosition()->y - from->getPosition()->y;
	if (meDir.x * towardDir.x + meDir.y * towardDir.y < 0.0f)
		return false;
	return true;
}
