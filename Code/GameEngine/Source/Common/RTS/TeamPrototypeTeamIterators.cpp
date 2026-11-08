// cl: /Ireference/shims/moduledata /DNDEBUG /MD
//
// TeamPrototype's team-instance walks (retail 0x0039ECD9..0x0039F000), in
// Zero Hour's Team.cpp order: each iterates the +0x334 DLINK team list with
// Zero Hour's DLINK_ITERATOR (the advance is a call through the member
// pointer &Team::dlink_next_TeamInstanceList, 0x005C4AF5, with its zero
// this-adjustment for Team's two bases) and forwards to the matching rowed
// Team member. countObjectsByThingTemplate, countBuildings, countObjects,
// healAllObjects and damageTeamMembers keep their Zero Hour names (same
// Team callees in Zero Hour's order; the Team bodies for the first and last
// are pinned from these calls, their loops match Zero Hour's); BFME changed the
// signatures of the rest (extra flags, filters by value, an int-returning
// iterateObjects that stops on 0), so those names stay address-derived,
// except hasAnyObjects, whose Team callee carries that name. Filters and
// masks are copied by value through the 28-byte copy constructor at
// 0x0004543D.
typedef bool Bool;
typedef int Int;

template <class OBJCLASS>
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

template <int N>
class BitFlags
{
public:
	BitFlags(const BitFlags &other);
private:
	unsigned int m_bits[7];
};
typedef BitFlags<116> KindOfMaskType;

// The by-value kind filters are the 28-byte storage the ledger names after
// its copy constructor 0x0004543D (FixedStorageCopyBFME2.cpp), the callee
// retail copies each argument through.
#include "../../../Include/Common/BfmeFixedStorage0004543D.h"
typedef BfmeFixedStorage0004543D Rva0039DDC2Filter;
typedef BfmeFixedStorage0004543D Rva0039DF1CFilter;

class Object;
class BfmeTab1026;
class ThingTemplate;
typedef float Real;
typedef Int (*ObjectIterateFunc)(Object *obj, void *userData);

#include "../../../Include/Common/MemoryPoolObject.h"

#include "Common/Snapshot.h"

#include "../../../Include/Common/TeamBFME2.h"

// Zero Hour's MAKE_DLINK(Team, TeamInstanceList) accessor (0x005C4AF5).
inline Team *Team::dlink_next_TeamInstanceList() const
{
	return m_dlink_TeamInstanceList_next;
}

#include "../../../Include/Common/Team.h"

inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const
{
	return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
}

void TeamPrototype::countObjectsByThingTemplate(Int numTmplates, const ThingTemplate* const* things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		iter.cur()->countObjectsByThingTemplate(numTmplates, things, ignoreDead, counts, ignoreUnderConstruction);
}

Int TeamPrototype::countBuildings()
{
	Int retVal = 0;
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		retVal += iter.cur()->countBuildings();
	return retVal;
}

Int TeamPrototype::countObjects(KindOfMaskType setMask, KindOfMaskType clearMask)
{
	Int retVal = 0;
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		retVal += iter.cur()->countObjects(setMask, clearMask);
	return retVal;
}

void TeamPrototype::healAllObjects()
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		iter.cur()->healAllObjects();
}

Int TeamPrototype::rva0039ED9C(ObjectIterateFunc func, void *userData)
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		if (!iter.cur()->rva0039DD12(func, userData))
			return 0;
	}
	return 1;
}

Bool TeamPrototype::rva0039EDE1(Bool flag)
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		if (iter.cur()->rva0039DD4B(flag))
			return true;
	}
	return false;
}

Bool TeamPrototype::rva0039EE21(Rva0039DDC2Filter filter, Bool flag)
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		if (iter.cur()->rva0039DDC2(filter, flag))
			return true;
	}
	return false;
}

Bool TeamPrototype::rva0039EE70(BfmeTab1026 *tab, Bool flag)
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		if (iter.cur()->rva0039DE46(tab, flag))
			return true;
	}
	return false;
}

Bool TeamPrototype::hasAnyUnits() const
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		if (iter.cur()->hasAnyUnits())
			return true;
	}
	return false;
}

Bool TeamPrototype::hasAnyBuildings(Rva0039DF1CFilter filter1, Rva0039DF1CFilter filter2)
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		if (iter.cur()->hasAnyBuildings(filter1, filter2))
			return true;
	}
	return false;
}

Bool TeamPrototype::rva0039EF46(BfmeTab1026 *tab)
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		if (iter.cur()->rva0039DF87(tab))
			return true;
	}
	return false;
}

Bool TeamPrototype::hasAnyObjects(Bool flag)
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		if (iter.cur()->hasAnyObjects(flag))
			return true;
	}
	return false;
}

Bool TeamPrototype::hasAnyBuildFacility() const
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		if (iter.cur()->hasAnyBuildFacility())
			return true;
	}
	return false;
}

void TeamPrototype::damageTeamMembers(Real amount)
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		iter.cur()->damageTeamMembers(amount);
}
