// cl: /GX- /MD
// ?doesTeamMeetThreat@AITeamBuilder@@QAEHPAVTeam@@@Z @0x0059A1C1 151B.
// Chain of 0x002A8B73: lookup max via global Rva002A8F24 then float-gate the
// Team sum of +0x51c over members whose template kind has 8 at +0x108 or 4 at
// +0x113. Evidence: caller 0x0059AD0D; callees rowed 0x002A8B73 0x002C5AE6
// 0x00263864 0x00263526; prev Rva00599FD7Count Team/iterator pattern.
class ThingTemplate
{
public:
	unsigned char m_pad108[0x108];
	unsigned char m_kind0;
	unsigned char m_pad109[0x0A];
	unsigned char m_kind1;
	unsigned char m_pad113[0x51C - 0x114];
	float m_51C;
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

struct TeamProto
{
	char m_pad[0x2C4];
	int m_2C4;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	char m_pad00[0x30];
	TeamProto *m_proto30;
};

class Rva002A8F24
{
public:
	void *rva002A8B73(void *key, int key2);
};
extern Rva002A8F24 *g_00DFEEF8;

class Rva002C589B
{
public:
	float rva002C5AE6();
};

class AITeamBuilder
{
public:
	int doesTeamMeetThreat(Team *team);
private:
	char m_pad00[0x14];
	int m_14;
};

int AITeamBuilder::doesTeamMeetThreat(Team *team)
{
	void *found = g_00DFEEF8->rva002A8B73((void *)m_14, team->m_proto30->m_2C4);
	float vmax = 0.0f;
	if (found != 0)
		vmax = ((Rva002C589B *)found)->rva002C5AE6();
	float sum = 0.0f;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); ((DLINK_ITERATOR<Object> &)iter).advance())
	{
		Object *cur = iter.cur();
		ThingTemplate *tmpl = cur->m_template;
		if ((tmpl->m_kind0 & 8) != 0 || (tmpl->m_kind1 & 4) != 0)
			sum += tmpl->m_51C;
	}
	return sum >= vmax;
}
