// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?dlink_isInList_TeamInstanceList@Team@@QBE_NPBQAV1@@Z @0x0039D40F (26B).
// Zero Hour's MAKE_DLINK(Team, TeamInstanceList) membership test (GameCommon.h):
// true when the head slot holds this or either link is set. Retail shape is
// head compare plus prev test plus next test plus two single-byte returns.
// Identity: this is the node (links at +0x3C/+0x40, the Team dlink pair the
// rowed Team ctor 0x003A39A7 zeroes) and the argument is the +0x334 head of
// TeamPrototype (TeamPrototype::prependTo_TeamInstanceList 0x0039D4B5 and
// removeFrom_TeamInstanceList 0x0039D4D8 pass it; ~Team calls it before
// removeFrom). Siblings 0x0039D429 / 0x0039D440 are the WorldBuilder-named
// Team::dlink_prependTo / dlink_removeFrom of the same list.

typedef bool Bool;

class Team
{
public:
	Bool dlink_isInList_TeamInstanceList(Team *const *pListHead) const;

private:
	char m_pad00[0x3C];
	Team *m_dlink_TeamInstanceList_prev; // +0x3C
	Team *m_dlink_TeamInstanceList_next; // +0x40
};

Bool Team::dlink_isInList_TeamInstanceList(Team *const *pListHead) const
{
	return *pListHead == this || m_dlink_TeamInstanceList_prev != 0 || m_dlink_TeamInstanceList_next != 0;
}
