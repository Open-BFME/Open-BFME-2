// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
//
// ?rva003C08CC@Rva003C08CC@@QAEXPBVAsciiString@@PAX@Z @0x003C08CC 183B.
// Team member-flag dispatch: team-name copy, getTeamNamed, AI createGroup,
// getTeamAsAIGroup, pinned AIGroup 0x0036FC23 member with 1, null check on
// the extra arg, controlling player plus its +0x2EC object, member loop
// setting +0x3BE on +0x258-linked objects, then the banked 0x003C01E2
// thiscall (forwarded this) with the team name plus a static-or-member
// string. String/flag identities unproven.
#include "ascii_string.h"

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

struct Rva003C08CC258
{
	char m_pad[0x3BE];
	unsigned char m_3BE;
};

class Object
{
public:
	char m_pad[0x258];
	Rva003C08CC258 *m_p258; // +0x258
};

class Player;

class Team
{
public:
	Player *getControllingPlayer() const;
	void getTeamAsAIGroup(class AIGroup *group);
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern ScriptEngine *TheScriptEngine;

class AIGroup;
class AI
{
public:
	AIGroup *createGroup();
};
extern AI *TheAI;

class AIGroup
{
public:
	void rva0036FC23(int v);
};

struct Rva003C08CCP2EC
{
	char m_pad[0x30];
	void *m_p30;
};

class Player
{
public:
	char m_pad[0x2EC];
	Rva003C08CCP2EC *m_p2EC; // +0x2EC
};


class Rva003C01E2
{
public:
	void rva003C01E2(const AsciiString *a, const AsciiString *b);
};

class Rva003C08CC
{
public:
	void rva003C08CC(const AsciiString *teamName, bool extra);
};

void Rva003C08CC::rva003C08CC(const AsciiString *teamName, bool extra)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (team == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	group->rva0036FC23(1);
	if (extra == 0)
		return;
	Player *player = team->getControllingPlayer();
	Rva003C08CCP2EC *e = player->m_p2EC;
	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	while (!iter.done()) {
		Object *o = iter.cur();
		Rva003C08CC258 *p = o->m_p258;
		if (p != 0)
			p->m_3BE = 1;
		iter.advance();
	}
	const AsciiString *s;
	if (e->m_p30 == 0)
		s = &AsciiString::TheEmptyString;
	else
		s = (const AsciiString *)((const char *)e->m_p30 + 0x14);
	((Rva003C01E2 *)this)->rva003C01E2(teamName, s);
}
