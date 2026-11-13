// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Target identity: action-template index 0x11E is NAMED_FOLLOW_WAYPOINTS_EXACT;
// executeAction dispatches it to VA 0x007C8773 (RVA 0x003C8773), a 126-byte
// body. Target evidence shows named-unit lookup, Coord3D at Object+0x38,
// AIUpdateInterface at Object+0x258, terrain vtable slot +0x90, leaveGroup,
// and opaque helper at 0x352F2F with waypoint 0x7FFFFFFF and command source 1. BFME1 donor establishes the
// handler's purpose and command semantics; the target body does not perform
// the donor's debug path-purpose check or locomotor-set selection.

#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Object;
class Waypoint;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

#include "../../../Include/GameLogic/ScriptEngine.h"

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

class Rva00352F2FOpaque
{
public:
    void invoke(const Waypoint *, int, CommandSourceType);
};
#include "../../../Include/GameLogic/Module/AIUpdate.h"
#include "../Object/object.h"
class ScriptActions
{
protected:
    void doNamedFollowWaypointsExact(const AsciiString &, const AsciiString &);
};

extern ScriptEngine *TheScriptEngine;
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

void ScriptActions::doNamedFollowWaypointsExact(const AsciiString &unitName,
    const AsciiString &waypointPathLabel)
{
    Object *unit = TheScriptEngine->getUnitNamed(unitName);
    if (!unit) return;
    Coord3D pos;
    pos.x = unit->m_cachedPos.x;
    pos.y = unit->m_cachedPos.y;
    pos.z = unit->m_cachedPos.z;
    AIUpdateInterface *ai = unit->m_ai;
    if (!ai) return;
    Waypoint *waypoint = ((TerrainLogicByValue *)TheTerrainLogic)->getClosestWaypointOnPath(&pos,
        waypointPathLabel);
    if (!waypoint) return;
    unit->leaveGroup();
    // The rowed three-argument helper receives the command subobject at +0x20.
    ((Rva00352F2FOpaque *)&static_cast<AICommandInterface &>(*ai))->invoke(
        waypoint, 0x7fffffff, CMD_FROM_SCRIPT);
}
