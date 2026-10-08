// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva003C1020Do@@YGXABVAsciiString@@0PAVParameter@@@Z @0x003C1020 184B
// Team command-button on object via rowed callees.
// Evidence: caller 0x003CCCBE; neighbours 0x003C0FEA 0x003C10D8;
// globals g_Va009FE16C g_Va009FF0F8 g_bfmeWorldRV; StringBase copy 0x000365F0.
#include "ascii_string.h"
typedef bool Bool;

struct Coord3D { float x, y, z; };
class Waypoint;
class CommandButton;
class Object;
class AIGroup;
class Team;
class Parameter;
struct BfmeWorldRV;

class ScriptEngine {
public:
	Team *getTeamNamed(AsciiString, Bool);
	Object *getUnitNamed(Parameter *);
};

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

class Overridable {
public:
	const Overridable *friend_getFinalOverride() const;
};

enum GUICommandType { GUI_DUMMY = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };
class AIGroup {
public:
	Object *getSpecialPowerSourceObject(unsigned id);
	Object *getCommandButtonSourceObject(GUICommandType type);
	void groupDoCommandButtonAtObject(const CommandButton *b, Object *o, CommandSourceType src);
};

class BfmeObjFBC {
public:
	char bfmeCallFBC(void *a, void *b, int c, void *d);
};

extern class ScriptEngine *TheScriptEngine;
extern class AI *TheAI;
extern class ControlBar *TheControlBar;

void __stdcall Rva003C1020Do(const AsciiString &teamName, const AsciiString &cmdName, Parameter *unitParm)
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
	if (!((BfmeObjFBC *)button)->bfmeCallFBC(src, target, 0, (void *)1))
		return;
	group->groupDoCommandButtonAtObject(button, target, CMD_FROM_SCRIPT);
}
