// flags: region default (reverse/retail_inventory/flag_regions.csv)

// ?dlink_removeFrom_TeamInstanceList@Team@@QAEXPAPAV1@@Z @0x0039D440 (48B).
// Zero Hour's MAKE_DLINK(Team, TeamInstanceList) unlink (GameCommon.h):
// unlinks this from the +0x3C/+0x40 doubly-linked list, updating the head
// through its slot when this has no prev, then clears both links. Retail
// shape is next-gated prev store plus prev-gated next store else head store
// plus two and-zero clears plus ret 4.
// Identity: WorldBuilder twin 0x00EF1D30 is Team::dlink_removeFrom_TeamInstanceList
// (callgraph); the caller TeamPrototype::removeFrom_TeamInstanceList 0x0039D4D8
// (0x0039D4F2) passes the +0x334 TeamPrototype head.

class Team
{
public:
	void dlink_removeFrom_TeamInstanceList(Team **pListHead);

private:
	char m_pad00[0x3C];
	Team *m_dlink_TeamInstanceList_prev; // +0x3C
	Team *m_dlink_TeamInstanceList_next; // +0x40
};

void Team::dlink_removeFrom_TeamInstanceList(Team **pListHead)
{
	if( m_dlink_TeamInstanceList_next )
	{
		m_dlink_TeamInstanceList_next->m_dlink_TeamInstanceList_prev = m_dlink_TeamInstanceList_prev;
	}
	if( m_dlink_TeamInstanceList_prev )
	{
		m_dlink_TeamInstanceList_prev->m_dlink_TeamInstanceList_next = m_dlink_TeamInstanceList_next;
	}
	else
	{
		*pListHead = m_dlink_TeamInstanceList_next;
	}
	m_dlink_TeamInstanceList_prev = 0;
	m_dlink_TeamInstanceList_next = 0;
}
