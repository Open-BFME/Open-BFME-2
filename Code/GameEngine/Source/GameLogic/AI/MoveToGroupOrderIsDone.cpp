// cl: /O1 /G7 /arch:SSE /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /ICode/Libraries/Include/Lib
// stlport
//
// ?rva00547368@MoveToGroupOrder@@UAE_NW4ObjectID@@@Z, retail 0x00547368 143B.
// Virtual slot 5 (offset 0x14) of the MoveToGroupOrder vftable 0x00C6A478
// (layout in MoveToGroupOrderCtor.cpp; slot 5 of AttackObjectGroupOrder is the
// same bool(int) shape). Looks the argument up through TheGameLogic
// findObjectByID (0x00049DC5); a missing or rva002931BA (0x002931BA) Object or
// one without an AI (+0x258) counts as done. Otherwise the order's per-object
// destination map (+0x28 hash_map<ObjectID Coord3D>; _M_find 0x002888D4) is
// probed: no entry or the rowed 20.0 proximity test Rva00547263 resets the
// +0x3C counter and reports done. Else the AI's slot 110 (+0x1B8) decides:
// false resets the counter and reports not done; true bumps it and reports done
// only past one tick. No callers besides the vftable.

#include "Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"
#include <hash_map>
namespace rts {
template <typename T> struct hash {
    size_t operator()(const T &value) const { return (size_t)value; }
};
}
typedef _STL::hash_map<ObjectID, Coord3D, rts::hash<ObjectID>,
                      _STL::equal_to<ObjectID> > ObjectCoord3DMap;
extern GameLogic *TheGameLogic;

template <int N> class Rva00547368Slots : public Rva00547368Slots<N - 1>
{
public:
	virtual void gap(char (*)[N + 1]) = 0;
};
template <> class Rva00547368Slots<0>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

// AIUpdateInterface slot 110 (+0x1B8).
class AIUpdateInterface : public Rva00547368Slots<109>
{
public:
	virtual bool slot110() = 0;
};

class Object
{
public:
	bool rva002931BA();
	char m_pad0[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

bool Rva00547263(Object *p, const Coord3D *q);

class GroupOrder
{
public:
	virtual ~GroupOrder();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual bool rva00547368(ObjectID id);

private:
	unsigned char m_pad04[0x18 - 4];
};

class MoveToGroupOrder : public GroupOrder
{
public:
	virtual bool rva00547368(ObjectID id);

private:
	Coord3D m_destination;             // +0x18
	bool m_flag24;                     // +0x24
	bool m_flag25;                     // +0x25
	ObjectCoord3DMap m_map28;          // +0x28
	unsigned int m_value3C;            // +0x3C
};

bool MoveToGroupOrder::rva00547368(ObjectID id)
{
	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj == 0 || obj->rva002931BA())
		return true;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai == 0)
		return true;
	ObjectCoord3DMap *map = &m_map28;
	ObjectCoord3DMap::const_iterator it = map->find(id);
	if (it == map->end()) {
		m_value3C = 0;
		return true;
	}
	if (Rva00547263(obj, &it->second)) {
		m_value3C = 0;
		return true;
	}
	if (ai->slot110()) {
		++m_value3C;
		if (m_value3C > 1)
			return true;
	} else {
		m_value3C = 0;
	}
	return false;
}
