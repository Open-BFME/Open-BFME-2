// cl: /DNDEBUG /MD
//
// ?rva0036FA56@AIGroup@@QAEXPBVWaypoint@@W4CommandSourceType@@@Z, retail 0x0036FA56, 54 bytes.
// AIGroup forward of aiFollowWaypointPathExact to each member via the rowed
// AICommandInterface method at 0x0036ECE7. Evidence: same list-at-+0x00 plus
// Object+0x258 plus +0x20 subobject loop as the rowed groupAttackTeam at
// 0x0036FF33 in AIGroupAttackTeam.cpp; caller at 0x003BF712; prev/next are
// aiGuardPosition and groupAttackTeam with compatible flags.

#include <list>

class Waypoint;
class Object;
struct Coord3D;
class Rva003427DD;

typedef int Int;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class AICommandInterface
{
public:
	void aiFollowWaypointPathExact(const Waypoint *waypoint, CommandSourceType cmdSource);
	void aiMoveToAndEvacuate(const Coord3D *pos, CommandSourceType cmdSource);
	void aiMoveToAndEvacuateAndExit(const Coord3D *pos, CommandSourceType cmdSource);
	void rva0036F19B(Object *obj, CommandSourceType cmdSource);
	void rva0036F200(Object *obj, CommandSourceType cmdSource);
	void rva0036F265(Object *obj, CommandSourceType cmdSource);
	void rva0036F2CA(Object *obj, CommandSourceType cmdSource);
	void rva0026C3AC(Object *obj, CommandSourceType cmdSource);
	void aiHarvest(const Coord3D *pos, CommandSourceType cmdSource);
	void aiExit(Object *objectToExit, CommandSourceType cmdSource);
	void rva0036F400(const Rva003427DD *arg, CommandSourceType cmdSource);
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
	char m_pad[0x258];
	AIUpdateInterface *m_ai;
};

class AIGroup
{
public:
	void rva0036FA56(const Waypoint *waypoint, CommandSourceType cmdSource);
	void groupMoveToAndEvacuate(const Coord3D *pos, CommandSourceType cmdSource);
	void groupMoveToAndEvacuateAndExit(const Coord3D *pos, CommandSourceType cmdSource);
	void rva003700C0(Object *obj, CommandSourceType cmdSource);
	void rva003700F6(Object *obj, CommandSourceType cmdSource);
	void rva0037012C(Object *obj, CommandSourceType cmdSource);
	void rva00370162(Object *obj, CommandSourceType cmdSource);
	void rva00370217(Object *obj, CommandSourceType cmdSource);
	void groupHarvest(const Coord3D *pos, CommandSourceType cmdSource);
	void groupExit(Object *objectToExit, CommandSourceType cmdSource);
	void rva00370399(const Rva003427DD *arg, CommandSourceType cmdSource);
private:
	std::list<Object *> m_memberList;
};

void AIGroup::rva0036FA56(const Waypoint *waypoint, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.aiFollowWaypointPathExact(waypoint, cmdSource);
	}
}

// Ten more AIGroup forwards of the same 54-byte shape, each to the rowed
// AICommandInterface method its call reaches; only the call displacement differs
// from rva0036FA56's bytes. Zero Hour's AIGroup.cpp has groupMoveToAndEvacuate,
// groupMoveToAndEvacuateAndExit and groupExit as exactly this loop over
// aiMoveToAndEvacuate, aiMoveToAndEvacuateAndExit and aiExit; the others keep
// their addresses, as their callees do.

// retail 0x0036FA8C, 54 bytes -> AICommandInterface::aiMoveToAndEvacuate
void AIGroup::groupMoveToAndEvacuate(const Coord3D *pos, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.aiMoveToAndEvacuate(pos, cmdSource);
	}
}

// retail 0x0036FAC2, 54 bytes -> AICommandInterface::aiMoveToAndEvacuateAndExit
void AIGroup::groupMoveToAndEvacuateAndExit(const Coord3D *pos, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.aiMoveToAndEvacuateAndExit(pos, cmdSource);
	}
}

// retail 0x003700C0, 54 bytes -> AICommandInterface::rva0036F19B
void AIGroup::rva003700C0(Object *obj, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F19B(obj, cmdSource);
	}
}

// retail 0x003700F6, 54 bytes -> AICommandInterface::rva0036F200
void AIGroup::rva003700F6(Object *obj, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F200(obj, cmdSource);
	}
}

// retail 0x0037012C, 54 bytes -> AICommandInterface::rva0036F265
void AIGroup::rva0037012C(Object *obj, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F265(obj, cmdSource);
	}
}

// retail 0x00370162, 54 bytes -> AICommandInterface::rva0036F2CA
void AIGroup::rva00370162(Object *obj, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F2CA(obj, cmdSource);
	}
}

// retail 0x00370217, 54 bytes -> AICommandInterface::rva0026C3AC
void AIGroup::rva00370217(Object *obj, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0026C3AC(obj, cmdSource);
	}
}

// retail 0x0037024D, 54 bytes -> AICommandInterface::aiHarvest
void AIGroup::groupHarvest(const Coord3D *pos, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.aiHarvest(pos, cmdSource);
	}
}

// retail 0x00370283, 54 bytes -> AICommandInterface::aiExit
void AIGroup::groupExit(Object *objectToExit, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.aiExit(objectToExit, cmdSource);
	}
}

// retail 0x00370399, 54 bytes -> AICommandInterface::rva0036F400
void AIGroup::rva00370399(const Rva003427DD *arg, CommandSourceType cmdSource)
{
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai != 0)
			ai->m_commands.rva0036F400(arg, cmdSource);
	}
}
