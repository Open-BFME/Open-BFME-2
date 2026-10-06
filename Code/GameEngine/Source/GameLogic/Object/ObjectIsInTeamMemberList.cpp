// cl: /O1 /DNDEBUG /MD
// ?dlink_isInList_TeamMemberList@Object@@QBE_NPBQAV1@@Z, retail 0x0028A6C7
// (32 bytes).
// Identity: WorldBuilder maps this address to the TeamMemberList DLINK
// helper (Team.h:196, Team::isInList_TeamMemberList, which forwards to the
// member's own test), and retail's Team::LoadPostProcess (0x003A2339) calls
// it on the found Object with &team->m_dlinkhead_TeamMemberList (+0x38).
// Donor (Zero Hour GameCommon.h MAKE_DLINK): *pListHead == this, or either
// link set. Layout (target): the TeamMemberList prev/next links sit at
// +0x328/+0x32C, the same pair the rowed insert 0x0028A6E7 and remove
// 0x0028A704 neighbours use.
class Object
{
public:
	bool dlink_isInList_TeamMemberList(Object * const *pListHead) const;

private:
	unsigned char m_pad000[0x328];
	Object *m_dlinkprev_TeamMemberList; // +0x328
	Object *m_dlinknext_TeamMemberList; // +0x32C
};

bool Object::dlink_isInList_TeamMemberList(Object * const *pListHead) const
{
	return *pListHead == this || m_dlinkprev_TeamMemberList || m_dlinknext_TeamMemberList;
}
