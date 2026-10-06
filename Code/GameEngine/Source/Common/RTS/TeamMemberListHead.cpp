// cl: /O1 /DNDEBUG /MD
// Team's TeamMemberList DLINK head operations, from the Zero Hour GameCommon.h
// MAKE_DLINK_HEAD(Object, TeamMemberList) inlines (donor source):
//   ?prependTo_TeamMemberList@Team@@QAEXPAVObject@@@Z     0x0028A75F (32B)
//   ?removeFrom_TeamMemberList@Team@@QAEXPAVObject@@@Z    0x0028A77F (32B)
// Target evidence: WorldBuilder leads name 0x0028A75F/0x0028A77F
// Team::prependTo_/removeFrom_TeamMemberList; retail's bodies pass
// &m_dlinkhead_TeamMemberList (Team+0x38, the head the matched
// Team::iterate_TeamMemberList 0x00263864 reads) to the matched Object
// helpers dlink_isInList (0x0028A6C7), dlink_prependTo (0x0028A6E7) and
// dlink_removeFrom (0x0028A704). The boundaries are retail's: the three run
// back to back from the end of dlink_removeFrom to the getter at 0x0028A79F,
// each closing with ret 4. Both inline isInList_TeamMemberList, whose own
// out-of-line copy (0x0028A74F) is in TeamIsInTeamMemberList.cpp; here it
// stays the class-inline macro member, as in the donor.
typedef bool Bool;

class Object
{
public:
	Bool dlink_isInList_TeamMemberList(Object * const *pListHead) const;
	void dlink_prependTo_TeamMemberList(Object **pListHead);
	void dlink_removeFrom_TeamMemberList(Object **pListHead);
};

class Team
{
public:
	inline Bool isInList_TeamMemberList(Object *o) const
	{
		return o->dlink_isInList_TeamMemberList(&m_dlinkhead_TeamMemberList.m_head);
	}
	void prependTo_TeamMemberList(Object *o);
	void removeFrom_TeamMemberList(Object *o);

private:
	unsigned char m_pad000[0x38];
	struct DLINKHEAD_TeamMemberList { Object *m_head; } m_dlinkhead_TeamMemberList; // +0x38
};

void Team::prependTo_TeamMemberList(Object *o)
{
	if (!isInList_TeamMemberList(o))
		o->dlink_prependTo_TeamMemberList(&m_dlinkhead_TeamMemberList.m_head);
}

void Team::removeFrom_TeamMemberList(Object *o)
{
	if (isInList_TeamMemberList(o))
		o->dlink_removeFrom_TeamMemberList(&m_dlinkhead_TeamMemberList.m_head);
}
