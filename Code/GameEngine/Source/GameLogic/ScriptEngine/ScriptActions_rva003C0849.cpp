// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?Rva003C0849Do@@YGXABVAsciiString@@00@Z @0x003C0849 131B: team waypoint command-button order.
// Evidence: rowed getTeamNamed 0x003584E9 with false via g_Va009FE16C, TerrainLogic slot
// 0x88 getWaypointByName via TheTerrainLogic, findCommandButton 0x0031BE3C via
// g_bfmeWorldRV, createGroup 0x002FEC4B via g_Va009FF0F8, getTeamAsAIGroup 0x003A0F62,
// groupDoCommandButtonAtPosition 0x0036DCB8; neighbours ScriptActions 0x003C062D
// 0x003C0983; same shape as Rva003BF813Do precedent.
#include "ascii_string.h"
typedef bool Bool;

struct Coord3D { float x, y, z; };
class Waypoint
{
public:
	const Coord3D *location() const { return (const Coord3D *)((const char *)this + 0x0c); }
};
class CommandButton;
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };

class Team;
class AIGroup;
class ControlBar;

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

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &);
};

class AIGroup
{
public:
	void groupDoCommandButtonAtPosition(const CommandButton *commandButton, const Coord3D *pos, CommandSourceType cmdSource);
};

struct BfmeWorldRV;
extern ScriptEngine *g_Va009FE16C;
extern TerrainLogic *TheTerrainLogic;
extern struct BfmeWorldRV *g_bfmeWorldRV;
extern AI *g_Va009FF0F8;

void __stdcall Rva003C0849Do(const AsciiString &teamName, const AsciiString &commandName, const AsciiString &waypointName)
{
	Team *team = g_Va009FE16C->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (way == 0)
		return;
	const CommandButton *button = ((ControlBar *)g_bfmeWorldRV)->findCommandButton(commandName);
	if (button == 0)
		return;
	AIGroup *group = g_Va009FF0F8->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	group->groupDoCommandButtonAtPosition(button, way->location(), CMD_FROM_SCRIPT);
}
