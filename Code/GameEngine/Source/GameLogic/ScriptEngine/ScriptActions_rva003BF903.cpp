// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?Rva003BF903Do@@YGXABVAsciiString@@H@Z @0x003BF903 108B.
// Script team waypoint via getTeamNamed then TerrainLogic slot 0x88,
// createGroup, getTeamAsAIGroup, followWaypointPathExact with 1.
// Evidence: rowed getTeamNamed createGroup getTeamAsAIGroup groupHarvest,
// externs g_Va009FE16C TheTerrainLogic g_Va009FF0F8, caller 0x003CB797.
#include "ascii_string.h"
typedef bool Bool;
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };
struct Coord3D { float x; float y; float z; };
class Team;
class AIGroup;
class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, Bool);
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
	void groupHarvest(const Coord3D *pos, CommandSourceType src);
};
class TerrainLogic
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
	virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
	virtual void d32(); virtual void d33();
	virtual void *v34(int a1);
};
extern class ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern class AI *TheAI;

void __stdcall Rva003BF903Do(const AsciiString &teamName, int way)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	void *obj = TheTerrainLogic->v34(way);
	if (obj == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	group->groupHarvest((const Coord3D *)((char *)obj + 0xc), CMD_FROM_SCRIPT);
}
