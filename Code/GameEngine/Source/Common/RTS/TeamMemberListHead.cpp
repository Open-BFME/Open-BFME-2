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
// out-of-line copy (0x0028A74F) is in TeamIsInTeamMemberList.cpp; the
// canonical Team header declares it out of line, so the bodies spell the
// macro's inline test themselves.
typedef bool Bool;

#include "../../../Include/Common/TeamBFME2.h"

class Object
{
public:
	Bool dlink_isInList_TeamMemberList(Object * const *pListHead) const;
	void dlink_prependTo_TeamMemberList(Object **pListHead);
	void dlink_removeFrom_TeamMemberList(Object **pListHead);
};

void Team::prependTo_TeamMemberList(Object *object)
{
	if (!object->dlink_isInList_TeamMemberList(&m_dlinkhead_TeamMemberList))
		object->dlink_prependTo_TeamMemberList(&m_dlinkhead_TeamMemberList);
}

void Team::removeFrom_TeamMemberList(Object *object)
{
	if (object->dlink_isInList_TeamMemberList(&m_dlinkhead_TeamMemberList))
		object->dlink_removeFrom_TeamMemberList(&m_dlinkhead_TeamMemberList);
}
