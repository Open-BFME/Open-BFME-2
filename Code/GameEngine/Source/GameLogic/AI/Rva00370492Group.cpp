// cl: /DNDEBUG /MD
// ?rva00370492@AIGroup@@QAEXPBVPolygonTrigger@@HW4CommandSourceType@@@Z @0x00370492 65B
// AIGroup forward of rva0036F5BB to each member via rowed 0x0036F5BB,
// null trigger returns, same list-at-+0 plus Object+0x258 plus +0x20 loop.
// Evidence: calls 0x0036F5BB; caller 0x003BF8A9; unblocks 0x003BF813;
// precedent Rva00370451Group.cpp 65B same loop with Team.
#include <list>

class PolygonTrigger;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void rva0036F5BB(const PolygonTrigger *trigger, int x, CommandSourceType cmdSource);
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
	void rva00370492(const PolygonTrigger *trigger, int x, CommandSourceType cmdSource);
private:
	std::list<Object *> m_memberList;
};

void AIGroup::rva00370492(const PolygonTrigger *trigger, int x, CommandSourceType cmdSource)
{
	if (trigger == 0)
		return;
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F5BB(trigger, x, cmdSource);
	}
}
