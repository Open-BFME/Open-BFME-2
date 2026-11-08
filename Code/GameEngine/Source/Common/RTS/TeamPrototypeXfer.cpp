// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /GX
// ?xfer@TeamPrototype@@MAEXPAVXfer@@@Z @0x003A3E74 473B: slot 3 of vtable 0x0081AE94 (class of ??1TeamPrototype). Evidence: donor BFME1 Team.cpp xfer plus TeamPrototypeInstanceWalks xfer plus rowed getNthPlayer 0x002A7A29 plus pins 0x0039F761 0x003A3DBE plus disp8 getter 0x005C4AF5.
// Slot 3 is TeamPrototype::xfer, retyped protected (MAE) from retail IsLightCRC early-out and Version(1,2) plus int player index plus Ascii plus bool plus Snapshot plus ushort count plus bool plus floats plus version-gated bools plus uint plus team save/load walks.
#include "ascii_string.h"
#include "../../../Include/Common/Team.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../Include/Common/BfmeXfer.h"

#include "../../../Include/Common/XferVersion.h"

#include "../../../Include/Common/MemoryPoolObject.h"

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};
class Team;
class TeamPrototype;
class Object;
class PlayerTemplate;
struct RetailPlayerRelationMap;
#include "../../../Include/Common/Player.h"

#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../../Include/Common/TeamBFME2.h"

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	bool done() const { return m_cur == 0; }
	OBJCLASS* cur() const { return m_cur; }
};

class TeamFactory;
#include "../../../Include/Common/TeamFactory.h"
extern TeamFactory *TheTeamFactory;

// The iterator's concrete ABI belongs to this TU; the shared declaration
// leaves it incomplete for consumers with other iterator implementations.
inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const
{
	return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
}

void TeamPrototype::xfer(Xfer *xfer)
{
	unsigned int teamID;
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 2);
	*xfer == version;
	int owningPlayerIndex;
	if (xfer->IsStoring())
		owningPlayerIndex = m_owningPlayer->getPlayerIndex();
	*xfer == owningPlayerIndex;
	m_owningPlayer = ThePlayerList->getNthPlayer(owningPlayerIndex);
	*xfer == m_attackPriorityName;
	*xfer == m_productionConditionAlwaysFalse;
	*xfer == *(Snapshot *)m_opaque12C;
	unsigned short teamInstanceCount = 0;
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		teamInstanceCount++;
	*xfer == teamInstanceCount;
	*xfer == m_field324;
	*xfer == m_coordinate328[0];
	*xfer == m_coordinate328[1];
	*xfer == m_coordinate328[2];
	if (version.m_minimum >= 2)
	{
		*xfer == m_field31C;
		*xfer == m_field31D;
		*xfer == m_field31E;
		*xfer == m_frame320;
	}
	if (xfer->IsStoring())
	{
		for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			teamID = iter.cur()->m_id;
			*xfer == teamID;
			*xfer == (Snapshot &)*iter.cur();
		}
	}
	else
	{
		for (unsigned short i = 0; i < teamInstanceCount; ++i)
		{
			*xfer == teamID;
			Team *teamInstance = TheTeamFactory->findTeamByID(teamID);
			if (teamInstance == 0)
			{
				teamInstance = TheTeamFactory->createTeamOnPrototype(this, true);
				if (teamInstance)
					teamInstance->m_id = teamID;
			}
			*xfer == (Snapshot &)*teamInstance;
		}
	}
}
