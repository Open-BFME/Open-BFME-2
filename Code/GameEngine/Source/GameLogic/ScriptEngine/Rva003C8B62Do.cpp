// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// ?Rva003C8B62Do@@YGXABVAsciiString@@@Z @0x003C8B62 (105B).
// Team wander-in-place via getTeamNamed plus iterate plus chooseLocomotorSet
// slot 0x238 plus aiWanderInPlace. Evidence: callees rowed getTeamNamed
// 0x003584E9 iterate 0x00263864 advance 0x00263526 aiWander 0x003C7853,
// caller 0x003CB94B. Precedent doTeamGuard.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef int LocomotorSetType;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class Object;
class Locomotor;
class Waypoint;
typedef float Real;

template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};

class AICommandInterface
{
public:
	void aiWanderInPlace(CommandSourceType src);
	void rva003C77EE(const Waypoint *way, CommandSourceType source);
	void rva003C78AF(const Waypoint *way, CommandSourceType source);
};

class AIUpdateInterface : public AIUpdateSlots<142>
{
public:
	virtual Bool chooseLocomotorSet(LocomotorSetType wst) = 0;
private:
	char m_pad[0x20 - 0x04];
public:
	AICommandInterface m_command;
};

class Object
{
public:
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((const char *)this + 0x258); }
	const Coord3D *getPosition() const { return reinterpret_cast<const Coord3D *>((const char *)this + 0x38); }
};

template<class OBJ> class DLINK_ITERATOR
{
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJ *cur() const { return m_cur; }
private:
	OBJ *m_cur;
	char m_pad[20];
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003C8B62Do(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		AIUpdateInterface *ai = obj->getAI();
		if (!ai)
			continue;
		ai->chooseLocomotorSet(3);
		ai->m_command.aiWanderInPlace(CMD_FROM_SCRIPT);
	}
}

// ZH doTeamWander/doTeamPanic and BFME1 f989 ScriptActionsTeamWanderPanic
// supply the whole algorithm. Target 3C8ABF/3C8BCB each proves free RET8,
// native Object+38 scalar position copy, Terrain slot36, AI slot142 and
// separate rowed waypoint-command providers. Original free spellings unknown.
template<int N> class Rva003C8ABFTerrainSlots : public Rva003C8ABFTerrainSlots<N - 1>
{
public:
    virtual void gap(char (*)[N]);
};
template<> class Rva003C8ABFTerrainSlots<0> {};
class TerrainLogic : public Rva003C8ABFTerrainSlots<36>
{
public:
    virtual Waypoint *getClosestWaypointOnPath(const Coord3D *position, const AsciiString &path);
};
extern TerrainLogic *TheTerrainLogic;

void __stdcall Rva003C8ABFDo(const AsciiString &teamName, const AsciiString &path)
{
    Team *team = TheScriptEngine->getTeamNamed(teamName, false);
    if (!team)
        return;
    for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
    {
        Object *object = iter.cur();
        AIUpdateInterface *ai = object->getAI();
        if (!ai)
            continue;
        const Coord3D *p = object->getPosition();
        Coord3D position;
        position.x = p->x;
        position.y = p->y;
        position.z = p->z;
        Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath(&position, path);
        if (!way)
            return;
        ai->chooseLocomotorSet(3);
        ai->m_command.rva003C77EE(way, CMD_FROM_SCRIPT);
    }
}

void __stdcall Rva003C8BCBDo(const AsciiString &teamName, const AsciiString &path)
{
    Team *team = TheScriptEngine->getTeamNamed(teamName, false);
    if (!team)
        return;
    for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance())
    {
        Object *object = iter.cur();
        AIUpdateInterface *ai = object->getAI();
        if (!ai)
            continue;
        const Coord3D *p = object->getPosition();
        Coord3D position;
        position.x = p->x;
        position.y = p->y;
        position.z = p->z;
        Waypoint *way = TheTerrainLogic->getClosestWaypointOnPath(&position, path);
        if (!way)
            return;
        ai->chooseLocomotorSet(4);
        ai->m_command.rva003C78AF(way, CMD_FROM_SCRIPT);
    }
}
