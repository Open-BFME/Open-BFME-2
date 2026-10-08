// cl: /O1 /DNDEBUG /MD /arch:SSE
// AIGroup::groupTightenToPosition, retail 0x0036F917 (231 bytes):
// ?groupTightenToPosition@AIGroup@@QAEXPBUCoord3D@@_NW4CommandSourceType@@@Z
// Identity (target): WorldBuilder's debug AIGroup.cpp
// AIGroup::groupTightenToPosition calls, in retail's order, operator new,
// the iterator constructor (0x0054B7B7), SimpleObjectIterator::insert
// (WB-named, 0x0054BBB5), the sort (0x0054C64A), the iterator's first/next
// virtuals and AICommandInterface::aiTightenToPosition /
// aiFollowPathAppend.
// Donor (Zero Hour AIGroup::groupTightenToPosition): members not held
// (disabled bit 3 of +0x1C8), not immobile (kind 2) and with an AI are
// queued by planar distance squared, sorted near to far, then each tightens
// to the position or appends it as a waypoint. BFME 2 deltas (target): no
// click-to-gather pass, no helicopter offsets and no iterator holder (the
// 0x3C-byte iterator from plain operator new is never released here).
// Layout (target): Object position +0x38, template +0x04 (kind bits from
// +0x108), disabled mask +0x1C8, AI +0x258 with its command interface at
// +0x20.
#include <list>

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum IterOrderType
{
	ITER_FASTEST = 0,
	ITER_SORTED_NEAR_TO_FAR = 1
};

enum KindOfType
{
	KINDOF_IMMOBILE = 2
};

enum DisabledType
{
	DISABLED_HELD = 3
};

class ThingTemplate
{
public:
	__forceinline bool isKindOf(KindOfType t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
};

class AICommandInterface
{
public:
	void aiTightenToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiFollowPathAppend(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	AICommandInterface *getCommands() { return &m_commands; }

private:
	unsigned char m_pad00[0x20];
	AICommandInterface m_commands; // +0x20
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	__forceinline bool isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	__forceinline bool isDisabledByType(DisabledType t) const { return (m_disabledMask[t >> 3] & (1 << (t & 7))) != 0; }
	AIUpdateInterface *getAI() const { return m_ai; }

private:
	unsigned char m_pad00[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x1C8 - 0x44];
	unsigned char m_disabledMask[0x04]; // +0x1C8
	unsigned char m_pad1CC[0x258 - 0x1CC];
	AIUpdateInterface *m_ai; // +0x258
};

class ObjectIterator
{
public:
	virtual ~ObjectIterator();
	virtual Object *first() = 0;
	virtual Object *next() = 0;
};

class SimpleObjectIterator : public ObjectIterator
{
public:
	SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *obj, float numeric);
	void sort(IterOrderType order);

private:
	unsigned char m_pad04[0x3C - 0x04];
};

class AIGroup
{
public:
	void groupTightenToPosition(const Coord3D *pos, bool addWaypoint, CommandSourceType cmdSource);

private:
	std::list<Object *> m_memberList;
};

void AIGroup::groupTightenToPosition(const Coord3D *pos, bool addWaypoint, CommandSourceType cmdSource)
{
	SimpleObjectIterator *iter = new SimpleObjectIterator;

	std::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		float dx, dy;
		const Coord3D *from = (*i)->getPosition();
		Coord3D unitPos;
		unitPos.x = from->x;
		unitPos.y = from->y;
		unitPos.z = from->z;
		if ((*i)->isDisabledByType(DISABLED_HELD))
			continue;
		if ((*i)->isKindOf(KINDOF_IMMOBILE))
			continue;
		if ((*i)->getAI() == 0)
			continue;
		dx = unitPos.x - pos->x;
		dy = unitPos.y - pos->y;
		iter->insert((*i), dx * dx + dy * dy);
	}

	iter->sort(ITER_SORTED_NEAR_TO_FAR);

	Object *theUnit;
	for (theUnit = iter->first(); theUnit; theUnit = iter->next())
	{
		AIUpdateInterface *ai = theUnit->getAI();
		if (!addWaypoint)
			ai->getCommands()->aiTightenToPosition(pos, cmdSource);
		else
			ai->getCommands()->aiFollowPathAppend(pos, cmdSource);
	}
}
