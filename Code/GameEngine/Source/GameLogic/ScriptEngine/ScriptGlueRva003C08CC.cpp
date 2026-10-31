// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
// stlport
//
// ?rva003C08CC@Rva003C08CC@@QAEXPBVAsciiString@@PAX@Z @0x003C08CC 183B.
// Team member-flag dispatch: team-name copy, getTeamNamed, AI createGroup,
// getTeamAsAIGroup, AIGroup::groupIdle (0x0036FC23) from a script, null
// check on the extra arg, controlling player plus its +0x2EC object, member
// loop setting +0x3BE on +0x258-linked objects, then ScriptActions'
// doMergeTeamIntoTeam (0x003C01E2) on the forwarded this with the team name
// plus a static-or-member string. String/flag identities unproven. Both
// callees are called by their rows' names; the protected merge is reached
// through a ScriptActions base.
#include "ascii_string.h"
#include "GameLogic/ScriptActionsBFME2.h"

enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };

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
	unsigned char m_isRecruitable;
};

class Object
{
public:
	char m_pad[0x258];
	Rva003C08CC258 *m_p258; // +0x258
};

class Player;

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
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
	void groupIdle(CommandSourceType cmdSource);
};

struct Rva003C08CCP2EC
{
	char m_pad[0x30];
	void *m_proto;
};

class Player
{
public:
	char m_pad[0x2EC];
	Rva003C08CCP2EC *m_p2EC; // +0x2EC
};

class Rva003C08CC : public ScriptActions
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
	group->groupIdle(CMD_FROM_SCRIPT);
	if (extra == 0)
		return;
	Player *player = team->getControllingPlayer();
	Rva003C08CCP2EC *playerDefaultTeam = player->m_p2EC;
	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
	while (!iter.done()) {
		Object *teamMember = iter.cur();
		Rva003C08CC258 *ai = teamMember->m_p258;
		if (ai != 0)
			ai->m_isRecruitable = 1;
		iter.advance();
	}
	const AsciiString *defaultTeamName;
	if (playerDefaultTeam->m_proto == 0)
		defaultTeamName = &AsciiString::TheEmptyString;
	else
		defaultTeamName = (const AsciiString *)((const char *)playerDefaultTeam->m_proto + 0x14);
	doMergeTeamIntoTeam(*teamName, *defaultTeamName);
}
