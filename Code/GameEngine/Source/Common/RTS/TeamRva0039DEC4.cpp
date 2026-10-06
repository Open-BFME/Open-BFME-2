// cl: /DNDEBUG /MD
//
// ?rva0039DEC4@Team@@QAE_NXZ @0x0039DEC4 (88B).
// Team member scan returning true when a live member passes the 0x108 kind
// gates plus the 0x11A bit gate. Retail walks via rowed iterate 0x263864
// and DLINK advance 0x263526 (pin), skips dead Object+0x438 bit0 and status
// Object+0x94 bit0, template dword at +0x108 bits 0x80 and 0x2000000, then
// returns true when template byte at +0x11A bit 0x10 is clear. Same flags
// and sibling model as TeamRva0039DE46 and TeamRva0039DF1C. Callers at
// 0x0039E755 0x0039EECC 0x003C00F8 0x003E93CC 0x003E9434 0x004F3E69.
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
	unsigned char m_pad108[0x108];
	int m_kind0;
	unsigned char m_pad10C[0x11A - 0x10C];
	unsigned char m_kindByte11a;
};

class Object
{
public:
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
	unsigned char m_pad8[0x94 - 0x08];
	unsigned char m_status94;
	unsigned char m_pad95[0x438 - 0x95];
	unsigned char m_dead;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	bool rva0039DEC4();
};

bool Team::rva0039DEC4()
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		if ((cur->m_dead & 1) != 0)
			continue;
		if ((cur->m_status94 & 1) != 0)
			continue;
		ThingTemplate *tmpl = cur->m_template;
		if ((tmpl->m_kind0 & 0x80) != 0)
			continue;
		if ((tmpl->m_kind0 & 0x2000000) != 0)
			continue;
		if ((tmpl->m_kindByte11a & 0x10) == 0)
			return true;
	}
	return false;
}
