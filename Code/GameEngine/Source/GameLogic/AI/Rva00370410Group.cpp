// cl: /DNDEBUG /MD
// ?rva00370410@AIGroup@@QAEXPAVObject@@HW4CommandSourceType@@@Z @0x00370410 65B
// AIGroup forward of rva0036F4DF to each member via rowed 0x0036F4DF,
// null object returns, same list-at-+0 plus Object+0x258 plus +0x20 loop.
// Evidence: calls 0x0036F4DF; callers 0x00378690 0x003BF807 0x003C2BB5;
// precedent Rva003703CFGroup.cpp 65B same loop with aiGuardPosition.
#include <list>

class Object;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void rva0036F4DF(Object *obj, int x, CommandSourceType cmdSource);
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
	void rva00370410(Object *obj, int x, CommandSourceType cmdSource);
private:
	std::list<Object *> m_memberList;
};

void AIGroup::rva00370410(Object *obj, int x, CommandSourceType cmdSource)
{
	if (obj == 0)
		return;
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F4DF(obj, x, cmdSource);
	}
}
