// cl: /O1 /DNDEBUG /MD
// ?didAllEnter@Team@@QAE_NPAVPolygonTrigger@@I@Z @0x0039E15D 176B.
// ?didAllExit@Team@@QAE_NPAVPolygonTrigger@@I@Z @0x0039E303 197B.
// Identity: BFME1 donor
// reference/open-bfme-1/Code/GameEngine/Source/Common/RTS/TeamTriggerAreaTests.cpp
// (didAllEnter / didAllExit) proves the names and loops; they sit with the
// rowed trigger-area siblings in TeamDidPartialEnter.cpp. Callers 0x003E6DFE /
// 0x003E7011 (didAllEnter) and 0x003E6EC6 / 0x003E7024 (didAllExit) pass Team
// ECX with trigger/type args.
// BFME 2 deltas (target): the guard is the byte at Team +0x5C; a member is
// considered when its AI (+0x258) surfaces (+0x1DC) hold 1 << which, or,
// without AI, when which is 0; dead members (+0x438 bit 0) and templates
// (+0x04) with kind byte +0x113 bit 1 are skipped, didAllExit also skips
// kind byte +0x118 bit 0x40. didEnter / didExit / isInside are the Object
// members 0x0028D718 / 0x0028D757 / 0x0028B411.
// Shape: the DLINK iterator and Team::iterate_TeamMemberList are defined
// in-TU over the virtual-inheritance Object skeleton (TeamUpdateState.cpp);
// with the declared-only iterator the member landed in EAX instead of ESI.

typedef unsigned int UnsignedInt;

class PolygonTrigger;
class Object;

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x1dc];
	UnsignedInt m_surfaces;		// +0x1DC
};

struct ThingTemplate
{
	unsigned char m_pad[0x113];
	unsigned char m_kindByte113;	// +0x113
	unsigned char m_pad114[0x118 - 0x114];
	unsigned char m_kindByte118;	// +0x118
};

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

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

class BfmeObjectDlinkPad
{
public:
	ThingTemplate *m_template;	// +0x04
	unsigned char m_pad[0x60];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	bool didEnter(PolygonTrigger *pTrigger);	// 0x0028D718
	bool didExit(PolygonTrigger *pTrigger);		// 0x0028D757
	bool isInside(PolygonTrigger *pTrigger);	// 0x0028B411

	unsigned char m_pad070[0x258 - 0x70];
	AIUpdateInterface *m_ai;	// +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_dead;		// +0x438
};

// DLINK_ITERATOR<Object>::advance (0x00263526) and
// Team::iterate_TeamMemberList (0x00263864) are defined as in the header;
// neither is inlined here.
template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = ((*m_cur).*(m_getNextFunc))(); }
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const { return DLINK_ITERATOR<Object>(m_head, &Object::dlink_next_TeamMemberList); }
	bool didAllEnter(PolygonTrigger *pTrigger, UnsignedInt whichToConsider);
	bool didAllExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider);

private:
	unsigned char m_pad00[0x38];
	Object *m_head;			// +0x38
	unsigned char m_pad3C[0x5c - 0x3C];
	bool m_enteredOrExited;		// +0x5C
};

bool Team::didAllEnter(PolygonTrigger *pTrigger, UnsignedInt whichToConsider)
{
	if (!m_enteredOrExited)
		return false;

	bool entered = false;
	bool outside = false;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		AIUpdateInterface *ai = cur->m_ai;
		if (ai) {
			UnsignedInt mask = 1u << whichToConsider;
			if ((ai->m_surfaces & mask) == 0)
				continue;
		} else {
			unsigned char mask8 = (unsigned char)(1u << whichToConsider);
			if ((mask8 & 1) == 0)
				continue;
		}
		if ((cur->m_dead & 1) != 0)
			continue;
		ThingTemplate *tmpl = cur->m_template;
		if ((tmpl->m_kindByte113 & 2) != 0)
			continue;
		if (cur->didEnter(pTrigger))
			entered = true;
		else if (!cur->isInside(pTrigger))
			outside = true;
	}
	return entered && !outside;
}

bool Team::didAllExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider)
{
	if (!m_enteredOrExited)
		return false;

	bool anyConsidered = false;
	bool exited = false;
	bool inside = false;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		AIUpdateInterface *ai = cur->m_ai;
		if (ai) {
			UnsignedInt mask = 1u << whichToConsider;
			if ((ai->m_surfaces & mask) == 0)
				continue;
		} else {
			unsigned char mask8 = (unsigned char)(1u << whichToConsider);
			if ((mask8 & 1) == 0)
				continue;
		}
		if ((cur->m_dead & 1) != 0)
			continue;
		ThingTemplate *tmpl = cur->m_template;
		if ((tmpl->m_kindByte113 & 2) != 0)
			continue;
		if ((tmpl->m_kindByte118 & 0x40) != 0)
			continue;
		if (cur->didExit(pTrigger))
			exited = true;
		else if (cur->isInside(pTrigger))
			inside = true;
		anyConsidered = true;
	}
	return anyConsidered && exited && !inside;
}
