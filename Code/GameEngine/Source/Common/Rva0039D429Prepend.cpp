// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?dlink_prependTo_TeamInstanceList@Team@@QAEXPAPAV1@@Z @0x0039D429 (23B).
// Zero Hour's MAKE_DLINK(Team, TeamInstanceList) prepend (GameCommon.h):
// stores the current head into this+0x40, links the old head back through
// its +0x3C slot when present, then publishes this as the new head. Retail
// shape is two loads of *head (aliasing forces the reload after the next
// store) plus test plus back-link plus head store plus ret 4.
// Identity: WorldBuilder twin 0x00EF40B0 is Team::dlink_prependTo_TeamInstanceList
// (callgraph); the caller TeamPrototype::prependTo_TeamInstanceList 0x0039D4B5
// (0x0039D4CF) passes the +0x334 TeamPrototype head.

class Team
{
public:
	void dlink_prependTo_TeamInstanceList(Team **pListHead);

private:
	char m_pad00[0x3C];
	Team *m_dlink_TeamInstanceList_prev; // +0x3C
	Team *m_dlink_TeamInstanceList_next; // +0x40
};

void Team::dlink_prependTo_TeamInstanceList(Team **pListHead)
{
	m_dlink_TeamInstanceList_next = *pListHead;
	Team *old = *pListHead;
	if (old) {
		old->m_dlink_TeamInstanceList_prev = this;
	}
	*pListHead = this;
}
