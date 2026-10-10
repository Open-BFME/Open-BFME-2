// flags: region default (reverse/retail_inventory/flag_regions.csv)

// ?removeAll_TeamInstanceList@TeamPrototype@@QAEXP6AXPAVTeam@@@Z@Z @0x0039D4FB (42B).
// Zero Hour's MAKE_DLINK_HEAD(Team, TeamInstanceList) removeAll (GameCommon.h):
// while the +0x334 head holds a team, unlinks it via removeFrom_TeamInstanceList
// 0x0039D4D8 then invokes the callback on it when present. Retail shape is
// head-load loop plus remove call plus null-gated indirect call with
// pop-clean plus ret 4. WorldBuilder twin 0x00EF1B70 is
// TeamPrototype::removeAll_TeamInstanceList; the caller ~TeamPrototype
// 0x003A33CD (0x003A33F3) passes deleteTeamCallback 0x003A33A7.

class Team;

class TeamPrototype
{
public:
	void removeFrom_TeamInstanceList(Team *o);
	void removeAll_TeamInstanceList(void (*p)(Team *));

private:
	char m_pad00[0x334];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

void TeamPrototype::removeAll_TeamInstanceList(void (*p)(Team *))
{
	Team *tmp;
	while( (tmp = m_dlinkhead_TeamInstanceList) != 0 )
	{
		removeFrom_TeamInstanceList(tmp);
		if( p != 0 )
		{
			p(tmp);
		}
	}
}
