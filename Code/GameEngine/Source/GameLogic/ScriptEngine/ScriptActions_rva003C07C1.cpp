// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva003C07C1Do@@YGXABVAsciiString@@00@Z @0x003C07C1 136B: team unit command-button order.
// Evidence: rowed getTeamNamed 0x003584E9 with false via g_Va009FE16C, rowed
// lookupUnitByValue 0x00358752 via same global cast to Rva00358752Opaque,
// findCommandButton 0x0031BE3C via g_bfmeWorldRV, createGroup 0x002FEC4B via
// g_Va009FF0F8, getTeamAsAIGroup 0x003A0F62, groupDoCommandButtonAtObject
// 0x0036DCE7; sibling Rva003C0849Do precedent.
#include "ascii_string.h"
typedef bool Bool;

class Object;
class Team;
class AIGroup;
class ControlBar;
class CommandButton;
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT = 1 };

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString, Bool);
};

class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString);
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
	void groupDoCommandButtonAtObject(const CommandButton *commandButton, Object *obj, CommandSourceType cmdSource);
};

struct BfmeWorldRV;
extern class ScriptEngine *TheScriptEngine;
extern class ControlBar *TheControlBar;
extern class AI *TheAI;

void __stdcall Rva003C07C1Do(const AsciiString &teamName, const AsciiString &commandName, const AsciiString &unitName)
{
	Team *team = TheScriptEngine->getTeamNamed((AsciiString &)teamName, false);
	if (team == 0)
		return;
	Object *target = ((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue((AsciiString &)unitName);
	if (target == 0)
		return;
	const CommandButton *button = ((ControlBar *)(*(BfmeWorldRV **)&TheControlBar))->findCommandButton(commandName);
	if (button == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	group->groupDoCommandButtonAtObject(button, target, CMD_FROM_SCRIPT);
}
