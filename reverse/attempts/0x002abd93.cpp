// ?setObjectsEnabled@Player@@QAEXABVAsciiString@@_N@Z
// partial score=0.8 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// stlport
// ?setObjectsEnabled@Player@@QAEXABVAsciiString@@_N@Z, RVA 0x002ABD93, size 145.
// Evidence (target): thiscall, ret 8, between Player::removeTeamFromList
// (0x002ABD48) and the next Player member. Walks the STLport list of team
// prototypes at Player +0x32C; for each prototype walks its team-instance DLINK
// list (head +0x334, next through the member pointer {0x005C4AF5, 0}, the
// Team +0x40 getter, the shape TeamPrototype's rowed iterators use); for each
// team takes the member iterator from the rowed Team::iterate_TeamMemberList
// (0x00263864) and advances it with the rowed DLINK_ITERATOR<Object>::advance
// (0x00263526). Each member's template (Object +4) name (+0x64) is compared
// with the referenced string by AsciiString::compare (0x000069D6) and a match
// calls Object::setScriptStatus (0x00292969) with bit 1 and (enable == 0).
// The string arrives as a pointer with no release at exit, so the parameter
// is a reference. Name and loop structure carried from Zero Hour's
// Player::setObjectsEnabled (OBJECT_STATUS_SCRIPT_DISABLED, !enable); BFME
// passes the template name by reference instead of by value.
#include "ascii_string.h"
#include <list>

typedef bool Bool;

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }

private:
	unsigned char m_pad[0x64];
	AsciiString m_name;	// +0x64
};

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_DISABLED = 0x01,
	OBJECT_STATUS_SCRIPT_UNPOWERED = 0x02
};

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

// Introduces the vbptr at its own +0; lands at +0x68 inside Object.
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	const ThingTemplate *m_template;	// +4
	unsigned char m_pad[0x60];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	void setScriptStatus(ObjectScriptStatusBit bit, Bool set);

	unsigned char m_tail[0x40];
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
	Team *m_dlinkhead_TeamInstanceList;	// +0x334
};

typedef _STL::list<TeamPrototype *> PlayerTeamList;

class Player
{
public:
	void setObjectsEnabled(const AsciiString &templateTypeToAffect, Bool enable);

private:
	unsigned char m_pad[0x32C];
	PlayerTeamList m_playerTeamPrototypes;	// +0x32C
};

void Player::setObjectsEnabled(const AsciiString &templateTypeToAffect, Bool enable)
{
	for (PlayerTeamList::iterator it = m_playerTeamPrototypes.begin(); it != m_playerTeamPrototypes.end(); ++it)
	{
		for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			Object *obj;
			for (DLINK_ITERATOR<Object> iter2 = team->iterate_TeamMemberList(); (obj = iter2.cur()) != 0; iter2.advance())
			{
				if (obj->getTemplate()->getName() == templateTypeToAffect)
					obj->setScriptStatus(OBJECT_STATUS_SCRIPT_DISABLED, !enable);
			}
		}
	}
}
