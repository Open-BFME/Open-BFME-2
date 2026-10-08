// cl: /GX-
//
// ?getCurNumUnits@AITeamBuilder@@QAEHPAVTeam@@@Z @0x00599FD7 69B
// Count team members whose template kind bytes have bit 8 at +0x108 or bit 4
// at +0x113. Evidence: unlock lane, iterate at 0x00263864 plus advance,
// ret-4 single Team arg, 2 callers, OR of two byte tests, honest Count verb.
class ThingTemplate
{
public:
	unsigned char m_pad108[0x108];
	unsigned char m_kind0;
	unsigned char m_pad109[0x0A];
	unsigned char m_kind1;
};

class Object
{
public:
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
};

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

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class AITeamBuilder
{
public:
	int getCurNumUnits(Team *team);
};

int AITeamBuilder::getCurNumUnits(Team *team)
{
	int count = 0;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); ((DLINK_ITERATOR<Object> &)iter).advance()) {
		Object *cur = iter.cur();
		ThingTemplate *tmpl = cur->m_template;
		if ((tmpl->m_kind0 & 8) != 0 || (tmpl->m_kind1 & 4) != 0)
			++count;
	}
	return count;
}
