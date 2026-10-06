// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Target identity: action-template index 0x39 is NAMED_FOLLOW_WAYPOINTS;
// executeAction dispatches it to VA 0x007C86FA (RVA 0x003C86FA), a 121-byte
// body. Target evidence shows named-unit lookup, Coord3D at Object+0x38,
// AIUpdateInterface at Object+0x258, terrain vtable slot +0x90, leaveGroup,
// and aiFollowWaypointPath with command source 1. BFME1 donor establishes the
// handler's purpose and command semantics; the target body does not perform
// the donor's debug path-purpose check or locomotor-set selection.

#include "ascii_string.h"

struct Coord3D { float x, y, z; };
class Object;
class Waypoint;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class ScriptEngine
{
public:
    Object *getUnitNamed(const AsciiString &);
};

class TerrainLogicByValue
{
public:
    virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
    virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
    virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
    virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
    virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
    virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
    virtual void _24()=0; virtual void _25()=0; virtual void _26()=0; virtual void _27()=0;
    virtual void _28()=0; virtual void _29()=0; virtual void _30()=0;
    virtual void _31()=0; virtual void _32()=0; virtual void _33()=0;
    virtual void _34()=0; virtual void _35()=0;
    virtual Waypoint *getClosestWaypointOnPath(const Coord3D *, const AsciiString &) = 0;
};

class AICommandInterface
{
public:
    void aiFollowWaypointPath(const Waypoint *, CommandSourceType);
};
class AIUpdateInterface
{
public:
    char pad[0x20];
    AICommandInterface command;
};
class Object
{
public:
    void leaveGroup();
private:
    char pad0[0x38];
public:
    Coord3D m_position;
private:
    char pad1[0x258 - 0x44];
public:
    AIUpdateInterface *m_ai;
};
class ScriptActions
{
protected:
    void doNamedFollowWaypoints(const AsciiString &, const AsciiString &);
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogicByValue *TheTerrainLogic;

void ScriptActions::doNamedFollowWaypoints(const AsciiString &unitName,
    const AsciiString &waypointPathLabel)
{
    Object *unit = TheScriptEngine->getUnitNamed(unitName);
    if (!unit) return;
    Coord3D pos;
    pos.x = unit->m_position.x;
    pos.y = unit->m_position.y;
    pos.z = unit->m_position.z;
    AIUpdateInterface *ai = unit->m_ai;
    if (!ai) return;
    Waypoint *waypoint = TheTerrainLogic->getClosestWaypointOnPath(&pos,
        waypointPathLabel);
    if (!waypoint) return;
    unit->leaveGroup();
    ai->command.aiFollowWaypointPath(waypoint, CMD_FROM_SCRIPT);
}
