// flags: region default (reverse/retail_inventory/flag_regions.csv)

// ?removeFrom_TeamInstanceList@TeamPrototype@@QAEXPAVTeam@@@Z @0x0039D4D8 (35B).
// Zero Hour's MAKE_DLINK_HEAD(Team, TeamInstanceList) removeFrom (GameCommon.h):
// when the team is in the +0x334 head list, unlinks it. Retail shape is head
// lea plus isInList test (Team::dlink_isInList_TeamInstanceList 0x0039D40F)
// plus conditional remove (Team::dlink_removeFrom_TeamInstanceList 0x0039D440)
// plus pop plus ret 4. WorldBuilder twin 0x00EF1C60 is
// TeamPrototype::removeFrom_TeamInstanceList; callers are removeAll 0x0039D4FB
// (0x0039D504) and ~Team 0x003A354F (0x003A3604).

typedef bool Bool;

class Team
{
public:
	Bool dlink_isInList_TeamInstanceList(Team *const *pListHead) const;
	void dlink_removeFrom_TeamInstanceList(Team **pListHead);
};

class TeamPrototype
{
public:
	void removeFrom_TeamInstanceList(Team *o);

private:
	char m_pad00[0x334];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

void TeamPrototype::removeFrom_TeamInstanceList(Team *o)
{
	Team **head = &m_dlinkhead_TeamInstanceList;
	if( !o->dlink_isInList_TeamInstanceList(head) )
	{
		return;
	}
	o->dlink_removeFrom_TeamInstanceList(head);
}
