// ?updateInterestZones@TacticalAI@@QAEXXZ
// partial score=0.85 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?updateInterestZones@TacticalAI@@QAEXXZ @0x002C6607 (370B)
//
// Identity: WorldBuilder names wb_va 0xE897E0 TacticalAI::updateInterestZones
// (asserts from ...\SkirmishAI\AITacticalAI\TacticalAI.cpp, lines 0x129-0x147:
// "TheGameLogic->getFrame() >= (*it)->m_lastActiveFrame", "oldProtos"); the
// retail body is its release build (no asserts, WB's player offsets less 4,
// Object offsets less 8).
//
// Target evidence: the interest zone vector<void*> at this+0x20 drops every
// zone whose +0x1C last active frame is g_00DFEFCC (logic fps * 4) frames old
// through operator delete and the rowed vector<void*>::erase (0x001FF51F);
// then the player (this+8) +0x32C team prototype list is walked, each
// prototype's +0x334 instance list through the MI member pointer
// dlink_next_TeamInstanceList (0x005C4AF5), skipping the player's +0x2EC team;
// for each team the first member with KindOf bit 3 or bit 90 whose AI
// (+0x258, rowed getCurrentVictim 0x00268D71) has a non-structure victim
// (KindOf bit 7) whose template +0x520 is not 4 within 300 2D units (90000.0
// at 0x00C004D4) adds an interest zone at the member's position through
// 0x002C64D0 (default id -1).

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

namespace _STL
{
	template <class T> class allocator {};
	template <class T, class A = allocator<T> > class vector
	{
	public:
		T *begin() { return _M_start; }
		T *end() { return _M_finish; }
		T *erase(T *pos);
	private:
		T *_M_start;
		T *_M_finish;
		T *_M_end_of_storage;
	};
}

struct Coord3D
{
	Real x, y, z;
	Real lengthSqr2D() const { return x * x + y * y; }
	void sub(const Coord3D *a) { x -= a->x; y -= a->y; z -= a->z; }
};

class Object;
class Team;

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	Bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

template <>
class DLINK_ITERATOR<Object>
{
private:
	Object *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	Bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

class Snapshot
{
public:
	virtual void crc(void *xfer) = 0;
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
	}
private:
	unsigned char m_pad[0x334];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_value;
};

struct PlayerTeamList
{
	PlayerTeamNode *begin() const { return m_node->m_next; }
	PlayerTeamNode *end() const { return m_node; }
	PlayerTeamNode *m_node;
};

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
	const PlayerTeamList *getPlayerTeams() const { return &m_playerTeamPrototypes; }
private:
	char m_pad[0x2EC];
	Team *m_defaultTeam; // +0x2EC
	char m_pad2F0[0x32C - 0x2F0];
	PlayerTeamList m_playerTeamPrototypes; // +0x32C
};

class ThingTemplate
{
public:
	UnsignedInt testKindOf(Int word, UnsignedInt mask) const { return m_kindOf[word] & mask; }
	Int get520() const { return m_520; }
private:
	char m_pad000[0x108];
	UnsignedInt m_kindOf[4]; // +0x108
	char m_pad118[0x520 - 0x118];
	Int m_520; // +0x520
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +4
	char m_pad008[0x38 - 0x08];
	Coord3D m_pos; // +0x38
	char m_pad044[0x258 - 0x44];
	AIUpdateInterface *m_ai; // +0x258
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	char m_pad[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

extern int g_00DFEFCC;

struct InterestZone
{
	~InterestZone() {}
	char m_pad[0x1C];
	UnsignedInt m_lastActiveFrame; // +0x1C
};

class TacticalAI
{
public:
	void updateInterestZones();
	void rva002C64D0(const Coord3D *pos, Int id = -1);
private:
	char m_pad00[8];
	Player *m_player; // +8
	char m_pad0C[0x20 - 0x0C];
	_STL::vector<void *> m_interestZones; // +0x20
};

void TacticalAI::updateInterestZones()
{
	void **it = m_interestZones.begin();
	while (it != m_interestZones.end())
	{
		if (TheGameLogic->getFrame() - ((InterestZone *)*it)->m_lastActiveFrame >= (UnsignedInt)g_00DFEFCC)
		{
			delete (InterestZone *)*it;
			it = m_interestZones.erase(it);
		}
		else
		{
			++it;
		}
	}

	const PlayerTeamList *oldProtos = m_player->getPlayerTeams();
	PlayerTeamNode *end = oldProtos->end();
	for (PlayerTeamNode *pt = oldProtos->begin(); pt != end; pt = pt->m_next)
	{
		for (DLINK_ITERATOR<Team> iter = pt->m_value->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (team == m_player->getDefaultTeam())
				continue;
			Bool found = false;
			DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList();
			for (Object *obj; (obj = objIter.cur()) != 0 && !found; objIter.advance())
			{
				if (!obj->getTemplate()->testKindOf(0, 0x8) && !obj->getTemplate()->testKindOf(2, 0x4000000))
					continue;
				Object *victim = 0;
				if (obj->getAI())
					victim = obj->getAI()->getCurrentVictim();
				if (!victim)
					continue;
				if (victim->getTemplate()->testKindOf(0, 0x80) || victim->getTemplate()->get520() == 4)
					continue;
				Real vx = victim->getPosition()->x;
				Real vy = victim->getPosition()->y;
				const Coord3D *op = obj->getPosition();
				vx -= op->x;
				vy -= op->y;
				if (vx * vx + vy * vy <= 90000.0f)
				{
					rva002C64D0(op);
					found = true;
				}
			}
		}
	}
}
