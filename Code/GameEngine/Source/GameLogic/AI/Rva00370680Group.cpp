// cl: /DNDEBUG /MD
// ?groupOneRing@AIGroup@@QAEXXZ @0x00370680 72B
// AIGroup member walk in the 0x003703CF..0x00370517 AIGroup block (same
// list-at-+0 plus Object+0x258 AI loop as Rva00370410Group.cpp): for each
// non-null member whose matched Object::rva0028F4BC finds the Rva00373EC6
// module, idle its AI from CMD_FROM_AI (rowed aiIdle) when it has one, then run
// the rowed Rva00373EC6::rva00374815 activation. Single caller 0x003799E4.
#include <list>

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	AICommandInterface m_commands;
};

class Rva00373EC6
{
public:
	void rva00374815();
};

class Object
{
public:
	Rva00373EC6 *rva0028F4BC();
	char m_pad[0x258];
	AIUpdateInterface *m_ai;
};

class AIGroup
{
public:
	void groupOneRing();
private:
	std::list<Object *> m_memberList;
};

void AIGroup::groupOneRing()
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		if (obj == 0)
			continue;
		AIUpdateInterface *ai = obj->m_ai;
		Rva00373EC6 *module = obj->rva0028F4BC();
		if (module == 0)
			continue;
		if (ai != 0)
			ai->m_commands.aiIdle(CMD_FROM_AI);
		module->rva00374815();
	}
}
