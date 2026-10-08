// cl: /DNDEBUG /MD
// ?getTeamAsAIGroup@Team@@QAEXPAVAIGroup@@@Z
// Target boundary 0x003A0F62..0x003A0FD2 (112B). BFME2's
// TEAM_SET_ATTITUDE body at 0x003BEE5E passes the team as this and its newly
// created AIGroup as the argument.
// Target disassembly calls rowed Object::rva002931BA (0x002931BA),
// Object::testStatus (0x0004E536), GameLogic::findObjectByID (0x00049DC5),
// then AIGroup::add at 0x0036E5F1. It reads the producer ID at Object+0x78,
// TheGameLogic at 0x00DFE78C, and the resolved template's byte +0x115 bit 0x20.
// Donor provenance: BFME1's matched Team::getTeamAsAIGroup at 0x000F45A0
// (126B), TeamMemberQueries.cpp, supplies the team-list iteration, member
// filtering, lookup, and AIGroup::add semantics; BFME2's offsets and helper
// calls above are target evidence, not copied BFME1 layout facts.

typedef bool Bool;

class Object;
class Player;
class AIGroup;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNNAMED_2 = 2
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	void advance();
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
};

// advance() is the rowed 32-byte DLINK_ITERATOR<Object> body at 0x263526,
// which consumes the 20-byte virtual-member state above; the 21-byte
// direct-next body at 0x203C93 is the DLINK_ITERATOR<Team> instantiation.
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	Bool rva002931BA();
	Bool testStatus(ObjectStatusTypes status) const;

	unsigned char m_head[4];
	struct ThingTemplate *m_template;
	unsigned char m_mid08[0x78 - 0x08];
	ObjectID m_producerID;
};

class AIGroup
{
public:
	void add(Object *object);
};

struct ThingTemplate
{
	unsigned char m_head[0x115];
	unsigned char m_kindByte115;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	void getTeamAsAIGroup(AIGroup *group);
};

void Team::getTeamAsAIGroup(AIGroup *pAIGroup)
{
	if (pAIGroup == 0)
		return;

	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done();
		reinterpret_cast<DLINK_ITERATOR<Object> *>(&iter)->advance())
	{
		Object *member = iter.cur();
		if (member->rva002931BA())
			continue;
		if (member->testStatus(OBJECT_STATUS_UNNAMED_2))
			continue;
		if (member->m_producerID != 0)
		{
			Object *found = TheGameLogic->findObjectByID(member->m_producerID);
			if (found != 0 && (found->m_template->m_kindByte115 & 0x20) != 0)
				continue;
		}
		pAIGroup->add(member);
	}
}
