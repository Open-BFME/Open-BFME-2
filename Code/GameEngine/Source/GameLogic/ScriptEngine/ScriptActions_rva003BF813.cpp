// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva003BF813Do@@YGXABVAsciiString@@00@Z @0x003BF813 161B
// Script team trigger waypoint order via getQualifiedTriggerAreaByName pin
// 0x0035768D plus getTeamNamed pin 0x003584E9 with false, TerrainLogic slot
// 0x88 getWaypointByName, createGroup pin 0x002FEC4B, getTeamAsAIGroup pin
// 0x003A0F62, then rowed rva003704D3 with trigger plus 0 1 and waypoint
// Coord3D at +0x0C else rowed rva00370492 with trigger plus 0 1.
// Evidence: TheScriptEngine 0x009FE16C, TheTerrainLogic 0x009FEC50,
// TheAI 0x009FF0F8; callers 0x003CB61F 0x003CB654; precedents Rva003C2A29
// team/group plus doTeamAttackArea trigger sequence.
#include "ascii_string.h"
typedef bool Bool;

class PolygonTrigger;
struct Coord3D { float x, y, z; };
class Waypoint
{
public:
	const Coord3D *location() const { return (const Coord3D *)((const char *)this + 0x0c); }
};
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };

class Team;
class AIGroup;

class ScriptEngine
{
public:
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString);
	Team *getTeamNamed(AsciiString, Bool);
};

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
	virtual Waypoint *getWaypointByName(const AsciiString &) = 0;
};

class AI
{
public:
	AIGroup *createGroup();
};

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

class AIGroup
{
public:
	void rva003704D3(const PolygonTrigger *trigger, int x, CommandSourceType src, const Coord3D *coord);
	void rva00370492(const PolygonTrigger *trigger, int x, CommandSourceType src);
};

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

void __stdcall Rva003BF813Do(const AsciiString &teamName, const AsciiString &areaName, const AsciiString &waypointName)
{
	PolygonTrigger *trigger = TheScriptEngine->getQualifiedTriggerAreaByName((AsciiString &)areaName);
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0 || trigger == 0)
		return;
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	if (way != 0)
		group->rva003704D3(trigger, 0, CMD_FROM_SCRIPT, way->location());
	else
		group->rva00370492(trigger, 0, CMD_FROM_SCRIPT);
}
