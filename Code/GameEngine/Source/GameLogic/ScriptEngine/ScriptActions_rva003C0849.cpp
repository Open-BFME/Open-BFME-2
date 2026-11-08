// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C0849Do@ScriptActions@@QAEXABVAsciiString@@00@Z @0x003C0849 131B: team waypoint command-button order.
// Evidence: rowed getTeamNamed 0x003584E9 with false via g_Va009FE16C, TerrainLogic slot
// 0x88 getWaypointByName via TheTerrainLogic, findCommandButton 0x0031BE3C via
// g_bfmeWorldRV, createGroup 0x002FEC4B via g_Va009FF0F8, getTeamAsAIGroup 0x003A0F62,
// groupDoCommandButtonAtPosition 0x0036DCB8; neighbours ScriptActions 0x003C062D
// 0x003C0983; same shape as Rva003BF813Do precedent.
#include "ascii_string.h"
typedef bool Bool;

#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Include/GameLogic/Waypoint.h"
class CommandButton;
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };

class Team;
class AIGroup;
class ControlBar;

#include "../../../Include/GameLogic/ScriptEngine.h"

#include "../../../Include/GameLogic/TerrainLogic.h"

#include "../../../Include/GameLogic/AI.h"

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameClient/ControlBar.h"

#include "../../../Include/GameLogic/AIGroup.h"

struct BfmeWorldRV;
extern class ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
extern class ControlBar *TheControlBar;
extern class AI *TheAI;

void ScriptActions::Rva003C0849Do(const AsciiString &teamName, const AsciiString &commandName, const AsciiString &waypointName)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (way == 0)
		return;
	const CommandButton *button = ((ControlBar *)(*(BfmeWorldRV **)&TheControlBar))->findCommandButton(commandName);
	if (button == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	group->groupDoCommandButtonAtPosition(button, way->getLocation(), CMD_FROM_SCRIPT);
}
