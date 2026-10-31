// cl: /DNDEBUG /MD
// ?rva0036FB57@AIGroup@@QAEXPBVWaypoint@@W4CommandSourceType@@H@Z @0x0036FB57 110B
// Evidence: pin AIGroup; BfmeC986 ready guard 0x0036E357 plus step 0x005494A0; same list-at-+0 plus Object+0x258 plus +0x20 subobject mode switch as Rva0036FAF8Group (mode1 rowed rva00352F9D with 0x7FFFFFFF mode0 rowed aiFollowWaypointPathAsTeam); no m_410 clear like AIGroupWaypointMode; callers 0x003BF4B0 0x003BF5DE.
#include <list>

class Waypoint;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Rva00352F9D
{
public:
	void rva00352F9D(const void *waypoint, int intVal, CommandSourceType cmdSource);
};

enum GuardMode
{
 GUARDMODE_NORMAL = 0,
 GUARDMODE_DUMMY = 0
};
class Rva0035149F;
class Object;
class Team;
struct Coord3D;
class Rva003427DD;
class PolygonTrigger;
struct AICommandParms;
class Rva0035149F;
class Object;
class Team;
struct Coord3D;
class Waypoint;
class Rva003427DD;
class PolygonTrigger;
struct AICommandParms;
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType);
	void rva0036EE16(const Rva0035149F *path, Object *ignoreObject, CommandSourceType cmdSource);
	void aiAttackTeam(const Team *team, int maxShotsToFire, CommandSourceType cmdSource);
	void aiHunt(CommandSourceType cmdSource);
	void rva0036EC1D(Object*,CommandSourceType);
	void aiAttackPosition(const Coord3D *, int, CommandSourceType);
	void aiForceAttackObject(Object*,int,CommandSourceType);
	void rva0026C2D9(Object*,int,CommandSourceType);
	void rva0036EFF5(Object*,CommandSourceType);
	void aiTightenToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiFollowPathAppend(const Coord3D *pos, CommandSourceType cmdSource);
	void aiFollowWaypointPath(const Waypoint *waypoint, CommandSourceType cmdSource);
	void aiFollowWaypointPathExact(const Waypoint *waypoint, CommandSourceType cmdSource);
	void aiMoveToAndEvacuate(const Coord3D *pos, CommandSourceType cmdSource);
	void aiEvacuate(bool exposeStealthUnits, CommandSourceType cmdSource);
	void aiMoveToAndEvacuateAndExit(const Coord3D *pos, CommandSourceType cmdSource);
	void rva0036F19B(Object *obj, CommandSourceType cmdSource);
	void aiResumeConstruction(Object *obj, CommandSourceType cmdSource);
	void aiGetHealed(Object *obj, CommandSourceType cmdSource);
	void aiGetRepaired(Object *obj, CommandSourceType cmdSource);
	void aiDock(Object *obj, CommandSourceType cmdSource);
	void aiHarvest(const Coord3D *pos, CommandSourceType cmdSource);
	void aiExit(Object *objectToExit, CommandSourceType cmdSource);
	void aiGoProne(const Rva003427DD *arg, CommandSourceType cmdSource);
	void aiFollowWaypointPathAsTeam(const Waypoint *waypoint, CommandSourceType cmdSource);
	void aiBfmeCommand33(const Waypoint *waypoint, CommandSourceType cmdSource);
	void rva0026C347(Object *target, CommandSourceType source);
	void aiGuardPosition(const Coord3D *pos, GuardMode mode, CommandSourceType cmdSource);
	void aiGuardObject(Object *obj, int x, CommandSourceType cmdSource);
	void rva0036F54D(const Team *team, int x, CommandSourceType cmdSource);
	void aiGuardArea(const PolygonTrigger *trigger, int x, CommandSourceType cmdSource);
	void aiGuardAreaFromPosition(const PolygonTrigger *trigger, int x, CommandSourceType cmdSource, const Coord3D *coord);
	void aiAttackArea(const PolygonTrigger *area, CommandSourceType cmd);
	void rva0036F6A7(float angle, CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	virtual void aiDoCommand(const struct AICommandParms *parms);
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
	void rva0036FB57(const Waypoint *waypoint, CommandSourceType cmdSource, int mode);
	void createFormation(int a, int b);
	bool rva0036E357();	// 0x0036E357
private:
	std::list<Object *> m_memberList;
};

void AIGroup::rva0036FB57(const Waypoint *waypoint, CommandSourceType cmdSource, int mode)
{
	if (!rva0036E357())
		return;
	createFormation(cmdSource, mode);
	for (std::list<Object *>::iterator i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		AIUpdateInterface *ai = (*i)->m_ai;
		if (ai == 0)
			continue;
		switch (mode)
		{
		case 1:
			reinterpret_cast<Rva00352F9D*>(&ai->m_commands)->rva00352F9D(waypoint, 0x7FFFFFFF, cmdSource);
			break;
		case 0:
			ai->m_commands.aiFollowWaypointPathAsTeam(waypoint, cmdSource);
			break;
		default:
			break;
		}
	}
}
