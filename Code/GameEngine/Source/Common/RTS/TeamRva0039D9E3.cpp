// cl: /DNDEBUG /MD
//
// ?rva0039D9E3@Team@@QBEHXZ @0x0039D9E3 (71B).
// Team::rva0039D9E3(): counts live members that either have an AI interface
// or whose template kind0 has bit 0x80. Retail walks via the rowed
// iterate_TeamMemberList at 0x263864 and advance at 0x263526, skipping dead
// bit at Object+0x438 bit0, then counting when AI at Object+0x258 is present
// otherwise checking template at Object+0x04 kind byte at +0x108 bit 0x80.
// Callers none yet; neighbours getControllingPlayer and healAllObjects share
// the /O1 flags and 24-byte iterator shape.

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
	unsigned char m_kind0;
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

class Object
{
public:
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
	unsigned char m_pad1[0x258 - 0x08];
	AIUpdateInterface *m_ai;
	unsigned char m_pad2[0x438 - 0x25C];
	unsigned char m_dead;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	int rva0039D9E3() const;
	int rva0039DC63() const;
	bool rva0039DAF4() const;
};

int Team::rva0039D9E3() const
{
	int count = 0;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		if ((cur->m_dead & 1) != 0)
			continue;
		if (cur->m_ai != 0) {
			++count;
			continue;
		}
		ThingTemplate *tmpl = cur->m_template;
		if ((tmpl->m_kind0 & 0x80) == 0)
			continue;
		++count;
	}
	return count;
}

// ?rva0039DC63@Team@@QBEHXZ @0x0039DC63 (59B).
// Team::rva0039DC63(): counts members whose template is present and whose
// template kind0 has bit 0x80. Retail walks via the rowed
// iterate_TeamMemberList at 0x263864 and advance at 0x263526, with the same
// 24-byte iterator and +0x04/+0x108 layout as the rva0039D9E3 sibling above.
// Caller at 0x0039ECF4.
int Team::rva0039DC63() const
{
	int count = 0;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		ThingTemplate *tmpl = cur->m_template;
		if( tmpl == 0 )
			continue;
		if( (tmpl->m_kind0 & 0x80) == 0 )
			continue;
		++count;
	}
	return count;
}

// ?rva0039DAF4@Team@@QBE_NXZ @0x0039DAF4 (61B).
// Team::rva0039DAF4(): true when any member has a current victim. Walks via
// rowed iterate_TeamMemberList at 0x263864 and advance at 0x263526, reads
// AI at Object+0x258 and calls rowed getCurrentVictim at 0x00268D71.
// Caller at 0x004ED068. Same /O1 flags and 24-byte iterator as siblings.
bool Team::rva0039DAF4() const
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		AIUpdateInterface *ai = cur->m_ai;
		if (ai == 0)
			continue;
		if (ai->getCurrentVictim() != 0)
			return true;
	}
	return false;
}
