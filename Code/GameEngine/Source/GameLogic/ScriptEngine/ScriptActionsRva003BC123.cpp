// cl: /Ireference/shims/bfme2_ascii
//
// ?doNamedBuildStructureAtWaypoint@ScriptActions@@IAEXPAVParameter@@ABVAsciiString@@M1@Z @0x003BC123 125B: script action with waypoint and lookup.
// Evidence: getUnitNamed 0x003588E7 with Parameter then TerrainLogic slot 0x88 getWaypointByName with 4th arg then Rva002D06CA 0x002D06CA with 2nd arg then AIUpdate at Object+0x258 slot 0x1F8 with Player from getControllingPlayer plus float plus coords; globals g_Va009FE16C TheTerrainLogic g_009FF000; ret 16.

#include "ascii_string.h"

class Parameter;
class Object;
class Player;
struct Coord3D { float x, y, z; };
class Waypoint
{
public:
	const Coord3D *location() const { return (const Coord3D *)((const char *)this + 0x0c); }
};

class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *param);
};
extern class ScriptEngine *TheScriptEngine;

class TerrainLogic
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
	virtual Waypoint *getWaypointByName(const AsciiString &name) = 0;
};
extern TerrainLogic *TheTerrainLogic;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern class ThingFactory *TheThingFactory;

class AIUpdateInterface
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
	virtual void _32()=0; virtual void _33()=0; virtual void _34()=0; virtual void _35()=0;
	virtual void _36()=0; virtual void _37()=0; virtual void _38()=0; virtual void _39()=0;
	virtual void _40()=0; virtual void _41()=0; virtual void _42()=0; virtual void _43()=0;
	virtual void _44()=0; virtual void _45()=0; virtual void _46()=0; virtual void _47()=0;
	virtual void _48()=0; virtual void _49()=0; virtual void _50()=0; virtual void _51()=0;
	virtual void _52()=0; virtual void _53()=0; virtual void _54()=0; virtual void _55()=0;
	virtual void _56()=0; virtual void _57()=0; virtual void _58()=0; virtual void _59()=0;
	virtual void _60()=0; virtual void _61()=0; virtual void _62()=0; virtual void _63()=0;
	virtual void _64()=0; virtual void _65()=0; virtual void _66()=0; virtual void _67()=0;
	virtual void _68()=0; virtual void _69()=0; virtual void _70()=0; virtual void _71()=0;
	virtual void _72()=0; virtual void _73()=0; virtual void _74()=0; virtual void _75()=0;
	virtual void _76()=0; virtual void _77()=0; virtual void _78()=0; virtual void _79()=0;
	virtual void _80()=0; virtual void _81()=0; virtual void _82()=0; virtual void _83()=0;
	virtual void _84()=0; virtual void _85()=0; virtual void _86()=0; virtual void _87()=0;
	virtual void _88()=0; virtual void _89()=0; virtual void _90()=0; virtual void _91()=0;
	virtual void _92()=0; virtual void _93()=0; virtual void _94()=0; virtual void _95()=0;
	virtual void _96()=0; virtual void _97()=0; virtual void _98()=0; virtual void _99()=0;
	virtual void _100()=0; virtual void _101()=0; virtual void _102()=0; virtual void _103()=0;
	virtual void _104()=0; virtual void _105()=0; virtual void _106()=0; virtual void _107()=0;
	virtual void _108()=0; virtual void _109()=0; virtual void _110()=0; virtual void _111()=0;
	virtual void _112()=0; virtual void _113()=0; virtual void _114()=0; virtual void _115()=0;
	virtual void _116()=0; virtual void _117()=0; virtual void _118()=0; virtual void _119()=0;
	virtual void _120()=0; virtual void _121()=0; virtual void _122()=0; virtual void _123()=0;
	virtual void _124()=0; virtual void _125()=0;
	virtual void slot126(void *a1, const Coord3D *a2, float a3, Player *a4, int a5, int a6) = 0;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	AIUpdateInterface *getAI() const { return *(AIUpdateInterface **)((const char *)this + 0x258); }
};

class ScriptActions
{
protected:
	void doNamedBuildStructureAtWaypoint(Parameter *param, const AsciiString &arg2, float f, const AsciiString &wayName);
};

void ScriptActions::doNamedBuildStructureAtWaypoint(Parameter *param, const AsciiString &arg2, float f, const AsciiString &wayName)
{
	Object *obj = TheScriptEngine->getUnitNamed(param);
	Waypoint *way = TheTerrainLogic->getWaypointByName(wayName);
	void *lookup = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&arg2);
	if (!obj || !way || !lookup)
		return;
	AIUpdateInterface *ai = obj->getAI();
	ai->slot126(lookup, way->location(), f, obj->getControllingPlayer(), 0, 0);
}
