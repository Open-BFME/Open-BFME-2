// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva003BF71EDo@@YGXABVAsciiString@@0@Z @0x003BF71E 142B
// Script team guard via TerrainLogic slot 0x88 getWaypointByName plus
// getTeamNamed pin 0x003584E9 with false, createGroup pin 0x002FEC4B,
// getTeamAsAIGroup pin 0x003A0F62, then rowed groupGuardPosition guard with
// waypoint Coord3D at +0x0C plus 0 and 1.
// Evidence: TheTerrainLogic 0x009FEC50, TheScriptEngine 0x009FE16C,
// TheAI 0x009FF0F8; caller 0x003CB5C2; precedents Rva003C2A29Script.cpp
// team/group plus doUnitGuardPosition movss x y z order.
#include "ascii_string.h"
typedef bool Bool;

struct Coord3D { float x, y, z; };
class Waypoint
{
public:
	const Coord3D *location() const { return (const Coord3D *)((const char *)this + 0x0c); }
};
enum GuardMode { GUARDMODE_NORMAL = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };

class Team;
class AIGroup;

class ScriptEngine
{
public:
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
	void groupGuardPosition(const Coord3D *pos, GuardMode mode, CommandSourceType src);
};

extern TerrainLogic *TheTerrainLogic;
extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

void __stdcall Rva003BF71EDo(const AsciiString &teamName, const AsciiString &waypointName)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0 || way == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	Coord3D position;
	position.x = way->location()->x;
	position.y = way->location()->y;
	position.z = way->location()->z;
	group->groupGuardPosition(&position, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
}
