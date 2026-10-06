// cl: /O1 /DNDEBUG /MD
// Object's TeamMemberList DLINK insert/remove, from the Zero Hour GameCommon.h
// MAKE_DLINK macro (donor source; carried, not a retail symbol):
//   ?dlink_prependTo_TeamMemberList@Object@@QAEXPAPAV1@@Z   0x0028A6E7 (29B)
//   ?dlink_removeFrom_TeamMemberList@Object@@QAEXPAPAV1@@Z  0x0028A704 (75B)
// Target evidence: both bodies were rowed earlier as anonymous list helpers
// (Rva0028A6E7 / Rva0028A704) on the +0x328/+0x32C link pair that the matched
// Object::dlink_isInList_TeamMemberList (0x0028A6C7) tests. Their only callers
// are Team::prependTo_TeamMemberList (0x0028A776) and
// Team::removeFrom_TeamMemberList (0x0028A796), each of which first calls
// dlink_isInList_TeamMemberList with &team->m_dlinkhead_TeamMemberList
// (Team+0x38, the head Team::iterate_TeamMemberList 0x00263864 also reads) --
// the exact shape of the macro's prependTo_/removeFrom_ inlines.
class Object
{
public:
	void dlink_prependTo_TeamMemberList(Object **pListHead);
	void dlink_removeFrom_TeamMemberList(Object **pListHead);

private:
	unsigned char m_pad000[0x328];
	Object *m_dlinkprev_TeamMemberList; // +0x328
	Object *m_dlinknext_TeamMemberList; // +0x32C
};

void Object::dlink_prependTo_TeamMemberList(Object **pListHead)
{
	m_dlinknext_TeamMemberList = *pListHead;
	if (*pListHead != 0)
		(*pListHead)->m_dlinkprev_TeamMemberList = this;
	*pListHead = this;
}

void Object::dlink_removeFrom_TeamMemberList(Object **pListHead)
{
	if (m_dlinknext_TeamMemberList != 0)
		m_dlinknext_TeamMemberList->m_dlinkprev_TeamMemberList = m_dlinkprev_TeamMemberList;
	Object **prevPtr = &m_dlinkprev_TeamMemberList;
	if (*prevPtr != 0)
		(*prevPtr)->m_dlinknext_TeamMemberList = m_dlinknext_TeamMemberList;
	else
		*pListHead = m_dlinknext_TeamMemberList;
	m_dlinkprev_TeamMemberList = 0;
	m_dlinknext_TeamMemberList = 0;
}
