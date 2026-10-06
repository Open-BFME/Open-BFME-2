// cl: /O1 /DNDEBUG /MD
// ?isInList_TeamMemberList@Team@@QBE_NPAVObject@@@Z, retail 0x0028A74F (16B).
// Zero Hour GameCommon.h MAKE_DLINK_HEAD(Object, TeamMemberList) isInList
// (donor source): forwards the Team+0x38 head to the matched
// Object::dlink_isInList_TeamMemberList (0x0028A6C7).
// Target evidence: the body sits between the matched
// Object::dlink_removeFrom_TeamMemberList (0x0028A704, 75B, ends here) and
// Team::prependTo_TeamMemberList (0x0028A75F), whose inlined isInList test
// is these same instructions; Team+0x38 is the head the matched
// Team::iterate_TeamMemberList (0x00263864) reads. No direct caller in
// game.dat: it is the out-of-line copy of a member the siblings inline.
typedef bool Bool;

class Object
{
public:
	Bool dlink_isInList_TeamMemberList(Object * const *pListHead) const;
};

class Team
{
public:
	Bool isInList_TeamMemberList(Object *o) const;

private:
	unsigned char m_pad000[0x38];
	struct DLINKHEAD_TeamMemberList { Object *m_head; } m_dlinkhead_TeamMemberList; // +0x38
};

Bool Team::isInList_TeamMemberList(Object *o) const
{
	return o->dlink_isInList_TeamMemberList(&m_dlinkhead_TeamMemberList.m_head);
}
