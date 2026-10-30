// cl: /O1 /DNDEBUG /MD
//
// ?iterate_TeamMemberList@Team@@QBE?AV?$DLINK_ITERATOR@VObject@@@@XZ @0x00263864 (49B).
// Team::iterate_TeamMemberList(): returns the 24-byte DLINK iterator over the
// member list. Retail loads the head at Team+0x38 and materializes the
// virtual-inheritance member pointer {pfn delta -100 vindex 0} for
// Object::dlink_next_TeamMemberList, copying 12 bytes to the output at +8 and
// storing the head at +0. BFME1 donor GameCommon.h MAKE_DLINK_HEAD proves the
// name and construction; BFME2 deltas are the +0x38 head and the inherited
// vbptr layout at Object+0x68 giving delta -100. Callers include 0x003C9A80
// and 0x0039E042 which copy the 24-byte output.

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

// Introduces the vbptr at its own +0; lands at +0x68 inside Object.
class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

// ??0?$DLINK_ITERATOR@VObject@@@@QAE@PAVObject@@P81@BEPAV1@XZ@Z present-unmatched
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

#include "../../../Include/Common/TeamBFME2.h"

inline DLINK_ITERATOR<Object> Team::iterate_TeamMemberList() const
{
	return DLINK_ITERATOR<Object>(m_dlinkhead_TeamMemberList, &Object::dlink_next_TeamMemberList);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeTeamInlineAnchor@@YAXPAVTeam@@@Z absent-from-retail
void _bfmeTeamInlineAnchor(Team *team)
{
    team->iterate_TeamMemberList();
}
#pragma inline_depth()
