// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?prependTo_TeamInstanceList@TeamPrototype@@QAEXPAVTeam@@@Z @0x0039D4B5 (35B).
// Zero Hour's MAKE_DLINK_HEAD(Team, TeamInstanceList) prependTo (GameCommon.h):
// when the team is not already in the +0x334 head list, prepends it. Retail
// shape is head lea plus isInList test (Team::dlink_isInList_TeamInstanceList
// 0x0039D40F) plus conditional prepend (Team::dlink_prependTo_TeamInstanceList
// 0x0039D429) plus pop plus ret 4. WorldBuilder twin 0x00EF3FE0 is
// TeamPrototype::prependTo_TeamInstanceList; the caller is the Team ctor
// 0x003A39A7 (call at 0x003A3ADA).

typedef bool Bool;

class Team
{
public:
	Bool dlink_isInList_TeamInstanceList(Team *const *pListHead) const;
	void dlink_prependTo_TeamInstanceList(Team **pListHead);
};

class TeamPrototype
{
public:
	void prependTo_TeamInstanceList(Team *o);

private:
	char m_pad00[0x334];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

void TeamPrototype::prependTo_TeamInstanceList(Team *o)
{
	Team **head = &m_dlinkhead_TeamInstanceList;
	if (o->dlink_isInList_TeamInstanceList(head)) {
		return;
	}
	o->dlink_prependTo_TeamInstanceList(head);
}
