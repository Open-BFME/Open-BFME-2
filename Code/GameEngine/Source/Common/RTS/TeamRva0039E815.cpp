// cl: /DNDEBUG /MD
//
// ?rva0039E815@Team@@QAE_NXZ @0x0039E815 54B, true when any member template has byte +0x5e6 set.
// Retail walks the 24-byte iterator via rowed iterate_TeamMemberList at
// 0x00263864 and DLINK advance pinned at 0x00263526, loading template at
// Object+0x04 then testing byte at template+0x5e6. Prev 0x0039E7F2 and next
// 0x0039E8EB share the Team iteration and DLINK layout. Caller at 0x0039EFDE.

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
	unsigned char m_pad[0x5e6];
	unsigned char m_byte5e6;
};

class Object
{
public:
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	bool rva0039E815();
};

bool Team::rva0039E815()
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		ThingTemplate *tmpl = cur->m_template;
		if (tmpl->m_byte5e6 != 0)
			return true;
	}
	return false;
}
