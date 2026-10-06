// cl: /DNDEBUG /MD
//
// ?hasAnyObjects@Team@@QAE_N_N@Z @0x0039E042 (142B).
// Team::hasAnyObjects(): returns true when a live member survives the dead,
// status, bfmeFlag-gated kind/status, and template kind filters. Retail reads
// dead bit at Object+0x438 bit0, status byte at Object+0x94 bit0, bfmeFlag gate
// via template dword at +0x108 bit 0x80 plus Object dword at +0x114 bits 3 and 4
// (named bool locals force the two shr+test idioms), then template dwords at
// +0x108/+0x110 with 0x2000000 plus template byte at +0x11A bit 0x10. Walk uses
// the pinned iterate_TeamMemberList at 0x263864 and the pinned DLINK advance at
// 0x263526. BFME1 donor
// reference/open-bfme-1/Code/GameEngine/Source/Common/RTS/TeamMemberQueries.cpp:320
// proves the name and loop; BFME2 deltas are the non-const signature plus the
// +0x438/+0x94/+0x108/+0x110/+0x114/+0x11A layout above. Callers include
// 0x003E5E1D and 0x0039E3D3.

typedef unsigned int UnsignedInt;

class Object;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

struct ThingTemplate
{
	unsigned char m_pad[0x108];
	UnsignedInt m_kind0;
	unsigned char m_pad2[0x110 - 0x10c];
	UnsignedInt m_kind2;
	unsigned char m_pad3[0x11a - 0x114];
	unsigned char m_kindByte11a;
};

class Object
{
public:
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
	unsigned char m_pad1[0x94 - 0x8];
	unsigned char m_status94;
	unsigned char m_pad2[0x114 - 0x95];
	UnsignedInt m_status114;
	unsigned char m_pad3[0x438 - 0x118];
	unsigned char m_dead;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	bool hasAnyObjects(bool bfmeFlag);

private:
	unsigned char m_pad[0x5c];
	bool m_enteredOrExited;
};

bool Team::hasAnyObjects(bool bfmeFlag)
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		if ((cur->m_dead & 1) != 0)
			continue;
		if ((cur->m_status94 & 1) != 0)
			continue;
		if (bfmeFlag) {
			ThingTemplate *tmpl = cur->m_template;
			if ((tmpl->m_kind0 & 0x80) != 0) {
				UnsignedInt s = cur->m_status114;
				bool b3 = ((s >> 3) & 1) != 0;
				bool b4 = ((s >> 4) & 1) != 0;
				if (b3)
					continue;
				if (b4)
					continue;
			}
		}
		ThingTemplate *tmpl2 = cur->m_template;
		if ((tmpl2->m_kind0 & 0x2000000) != 0)
			continue;
		if ((tmpl2->m_kind2 & 0x2000000) != 0)
			continue;
		if ((tmpl2->m_kindByte11a & 0x10) != 0)
			continue;
		return true;
	}
	return false;
}
