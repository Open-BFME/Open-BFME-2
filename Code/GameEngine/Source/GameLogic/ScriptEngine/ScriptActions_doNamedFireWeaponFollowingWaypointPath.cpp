// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail RVA 0x003C9206, 146 bytes.
// ?doNamedFireWeaponFollowingWaypointPath@ScriptActions@@IAEXABVAsciiString@@0@Z
// BFME1 donor reference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedFireWeaponFollowingWaypointPath.cpp
// Target evidence: named-unit lookup via rowed getUnitNamed 0x003588E7, Coord3D at Object+0x38,
// terrain vtable slot +0x90 via TheTerrainLogic 0x00DFEC50, rowed rva0028AEEA 0x0028AEEA,
// rowed forceFireWeapon 0x002CE76F, rowed leaveGroup 0x0028C01F, rowed aiFollowWaypointPath 0x0036EC82.
// Caller at 0x003CCA56. Prev Rva003C90B1Exit / next doUnitGuardForFramecount share flags.
#include "ascii_string.h"

struct Coord3D { float x, y, z; };
class Object;
class Waypoint;
struct RvaWeaponSlot;
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

class Weapon
{
public:
    Object *forceFireWeapon(const Object *source, const Coord3D *pos);
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
    RvaWeaponSlot *rva0028AEEA() const;
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
    void doNamedFireWeaponFollowingWaypointPath(const AsciiString &, const AsciiString &);
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogicByValue *TheTerrainLogic;

void ScriptActions::doNamedFireWeaponFollowingWaypointPath(const AsciiString &unitName,
    const AsciiString &waypointPathLabel)
{
    Object *unit = TheScriptEngine->getUnitNamed(unitName);
    if (!unit)
        return;
    Coord3D pos;
    pos.x = unit->m_position.x;
    pos.y = unit->m_position.y;
    pos.z = unit->m_position.z;
    Waypoint *waypoint = TheTerrainLogic->getClosestWaypointOnPath(&pos, waypointPathLabel);
    if (!waypoint)
        return;
    RvaWeaponSlot *slot = unit->rva0028AEEA();
    if (!slot)
        return;
    Object *projectile = ((Weapon *)slot)->forceFireWeapon(unit, &pos);
    if (!projectile)
        return;
    AIUpdateInterface *ai = projectile->m_ai;
    if (!ai)
        return;
    projectile->leaveGroup();
    ai->command.aiFollowWaypointPath(waypoint, CMD_FROM_SCRIPT);
}
