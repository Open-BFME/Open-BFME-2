// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Target identity: action-template index 0x134 is NAMED_FACE_WAYPOINT and
// executeAction case 0x134 calls VA 0x007C9A24 (RVA 0x003C9A24), 92 bytes.
// Target body resolves the named Object, obtains a Waypoint through
// TheTerrainLogic vtable slot +0x88, validates AIUpdateInterface at Object+
// 0x258, clears its waypoint queue, leaves its group, then calls the command
// at 0x3C7782 with Waypoint+0x0C and source 1. BFME1 donor maps this behavior
// to doNamedFaceWaypoint and aiFacePosition.

#include "ascii_string.h"

struct Coord3D { float x, y, z; };
class Object;
class Waypoint
{
public:
    const Coord3D *location() const { return (const Coord3D *)((const char *)this + 0x0c); }
};
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
    virtual void _28()=0; virtual void _29()=0; virtual void _30()=0; virtual void _31()=0;
    virtual void _32()=0; virtual void _33()=0;
    virtual Waypoint *getWaypointByName(const AsciiString &) = 0;
};
class AICommandInterface
{
public:
    void aiFacePosition(const Coord3D *, int);
};
class AIUpdateInterface
{
public:
    char pad[0x20];
    AICommandInterface command;
    void clearWaypointQueue();
};
class Object
{
public:
    void leaveGroup();
    AIUpdateInterface *aiUpdate() const
    {
        return *(AIUpdateInterface **)((const char *)this + 0x258);
    }
};
class ScriptActions
{
protected:
    void doNamedFaceWaypoint(const AsciiString &, const AsciiString &);
};
extern ScriptEngine *TheScriptEngine;
extern TerrainLogicByValue *TheTerrainLogic;

void ScriptActions::doNamedFaceWaypoint(const AsciiString &unitName,
    const AsciiString &waypointName)
{
    Object *unit = TheScriptEngine->getUnitNamed(unitName);
    if (!unit) return;
    Waypoint *waypoint = TheTerrainLogic->getWaypointByName(waypointName);
    if (!waypoint) return;
    AIUpdateInterface *ai = unit->aiUpdate();
    if (!ai) return;
    ai->clearWaypointQueue();
    unit->leaveGroup();
    ai->command.aiFacePosition(waypoint->location(), 1);
}
