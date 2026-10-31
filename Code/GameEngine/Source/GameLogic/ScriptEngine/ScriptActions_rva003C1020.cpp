// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C1020Do@ScriptActions@@QAEXABVAsciiString@@0PAVParameter@@@Z @0x003C1020 184B
// Team command-button on object via rowed callees.
// Evidence: caller 0x003CCCBE; neighbours 0x003C0FEA 0x003C10D8;
// globals g_Va009FE16C g_Va009FF0F8 g_bfmeWorldRV; StringBase copy 0x000365F0.
#include "ascii_string.h"
typedef bool Bool;

#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Waypoint;
class CommandButton;
class Object;
class AIGroup;
class Team;
class Parameter;
struct BfmeWorldRV;

#include "../../../Include/GameLogic/ScriptEngine.h"

class AI {
public:
	AIGroup *createGroup();
};

class Team {
public:
	void getTeamAsAIGroup(AIGroup *group);
};

class ControlBar {
public:
	const CommandButton *findCommandButton(const AsciiString &);
};

#include "../../../Include/Common/Overridable.h"

enum GUICommandType { GUI_DUMMY = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };
class AIGroup {
public:
	Object *getSpecialPowerSourceObject(unsigned id);
	Object *getCommandButtonSourceObject(GUICommandType type);
	void groupDoCommandButtonAtObject(const CommandButton *b, Object *o, CommandSourceType src);
};

// LINK: the button check 0x0035B2C3 is rowed as Rva0035B2C3::rva0035B2C3 (Rva0035B2C3Audio.cpp); same four-slot ABI.
class Rva0035B2C3 {
public:
	bool rva0035B2C3(void *a, int b, const Coord3D *c, int d);
};

extern class ScriptEngine *TheScriptEngine;
extern class AI *TheAI;
extern class ControlBar *TheControlBar;

void ScriptActions::Rva003C1020Do(const AsciiString &teamName, const AsciiString &cmdName, Parameter *unitParm)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	team->getTeamAsAIGroup(group);
	const CommandButton *button = ((ControlBar *)(*(BfmeWorldRV **)&TheControlBar))->findCommandButton(cmdName);
	if (button == 0)
		return;
	const Overridable *ov = *(const Overridable *const *)((const char *)button + 0x44);
	Object *src = 0;
	if (ov != 0) {
		ov = ov->friend_getFinalOverride();
		src = group->getSpecialPowerSourceObject(*(const unsigned *)((const char *)ov + 0x14));
	} else {
		src = group->getCommandButtonSourceObject((GUICommandType)*(const int *)((const char *)button + 0x14));
	}
	if (src == 0)
		return;
	Object *target = TheScriptEngine->getUnitNamed(unitParm);
	if (target == 0)
		return;
	if (!((Rva0035B2C3 *)button)->rva0035B2C3(src, (int)target, (const Coord3D *)0, 1))
		return;
	group->groupDoCommandButtonAtObject(button, target, CMD_FROM_SCRIPT);
}
