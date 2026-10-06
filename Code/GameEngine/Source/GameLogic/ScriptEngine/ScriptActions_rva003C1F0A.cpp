// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
// ?Rva003C1F0A@@YGXABVAsciiString@@ABV?$StringBase@D@@M@Z @0x003C1F0A 98B: Script team to AIGroup anim via getTeamNamed createGroup getTeamAsAIGroup and AIGroup slot10; neighbours ScriptActions_rva003C1E69 ScriptActions_rva003C1FAD; caller 0x003CD5F7.
#include "ascii_string.h"

class Team;
class AIGroup;

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool flag);
};
extern class ScriptEngine *TheScriptEngine;

class AI
{
public:
	AIGroup *createGroup();
};
extern class AI *TheAI;

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *grp);
};

class Drawable;
class Rva002D752DNode;
class Rva002D752D;

class AIGroup
{
public:
	void rva0036E1C3(const StringBase<char> &name, int val);
};

extern int g_Va00DBA4E4;

// ?getTeamNamed@ScriptEngine@@QAEPAVTeam@@VAsciiString@@_N@Z present-unmatched
// ?createGroup@AI@@QAEPAVAIGroup@@XZ present-unmatched
// ?getTeamAsAIGroup@Team@@QAEXPAVAIGroup@@@Z present-unmatched
// ?rva0036E1C3@AIGroup@@QAEXABV?$StringBase@D@@H@Z present-unmatched
void __stdcall Rva003C1F0A(const AsciiString &teamName, const StringBase<char> &animName, float f)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team == 0)
		return;
	AIGroup *grp = TheAI->createGroup();
	if (grp == 0)
		return;
	team->getTeamAsAIGroup(grp);
	int v = (int)((float)g_Va00DBA4E4 * f);
	grp->rva0036E1C3(animName, v);
}
