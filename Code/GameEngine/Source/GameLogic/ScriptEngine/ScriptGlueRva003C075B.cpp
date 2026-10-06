// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD
//
// ?Rva003C075BDo@@YGXPBVAsciiString@@0@Z @0x003C075B 102B (dump range 18).
// Team command-button dispatch: team-name copy, getTeamNamed, command
// button lookup through the rowed ControlBar 0x0031BE3C member on
// TheControlBar, AI createGroup, getTeamAsAIGroup, then the rowed AIGroup
// groupDoCommandButton 0x0036DC8D member with CMD_FROM_SCRIPT. Straight
// line, all callees rowed. String/global identities unproven.
#include "ascii_string.h"

class CommandButton;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Team
{
public:
	void getTeamAsAIGroup(class AIGroup *group);
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);
};
extern ScriptEngine *TheScriptEngine;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};
extern ControlBar *TheControlBar;

class AIGroup;
class AI
{
public:
	AIGroup *createGroup();
};
extern AI *TheAI;

class AIGroup
{
public:
	void groupDoCommandButton(const CommandButton *btn, CommandSourceType src);
};

void __stdcall Rva003C075BDo(const AsciiString *teamName, const AsciiString *btnName)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (team == 0)
		return;
	const CommandButton *btn = TheControlBar->findCommandButton(*btnName);
	if (btn == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	group->groupDoCommandButton(btn, CMD_FROM_SCRIPT);
}
