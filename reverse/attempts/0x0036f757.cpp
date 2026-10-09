// ?groupScatter@AIGroup@@QAEXW4CommandSourceType@@@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?groupScatter@AIGroup@@QAEXW4CommandSourceType@@@Z, retail
// 0x0036F757..0x0036F917 (448B), thiscall ret 4.
//
// Donor: Zero Hour AIGroup.cpp AIGroup::groupScatter (recompute when dirty,
// getMinMaxAndCenter, members that are held, immobile or AI-less skipped,
// pathfinder goal removal, insertion by squared distance from the centre,
// far-to-near sort, then each unit moves four bounding radii away from a
// centre nudged by 0.01 per unit). BFME 2 differences read from retail:
//   * the iterator is a plain new SimpleObjectIterator (0x3C bytes, ctor
//     0x0054B7B7 under the new-expression EH state) and is not released;
//   * the goal removal is Object's rowed rva0028AD32 (0x0028AD32);
//   * the move offset multiplies by the radius before the factor 4.
// Member list at +0x04 (STLport list head), dirty flag +0x0C; Object fields:
// template +0x04 (kind-of byte +0x108 bit 2 = immobile), position +0x38,
// geometry bounding radius +0xB8, disabled byte +0x1C8 bit 3 = held, AI
// update +0x258 whose AICommandInterface base sits at +0x20.
//
// Evidence (target): callees at the retail REL32s: AIGroup::recompute
// 0x0036D2C5, pinned getMinMaxAndCenter 0x0036D14F, operator new 0x0002FDA0,
// pinned SimpleObjectIterator ctor / insert / sort (0x0054B7B7 / 0x0054BBB5 /
// 0x0054C64A), Coord2D::normalize 0x0000378A and
// AICommandInterface::aiMoveToPosition 0x0026C26D; constants 0.01 (0x007CF628)
// and 4.0 (0x007C2918). WorldBuilder twin 0xEE56B0 (callgraph lead). Sole
// caller 0x003799CF.
#include "Coord2D.h"
#include "Coord3D.h"

typedef float Real;

// Coord3D with the member-wise copy constructor retail's copies show.
struct Coord3DCopy : public Coord3D
{
	Coord3DCopy(const Coord3D &o) { x = o.x; y = o.y; z = o.z; }
};
typedef bool Bool;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum IterOrderType
{
	ITER_FASTEST = 0,
	ITER_SORTED_NEAR_TO_FAR = 1,
	ITER_SORTED_FAR_TO_NEAR = 2
};

class Object;

class SimpleObjectIterator
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *obj, Real numeric);
	void sort(IterOrderType order);
private:
	unsigned char m_pad04[0x3C - 0x04];
};

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad00[0x20];
	AICommandInterface m_commands;		// +0x20
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource)
	{
		m_commands.aiMoveToPosition(pos, cmdSource);
	}
};

struct ThingTemplateView
{
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf108;		// +0x108
};

class Object
{
public:
	Bool isHeld() const { return (m_disabled1C8 & 8) != 0; }
	Bool isImmobile() const { return (m_template->m_kindOf108 & 4) != 0; }
	AIUpdateInterface *getAI() const { return m_ai; }
	const Coord3D *getPosition() const { return &m_pos; }
	Real getBoundingCircleRadius() const { return m_boundingRadius; }
	void rva0028AD32();

private:
	unsigned char m_pad00[0x04];
	ThingTemplateView *m_template;		// +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos;				// +0x38
	unsigned char m_pad44[0xB8 - 0x44];
	Real m_boundingRadius;			// +0xB8
	unsigned char m_padBC[0x1C8 - 0xBC];
	unsigned char m_disabled1C8;		// +0x1C8
	unsigned char m_pad1C9[0x258 - 0x1C9];
	AIUpdateInterface *m_ai;		// +0x258
};

struct ObjectListNode
{
	ObjectListNode *m_next;
	ObjectListNode *m_prev;
	Object *m_data;
};

class AIGroup
{
public:
	Bool getMinMaxAndCenter(Coord2D *min, Coord2D *max, Coord3D *center);
	void groupScatter(CommandSourceType cmdSource);

private:
	void recompute();

	unsigned char m_pad00[0x04];
	ObjectListNode *m_memberList;		// +0x04 list head
	unsigned char m_pad08[0x0C - 0x08];
	Bool m_dirty;				// +0x0C
};

void AIGroup::groupScatter(CommandSourceType cmdSource)
{
	if (m_dirty)
		recompute();

	Coord3D center;
	Coord2D min;
	Coord2D max;
	Coord3D dest;

	getMinMaxAndCenter(&min, &max, &center);

	SimpleObjectIterator *iter = new SimpleObjectIterator;
	for (ObjectListNode *i = m_memberList->m_next; i != m_memberList; i = i->m_next)
	{
		Real dx, dy;
		if (i->m_data->isHeld())
			continue;
		if (i->m_data->isImmobile())
			continue;
		if (i->m_data->getAI() == 0)
			continue;
		Coord3DCopy unitPos = *i->m_data->getPosition();
		i->m_data->rva0028AD32();
		dx = unitPos.x - center.x;
		dy = unitPos.y - center.y;
		iter->insert(i->m_data, dx * dx + dy * dy);
	}

	iter->sort(ITER_SORTED_FAR_TO_NEAR);
	Object *theUnit;
	for (theUnit = iter->first(); theUnit; theUnit = iter->next())
	{
		center.x -= 0.01f;
		AIUpdateInterface *ai = theUnit->getAI();
		Coord3DCopy unitPos = *theUnit->getPosition();
		Coord2D delta;
		dest = unitPos;
		delta.x = unitPos.x - center.x;
		delta.y = unitPos.y - center.y;
		delta.normalize();
		dest.x += delta.x * theUnit->getBoundingCircleRadius() * 4;
		dest.y += delta.y * theUnit->getBoundingCircleRadius() * 4;
		ai->aiMoveToPosition(&dest, cmdSource);
	}
}
