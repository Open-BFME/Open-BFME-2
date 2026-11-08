// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003BF71EDo@ScriptActions@@QAEXABVAsciiString@@0@Z @0x003BF71E 142B
// Script team guard via TerrainLogic slot 0x88 getWaypointByName plus
// getTeamNamed pin 0x003584E9 with false, createGroup pin 0x002FEC4B,
// getTeamAsAIGroup pin 0x003A0F62, then rowed groupGuardPosition guard with
// waypoint Coord3D at +0x0C plus 0 and 1.
// Evidence: TheTerrainLogic 0x009FEC50, TheScriptEngine 0x009FE16C,
// TheAI 0x009FF0F8; caller 0x003CB5C2; precedents Rva003C2A29Script.cpp
// team/group plus doUnitGuardPosition movss x y z order.
#include "ascii_string.h"
typedef bool Bool;

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Include/GameLogic/Waypoint.h"
enum GuardMode { GUARDMODE_NORMAL = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };

class Team;
class AIGroup;

#include "../../../Include/GameLogic/ScriptEngine.h"

#include "../../../Include/GameLogic/TerrainLogic.h"

#include "../../../Include/GameLogic/AI.h"

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/AIGroup.h"

extern TerrainLogic *TheTerrainLogic;
extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

void ScriptActions::Rva003BF71EDo(const AsciiString &teamName, const AsciiString &waypointName)
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
	position.x = way->getLocation()->x;
	position.y = way->getLocation()->y;
	position.z = way->getLocation()->z;
	group->groupGuardPosition(&position, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
}
