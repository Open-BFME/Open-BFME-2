// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ?Rva003C8A15Do@@YGXPAVParameter@@ABVAsciiString@@1@Z @0x003C8A15 (128B).
// Unit guard in trigger area via getQualifiedTriggerAreaByName plus
// getUnitNamed plus waypoint 0x88 plus rva0036F629 else rva0036F5BB.
// Evidence: callees rowed 0x0035768D 0x003588E7, caller 0x003CB6CD 0x003CB708.
// Precedent Rva003C8B62Do Rva003C87F1Do.
#include "ascii_string.h"

struct Coord3D { float x, y, z; };
class Parameter;
class Object;
class Waypoint;
class PolygonTrigger;
enum CommandSourceType { CMD_FROM_SCRIPT = 1 };

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
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
	virtual Waypoint *getWaypointByName(const AsciiString &name) = 0;
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

class AICommandInterface
{
public:
	void rva0036F629(const PolygonTrigger *area, int v, CommandSourceType src, const Coord3D *pos);
	void rva0036F5BB(const PolygonTrigger *area, int v, CommandSourceType src);
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
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((const char *)this + 0x258); }
};

class Waypoint
{
public:
	const Coord3D *location() const { return (const Coord3D *)((const char *)this + 0x0c); }
};

extern class ScriptEngine *TheScriptEngine;

void __stdcall Rva003C8A15Do(Parameter *unitParam, const AsciiString &areaName, const AsciiString &wayName)
{
	PolygonTrigger *area = TheScriptEngine->getQualifiedTriggerAreaByName(areaName);
	Object *obj = TheScriptEngine->getUnitNamed(unitParam);
	if (!obj)
		return;
	if (!obj->getAI())
		return;
	if (!area)
		return;
	Waypoint *wp = ((TerrainLogicByValue *&)TheTerrainLogic)->getWaypointByName(wayName);
	AIUpdateInterface *ai = obj->getAI();
	if (wp)
		ai->m_command.rva0036F629(area, 0, CMD_FROM_SCRIPT, wp->location());
	else
		ai->m_command.rva0036F5BB(area, 0, CMD_FROM_SCRIPT);
}
