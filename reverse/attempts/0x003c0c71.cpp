// ?Rva003C0C71Do@@YGXPBVAsciiString@@H_N@Z
// partial score=0.92 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva003C0C71Do@@YGXPBVAsciiString@@H_N@Z @0x003C0C71 125B (dump range 18).
// Team sequential-timer dispatch: team-name copy, getTeamNamed, AI
// createGroup, getTeamAsAIGroup, AIGroup getCenter into a dead Coord3D
// (computed but never read in retail), AIGroup 0x0036FC23 member with 1,
// then the rowed ScriptEngine setSequentialTimer 0x00204002 member with
// either the scaled (g_00DBA4E4 * mult) or raw int by flag. Identities
// unproven beyond byte roles.
#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
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
	void setSequentialTimer(Team *team, int v);
};
extern ScriptEngine *TheScriptEngine;

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
	bool getCenter(Coord3D *pos);
	void rva0036FC23(int v);
};

extern int g_00DBA4E4;

void __stdcall Rva003C0C71Do(const AsciiString *teamName, int mult, bool flag)
{
	Team *team = TheScriptEngine->getTeamNamed(*teamName, false);
	if (team == 0)
		return;
	AIGroup *group = TheAI->createGroup();
	if (group == 0)
		return;
	team->getTeamAsAIGroup(group);
	Coord3D center;
	group->getCenter(&center);
	group->rva0036FC23(1);
	TheScriptEngine->setSequentialTimer(team, flag != 0 ? g_00DBA4E4 * mult : mult);
}
