// cl: /DNDEBUG /MD
//
// ?rva0036F9FE@AIGroup@@QAEXPBVWaypoint@@W4CommandSourceType@@H@Z, retail 0x0036F9FE, 88 bytes.
// AIGroup mode switch forwarding to each member via rowed aiFollowWaypointPath
// at 0x0036EC82 (mode 0) and the pinned invoke at 0x00352F2F (mode 1 with
// 0x7FFFFFFF). Evidence: same list-at-+0x00 plus Object+0x258 plus +0x20
// subobject loop as groupAttackTeam and the landed rva0036FA56/rva0036FBC5;
// callers at 0x003BF1DD 0x003BF4C3 0x003BF5F2; both callees share the +0x20
// subobject (union in TU).

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
	void aiFollowWaypointPath(const Waypoint *waypoint, CommandSourceType cmdSource);
};

class Rva00352F2FOpaque
{
public:
	void invoke(const Waypoint *waypoint, int maxShots, CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	union
	{
		AICommandInterface m_commands;
		Rva00352F2FOpaque m_invokeHolder;
	};
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
	void rva0036F9FE(const Waypoint *waypoint, CommandSourceType cmdSource, int mode);
private:
	std::list<Object *> m_memberList;
};

void AIGroup::rva0036F9FE(const Waypoint *waypoint, CommandSourceType cmdSource, int mode)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai == 0)
			continue;
		switch (mode)
		{
		case 1:
			reinterpret_cast<Rva00352F2FOpaque*>(&ai->m_commands)->invoke(waypoint, 0x7FFFFFFF, cmdSource);
			break;
		case 0:
			ai->m_commands.aiFollowWaypointPath(waypoint, cmdSource);
			break;
		default:
			break;
		}
	}
}
