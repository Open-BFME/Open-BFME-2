// ?rva004B0FEB@Rva004B0FEB@@QAE_NPAVObject@@@Z @0x004B0FEB 367B.
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
	unsigned m_108;
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

struct EntryInner
{
	char m_pad00[4];
	int m_4;
};

class Rva004DD018
{
public:
	bool rva004DD018(void *a, void *b, Object *other);
	char m_pad00[4];
	EntryInner *m_4;
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
	Rva004DD018 **m_begin;
	Rva004DD018 **m_end;
};

extern void *g_00DFF0F8;

class Rva004B0FEB
{
public:
	bool rva004B0FEB(Object *other);

private:
	char m_pad00[8];
	Rva004B0FEBData *m_8;
	Object *m_c;
	void *m_10;
	void *m_14;
	void *m_18;
	Object *m_1c;
	volatile unsigned char m_20;
};

bool Rva004B0FEB::rva004B0FEB(Object *other)
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

	unsigned flags108 = other->m_template->m_108;
	if ((flags108 & 0x80) != 0)
		return false;
	if (other->m_template->m_115 & 0x20)
		return false;
	unsigned flags10c = other->m_template->m_10c;
	if ((flags10c & 0x400000) != 0)
		return false;
	if ((flags108 & 4) != 0)
		return false;
	if ((flags10c & 0x8000) != 0)
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

	Pathfinder *path = *(Pathfinder **)((char *)g_00DFF0F8 + 0x10);
	if (path->IsPointOnWall((int)(void *)&other->m_pos, false))
		return false;

	Rva004DD018 **it = m_8->m_begin;
	while (it != m_8->m_end)
	{
		int kind = (*it)->m_4->m_4;
		if ((kind == 0 || kind == 3) && (*it)->rva004DD018(m_14, m_18, other))
			break;
		++it;
	}
	if (it == m_8->m_end)
		return false;

	path = *(Pathfinder **)((char *)g_00DFF0F8 + 0x10);
	if (!path->IsPointOnWall((int)(void *)&m_c->m_pos, false))
	{
		if (other->rva0028B511() == 1)
		{
			path = *(Pathfinder **)((char *)g_00DFF0F8 + 0x10);
			if (!path->IsGroundLineOnly(&m_c->m_pos, &other->m_pos))
				return false;
		}
	}

	m_1c = other;
	return true;
}
