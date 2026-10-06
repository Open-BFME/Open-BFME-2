// cl: /DNDEBUG /MD
//
// ?rva0036FBC5@AIGroup@@QAEXPBVWaypoint@@W4CommandSourceType@@@Z, retail 0x0036FBC5, 61 bytes.
// AIGroup forward of aiBfmeCommand33 to each member via the rowed
// AICommandInterface method at 0x0036EDB1 plus an Object+0x410 clear.
// Evidence: same list-at-+0x00 plus Object+0x258 plus +0x20 subobject loop
// as the rowed groupAttackTeam at 0x0036FF33 and the landed rva0036FA56 at
// 0x0036FA56; caller at 0x003BF70B.

#include <list>

class Waypoint;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiBfmeCommand33(const Waypoint *waypoint, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	void rva0026DE3B(int arg);
	char m_pad[0x20];
	AICommandInterface m_commands;
};

class Object
{
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x410 - 0x25C];
	int m_410;
};

class AIGroup
{
public:
	void rva0036FBC5(const Waypoint *waypoint, CommandSourceType cmdSource);
private:
	std::list<Object *> m_memberList;
};

void AIGroup::rva0036FBC5(const Waypoint *waypoint, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		obj->m_410 = 0;
		AIUpdateInterface *ai = obj->m_ai;
		if (ai != 0)
			ai->m_commands.aiBfmeCommand33(waypoint, cmdSource);
	}
}
