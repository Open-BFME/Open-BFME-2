// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva003C87F1Do@@YGXPAVParameter@@ABVAsciiString@@@Z @0x003C87F1 (121B).
// Named follow waypoints exact via getUnitNamed plus closest waypoint plus
// leaveGroup plus aiFollowWaypointPathExact. Evidence: callees rowed
// getUnitNamed 0x003588E7 aiFollow 0x0036ECE7, caller 0x003CA812.
// Precedent doNamedFollowWaypointsExact.
#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Object;
class Waypoint;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };
class Parameter;

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
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

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

class AICommandInterface
{
public:
	void aiFollowWaypointPathExact(const Waypoint *wp, CommandSourceType src);
};

class AIUpdateInterface
{
public:
	char m_pad[0x20];
	AICommandInterface m_command;
};

class Object
{
public:
	void leaveGroup();
private:
	char m_pad0[0x38];
public:
	Coord3D m_position;
private:
	char m_pad1[0x258 - 0x44];
public:
	AIUpdateInterface *m_ai;
};

extern ScriptEngine *TheScriptEngine;

void __stdcall Rva003C87F1Do(Parameter *unitParam, const AsciiString &pathName)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitParam);
	if (!unit)
		return;
	Coord3D pos;
	pos.x = unit->m_position.x;
	pos.y = unit->m_position.y;
	pos.z = unit->m_position.z;
	AIUpdateInterface *ai = unit->m_ai;
	if (!ai)
		return;
	Waypoint *wp = ((TerrainLogicByValue *&)TheTerrainLogic)->getClosestWaypointOnPath(&pos, pathName);
	if (!wp)
		return;
	unit->leaveGroup();
	ai->m_command.aiFollowWaypointPathExact(wp, CMD_FROM_SCRIPT);
}
