// cl: /DNDEBUG /MD
// ?rva00370451@AIGroup@@QAEXPBVTeam@@HW4CommandSourceType@@@Z @0x00370451 65B
// AIGroup forward of rva0036F54D to each member via rowed 0x0036F54D,
// null team returns, same list-at-+0 plus Object+0x258 plus +0x20 loop.
// Evidence: calls 0x0036F54D; caller 0x003C2A94; unblocks 0x003C2A29;
// precedent Rva00370410Group.cpp 65B same loop with rva0036F4DF.
#include <list>

class Team;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void rva0036F54D(const Team *team, int x, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	AICommandInterface m_commands;
};

class Object
{
public:
	char m_pad[0x258];
	AIUpdateInterface *m_ai;
};

class AIGroup
{
public:
	void rva00370451(const Team *team, int x, CommandSourceType cmdSource);
private:
	std::list<Object *> m_memberList;
};

void AIGroup::rva00370451(const Team *team, int x, CommandSourceType cmdSource)
{
	if (team == 0)
		return;
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F54D(team, x, cmdSource);
	}
}
