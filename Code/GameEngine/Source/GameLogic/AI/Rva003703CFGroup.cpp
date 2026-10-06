// cl: /DNDEBUG /MD
// ?groupGuardPosition@AIGroup@@QAEXPBUCoord3D@@W4GuardMode@@W4CommandSourceType@@@Z @0x003703CF 65B
// AIGroup forward of aiGuardPosition to each member via rowed 0x0036F46A,
// null position returns, same list-at-+0 plus Object+0x258 plus +0x20 loop.
// Evidence: calls 0x0036F46A; callers 0x0037864E 0x003BF7A0 0x004F2BE3;
// precedent AIGroupFollowWaypointPathExact.cpp and BfmeCommand33.cpp same loop.
#include <list>

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum GuardMode
{
	GUARDMODE_DUMMY = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiGuardPosition(const Coord3D *pos, GuardMode mode, CommandSourceType cmdSource);
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
	void groupGuardPosition(const Coord3D *pos, GuardMode mode, CommandSourceType cmdSource);
private:
	std::list<Object *> m_memberList;
};

void AIGroup::groupGuardPosition(const Coord3D *pos, GuardMode mode, CommandSourceType cmdSource)
{
	if (pos == 0)
		return;
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.aiGuardPosition(pos, mode, cmdSource);
	}
}
