// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003BF813Do@ScriptActions@@QAEXABVAsciiString@@00@Z @0x003BF813 161B
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
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Include/GameLogic/Waypoint.h"
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };

class Team;
class AIGroup;

#include "../../../Include/GameLogic/ScriptEngine.h"

#include "../../../Include/GameLogic/TerrainLogic.h"

#include "../../../Include/GameLogic/AI.h"

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameLogic/AIGroup.h"

extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

void ScriptActions::Rva003BF813Do(const AsciiString &teamName, const AsciiString &areaName, const AsciiString &waypointName)
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
		group->rva003704D3(trigger, 0, CMD_FROM_SCRIPT, way->getLocation());
	else
		group->rva00370492(trigger, 0, CMD_FROM_SCRIPT);
}
