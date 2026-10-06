// cl: /DNDEBUG /MD
// ?rva003704D3@AIGroup@@QAEXPBVPolygonTrigger@@HW4CommandSourceType@@PBUCoord3D@@@Z @0x003704D3 68B
// AIGroup forward of rva0036F629 to each member via rowed 0x0036F629,
// null trigger returns, same list-at-+0 plus Object+0x258 plus +0x20 loop.
// Evidence: calls 0x0036F629; caller 0x003BF89B; unblocks 0x003BF813;
// precedent Rva00370492Group.cpp 65B same loop with 3 args.
#include <list>

class PolygonTrigger;

struct Coord3D
{
	float x;
	float y;
	float z;
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
	void rva0036F629(const PolygonTrigger *trigger, int x, CommandSourceType cmdSource, const Coord3D *coord);
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
	void rva003704D3(const PolygonTrigger *trigger, int x, CommandSourceType cmdSource, const Coord3D *coord);
private:
	std::list<Object *> m_memberList;
};

void AIGroup::rva003704D3(const PolygonTrigger *trigger, int x, CommandSourceType cmdSource, const Coord3D *coord)
{
	if (trigger == 0)
		return;
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F629(trigger, x, cmdSource, coord);
	}
}
