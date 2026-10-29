// cl: /O1 /Ireference/shims/moduledata /DNDEBUG /MD /EHsc /arch:SSE /Oy-
// Donor fact: Open-BFME-1 Team.cpp names TeamPrototype::moveTeamTo(Coord3D)
// and forwards the copied coordinate to each Team in the prototype's list.
// Target evidence: 0x0039F03A reads the team head at +0x334, advances through
// a member-function callback, copies three float coordinates to a 12-byte
// outgoing argument block, and calls 0x0039E7F2. That callee is byte-matched
// under an address-derived three-float Team spelling. The struct/three-float
// ABI alias is inferred from this call site and the donor, not a target name.
// The iterator callback's donor name is also an inference; retail target
// address 0x005C4AF5 is independently rowed only under an opaque getter name.
#include "../../../Include/Common/MemoryPoolObject.h"
#include "Common/Snapshot.h"

// Coord3D: shared header/view; no private copy.
#define COORD3D_VIEW_DTOR
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	void moveTeamTo(Coord3D destination);
};

class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
	}
	void moveTeamTo(Coord3D destination);

private:
	unsigned char m_pad[0x334];
	Team *m_dlinkhead_TeamInstanceList;
};

void TeamPrototype::moveTeamTo(Coord3D destination)
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		iter.cur()->moveTeamTo(destination);
}
