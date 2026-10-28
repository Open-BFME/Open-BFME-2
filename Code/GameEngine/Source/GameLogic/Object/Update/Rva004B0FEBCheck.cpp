// ?Allow@TauntPointFilter@EmotionTrackerUpdate@@UAE_NPAVObject@@@Z @0x004B0FEB 367B.
// Name: WorldBuilder twin 0x01230A20 EmotionTrackerUpdate::TauntPointFilter::Allow
// (EmotionTrackerUpdate.cpp:243, call graph).
// Target gate. The object at +0xC must be present and, when status 0x0F is
// set, status 0x11 must be set too. A cached object with the same non-zero
// +0x274 id is an immediate hit. Otherwise the argument's template flags,
// enemy relationship, private-status bit, the +0x10 helper, the filter at
// data+4+0x10, and the wall test all have to pass. One entry in the data
// vector at +0x90 whose inner kind is 0 or 3 must accept the pair, and the
// two positions must satisfy the pathfinder unless the wall or rank test
// already does.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum ObjectStatusTypes;
enum Relationship
{
	ENEMIES = 0
};

class Player;
class Object;
class Pathfinder;

class ThingTemplate
{
public:
	char m_pad00[0x108];
	unsigned m_kindOf;
	unsigned m_10c;
	char m_pad110[0x115 - 0x110];
	unsigned char m_115;
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	Relationship getRelationship(const Object *other) const;
	int rva0028B511() const;
	bool rva00294471(void *key, int arg);

	char m_pad00[4];
	ThingTemplate *m_template;
	char m_pad08[0x38 - 8];
	Coord3D m_pos;
	char m_pad44[0x274 - 0x44];
	int m_274;
	char m_pad278[0x438 - 0x278];
	unsigned char m_438;
};

class Pathfinder
{
public:
	bool IsPointOnWall(int point, bool flag);
	bool IsGroundLineOnly(const Coord3D *a, const Coord3D *b);
};

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

struct EmotionEntry
{
	char m_pad00[4];
	int m_04;
};

// The owned 4DD018 provider is EmotionNugget::CanBeActivatedFor.
// Native caller4B10E3 pushes two counter words (ctor4B0EE5 stores counts at
// +14/+18) and the complete Object pointer through that provider's proven
// argument view. Use its existing name/ABI; no second pin or wrapper.
struct Rva004DD018Arg;

class EmotionNugget
{
public:
	bool CanBeActivatedFor(int a, int b, Rva004DD018Arg *other);
	char m_pad00[4];
	EmotionEntry *m_entry;
};

struct RvaFilterHolder10
{
	char m_lead[0x10];
	Rva2225E0Filter m_filter;
};

struct Rva004B0FEBData
{
	char m_pad00[4];
	RvaFilterHolder10 *m_4;
	char m_pad08[0x90 - 8];
	EmotionNugget **m_begin;
	EmotionNugget **m_end;
};

class AI {public:char pad[0x10];Pathfinder *pathfinder;};
extern AI *TheAI;

class Rva000421C8 {public:virtual ~Rva000421C8();virtual bool Allow(Object*)=0;virtual int getPlayerMask();Rva000421C8 *next;};

class EmotionTrackerUpdate
{
public:
	class TauntPointFilter;
};

class EmotionTrackerUpdate::TauntPointFilter:public Rva000421C8
{
public:
	virtual bool Allow(Object *other);
	virtual int getPlayerMask();

private:
	Rva004B0FEBData *m_8;
	Object *m_c;
	void *m_10;
	int m_14;
	int m_18;
	Object *m_1c;
	volatile unsigned char m_20;
};

bool EmotionTrackerUpdate::TauntPointFilter::Allow(Object *other)
{
	Object *objA = m_c;
	if (!objA)
		goto earlyFail;
	if (objA->testStatus((ObjectStatusTypes)0x0F))
	{
		if (!objA->testStatus((ObjectStatusTypes)0x11))
			goto earlyFail;
	}
	goto body;
earlyFail:
	return false;
body:
	;

	if (m_1c)
	{
		int id = m_1c->m_274;
		if (id != 0 && id == other->m_274)
			return true;
	}

	unsigned flags108 = other->m_template->m_kindOf;
	if ((flags108 & 0x80) != 0)
		return false;
	if (other->m_template->m_115 & 0x20)
		return false;
	unsigned kindOfHigh = other->m_template->m_10c;
	if ((kindOfHigh & 0x400000) != 0)
		return false;
	if ((flags108 & 4) != 0)
		return false;
	if ((kindOfHigh & 0x8000) != 0)
		return false;

	if (objA->getRelationship(other) != ENEMIES)
		return false;
	if ((other->m_438 & 1) != 0)
		return false;

	if (!other->rva00294471(m_10, 0))
		return false;

	Rva004B0FEBData *data = m_8;
	m_20 = 1;
	void *holder = data->m_4;
	if (((RvaFilterHolder10 *)holder)->m_filter.accepts(other, 0))
		return false;

	Pathfinder *path = TheAI->pathfinder;
	if (path->IsPointOnWall((int)(void *)&other->m_pos, false))
		return false;

	EmotionNugget **it = m_8->m_begin;
	while (it != m_8->m_end)
	{
		int kind = (*it)->m_entry->m_04;
		if ((kind == 0 || kind == 3) && (*it)->CanBeActivatedFor(m_14, m_18, reinterpret_cast<Rva004DD018Arg *>(other)))
			break;
		++it;
	}
	if (it == m_8->m_end)
		return false;

	path = TheAI->pathfinder;
	if (!path->IsPointOnWall((int)(void *)&m_c->m_pos, false))
	{
		if (other->rva0028B511() == 1)
		{
			path = TheAI->pathfinder;
			if (!path->IsGroundLineOnly(&m_c->m_pos, &other->m_pos))
				return false;
		}
	}

	m_1c = other;
	return true;
}
